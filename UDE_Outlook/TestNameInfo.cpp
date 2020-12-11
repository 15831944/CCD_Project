// TestNameInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "TestNameInfo.h"
#include "afxdialogex.h"


// CTestNameInfo �Ի���

IMPLEMENT_DYNAMIC(CTestNameInfo, CTpLayerWnd)

CTestNameInfo::CTestNameInfo(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CTestNameInfo::IDD, pParent)
{

}

CTestNameInfo::CTestNameInfo(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	
{

}

CTestNameInfo::~CTestNameInfo()
{
}

void CTestNameInfo::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestNameInfo, CTpLayerWnd)
END_MESSAGE_MAP()


// CTestNameInfo ��Ϣ�������


void CTestNameInfo::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_strTestName = ((CBL_Edit *)(GetDlgItem(IDC_BL_edTestNameInfo)))->GetValueText();
	CTpLayerWnd::OnOK();
}


BOOL CTestNameInfo::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CBL_Edit *)(GetDlgItem(IDC_BL_edTestNameInfo)))->SetValueText(m_strTestName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
