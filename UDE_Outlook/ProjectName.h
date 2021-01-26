#pragma once

#include "..\BlendWndDll\MsgBox.h"
#include "..\CamMgrDll\CamShow.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CamMgrDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CamMgrDll.lib")
#endif

// CProjectName �Ի���

class CProjectName : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CProjectName)

public:
	CProjectName(CWnd* pParent = NULL);   // ��׼���캯��
	CProjectName(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CProjectName();

// �Ի�������
	enum { IDD = IDD_PROJECTNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProjectName;

	virtual BOOL OnInitDialog();
public:
	CBL_Edit m_BL_ProjectName;
public:
	virtual void OnOK();
	virtual void OnCancel();
};
