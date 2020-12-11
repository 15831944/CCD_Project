#pragma once

#include "Resource.h"

#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"
#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#endif

#include <math.h>
#include <windows.h>

// CImageEnhancement �Ի���

class CImageEnhancement : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageEnhancement)

public:
	CImageEnhancement(CWnd* pParent = NULL);   // ��׼���캯��
	CImageEnhancement(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageEnhancement();

// �Ի�������
	enum { IDD = IDD_IMAGEENHANCEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	BOOL m_bParamChange;
public:
	CImgBox m_ImageEnhancementSrcShow;//Դ�D���@ʾ��
	CImgBox m_ImageEnhancementDstShow;//Ŀ�ˈD���@ʾ��
public:
	CSmartImage m_ImageEnhancementSrc;//�D������Դ�D��
	CSmartImage m_ImageEnhancementDst;//�D������Ŀ�ˈD��

public:
	CBL_Radio m_BL_ImageEnhancementLog;
	CBL_Radio m_BL_ImageEnhancementIndex;
	CBL_Radio m_BL_ImageEnhancementLaplace;
	CBL_Radio m_BL_ImageEnhancementExporeover;
	CBL_Radio m_BL_ImageEnhancementGamma;
	CBL_Radio m_BL_ImageEnhancementFuzzy;

	CBL_DropDown m_BL_ImageEnhancementChannel;

	CBL_Edit m_BL_ImageEnhancenmentLog_C;
	CBL_Edit m_BL_ImageEnhancenmentLog_R;
	CBL_Edit m_BL_ImageEnhancenmentIndex_C;
	CBL_Edit m_BL_ImageEnhancenmentIndex_R;
	CBL_Edit m_BL_ImageEnhancenmentGammaData;

public:
	CString m_strPartAll;
	CString m_strImageEnhancementMode;
	CString m_strImageEnhancementChannel;
	CString m_strImageEnhancementLog_C;
	CString m_strImageEnhancementLog_R;
	CString m_strImageEnhancementIndex_C;
	CString m_strImageEnhancementIndex_R;
	CString m_strImageEnhancementGammaData;
	
public:
	void UpdateParam();
	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));
public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	YX_ENHANCEMENT_PARAM m_EnhancementParam;
	CString m_strTime;//�D��̎��r�g


	virtual void OnCancel();
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlSaveimageenhacement(long nFlags);
	void StatusChangedBlImageenhancementlog(BOOL bNewStatus);
	void StatusChangedBlImageenhancementindex(BOOL bNewStatus);
	void StatusChangedBlImageenhancementgamma(BOOL bNewStatus);
	void StatusChangedBlImageenhancementexporeover(BOOL bNewStatus);
	void StatusChangedBlImageenhancementlaplace(BOOL bNewStatus);
	void SelectChangedBlImageenhancementchannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void ValueChangedBlImageenhancementlogc(LPCTSTR strNew);
	void ValueChangedBlImageenhancementlogr(LPCTSTR strNew);
	void ValueChangedBlImageenhancementindexc(LPCTSTR strNew);
	void ValueChangedBlImageenhancementindexr(LPCTSTR strNew);
	void ValueChangedBlImageenhancementgammadata(LPCTSTR strNew);
	void StatusChangedBlImageenhancementfuzzy(BOOL bNewStatus);
};
