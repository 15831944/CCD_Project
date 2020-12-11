// AutoLockTime.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoLockTime.h"
#include "afxdialogex.h"


// CAutoLockTime �Ի���

IMPLEMENT_DYNAMIC(CAutoLockTime, CTpLayerWnd)

CAutoLockTime::CAutoLockTime(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAutoLockTime::IDD, pParent)
	, m_nTime(30)
{

}

CAutoLockTime::CAutoLockTime(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nTime(30)
{
}

CAutoLockTime::~CAutoLockTime()
{
}

void CAutoLockTime::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoLockTime, CTpLayerWnd)
END_MESSAGE_MAP()


// CAutoLockTime ��Ϣ�������


BOOL CAutoLockTime::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CBL_DropDown *p = (CBL_DropDown *)GetDlgItem(IDC_DN_AUTO_LOCK_TIME);

	p->SetValue(m_nTime);

	if (_GetPsdLevel() < PSD_LEVEL_TE)
	{
		p->SetReadOnly(_GetPsdLevel() < TRUE);
		m_BtBaseOk.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAutoLockTime::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_nTime = _ttoi(((CBL_DropDown *)GetDlgItem(IDC_DN_AUTO_LOCK_TIME))->GetValueText());

	CTpLayerWnd::OnOK();
}
