
// UDE_OutlookDlg.h : ͷ�ļ�
//

#pragma once

#include <DbgHelp.h>

#include "CreateProject.h"
#include "ControllerDlg.h"
#include "ControllerAddDlg.h"

#include "MsgInfoDlg.h"
#include "CamStc.h"
#include "USBCamStc.h"
#include "ProjectName.h"
#include "ViewDraw.h"
#include "SampleCollectionDlg.h"


#include "..\\BlendWndDll\MsgBox.h"
#include "..\\BlendWndDll\PsdMgr.h"
#include "..\\CRCDll\\CRC.h"
#include "..\\FindFileDll\FindCtrlFile.h"
#include "..\\RegisterDll\RegisterDlg.h"
#include "..\\LightDll\LightCtrl.h"
#include "..\\ExcelDll\Excel.h"
#include "..\\SoftwareManageDll\\ParamManage.h"
#include "..\\SoftwareManageDll\\QualityManage.h"
#include "..\\SoftwareManageDll\\VerisonManage.h"
#include "..\\CodeLoggerDll\\Logger.h"

#include <iostream> 
#include <vector>
#include <math.h>
#include <memory>
#include <array>
#include <iomanip>  
#include <deque>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <set>
#pragma comment(lib,"Winmm.lib")

#include "tlhelp32.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#pragma comment(lib, "..\\Debug\\FindFileDll.lib")
#pragma comment(lib, "..\\Debug\\CamMgrDll.lib")
#pragma comment(lib, "..\\Debug\\RegisterDll.lib")
#pragma comment(lib, "..\\Debug\\LightDll.lib")
#pragma comment(lib, "..\\Debug\\ExcelDll.lib")
#pragma comment(lib, "..\\Debug\\SoftwareManageDll.lib")
#pragma comment(lib, "..\\Debug\\CodeLoggerDll.lib")

#define DEBUGSTYLE   0
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#pragma comment(lib, "..\\Release\\FindFileDll.lib")
#pragma comment(lib, "..\\Release\\CamMgrDll.lib")
#pragma comment(lib, "..\\Release\\RegisterDll.lib")
#pragma comment(lib, "..\\Release\\LightDll.lib")
#pragma comment(lib, "..\\Release\\ExcelDll.lib")
#pragma comment(lib, "..\\Release\\SoftwareManageDll.lib")
#pragma comment(lib, "..\\Release\\CodeLoggerDll.lib")

#define RELEASESTYLE   1
#endif

#define  MAXLEN  50

#define  NO_IMAGE  0
#define  SHOW_IMAGE  1//�����@ʾ���x�����C�Č��r�D��
#define  GET_IMAGE  2//�����@ʾ���x�����C���յĈD��
#define  LOAD_IMAGE 3//�����@ʾ���d�ĈD��

#define  SEARCH_SCOPE 1
#define  MAIN_POS 2
#define  SLAVE_POS 3
#define  TEST_SCPOE 4
#define  SPECIAL_SCPOE 5//������

enum CHANGE_POS{MOUSE_TOPLEFT, MOUSE_TOPRIGHT, MOUSE_BOTTOMLEFT, MOUSE_BOTTOMRIGHT, MOUSE_TOPMIDDLE, MOUSE_BOTTOMMIDDLE, MOUSE_LEFTMIDDLE, MOUSE_RIGHTMIDDLE};
enum SHOW_WND_MODE{SHOW_IMAGE_SINGLE, SHOW_IMAGE_MULTIPLE, SHOW_IMAGE_SCREEN};//�ή����@ʾ,�஋���@ʾ,ȫ���@ʾ
enum GET_IMG_MODE{GET_IMAGE_MODE_SYN, GET_IMAGE_MODE_ASY};//ͬ�r����,�������
enum RUN_CHECK_ERR{RUN_CHECK_PROPOR_ERROR = 1, RUN_CHECK_CMP_ERROR};//����У������,��������
enum FILE_INFO{NO_FILE, NEW_FILE, LOAD_FILE, LOAD_FILE_INFO};//���d�n����Ϣ�ͼ��d�n����ͬ���½��ᣬ���Լ��d�n����Ϣ�����ǲ��ܼ��d�n��
enum COMMUNI_TYPE{PROCESS, MODBUS, CUSTOM, IO_CARD,IO_NET};//�M���gͨӍ��MODBUS�f�h���Զ��x�f�h��IO�忨���W��IO

