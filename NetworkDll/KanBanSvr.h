#pragma once

#include "FileReply.h"

#define NET_KANBAN_DEFAULT_PORT	9999

// CKanBanSvr �Ի���

class AFX_EXT_CLASS CKanBanSvr : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CKanBanSvr)

public:
	CKanBanSvr(CWnd* pParent = NULL);   // ��׼���캯��
	CKanBanSvr(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CKanBanSvr();

	// �Ի�������
	enum { IDD = IDD_KANBANSVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	CString m_strIp;
	int m_nPort;
	CString m_strStartFix;
	CString m_strEndFix;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	void UpdateUi(void);
	void LoadDefaultSet(void);
	void SaveDefaultSet(void);
protected:
	CString m_strIpBkup;
	int m_nPortBkup;
	CString m_strStartFixBkup;
	CString m_strEndFixBkup;
public:
	void IpChangedIpKanbanSvr(LPCTSTR strNew);
};
