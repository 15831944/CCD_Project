#pragma once

#include <gdiplus.h>
#include "..\BlendFigureDll\FigureBase.h"
#include "..\BlendWndDll\\AppBase.h"

#include "..\\LocatorPtDll\\LocatorPt.h"
#include "..\\LocatorDistanceDll\\LocatorDistance.h"
#include "..\\TestConfiguraDll\\TestConfigura.h"
#include "..\\TestResultDll\\TestResult.h"

#include "TestLightInfo.h"
#include "TestNameInfo.h"

#include "CamStc.h"
//#include "USBCamStc.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendFigureDll.lib")
#pragma comment(lib, "..\\Debug\\LocatorPtDll.lib")
#pragma comment(lib, "..\\Debug\\LocatorDistanceDll.lib")
#pragma comment(lib, "..\\Debug\\TestConfiguraDll.lib")
#pragma comment(lib, "..\\Debug\\TestResultDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendFigureDll.lib")
#pragma comment(lib, "..\\Release\\LocatorPtDll.lib")
#pragma comment(lib, "..\\Release\\LocatorDistanceDll.lib")
#pragma comment(lib, "..\\Release\\TestConfiguraDll.lib")
#pragma comment(lib, "..\\Release\\TestResultDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#endif

#include<vector>
#include <math.h>
#include <string>
#include <cstring>
// CViewTop �Ի���
using namespace std;


#define NO_CIRCLR_ERROR 32000
#define MIAN_POS_EMPTY_ERROR 32001//����λ�c������
#define SLAVE_POS_EMPTY_ERROR 32002//�Ķ�λ�c������
#define MAIN_GET_CIRCLE_ERROR 32003//���cλ�c�M�ψ@ʧ��
#define SLAVE_GET_CIRCLE_ERROR 32004//�Ķ�λ�c�M�ψ@ʧ��
#define MAIN_GET_CENTER_ERROR 32005//����λ�c���Ҏ׺�����ʧ��
#define SLAVE_GET_CENTER_ERROR 32006//�Ķ�λ�c���Ҏ׺�����ʧ��
#define MAIN_ANGEL_ERROR   32007// ����λ�c�Ƕ��e�`
#define MAIN_CHOOSE_ERROR  32008//����У��߅�x���e�`
#define TEST_POS_EMPTY_ERROR 32009//�yԇ����������
#define TEST_GET_ERROR 32010//�yԇ�����M�ψ@ʧ��
#define TEST_FLATNESS_SPECIAL_ERROR 32011//�yԇ���ʾ�ƽ���ȕr��δ�ҵ����ʾ�
#define SPECIAL_POS_EMPTY_ERROR 32012//���ⶨλ�����ڲ�����
#define TEST_GET_CONTOUR_ERROR 32013//�yԇ�����@ȡ݆��ʧ��

#define GET_LED_IMG 32200//LED��Ļ�yԇ��δ�z�y���D��׃����������


#define NO_CMP_ERROR 32100//�������_
#define CMP_ERROR 32101//�����e�`

#define WM_TESTINFO			WM_USER + 40//�yԇ��Ϣ
#define WM_TESTSTART		WM_USER + 41//�_ʼ�yԇ
#define WM_SHOWTESTRESLUT   WM_USER + 42//�@ʾ�yԇ�Y��
#define WM_TESTFINISH       WM_USER + 43//�yԇ���

#define WM_IMAGE_TEMPLATE   WM_USER + 46//�u��ģ��D��

#define TEST_RESULT_LENGTH 32767
#define TEST_RESULT_PASSNG 32766
#define TEST_FINISH        32765
#define CAM_GET_IMAGE      32764

#define TEST_INFO_ARRAY_LEN  128

#define CAM_MAX   12//���C�������

#define MARK_WITH_POINT       1//��mark�c��λ
#define MARK_WITH_MATERIAL    2//�ò��϶�λ
#define MARK_EMPTY            3//����λ���m��춹̶��yԇ������Cе��λ���ȸ�
#define MARK_MOVE_CAMERA      4//�Ƅ����C���y�����x�r����ƽ�ƻ����D�D��ֻ��Ӌ��X��Y�����ϵ�ƫ����

