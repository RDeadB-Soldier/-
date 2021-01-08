
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "Platform.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	//BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	CRect m_client;
	CDC m_cacheDC;
	CBitmap m_cacheCBitmap;

	//client_state
	//记录游戏的状态
	//0:开始界面
	//1:选择模式
	//3:标准
	//4:无尽
	//5:谜题
	//6:
	//7:
	//8:
	int client_state = 0;
	Platform platform;

	int info = 0;
	
	CImage number[10];

	bool if_clicked_in(CPoint point, int x1, int x2, int y1, int y2);
	bool button(CPoint point, int x1, int x2, int y1, int y2, int n);

	void paint_bgd(CString string);
	void paint_info(CString string);
	void paint_num(int x, int y, int num, int n);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void TransparentPNG(CImage *png);

};

