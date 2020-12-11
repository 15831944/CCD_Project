// NetCamMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetCamMgr.h"
#include "afxdialogex.h"


// CNetCamMgr �Ի���

IMPLEMENT_DYNAMIC(CNetCamMgr, CTpLayerWnd)

CNetCamMgr::CNetCamMgr(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CNetCamMgr::IDD, pParent)
	, m_nMethod(NET_CAM_CHANGE_BY_INDEX)
	, m_nMethodBkup(NET_CAM_CHANGE_BY_INDEX)
{
	m_NetCam.nNet = 0;
	m_NetCam.nCam = 0;
}

CNetCamMgr::CNetCamMgr(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nMethod(NET_CAM_CHANGE_BY_INDEX)
	, m_nMethodBkup(NET_CAM_CHANGE_BY_INDEX)
{
	m_NetCam.nNet = 0;
	m_NetCam.nCam = 0;
}

CNetCamMgr::~CNetCamMgr()
{
}

void CNetCamMgr::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNetCamMgr, CTpLayerWnd)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CNetCamMgr, CTpLayerWnd)
	ON_EVENT(CNetCamMgr, IDC_RD_NET_CAM_INDEX, 1, CNetCamMgr::StatusChangedRdNetCamIndex, VTS_BOOL)
	ON_EVENT(CNetCamMgr, IDC_RD_NET_CAM_MAC, 1, CNetCamMgr::StatusChangedRdNetCamMac, VTS_BOOL)
END_EVENTSINK_MAP()

// CNetCamMgr ��Ϣ�������


BOOL CNetCamMgr::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_NetCamBkup = m_NetCam;

	_UpdateUi();
	LockCtrls(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CNetCamMgr::OnOK()
{
	m_NetCam.nNet = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_NET)))->GetIntValue() - 1;
	m_NetCam.nCam = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_CAM)))->GetIntValue() - 1;
	m_NetCam.strMac = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_MAC)))->GetValueText();

	m_NetCam.strMac.MakeUpper();
	m_NetCamBkup.strMac.MakeUpper();

	if (m_nMethod != m_nMethodBkup ||
		m_NetCam.nNet != m_NetCamBkup.nNet ||
		m_NetCam.nCam != m_NetCamBkup.nCam ||
		m_NetCam.strMac != m_NetCamBkup.strMac)
	{
		_FileDirty(TRUE);

		CTpLayerWnd::OnOK();
	}
	else
	{
		OnCancel();
	}
}


void CNetCamMgr::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);
	const BOOL bEnable = !bLocked;

	for (int i = 0; i < NET_CAM_CHAGE_METHOD_SUM; i++)
	{
		GetDlgItem(IDC_RD_NET_CAM_INDEX + i)->EnableWindow(bEnable);
	}

	((CBL_Edit *)GetDlgItem(IDC_EDIT_NET_CAM_NET))->SetReadOnly(NET_CAM_CHANGE_BY_INDEX != m_nMethod);
	((CBL_Edit *)GetDlgItem(IDC_EDIT_NET_CAM_CAM))->SetReadOnly(NET_CAM_CHANGE_BY_INDEX != m_nMethod);
	((CBL_Edit *)GetDlgItem(IDC_EDIT_NET_CAM_MAC))->SetReadOnly(NET_CAM_CHANGE_BY_MAC != m_nMethod);

	m_BtBaseOk.EnableWindow(bEnable);

}


void CNetCamMgr::_UpdateUi(void)
{
	for (int i = 0; i < NET_CAM_CHAGE_METHOD_SUM; i++)
	{
		((CBL_Radio *)(GetDlgItem(IDC_RD_NET_CAM_INDEX + i)))->SetSelect(i == m_nMethod);
	}

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_NET)))->SetValue(m_NetCam.nNet + 1);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_CAM)))->SetValue(m_NetCam.nCam + 1);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NET_CAM_MAC)))->SetValueText(m_NetCam.strMac);
}


void CNetCamMgr::StatusChangedRdNetCamIndex(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_nMethod = NET_CAM_CHANGE_BY_INDEX;

	for (int i = 0; i < NET_CAM_CHAGE_METHOD_SUM; i++)
	{
		((CBL_Radio *)(GetDlgItem(IDC_RD_NET_CAM_INDEX + i)))->SetSelect(i == m_nMethod);
	}

	LockCtrls(-1);
}


void CNetCamMgr::StatusChangedRdNetCamMac(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_nMethod = NET_CAM_CHANGE_BY_MAC;

	for (int i = 0; i < NET_CAM_CHAGE_METHOD_SUM; i++)
	{
		((CBL_Radio *)(GetDlgItem(IDC_RD_NET_CAM_INDEX + i)))->SetSelect(i == m_nMethod);
	}

	LockCtrls(-1);
}
