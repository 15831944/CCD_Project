#pragma once

#include "..\BlendWndDll\MsgBox.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")

#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CSampleCollectionDlg �Ի���

class CSampleCollectionDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSampleCollectionDlg)

public:
	CSampleCollectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSampleCollectionDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSampleCollectionDlg();

// �Ի�������
	enum { IDD = IDD_SAMPLECOLLECTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
