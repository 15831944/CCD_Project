#pragma once

#include "resource.h"
#include "StDevice.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#endif

#include <vector>
#include <PvSystem.h>
#include <PvDeviceFinderWnd.h>
#include <PvInterface.h>
#include <PvDisplayWnd.h>

using namespace std;

static UINT gMsgCameraInfo = RegisterWindowMessage(_T("gMsgCameraInfo"));

#define INFO_CAM_CALLBACK	0
#define INFO_CAM_SELECT		1

#define CAM_RES_30      1//30������
#define CAM_RES_130     2//130������
#define CAM_RES_200     3//200������
#define CAM_RES_500     4//500������
#define CAM_RES_600     5//600������
#define CAM_RES_SELF    6//�Զ�������


#define ST_WB_PARAMS	4//��ƽ�Ⅲ��


typedef struct _tagStGigEIndex
{
	int nNet;
	int nCam;
	CString strMac;
}ST_INDEX;

// CStGigECam �Ի���

class AFX_EXT_CLASS CStGigECam : public CTpLayerWnd, public CStDevice
{
	// #define WM_ST_CHANGE_CAMERA			WM_USER + 1
	// #define WM_ST_CHANGE_NET				WM_USER + 2
	// #define WM_ST_CHANGE_CAM				WM_USER + 3
	// #define WM_ST_CHANGE_MAC				WM_USER + 4
	// #define WM_ST_CHANGE_IP				WM_USER + 5

