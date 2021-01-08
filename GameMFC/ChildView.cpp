
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "GameMFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define TIMER_PAINT 1
#define TIMER_MOVE 2
#endif

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	CDC *cDC = this->GetDC();
	GetClientRect(&m_client);

	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
	m_cacheDC.SelectObject(&m_cacheCBitmap);

	switch (client_state)
	{
	case 0:
		paint_bgd(_T(".\\res\\title.png"));
		break;
	case 1:
		paint_bgd(_T(".\\res\\select.png"));
		break;
	case 3:
		paint_bgd(_T(".\\res\\background_standard.png"));
		platform.paint_platform(&m_cacheDC);
		paint_num(610, 100, platform.get_level(), 3);
		paint_num(610, 270, platform.get_score(), 3);
		break;
	case 4:
		paint_bgd(_T(".\\res\\background_standard.png"));
		platform.paint_platform(&m_cacheDC);
		paint_num(610, 100, platform.get_level(), 3);
		paint_num(610, 270, platform.get_score(), 3);
		break;
	case 5:
		paint_bgd(_T(".\\res\\background_special.png"));
		platform.paint_platform(&m_cacheDC);
		paint_num(610, 100, platform.get_move(), 3);
		paint_num(610, 270, platform.get_score(), 3);
		break;

	}

	if (info == 1)
	{
		switch (client_state)
		{
		case 0:
			paint_info(_T(".\\res\\help1.png"));
			break;
		case 1:
			paint_info(_T(".\\res\\help2.png"));
			break;
		case 3:
			paint_info(_T(".\\res\\no_more_moves.png"));
			break;
		//case 4:
		//	paint_info(_T(".\\res\\help1.png"));
		//	break;
		case 5:
			paint_info(_T(".\\res\\gameover.png"));
			break;
		}
	}

	if (info == 2)
	{
		switch (client_state)
		{
		case 3:
			paint_info(_T(".\\res\\level_complete.png"));
			break;
		}
	}


	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);

	ValidateRect(&m_client);
	m_cacheDC.DeleteDC();
	m_cacheCBitmap.DeleteObject();
	ReleaseDC(cDC);

	// 不要为绘制消息而调用 CWnd::OnPaint()
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (info == 1)
	{
		info = 0;
		switch (client_state)
		{
		case 3:
			client_state = 0;
			platform.set_ingame(0);
			break;
		case 4:
			client_state = 0;
			platform.set_ingame(0);
			break;
		case 5:
			client_state = 0;
			platform.set_ingame(0);
			break;
		}
	}
	else if (info == 0)
	{
		switch (client_state)
		{
		case 0:
			button(point, 304, 613, 271, 371, 1);
			button(point, 305, 612, 420, 523, -1);
			break;
		case 1:
			if (button(point, 186, 309, 111, 202, 3))
				platform.gem_initialiation(3, 7);
			if (button(point, 483, 606, 107, 203, 4))
				platform.gem_initialiation(4, 7);
			if (button(point, 184, 307, 343, 445, 5))
				platform.gem_initialiation(5, 7);
			button(point, 491, 597, 331, 449, -1);
			button(point, 665, 783, 536, 581, 0);
			break;
		case 2:
			button(point, 400, 600, 400, 600, 0);
			break;
		case 3:
			if (button(point, 600, 800, 400, 600, 0))
				platform.set_ingame(0);
			platform.gem_operation(point);
			break;
		case 4:
			if (button(point, 600, 800, 400, 600, 0))
				platform.set_ingame(0);
			platform.gem_operation(point);
			break;
		case 5:
			if (button(point, 600, 800, 400, 600, 0))
				platform.set_ingame(0);
			platform.gem_operation(point);
			break;

		}
	}
	else
	{
		platform.gem_initialiation(0, 7);
		info = 0;
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::TransparentPNG(CImage * png)
{
	for (int i = 0; i <png->GetWidth(); i++)
	{
		for (int j = 0; j <png->GetHeight(); j++) 
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;            
			pucColor[1] = pucColor[1] * pucColor[3] / 255;            
			pucColor[2] = pucColor[2] * pucColor[3] / 255; 
		}
	}
}

bool CChildView::if_clicked_in(CPoint point, int x1, int x2, int y1, int y2)
{
	if (point.x >= x1 && point.x <= x2)
		if (point.y >= y1 && point.y <= y2)
			return TRUE;
	return FALSE;
}

bool CChildView::button(CPoint point, int x1, int x2, int y1, int y2, int n)
{
	if (if_clicked_in(point, x1, x2, y1, y2))
	{
		if (n == -1)
		{
			info = 1;
			return TRUE;
		}

		client_state = n;
		return TRUE;
	}
	return FALSE;
}

void CChildView::paint_bgd(CString string)
{
	CImage bgd;

	if (FALSE == bgd.Load(string))
	{
		bgd.Draw(m_cacheDC, m_client);
		//bgd.Draw(m_cacheDC, 0, 0, 800, 600);
	}

}

void CChildView::paint_info(CString string)
{
	CImage bgd;

	if (FALSE == bgd.Load(string))
	{
		bgd.Draw(m_cacheDC, 200, 100, m_client.Width() - 400, m_client.Height() - 200);
	}
}

void CChildView::paint_num(int x, int y, int num, int n)
{
	int k = 0;

	for (int i = n;i > 0;--i)
	{
		int temp = num / pow(10, i - 1);
		if (temp > 9) return;
		number[temp].Draw(m_cacheDC, x + k * 50, y, 50, 70);
		num -= temp*pow(10, i - 1);
		++k;
	}
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case TIMER_PAINT:
		CChildView::OnPaint();

		if (platform.get_ingame() != 0)
		{
			platform.gem_move(7, 3, 0);
		}

		if (platform.get_ingame() != 0)
			if (platform.if_cannot_move()) 
			{ 
				platform.set_level(0);
				info = 1; 
			}

		if (platform.get_score() >= (platform.get_level() + 1)*platform.get_level() * 10
			&& platform.get_ingame() != 0)
		{
			switch (client_state)
			{
				case 3:
					info = 2;
					break;
				case 4:
					break;
				case 5:
					platform.set_move(platform.get_move() + 10);
			}
			platform.set_level(platform.get_level() + 1);
		}
		break;
	}

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(TIMER_PAINT, 40, NULL);

	AfxGetMainWnd()->SetWindowText(_T("GeMystery"));

	PlaySound(_T(".\\res\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	number[0].Load(_T(".\\res\\number_0.png"));
	number[1].Load(_T(".\\res\\number_1.png"));
	number[2].Load(_T(".\\res\\number_2.png"));
	number[3].Load(_T(".\\res\\number_3.png"));
	number[4].Load(_T(".\\res\\number_4.png"));
	number[5].Load(_T(".\\res\\number_5.png"));
	number[6].Load(_T(".\\res\\number_6.png"));
	number[7].Load(_T(".\\res\\number_7.png"));
	number[8].Load(_T(".\\res\\number_8.png"));
	number[9].Load(_T(".\\res\\number_9.png"));

	return 0;
}
