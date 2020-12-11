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
// CImageMorphology �Ի���

#define IMAGE_MORPHOLOGY_ERODE     0  //���g
#define IMAGE_MORPHOLOGY_DILATE    1  //��Û
#define IMAGE_MORPHOLOGY_OPEN      2  //�_�\��
#define IMAGE_MORPHOLOGY_CLOSE     3  //�]�\��
#define IMAGE_MORPHOLOGY_GRADIENT  4  //�ΑB�W�ݶ�
#define IMAGE_MORPHOLOGY_TOP       5  //�ñ�\��
#define IMAGE_MORPHOLOGY_BLACK     6  //��ñ�\��
#define IMAGE_MORPHOLOGY_EDGE      7  //��݋��ȡ



class CImageMorphology : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CImageMorphology)

public:
	CImageMorphology(CWnd* pParent = NULL);   // ��׼���캯��
	CImageMorphology(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CImageMorphology();

// �Ի�������
	enum { IDD = IDD_IMAGEMORPHOLOGY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CImgBox m_ImageMorphologySrcShow;
	CImgBox m_ImageMorphologyDstShow;

public:
	CBL_Radio m_BL_ImageMorphologyDilate;//��Û����
	CBL_Radio m_BL_ImageMorphologyErode;//���g����
	CBL_Radio m_BL_ImageMorphologyOpen;//�_�\�����
	CBL_Radio m_BL_ImageMorphologyClose;//�]�\�����
	CBL_Radio m_BL_ImageMorphologyGradient;//�ΑB�W�ݶ�
	CBL_Radio m_BL_ImageMorphologyTop;//�ñ�\��
	CBL_Radio m_BL_ImageMorphologyBlack;//��ñ�\��
	CBL_Radio m_BL_ImageMorphologyEdge;//߅����ȡ

	CBL_DropDown m_BL_ImageMorphologyChannel;//�ΑB�W�����D��ͨ��
	CBL_DropDown m_BL_ImageMorphologyShape;//�ΑB�W�����Ⱥ��Π�

	CBL_Edit m_BL_ImageMorphologyIterCounter;//�ΑB�W�����Δ�

	CBL_Edit m_BL_ImageMorphologyConvolX;//�Ⱥ˳ߴ�
	CBL_Edit m_BL_ImageMorphologyConvolY;//�Ⱥ˳ߴ�
	
public:
	CSmartImage m_ImageMorphologySrc;
	CSmartImage m_ImageMorphologyDst;
public:
	BOOL m_bParamChange;

	CString m_strPartAll;
	CString m_strImageMorphologyMode;//�ΑB�W����
	CString m_strImageMorphologyChannel;//�ΑB�Wͨ��
	CString m_strImageMorphologyShape;//
	CString m_strImageMorphologyIterCounter;
	CString m_strImageMorphologyConvolX;
	CString m_strImageMorphologyConvolY;

protected:
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlImagemorphologydilate(BOOL bNewStatus);
	void StatusChangedBlImagemorphologyerode(BOOL bNewStatus);
	void StatusChangedBlImagemorphologyopen(BOOL bNewStatus);
	void StatusChangedBlImagemorphologyclose(BOOL bNewStatus);
	void StatusChangedBlImagemorphologygradient(BOOL bNewStatus);
	void StatusChangedBlImagemorphologytop(BOOL bNewStatus);
	void StatusChangedBlImagemorphologyblack(BOOL bNewStatus);
public:
	virtual void OnCancel();
	void UpdateParam();
	void ImageProcess(BOOL bMode = FALSE, vector<CString> vstrImgMode = vector<CString>(3, _T("")));
public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;
	void StatusChangedBlImagemorphologyedge(BOOL bNewStatus);
	void SelectChangedBlImagemorphologychannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void ValueChangedBlImagemorphologyitercounter(LPCTSTR strNew);
	void LBtClickedBlSaveimagemorphology(long nFlags);
};
