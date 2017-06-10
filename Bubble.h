#ifndef CBUBBLE_H_
#define CBUBBLE_H_

#include "Sys.h"

class CBubble
{
public:
	CBubble();
	~CBubble();
	void BubbleInit(HINSTANCE hIns,int x,int y);
	void BubbleShow(HDC hMemDC);
public:
	int m_nShowID;
	int m_nBubbleBj; // 确定使泡泡跳动五次以后消失，图片循环五次图片有三份，所以设置为16
private:
	HBITMAP m_bitmap_bubble;
	int m_nBubble_x;
	int m_nBubble_y;
};

#endif // !CBUBBLE_H_

