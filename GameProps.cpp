#include "GameProps.h"

CGameProps::CGameProps()
{
	m_bitmap_energybubble=NULL;
	m_bitmap_energywater = NULL;
	m_bitmap_rollerskate = NULL;
	m_bitmap_redhead = NULL;
	m_bitmap_powerball = NULL;
	m_nposh = 0;
	m_nposw = 0;
	m_nShowID = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_bj[i][j]=noprop;
		}
	}
	for (int i=0;i<4;i++)
	{
		energybubblewpos[i]=0;
	}
	for (int i=0;i<4;i++)
	{
		energybubblehpos[i]=0;
	}
	for (int i=0;i<4;i++)
	{
		energywaterwpos[i]=0;
	}
	for (int i=0;i<4;i++)
	{
		energywaterhpos[i]=0;
	}
	for (int i=0;i<3;i++)
	{
		rollerskatewpos[i]=0;
	}
	for (int i=0;i<3;i++)
	{
		rollerskatehpos[i]=0;
	}
	for (int i=0;i<2;i++)
	{
		edheadwpos[i]=0;
	}
	for (int i=0;i<2;i++)
	{
		edheadhpos[i]=0;

	}
	for (int i=0;i<2;i++)
	{
		powerballwpos[i]=0;
	}
	for (int i=0;i<2;i++)
	{
		powerballhpos[i]=0;
	}
}

CGameProps::~CGameProps()
{
	DeleteObject(m_bitmap_energybubble);
	DeleteObject(m_bitmap_energywater);
	DeleteObject(m_bitmap_rollerskate);
	DeleteObject(m_bitmap_redhead);
	DeleteObject(m_bitmap_powerball);
	m_bitmap_energybubble=NULL;
	m_bitmap_energywater=NULL;
	m_bitmap_rollerskate=NULL;
	m_bitmap_redhead=NULL;
	m_bitmap_powerball=NULL;

}

void CGameProps::PropInit(HINSTANCE hIns)
{
	srand((unsigned int)time(0));
	//加载图片
	m_bitmap_energybubble=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WATER_BUBBLE));
	m_bitmap_energywater=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_POWER_WATER));
	m_bitmap_rollerskate=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SPEED_SHOE));
	m_bitmap_redhead=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAX_SPEED));
	m_bitmap_powerball=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAX_POWER));
	m_nShowID=2;
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
				fscanf_s(fp,"%d",&map.map_type[i][j]);
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
	for (int a=0;a<4;a++)
	{
		energybubblewpos[a]=rand()%MAP_WIDTH;
	}
	for (int a=0;a<4;a++)
	{
		energybubblehpos[a]=rand()%MAP_HEIGHT;
	}
	for (int i=0;i<4;i++)
	{
		if((map.map_type[energybubblehpos[i]][energybubblewpos[i]]==R_B_||map.map_type[energybubblehpos[i]][energybubblewpos[i]]==Y_B_) && m_bj[energybubblehpos[i]][energybubblewpos[i]] == noprop)
		{
			m_bj[energybubblehpos[i]][energybubblewpos[i]]=energybubble;
		}
	}
	for (int a=0;a<4;a++)
	{
		energywaterwpos[a]=rand()%MAP_WIDTH;
	}
	for (int a=0;a<4;a++)
	{
		energywaterhpos[a]=rand()%MAP_HEIGHT;
	}
	for (int i=0;i<4;i++)
	{
		if((map.map_type[energywaterhpos[i]][energywaterwpos[i]]==R_B_||map.map_type[energywaterhpos[i]][energywaterwpos[i]]==Y_B_) && m_bj[energywaterhpos[i]][energywaterwpos[i]] == noprop)
		{
			m_bj[energywaterhpos[i]][energywaterwpos[i]]=energywater;
		}
	}
	for (int a=0;a<3;a++)
	{
		rollerskatewpos[a]=rand()%MAP_WIDTH;
	}
	for (int a=0;a<3;a++)
	{
		rollerskatehpos[a]=rand()%MAP_HEIGHT;
	}
	for (int i=0;i<3;i++)
	{
		if((map.map_type[rollerskatehpos[i]][rollerskatewpos[i]]==R_B_||map.map_type[rollerskatehpos[i]][rollerskatewpos[i]]==Y_B_) && m_bj[rollerskatehpos[i]][rollerskatewpos[i]] == noprop)
		{
			m_bj[rollerskatehpos[i]][rollerskatewpos[i]]=rollerskate;
		}

	}
	for (int a=0;a<3;a++)
	{
		edheadwpos[a]=rand()%MAP_WIDTH;
	}
	for (int a=0;a<2;a++)
	{
		edheadhpos[a]=rand()%MAP_HEIGHT;

	}
	for (int i=0;i<2;i++)
	{
		if((map.map_type[edheadhpos[i]][edheadwpos[i]]==R_B_ || map.map_type[edheadhpos[i]][edheadwpos[i]]==Y_B_) && m_bj[edheadhpos[i]][edheadwpos[i]] == noprop)
		{
			m_bj[edheadhpos[i]][edheadwpos[i]] = redhead;
		}
	}

	for (int a=0;a<2;a++)
	{
		powerballwpos[a]=rand()%MAP_WIDTH;
	}
	for (int a=0;a<2;a++)
	{
		powerballhpos[a]=rand()%MAP_HEIGHT;
	}
	for (int i=0;i<2;i++)
	{
		if((map.map_type[powerballhpos[i]][powerballwpos[i]]==R_B_ || map.map_type[powerballhpos[i]][powerballwpos[i]]==Y_B_) && m_bj[powerballhpos[i]][powerballwpos[i]] == noprop)
		{
			m_bj[powerballhpos[i]][powerballwpos[i]] = powerball;
		}
	}
}


void CGameProps::PropPositionShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	int x = 0;
	int y = 0;
	for (int i=0;i<4;i++)
	{
		x = energybubblewpos[i] * 40 + 20;
		y = energybubblehpos[i] * 40 + 41;
		if( m_bj[energybubblehpos[i]][energybubblewpos[i]] == energybubble)
		{
			SelectObject(hdcMem,m_bitmap_energybubble);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int j=0;j<4;j++)
	{
		x = energywaterwpos[j] * 40 + 20;
		y = energywaterhpos[j] * 40 + 41;
		if(m_bj[energywaterhpos[j]][energywaterwpos[j]] == energywater)
		{
			SelectObject(hdcMem,m_bitmap_energywater);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int k=0;k<3;k++)
	{

		x = rollerskatewpos[k] * 40 + 20;
		y = rollerskatehpos[k] * 40 + 41;
		if(m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == rollerskate)
		{
			SelectObject(hdcMem,m_bitmap_rollerskate);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int m=0;m<2;m++)
	{

		x = edheadwpos[m] * 40 + 20;
		y = edheadhpos[m] * 40 + 41;
		if(m_bj[edheadhpos[m]][edheadwpos[m]] == redhead)
		{
			SelectObject(hdcMem,m_bitmap_redhead);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int n=0;n<2;n++)
	{

		x = powerballwpos[n] * 40 + 20;
		y = powerballhpos[n] * 40 + 41;
		if(m_bj[powerballhpos[n]][powerballwpos[n]] == powerball)
		{
			SelectObject(hdcMem,m_bitmap_powerball);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}

	DeleteDC(hdcMem);
}
