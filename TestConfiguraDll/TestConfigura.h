#pragma once

#include "resource.h"
#include <math.h>
#include <iostream>
#include <io.h>

#include <set>
#include <deque>
#include <queue>

#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"
#include "..\BlendWndDll\MsgBox.h"
#include "..\MachineLearningDll\SVMTrainModel.h"
#include "..\MachineLearningDll\MLTrain.h"
#include "..\CodeSystemDll\QrParse.h"
#include "..\DeepLearnDll\SequentialNet.h"

#include "ImageBinary.h"
#include "ImageGray.h"
#include "ImageMorphology.h"
#include "ImageSmooth.h"
#include "ImageSharpen.h"
#include "ImageEnhancement.h"
#include "ImageCHSplit.h"
#include "ImageColBinary.h"
#include "ImageContourFilter.h"
#include "ParamCopy.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\MachineLearningDll.lib")
#pragma comment(lib, "..\\Debug\\CodeSystemDll.lib")
#pragma comment(lib, "..\\Debug\\DeepLearnDll.lib")
#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\MachineLearningDll.lib")
#pragma comment(lib, "..\\Release\\CodeSystemDll.lib")
#pragma comment(lib, "..\\Release\\DeepLearnDll.lib")
#endif

#include <set>
#include <list>

#include<iostream>

#include <string>
#include <cstring>
using namespace std;

// CTestConfigura �Ի���
extern BOOL _declspec(dllimport) g_bSystemRunStatus;//ܛ���\�Р�B TRUE-�Ԅ�  FALSE-�ք�

enum METHOD {ADD = 1, INSERT, ERASE};//�����D��Y�������ķ���

enum RC_TYPE{RC_MAIN_POS = 1, RC_SLAVE_POS, RC_TEST_POS, RC_SPECIAL_POS};

#define TEST_FIRST_LENGTH			1//�z�y�A���_
#define TEST_FORM_SIMILAR			2//�ΑB���ƶșz�y
#define TEST_PIN_LENGTH				3//PIN�L�z�y
#define TEST_HOR_POSITION			4//ˮƽ��λ�șz�y
#define TEST_VER_POSITION			5//��ֱ��λ�șz�y
#define TEST_COL_MEAN				6//��ɫƽ��ֵ���
#define TEST_COL_PROPOR_All			7//��ɫ���w�������
#define TEST_COL_PROPOR_PIECE       8//��ɫ�ֶα������
#define TEST_P2P_DISTANCE           9//�c�c�c֮�g�ľ��x�y��
#define TEST_VALID_PIXEL            10//�yԇ��Ч����
#define TEST_SIDE_POSITION			11//�yԇ߅����λ��
#define TEST_COL_SORT_FIXED			12//�ɫ�̶�λ������z�y
#define TEST_COL_SORT_RANDOM		13//�ɫ�S�Cλ������z�y
#define TEST_LED_SCREEN				14//LED��Ļ�@ʾ�z�y
#define TEST_P2P_ANGLE				15//P2P�Ƕșz�y
#define TEST_COL_SURFACE			16//�����ɫ�z�y
#define TEST_FLATNESS			    17//ƽ���șz�y
#define TEST_CHARACTER			    18//�ַ��z�y
#define TEST_POSITION			    19//ҕ�X��λ��Ӌ������춈D�����ĵ�XYƫ������
#define TEST_DEEPLEARN              20//��ȌW���z�y
#define TEST_IMG_SIMILARITY         21//�D�����ƶ�

#define IMAGE_PROCESS_MODE  _T("�֏�Դ�D��;����V��;߅���J��;�D������;�D�Q��ҶȈD��;�Ҷ�׃�Q;��ֵ��;�D���D;�ΑB�W����;�D����;�M�ψ@;�D�Q��HSV�D��;�D�Q��RGB�D��;��ɫ��ֵ��;���؞V��;݆�����;�D��ͨ�����x;�D�����;�D�����D;�D���D")

#define TEST_VER_POSITION_TIMES 20
enum IMG_PROCESS_METHOD
{
	IMAGE_SOURCE,
	IMAGE_SMOOTH,
	IMAGE_BINARY,
	IMAGE_MORPHOLOGY,
	IMAGE_GRAY,
	IMAGE_GET_GRAY,
	IMAGE_RGB2HSV,
	IMAGE_INVERSE,
	IMAGE_KEEP,
	IMAGE_CIRCLE,
	IMAGE_HSV2RGB,
	IMAGE_SHARPEN,
	IMAGE_ENHANCEMENT,
	IMAGE_COL_BINARY,
	IMAGE_FILTER_PIX,
	IMAGE_CONTOUR_FILL,
	IMAGE_CH_SPLIT,
	IMAGE_IGNORE,
	IMAGE_ROTATION,
	IMAGE_FLIP
};


