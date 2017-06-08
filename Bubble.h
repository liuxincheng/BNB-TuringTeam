#ifndef CBUBBLE_H_
#define CBUBBLE_H_

#include "Sys.h"

class CBubble
{
public:
	HBITMAP m_hBmpBubble;
	int m_nShowID;
	int x;
	int y;
public:
	CBubble();
	~CBubble();
	void BubbleInit(HINSTANCE hIns,int x,int y);
	void BubbleShow(HDC hMemDC);
};

#endif // !CBUBBLE_H_

