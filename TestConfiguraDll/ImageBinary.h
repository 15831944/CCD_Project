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
#define IMAGE_BINARY_NORMAL      1//��Ҏ��ʽ
#define IMAGE_BINARY_OTSU        2//���ɷ�
#define IMAGE_BINARY_GRAYMEAN    3//�ҶȾ�ֵ��
#define IMAGE_BINARY_TROUGHMIN   4//�ȵ���Сֵ��
#define IMAGE_BINARY_BIMODALMEAN 5//�p���ֵ��
#define IMAGE_BINARY_ITER		 6//��ѵ���ֵ
#define IMAGE_BINARY_ENTROPY     7//һ�S�����
#define IMAGE_BINARY_VAGUE       8//ģ������Փ


// CImageBinary �Ի���

class CImageBinary : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageBinary)

public:
	CImageBinary(CWnd* pParent = NULL);   // ��׼���캯��
	CImageBinary(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageBinary();

// �Ի�������
	enum { IDD = IDD_IMAGEBINARY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
public:
	CImgBox m_ImageBinarySrcShow;
	CImgBox m_ImageBinaryDstShow;
	CImgBox m_ImageBinaryHistShow;

public:
	CBL_Radio m_BL_ImageBinaryNormal;//���ζ�ֵ��
	CBL_Radio m_BL_ImageBinaryOtsu;//���ɷ���ֵ��
	CBL_Radio m_BL_ImageBinaryGrayMean;//�ҶȾ�ֵ��ֵ��
	CBL_Radio m_BL_ImageBinaryTroughMin;//�ȵ���Сֵ��ֵ��
	CBL_Radio m_BL_ImageBinaryBimodalMean;//�p���ֵ��ֵ��
	CBL_Radio m_BL_ImageBinaryIter;//��ѵ���ֵ
	CBL_Radio m_BL_ImageBinaryEntropy;//һ�S�����
	CBL_Radio m_BL_ImageBinaryVague;//ģ������Փ


	CBL_DropDown m_BL_ImageBinaryChannel;//��ֵ�D��ͨ��

	CBL_CheckBox m_BL_ImageBinaryInverse;//��ֵ������

	CBL_Edit m_BL_ImageBinaryLimit;//��ֵ���ֵ


public:
	CSmartImage m_ImageBinarySrc;
	CSmartImage m_ImageBinaryDst;

public:
	BOOL m_bParamChange;

	CString m_strPartAll;
	CString m_strImageBinaryMode;
	CString m_strImageBinaryChannel;
	CString m_strImageBinaryInverse;
	CString m_strImageBinaryLimit;
public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;

	void UpdateParam();
	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));

protected:
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlImagebinarynormal(BOOL bNewStatus);
	void StatusChangedBlImagebinaryotsu(BOOL bNewStatus);
	void StatusChangedBlImagebinarygraymean(BOOL bNewStatus);
	void StatusChangedBlImagebinarytroughmin(BOOL bNewStatus);
	void StatusChangedBlImagebinarybimodalmean(BOOL bNewStatus);
	void StatusChangedBlImagebinaryiter(BOOL bNewStatus);
	void StatusChangedBlImagebinaryentropy(BOOL bNewStatus);
	void StatusChangedBlImagebinaryvague(BOOL bNewStatus);

public:
	virtual void OnCancel();
	void LBtClickedBlSaveimagebinary(long nFlags);

	void SelectChangedBlImagebinarychannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void ValueChangedBlImagebinarylimit(LPCTSTR strNew);
	void StatusChangedBlImagebinaryinverse(short nNewStatus);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL m_bLButtonDown;//���I����
	CPoint m_ptHist[3];//�޸�ֱ���D�������c
	CRect m_HistRect;//ֱ���D����
	CRect m_InvalidateRect;//��Ҫˢ�µľ���
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	void GetGrayHist(CSmartImage ImgSrc, CRect rcSrc, CSmartImage & Hist);
	void GetColorHist(CSmartImage ImgSrc, CRect rcSrc, vector<CSmartImage> & vHist);

	vector<CSmartImage>  m_vImageHist;
	CSmartImage m_ImageHist;
	
public:
	BOOL GetSingleChannelImageHist(CSmartImage ImgSrc, vector<int> & vnHist);//�@ȡ��ͨ���D��ֱ���D 
	int GetMinimumThreshold(vector<int> & vnHist);//��ȵ���Сֵ�����ֵ�M�ж�ֵ��
	int GetIntermodesThreshold(vector<int> & vnHist);//���p���ֵ�����ֵ�M�ж�ֵ��
	BOOL IsDimodal(vector<double> & vnHist);
	int GetIterativeBestThreshold(vector<int> & vnHist);//��������ֵ�M�ж�ֵ��
	int Get1DMaxEntropyThreshold(vector<int> & vnHist);//һ�S������ֵ�M�ж�ֵ��
	int GetHuangFuzzyThreshold(vector<int> & vnHist);//ģ������Փ
	
};
