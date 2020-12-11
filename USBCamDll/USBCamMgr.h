#pragma once

#include "Resource.h"

#include <opencv2\opencv.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\nonfree\features2d.hpp>

extern "C" {  
#include "setupapi.h" 
#include "hidsdi.h" 
}

using namespace std;
using namespace cv;

#include <SetupAPI.h>
#pragma comment(lib, "Setupapi.lib")

#include "vfw.h"
#pragma comment(lib, "Vfw32.lib")

#define MY_USB_PID_VID	_T("VID_1111&PID_2222")

#include <initguid.h>
#pragma comment(lib,"setupapi.lib")


#include <windows.h>

typedef struct _HIDD_VIDPID
{
	ULONG	VendorID;
	ULONG	ProductID;
} HIDD_VIDPID;


DEFINE_GUID (UsbClassGuid, 0x6BDD1FC6, 0x810F, 0x11D0, 0xBE, 0xC7, 0x08, 0x00, 0x2B, 0xE2, 0x09, 0x2F);


// CUSBCamMgr �Ի���

class AFX_EXT_CLASS CUSBCamMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CUSBCamMgr)

public:
	CUSBCamMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUSBCamMgr();

// �Ի�������
	enum { IDD = IDD_USBCAMMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	int FindCamera();//����USB���C����


public:

	void USBCamShowImg();
	HWND hWndC;

	void CamInfo();

	void GetCamInfo();

	vector<HIDD_VIDPID> m_vVIDPID;// Ӌ��C�����е�USB���C��VID&PID����

	vector<HIDD_VIDPID> m_vFreeCamVIDPID;//̎춿��f��B�����C��VID��PID��̖

	vector<HIDD_VIDPID> m_vUsedCamVIDPID;//��ʹ�õ����C��VID��PID��̖


	/*
���ܣ���ȡϵͳ�����豸��VIDPID
��ڲ�����
	[out] pVidPid���洢���ص�VIDPID�����Զ����˵��ظ���VIDPID
	[in] iCapacity���洢��Ԫ������������Ϊ32
	[in] SetupClassGuid���豸��װ��GUID��Ĭ��ΪNULL
	[in] InterfaceClassGuid���豸�ӿ���GUID��Ĭ��ΪNULL
����ֵ��
	��ȡ����VID��PID��Ŀ
�ŵ㣺
	ֱ��ͨ���豸ʵ��ID��ȡVIDPID���Ӷ������ȡ�豸·������дIO��
*/

	BOOL WDK_WhoAllVidPid(vector<HIDD_VIDPID> *pvVidPid, INT iCapacity = 32, 
		const GUID* SetupClassGuid = NULL/*�O�䰲�b�GUID*/, 
		const GUID* InterfaceClassGuid = NULL/*�O��ӿ��GUID*/);
};
