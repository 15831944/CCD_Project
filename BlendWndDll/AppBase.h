#pragma once

#include "Resource.h"
#include "TopBlur.h"

#include <afxsock.h>
#pragma comment(lib, "ws2_32.lib")

#include "..\\MiscKitDll\\ValRst.h"
#include "..\\MiscKitDll\\MiscFuns.h"
#include "..\\MiscKitDll\\SyncCtrl.h"
#include "..\\MiscKitDll\\TimerCtrl.h"
#include "..\\MiscKitDll\\Encryption.h"
#include "..\\MiscKitDll\\HardwareInfo.h"

#include "..\\BlActiveXDll\\BL_Ctrls.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MiscKitDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\MiscKitDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

#define APP_LOCK_AUTO				-1
#define APP_NO_TITLE				_T("�ޱ���")

#define TMR_TOP_LEFT_FLASH			32767		// ��������Ͻ���˸
#define TMR_APP_AUTO_LOCK			32766		// �����Զ��������ʱ��

#define RGB_APP_MAIN_KEY			RGB(55, 56, 57)
#define RGB_TRANS_TOP_KEY			RGB(55, 56, 57)
#define RGB_BT_LAYER_BACK			RGB(45, 50, 55)
#define RGB_ALL_64					RGB(64, 64, 64)
#define RGB_0_255_230				RGB(0, 255, 230)
#define RGB_BT_HOVER_BACK			RGB(70, 70, 70)

#define GET_WORK_AREA(rcWork)		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0)

#define SET_FILE_VERSION(n)			const int nVersion = n; ar << nVersion
#define GET_FILE_VERSION			int nVersion = 0; ar >> nVersion

#define FUN_ERR_INFO_LOAD(Info)		if (nullptr != pErr) *pErr = Info

#define LOCK_CTRL_AUTO				if (nullptr != GetSafeHwnd()) {LockCtrls(APP_LOCK_AUTO);}
#define UPDATE_LOCK_CTRL_AUTO		if (nullptr != GetSafeHwnd()) {UpdateUi(); LockCtrls(APP_LOCK_AUTO);}

#define SET_INI_STR(key, item, str, path)				WritePrivateProfileString(key, item, str, path)
#define SET_INI_INT(key, item, val, path)				{\
															CString si;\
															si.Format(_T("%d"), val);\
															SET_INI_STR(key, item, si, path);\
														}

#define SET_INI_DOUBLE(key, item, val, path)			{\
															CString sd;\
															sd.Format(_T("%f"), (double)(val));\
															SET_INI_STR(key, item, sd, path);\
														}

#define GET_INI_STR(key, item, defval, retstr, path)	GetPrivateProfileString(key, item, defval, retstr.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, path); retstr.ReleaseBuffer()
#define GET_INI_INT(key, item, defval, retval, path)	retval = GetPrivateProfileInt(key, item, defval, path)
#define GET_INI_DOUBLE(key, item, defval, retval, path)	{\
															CString sdef, sval;\
															sdef.Format(_T("%f"), (double)(defval));\
															GET_INI_STR(key, item, sdef, sval, path);\
															retval = _ttof(sval);\
														}
									
enum
{
	FIRE_MODE_MENU = 0,		// �˵�����
	FIRE_MODE_232,			// 232����
	FIRE_MODE_COPYDATA,		// CopyData����
	FIRE_MODE_SHARE_WND,	// Ipc��Ϣ����
	FIRE_MODE_ETHERNET,		// Ethernet����
	FIRE_MODE_AUTO_TST		// �Զ���ͼ����
};

enum
{
	IDC_BT_BASE_OK = 32760,
	IDC_BT_BASE_CANCEL,
	IDC_BT_BASE_APPLY,
	IDC_SW_BASE_LOCK,
	IDC_BT_BASE_MIN,
	IDC_BT_BASE_SIZE,
	IDC_BT_BASE_CLOSE,
	IDC_MENU_APP_MAIN
};

// Ȩ�޼���
enum
{
	PSD_LEVEL_LOCK = -1,	// ����
	PSD_LEVEL_OP = 0,		// ����Ա
	PSD_LEVEL_QC,			// Ʒ��
	PSD_LEVEL_TE,			// ����Ա
	PSD_LEVEL_MGR,			// ����Ա
	PSD_LEVEL_SUM
};

// ������ô���
typedef struct _tagBaseBlurInfo
{
	CWnd *pWnd;
	CString strInfo;
	int nShowCmd;
}BASE_BLUR_INFO;

// �ͻ�������
typedef struct _tagTpUiLine
{
	CString strName;
	int nNum;
	CPoint pt1;
	CPoint pt2;
	COLORREF rgbLine;
	int nWidth;
	int nStytle;
}TP_UI_LINE;


// ���ݿ���Ϣ
typedef struct _tagDbSvrInfo
{
	CString strHost;
	USHORT nPort;

	CString strDbName;
	CString strUser;
	CString strPsd;
	CString strCharSet;
}DB_SVR_INFO;


