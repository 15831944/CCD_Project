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
// CImageGray �Ի���

#define IMAGE_GRAY_LOG       1
#define IMAGE_GRAY_INDEX     2
#define IMAGE_GRAY_CHANGE    3
#define IMAGE_GRAY_EQUAHIST  4 

class CImageGray : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageGray)

public:
	CImageGray(CWnd* pParent = NULL);   // ��׼���캯��
	CImageGray(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageGray();

// �Ի�������
	enum { IDD = IDD_IMAGEGRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	virtual BOOL OnInitDialog();
public:
	CImgBox m_ImageGraySrcShow;
	CImgBox m_ImageGrayDstShow;

public:
	CBL_Radio m_BL_ImageGrayIndex;//ָ��׃�Q
	CBL_Radio m_BL_ImageGrayLog;//����׃�Q
	CBL_Radio m_BL_ImageGrayChange;//�Ҷ�����
	CBL_Radio m_BL_ImageGrayEquaHist;//ֱ���D���⻯

	CBL_DropDown m_BL_ImageGrayChannel;//�Ҷ�����D��ͨ��

	CBL_CheckBox m_BL_ImageGrayInverse;//�Ҷ����췴��

	CBL_Edit m_BL_ImageGrayLimitLow;//�Ҷ���������
	CBL_Edit m_BL_ImageGrayLimitLowValue;//�Ҷ��������ޘO��ֵ
	CBL_Edit m_BL_ImageGrayLimitHigh;//�Ҷ���������
	CBL_Edit m_BL_ImageGrayLimitHighValue;//�Ҷ��������ޘO��ֵ

	CBL_Edit m_BL_ImageGrayConvolX;//�R��ߴ�
	CBL_Edit m_BL_ImageGrayConvolY;//�R��ߴ�

public:
	CSmartImage m_ImageGraySrc;
	CSmartImage m_ImageGrayDst;
public:
	BOOL m_bParamChange;

	CString m_strPartAll;
	CString m_strImageGrayMode;
	CString m_strImageGrayChannel;//

	CString m_strImageGrayInverse;//

	CString m_strImageGrayLimitLow;//
	CString m_strImageGrayLimitLowValue;//
	CString m_strImageGrayLimitHigh;//
	CString m_strImageGrayLimitHighValue;//

	CString m_strImageGrayConvolX;//
	CString m_strImageGrayConvolY;//
protected:
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlImagegraylog(BOOL bNewStatus);
	void StatusChangedBlImagegrayindex(BOOL bNewStatus);
	void StatusChangedBlImagegraychange(BOOL bNewStatus);
	void StatusChangedBlImagegrayequahist(BOOL bNewStatus);
public:
	virtual void OnCancel();
	void UpdateParam();//������
	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));
public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;
	void SelectChangedBlImagegraychannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void StatusChangedBlImagegrayinverse(short nNewStatus);
	void ValueChangedBlImagegraylimitlow(LPCTSTR strNew);
	void ValueChangedBlImagegraylimitlowvalue(LPCTSTR strNew);
	void ValueChangedBlImagegraylimithigh(LPCTSTR strNew);
	void ValueChangedBlImagegraylimithighvalue(LPCTSTR strNew);
	void LBtClickedBlSaveimagegray(long nFlags);
	void ValueChangedBlImagegrayconvolx(LPCTSTR strNew);
	void ValueChangedBlImagegrayconvoly(LPCTSTR strNew);
};