#define MARK_PT_A        1//��ӛA�c
#define MARK_PT_B        2//��ӛB�c


#define LINE_POS_UP      1//��׼������Ļ�Ϸ�
#define LINE_POS_DOWN    2//��׼������Ļ�·�
#define LINE_POS_LEFT    3//��׼������Ļ��
#define LINE_POS_RIGHT   4//��׼������Ļ�ҷ�

#define LINE_STYLE_X     1//X������
#define LINE_STYLE_Y     2//Y������


#define TEST_SIDE_POSITION_RES_LENGTH_OK  0//��Ե��λ�Ȳ��ԣ���������
#define TEST_SIDE_POSITION_RES_LENGTH_NG  1//��Ե��λ�Ȳ��ԣ����߳�����
#define TEST_SIDE_POSITION_RES_LENGTH_NG_GRAY_OK  2//��Ե��λ�Ȳ��ԣ����ߴ��󣬻Ҷ�����
#define TEST_SIDE_POSITION_RES_LENGTH_NG_GRAY_NG  3//��Ե��λ�Ȳ��ԣ����ߴ��󣬻Ҷȴ���


#define CHECK_FINISH      1
#define CMP_FINISH        2

#define USED_THREAD_COUNTER  8


class CViewTop : public CFigureBase// , public CAppBase
{
	
