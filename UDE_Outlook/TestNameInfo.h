#pragma once
#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


// CTestNameInfo �Ի���

class CTestNameInfo : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CTestNameInfo)

public:
	CTestNameInfo(CWnd* pParent = NULL);   // ��׼���캯��
	CTestNameInfo(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CTestNameInfo();

// �Ի�������
	enum { IDD = IDD_TESTNAMEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_strTestName;
	virtual BOOL OnInitDialog();
};