#define TEST_PROGRAM_TEXT				_T("�cMARKλ���P�S;�yԇĿ�˔���;�˜ʈD��̎��;����У������;")
#define TEST_FIRST_LENGTH_PROGRAM		_T("")
#define TEST_FORM_SIMILAR_PROGRAM		_T("�O�����ƶ��ֵ")
#define TEST_PIN_LENGTH_PROGRAM			_T("�O�Ø˜��L��;�O�Ø˜ʌ���;�O���L������;�O���L������;�O�Ì�������;�O�Ì�������")
#define TEST_HOR_POSITION_PROGRAM		_T("��������;�O�Ø˜��L��;�O�Ø˜ʌ���;�O��ˮƽƫ������;�O��ˮƽƫ������")
#define TEST_VER_POSITION_PROGRAM		_T("��������;�O�Ø˜ʳߴ�;�O�ð돽ƫ���ֵ;����Pin����;����Pin�g��;����Pin����;����Pin�g��;������X�g��;������Y�g��")
#define TEST_COL_MEAN_PROGRAM			_T("�O����e����;�O����e����;�O��ɫ������_1;�O��ɫ������_1;�O��ɫ������_2;�O��ɫ������_2;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������")
#define TEST_COL_PROPOR_ALL_PROGRAM     _T("�O����e����;�O����e����;�ɫ�����ֵ;�O��ɫ������_1;�O��ɫ������_1;�O��ɫ������_2;�O��ɫ������_2;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������")
#define TEST_COL_PROPOR_PIECE_PROGRAM   _T("�O����e����;�O����e����;�ɫ�����ֵ;�O��ɫ������_1;�O��ɫ������_1;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������")
#define TEST_P2P_DISTANCE_PORGRAM		_T("�O���g������;�O���g������")
#define TEST_VALID_PIXEL_PROGRAM		_T("�O�Üyԇ��ʽ;�O����e����;�O����e����")
#define TEST_SIDE_POSITION_PROGRAM		_T("�O�Ø˜ʳߴ�;�˜�ƫ��;��������;�O�û���߅;�O��ƫ������;�O��ƫ������;�O����Ч��������;�O����Ч��������;߅������;�����茒��;����-�B�m��������;����-�����xɢ�z�y����;����-�xɢ��������")
#define TEST_COL_SORT_FIXED_PROGRAM		_T("")
#define TEST_COL_SORT_RANDOM_PROGRAM	_T("")
#define TEST_LED_SCREEN_PROGRAM			_T("�O����e����;�O����e����;�O��ɫ������_1;�O��ɫ������_1;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������")
#define TEST_P2P_ANGLE_PROGRAM			_T("�O�Ø˜ʽǶ�ƫ��;�O�Ø˜ʰ돽;�O�ð돽ƫ������;�O�ð돽ƫ������")
#define TEST_COL_SURFACE_PROGRAM		_T("��������;�O����e����;�O����e����;���}�D��̎��1;���}̎��1��e����;���}̎��1��e����")//;�O��ɫ������_1;�O��ɫ������_1;�O��ɫ������_2;�O��ɫ������_2;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������")
#define TEST_FLATNESS_PROGRAM			_T("���з���;�O�Üyԇ��ʽ;�O�Üyԇλ��;�O�Ø˜ʳߴ�;�O��ƫ������;�O��ƫ������")
#define TEST_CHARACTER_PROGRAM			_T("�˜��ַ�;�ַ��Д�;��һ���ַ���;�ڶ����ַ���;�W��ģ��·��;�O����e����;�O����e����;�������ֵ")
#define TEST_POSITION_PROGRAM			_T("�O����e����;�O����e����;�O�����ƶ��ֵ;ݔ������")
#define TEST_DEEPLEARN_PROGRAM			_T("�O�Ø˜ʳߴ�;�W��ģ��·��;�W������·��;�W���֔��ֵ")
#define TEST_IMG_SIMILARITY_PROGRAM     _T("�Ȍ���ʽ;�O�����ƶ��ֵ")

#define TEST_PROGRAM_PARAM_UNIT			_T("%;mm;��")

#define TEST_UNIT_DISTANCE    _T("�O�Ø˜��L��;�O�Ø˜ʌ���;�O���L������;�O���L������;�O�Ì�������;�O�Ì�������;�O��ˮƽƫ������;�O��ˮƽƫ������;�O�Ø˜ʰ돽;�O�ð돽ƫ���ֵ;�O��ƫ������;�O��ƫ������;�˜�ƫ��;�O�Ø˜ʳߴ�;߅������;�����茒��;�O�ð돽ƫ������;�O�ð돽ƫ������;�O��ƫ������;�O��ƫ������;�x���ʾ��g��;�O���g������;�O���g������;�O��݆���ߴ�����;�O��݆���ߴ�����;����Pin�g��;����Pin�g��;������X�g��;������Y�g��;�O���a��ֵ")
#define TEST_UNIT_PROPOR      _T("�O�����ƶ��ֵ;�O����e����;�O����e����;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������;�ɫ�����ֵ;�O����Ч��������;�O����Ч��������;����-�B�m��������;����-�����xɢ�z�y����;����-�xɢ��������;���}̎��1��e����;���}̎��1��e����;���}̎��2��e����;���}̎��2��e����")
#define TEST_UNIT_NULL		  _T("�O�����ƶ��ֵ;�Ҷȷ�������;�Ҷȷ�������;�ҶȾ�ֵ����;�ҶȾ�ֵ����;�W��ģ��·��;�W������·��;�W���֔��ֵ")

#define TEST_PROGRAM_TEXT_NO_RESET  _T("�O���L������;�O���L������;�O�Ì�������;�O�Ì�������;�O����e����;�O����e����;�ɫ�����ֵ;�O��ɫ������_1;�O��ɫ������_1;�O��ɫ������_2;�O��ɫ������_2;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������;�O����Ч��������;�O����Ч��������;�Ҷȷ�������;�Ҷȷ�������;�ҶȾ�ֵ����;�ҶȾ�ֵ����;߅������;�����茒��;����-�B�m��������;����-�����xɢ�z�y����;����-�xɢ��������;�O�ð돽ƫ������;�O�ð돽ƫ������;�O�Ø˜ʽǶ�ƫ��;�O��ƫ������;���}̎��1��e����;���}̎��1��e����;���}̎��2��e����;���}̎��2��e����;���}̎��3��e����;���}̎��3��e����;�O��݆���ߴ�����;�O��݆���ߴ�����;�O���g������;�O���g������;�W��ģ��·��;�W������·��;�W���֔��ֵ;�O���a��ֵ;�׶�����;�׶������Δ�;�׶���e;�������ֵ;�O��ƫ�ƽǶ�����;�O��ƫ�ƽǶ�����;��e��������")//��ǰ���Խű������޸ģ��������¶���


