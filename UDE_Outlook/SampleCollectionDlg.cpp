// SampleCollectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "SampleCollectionDlg.h"
#include "afxdialogex.h"


// CSampleCollectionDlg �Ի���

IMPLEMENT_DYNAMIC(CSampleCollectionDlg, CTpLayerWnd)


CSampleCollectionDlg::CSampleCollectionDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSampleCollectionDlg::IDD, pParent)
{

}

CSampleCollectionDlg::CSampleCollectionDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CSampleCollectionDlg::~CSampleCollectionDlg()
{
}

void CSampleCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSampleCollectionDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CSampleCollectionDlg ��Ϣ�������


BOOL CSampleCollectionDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_BtBaseOk.ShowWindow(FALSE);
	m_BtBaseCancel.ShowWindow(FALSE);

	SetTitle(_T("�ӱ���"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
