#pragma once

#include "Resource.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#endif

// CVerisonManage �Ի���

#include <vector>
#include <deque>
using namespace std;


// CProcessCommMgr �Ի���

class AFX_EXT_CLASS CProcessCommMgr : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CProcessCommMgr)

public:
	CProcessCommMgr(CWnd* pParent = NULL);   // ��׼���캯��
	CProcessCommMgr(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CProcessCommMgr();

// �Ի�������
	enum { IDD = IDD_PROCESSCOMMMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProcessName;
	CBL_Edit m_BL_ProcessName;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
