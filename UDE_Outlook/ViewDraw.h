#pragma once

#include <gdiplus.h>
#include "..\BlendFigureDll\FigureBase.h"
#include "..\\StaticCtrlDll\\SmartDC.h"

// CViewDraw �Ի���

#include<vector>

using namespace std;

class CViewDraw : public CFigureBase
{
	DECLARE_DYNAMIC(CViewDraw)

public:
	CViewDraw(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewDraw();

// �Ի�������
	enum { IDD = IDD_VIEWDRAW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawFigure(CDC * pDC, CRect rcDraw);

public:
	int m_nDrawNo;//������̖
	int m_nTestRes;//���C�ľC�Ϝyԇ�Y�� 

	vector<CSmartDC *> m_pdcTopWnd;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