#define TEST_PROGRAM_TEXT_ALLOW_EMPTY _T("�yԇĿ�˔���;�O��ɫ������;�O��ɫ������_1;�O��Ͷ�����;�O��Ͷ�����;�O����������;�O����������;�Ҷȷ�������;�Ҷȷ�������;�ҶȾ�ֵ����;�ҶȾ�ֵ����;�����茒��;����-�B�m��������;����-�����xɢ�z�y����;�O�Ø˜ʽǶ�ƫ��;�O��ɫ������_2;�O��ɫ������_2;���}̎��1��e����;���}̎��2��e����;���}̎��3��e����;�����ӛ;�Ȳ���ӛ;�����ӛ��;�@ʾ�˜ʈD��;������X�g��;�׶������Δ�");

#define TEST_FLATNESS_PROGRAM_SPECIAL	_T("���з���;�O�ë@ȡ���ʷ�ʽ;�O�û�������A;�O�û�������B;�O���a��ֵ")//�yԇƽ���������ӛ---���ʾ�


#define GET_STANDARD_METHOD_CUSTOM_LINE       1//�@ȡ���ʵķ�ʽ---�Զ��xֱ��
#define GET_STANDARD_METHOD_CONTOUR_TOP       2//�@ȡ���ʵķ�ʽ---݆��픲�
#define GET_STANDARD_METHOD_CONTOUR_BOTTOM    3//�@ȡ���ʵķ�ʽ---݆���ײ�

enum PROPOR_METHOD//�@ȡ������ʽ
{
	TEST_TARGET_CHECK_BY_LENGTH = 1,    //ʹ����Ӿ����еĽϳ��߽�������У��
	TEST_TARGET_CHECK_BY_WIDDTH,	    //ʹ����Ӿ����еĽ϶̱߽�������У��
	TEST_TARGET_CHECK_BY_STANDARD_LINE, //ʹ�Ø˜ʾ��͹���ĳ��λ��У������
	TEST_TARGET_CHECK_BY_TESTSCOPE_EDGE //ʹ�Üyԇ������߅������У������
};


#define TEST_TARGET_SIDE_STANDARD_UP			1//���Ա�Ե��λ�ȣ����Ϸ���ʼ������Ч����
#define TEST_TARGET_SIDE_STANDARD_DOWN			2//���Ա�Ե��λ�ȣ����·���ʼ������Ч����
#define TEST_TARGET_SIDE_STANDARD_LEFT			3//���Ա�Ե��λ�ȣ����󷽿�ʼ������Ч����
#define TEST_TARGET_SIDE_STANDARD_RIGHT			4//���Ա�Ե��λ�ȣ����ҷ���ʼ������Ч����


enum FLATNESS_POS{TEST_TARGET_FLATNESS_STANDARD_UP = 1, TEST_TARGET_FLATNESS_STANDARD_DOWN,
				  TEST_TARGET_FLATNESS_STANDARD_LEFT, TEST_TARGET_FLATNESS_STANDARD_RIGHT,
				  TEST_TARGET_FLATNESS_STANDARD_MIDDLE};//݆��픲�ƽ���Ȝyԇλ��


#define TEST_TARGET_FLATNESS_WITH_STANDARD_LINE		1//�c���ʾ����^���yԇƽ����
#define TEST_TARGET_FLATNESS_IN_SCOPE				2//�yԇ�����Ȳ����^��λ��

enum VALID_PIXEL_MOTHOD
{
	TEST_VALID_PIXEL_PROPOR = 1,//�y����Ч����ʹ�����ر���
	TEST_VALID_PIXEL_PIX,//�y����Ч����ʹ�����ؔ���
	TEST_VALID_PIXEL_AREA,//�y����Ч����ʹ����e��λ
	TEST_VALID_PIXEL_LENGTH,//�y����Ч����ʹ����С��Ӿ����L
	TEST_VALID_PIXEL_WIDTH//�y����Ч����ʹ����С��Ӿ��Ό�
};

#define TEST_TARGET_DIR_X    1//���Թ���X����
#define TEST_TARGET_DIR_Y    2//���Թ���Y����

#define SORT_AREA      1//������e����݆��
#define SORT_PERIMETER 2//�������L����݆��


#define TEST_SIMILARITY_HIST_CORREL         1//ֱ���D-���P��
#define TEST_SIMILARITY_HIST_CHISQR         2//ֱ���D-����
#define TEST_SIMILARITY_HIST_INTERSECT      3//ֱ���D-ʮ�ֽ���
#define TEST_SIMILARITY_HIST_BHATTACHARYYA  4//ֱ���D-���Ͼ��x
#define TEST_SIMILARITY_EMD                 5//�����Զ���
#define TEST_SIMILARITY_MSSIM               6//�Y��������
#define TEST_SIMILARITY_PHASH               7//��֪��ϣ

#define GET_HOLE_OUT 1//���c�z�y�׶��˜�-�������P
#define GET_HOLE_IN  2//���c�z�y�׶��˜�-�Ȳ��׶�

//�ظ�ͼ���������ڱ�׼ͼ�����޷�ͨ����ͨ���ٴ�ͼ�����ٴβ���

