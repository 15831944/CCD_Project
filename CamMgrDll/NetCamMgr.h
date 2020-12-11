#pragma once

#include "CamMgr.h"

enum
{
	NET_CAM_CHANGE_BY_INDEX = 0,
	NET_CAM_CHANGE_BY_MAC,
	NET_CAM_CHAGE_METHOD_SUM
};

// CNetCamMgr �Ի���

class AFX_EXT_CLASS CNetCamMgr : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CNetCamMgr)

public:
	CNetCamMgr(CWnd* pParent = NULL);   // ��׼���캯��
	CNetCamMgr(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CNetCamMgr();

// �Ի�������
	enum { IDD = IDD_NETCAMMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	int m_nMethod;
	ST_INDEX m_NetCam;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void LockCtrls(int nLock);
protected:
	int m_nMethodBkup;
	ST_INDEX m_NetCamBkup;
	void _UpdateUi(void);
public:
	void StatusChangedRdNetCamIndex(BOOL bNewStatus);
	void StatusChangedRdNetCamMac(BOOL bNewStatus);
};
