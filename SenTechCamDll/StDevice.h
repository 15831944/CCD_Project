#pragma once

#include "StCallBack.h"

#include <PvDevice.h>
#include <PvPipeline.h>
#include <PvStream.h>
#include <PvAcquisitionStateManager.h>

class ListenerBase
{
public:
	// Invoke ����
	virtual void Invoke(PvBuffer * pBuffer, void * pUser) = 0;
};

// ��ģ��
template <class T>
class MemFuncListener : public ListenerBase
{
public:
	MemFuncListener(T * pObj, void (T:: * pCbf)(PvBuffer*, void *))
	{
		m_pObj = pObj;
		m_cbf = pCbf;
	};

	virtual void Invoke(PvBuffer* pBuffer, void *pUser)
	{
		(m_pObj->*m_cbf)(pBuffer, pUser);
	};
private:
	T * m_pObj;
	void (T::*m_cbf)(PvBuffer* , void *);
};


class CStDevice : public PvDevice
{
public:
	CStDevice(void);
	~CStDevice(void);
public:
	PvResult Connect(PvDeviceInfo * pInfo);		// �����豸��Ϣ���Ӻ���
	PvResult ConnectMac(PvString strMac);		// ����Mac��ַ���Ӻ���
	PvResult ConnectIP(PvString strIP);			// ����IP��ַ���Ӻ���
	PvResult SetNewIP(PvString strIP);			// ������IP��ַ
	void	 SetIPAdd(PvString strIP);			// ����IP
	PvResult Disconnect(void);					// �Ͽ�����
	PvString GetIPStr(void);					// ȡ��IP�ַ���

	void SetMacAdd(PvString strMac);			// ����MAC��ַ
	PvString GetMacStr(void);					// ȡ��Mac�ַ���

	PvResult StartSnap(void);					// ��ʼ�ɼ�
	PvResult StopSnap(void);					// ֹͣ�ɼ�
	BOOL IsStarted(void);						// �ж��Ƿ��Ѿ���ʼ�ɼ�

	// ����ģ��: �ص�����
	template <class T>
	void RegisterCallback(T * pObj, void (T:: * pCbf)(PvBuffer *, void *), void * pUser )	// ע��ص�����
	{
		UnregisterCallback();
		m_pListener = new MemFuncListener<T>(pObj, pCbf);
		m_pUser = pUser;
	}

	void UnregisterCallback()					// ȡ��ע��ص�
	{
		if(nullptr != m_pListener)
		{
			delete m_pListener;
			m_pListener = nullptr;
		}

		m_pUser = nullptr;
	}

	void OnImageCallback(PvBuffer * pBuffer);	// �ص�������Ӧ����
	PvPipeline * GetPipeline(void){return &m_Pipeline;}		// ȡ�ùܵ�

protected:
	ListenerBase	*m_pListener;				// ������
	void			*m_pUser;					// �û�
	PvStream		m_Stream;					// ��
	PvPipeline		m_Pipeline;					// �ܵ�

private:
	PvString		m_strIpAdd;					// IP�ַ���
	PvString		m_strMacAdd;				// Mac�ַ���

	CStCallBack *m_pCallbackThread;				// �ص��߳�
	PvAcquisitionStateManager *m_pAcquisitionStateManager;	// �ɼ�״̬����

	PvResult __ConnectSet(PvDeviceInfo * pInfo);	// ��������
	void __StartStreaming(void);					// ��ʼ��
	void __StopStreaming(void);						// ������
	PvUInt64 __GetPayloadSize(void);				// ȡ�ÿռ��С
};