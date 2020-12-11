// USBCamMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USBCamMgr.h"
#include "afxdialogex.h"


#define DeviceInstanceIdSize 256	// �豸ʵ��ID��󳤶�

// ��ȡϵͳ��VID��PID����


// CUSBCamMgr �Ի���

IMPLEMENT_DYNAMIC(CUSBCamMgr, CDialogEx)

CUSBCamMgr::CUSBCamMgr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUSBCamMgr::IDD, pParent)
{

}

CUSBCamMgr::~CUSBCamMgr()
{
}

void CUSBCamMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUSBCamMgr, CDialogEx)
END_MESSAGE_MAP()


// CUSBCamMgr ��Ϣ�������

void CUSBCamMgr::CamInfo()
{
}

int CUSBCamMgr::FindCamera()//����USB���C����
{
 	int nUSBCam = 0;
	Mat USBImage;

	m_vFreeCamVIDPID.clear();

	if (WDK_WhoAllVidPid(&m_vVIDPID, 32, &UsbClassGuid, NULL))
	{
		nUSBCam = m_vVIDPID.size();
		for (size_t i = 0; i < m_vVIDPID.size(); i++)
		{
			BOOL bImageValid = FALSE;
			VideoCapture capture;	
			capture.open(i);
			bool stop = false;
			int nFindCamCounter = 0;
			if (nUSBCam == 1)
			{
				while (!stop)        
				{           
					USBImage.release();
					capture >> USBImage;	
					if (!USBImage.empty())
						stop = true;
					if (waitKey(1) >= 0)
						stop = true;																		   
				}
			}
			else
			{
				while (!stop)        
				{           
					USBImage.release();
					capture >> USBImage;	
					nFindCamCounter++;
					if (nFindCamCounter >= 10)
						stop = true;														   
				}
				if (USBImage.empty())
					bImageValid = FALSE;
			}
			if (!USBImage.empty())
			{
				vector<Mat> mChannels;
				split(USBImage, mChannels);
				for (int j = 0; j < USBImage.channels(); j++)
				{
					for (int h = 0; h < USBImage.rows; h++)
					{
						BYTE *pDst = mChannels[j].ptr<BYTE>(h);
						for (int w = 0; w < USBImage.cols; w++)
						{
							if (pDst != NULL)
							{
								if (pDst[w] != 205)//�������Ч����
								{
									bImageValid = TRUE;
									break;
								}
							}
						}
						if (bImageValid)
						{
							break;
						}
					}
					if (bImageValid)
					{
						break;
					}
				}
			}
			
			capture.release();
			if (bImageValid)
			{
				m_vFreeCamVIDPID.push_back(m_vVIDPID[i]);
			}
		}
		nUSBCam = m_vFreeCamVIDPID.size();
	}
	return nUSBCam;
}

void CUSBCamMgr::GetCamInfo()
{


}


void CUSBCamMgr::USBCamShowImg()
{


}

BOOL CUSBCamMgr:: WDK_WhoAllVidPid(vector<HIDD_VIDPID> *pvVidPid, INT iCapacity, const GUID* SetupClassGuid, const GUID* InterfaceClassGuid )
{
	// �����ڲ���
	pvVidPid->clear();
	if (iCapacity <= 0)
	{
		return FALSE;	
	}
	// �����豸��װ��GUID�����յ��豸��Ϣ����
	HDEVINFO DeviceInfoSet = SetupDiCreateDeviceInfoList(SetupClassGuid, NULL );
	if (DeviceInfoSet == INVALID_HANDLE_VALUE) 
	{
		return FALSE;
	}
	// �����豸��װ��GUID��ȡ�豸��Ϣ����
	HDEVINFO hDevInfo;
	if(InterfaceClassGuid == NULL)
	{
		hDevInfo = SetupDiGetClassDevsEx( NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT, DeviceInfoSet, NULL, NULL );
	}
	else
	{
		hDevInfo = SetupDiGetClassDevsEx( InterfaceClassGuid, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT, DeviceInfoSet, NULL, NULL );
	}
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	// �洢�豸ʵ��ID	
	TCHAR DeviceInstanceId[DeviceInstanceIdSize];	

	// �洢�豸��Ϣ����
	SP_DEVINFO_DATA DeviceInfoData;					
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	// ��ȡ�豸��Ϣ����
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hDevInfo, DeviceIndex++, &DeviceInfoData))
	{
		// ��ȡ�豸ʵ��ID
		if (SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, NULL))
		{
			// ���豸ʵ��ID����ȡVID��PID
			TCHAR* pVidIndex = _tcsstr(DeviceInstanceId, TEXT("VID_"));
			if (pVidIndex == NULL) 
			{
				continue;
			}

			TCHAR* pPidIndex = _tcsstr(pVidIndex + 4, TEXT("PID_"));
			if (pPidIndex == NULL) 
			{
				continue;
			}

			HIDD_VIDPID VIDPIDTem;
			VIDPIDTem.VendorID = _tcstoul(pVidIndex + 4, NULL, 16);
			VIDPIDTem.ProductID = _tcstoul(pPidIndex + 4, NULL, 16);

			BOOL bHasSameID = FALSE;

			if (pvVidPid->size() <= 0)//������]��Ԫ��
			{
				pvVidPid->push_back(VIDPIDTem);
			}
			else
			{
				for (size_t i = 0; i < pvVidPid->size(); i++)//���������������Ƿ������ֵͬ
				{
					if ((VIDPIDTem.VendorID == (*pvVidPid)[i].VendorID) && (VIDPIDTem.ProductID == (*pvVidPid)[i].ProductID))
					{
						bHasSameID = TRUE;
						break;
					}
				}
				if (!bHasSameID)
				{
					pvVidPid->push_back(VIDPIDTem);
				}
			}
		}
	}
	return TRUE;
}