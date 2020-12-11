#pragma once

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CControllerDlg �Ի���

class CControllerDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CControllerDlg)

public:
	CControllerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CControllerDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CControllerDlg();

// �Ի�������
	enum { IDD = IDD_CONTROLLERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nControllerDlgCounter;
};
