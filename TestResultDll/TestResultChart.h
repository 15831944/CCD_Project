#pragma once

#include "Resource.h"

#include "..\BlendWndDll\MsgBox.h"
#include "..\\CRCDll\\ValueCalculate.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

#include <math.h>

static UINT gMsgTestDataUpdate		= RegisterWindowMessage(_T("gMsgTestDataUpdate"));//�yԇ��������


// CTestResultChart �Ի���

#define  DATA_SUM  100

#define  DATA_CYCLE  5000

class AFX_EXT_CLASS CTestResultChart : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CTestResultChart)

public:
	CTestResultChart(CWnd* pParent = NULL);   // ��׼���캯��
	CTestResultChart(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CTestResultChart();

// �Ի�������
	enum { IDD = IDD_TESTRESULTCHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
	virtual BOOL OnInitDialog();

public:
	int m_nTestGroup;//�yԇ�M
	int m_nTestProject;//�yԇ�Ŀ��̖
	CString m_strExePath;
	static BOOL m_bSaveData;//���攵��
public:
	CBL_List m_BL_ltTestResult_AM;//�yԇ�Y����� ����
	CBL_List m_BL_ltTestResult_PM;//�yԇ�Y����� ����

	float m_fValueMax;//�������ֵ
public:
	void _GetDisplayScreenInfo();
	long m_nScreenPhysicsWidth;
	long m_nScreenPhysicsHeight;

	long m_nScreenPixelWidth;
	long m_nScreenPixelHeight;
	long m_nDisplayFrequency;

	int m_nScreenPixelWidthNoTask;
	int m_nScreenPixelHeightNoTask;

public:
	void _UpdateUI();
	void _GetSystemTime(CString & strYear, CString & strMouth, CString & strDay, CString & strHour, CString & strMinute, CString & strSeconds);
	void _LoadData();//���d����Ĕ���

	DECLARE_EVENTSINK_MAP()
	void ItemChangedBllttestresultAm(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBllttestresultAm(long nRow, long nCol, short* pnParam, short nFlags);

public:
	CRect m_rcDraw;//���D�^�����

	vector<vector<float>> m_vvfShowData;//��񔵓�����
	int m_nCurRow;
	void RowsChangedBllttestresultAm(long nOldRows, long nNewRows, BOOL bAppend);
	void SelectChangedBllttestresultAm(long nOldSels, long nNewSels);

public://������ָʾ�r�@ʾ����
	vector<CRect> m_vrcData;//��������
	vector<float> m_vfData;
	CPoint m_ptMouse;//�������

protected:
	afx_msg LRESULT OnGmsgTestDataUpdate(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void Serialize(CArchive& ar);
};
