#pragma once

#include "MsgBox.h"

// CStartDelay �Ի���

class AFX_EXT_CLASS CStartDelay : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CStartDelay)

public:
	CStartDelay(CWnd* pParent = NULL);   // ��׼���캯��
	CStartDelay(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CStartDelay();

// �Ի�������
	enum { IDD = IDD_STARTDELAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nDelay;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void LockCtrls(int nLock);
};
