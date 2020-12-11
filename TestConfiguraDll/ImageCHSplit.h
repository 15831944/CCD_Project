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

using namespace std;

#define IMG_GRAY   1
#define IMG_RGB    2
#define IMG_HSV    3

// CImageCHSplit �Ի���

class CImageCHSplit : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageCHSplit)

public:
	CImageCHSplit(CWnd* pParent = NULL);   // ��׼���캯��
	CImageCHSplit(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageCHSplit();

// �Ի�������
	enum { IDD = IDD_IMAGECHSPLIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CImgBox m_ImageCHSplitSrcShow;//Դ�D���@ʾ��
	CImgBox m_ImageCHSplitDstShow;//Ŀ�ˈD���@ʾ��
public:
	CSmartImage m_ImageCHSplitSrc;
	CSmartImage m_ImageCHSplitDst;

public:
	CBL_Radio m_BL_ImageFormat_RGB;
	CBL_Radio m_BL_ImageFormat_HSV;
	CBL_Radio m_BL_ImageCH_0;
	CBL_Radio m_BL_ImageCH_1;
	CBL_Radio m_BL_ImageCH_2;

public:
	int m_nImageFormat;//��ɫ�D���ʽ
	CString m_strImageCHSplit_Choose;//���x���x���ͨ��
	BOOL m_bParamChange;

	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;

public:
	void ImageProcess();
	void UpdateParam();
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlImagech0(BOOL bNewStatus);
	void StatusChangedBlImagech1(BOOL bNewStatus);
	void StatusChangedBlImagech2(BOOL bNewStatus);
	virtual void OnCancel();
};
