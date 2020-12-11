#pragma once
#include "..\StaticCtrlDll\CtrlBase.h"
#include "USBCamMgr.h"
#include "..\ImgProcDll\ImgBox.h"
#include "USBCamParamDlg.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\StaticCtrlDll.lib")
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#else
#pragma comment(lib, "..\\Release\\StaticCtrlDll.lib")
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#endif


#define APP_FONT		_T("������")
#define FORTH_INT(D)	((int)(D + (D > 0? 0.5: -0.5)))

static UINT gMsgUSBCamShowInitFinish = RegisterWindowMessage(_T("gMsgUSBCamShowInitFinish"));
static UINT gMsgUSBCamDrawFinish     = RegisterWindowMessage(_T("gMsgUSBCamDrawFinish"));

class AFX_EXT_CLASS CUSBCamShow : public CCtrlBase
{
	// ����"XXX"���л�  ��Ҫ5������
	// 1.Ҫ������CObject��
	// 2.����дvoid Serialize( CArchive& ar )
	// 3.����ͷ�ļ�����궨��DECLARE_SERIAL("XXX")
	// 4.�޲����Ĺ��캯��XXX();
	// 5.��ʵ���ļ�cpp�� ʹ�ú궨��DECLARE_SERIAL("XXX"��CObject, 1 /*��İ汾��*/)
	DECLARE_SERIAL(CUSBCamShow) // 3.����ͷ�ļ�����궨��DECLARE_SERIAL("XXX")

public:
	CUSBCamShow(void);
	~CUSBCamShow(void);
public:
	CBlender<CUSBCamParamDlg> m_USBCamParamDlg;
public:
	BOOL Init(CUSBCamMgr * pCamMgr, int nUSBCamNO, BOOL bCreateParam/* = FALSE*/);//�Ƿ񄓽�������Ԓ��
	BOOL Init(BOOL bAutoDisconnect = FALSE);
public:
	VideoCapture m_VedioCapture;	//���Ccapture
	int m_nUSBCamNO;//usb���C��̖

	CSmartImage m_ImgUSBCam;

	BOOL m_bIsShow;//�Ƿ�D���@ʾ

	BOOL m_bCloseFinish;//�Ƿ��˳����

	BOOL m_bCancel;

	void GetUSBCamInfo();//�@ȡ���C�����P��Ϣ

	BOOL m_bUSBCamImgSuccessful;//�ɹ��@ȡ�D��

	double m_dUSBCamExposureValue_H;//�ع�ֵ����

	double m_dUSBCamExposureValue_L;//�ع�ֵ����

	double m_dUSBCamCurExposureValue;

	BOOL m_bUpdateUSBCamInfo;//�������C����

	int m_nUSBCamFPS;//USB���C����

	int m_nUpdateSpeed;//�D���@ʾˢ���ٶ�

	int m_nImageFrame;//�D��ֱ����x��

public:

	BOOL m_bShowIndex;
	BOOL m_bImgUpdated;
	BOOL m_bShowCross;
	CString m_strIndex;

	CRect m_rcScale;	// �����������������ʾ���������ʱʹ��
	CRect m_rcThumbnail;

	int m_nAttathMode;
	CUSBCamMgr *m_pUSBCamMgr;
	BOOL m_bWhiteBalance;
	int m_nExposureTime;

	CSemaphore m_seUpdate;

	//virtual void Serialize(CArchive& ar, CUSBCamMgr * pMgr);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
	virtual void DrawOthers(CDC * pDC, CRect rcDraw);
	//virtual void SaveUpdateImage(void);

	void LockUpdate(BOOL bLock);

	

	void ShowDynamic(BOOL bShow);
	BOOL IsDynamic(void);

	void DetatchCam(void);

	AFX_INLINE BOOL GetImage(BYTE * pData);

	AFX_INLINE int GetImageWidth(void);
	AFX_INLINE int GetImageHeight(void);

	AFX_INLINE BOOL IsColor(void);
	AFX_INLINE void DrawImage(int nWidth, int nHeight, int nChannel, BYTE * pData,
		BOOL bKeepScale = TRUE, BOOL bTopLeft = FALSE);

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

	static UINT _CamMgrInitThread(LPVOID pParam);
	UINT _CamMgrInitThreadKernal(void);

	static UINT _CamFindThread(LPVOID pParam);
	UINT _CamFindThreadKernal(void);

	static UINT _USBCamShowThread(LPVOID pParam);
	UINT _USBCamShowThreadKernal(void);

	void _DrawCross(CDC * pDC, CRect rcDraw, int nLength, COLORREF rgb);

public:
	void USBCamSearchExposureLimit();
};

