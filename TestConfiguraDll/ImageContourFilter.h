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

#define CONTOUR_FILTER_QUANTITY 0//݆�������V��
#define CONTOUR_FILTER_PIX		1//������e�V��

#define CONTOUR_SORT_AREA 0//݆����e����
#define CONTOUR_SORT_PER  1//݆�����L����

#define CONTOUR_TYPE_OUT 0
#define CONTOUR_TYPE_ALL 1

// CImageContourFilter �Ի���

static inline bool ContoursSortFun_Area(vector<cv::Point> contour1,vector<cv::Point> contour2)
{
	return (cv::contourArea(contour1) > cv::contourArea(contour2));
}

static inline bool ContoursSortFun_Perimeter(vector<cv::Point> contour1,vector<cv::Point> contour2)
{
	return (contour1.size() > contour2.size());
}


class CImageContourFilter : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageContourFilter)

public:
	CImageContourFilter(CWnd* pParent = NULL);   // ��׼���캯��
	CImageContourFilter(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageContourFilter();

// �Ի�������
	enum { IDD = IDD_IMAGECONTOURFILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CImgBox m_ImageContourFilterSrcShow;//Դ�D���@ʾ��
	CImgBox m_ImageContourFilterDstShow;//Ŀ�ˈD���@ʾ��
public:
	CSmartImage m_ImageContourFilterSrc;//�{����ʹ�õ�Դ�D��

	CSmartImage m_ImageContourFilterUse;//�@ʾ��Դ�D����У��к��Ԙ�ӛ�Ĳ�ɫ�D����ʾ��ԭͼ���ǳ���ɾ���Ĳ��֣�
	CSmartImage m_ImageContourFilterDst;

public:
	CBL_Radio m_BL_raImageFilterMode_Counter;//݆�������V��ģʽ
	CBL_Radio m_BL_raImageFilterMode_Pix;//������e�V��ģʽ

	CBL_Radio m_BL_raImageContourSort_Area;//����e����
	CBL_Radio m_BL_raImageContourSort_Per;//�����L����

	CBL_Edit m_BL_edImageGetContourQuantity;//ݔ�뱣��݆������
	CBL_Edit m_BL_edImagePixUpper;//��������
	CBL_Edit m_BL_edImagePixLower;//��������

	CBL_Radio m_BL_raImageContourType_Out;
	CBL_Radio m_BL_raImageContourType_All;

public:
	CString m_strPartAll;
	CString m_strImageImageFilterMode;//݆���V������
	CString m_strImageContourSortMode;//݆�����򷽷�

	CString m_strImageGetContourQuantity;//݆����������
	CString m_strImagePixUpper;//���؞V������
	CString m_strImagePixLower;//���؞V������

	CString m_strImageContourType;//݆�����

public:
	BOOL m_bParamChange;

	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;

public:
	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));
	void UpdateParam();

public:
	void _ContoursSort(cvContours & vContours, int nSortMode = CONTOUR_SORT_AREA);//݆�����򣨏Ĵ�С��
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlImagefiltermodeCounter(BOOL bNewStatus);
	void StatusChangedBlImagefiltermodePix(BOOL bNewStatus);
	void StatusChangedBlImagecontoursortArea(BOOL bNewStatus);
	void StatusChangedBlImagecontoursortPer(BOOL bNewStatus);
	void ValueChangedBlImagegetcontourquantity(LPCTSTR strNew);
	void ValueChangedBlImagepixupper(LPCTSTR strNew);
	void ValueChangedBlImagepixlower(LPCTSTR strNew);
	virtual void OnCancel();
	void StatusChangedBlImagecontourtypeOut(BOOL bNewStatus);
	void StatusChangedBlImagecontourtypeAll(BOOL bNewStatus);
};