#define MAXHISTORYPATH 6

#define WM_GROUPTEST_RUN  WM_USER + 4000

#define PROGRAM_LOCK_PASSWORD  _T("UDE88888888")


#define SPACE_TEST_DELAY_TIME   60000//�ո񆢄Ӡ�B�����ӕr 

#define DATA_BASE_NAME			_T("smart_led")				// ���ݿ�����
#define DB_SERVER_HOST			_T("localhost")				// ���ݿ��������ַ
#define DB_SERVER_PORT			3306						// ���ݿ�������˿�
#define DB_SERVER_USER			_T("guest")					// ���ݿ��û���
#define DB_SERVER_PSD			_T("guest")					// ���ݿ�����
#define DB_CLIENT_CHAR_SET		_T("gbk")					// �ͻ����ַ���


LRESULT CALLBACK FrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr);

static void PASCAL  TimerCallBack_GetImageContinue(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
static void PASCAL  TimerCallBack_GroupTestRun(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);


// CUDE_OutlookDlg �Ի���
using namespace LOGGER;

class CUDE_OutlookDlg : public CAppBase
{
// ����
public:
	CUDE_OutlookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDE_OUTLOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int m_nRunStyle;//�D���@ʾģʽ
	int m_nTagStyle;//�D���ӛģʽ
	int m_nCameras;//ʹ�õľW�����C����

	CString m_strPassword;
	CString m_strTimeCounter;

	BOOL m_bAutoRunCheck;//���d�n�����Ԅәz�y���\��
	BOOL m_bAutoFindFile;//�ԄӼ��d�ׂ��n��

	int m_nUSBCameras;//ʹ�õ�USB���C����

	int m_nCurFileStatus;//��ǰ�ļ���B,�cö�eFILE_INFO���ʹ��

	int m_nCommuniType;//ܛ��ͨӍ��ʽ

public:
	void ItemClickMenuAppMain(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);
	void StatusChangedSwAppLock(BOOL bStatus);
	CTimerCtrl m_IdleTimer;								// �Զ�������ʱ��

protected:
	virtual void _PreMenuPopupShow(LPCTSTR strMenu);
	virtual void _ClickMenuItem(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);

public:
	CBlender<CCreateProject> m_CreateProjectDlg;
	CBlender<CMsgInfoDlg> m_MsgInfoDlg;
	vector<CBlender<CControllerDlg>*> m_pControllerDlg;
	CBlender<CControllerAddDlg> m_ControllerAddDlg;
	CBlender<CRegisterDlg> m_Register;
	CLightCtrl m_LightCtrl;//��Դ����������
	CBlender<CProjectName> m_ProjectName; 

	CBlender<CSampleCollectionDlg> * m_pCollection;

	CBlender<CMLTrain> * m_pMLTrain;

	CFindCtrlFile m_FindImageFile;

	vector <CViewTop *> m_TopWnd_Child;
	vector <vector <CViewTop *>> m_TopWnd;

	CValueCalculate m_ValueCalculate;

	CBlender<CParamManage> * m_pParamMange;//���������ָ�
	CBlender<CQualityManage> * m_pQualityMange;//Ʒ�|�����ָ�
	CBlender<CVerisonManage> * m_pVerisonMange;//�汾̖�@ʾָ�

public:
	BOOL m_bAutoSaveNGImg;//�Ԅӱ���NG�D��
	int m_nGetImageMode;//���շ�ʽ  0-ͬ�����գ�1-��������
	BOOL m_bImageTrigger;//�|�lģʽ���գ�������Ҫ�l����Ϣ
	int m_nShowImageMode;//�D���@ʾģʽ��0-�ή����@ʾ  1-�஋���@ʾ  2-ȫ���@ʾ
	BOOL m_bStarTestBySpace;//ʹ�ÿո��I���Ԇ��Ӯ�ǰȺ�M�yԇ��ֻ�m��춆΂�Ⱥ�M

	BOOL m_bTestContinue;//���m�z�y

public:
	CWnd *m_pOutlookDlg;
	BOOL m_nDrawImage;
	BOOL m_bIsDraw;//�L�u�µľ���
	BOOL m_bIsDrawStart;
	BOOL m_bInChangePos;//����ڹ����޸ľ��΃ȣ����S�޸ľ��δ�С
	CPoint m_PtStart;
	CPoint m_PtEnd;
	BOOL m_bViewTopShow;//�Ƿ���viewtop�����@ʾ����o�@ʾ���t�o���L�uROI
	BOOL m_bMousePos[8];
	CRect m_rcChange;//���޸ĵľ���
	int m_nChangePosCounter;//���޸ľ��ε��޸�λ�þ�̖�����ϣ����ϣ����£����£��ϣ��£��������Ξ�0��1��2��3��4��5��6��7
	int m_nTestScopeChangeCounter;
	int m_nMovePos;//�Ƅ�����һ������
	BOOL m_bPosMove;
	CPoint m_ptPosMoveOld;
	CPoint m_ptPosMoveNew;
	CRect m_rcTopWnd;//�D���@ʾ����
	CRect m_rcSingleImgShowWnd[12];
	BOOL m_bUpdateSingleShow[12];
	int m_nSingleCamRes[12];//�΂����C���Мyԇ�Ŀ�ľC�ϽY�� 0 - FALSE  1 - TRUE  2 - ���@ʾ�Y��
	int	m_nSingleImgShowCamNo[12];//�@ʾ�򌦑������C��̖
	CViewDraw m_ViewDraw[12];//������ȫ���@ʾ�r������L�u��͸����Ԓ��

	int m_nCurRowCounter;//��ǰȺ��������� 
	int m_nCurGroup;

	int m_nWaitCamCounter;//�ȴ����������ɼ�ʱ����ʱ������������
	CString m_strSoftwareVersion;//ܛ���汾̖

public:
	int m_nControllerDlgCounter;
	vector<int> m_nTestGroup;
	vector<CString> m_strTestGroup;
	BOOL m_bAutoAdd_MainList;
	BOOL m_bAutoAdd_SlaveList;
	BOOL m_bAllCamConnect;//�������C�B�����
	BOOL m_bRegister; //���ע��ɹ������ں�Ȩ����Ͽ��Ʋ˵�����

public:
	CCRC    m_CRC;
	CFindCtrlFile m_FindCtrlFile;
	CCamStc m_CamStc[MAX_CAM];

	int m_nCurCam;//���ڂ��͈D������Ԓ������C
	CSmartImage m_CurrentImage;
	CTestGroup m_TestGroup;
	CImgBox m_MainImgShow;
	CImgBox m_SingleImgShow[12];
	CSmartImage m_NewImage;

public:
	CUSBCamStc m_USBCamStc[MAX_CAM];

public:
	ST_INDEX m_NetCam[MAX_CAM];
public:
	CBL_Menu  m_BL_MainMenu;
	CBL_Line  m_BL_Line;
	CBL_Switch m_BL_AllTestRun;
	CBL_Button m_BL_TestRunStatus;
	CBL_Edit   m_BL_TestTime;
	CBL_Edit   m_BL_FinishCam;
	CBL_Edit   m_BL_TimeOut;
public:
	double m_dStartTime;
	double m_dEndTime;
public:
	virtual void LockCtrls(int nLock);//��Ӧ�����ؼ���Ϣ
	virtual void PreInitDialog();
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
	virtual void Serialize(CArchive& ar);
protected:
	BOOL _RegisterActivex(BOOL bRegister);

public:
	void InitMainWindow();//��ʼ��������

	void SetMainMenu();//�������˵���

	void CreateChildWindow();//���������������ԶԻ���

	void CleanCurrentReportList();//���Ŀǰ����������

	void SearchConfigurationFile();//����CRC�����ļ�

	void SearchControllerFile();//���һ�̨�����ļ���

	void SearchImageFile();//����NG�DƬ�����ļ��A

	void SearchReportFile();//���ұ��������ļ���

	void CreateTestList_Slave();

	BOOL GetImageFromCam(int nCam, CRect & rcAOI);//ʹ�����C���ի@ȡ�DƬ����o�����C��̖�͈D��ľ���׃��

	BOOL GetImageFromCam(int nCam, CRect & rcAOI, CSmartImage & ImgDst);//ʹ�����C���ի@ȡ�DƬ����o�����C��̖�͈D��ľ���׃��

	DECLARE_EVENTSINK_MAP()

public:
	int m_nHistoryPathCounter;
	vector<CString>  m_strHistoryPath;

	void LoadHistoryPath();//���d�n���vʷ·��

	void UpdateMenu();//���²ˆΙ�

	void SaveHistoryPath();
	
	void OpenprojectWithFilePath(CString strPath);

	void _TestRunCheck(BOOL bAuto = TRUE);//����ǰ��⣨�ֶ��������� or �Զ��������ԣ�

	void _AddTestProject();

	vector<pair<CString, int>> m_vpTestProject;//������Ŀ��������
	vector<pair<CString, int>> m_vpTestProject_CMP;//������Ŀ������Ҫ����

public:
	afx_msg void OnClose();

public:
	CCamMgr m_CamMgr;
	CCamShow m_CamShow[MAX_CAM];

	CUSBCamMgr m_USBCamMgr;//USB���C������

protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	void _NewFile();//�����¹���
	void _SaveFile(BOOL bSaveAs = FALSE);//���湤��
	void _LoadFile();//���d����
	void _SaveImage();//����D��
	void _LoadImage();//���d�D��

	void _SaveFileInfo();//����n����Ϣ�������C��
	void _LoadFileInfo();//�xȡ�n����Ϣ�������C��

	BOOL MouseMoveTranslate(CPoint ptInfo, CRect rcInfo);//�Д��c�Ƿ��ھ��΃�
protected:
	afx_msg LRESULT OnRegister(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawImage(WPARAM wParam, LPARAM lParam);//�յ��W�����C�l����Ϣ
	afx_msg LRESULT OnDrawimageUsb(WPARAM wParam, LPARAM lParam);//�յ�USB���C�l����Ϣ

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
protected:
	afx_msg LRESULT OnTestProjectListChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGroupChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProjectNamecChange(WPARAM wParam, LPARAM lParam);//�յ��M����׃����Ϣ
public:
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnTestfinish(WPARAM wParam, LPARAM lParam);

public:
	void GroupTestRun(int nGroup);//�_ʼȺ�M�z�y

	BOOL m_bGetImageFinish[CAM_MAX];//�Ƿ�@ȡ�ˈD��

	vector<CSmartImage> m_vAllCamImage;//ͼ������������װ���е�ͼ�������12��ͼ�񣬸���Ⱥ���ڲ��Ե���������գ���һ����ÿ̨���������

	vector<CRect> m_vrcAOI;//����������ߴ�

	int m_nAllTestProjectCounter;//����Ⱥ�M�й��ж��ٜyԇ�Ŀ�����Ӌ�㌦�Ӻͱ���У���r���_�J�Ƿ�����������c

	int m_nCurTestProjectCounter;//��ǰ��Ҫ�yԇ��Ⱥ�M�е��ĿӋ�������Ӌ�㮔ǰȺ�M�Ƿ�z�y���

	vector<int> m_vnTestProjectCounter;

	int m_nGetImgCamCounter;//��ǰȺ�M��Ҫ���յ����C����

	vector<int> m_vnGetImgCamCounter;//ÿ��Ⱥ�M��Ҫ���յ����C����

	vector<vector<int>> m_vnGroupGetImgCam;//ÿ���yԇȺ�M��Ҫ���յ����C���چ��ӕr���ͽyӋ���


	void UpdateViewTopWndInfo(int nGroupNum, int nRowNum, BOOL bCheckOnly = FALSE, BOOL bCmpOnly = FALSE);//����ÿ���yԇ����Č��Ӻ�����У����Ϣ

	BOOL CheckViewTopWndInfo(int & nGroup, int & nProject, int & Err);//�z��������Ҫ�z�y���Ŀ�Ƿ�У�����˻��ǌ��ӣ��e�`�����Ă�Ⱥ�M���Ă��yԇ헣������e�`߀�ǌ����e�`

	BOOL m_bAutoCheck;// TRUR �ڰ����ԄӰ��o���������У���͌��ӟo�κΆ��}���t���@ʾ�κ���Ϣ��ֱ���M��yԇ�h��

	vector<CString> m_strTestRunStatus;//������ʾܛ���\��״̬

	BOOL m_bFinishTest;//�ԄӜyԇ���
	int m_nFinishTest;//�yԇ��ɔ���
	int m_nFinishGetImg;//�����������
	int m_nTestGroupBkup;//�yԇȺ�M��ݣ�����Д��Ƿ���Ҫ���´��_��Դ������Ч��

	CString m_strDstWnd;//�yԇĿ�˴������Q

	void ClearTopWndText();//�����ǰ�@ʾ�����ϵ����нY���@ʾ����
public:
	vector<CString> m_vstrTestRes;//�yԇ�Y���ַ�������,�b�d�yԇȺ�M��ÿ���Ŀ�ĽY����ȫ���yԇ����ᣬ���f�oPLC

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
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

		int Result[TEST_INFO_ARRAY_LEN];


		byte byStarGroup[TEST_INFO_ARRAY_LEN];
		char szResult[TEST_INFO_ARRAY_LEN];
		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_INFO;
	void StatusChangedBlAlltestrun(BOOL bStatus);
public:
	HWND m_myCapWnd;

public:
	static UINT _GetCamImageThread_0(LPVOID pParam);
	UINT _GetCamImageThreadKernal_0(void);

	static UINT _GetCamImageThread_1(LPVOID pParam);
	UINT _GetCamImageThreadKernal_1(void);

	static UINT _GetCamImageThread_2(LPVOID pParam);
	UINT _GetCamImageThreadKernal_2(void);

	static UINT _GetCamImageThread_3(LPVOID pParam);
	UINT _GetCamImageThreadKernal_3(void);

	static UINT _GetCamImageThread_4(LPVOID pParam);
	UINT _GetCamImageThreadKernal_4(void);

	static UINT _GetCamImageThread_5(LPVOID pParam);
	UINT _GetCamImageThreadKernal_5(void);

	static UINT _GetCamImageThread_6(LPVOID pParam);
	UINT _GetCamImageThreadKernal_6(void);

	static UINT _GetCamImageThread_7(LPVOID pParam);
	UINT _GetCamImageThreadKernal_7(void);

	static UINT _GetCamImageThread_8(LPVOID pParam);
	UINT _GetCamImageThreadKernal_8(void);

	static UINT _GetCamImageThread_9(LPVOID pParam);
	UINT _GetCamImageThreadKernal_9(void);

	static UINT _GetCamImageThread_10(LPVOID pParam);
	UINT _GetCamImageThreadKernal_10(void);

	static UINT _GetCamImageThread_11(LPVOID pParam);
	UINT _GetCamImageThreadKernal_11(void);

protected:
	afx_msg LRESULT OnGrouptestRun(WPARAM wParam, LPARAM lParam);

protected:

	/*
	nScreenPhysicsWidth  �@ʾ���������L��
	nScreenPhysicsHeight �@ʾ��������߶�
	nScreenPixelWidth    �@ʾ���������L��
	nScreenPixelHeight	 �@ʾ�������ظ߶�
	nDisplayFrequency	 �@ʾ����ˢ���l��
	nScreenPixelWidthNoTask  �@ʾ���������L�� �����΄ՙ�
	nScreenPixelHeightNoTask �@ʾ�������ظ߶� �����΄ՙ�
	*/
	void _GetDisplayScreenInfo(long & nScreenPhysicsWidth, long & nScreenPhysicsHeight,
								long & nScreenPixelWidth, long & nScreenPixelHeight,
								long & nDisplayFrequency,
								int & nScreenPixelWidthNoTask, int & nScreenPixelHeightNoTask);//�@ȡ�@ʾ�����P��Ϣ

	void _UpdateInterface();//���½��棬��춴��_ܛ�����ГQ�@ʾģʽ�r�{��
	
	void _IsShowParamPart(int nShow);//���½���r���Ƿ��@ʾ�ӑB�D���ͅ������ñ�

	void _HideTopeWnd();//�[��ÿ���yԇ�Ŀ��DC��

public:
	UINT m_TimerID;//���_���r���ľ��

	void _TimerGetImageContinue();//���_���r�����m����

	void _TimerGroupTestRun();//���_���r���_ʼȺ�M�yԇ

public:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// 	std::tuple<std::string, int>  
// 		giveName(void)  
// 	{  
// 		std::string cw("Caroline");  
// 		int a(2013);  
// 		std::tuple<std::string, int> t = std::make_tuple(cw, a);  
// 		return t;  
// 	}  

protected:
	
	afx_msg LRESULT OnGmsgappbaseunlockui(WPARAM wParam, LPARAM lParam);

public:
};
