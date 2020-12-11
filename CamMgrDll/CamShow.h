#pragma once
#include "NetCamMgr.h"
#include "..\StaticCtrlDll\CtrlBase.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\StaticCtrlDll.lib")
#else
#pragma comment(lib, "..\\Release\\StaticCtrlDll.lib")
#endif

enum
{
	CAM_ATTACH_BY_INDEX = 0,
	CAM_ATTACH_BY_MAC,
	CAM_ATTCH_METHOD_SUM
};

static UINT gMsgCamShowInitFinish = RegisterWindowMessage(_T("gMsgCamShowInitFinish"));
static UINT gMsgCamShowGetNewImage = RegisterWindowMessage(_T("gMsgCamShowGetNewImage"));

// CCamShow

class AFX_EXT_CLASS CCamShow : public CCtrlBase
{
	// ����"XXX"���л�  ��Ҫ5������
	// 1.Ҫ������CObject��
	// 2.����дvoid Serialize( CArchive& ar )
	// 3.����ͷ�ļ�����궨��DECLARE_SERIAL("XXX")
	// 4.�޲����Ĺ��캯��XXX();
	// 5.��ʵ���ļ�cpp�� ʹ�ú궨��DECLARE_SERIAL("XXX"��CObject, 1 /*��İ汾��*/)
	DECLARE_SERIAL(CCamShow) // 3.����ͷ�ļ�����궨��DECLARE_SERIAL("XXX")

public:
	CCamShow();
	virtual ~CCamShow();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShowIndex;
	BOOL m_bImgUpdated;
	BOOL m_bShowCross;
	CString m_strIndex;


	CRect m_rcScale;	// �����������������ʾ���������ʱʹ��
	CRect m_rcThumbnail;

	int m_nAttathMode;
	CCamMgr *m_pCamMgr;
	ST_INDEX m_NetCam;
	BOOL m_bWhiteBalance;
	int m_nExposureTime;
	int m_nUpdateSpeed;
	CRect m_rcAOI;
	
	PvInt64 m_nWbParam[ST_WB_PARAMS];	// ��ƽ�����

	CSemaphore m_seUpdate;

	virtual void Serialize(CArchive& ar, CCamMgr * pMgr);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
	virtual void DrawOthers(CDC * pDC, CRect rcDraw);

	virtual void SaveUpdateImage(void);

	void LockUpdate(BOOL bLock);

	BOOL Init(BOOL bAutoDisconnect = FALSE);
	BOOL Init(CCamMgr * pCamMgr, ST_INDEX NetCam, BOOL bAutoDisconnect = FALSE);	

	void ShowDynamic(BOOL bShow);
	BOOL IsDynamic(void);

	void SetCamPtr(CStCamera *pCam);

	CStCamera * GetCamera(void);
	void DetatchCam(void);

	AFX_INLINE BOOL GetImage(BYTE * pData);

	AFX_INLINE BOOL GetImageCallback(BYTE * pData, BOOL bNext = FALSE);

	AFX_INLINE int GetImageWidth(void);
	AFX_INLINE int GetImageHeight(void);

	AFX_INLINE BOOL IsColor(void);
	AFX_INLINE void DrawImage(int nWidth, int nHeight, int nChannel, BYTE * pData,
		BOOL bKeepScale = TRUE, BOOL bTopLeft = FALSE);

	AFX_INLINE BOOL SetOnceTrigger(int nIndex, int nSleepTime);
	AFX_INLINE BOOL SetControlBit(int nIndex, bool bFlg);

	AFX_INLINE void RegisterCallback();
	AFX_INLINE void UnregisterCallback();


	struct
	{
		BYTE *pBuffer;
		BITMAPINFO *pBmpInfo;
		int nWidth;
		int nHeight;
		BOOL bKeepScale;
		BOOL bTopLeft;
		BOOL bShowStatic;
	}m_ShowInfo;

protected:
	CSemaphore m_seShow;

	BOOL m_bAutoDisconnect;
	BOOL m_bAutoCamera;
	CStCamera *m_pCamera;

	static UINT _CamMgrInitThread(LPVOID pParam);
	UINT _CamMgrInitThreadKernal(void);

	static UINT _CamFindThread(LPVOID pParam);
	UINT _CamFindThreadKernal(void);

	void _DrawCross(CDC * pDC, CRect rcDraw, int nLength, COLORREF rgb);
public:
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT OnGmsgcamerainfo(WPARAM wParam, LPARAM lParam);
};


