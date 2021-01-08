
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "Platform.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	//BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	CRect m_client;
	CDC m_cacheDC;
	CBitmap m_cacheCBitmap;

	//client_state
	//��¼��Ϸ��״̬
	//0:��ʼ����
	//1:ѡ��ģʽ
	//3:��׼
	//4:�޾�
	//5:����
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

