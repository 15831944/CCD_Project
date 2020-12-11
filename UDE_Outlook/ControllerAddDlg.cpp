// ControllerAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ControllerAddDlg.h"
#include "afxdialogex.h"


// CControllerAddDlg �Ի���

IMPLEMENT_DYNAMIC(CControllerAddDlg, CTpLayerWnd)

CControllerAddDlg::CControllerAddDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CControllerAddDlg::IDD, pParent)
{

}


CControllerAddDlg::CControllerAddDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CControllerAddDlg::~CControllerAddDlg()
{
}

void CControllerAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ControllerName, m_BL_ControllerName);
	DDX_Control(pDX, IDC_BL_ControllerCheckModeName, m_BL_ControllerCheckModeName);
	DDX_Control(pDX, IDC_BL_CtrlCoilStart, m_BL_CtrlCoilStart);
	DDX_Control(pDX, IDC_BL_CtrlCoilEnd, m_BL_CtrlCoilEnd);
	DDX_Control(pDX, IDC_BL_CtrlRegistersStart, m_BL_CtrlRegistersStart);
	DDX_Control(pDX, IDC_BL_CtrlRegistersEnd, m_BL_CtrlRegistersEnd);
}


BEGIN_MESSAGE_MAP(CControllerAddDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CControllerAddDlg ��Ϣ�������


BOOL CControllerAddDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTitle(WINDOWTITLE);
	m_BtBaseClose.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_EVENTSINK_MAP(CControllerAddDlg, CTpLayerWnd)
	ON_EVENT(CControllerAddDlg, IDC_BL_AddOK, 1, CControllerAddDlg::LBtClickedBlAddok, VTS_I4)
	ON_EVENT(CControllerAddDlg, IDC_BL_AddCancel, 1, CControllerAddDlg::LBtClickedBlAddcancel, VTS_I4)
END_EVENTSINK_MAP()


void CControllerAddDlg::LBtClickedBlAddok(long nFlags)
{
	OnOK();
	// TODO: �ڴ˴������Ϣ����������
}


void CControllerAddDlg::LBtClickedBlAddcancel(long nFlags)
{
	OnCancel();
	// TODO: �ڴ˴������Ϣ����������
}
