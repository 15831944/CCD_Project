#pragma once
#include "resource.h"


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

// CLocatorPT �Ի���


typedef struct _tagCircleTarget
{
	double x;
	double y;
	double r;
}CIRCLE_TAR_INFO;

typedef struct _tagCircleParamNew
{
	double x;
	double y;
	double r;
	vector<Point2d> vpt;
}FIT_CIRCLE_PARAM_NEW;


typedef struct _tagLocParam
{
	double d2LocRad;//����
	double d2LocAngle;//�Ƕ�
	double d2LocDist;//���x
	Point2d pt2LocCenter;//�ɂ���λ�c�B�������c����
}TWO_LOC_INFO;

enum
{
	SORT_LOC_MAIN = 0,
	SORT_LOC_AUX,
	SORT_LOC_OTHER
};

class AFX_EXT_CLASS CLocatorPT : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CLocatorPT)

public:
	CLocatorPT(CWnd* pParent = NULL);   // ��׼���캯��
	CLocatorPT(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CLocatorPT();

// �Ի�������
	enum { IDD = IDD_LOCATORPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CString m_strTitle;

public:
	int m_nStretchLow;//�Ҷ�ֵ����
	int m_nStretchHigh;//�Ҷ�ֵ����
	int m_nBinaryThre;//��ֵ���ֵ
	int m_nMorphInter;//�ΑB�W�����Δ�


	BOOL m_bParamChange;//�����Ƿ�l����׃

	BOOL m_bAutoThres;//�ԄӶ�ֵ���ֵ
	BOOL m_bInverse;//�D����,�ڶ�ֵ���D���У���ɫ������ڣ���ɫ�������ڣ�����λ�c���ɫ�ĕr�򣬄t��Ҫ����
	BOOL m_bFitCircle;//�ԄӔM�ψA��
	BOOL m_bClearOutline;//�Ƿ�ȥ��߅��
	BOOL m_bInside;//�Ƿ�ȥ��݆��

	CSmartImage m_ImgShow;
	CImgBox m_BoxShow;

	virtual void OnCancel();
	void SetImage(CSmartImage * pSrc);//���D���뺯��
	void LocImgProc(CSmartImage * pSrc, CSmartImage * pDst);//�D�Q�D�񺯔����D���D����Ҷȼ���ֵ�D��
	Point3d GetLocation(CSmartImage * pSrc, cvContours * pvTarget);//�M�ψA����
	//void _GetCircle(Point3d ptLoc, CSmartImage ImgSrc);
	Point3d GetContoursCenter(CSmartImage * pSrc, cvContours & vOutline, int & nMax);
public:
	//��헔������
	CSmartImage m_ImgBkup;

	int m_nStretchLowBkup;
	int m_nStretchHighBkup;
	int m_nBinaryThreBkup;
	int m_nMorphInterBkup;

	BOOL m_bAutoThresBkup;
	BOOL m_bInverseBkup;
	BOOL m_bFitCircleBkup;
	BOOL m_bClearOutlineBkup;
	BOOL m_bInsideBkup;//�Ƿ�ȥ��݆��
	//virtual void _PreShowWnd(void);
	Point3d m_CenterPoint;//�׺������c

	vector<Point3d> _GetFitCircle(CSmartImage * pSrc,
		double dRadius, double dScaleMin, double dScaleMax,
		double dScore, int nWant);

	Point3d _Fitcircle(vector<Point2d> * pvPos);

	void _UpdateUi(void);//ʹ��׃�����¿ؼ�

	DECLARE_EVENTSINK_MAP()
	void PosChangedBlLocStretchLow(long nNewPos);
	void PosChangedBlLocStretchHigh(long nNewPos);
	void PosChangedBlLocBinaryThres(long nNewPos);
	void PosChangedBlLocMorphOp(long nNewPos);
	void StatusChangedBlLocatorAutoThres(short nNewStatus);
	void StatusChangedBlLocatorInverse(short nNewStatus);
	void StatusChangedBlLocatorCircle(short nNewStatus);
	void LBtClickedBlLocatorOk(long nFlags);
	void LBtClickedBlLocatorCancel(long nFlags);
public:
	virtual void Serialize(CArchive& ar);
	void StatusChangedBlLocatorClearoutline(short nNewStatus);
	void StatusChangedBlLocatorInside(short nNewStatus);
};

TWO_LOC_INFO _declspec(dllexport) Get2LocatorParam(Point2d ptMain, Point2d ptAux);//�@ȡ�M�ψA��