static UINT gMsgShowTestResult			 = RegisterWindowMessage(_T("gMsgTestConfiguraFinish"));//�����������
static UINT gMsgTestConfiguraSetParamSame    = RegisterWindowMessage(_T("gMsgTestConfiguraSetParamSame"));//���ò��Է�Χ�����в�����ͬ
static UINT gMsgTestConfiguraSetImgParamSame    = RegisterWindowMessage(_T("gMsgTestConfiguraSetImgParamSame"));//���ò��Է�Χ�����ЈD��̎�������ͬ
static UINT gMsgSpecialMarkFinish    = RegisterWindowMessage(_T("gMsgSpecialMarkFinish"));//���⹠����ӛ���


static UINT gMsgTestProgramListItemChange    = RegisterWindowMessage(_T("gMsgTestProgramListItemChange"));//�yԇ�_������׃��


static inline bool ContoursSortFun_PosX(vector<cv::Point> contour1,vector<cv::Point> contour2)//X�����С��������
{
	return (contour1[0].x < contour2[0].x);
}

static inline bool ContoursSortFun_PosY(vector<cv::Point> contour1,vector<cv::Point> contour2)
{
	return (contour1[0].y < contour2[0].y);
}


typedef struct _tagCircleParamNewTwo
{
	double x;
	double y;
	double r;
	vector<Point2d> vpt;
}FIT_CIRCLE_PARAM_NEW_TWO;


typedef struct _DISTANCE_XY
{
	double	dDistance_X;
	double	dDistance_Y;
}DISTANCE_XY;


typedef struct _COL_SORT_LIMIT
{
	double	dCol_H_LimitH;
	double	dCol_H_LimitL;
	double	dCol_S_LimitH;
	double	dCol_S_LimitL;
	double	dCol_V_LimitH;
	double	dCol_V_LimitL;

}COL_SORT_LIMIT;



class AFX_EXT_CLASS CTestConfigura : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CTestConfigura)

public:
	CTestConfigura(CWnd* pParent = NULL);   // ��׼���캯��
	CTestConfigura(UINT nIDTemplate, CWnd * pParent = nullptr);

	CTestConfigura(const CTestConfigura & CopyFun);//��ؐ���캯��CTestConfigura

	virtual ~CTestConfigura();

