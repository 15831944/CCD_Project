#pragma once
#include <PvDevice.h>
#include <PvStream.h>
#include <PvPipeline.h>
#include <PvAcquisitionStateManager.h>
#include <PvDisplayWnd.h>
#include "CallbackThread.h"

#include <iostream>

#define  STC_AUTO_WHITE_BALENCE   4
#define  OPT_AUTO_WHITE_BALENCE   2


#define  USE_DISPLAY_WINDOW   1
#define  USE_CALLBACK         2

#define  WM_MSG_CAMERAINFO   WM_USER + 1

typedef struct _tagStGigEIndex
{
	int nNet;
	int nCam;
}ST_INDEX;


class ListenerBase{
public:
	virtual void Invoke(PvBuffer* pBuffer, void *pUser) = 0;    
};

template <class T>
class MemFuncListener : public ListenerBase
{
public:
	MemFuncListener(T* obj, void (T::*cbf)(PvBuffer* , void *)){
		m_obj = obj;
		m_cbf = cbf;
	};

	virtual void Invoke(PvBuffer* pBuffer, void *pUser)
	{
		(m_obj->*m_cbf)(pBuffer,pUser);
	};
private:
	T* m_obj;
	void (T::*m_cbf)(PvBuffer* , void *);
};

class StDeviceCustom :
	public PvDevice
{
public:
	StDeviceCustom(void);
	~StDeviceCustom(void);
	BOOL ConnectCustom(PvString Pv_MAC, PvString Pv_ID);
	BOOL DisconnectCustom(void);
	void GetIPAddressStr( PvString &aString );
	void GetMACAddressStr( PvString &aString );
	void GetManufacturerInfo( PvString &aString );
	void StartAcquisition(void);
	void StopAcquisition(void);
	bool IsStarted(void);
	PvResult SetExposureTime(int nTime);
	PvResult AutoWhiteBalance(BOOL bStatus, int nCamInfo);

	void _RegisterCallBack();
	template <class T>
	void RegisterCallback(T *obj, void (T::*cbf)(PvBuffer*, void *), void *pUser)
	{
		UnregisterCallback();
		m_Listener = new MemFuncListener<T>(obj, cbf);
		m_pUser = pUser;
	}

	void UnregisterCallback()
	{
		if( m_Listener )
		{
			delete m_Listener;
			m_Listener = NULL;
		}
		m_pUser = NULL;
	}

private:
	ListenerBase* m_Listener;
	void *m_pUser;

public:
	void OnImageCallback(PvBuffer *aBuffer);
	PvPipeline * GetPipeline(void){return &mPipeline;}

private:	
	PvStream mStream;
	PvPipeline mPipeline;

	PvString mIPAddressStr;
	PvString mMACAddressStr;

	void StartStreaming();
	void StopStreaming();

	CallbackThread *mCallbackThread;

	PvUInt64 GetPayloadSize();
	PvAcquisitionStateManager *mAcquisitionStateManager;

public:
	void Init(CWnd *pWnd, INT nNet, INT nCma);
public:
	int  m_nDisplayMode;
	PvDisplayWnd mDisplay;
	void ImageCallback(PvBuffer *aBuffer, void *pValue);
	void GetImage(BYTE * p_Image);
	BOOL m_bColor;//��Ϊδ��ɫͼ��
	CRect DrawImage(CDC * pDC, CRect rcShow, BOOL bKeepScale, BOOL bTopLeft);

public:


	int m_nFrameRate;			// ֡��
	double m_dFPS;				// ��ǰ֡��
	double m_dMbps;				// ��ǰ����

	DWORD m_nFrameCount;		// ����ͼ�����
	DWORD m_dwStartTime;		// ��ʼʱ��
	PvDisplayWnd m_DisWnd;		// ��ʾ����
	CRect m_rcShow;				// ��ʾ����

	BOOL m_bPreparedBuffer;		// �Ƿ��Ѿ�׼����Buffer
	int m_nDeviceSum;			// �������
	BYTE m_IPAdd[4];			// IP��ַ
	BOOL m_bCallBack;			// �ص���ʽ��ʾ
	BOOL m_bDisWnd;				// �Դ���ģʽ��ʾ
	int m_nDisCounter;			// ˢ�¼���

	int m_nUpdateSpeed;


public:
	CWnd  *m_pShowWnd;
	ST_INDEX m_NetCam;

	struct
	{
		BYTE		*pBufferRGB;			// �洢RGBͼ�񻺳�����ָ��
		BYTE		*pBufferRaw8;			// �洢Raw8ͼ�񻺳�����ָ��
		BITMAPINFO	*pBmpInfo;				// ������ʾͼ��Ľṹָ��
		size_t		nImageSize;				// RGBͼ�����ݴ�С
		int			nPixelByte;				// һ��������ռ�ֽ���
		BYTE		*pMultFrame;			// ��֡ģʽ�µļ�¼
	}m_Buffer;	
	void ReleaseBuffer(void);
	void _CallbackKernal(PvBuffer * pBuffer);//��Draw��ͼƬ��ʾ���ؼ���ָ��λ��
	BOOL GetImageReady(BOOL bColor);
	void ImageConversion(BYTE *pImage, CDC *dc, CRect PictureRect);


public:
	CRect  m_rcAOI;

	PvResult SetAOI(CRect rcAOI);//����������񴫸���
	PvResult SetMaxAOI(void); //���ô�����������
	PvResult GetMaxSensorWidth(PvInt64 & nWidth);
	PvResult GetMaxSensorHeight(PvInt64 & nHeight);
};


