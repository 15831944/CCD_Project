#pragma once

#include "TpLayerWnd.h"

// CAutoLockTime �Ի���

class AFX_EXT_CLASS CAutoLockTime : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CAutoLockTime)

public:
	CAutoLockTime(CWnd* pParent = NULL);   // ��׼���캯��
	CAutoLockTime(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAutoLockTime();

// �Ի�������
	enum { IDD = IDD_AUTOLOCKTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nTime;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
