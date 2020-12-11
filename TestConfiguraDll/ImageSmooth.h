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
// CImageSmooth �Ի���

#define IMAGE_SMOOTH_BLUR    1
#define IMAGE_SMOOTH_GUESS   2
#define IMAGE_SMOOTH_MEDIAN  3
#define IMAGE_SMOOTH_BILA    4

class CImageSmooth : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageSmooth)

public:
	CImageSmooth(CWnd* pParent = NULL);   // ��׼���캯��
	CImageSmooth(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageSmooth();

// �Ի�������
	enum { IDD = IDD_IMAGESMOOTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CBL_Radio m_BL_ImageSmoothBlur;//��ֵ�V��
	CBL_Radio m_BL_ImageSmoothGauss;//��˹�V��
	CBL_Radio m_BL_ImageSmoothMedian;//��ֵ�V��
	CBL_Radio m_BL_ImageSmoothBila;//�p߅�V��

	CBL_DropDown m_BL_ImageSmoothChannel;//�V���D��ͨ��
	CBL_Edit m_BL_ImageSmoothSigmaX;
	CBL_Edit m_BL_ImageSmoothSigmaY;
	CBL_Edit m_BL_ImageSmoothVar;
	CBL_Edit m_BL_ImageSmoothSharpenParam;
	CBL_Edit m_BL_ImageSmoothConcolX;
	CBL_Edit m_BL_ImageSmoothConcolY;

public:
	CImgBox m_ImageSmoothSrcShow;//Դ�D���@ʾ��
	CImgBox m_ImageSmoothDstShow;//Ŀ�ˈD���@ʾ��
public:
	CSmartImage m_ImageSmoothSrc;//�V��Դ�D��
	CSmartImage m_ImageSmoothDst;//�V��Ŀ�ˈD��
public:
	BOOL m_bParamChange;

	CString m_strPartAll;//���Ѕ�����ɺ󣬺ϳ��ַ���
	CString m_strImageSmoothMode;//�V����ʽ
	CString m_strImageSmoothChannel;//ͨ���x�
	CString m_strImageSmoothSigmaX;
	CString m_strImageSmoothSigmaY;
	CString m_strImageSmoothVar;
	CString m_strImageSmoothSharpenParam;
	CString m_strImageSmoothConcolX;
	CString m_strImageSmoothConcolY;
public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	YX_SMOOTH_PARAM m_SmoothParam;//�V�������Y���w
	CString m_strTime;//�D��̎��r�g

public:

	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlSaveimagesmooth(long nFlags);
	void StatusChangedBlImagesmoothblur(BOOL bNewStatus);
	void StatusChangedBlImagesmoothgauss(BOOL bNewStatus);
	void StatusChangedBlImagesmoothmedian(BOOL bNewStatus);
	void StatusChangedBlImagesmoothbila(BOOL bNewStatus);
public:
	virtual void OnCancel();
	void UpdateParam();//������

	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));//bMode = TRUE�ⲿ���f�D��̎��
	void ValueChangedBlImagesmoothsigmax(LPCTSTR strNew);
	void ValueChangedBlImagesmoothsigmay(LPCTSTR strNew);
	void ValueChangedBlImagesmoothconvolx(LPCTSTR strNew);
	void ValueChangedBlImagesmoothconvoly(LPCTSTR strNew);
	void SelectChangedBlImagesmoothchannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
};
