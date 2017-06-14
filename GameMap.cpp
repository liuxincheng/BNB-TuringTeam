#include "GameMap.h"

CGameMap::CGameMap()
{
	m_bitmap_redBrick = NULL;
	m_bitmap_redHouse = NULL;
	m_bitmap_yellowBrick = NULL;
	m_bitmap_yellowHouse = NULL;
	m_bitmap_Tree = NULL;
	m_bitmap_Box = NULL;
	m_bitmap_blueHouse = NULL;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map_type[i][j] = 0;
		}
	}
}

CGameMap::~CGameMap()
{
	DeleteObject(m_bitmap_redBrick);
	DeleteObject(m_bitmap_redHouse);
	DeleteObject(m_bitmap_yellowBrick);
	DeleteObject(m_bitmap_yellowHouse);
	DeleteObject(m_bitmap_Tree);
	DeleteObject(m_bitmap_Box);
	DeleteObject(m_bitmap_blueHouse);
	m_bitmap_redBrick = NULL;
	m_bitmap_redHouse = NULL;
	m_bitmap_yellowBrick = NULL;
	m_bitmap_yellowHouse = NULL;
	m_bitmap_Tree = NULL;
	m_bitmap_Box = NULL;
	m_bitmap_blueHouse = NULL;
}

void CGameMap::MapInit(HINSTANCE hIns)
{
	m_bitmap_redBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDBRICK));
	m_bitmap_redHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDHOUSE));
	m_bitmap_yellowBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWBRICK));
	m_bitmap_yellowHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWHOUSE));
	m_bitmap_Tree = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TREE));
	m_bitmap_Box = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BOX));
	m_bitmap_blueHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BLUEHOUSE));

	// 加载地图数据
	FILE *fp = NULL;
	fopen_s(&fp,"mapData/map_village1.txt","r");
	// 打开文件成功
	if (fp != NULL)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp,"%d",&map_type[i][j]);
			}
		}

		fclose(fp);
	}
	// 打开文件失败
	else
	{
		if ( MessageBox( NULL, TEXT("地图初始化失败!"), TEXT("加载程序错误"), MB_OK | MB_ICONERROR ) == IDOK )
		{
			PostQuitMessage(0);
		}
	}
}

void CGameMap::MapShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			x = j * 40 + 20;
			y = i * 40 + 41;

			if (map_type[i][j] == B_H_)
			{
				SelectObject(hdcMem,m_bitmap_blueHouse);
				TransparentBlt(hdc,x,y-17,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == R_H_)
			{
				SelectObject(hdcMem,m_bitmap_redHouse);
				TransparentBlt(hdc,x,y-17,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == Y_H_)
			{
				SelectObject(hdcMem,m_bitmap_yellowHouse);
				TransparentBlt(hdc,x,y-17,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == R_B_)
			{
				SelectObject(hdcMem,m_bitmap_redBrick);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == Y_B_)
			{
				SelectObject(hdcMem,m_bitmap_yellowBrick);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == Tree)
			{
				SelectObject(hdcMem,m_bitmap_Tree);
				TransparentBlt(hdc,x,y-27,40,67,hdcMem,0,0,40,67,RGB(255,0,255));
			}
			if (map_type[i][j] == Box)
			{
				SelectObject(hdcMem,m_bitmap_Box);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
		}
	}

	DeleteDC(hdcMem);
}

void CGameMap::MapBlast(int i, int j, int power)
{
	switch (power)
	{
	case 1:
		// 泡泡威力为1格
		BlastBlock_One(i,j);
		break;
	case 2:
		// 泡泡威力为2格
		BlastBlock_One(i,j);
		BlastBlock_Two(i,j);
		break;
	case 3:
		// 泡泡威力为3格
		BlastBlock_One(i,j);
		BlastBlock_Two(i,j);
		BlastBlock_Three(i,j);
		break;
	case 4:
		// 泡泡威力为4格
		BlastBlock_One(i,j);
		BlastBlock_Two(i,j);
		BlastBlock_Three(i,j);
		BlastBlock_Four(i,j);
		break;
	default:
		BlastBlock_One(i,j);
		break;
	}
}

void CGameMap::BlastBlock_One(int i, int j)
{
	// 泡泡 →
	if ( i < MAP_HEIGHT - 1 && map_type[i+1][j] <= Box && map_type[i+1][j] != No)
	{
		map_type[i+1][j] = No;
	}
	// 泡泡 ←
	if ( i > 0 && map_type[i-1][j] <= Box && map_type[i-1][j] != No)
	{
		map_type[i-1][j] = No;
	}
	// 泡泡 ↓
	if ( j < MAP_WIDTH - 1 && map_type[i][j+1] <= Box && map_type[i][j+1] != No)
	{
		map_type[i][j+1] = No;
	}
	// 泡泡 ↑
	if ( j > 0 && map_type[i][j-1] <= Box && map_type[i][j-1] != No)
	{
		map_type[i][j-1] = No;
	}
}

void CGameMap::BlastBlock_Two(int i, int j)
{
	if ( i < MAP_HEIGHT - 2 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box && map_type[i+2][j] != No)
	{
		map_type[i+2][j] = No;
	}
	if ( i > 1 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-2][j] != No)
	{
		map_type[i-2][j] = No;
	}
	if ( j < MAP_WIDTH - 2 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+2] != No)
	{
		map_type[i][j+2] = No;
	}
	if ( j > 1 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-2] != No)
	{
		map_type[i][j-2] = No;
	}
}

void CGameMap::BlastBlock_Three(int i, int j)
{
	if ( i < MAP_HEIGHT - 3 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box &&  map_type[i+3][j] <= Box && map_type[i+3][j] != No)
	{
		map_type[i+3][j] = No;
	}
	if ( i > 2 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-3][j] <= Box && map_type[i-3][j] != No)
	{
		map_type[i-3][j] = No;
	}
	if ( j < MAP_WIDTH - 3 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+3] <= Box && map_type[i][j+3] != No)
	{
		map_type[i][j+3] = No;
	}
	if ( j > 2 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-3] <= Box && map_type[i][j-3] != No)
	{
		map_type[i][j-3] = No;
	}
}

void CGameMap::BlastBlock_Four(int i, int j)
{
	if ( i < MAP_HEIGHT - 4 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box &&  map_type[i+3][j] <= Box &&  map_type[i+4][j] <= Box && map_type[i+4][j] != No)
	{
		map_type[i+4][j] = No;
	}
	if ( i > 3 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-3][j] <= Box && map_type[i-4][j] <= Box && map_type[i-4][j] != No)
	{
		map_type[i-4][j] = No;
	}
	if ( j < MAP_WIDTH - 4 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+3] <= Box && map_type[i][j+4] <= Box && map_type[i][j+4] != No)
	{
		map_type[i][j+4] = No;
	}
	if ( j > 3 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-3] <= Box && map_type[i][j-4] <= Box && map_type[i][j-4] != No)
	{
		map_type[i][j-4] = No;
	}
}