#include "GameMap.h"

int CGameMap::map_type[MAP_HEIGHT][MAP_WIDTH] = 
{
	{No,RedHouse,RedBrick,RedHouse,RedBrick,Tree,No,Tree,No,Tree,RedBrick,BlueHouse,RedBrick,BlueHouse,No},
	{No,No,YellowBrick,RedBrick,YellowBrick,RedBrick,No,No,No,RedBrick,YellowBrick,RedBrick,YellowBrick,No,No},
	{No,RedHouse,RedBrick,RedHouse,RedBrick,Tree,Box,Tree,Box,Tree,RedBrick,BlueHouse,RedBrick,BlueHouse,No},
	{YellowBrick,RedBrick,YellowBrick,RedBrick,Tree,Box,Box,RedBrick,Box,Box,Tree,RedBrick,YellowBrick,RedBrick,YellowBrick},
	{RedBrick,Tree,RedBrick,Tree,Box,Box,Tree,No,Tree,Box,Box,Tree,RedBrick,Tree,RedBrick},
	{YellowBrick,No,Box,No,No,Tree,RedBrick,RedBrick,RedBrick,Tree,No,No,Box,No,YellowBrick},
	{YellowBrick,Tree,RedBrick,Tree,No,YellowBrick,No,No,No,YellowBrick,No,Tree,RedBrick,Tree,YellowBrick},
	{YellowBrick,No,Box,No,No,Tree,RedBrick,RedBrick,RedBrick,Tree,No,No,Box,No,YellowBrick},
	{YellowBrick,RedBrick,YellowBrick,RedBrick,Tree,Box,Box,RedBrick,Box,Box,Tree,RedBrick,YellowBrick,RedBrick,YellowBrick},
	{No,BlueHouse,RedBrick,BlueHouse,RedBrick,Tree,Box,Tree,Box,Tree,RedBrick,YellowHouse,RedBrick,YellowHouse,No},
	{No,No,YellowBrick,RedBrick,YellowBrick,RedBrick,No,No,No,RedBrick,YellowBrick,RedBrick,YellowBrick,No,No},
	{No,BlueHouse,RedBrick,BlueHouse,RedBrick,Tree,No,Tree,No,Tree,RedBrick,YellowHouse,RedBrick,YellowHouse,No},
};

CGameMap::CGameMap()
{
	m_bitmap_road = NULL;
	m_bitmap_redBrick = NULL;
	m_bitmap_redHouse = NULL;
	m_bitmap_yellowBrick = NULL;
	m_bitmap_yellowHouse = NULL;
	m_bitmap_Tree = NULL;
	m_bitmap_Box = NULL;
	m_bitmap_blueHouse = NULL;
}


CGameMap::~CGameMap()
{
	DeleteObject(m_bitmap_road);
	DeleteObject(m_bitmap_redBrick);
	DeleteObject(m_bitmap_redHouse);
	DeleteObject(m_bitmap_yellowBrick);
	DeleteObject(m_bitmap_yellowHouse);
	DeleteObject(m_bitmap_Tree);
	DeleteObject(m_bitmap_Box);
	DeleteObject(m_bitmap_blueHouse);
	m_bitmap_road = NULL;
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
	m_bitmap_road = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ROAD));
	m_bitmap_redBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDBRICK));
	m_bitmap_redHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDHOUSE));
	m_bitmap_yellowBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWBRICK));
	m_bitmap_yellowHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWHOUSE));
	m_bitmap_Tree = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TREE));
	m_bitmap_Box = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BOX));
	m_bitmap_blueHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BLUEHOUSE));
}

void CGameMap::MapShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_road);
	BitBlt(hdc,20,41,800,600,hdcMem,0,0,SRCCOPY);

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			x = j * 40 + 20;
			y = i * 44 + 36;

			if (map_type[i][j] == BlueHouse)
			{
				SelectObject(hdcMem,m_bitmap_blueHouse);
				TransparentBlt(hdc,x,y-14,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == RedHouse)
			{
				SelectObject(hdcMem,m_bitmap_redHouse);
				TransparentBlt(hdc,x,y-14,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == YellowHouse)
			{
				SelectObject(hdcMem,m_bitmap_yellowHouse);
				TransparentBlt(hdc,x,y-14,40,57,hdcMem,0,0,40,57,RGB(255,0,255));
			}
			if (map_type[i][j] == RedBrick)
			{
				SelectObject(hdcMem,m_bitmap_redBrick);
				BitBlt(hdc,x,y,40,44,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == YellowBrick)
			{
				SelectObject(hdcMem,m_bitmap_yellowBrick);
				BitBlt(hdc,x,y,40,44,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == Tree)
			{
				SelectObject(hdcMem,m_bitmap_Tree);
				TransparentBlt(hdc,x,y-28,40,67,hdcMem,0,0,40,67,RGB(255,0,255));
			}
			if (map_type[i][j] == Box)
			{
				SelectObject(hdcMem,m_bitmap_Box);
				BitBlt(hdc,x,y,40,44,hdcMem,0,0,SRCCOPY);
			}
		}
	}

	DeleteDC(hdcMem);
}