	DECLARE_SERIAL(CStGigECam)

public:
	CStGigECam(CWnd* pParent = NULL);   // ��׼���캯��
	CStGigECam(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CStGigECam();

	// �Ի�������
	enum { IDD = IDD_STGIGECAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	ST_INDEX m_NetCam;			// ������������
	PvAccessType m_AccType;		// ��������
	BOOL m_bUsed;				// �Ƿ�ռ��
	CString m_strMac;			// MAC ��ַ
	CString m_strIp;			// IP ��ַ�ִ�
	CString m_strMask;			// ������
	CString m_strSerial;		// ���к�
	CString m_strManuFacture;	// ������Ϣ
	int m_nInterFace;			// �������

	vector<int> m_vNetIndex;	// �������
	vector<int> m_vCamIndex;	// ͬһ����������������
	vector<CString> m_vMacAdd;	// Mac��ַ
	vector<CString>	m_vIpAdd;	// ���IP��ַ
	int m_nCamSum;				// ͬһ�������������

	CWnd *m_pMgr;				// ���������
	CString m_strChangeMac;		// �ı���Mac
	CString m_strChangeIp;		// �ı���IP

	CWnd *m_pShowWnd;			// ��ʾ����ָ��
	void **m_ppCamTach;			// �����������

	CRect m_rcAOI;				// ���ROI
	long m_nExposureTime;		// �ع�ʱ��
	long m_nUpdateSpeed;		// ˢ���ٶ�
	BOOL m_bWtBalance;			// ��ƽ��
	int m_nFrameRate;			// ֡��
	double m_dFPS;				// ��ǰ֡��
	double m_dMbps;				// ��ǰ����
	BOOL m_bSnap;				// �ɼ�
	int m_nCamResValue;         //�������ֵ

	PvInt64 m_nWbParam[ST_WB_PARAMS];	// ��ƽ�����

	PvInt64 m_nWidthMax;
	PvInt64 m_nWidthMin;
	PvInt64 m_nHeightMax;
	PvInt64 m_nHeightMin;

	int m_nImageCounter;//���{�����@ȡ�D����
	vector<double> m_vdImageCounter;

	struct
	{
		BYTE		*pBufferRGB;			// �洢RGBͼ�񻺳�����ָ��
		BYTE		*pBufferRaw8;			// �洢Raw8ͼ�񻺳�����ָ��
		BITMAPINFO	*pBmpInfo;				// ������ʾͼ��Ľṹָ��
		size_t		nImageSize;				// RGBͼ�����ݴ�С
		int			nPixelByte;				// һ��������ռ�ֽ���
		BYTE		*pMultFrame;			// ��֡ģʽ�µļ�¼
	}m_Buffer;								// ���Buffer

protected:
	CWnd *m_pShowWndBkup;

	DWORD m_nFrameCount;		// ����ͼ�����
	DWORD m_dwStartTime;		// ��ʼʱ��
	PvDisplayWnd m_DisWnd;		// ��ʾ����
	CRect m_rcShow;				// ��ʾ����
	PvDeviceFinderWnd m_DevFinder;			// �豸��Ѱ

	LARGE_INTEGER m_Freq;//Ӌ��CӲ���㾫��Ӌ�r������
	LARGE_INTEGER m_BeginTime;//�߾���Ӌ����Ӌ�r

	BOOL m_bPreparedBuffer;		// �Ƿ��Ѿ�׼����Buffer
	int m_nDeviceSum;			// �������
	BYTE m_IPAdd[4];			// IP��ַ
	BOOL m_bCallBack;			// �ص���ʽ��ʾ
	BOOL m_bDisWnd;				// �Դ���ģʽ��ʾ
	BOOL m_bColor;				// �Ƿ�Ϊ��ɫ���
	int m_nDisCounter;			// ˢ�¼���

	CSemaphore m_seWnd;			// ����ָ����
	CSemaphore m_seBuffer;		// Buffer��
	CSemaphore m_seGetImage;	// �@ȡ�D����

	//////////////////////////////////////////////////////////////////////////
	long m_nExposureTimeBkup;
	long m_nUpdateSpeedBkup;
	BOOL m_bWtBalanceBkup;
	int m_nCamResValueBkup;

	CRect m_rcAOIBkup;


public:
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	void ShowParamWnd(int nShow);

	BOOL Init(CWnd * pWnd, CRect rcShow);	// ��ʼ��
	PvResult Init(void * pWnd, CRect rcShow, PvUInt32 unID, COLORREF rgbBack = RGB_TRANS_TOP_KEY);

	PvResult CamSelect(CWnd * pParent = nullptr);	// �豸ѡ��

	BOOL Connect(BOOL bScaledAOI);			// ����
	BOOL Disconnect(void);					// �Ͽ�����
	BOOL StartSnap(void);					// ��ʼ�ɼ�
	BOOL StopSnap(void);					// ֹͣ�ɼ�
	BOOL IsColor(void);						// �Ƿ�Ϊ��ɫ���
	void DetachShowWnd(void);				// �Ͽ�����
	void SetShowMode(BOOL bMode);			// ��ʾ��������

	PvResult GetSensorLimitWidth(PvInt64 & nMaxWidth, PvInt64 & nMinWidth);			// ȡ�����Ĵ��������
	PvResult GetSensorLimitHeight(PvInt64 & nMaxHeight, PvInt64 & nMinHeight);			// ȡ�����Ĵ������߶�

	CRect GetAOI(void);										// ȡ��AOI
	PvResult GetScaledAOI(CRect rcWnd, CRect & rcAOI);		// ȡ�ñ���AOI
	PvResult SetAOI(CRect rcAOI);							// ����AOI	
	PvResult SetScaledAOI(CRect rcShow);					// ���ñ���AOI
	PvResult SetMaxAOI(void);								// �������AOI

	PvResult SetExposureTime(long nTime);					// �����ع�ʱ��
	PvResult GetExposureTime(long & nTime);					// ȡ���ع�ʱ��
	int GetExposureTime(void);								// ȡ���ع�ʱ��

	PvResult AutoWtBalance(BOOL bOn);						// ��ƽ��
	BOOL GetWtBalnce(void);									// ȡ�ð�ƽ��״̬

	void SetUpdateSpeed(long nSpeed);						// ����ˢ���ٶ�
	long GetUpdateSpeed(void);								// ȡ��ˢ���ٶ�

	void RegisterCallback(void);							// �ص�������
	void UnregisterCallback(void);							// ȡ���]�Ի��{����
	PvResult GetPixelBits(PvInt32 & nBits);					// ȡ������λ��
	PvResult GetImageSize(PvInt32 & nSize);					// ȡ��ͼ���С
	BOOL GetImage(BYTE * pImgDst);							// ȡ��һ֡ͼ��
	BOOL GetImageCallback(BYTE * pImgDst, BOOL bNext);					// ͨ�^���{����ָ�ȡ��һ֡ͼ��
	PvBuffer *m_pCallbackBuffer;							// �ɆT���{����ָ�׃����ÿ����һ�λ��{������ԓָᘸ���һ��
	int m_nCallbackCounter;									// ���л��{�����ĴΔ�������Д��Ƿ�������һ���D��

	AFX_INLINE CRect DrawImage(CDC * pDC, CRect rcShow,
		BOOL bKeepScale = FALSE, BOOL bTopLeft = FALSE);	// ��DC�л�ͼ��

	virtual void SaveSetData(CString * pPath = nullptr);	// �������ò���
	virtual void LoadSetData(CString * pPath = nullptr);	// �������ò���

protected:
	void _UpdateUi(void);//���¿ؼ�״̬
	void _UpdateCamResStatus();//��������ѡ��״̬

	PvResult _SetScaledAOI(void);				// ���ñ���AOI

	BOOL _PrepareForShowImage(BOOL bColor);		// ׼����ʾͼ��
	void _ReleaseBuffer(void);					// �ͷ�Buffer
	void _ImageCallback(PvBuffer *pBuffer, void *pValue);	// �ص�������

	AFX_INLINE void _CallbackKernal(PvBuffer * pBuffer);

	static UINT _ShowThumThread(LPVOID pParam);
	UINT _ShowThumThreadKernal(void);

public:
	void PosChangedSbExposureTime(long nNewPos);
	void PosChangedSbUpdateSpeed(long nNewPos);
	void StatusChangedSwCamCnt(BOOL bStatus);
	void StatusChangedSwCamSnap(BOOL bStatus);
	void StatusChangedSwCamWtBalance(BOOL bStatus);
protected:
	afx_msg LRESULT OnGmsgcamerainfo(WPARAM wParam, LPARAM lParam);	
public:
	void LBtClickedRdResReset(long nFlags);
	void StatusChangedRdRes30(BOOL bNewStatus);
	void StatusChangedRdRes130(BOOL bNewStatus);
	void StatusChangedRdRes200(BOOL bNewStatus);
	void StatusChangedRdRes500(BOOL bNewStatus);
	void StatusChangedRdRes600(BOOL bNewStatus);
	void StatusChangedRdResSelf(BOOL bNewStatus);

public:
// 	PvStream mStream;
// 	PvPipeline mPipeline;
// 
// 	void StartStreaming();
// 	void StopStreaming();
// 
// 	CStCallBack *mCallbackThread;
// 
// 	PvUInt64 GetPayloadSize();
// 	PvAcquisitionStateManager *mAcquisitionStateManager;

public:
	BOOL SetPulseGenerator(int nIndex, int nDurationOfHigh, int nDurationOfLow, BOOL bTrgMode, int nPulseScale);
	BOOL SetOnceTrigger(int nIndex, int nSleepTime);//�O��һ���|�l
	BOOL SetControlBit(int nIndex, bool bFlg);
};
