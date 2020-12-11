// ProjectName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ProjectName.h"
#include "afxdialogex.h"


// CProjectName �Ի���

IMPLEMENT_DYNAMIC(CProjectName, CTpLayerWnd)

CProjectName::CProjectName(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CProjectName::IDD, pParent)
	, m_strProjectName(_T(""))
{

}

CProjectName::CProjectName(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(CProjectName::IDD, pParent)
	, m_strProjectName(_T(""))
{
}

CProjectName::~CProjectName()
{
}

void CProjectName::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ProjectName, m_BL_ProjectName);
}


BEGIN_MESSAGE_MAP(CProjectName, CTpLayerWnd)
END_MESSAGE_MAP()


// CProjectName ��Ϣ�������


BOOL CProjectName::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CProjectName::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_strProjectName;
	}
	else
	{	// loading code
		ar >> m_strProjectName;
		m_pProjectName->SendMessage(WM_PROJECTNAMECHANGE);
	}
}


void CProjectName::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_strProjectName = m_BL_ProjectName.GetValueText();
	m_pProjectName->SendMessage(WM_PROJECTNAMECHANGE);
	CTpLayerWnd::OnOK();
}


void CProjectName::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CTpLayerWnd::OnCancel();
}
