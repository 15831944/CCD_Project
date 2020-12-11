#pragma once

#include "Resource.h"

#include "..\\BlendWndDll\\TpLayerWnd.h"

// CFileReply �Ի���

class AFX_EXT_CLASS CFileReply : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CFileReply)

public:
	CFileReply(CWnd* pParent = NULL);   // ��׼���캯��
	CFileReply(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CFileReply();

	// �Ի�������
	enum { IDD = IDD_FILEREPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strOk;
	CString m_strNg;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	void UpdateUi(void);
	void LoadDefaultSet(void);
	void SavedDefaultSet(void);
protected:
	CString m_strOkBkup;
	CString m_strNgBkup;
};
