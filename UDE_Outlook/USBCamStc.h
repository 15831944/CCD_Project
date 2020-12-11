#pragma once
#include "CreateProject.h"
#include "ViewTop.h"
#include "TestGroup.h"

#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#endif

// CUSBCamStc
#define  WM_DRAWIMAGE_USB  WM_USER + 60

class CUSBCamStc : public CUSBCamShow
{
	DECLARE_DYNAMIC(CUSBCamStc)

public:
	CUSBCamStc();
	virtual ~CUSBCamStc();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nUSBCamNO;
	BOOL m_bIfDraw;

	CSmartImage m_ImgShow;

	virtual void DrawOthers(CDC * pDC, CRect rcDraw);

public:
	CWnd *m_pUSBCamStc;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

public:
	BOOL GetUSBCamImage();//��USB���C�Ы@ȡһ���D��
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
public:

	HIDD_VIDPID m_CurVIDPID;

protected:
	afx_msg LRESULT OnGmsgusbcaminfochange(WPARAM wParam, LPARAM lParam);//���C�����и�׃
public:
	BOOL m_bUSBCamBalanceBkup;
	double m_dUSBCamExposureValueBkup;

	CValueCalculate m_ValueCalculate;
	CString m_strSoftwareVersion;

	virtual void Serialize(CArchive& ar);
};