// �Ի�������
	enum { IDD = IDD_TESTCONFIGURA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowTestConfigWnd();
	virtual void LockCtrls(int nLock);//��Ӧ�����ؼ���Ϣ

public:
	vector<COL_SORT_LIMIT> m_vColSortLimit;
	int m_nCurColSortCounter;
public:
	CBL_Edit m_BL_AreaLimit;
	CBL_Edit m_BL_AngleLimit;

	CBL_List m_BL_SetImageList;//�D��̎����

	CBL_List m_BL_TestProgramList;//���Խű����

	CBL_List m_BL_ImageResList;//���Խű����к�ͼ�������Ľ��

	CBL_Edit m_BL_ImageColInfo;//�@ʾ�D���ɫ��Ϣ����ɫ��RGB��HSV���ҶȈD���@ʾ�Ҷ�ֵ

	CBL_Edit m_BL_ImageSize;//�D��ߴ�

	CBL_Button m_BL_ImageCurCol;//��ǰ�����ɫ�@ʾ

	CBL_Button m_BL_ColMaxShow;

	CBL_Button m_BL_ColMinShow;

	CBL_Button m_BL_CurImagePt;//�D�������ָʾ�Į�ǰ����

public:
	CString m_strTitle;
public:
	CValueCalculate m_ValueCalculate;
	CQrParse m_QrParse;

public:
	CBlender<CImageBinary> m_ImageBinary;//�Ҷȶ�ֵ��
	CBlender<CImageSmooth> m_ImageSmooth;//�D��V��
	CBlender<CImageMorphology> m_ImageMorphology;//�ΑB�W����
	CBlender<CImageGray> m_ImageGray;//�Ҷ�����
	CBlender<CImageSharpen> m_ImageSharpen;//߅���J��
	CBlender<CImageEnhancement> m_ImageEnhancement;//�D������
	CBlender<CImageCHSplit> m_ImageCHSplit;//�D��ͨ�����x
	CBlender<CImageColBinary> m_ImageColBinary;//��ɫ��ֵ��
	CBlender<CImageContourFilter> m_ImageContourFilter;//݆���V����

	CSVMTrainModel m_SVM;

	BOOL m_bParamChange;//�������޸�

	int m_nImageFormat;//�D���ʽ 1-�Ҷ� 2-RGB 3-HSV

	CString m_strSoftwareVersion;

public:
	typedef struct _tagTestProgramText
	{
		CString strTestProgramSet;//���Խű���Ŀ����һ��
		CString strTestProgramParam;//���Խű���Ŀ�������ڶ���
		CString strTestProgramParamUnit;//���Խű���Ŀ������λ��������
	}tagTestProgramText;

	typedef struct _tagImageResText
	{
		CString strImageProgram;//�������ݣ���һ��
		CString strImageRes;//ͼ�������ڶ���
	}tagImageResText;

	typedef struct _tagImageColInfo
	{
		int nImageColValue_H;
		int nImageColValue_S;
		int nImageColValue_V;
	}tagImageColInfo;

	vector<tagTestProgramText> m_vstrTestProgram;
	vector<tagImageResText> m_vstrImageRes;
	vector<tagImageResText> m_vstrImageColInfo;//�D���ɫ��Ϣ�����T��춱���僌әz�y��׽�c��HSVֵ

	vector<tagTestProgramText> m_vstrTestProgramBkup;
	vector<tagImageResText> m_vstrImageResBkup;
	vector<tagImageResText> m_vstrImageColInfoBkup;

	vector<CString> m_vstrTestProgramText;
	CString m_strTestProgramText;

	typedef struct _tagSetImageText
	{
		CString strSetImageWay;//ͼ����������һ��
		CString strSetImageParam;//ͼ����������ڶ���
	}tagSetImageText;

	vector<tagSetImageText> m_vstrSetImage;
	vector<tagSetImageText> m_vstrSetImageBkup;

	typedef struct _tagParamCopyInfo
	{
		int     nSelectType;
		CString strParamCopyData;
		int     nSelectType_SP;
		CString strParamCopyData_SP;
	}tagParamCopyInfo;

	tagParamCopyInfo m_tagParamCopyInfo;//��ؐ��Ϣ�Y���w
	
public:
	int m_nTestProject;//�yԇ�Ŀ

	int m_nTestConfigWndType;//������ͣ�����������λ�������Ķ�λ�����������ӛ���yԇ����

	int m_nTestConfiguraNo;//���Է�Χ���

	int m_nTestTargetCounter;//�yԇĿ�˔���

	BOOL m_bTestTargetSamePlane;//����Ŀ���붨λĿ���Ƿ���,TRUE���� FALSE����

	int m_nTestTargetDir;//���Թ����ķ��򣬷֡�X = 1���͡�Y = 2������

	int m_nTestTargetCheckSide;//����У��ʱ��ѡ���׼��

	int m_nTestMethod;//�yԇ��ʽ������yԇƽ���ȕr����Ҫ�x��  ���ʾ����^ƽ���� or �����Ȳ����^ƽ����
					  //�yԇ��Ч���ؕr���x�� ���ر��������ؔ��� or ��e��λ

	int m_nGetStandardMethod;//�@ȡ���ʵķ���

	int m_nStandardPos;//����λ������

	Point2i m_ptStandard_A;//�����cA����
	Point2i m_ptStandard_B;//�����cB����

	BOOL m_bSpecialMarkFinish;//�����ӛ��ɣ�ֻ��ԓ׃��TRUE�r���������@ʾ�����ӛ
	BOOL m_bSpecialMarkFinishBkup;//

	double m_dStandardDistance;//���x���ʾ�λ�ã����У�����H���x�����C�ı���
	double m_dLengthStandard;//�˜��L��
	double m_dLengthLimitL;//�L���`���
	double m_dLengthLimitH;//�L���`���
	double m_dWidthStandard;//�˜ʌ���
	double m_dWidthLimitL;//�����`���
	double m_dWidthLimitH;//�����`���
	double m_dRadiusStandard;//�˜ʰ돽
	double m_dStandardAngleOffset;//��׼ƫ�ƽǶ�

	double m_dRadiusOffsetH;//�돽����
	double m_dRadiusOffsetL;//�돽����

	double m_dRadiusLimit;//�돽�`���

	double m_dSimilarLimit;//���ƶ��`���

	double m_dAreaLimit;//��e�`���
	double m_dAngleLimit;//�Ƕ��`���
	bool m_bSamePlane;//�cMARK�c����
	bool m_bDifferentPlane;//�cMARK�c����
	double m_dTestProportion;//�yԇ����������

	double m_dOffsetStandard;//��Ș˜�߅ƫ�Ƶľ��x
	double m_dOffsetLengthLimitL;//ƫ�ƾ��x�`���
	double m_dOffsetLengthLimitH;//ƫ�ƾ��x�`���
	double m_dOffsetAngle;//����У���r����Ʒ�ăAб�Ƕ�
	double m_dOffsetLength_0;//ˮƽ��λ��ƫ�Ƶ���ֵ
	double m_dOffsetLength_1;//ˮƽ��λ��ƫ�Ƶ���ֵ

	int m_nSideStandard;//���]߅��

	int m_nPixelValidCounter;//��Ч���ظ�������춺ͮaƷ������e

	int m_nCurPixelValidCounter;//��ǰ��Ч���؂���

	double m_dOffsetAngel;//ƫ�ƽǶ�

	double m_dColValue_H;//��ɫ��Hƽ��ֵ
	double m_dColValue_S;//��ɫ��Sƽ��ֵ
	double m_dColValue_V;//��ɫ��Vƽ��ֵ
	
	vector<int> m_vnImgValid_H;//��Ч���ص�Hֵ����
	vector<double> m_vdImgValid_S;//��Ч���ص�Sֵ����
	vector<double> m_vdImgValid_V;//��Ч���ص�Vֵ����


	double m_dColAreaLimitH;//�ɫ��e������
	double m_dColAreaLimitL;//�ɫ��e������
	double m_dColProporLimit;//�ɫ�����ֵ���ַ��z�y�L���������ֵ

	double m_dAreaSumLimit_H;//��e�������ޣ������Мyԇ�M����e����
	double m_dAreaSumLimit_L;//��e�������ޣ������Мyԇ�M����e����

	int m_nSideTestTimes;//��Ե��λ�ȼ�����

	double m_dSideWidth;//��Ե���ʱ����Ե�Ŀ��(��λ������),(�������ñ������޵������У����У������� * ���ر���)

	double m_dLineScanWidth;//ʹ����ɨ���⣬�߿���λ�����ף�

	double m_dLineScanPropor_Conti;//��ɨ��ʱ��ɨ�跶Χ�ڣ�������Ч���ص�ռ��

	double m_dLineScanPropor_DisperStar;//��ɨ��ʱ��ɨ�跶Χ�ڣ�������Ч���ص�ռ��

	double m_dLineScanPropor_Disper;//��ɨ��ʱ��ɨ�跶Χ�ڣ�������Ч���ص�ռ��

	int m_nCol_H_LimitH_P1;//ɫ������
	int m_nCol_H_LimitL_P1;//ɫ������

	int m_nCol_H_LimitH_P2;//ɫ������
	int m_nCol_H_LimitL_P2;//ɫ������
	
	double m_dCol_S_LimitH;//ͶȲ����
	double m_dCol_S_LimitL;//ͶȲ����

	double m_dCol_V_LimitH;//���Ȳ����
	double m_dCol_V_LimitL;//���Ȳ����

	double m_dGraySum;//�Ҷ��ܺ�
	double m_dGrayMean;//�ҶȾ�ֵ
	double m_dGrayVari;//�Ҷȷ���

	double m_dGrayMeanLimit_H;//�ҶȾ�ֵ����
	double m_dGrayMeanLimit_L;//�ҶȾ�ֵ����

	double m_dGrayVariLimit_H;//�Ҷȷ�������
	double m_dGrayVariLimit_L;//�Ҷȷ�������

	double m_dRepeatAreaLimit_H1;//���}�D��̎��1��e����
	double m_dRepeatAreaLimit_L1;//���}�D��̎��1��e����

	double m_dRepeatAreaLimit_H2;//���}�D��̎��2��e����
	double m_dRepeatAreaLimit_L2;//���}�D��̎��2��e����

	double m_dRepeatAreaLimit_H3;//���}�D��̎��2��e����
	double m_dRepeatAreaLimit_L3;//���}�D��̎��2��e����

	double m_dHoleArea;//���c�׶���e
	int    m_nHoleStandard;//���cӋ��˜�
	int    m_nHoleIterTimes;//�׶������Δ�-���g�Δ������g�Ǟ�������߅��������ɵĿ׶��`��

	double m_dDistanceLimit_H;//�g������
	double m_dDistanceLimit_L;//�g������

	double m_dAngleLimit_H;//�Ƕ�ƫ������
	double m_dAngleLimit_L;//�Ƕ�ƫ������
	vector<Point2i> m_vptFlatLine;//����yԇ�c���ʾ��Ƕȣ��t��ԓ׃������M��ֱ�����c

	int m_nCharacterRows;//�ַ��Д�

	int m_nCharactersFirRow;//��һ���ַ���

	int m_nCharactersSecRow;//�ڶ����ַ���

	CString m_strCharacterStandard;//�˜��ַ�

	BOOL m_bCharacterSample;//�ַ��z�y����

	vector<vector<int>> m_vvnCharacterWidth;//�ַ���������

	vector<vector<int>> m_vvnCharacterHeight;//�ַ��߶�����

	vector<vector<int>> m_vvnCharacterPixel;//�ַ����ؔ�

	int m_nPinCounter_Fir;//��һ��Pin����

	double m_dPinDistance_Fir;//��һ��Pin�g��

	int m_nPinCounter_Sec;//�ڶ���Pin����

	double m_dPinDistance_Sec;//�ڶ���Pin�g��

	double m_dPinDistance_Fir2Sec_X;//��һ�ź͵ڶ�����Pin��X������x

	double m_dPinDistance_Fir2Sec_Y;//��һ�ź͵ڶ�����Pin��Y������x

	CString m_strDeepLearnModelPath;//�W��ģ��·�� 
	CString m_strDeepLearnParamPath;//�W������·��
	double  m_dDeepLearnScoreLimit;//�W���֔��ֵ

	int m_nTestSimilarityMethod;//�yԇ�D�����ƶȵķ���

	bool m_bWndShow;//�����Ƿ��@ʾ

	BOOL m_bInside;//�Ƿ�ȥ��݆��

	CSmartImage m_ImgShow;
	CSmartImage m_ImgShowRepeat[6];//���}�D��̎����ĈD��
	CImgBox m_BoxShow;


	CSmartImage m_ImgHSV;//HSV�D�����_�������DHSV�r��ԓ�D�����

	Point2i m_ptLimitLine_1;
	Point2i m_ptLimitLine_2;
	Point2i m_ptLimitLine_3;
	Point2i m_ptLimitLine_4;

	vector<CSmartImage> m_vSegmentImage;//�и���Ī����ַ�
 
	virtual void OnCancel();
	void SetImage(CSmartImage * pSrc);//���D���뺯��
	
	Point3d GetLocation(CSmartImage * pSrc, cvContours * pvTarget);//�M�ψA����

	Point3d GetLocation(vector<Point2i> vOutline);//�M�ψA����(�΂�݆���M�ϣ����؈A������)

	vector<Point3d> GetLocation(CSmartImage * pSrc, double dScore = 0.5);//�M�ψA����(�D���ѽ�̎����ɣ��������п��ԔM�ψ@��݆���a����������Ϣ)

	//void _GetCircle(Point3d ptLoc, CSmartImage ImgSrc);

	BOOL GetContours(cvContours & vOutline);//�@ȡָ��������݆��,���ڶԱ��������ƶȣ�ݔ��݆��������e����

	void GetContoursPerimeter();//�@ȡ݆�����L

	BOOL GetValidPixelSample();//�@ȡ��Ч���؂���(�˜�)

	BOOL GetColSample();//��ȡ��ɫ��Ʒ

	BOOL GetColSurfaceSample();//�@ȡ����̎�팦�ӣ�������@ȡ��ɫ��ֵ����Ę˜����ؔ���

	BOOL GetCharacterSample();//�@ȡ�ַ��z�y���ӣ��@ȡ�ַ��߶Ⱥ͌��ȣ��ַ����ؔ���

	BOOL GetImgSimilaritySample();//�@ȡ�˜�ģ��D����출yԇ�ɏ��D������ƶ� 

	BOOL GetValidPixel(int & nValidPixelCounter, double & dColAreaPropor);//�@ȡ��Ч���؂���(�yԇ)

	BOOL GetContoursMaxLength(vector<double> & dLength, vector<double> & dWidth);//�@ȡ݆�������h�ľ��x

	BOOL GetContoursSimilar(double & dFormSimilar);//��ȡ���ƶȽ��

	BOOL GetHorPosition(bool & bHorPositionResult);//��ȡˮƽ��λ�Ƚ��

	BOOL GetVerPosition(BOOL & bVerPositionResult);//��ȡ��ֱ��λ�Ƚ��

	BOOL GetColMean(double & dColAreaPropor, double & dColMean_H, double & dColMean_S, double & dColMean_V);//��ȡ��ɫ��ƽ��ֵ

	BOOL GetColProporAll(double & dColAreaPropor, double & dColPropor);//��ȡ��ɫ���w����

	BOOL GetColProporPiece(double & dColAreaPropor, double & dColPropor);//��ȡ��ɫ�ֶα���

	BOOL GetP2PDistance(DISTANCE_XY & vDistance);//�@ȡP2P���x�����ص��ǈD�����ĵ��D��ԭ�c����������

	BOOL GetProportion();//Ӌ��ÿ���yԇ�����ı�����

	BOOL GetSidePosition(int & nSideWidthPixel, int & nValidPixelCounter, double & dColAreaPropor);

    void GetSidePositionRetestImg(CSmartImage * ImgSrc_Gray, CSmartImage * ImgDst_Bin);//��ȡ��Ե��λ���ز�ͼ��

	BOOL GetColSortFixed(double & dColArea, double & dColMean_H, double & dColMean_S, double & dColMean_V);

	BOOL GetColSortRandom(double & dColMean_H, double & dColMean_S, double & dColMean_V);

	BOOL GetColSurface(int & nValidPixelCounter, double & dColAreaPropor, double & dRepeatAreaPropor_1, double & dRepeatAreaPropor_2, double & dRepeatAreaPropor_3);//�z�y�����ɫ
	double m_dColSurfaceResType;//��춅^�ֺ��c�z�y�����Ŀ��©�� or �B�a

	BOOL GetFlatness(vector<vector<Point2i>> & vvnTestPosValue);//ƽ���șz�y

	BOOL GetCharacter(CString & strCharacter, vector<int> & vnCharacterPixel);

	BOOL GetDeepLearn(double & dDeepLearnScore);

	BOOL GetImgSimilarity(double & dSimilar);//��ȡ�D�����ƶȽ��

	CSequentialNet m_AiNet;

	BOOL m_bLoadDeepLearnData;

	static BOOL m_bLoadData;//���d�W�������i

	void GetImageRes(const CString strImageProcessMode/*��׼������ظ�����*/, int nTestAgainProcessRow = 0/*�ظ�����ͼ��������к�*/);//���ݽű�����ͼ�����ﴦ���Դͼ���������ͼ��

	/*�D��̎�������ƶ���ʼ�ͽY���У���bShowProcessWnd�@ʾ�D��̎���ڣ�����p��D��̎����*/
	void ImageProcess(CSmartImage * ImgSrc, int nProcessRowStart, int nProcessRowEnd, BOOL bShowProcessWnd = FALSE);

	void ImageColProcess(int & nPixelValidCounter, double & dColValue_H, double & dColValue_S, double & dColValue_V,
		vector<int> & vnImgValid_H, vector<double> & vdImgValid_S, vector<double> & vdImgValid_V);//�D���ɫ̎��������Ч�^��

	void ImageColProcess(int & nPixelValidCounter, vector<int> & vnImgValid_H, vector<double> & vdImgValid_S, vector<double> & vdImgValid_V);//�D���ɫ̎����(����)

	vector<CSmartImage> m_vImgTemplate;//�˜ʈD��ģ��

	cvContours m_vOutlinePropor;//݆��������У�������rʹ��

	cvContours m_vOutline;//݆���������yԇ݆�����ƶȻ�ֱ��λ�ȕrʹ�ã����л�

	double m_dCircleRad;//�A�돽
	Point2d m_ptCircleCenter;//�A������

	CRect m_rcTestConfigura;//�yԇ�����������D���ϵ�λ��

	BOOL m_bColMark;//�ɫ����z�y�r���Ƿ�̎��ɫ��ӛ��

	BOOL m_bMarkOutsideNew;//����ӛ��݆��,��ԓ׃���^�e�Ƿ����݆���������D���ϵ�����

	BOOL m_bMarkInsideNew;//����ӛ��݆��,��ԓ׃���^�e�Ƿ����݆���������D���ϵ�����

	BOOL m_bMarkIgnoreNew;//����ӛ����݆��,��ԓ׃���^�e�Ƿ����݆���������D���ϵ�����

	int m_nColMarkMode;//��ӛģʽ 1-�Ȳ� 2-�ⲿ

	Point2i m_ptMarkLast;//ǰһ����ӛ�c���ژ�ӛ�D��r��ʹ��

	vector<Point2i> m_vptMarkOutside;//�����ӛ(�����D��)
	vector<Point2i> m_vptMarkInside;//�Ȳ���ӛ(�����D��)
	vector<Point2i> m_vptMarkIgnore;//���ԅ^��(�����D��)

	BOOL m_bPtMark;//�c��ӛ����춴_�J��ǰ�c�Ƿ�����Ҫ���cλ

public://�yԇ�Y���ɆT����
	void TestRun();//�_ʼ�yԇ

	static UINT _ConfigTestRunThread(LPVOID pParam);
	UINT _ConfigTestRunThreadKernal(void);

	BOOL m_bTestFinish;//�yԇ���

	int m_nValidPixelCounter;
	double m_dAreaPropor;
	double m_dRepeatAreaPropor_1;
	double m_dRepeatAreaPropor_2;
	double m_dRepeatAreaPropor_3;

	double m_dSimliarResult;//݆�����ƶ�

	BOOL m_bVerPositionResult;//��ֱ��λ�ȽY��

	DISTANCE_XY m_DistanceXY;//ҕ�X��λ�Y��

	vector<vector<Point2i>> m_vvptTestPosValue;//�yƽ���ȵĘO��λ�ú���������

	CString  m_strCharacter;//�ַ��z�y�Y��
	vector<int> m_vnCharacterPixel;//�ַ��z�y���ؔ���

	double m_dDeepLearnScore;//��ȌW���֔�

	double m_dFormSimilar;//�D�����ƶȷ֔�
public:
	//��헔������
	CSmartImage m_ImgBkup;

	//virtual void _PreShowWnd(void);
	Point3d m_CenterPoint;//�׺������c
// 
	vector<Point3d> _GetFitCircle(CSmartImage * pSrc,
		double dRadius, double dScaleMin, double dScaleMax,
		double dScore, int nWant);
// 
 	Point3d _Fitcircle(vector<Point2d> * pvPos);
// 
 	void _UpdateUi(void);//ʹ��׃�����¿ؼ�

	void _UpdateSetImage(void);//ʹ�ÈD��̎������D��̎���ַ�����

	void _UpdateParam(void);//ʹ�������е����ݸ�������Ĳ��Բ�������

	void _UpdateColSurfaceTestInfo(void);//���±���z�y�ɫ��Ϣ

	void _HSVToRGB(int &r, int &g, int &b, int h, int s, int v);//HSVֵ�D�Q��RGBֵ

	vector<Point2i> _GetContoursLimitPos(vector<Point2i> nvContoursSrc);//ݔ��݆��������݆���ĘO�ޣ������ؘO��ֻ������߅����λ�ã�ԓλ�ò�һ����݆����

	void _ContoursPosSort(cvContours & vContours, int nContoursDir) const;//݆��λ������,ݔ�녢����݆�������݆������

	void _ContoursSort(cvContours & vContours, int nSortMode = SORT_AREA);//݆������

	double _GetRotateAngle(Point2f pt_Start,Point2f pt_End) const;//�����ת�Ƕ�

	void _ImageSlicerRow(CSmartImage * ImgSrc, vector<Point2i> & vptEdge, vector<CSmartImage> & vRowImage) const;//�D�����и� 

	bool _ThiningDIBSkeleton (unsigned char* lpDIBBits, int lWidth, int lHeight);//�D�񼚻�������D��Ǽ�

 public:
 	virtual void Serialize(CArchive& ar);
	
	int GetImageProcessMode(CString strInput);//�@ȡ�D��̎��ʽ
	
	DECLARE_EVENTSINK_MAP()
	
	void StatusChangedBlTestInside(short nNewStatus);
	
	void LBtClickedBlGettestproportion(long nFlags);
	void LBtClickedBlSavetestimage(long nFlags);
	void LBtDbClickBlSetimagelist(long nRow, long nCol, short* pnParam, short nFlags);
	void LBtClickedBlImagesrc(long nFlags);
	void LBtClickedBlImagedst(long nFlags);
	void RowsChangedBlSetimagelist(long nOldRows, long nNewRows, BOOL bAppend);
	void ItemChangedBlSetimagelist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);

public:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	virtual void OnOK();

	void LBtClickedBlSetparamsame(long nFlags);
	void LBtClickedBlSetimgparamsame(long nFlags);

public:

	BOOL CheckTestProgramList(int & nErrorRow, BOOL bUpdateParam = FALSE);//�����Խű�����ȷ��
	BOOL CheckFloatText(CString strSrc, CString strErrText, BOOL bWarning = FALSE);//����ַ����Ƿ����������С����Ҫ��
	void InitTestProgramList();//��ʼ���yԇ�����ű�����ʼʱ�����ݲ�����Ŀ��Ԥ���г�������Ŀ
	void InitTestProgramList_Special();//��ʼ�������ӛ�����ű�������״΄����n���r�ĳ�ʼ��

	void LBtDbClickBlTestprogramlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemChangedBlTestprogramlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtClickedBlChecktestprogram(long nFlags);

public:
	int FindProgramInImageResText(vector<tagImageResText> ImageResTextSrc, CString strSrc);//�ڽű������Ѱ�ҽ����Ӧ��Ŀ�Ƿ����
	void _AlterImageResText(CString strSearchSrc, CString strNew, int nMode, int nInsertPos = 0);//�޸ĽY���_�����ݣ�����strSrc-�����ַ���nMode-�޸ķ�ʽ��nInsertPos-����λ��
public:
	CString m_strErrorInfo;

	void LBtClickedBlImagecolmark(long nFlags);
	void LBtClickedBlImagecolmarkcancel(long nFlags);
	void _MarkBtStatusChange(BOOL bMarkStatus, long nFlags = 0);//��ӛ���o��B׃��

	CString m_strMartBtText;
protected:
	afx_msg LRESULT OnGmsgColMarkPoint(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgImgPointMove(WPARAM wParam, LPARAM lParam);
public:
	
protected:
	afx_msg LRESULT OnGmsgtestprogramlistitemchange(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnGmsgColMarkFinish(WPARAM wParam, LPARAM lParam);

public:
	void LBtClickedBlImageptmark(long nFlags);
};

