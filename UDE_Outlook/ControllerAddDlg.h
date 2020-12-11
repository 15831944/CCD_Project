#pragma once

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


#define  WINDOWTITLE   _T("�豸���")

// CControllerAddDlg �Ի���

class CControllerAddDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CControllerAddDlg)

public:
	CControllerAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CControllerAddDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CControllerAddDlg();

// �Ի�������
	enum { IDD = IDD_CONTROLLERADDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBL_DropDown  m_BL_ControllerName;
	CBL_DropDown m_BL_ControllerCheckModeName;

	CBL_Edit m_BL_CtrlCoilStart;
	CBL_Edit m_BL_CtrlCoilEnd;
	CBL_Edit m_BL_CtrlRegistersStart;
	CBL_Edit m_BL_CtrlRegistersEnd;

public:
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlAddok(long nFlags);
	void LBtClickedBlAddcancel(long nFlags);

};
