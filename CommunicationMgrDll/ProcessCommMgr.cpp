// ProcessCommMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessCommMgr.h"
#include "afxdialogex.h"


// CProcessCommMgr �Ի���

IMPLEMENT_DYNAMIC(CProcessCommMgr, CTpLayerWnd)

CProcessCommMgr::CProcessCommMgr(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CProcessCommMgr::IDD, pParent)
{

}


CProcessCommMgr::CProcessCommMgr(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}


CProcessCommMgr::~CProcessCommMgr()
{
}

void CProcessCommMgr::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ProcessName, m_BL_ProcessName);
}


BEGIN_MESSAGE_MAP(CProcessCommMgr, CTpLayerWnd)
END_MESSAGE_MAP()


// CProcessCommMgr ��Ϣ�������


BOOL CProcessCommMgr::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	m_BL_ProcessName.SetValueText(m_strProcessName);

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}


void CProcessCommMgr::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	const CString strName = m_BL_ProcessName.GetValueText();

	HWND hWnd = ::FindWindow(NULL, strName);//����Ŀ�괰��
	if(hWnd != NULL)
	{
		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(_T("�������Q�Ѵ��ڣ�Ո�_�J��"), _T("�������}"), MB_OK);
		return;
	}

	m_strProcessName = strName;

	CTpLayerWnd::OnOK();
}
