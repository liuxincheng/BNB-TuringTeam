#ifndef CBUBBLE_H_
#define CBUBBLE_H_

#include "Sys.h"

class CBubble
{
public:
	CBubble();
	~CBubble();
	void BubbleInit(HINSTANCE hIns,int x,int y, int power);
	void BubbleShow(HDC hMemDC);
	void BoomShow(HDC hMemDC);

public:
	int m_nShowID;
	int m_nBubbleBj;      // ȷ��ʹ������������Ժ���ʧ��ͼƬѭ�����ͼƬ�����ݣ���������Ϊ16
	int m_nBubble_x;
	int m_nBubble_y;
	int m_nBubble_power;  // ���ݱ�ը���� 1 ~ 4
	int m_arrfx[4];       // ���ݱ�ը���췶Χ
	int m_nBoomShowID;
private:
	HBITMAP m_bitmap_bubble;
	HBITMAP m_bitmap_shadow_bubble;
	HBITMAP m_bitmap_boom;
};

#endif // !CBUBBLE_H_