const UINT gMsgAppBaseLockUi	= RegisterWindowMessage(_T("gMsgAppBaseLockUi"));
const UINT gMsgAppBaseUnlockUi	= RegisterWindowMessage(_T("gMsgAppBaseUnlockUi"));
const UINT gMsgAppBaseSetFocus	= RegisterWindowMessage(_T("gMsgAppBaseSetFocus"));
const UINT gMsgAppBaseLoadFile	= RegisterWindowMessage(_T("gMsgAppBaseLoadFile"));
const UINT gMsgAppBaseFileDirty	= RegisterWindowMessage(_T("gMsgAppBaseFileDirty"));

// CAppBase �Ի���

class AFX_EXT_CLASS CAppBase : public CDialogEx
{
	DECLARE_DYNAMIC(CAppBase)

public:
	CAppBase(CWnd* pParent = NULL);   // ��׼���캯��
	CAppBase(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAppBase();

	// �Ի�������
	enum { IDD = IDD_APPBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	BOOL m_bClickShow;									// ��������
	SOCKET m_Socket;									// �ͻ�Socket
	CString m_strLastFile;								// ��һ�ε��õ���
	CString m_strFilePath;								// ��������·��

	virtual BOOL OnInitDialog();
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);	// ���Ʊ���
	virtual void DrawElement(CDC * pDC, CRect rcDraw);	// �Զ����ͼ
	virtual void DrawLine(CDC * pDC, CRect rcDraw);		// ����
	virtual void LockCtrls(int nLock);					// �����ؼ�
	virtual void PreWndDestroy(void);					// �ڴ�������ǰ���ú���
	virtual BOOL PreTranslateMessage(MSG* pMsg);		// ��Ϣ������

	virtual BOOL ServerMsgPorc(CSocket * pUser, CNewPtr<char> * pGets, CNewPtr<char> * pAns);	// ��������Ϣ������
	virtual BOOL ClientMsgPorc(CAppBase * pUser, CNewPtr<char> * pGets);	// �ͻ�����Ϣ������

	virtual void OnApplyBtClicked(CWnd * pWnd);			// Ӧ�ð�ť������ʱ�ĵ��ú���
	virtual void VariableParamListFun(int nVars, ...);	// Ӧ�ÿɱ��������

	virtual void _ClickMenuItem(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);

	BOOL ShowWindow(int nCmdShow);						// ��ʾ����

	CWnd * GetOwner(void);								// ȡ�ø�����ָ��
	void SetOwner(CWnd * pOwner);						// ���ø�����ָ��

	CString GetTitle(void);								// ȡ�ô��ڱ���
	void SetTitle(const CString & strTitle);			// ���ô��ڱ���

	COLORREF GetTitleColor(void);						// ȡ�ñ����ַ���ɫ
	void SetTitleColor(COLORREF rgbTitle);				// ���ñ����ַ���ɫ

	template<typename T>
	void ChangeFont(T * pCtrl, double dScale)			// �ı�ؼ������С
	{
		COleFont ft = pCtrl->GetFont();
		CY sz = ft.GetSize();
		sz.int64 = (LONGLONG)(sz.int64 * dScale);
		sz.Lo = (unsigned long)(sz.Lo * dScale);
		ft.SetSize(sz);
		pCtrl->SetFont(ft);
	}

	template<typename T>
	void ChangeFont(T * pCtrl, CY szNew)				// �ı�ؼ������С
	{
		COleFont ft = pCtrl->GetFont();
		ft.SetSize(szNew);
		pCtrl->SetFont(ft);
	}

	CString GetTitleFont(void);							// ȡ�ñ�������
	REAL GetTitleFontSize(void);						// ȡ�ñ�������ߴ�
	void SetTitleFont(CString strFont, REAL fSize);		// ���ô��ڱ�������

	void LockStatus(BOOL bLock);						// ���ô��ڿؼ�����

	void DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath);	// ��·����ͼ
	BOOL AddLine(const CString & strName, int nIndex, CPoint pt1, CPoint pt2, COLORREF rgbLine, int nWidth, int nStyle);	// �ڴ����ϻ�һ����
	BOOL DeleteLine(const CString & strName);			// ɾ���ڴ����ϻ�����
	BOOL DeleteLine(int nLine);							// ɾ���ڴ����ϻ�����

	BOOL SendUdpMsg(const CString & strIp, USHORT nPort,
		char * pSend, int & nLength, char * pAns = nullptr, int nWaitTime = 3000);			// ����UDP��Ϣ

	BOOL SendUdpMsg(const CString & strIp, USHORT nPort,
		CNewPtr<char> * pSend, CNewPtr<char> * pAns = nullptr, int nWaitTime = 3000);		// ����UDP��Ϣ

