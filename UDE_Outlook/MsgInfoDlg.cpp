// MsgInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "MsgInfoDlg.h"
#include "afxdialogex.h"


// CMsgInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CMsgInfoDlg, CTpLayerWnd)

CMsgInfoDlg::CMsgInfoDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CMsgInfoDlg::IDD, pParent)
{

}


CMsgInfoDlg::CMsgInfoDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{
}


CMsgInfoDlg::~CMsgInfoDlg()
{
}

void CMsgInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_BT_ErrorInfo, m_BL_BT_ErrorInfo);
}


BEGIN_MESSAGE_MAP(CMsgInfoDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CMsgInfoDlg ��Ϣ�������
