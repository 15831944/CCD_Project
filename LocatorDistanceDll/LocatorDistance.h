#pragma once
#include "resource.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


// CLocatorDistance �Ի���

class AFX_EXT_CLASS CLocatorDistance : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CLocatorDistance)

public:
	CLocatorDistance(CWnd* pParent = NULL);   // ��׼���캯��
	CLocatorDistance(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CLocatorDistance();

// �Ի�������
	enum { IDD = IDD_LOCATORDISTANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
public:
	BOOL m_bSystemRunStatus;
	BOOL m_bParamChange;//�Ƿ��޸��˅���
	CString m_strDistance;
	CBL_Edit m_BL_LocatorDistance;
	BOOL m_bLongSide;
	BOOL m_bShortSide;
	CString m_strLocOffsetX;
	CString m_strLocOffsetY;
	CString m_strLocOffsetAngle;
	CString m_strLocOffsetArea;
	CString m_strLocPtStrat;
	CString m_strLocPtEnd;
	virtual void OnOK();
	virtual void OnCancel();
	void UpdateBL();//���¿ؼ���B
	BOOL CheckInput(CString strInput);//�z�yݔ�딵���Ƿ��e�`
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlLongside(BOOL bNewStatus);
	void StatusChangedBlShortside(BOOL bNewStatus);
	void ValueChangedBlLocatordistance(LPCTSTR strNew);
	void ValueChangedBlLocoffsetarea(LPCTSTR strNew);
	void ValueChangedBlLocoffsetx(LPCTSTR strNew);
	void ValueChangedBlLocoffsety(LPCTSTR strNew);
	void ValueChangedBlLocoffsetangle(LPCTSTR strNew);
	void ValueChangedBlLocptstart(LPCTSTR strNew);
	void ValueChangedBlLocptend(LPCTSTR strNew);
};
