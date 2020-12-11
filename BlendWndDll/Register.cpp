// RegLayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "afxdialogex.h"

#define REG_PSD_SUB			5
#define REG_MAX_ID_LEN		32

#define APP_HAS_REGISTERED	_T("�������ע�ᣡ")

// CRegister �Ի���

IMPLEMENT_DYNAMIC(CRegister, CTpLayerWnd)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CRegister::IDD, pParent)
{

}

CRegister::CRegister(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{
}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegister, CTpLayerWnd)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CRegister, CTpLayerWnd)
	ON_EVENT(CRegister, IDC_EDIT_REGWND_PSD, 2, CRegister::EnterPressedEditRegwndpsd, VTS_BSTR)
	ON_EVENT(CRegister, IDC_BT_REGWND_DONGLE, 1, CRegister::LBtClickedBtRegwndDongle, VTS_I4)
END_EVENTSINK_MAP()

// CRegister ��Ϣ�������


BOOL CRegister::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strId = ReadSoftwareId(-1);

	if (IsRegistred(&strId))
	{
		((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_PSD))->SetReadOnly(TRUE);
		((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_PSD))->SetValueText(APP_HAS_REGISTERED);

		m_BtBaseOk.ShowWindow(SW_HIDE);
		m_BtBaseCancel.SetWindowText(_T("�˳�"));

		GetDlgItem(IDC_BT_REGWND_DONGLE)->EnableWindow(FALSE);
	}

	((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_ID))->SetValueText(strId);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRegister::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	const CString strPsd = ((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_PSD))->GetValueText();

	if (strPsd.IsEmpty())
	{
		ShowMsgBox(_T("��Կ����Ϊ�գ�"), _T("ע��"), MB_OK | MB_ICONERROR);
		return;
	}

	CCryptoAes Aes(CRYPT_AES_ECB, REG_MAX_ID_LEN);
	
	const CString strId = ReadSoftwareId(-1);
	const CString strHex = Aes.EncryptStr(strId.Left(REG_PSD_SUB) + strId.Right(REG_PSD_SUB));

	if (strHex == strPsd)
	{
		CRegKey regKey;
		CString strKeyName;

		const CString strPath = Aes.EncryptStr(_T("Register"));

		strKeyName.Format(_T("Software\\%s\\%s"), AfxGetAppName(), strPath);

		const LONG nRes = regKey.Open(HKEY_LOCAL_MACHINE, strKeyName);

		const CString strRegKeyHex = Aes.EncryptStr(_T("SerialNumber"));

		if (ERROR_SUCCESS == nRes)
		{
			regKey.SetStringValue(strRegKeyHex, strPsd);
		}
		else if (ERROR_SUCCESS == regKey.Create(HKEY_LOCAL_MACHINE, strKeyName))
		{
			regKey.SetStringValue(strRegKeyHex, strPsd);
		}
		else
		{
			ShowMsgBox(_T("����ע���ļ�ʧ�ܣ�"), _T("ע��"), MB_OK | MB_ICONERROR);
			return;
		}

		regKey.Close();

		ShowMsgBox(_T("ע��ɹ�"), _T("ע��"), MB_OK | MB_ICONINFORMATION);

		((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_PSD))->SetReadOnly(TRUE);
		((CBL_Edit *)GetDlgItem(IDC_EDIT_REGWND_PSD))->SetValueText(APP_HAS_REGISTERED);

		GetDlgItem(IDC_BT_REGWND_DONGLE)->EnableWindow(FALSE);

		m_BtBaseOk.ShowWindow(SW_HIDE);
		m_BtBaseCancel.SetWindowText(_T("�˳�"));

		_SetRegister(TRUE);

		return;
	}
	else
	{		
		ShowMsgBox(_T("��Կ����ע��ʧ�ܣ�"), _T("ע��"), MB_OK | MB_ICONINFORMATION);

		return;
	}

	CTpLayerWnd::OnOK();
}


BOOL CRegister::IsRegistred(CString * pstrId)
{
	_ReadKeyWord();

	CCryptoAes Aes(CRYPT_AES_ECB, REG_MAX_ID_LEN);

	CString strId = ReadSoftwareId(-1);
	CString strHex = Aes.EncryptStr(strId.Left(REG_PSD_SUB) + strId.Right(REG_PSD_SUB));

	if (strHex == m_strPsd)
	{
		if (nullptr != pstrId)
		{
			*pstrId = strId;
		}

		return TRUE;
	}

	CHardwareInfo DevInfo;
	const std::vector<CString> vMacAdd = DevInfo.GetMacAdd(FALSE, FALSE, FALSE);

	const int nMacs = vMacAdd.size();

	for (int i = 0; i < nMacs; i++)
	{
		strId = vMacAdd[i];
		strId.Remove('-');

		strHex = Aes.EncryptStr(strId.Left(REG_PSD_SUB) + strId.Right(REG_PSD_SUB));

		if (strHex == m_strPsd)
		{
			if (nullptr != pstrId)
			{
				*pstrId = strId;
			}

			return TRUE;
		}
	}

	return FALSE;
}


CString CRegister::ReadSoftwareId(int nDev)
{
	CString strId;
	CHardwareInfo DevInfo;

	BOOL bRetVal = FALSE;

	if (nDev < 0)
	{
		DRIVEINFO DiskInfo;

		bRetVal = DevInfo.GetDriveInfo(-nDev - 1, &DiskInfo);

		if (bRetVal)
		{
			strId = DiskInfo.sSerialNumber;

			const int nLength = strId.GetLength();

			if (nLength < REG_PSD_SUB)
			{
				bRetVal = FALSE;
			}
		}
	}

	if (nDev < 0 && FALSE == bRetVal)
	{
		nDev = -nDev - 1;
	}

	if (nDev >= 0)
	{
		const std::vector<CString> vMacAdd = DevInfo.GetMacAdd(FALSE, FALSE, FALSE);

		if (vMacAdd.size())
		{
			strId = vMacAdd[nDev];
			strId.Remove('-');
		}
	}

	CCryptoAes Aes(CRYPT_AES_ECB, REG_MAX_ID_LEN);

	strId = Aes.EncryptStr(strId.Left(REG_PSD_SUB) + strId.Right(REG_PSD_SUB));

	return strId;
}


void CRegister::_ReadKeyWord(void)
{
	CRegKey regKey;
	CString strKeyName;

	CCryptoAes Aes;
	const CString strPath = Aes.EncryptStr(_T("Register"));

	strKeyName.Format(_T("Software\\%s\\%s"), AfxGetAppName(), strPath);

	BOOL bOpenSuccess = ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE, strKeyName);

	if (bOpenSuccess)
	{
		DWORD dwChars = 1024;

		const CString strRegKeyHex = Aes.EncryptStr(_T("SerialNumber"));

		if (ERROR_SUCCESS == regKey.QueryStringValue(strRegKeyHex, m_strPsd.GetBufferSetLength(MAX_PATH + 1), &dwChars))
		{
			m_strPsd.ReleaseBuffer();
		}
		else
		{
			m_strPsd = strRegKeyHex;
		}

		regKey.Close();
	}
}


void CRegister::EnterPressedEditRegwndpsd(LPCTSTR strValue)
{
	// TODO: �ڴ˴������Ϣ����������
	OnOK();
}


void CRegister::LBtClickedBtRegwndDongle(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
}
