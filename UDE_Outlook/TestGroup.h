#pragma once


#include "..\BlendWndDll\MsgBox.h"
#include "..\CRCDll\\ValueCalculate.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

#include<vector>
// CViewTop �Ի���
using namespace std;

#define MOUSE_IN_ADD 1
#define MOUSE_OUT_ADD 2
#define MOUSE_IN_GROUP 3
#define MAX_GROUP 10

#define ROWS_DELETE 0//�����������
#define ROWS_ADD 1//�����������
#define ROWS_SELECT 2//�й���ƶ�
#define NO_ROWS_SELECT 3//�]�й��ָ����
#define DCLICK_LIGHT_ITEM 4//���I�p����Դ��Ԫ��
#define TEST_RUN 5//�_ʼ�քӜyԇ
#define CHECK_RUN 6//�_ʼ����У��
#define MARK_ITEM_CHANGE 7//��ӛ��ʽ��Ԫ����ݸ�׃
#define TEST_MODE_CHANGE 8//�yԇ��͸�׃
#define TEST_PROJECT_CHANGE 9//�yԇ�Ŀ��׃
#define TEST_IMAGE_CHANGE 10//�yԇ�ĈDƬ�l��׃��
#define CMP_RUN 11 //�_ʼ����
#define TEST_STATUS_CHANGE 12//�yԇ��B�l����׃
#define SHOW_TEST_RESULT 13//��ʾ���Խ��
#define DCLICK_TEST_NAME_ITEM 14//���I�p���yԇ�e����Ԫ��


#define GROUP_ADD 1//Ⱥ������
#define GROUP_CHANGE 2
#define GROUP_NO_ROWS 3
#define GROUP_TEST_RUN 4//�_ʼȺ�M�yԇ
#define GROUP_DELETE   5

#define COL_MAX  7//���Ŀ��Д�

#define  WM_LISTCHANGE   WM_USER + 30//�����Ϣ
#define  WM_GROUPCHANGE  WM_USER + 31//Ⱥ��仯��Ϣ

//�ɫ��ֵ;�ɫ���w����;�ɫ�ֶα���;�ɫ�̶�����;�ɫ�S�C����;߅����λ��;����ƥ��;�L�șz�y;P2P���x;�ΑB����
#define TEST_PROJECT    _T("��ֱ��λ��;ˮƽ��λ��;������e;P2P�Ƕ�;�����ɫ�z�y;ƽ����;�ַ��z�y;ҕ�X��λ;��ȌW���z�y;�D�����ƶ�")
//#define TEST_PROJECT    _T("P2P�Ƕ�")//��ʢ����

#include <opencv2\opencv.hpp>
#include <opencv2\features2d\features2d.hpp> 
#include <opencv2\nonfree\features2d.hpp>

using namespace std;
using namespace cv;
// CTestGroup �Ի���

class CTestGroup : public CDialogEx
{
	DECLARE_DYNAMIC(CTestGroup)

public:
	CTestGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestGroup();

// �Ի�������
	enum { IDD = IDD_TESTGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnPaint();
public:
	vector<CRect> m_rcGroup;//�M����
	vector<BOOL> m_bLBtClick;//�c����Ⱥ�M���x�е���r����
	CRect m_rcAdd;//��ӽM����
	BOOL m_bAutoAdd;
	int m_nFocusGroup;
	int m_nOldGroup;
	int m_nCurGroup;
	int m_nCurRow;
	CRect m_rcCurGroup;
	BOOL m_bDraw;
	BOOL m_bGroupChange;//Ⱥ�M��׃
	vector<int> m_nListRowsCounter;//��ͬȺ����б����������
	vector<int> m_nStartCode;//��ͬȺ�M�Ć��Ӵa����

	BOOL m_bItemInputFinish;

	vector<int> m_vnUsedCam;//����ʹ�õ����C��̖
	BOOL m_bTesting;//ܛ�����ԄӜyԇ��
	BOOL m_bLock;//�i����B

	vector<vector<vector<CString>>> m_strAllInfo;//���б����Ϣ

	vector<BOOL> m_vbMergeResult;//���f�Y��ǰ���Ƿ�ρ�Y��

	CString m_strSoftwareVersion;//ܛ���汾̖
public:
	CBL_List m_BL_TestProjectList;
	CBL_Edit m_BL_StartCode;
	CBL_Button m_BL_RunGroup;
	CBL_Button m_BL_Delete;
	CBL_Button m_BL_Add;
	//CBL_CheckBox m_BL_ckMergeResult;

public:
	CWnd *m_pTestGroup;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	int m_nMousePos;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	void UpdateList();//���±���е�����
	void UpdateTestInfo();//�������@ʾ�ı����ݸ������z�y��Ϣ����
	DECLARE_EVENTSINK_MAP()
	void RowsChangedBlTestprojectlist(long nOldRows, long nNewRows, BOOL bAppend);
	void SelectChangedBlTestprojectlist(long nOldSels, long nNewSels);
	void LBtDbClickBlTestprojectlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemChangedBlTestprojectlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	virtual void Serialize(CArchive& ar);
	void ItemEditFinishBlTestprojectlist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlRungroup(long nFlags);
	void StatusChangedBlckmergeresult(short nNewStatus);
	void RButtonUpBlTestprojectlist(long nRow, long nCol, short* pnParam, short nX, short nY);
	void LBtClickedBlDelete(long nFlags);//��Ӧɾ����ť�¼�����

public:
	vector<int> m_vnSelectRows;
	vector<int> _GetSelectRows();//��ѡ���е��к�
	BOOL m_bDelete;//�_�J�Ƿ�h��
	void LBtClickedBlAdd(long nFlags);

public:
	void _SetLockStatus();
};