	DECLARE_DYNAMIC(CViewTop)

public:
	CViewTop(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewTop();

// �Ի�������
	enum { IDD = IDD_VIEWTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawFigure(CDC * pDC, CRect rcDraw);
	
public:

	int m_nImageChannel;

	int m_nGetImageCounter;

	CSmartImage *m_pCamImage;//��ǰͼ��ָ��

	float m_fLine_K;
	float m_fLine_B;

	float m_fLine_K_Stander;//��׼б��
	float m_fLine_B_Stander;
	float m_fLine_B_Current;//��ǰֱ�ߵ�B

	Point2f m_ptStart;//��ʼ��
	Point2f m_ptEnd;//��ֹ��

	Point2f m_fLine_Stander_Start;
	Point2f m_fLine_Stander_End;

	CSmartDC * m_pdcViewTop;

	void _DrawWithoutWndShow();//�ڴ����@ʾ�ĕr���L�u����
	BOOL m_bDrawFinish;//�o�����@ʾ�r�L�u���
	CString m_strSavePath;

	BOOL m_bSystemRunStatus;//ϵ�y�\�Р�B�������Ԅӻ����ք�ģʽ

	int m_nTestFinishSet;    //�yԇ�O�Ô���
	int m_nTestFinishCounter;//�yԇ��ɔ���

	typedef struct _RECT_FOCUS_INFO
	{
		BOOL bMainFocus;
		BOOL bSlaveFocus;
		BOOL bSpecialFocus;
		BOOL bTestFocus;
		set<int> snTestFocusNb;

		void _Clear()
		{
			bMainFocus = FALSE;
			bSlaveFocus = FALSE;
			bSpecialFocus = FALSE;
			bTestFocus = FALSE;
			snTestFocusNb.clear();
		}

		BOOL _IsTestScopeInFocus(int nTestScopeNb)
		{
			BOOL bFocus = FALSE;

			for (set<int>::iterator it = snTestFocusNb.begin(); it != snTestFocusNb.end(); it++)
			{
				if (nTestScopeNb == *it)
				{
					bFocus = TRUE;
					break;
				}
			}
			return bFocus;
		}
	}RECT_FOCUS_INFO;//���ν��c�Y���w

	RECT_FOCUS_INFO m_RectFocusInfo;

public:

	CRect m_rcSearchScope;
	vector<CRect> m_rcSearchScopeChange;

	CRect m_rcMainPos;
	vector<CRect> m_rcMainPosChange;

	CRect m_rcSlavePos;
	vector<CRect> m_rcSlavePosChange;

	vector <CRect> m_rcTestScope;
	vector<vector <CRect>> m_rcTestScopeChange;

	vector <CRect> m_rcTestScope_TestRes;//�yԇ�Y�����NG���yԇ���ӛ�ɼtɫ

	vector<CRect> m_vrcTestScopeTem;//���ź�Ĳ��Ծ��η�Χ

	CRect m_rcTest;

	CRect m_rcSpecialScope;//�����Ǿ���
	vector<CRect> m_vrcSpecialScopeChange;

	BOOL m_bDrawing;//�����L�u����

	BOOL m_bShowChangePos;//�@ʾ�����޸Ĺ���

	CString m_strSoftwareVersion;//ܛ���汾̖

	double m_dRecResize_Width;//ͼ��������ű���   �� / ��

	double m_dRecResize_Height;//ͼ���������ű���  �� / ��

public:
	CBlender<CLocatorPT> m_MainPosLoc;
	CBlender<CLocatorPT> m_SlavePosLoc;

	CBlender<CTestConfigura> m_MainPos;//����λ��
	CBlender<CTestConfigura> m_SlavePos;//�Ӷ�λ��
	CBlender<CTestConfigura> m_SpecialPos;//����˶�

	CBlender<CTestLightInfo> m_TestLightInfo;

	CBlender<CLocatorDistance> m_LocatorDistance;

	vector<CBlender<CTestConfigura> *> m_TestConfig;//�yԇ����

	CBlender<CTestResult> m_TestResult;

	CValueCalculate m_ValueCalculate;

	CFindCtrlFile m_FindFile;

	CBlender<CTestNameInfo> m_TestNameInfo;
public:
	void ChangeRect(CRect rcInfo, vector<CRect> & rcTarget);
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);

	BOOL m_bIsWindowShow;//�ô����Ƿ���ʾ

	BOOL _bUpdateUI;
public:
	void ShowLocDistance();//�@ʾ��λ�c���x��Ԓ��

	void ShowTestLoc(int LocMode);//��ʾ��λ��ͼ������(����ע��λ�㻹�Ǵӵ�λ��)
	void CreateTestConfig();//�����yԇ�Ŀ���Ì�Ԓ��
	void ShowTestConfig(int nConfig);//�@ʾ�yԇ���ô���
	BOOL SearchLocatorPt(CSmartImage * ImgSrc);//�ڈD���ϲ��Ҷ�λ�c
	void SearchMinAreaRectPt(vector<Point2f> & vptMinAreaRec_Src);//������С��Ӿ��εĶ��㣬��������������ϣ����£����ϣ�����

	vector<Point2f> SearchContoursLimitPt(vector<Point2i> vptContours, CRect rcContours);//���������ļ��޵�λ����

	Point2f SearchContoursLimitPt(vector<Point2i> vptContours, CRect rcContours, int nDir);//���������ļ��޵�λλ�ã�ֻ����ĳһ����

	vector<Point2i> SearchContoursEdgePt(vector<Point2i> vptContours, CRect rcContours, const CSmartImage * pImgSrc, int nLinePos);//����������Ե��λ����

	vector<Point2i> SearchContoursEdgePt(vector<Point2i> vptContours, int nLinePos);

	double GetRotateAngle(Point2f pt_Start,Point2f pt_End) const;//�����ת�Ƕ�

	vector<Point2f> FitLineByPoint(vector<Point2i> vptSrc, int nLineStyle, BOOL bLineDirect, BOOL bGetPt = TRUE);//���ݵ��������ֱ�ߣ�����ֱ��ģʽ(X��Y)������������TRUE ����FALSE����bGetPt �Ƿ񷵻؃ɶ��c

	void ImageResize(CSmartImage *pSrcImg, CSmartImage *pDstImg, double dScale, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR );//ͼ������

public:
	BOOL m_bCheckFinish;//����У�����
	BOOL m_bCmpFinish;//�������

	int GetProportion(CRect rcTop, CRect rcAOI, CSmartImage ImgSrc);//ͨ�^�ɶ�λ�c֮�g�ľ��x��Ӌ������H���x�͈D����x�ı���

	int GetSizeByAOI(CRect rcTop, CRect rcAOI, CSmartImage * ImgSrc, int nRCPosMode, int nRCCounter, CBlender<CTestConfigura> * pTestConfig, BOOL bCheck = FALSE/*�Ƿ�У����*/);

	BOOL _MoveCamMark(int nMarkPtMode);//�Ƅ����C��ӛ nMarkPtMode--��ӛ�c��ͣ�A�c��B�c

	CRect m_rcMainPos_Check;//�L�u�����ڈD���еľ��w���Σ����������Ŵ�
	CRect m_rcSlavePos_Check;
	CRect m_rcSpecialPos_Check;

	double m_dProportion;//�D������ߣ��D��һ�������c�����Č��H���x
	Point2d m_ptMainLocator;//���cλ�c����������,���������D��
	Point2d m_ptSlaveLocator;//���cλ�c���������ˣ����������D��
	double m_dLocatorAngle;//��λ�c�B���cˮƽ�����ϵĊA��

	int m_nLocatorResize;//���ò��϶�λʱ������޷���ѡ�������ϣ�����Ҫ�ڶ�λ�ߵ���һ�������ϣ�Ԥ�����һ�����ߴ磬����ʵ�ֲ��Կ�����

	vector<Point2f> m_vptContourLimitPt;//������8�����޵�

	vector<Point2f> m_vptMinAreaRectPt;//��С�����ζ���

	double m_dStartTime;
	double m_dEndTime;

	BOOL m_bFindMark;// �Ƿ��ҵ�MARK�c


	void TestRun(BOOL bMultipleThread = FALSE);//�_ʼ�yԇ

	void _SaveContinueImage(CSmartImage * pImgSrc);//�惦�B�m�D��

	BOOL m_bContinueThreadStatus;//�ྀ�̜yԇ�\�Р�B��True - �\�� False - ֹͣ

	vector<CSmartImage> m_vContinueImage; 

	BOOL m_TestThreadBusy[8];

	CSmartImage m_TestThreadImg[8];

	static UINT _TestRunThread(LPVOID pParam);
	UINT _TestRunThreadKernal(void);

	static UINT _AllocImgThread(LPVOID pParam);//�����B�m�D�񾀳�
	UINT _AllocImgThreadKernal(void);

	static UINT _TestContinueThread_0(LPVOID pParam);
	UINT _TestContinueThreadKernal_0(void);

	static UINT _TestContinueThread_1(LPVOID pParam);
	UINT _TestContinueThreadKernal_1(void);

	static UINT _TestContinueThread_2(LPVOID pParam);
	UINT _TestContinueThreadKernal_2(void);

	static UINT _TestContinueThread_3(LPVOID pParam);
	UINT _TestContinueThreadKernal_3(void);

	static UINT _TestContinueThread_4(LPVOID pParam);
	UINT _TestContinueThreadKernal_4(void);

	static UINT _TestContinueThread_5(LPVOID pParam);
	UINT _TestContinueThreadKernal_5(void);

	static UINT _TestContinueThread_6(LPVOID pParam);
	UINT _TestContinueThreadKernal_6(void);

	static UINT _TestContinueThread_7(LPVOID pParam);
	UINT _TestContinueThreadKernal_7(void);


	vector<int> m_vnValidPixelCounter;//��Ч���؜yԇ����
	vector<int> m_vnSideWidthPixel;


	void TestLength(vector<vector<double>> & vdLength, vector<vector<double>> & vdWidth);//�yԇ�L��
	vector<vector<double>> m_vdLengthResult;
	vector<vector<double>> m_vdWidthResult;

	vector<double> m_vdSimliarResult;//���ƶȽY��������݆�����ƶȡ��D�����ƶȣ�

	void TestHorPosition(vector<bool> & vbHorPositionResult);//�yˮƽ��λ��
	vector<bool> m_vbHorPositionResult;//ˮƽ��λ�Ȝyԇ�L�Ȝyԇ�Y��
	
	vector<bool> m_vbVerPositionResult;

	void TestColMean(vector<double> & vdColAreaPropor, vector<double> & vdColMean_H, vector<double> & vdColMean_S, vector<double> & vdColMean_V);//�y�ɫƽ��ֵ

	vector<double> m_vdColAreaPropor;//�yԇ�ɫƽ��ֵ����eƽ��ֵ
	vector<double> m_vdColArea;//�yԇ�ɫƽ��ֵ����eƽ��ֵ
	vector<double> m_vdColMean_H;//�yԇ�ɫƽ��ֵ��Hƽ��ֵ
	vector<double> m_vdColMean_S;//�yԇ�ɫƽ��ֵ��Sƽ��ֵ
	vector<double> m_vdColMean_V;//�yԇ�ɫƽ��ֵ��Vƽ��ֵ
	vector<double> m_vdRepeatAreaPropor_1;
	vector<double> m_vdRepeatAreaPropor_2;
	vector<double> m_vdRepeatAreaPropor_3;

	/*
		m_vnColSurfaceRes
		���c�z�y�Y������춅^�ֲ�����ͣ��aƷ��Ʒ�r���������
		1-©��
		2-�B�a
		//3-©�~
		3-�׶�
		4-����
	*/

	int m_nTestLEDFinish;//LED������ɣ���LED������ɺ���ʱ����ץȡͼ���ٻ�ȡ���

	int m_nValidPixelBkup;//��Ч�������

	BOOL m_bGetValidPixel;//�Ƿ���Ҫ�ٴ�Ӌ��Դ푶�
	vector<BOOL> m_vbLEDScreenRes;
	int m_nTestRes;//�������--�yԇ�Ŀ�����w�Y��


	vector<int> m_vnTestRes;//�������--�yԇ�Ŀ��ÿһ���yԇ�����ĽY��

	void TestLEDScreen(vector<double> & vdColAreaPropor, vector<double> & vdColMean_H, vector<double> & vdColMean_S, vector<double> & vdColMean_V);//�_ʼ�yԇLED��Ļ

	void TestColSortFixed(vector<double> & vdColArea, vector<double> & vdColMean_H, vector<double> & vdColMean_S, vector<double> & vdColMean_V);//�yԇ�ɫ����

	void TestColSortRandom(vector<double> & vdColMean_H, vector<double> & vdColMean_S, vector<double> & vdColMean_V);//�yԇ�ɫ����

	vector<double> m_vdColSortArea;//�yԇ�ɫ������eƽ��ֵ
	vector<double> m_vdColSort_H;//�yԇ�ɫ����Hƽ��ֵ
	vector<double> m_vdColSort_S;//�yԇ�ɫ����Sƽ��ֵ
	vector<double> m_vdColSort_V;//�yԇ�ɫ����Vƽ��ֵ
	vector<int> m_vnColSortRes;//�ɫ����Y��
	int m_nColSortRes;

	void TestColProporAll(vector<double> & vdColAreaPropor, vector<double> & vdColPropor);//�y�ɫ���w����
	vector<double> m_vdColProporAll;//�ɫ���w��������


	void TestColProporPiece(vector<double> & vdColAreaPropor, vector<double> & vdColPropor);//�y�ɫ�ֶα���
	vector<double> m_vdColProporPiece;//�ɫ���w��������


	vector<DISTANCE_XY> m_vDistanceXY;//Ŀ��݆���ļ��������������������������D��

	void TestSidePosition(vector<int> & vnSideWidthPixel, vector<int> & vnValidPixelCounter, vector<double> & vdColAreaPropor);//��Ե������أ���Ч���ؼ�����������e��

	void TestP2PAngle();// �yԇP2P�Ƕ�

	vector<int> m_vnColSurfaceRes;


	vector<vector<vector<Point2i>>> m_vvvptTestPosValue;//�yԇλ�õ���������
	vector<double> m_vdLength_Flatness;//����݆���ߴ电���������ƽ���Ȝy��
	vector<double> m_vdDistance_Flatness;//����݆���g�������������ƽ���Ȝy��
	vector<double>  m_vdAngle_Flatness;

	vector<double> m_vdHighDiffMax;//���ʾ��yԇ�����ÿ���yԇ������ƫ�����������Ȝyԇ��������߶Ȳ�

	vector<vector<int>> m_vvnHighDiffPos;//�a�����߶Ȳ�ăɂ�݆���Ę�̖,ֻ�����ֵ����Сֵ��݆����̖

	vector<Point3d> m_vCurrentCircleParam;//��ǰ�A�����P����

	double m_dP2PAngle;
	double m_dP2PAngleOffset;


	vector<CString> m_vstrCharacter;//�z�y�����ַ���
	vector<vector<int>> m_vvnCharacterPixel;//�z�y�����ַ����ؔ���

	vector<double> m_vdDeepLearnScore;//��ȌW���֔�

	CSmartImage m_ImgShow;

	BOOL CheckResult();//�Д෵�ؽY��

	void GetAllTestSizeByAOI(CRect rcTop, CRect rcAOI, CSmartImage srcImg);//�@ȡ���еĜyԇ����AOI
	int m_nTestProject;//�yԇ�Ŀ
	int m_nTestMode;//�yԇ�����
	int m_nMarkMode;//��λ���
	CString m_strTestName;//�yԇ���Q

	Point2d m_ptMoveCameraMark_A;//�Ƅ����C��A��ӛ�c
	Point2d m_ptMoveCameraMark_B;//�Ƅ����C��B��ӛ�c

	void CheckProportation();//��������У򞾀��
	static UINT _CheckProportationThread(LPVOID pParam);//У�����
	UINT _CheckProportationThreadKernal(void);


	void CmpRun();//���ӌ���, �yԇ���ƶȡ��ɫ �r��Ҫ����
	static UINT _CmpRunThread(LPVOID pParam);//����
	UINT _CmpRunThreadKernal(void);


	double m_dMainPosArea;//��С��Ӿ�����e
	double m_dAreaProporation;//�ڲ��ό��ӵ���r�£���e�ı���
	double m_dSubOffsetX;
	double m_dSubOffsetY;
	double m_dSubOffsetAngle;


	CWnd *m_pTopWnd;
	int m_nTopWndGroup;
	int m_nTopWndNO;

	typedef struct _tagTestInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		int nResult;
		double dResult;
		BOOL bResult;
		int nResCounter;

		int  Result[TEST_INFO_ARRAY_LEN];
		byte byStarGroup[TEST_INFO_ARRAY_LEN];
		char szResult[TEST_INFO_ARRAY_LEN];
		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_INFO;

	CString m_strTestRes;
public:
	CRect m_rcTopWnd;
	CRect m_rcAOI;
	CSmartImage m_ImgSrc;
	CSmartImage m_ImgSave;//�Á���ĈD��
	CSmartImage m_ImgSpecialScope;//���������ͼ��
protected:
	afx_msg LRESULT OnGmsgtestconfigurafinish(WPARAM wParam, LPARAM lParam);//�Д������Ƿ��޸ģ��Ƿ���ҪУ������
	afx_msg LRESULT OnGmsgtestconfigurasetparamsame(WPARAM wParam, LPARAM lParam);//��Ҫ�������������еĲ���ͳһ
	afx_msg LRESULT OnGmsgtestconfigurasetimgparamsame(WPARAM wParam, LPARAM lParam);//��Ҫ�������������еĈD��̎�����ͳһ
	afx_msg LRESULT OnTeststart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgspecialmarkfinish(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	
	afx_msg LRESULT OnShowTestReslut(WPARAM wParam, LPARAM lParam);

public:
	template<typename T>
	BOOL GetLimitValue(vector<T> vSrc, T & Max, T & Min, int & nMaxPos, int & nMinPos)
	{
		if (vSrc.empty())
			return FALSE;

		Max = Min = vSrc[0];
		nMaxPos = nMinPos = 0;

		for (size_t i = 1; i < vSrc.size(); i++)
		{
			if (Max < vSrc[i])
			{
				Max = vSrc[i];
				nMaxPos = i;
			}
			if (Min > vSrc[i])
			{
				Min = vSrc[i];
				nMinPos = i;
			}
		}
		return TRUE;
	}	

};