	BOOL SendUdpMsg(const CString & strIp, USHORT nPort,
		const CString & strSend, CString * pAns = nullptr, int nWaitTime = 3000);			// ����UDP��Ϣ
public:
	void LBtClickedBtClose(long nFlags);
	void LBtClickedBtSize(long nFlags);
	void LBtClickedBtMin(long nFlags);
	void LBtClickedBtOk(long nFlags);
	void LBtClickedBtCancel(long nFlags);
protected:
	CWnd *m_pOwner;						// ������
	BOOL m_bStatusLock;					// ״̬����, �����ֱ������Ķ����������״̬��ʶ
	BOOL m_bChildWnd;					// �Ӵ��ڱ��
	BOOL m_bNoMenu;						// ����Ҫ�˵�
	int m_nMenuStart;					// �˵���ʼ����

	COLORREF m_rgbTitle;				// �����ַ���ɫ
	COLORREF m_rgbKey;					// ͸����ɫ

	REAL m_fTitleFontSize;				// ���������С
	CString m_strTitle;					// ���ڱ���
	CString m_strTitleFont;				// ��������

	int m_nBlurCount;					// ������ô������ü���
	CTopBlur m_TopBlur;					// ������ô���
	std::vector<TP_UI_LINE> m_vUiLines;	// UI����

	CBL_Menu m_Menu;					// �˵�
	CBL_Button m_BtBaseClose;			// �رհ�ť
	CBL_Button m_BtBaseSize;			// ��ԭ��ť
	CBL_Button m_BtBaseMin;				// ��С����ť
	CBL_Switch m_swBaseLock;			// ������ť
	CBL_Button m_BtBaseOk;				// ȷ����ť
	CBL_Button m_BtBaseCancel;			// ȡ����ť
	CBL_Button m_btBaseApplay;			// Ӧ�ð�ť

	int m_nUdpMemSize;					// ������ʱUDP��Ϣ��������С
	BOOL m_bNetAnswered;				// ������Ϣ�Ƿ񱻻ظ�
	SOCKADDR_IN m_SockAddr;				// ͨ�ŵ�ַ
	CNewPtr<char> m_NetBuffer;			// ���ջ�����
	CWinThread *m_pNetThread;			// �����߳�

	BOOL m_bAppMain;					// �Ƿ��ǳ���������
	BOOL m_bCanMove;					// �Ƿ�����ƶ�����
	BOOL m_bAppQuit;					// �������˳����
	BOOL m_bUseEscape;					// Esc������Ч���

	virtual void _PreShowWnd(void);		// ��ʾ����ʾ���ô˺���
	virtual void _DefaultFocus(void);	// Ĭ��ӵ�н���Ŀؼ�
	virtual void _WndSizeChange(long nFlags);			// ���ڳߴ�ı亯��

	void _SetWndConer(void);			// ���ô��ڱ߽�͸��
	void _SetRegister(BOOL bState);		// ����ע��״̬
	BOOL _IsRegistered(void);			// ��ѯ����Ƿ��Ѿ�ע��

	int _GetFireMode(void);				// ȡ�ó���������ʽ
	void _SetFireMode(int nMode);		// ���ó���������ʽ

	BOOL _IsFileDirty(void);			// ��ѯ�����Ƿ��޸Ĺ�
	void _FileDirty(BOOL bDirty);		// ���õ����޸ı��

	CString _GetFileName(void);			// ȡ�õ�����
	CString _GetSharePath(void);		// ȡ�ô洢ͨ�������ļ�·��

	BOOL _GetLockState(int nLock, int nLevel);		// ȡ�õ�ǰȨ���Ƿ�����
	BOOL _IsUiLocked(void);							// ��ѯ��������״̬
	void _LockAllUis(BOOL bLock);					// ����ȫ������

	int _GetPsdLevel(void);							// ȡ�õ�ǰȨ��
	BOOL _IsPsdLevel(int nLevel);					// �Ƿ���ĳ��Ȩ��
	void _SetPsdLevel(int nLevel);					// ���õ�ǰȨ��

	void _AddModifyLog(const CString & strLogInfo);	// �����޸���־

	void _SendBlurMsg(BOOL bShow);
	void _AddBlurInfo(CWnd * pDstWnd, const CString & strWnd);
	void _RemoveBlurInfo(CWnd * pDstWnd);

	void _ShowFileErrMsg(CFileException & e, const CString & strTitle);

	CRect _GetScaledRect(int nWidth, int nHeight, CRect rcDraw, BOOL bTopLeft);		// ȡ��һ���ȱ������ŵľ���
	BOOL _LoadImageFromResource(ATL::CImage *pImage, UINT nResID, LPCTSTR lpTyp);	// ����Դ�ļ��м���ͼƬ
private:
	int m_nFlash;
	CTimerCtrl m_FlashTimer;
	CSemaphore m_seTitle;

	static UINT __ReceiveUdpAnsThread(LPVOID pParam);		// ����Upd��������Ϣ�߳�
	UINT __ReceiveUdpAnsThreadKernel(void);					// ����Upd��������Ϣ�߳�	

public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT OnGmsgsemitransblur(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgappbaselockui(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT OnGmsgappbasesetfocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgappbasefiledirty(WPARAM wParam, LPARAM lParam);
};
