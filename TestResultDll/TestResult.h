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

#include "TestResultChart.h"

#include <math.h>

#define TEST_RES_TYPE_SUM  6//�yԇ������͔���

static UINT gMsgTestResultUpdate		= RegisterWindowMessage(_T("gMsgTestResultUpdate"));//������ɣ���������
static UINT gMsgTestResultType   		= RegisterWindowMessage(_T("gMsgTestResultType"));//������ɣ��yԇ�Y������ͣ�������NGƷ����ͣ���춅^�ֺηN����

// CTestResult �Ի���

class AFX_EXT_CLASS CTestResult : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CTestResult)

public:
	CTestResult(CWnd* pParent = NULL);   // ��׼���캯��
	CTestResult(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CTestResult();

// �Ի�������
	enum { IDD = IDD_TESTRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pTestRes;
public:
	CBlender<CTestResultChart> m_TestResultChart;

public:
	CValueCalculate m_ValueCalculate;
	CString m_strSoftwareVersion;

public:
	int m_nFinishCounter;//�������
	int m_nNGCountetr;//NG����
	int m_nPASSCounter;//Pass����

	int m_nTestErrType[TEST_RES_TYPE_SUM];

public:
	BOOL m_bSaveOKImage;//�Ƿ񱣴�OKͼ��
	BOOL m_bSaveNGImage;//�Ƿ񱣴�NGͼ��

	CString m_strOKImagePath;//Passͼ�񱣴��ļ���
	CString m_strNGImagePath;//NGͼ�񱣴��ļ���
public:
	CBL_CheckBox m_BL_ckSaveOKImage;
	CBL_CheckBox m_BL_ckSaveNGImage;

	CBL_Edit m_BL_edOKImagePath;
	CBL_Edit m_BL_edNGImagePath;

public:
	CFindCtrlFile m_FindFile;
protected:
	afx_msg LRESULT OnGmsgTestResultUpdate(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
public:

	void LBtClickedBlCleanres(long nFlags);
	void TestResultUpdate();//���²��Խ��
	virtual void Serialize(CArchive& ar);
	afx_msg void OnClose();
	void StatusChangedBlcksavengimage(short nNewStatus);
	void StatusChangedBlcksaveokimage(short nNewStatus);
	void LBtClickedBlbtopenokimage(long nFlags);
	void LBtClickedBlbtopenngimage(long nFlags);
public:
	void _DeleteDirectory(CString strPath);
protected:
	afx_msg LRESULT OnGmsgTestResultType(WPARAM wParam, LPARAM lParam);
public:
	void LBtClickedBlTestresultchartshow(long nFlags);
};
