// CamTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CamTestDlg.h"
#include "afxdialogex.h"


// CCamTestDlg �Ի���

IMPLEMENT_DYNAMIC(CCamTestDlg, CTpLayerWnd)

CCamTestDlg::CCamTestDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CCamTestDlg::IDD, pParent)
{

}

CCamTestDlg::CCamTestDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}


CCamTestDlg::~CCamTestDlg()
{
}

void CCamTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	for (int i = 0; i < CAM_MAX; i++)
	{
		DDX_Control(pDX, IDC_BL_ShowImage0 + i, m_BL_ShowImage[i]);
		DDX_Control(pDX, IDC_BL_ImageText0 + i, m_BL_ImageText[i]);
	}
	
}


BEGIN_MESSAGE_MAP(CCamTestDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CCamTestDlg ��Ϣ�������


BOOL CCamTestDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCamTestDlg::DrawElement(CDC * pDC, CRect rcDraw)
{
	CRect rcShowImage[CAM_MAX];

	CPen  penFrame_2(PS_SOLID,1,RGB(128,128,128));

	pDC->SelectStockObject(NULL_BRUSH);
	for (int x  = 0; x < CAM_MAX; x++)
	{
		m_BL_ShowImage[x].GetWindowRect(rcShowImage[x]);
		ScreenToClient(rcShowImage[x]);   
		pDC->SelectObject(penFrame_2);
		pDC->Rectangle(rcShowImage[x]);
	}
}