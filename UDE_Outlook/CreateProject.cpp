// CreateProject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "CreateProject.h"
#include "afxdialogex.h"


// CCreateProject �Ի���

IMPLEMENT_DYNAMIC(CCreateProject, CTpLayerWnd)

CCreateProject::CCreateProject(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CCreateProject::IDD, pParent)
	, m_pCamMgr(NULL)
	, m_bEnableOk(FALSE)
	, m_nCamInitFinish(0)
	, m_strValidCam(_T(""))
	, m_strWindowName(_T(""))
	, m_nUSBCamInitFinish(0)
	, m_bNetCamInitFinish(FALSE)
	, m_bUSBCamInitFinish(FALSE)
{

}

CCreateProject::CCreateProject(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_pCamMgr(NULL)
	, m_bEnableOk(FALSE)
	, m_nCamInitFinish(0)
	, m_strValidCam(_T(""))
	, m_strWindowName(_T(""))
	, m_nUSBCamInitFinish(0)
	, m_bNetCamInitFinish(FALSE)
	, m_bUSBCamInitFinish(FALSE)
{
}

CCreateProject::~CCreateProject()
{
}

void CCreateProject::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	for (int i = 0; i < MAX_CAM; i++)
	{
		DDX_Control(pDX, IDC_ShowImage0 + i, m_CamShow[i]);
		DDX_Control(pDX, IDC_BL_CamInfo0 + i, m_CamInfo[i].CamLabel);
		DDX_Control(pDX, IDC_BL_CamChoose0 + i, m_CamInfo[i].CamChoose);
	}

	for (int i = 0; i < MAX_CAM; i++)
	{
		DDX_Control(pDX, IDC_ShowImage6 + i, m_USBCamShow[i]);
		DDX_Control(pDX, IDC_BL_CamInfo6 + i, m_USBCamInfo[i].CamLabel);
		DDX_Control(pDX, IDC_BL_CamChoose6 + i, m_USBCamInfo[i].CamChoose);
	}
	
	DDX_Control(pDX, IDC_BL_CeateProjectList, m_BL_CreateProjectList);
}


BEGIN_MESSAGE_MAP(CCreateProject, CTpLayerWnd)
	ON_WM_TIMER()
	ON_STN_DBLCLK(IDC_ShowImage0, &CCreateProject::OnStnDblclickShowimage0)
	ON_STN_DBLCLK(IDC_ShowImage1, &CCreateProject::OnStnDblclickShowimage1)
	ON_STN_DBLCLK(IDC_ShowImage2, &CCreateProject::OnStnDblclickShowimage2)
	ON_STN_DBLCLK(IDC_ShowImage3, &CCreateProject::OnStnDblclickShowimage3)
	ON_STN_DBLCLK(IDC_ShowImage4, &CCreateProject::OnStnDblclickShowimage4)
	ON_STN_DBLCLK(IDC_ShowImage5, &CCreateProject::OnStnDblclickShowimage5)
	ON_STN_DBLCLK(IDC_ShowImage6, &CCreateProject::OnStnDblclickShowimage6)
	ON_STN_DBLCLK(IDC_ShowImage7, &CCreateProject::OnStnDblclickShowimage7)
	ON_WM_HOTKEY()
	ON_REGISTERED_MESSAGE(gMsgCamShowInitFinish, &CCreateProject::OnGmsgcamshowinitfinish)
	ON_MESSAGE(WM_MSGCHECKBOX, &CCreateProject::OnMsgcheckbox)
	ON_REGISTERED_MESSAGE(gMsgUSBCamShowInitFinish, &CCreateProject::OnGmsgusbcamshowinitfinish)
	ON_MESSAGE(WM_MSGCHECKBOX_USB, &CCreateProject::OnMsgcheckboxUsb)
	ON_STN_DBLCLK(IDC_ShowImage8, &CCreateProject::OnStnDblclickShowimage8)
	ON_STN_DBLCLK(IDC_ShowImage9, &CCreateProject::OnStnDblclickShowimage9)
	ON_STN_DBLCLK(IDC_ShowImage10, &CCreateProject::OnStnDblclickShowimage10)
	ON_STN_DBLCLK(IDC_ShowImage11, &CCreateProject::OnStnDblclickShowimage11)
END_MESSAGE_MAP()


// CCreateProject ��Ϣ�������
BOOL CCreateProject::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (size_t i = 0; i < MAX_CAM; i++)
	{
		m_CamShow[i].SetBorderColor(RGB(128, 128, 128));
		m_CamShow[i].Invalidate(FALSE);
		m_CamInfo[i].CamChoose.ShowWindow(SW_HIDE);
	}

	for (size_t i = 0; i < MAX_CAM; i++)
	{
		m_USBCamShow[i].SetBorderColor(RGB(128, 128, 128));
		m_USBCamShow[i].m_ImgUSBCam.release();
		m_USBCamShow[i].m_bIsShow = FALSE;
		m_USBCamShow[i].m_bCancel = FALSE;
		m_USBCamShow[i].Invalidate(FALSE);
		m_USBCamInfo[i].CamChoose.ShowWindow(SW_HIDE);
		
	}

	RegisterHotKey(GetSafeHwnd(), 1, 0, VK_F5);//�]�ԟ��I����

	SetTimer(0, 80, nullptr);//�_ʼ�������C

	m_bEnableOk = FALSE;

	m_BtBaseClose.SetEnabled(m_bEnableOk);

	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BL_CreateOK)->EnableWindow(m_bEnableOk);
	GetDlgItem(IDC_BL_CreateCancel)->EnableWindow(m_bEnableOk);

	for (int i = 0; i < MAX_CAM; i++)
	{
		m_strCamSel[i].Empty();
	}

	for (int i = 0; i < MAX_CAM; i++)
	{
		m_strUSBCamSel[i].Empty();
	}

	m_nCamInitFinish = 0;
	m_nUSBCamInitFinish = 0;
	m_bEnableOk = FALSE;
	m_strValidCam.Empty();

	m_bNetCamInitFinish = FALSE;
	m_bUSBCamInitFinish = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCreateProject::DrawElement(CDC * pDC, CRect rcDraw)
{
}

UINT CCreateProject::_CamFindThread(LPVOID pParam)
{
	CCreateProject *pApp = (CCreateProject *)pParam;
	const UINT nRetVul = pApp->_CamFindThreadKernal();

	return nRetVul;
}


UINT CCreateProject::_CamFindThreadKernal(void)
{
	CString strNetCam;
	const size_t nSize = m_pCamMgr->m_vNetCam.size();

	for (size_t i = 0; i < nSize; i++)
	{
		m_CamInfo[i].bActive = TRUE;

		strNetCam.Format(_T("%d-%d"), m_pCamMgr->m_vNetCam[i].nNet + 1, m_pCamMgr->m_vNetCam[i].nCam + 1);

		m_CamInfo[i].CamLabel.SetCaption(strNetCam);//�������C��̖

		m_CamShow[i].Init(m_pCamMgr, m_pCamMgr->m_vNetCam[i], FALSE);
	}


	for (size_t j = 0; j < m_pUSBCamMgr->m_vFreeCamVIDPID.size(); j++)
	{
		for (size_t i = 0; i < m_pUSBCamMgr->m_vVIDPID.size(); i++)
		{
			if ((m_pUSBCamMgr->m_vVIDPID[i].ProductID == m_pUSBCamMgr->m_vFreeCamVIDPID[j].ProductID))
			{
				if (m_pUSBCamMgr->m_vVIDPID[i].VendorID == m_pUSBCamMgr->m_vFreeCamVIDPID[j].VendorID)
				{
					m_USBCamInfo[j].bActive = TRUE;

					strNetCam.Format(_T("USB-%d"), j + 1);

					m_USBCamInfo[j].CamLabel.SetCaption(strNetCam);//�������C��̖
					m_USBCamShow[j].Init(m_pUSBCamMgr, i, FALSE);
					m_USBCamShow[j].m_bIsShow = TRUE;
				}
			}
		}
	}

	return 0;
}


void CCreateProject::_RefindCam(void)
{
	for (size_t i = 0; i < MAX_CAM; i++)
	{
		m_CamInfo[i].CamLabel.SetCaption(_T("---"));
		m_CamInfo[i].CamLabel.SetForeColor(RGB(128, 128, 128));
		m_CamInfo[i].CamChoose.ShowWindow(SW_HIDE);
		m_CamShow[i].SetBorderColor(RGB(128, 128, 128));
		m_CamShow[i].Invalidate(FALSE);
	}


	for (size_t i = 0; i < MAX_CAM; i++)
	{
		m_USBCamInfo[i].CamLabel.SetCaption(_T("---"));
		m_USBCamInfo[i].CamLabel.SetForeColor(RGB(128, 128, 128));
		m_USBCamInfo[i].CamChoose.ShowWindow(SW_HIDE);
		m_USBCamShow[i].SetBorderColor(RGB(128, 128, 128));
		m_USBCamShow[i].m_bIsShow = FALSE;
		m_USBCamShow[i].Invalidate(FALSE);
	}

 	m_strValidCam.Empty();

	for (int i = 0; i < MAX_CAM; i++)
	{
		m_strCamSel[i].Empty();
	}
	for (int i = 0; i < MAX_CAM; i++)
	{
		m_strUSBCamSel[i].Empty();
	}

 	m_nCamInitFinish = 0;
	m_nUSBCamInitFinish = 0;
	m_bEnableOk = FALSE;

	m_BtBaseClose.SetEnabled(m_bEnableOk);
	GetDlgItem(IDC_BL_CreateOK)->EnableWindow(m_bEnableOk);
	GetDlgItem(IDC_BL_CreateCancel)->EnableWindow(m_bEnableOk);

	m_bNetCamInitFinish = FALSE;
	m_bUSBCamInitFinish = FALSE;

	SetTimer(0, 80, nullptr);
}


void CCreateProject::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nAllCam = 0;//�������CӋ��

	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		nAllCam = m_pCamMgr->FindCamera(GetParent()) + m_pUSBCamMgr->FindCamera();  

		if (nAllCam > 0)//�����Ƿ���ھW�j���C��USB���C
		{
			CString strIndex;
			const size_t nNetCameras = m_pCamMgr->m_vNetCam.size();

			const size_t nUSBCameras = m_pUSBCamMgr->m_vFreeCamVIDPID.size();//����ʹ�õ�USB���C

			if (nNetCameras)
			{
				for (size_t i = 0; i < nNetCameras; i++)//�W�����C
				{
					strIndex.Format(_T("%d-%d"), m_pCamMgr->m_vNetCam[i].nNet + 1, m_pCamMgr->m_vNetCam[i].nCam + 1);
					m_strValidCam.Append(strIndex);
					m_CamInfo[i].CamChoose.SetCaption(strIndex);
					m_CamInfo[i].CamChoose.ShowWindow(SW_SHOW);
				}
			}
			else
			{
				m_bNetCamInitFinish = TRUE;
			}
			if (nUSBCameras)
			{
				for (size_t j = 0; j < nUSBCameras; j++)//USB���C
				{
					strIndex.Format(_T("USB-%d"), j + 1);
					m_strValidCam.Append(strIndex);
					m_USBCamInfo[j].CamChoose.SetCaption(strIndex);
					m_USBCamInfo[j].CamChoose.ShowWindow(SW_SHOW);
				}
			}
			else
			{
				m_bUSBCamInitFinish = TRUE;
			}
			m_strValidCam.Delete(m_strValidCam.GetLength() - 1, 1);
			AfxBeginThread(_CamFindThread, this);
		}
		else
		{
			const CString strInfo = _T("�]�аl�F�������C�����ܵ�ԭ���ǣ�\n1. ���Cδ�B�ӣ��B�����C��ˢ�£���\n2. ���C������������ã��P�]�������C�ĳ����ˢ�£���\n3. ���C������B�ӣ���δ��ʼ����ɣ��ȴ���ʼ����ɺ�ˢ�£���");

			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(strInfo, _T("�½��n��"), MB_OK | MB_ICONERROR);

			m_bEnableOk = TRUE;

			m_BtBaseClose.SetEnabled(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateOK)->EnableWindow(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateCancel)->EnableWindow(m_bEnableOk);
		}
		break;
	default:
		break;
	}
	CTpLayerWnd::OnTimer(nIDEvent);
}


void CCreateProject::OnStnDblclickShowimage0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}

void CCreateProject::OnStnDblclickShowimage8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}


void CCreateProject::OnStnDblclickShowimage11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_RefindCam();
}

void CCreateProject::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nHotKeyId)
	{
	case 1:
		m_bEnableOk = FALSE;
		_RefindCam();
		break;
	}
	CTpLayerWnd::OnHotKey(nHotKeyId, nKey1, nKey2);
}


afx_msg LRESULT CCreateProject::OnGmsgcamshowinitfinish(WPARAM wParam, LPARAM lParam)
{
	m_nCamInitFinish++;

	const size_t nSize = m_pCamMgr->m_vNetCam.size();

	if (m_nCamInitFinish >= nSize)
	{
		for (size_t i = 0; i < nSize; i++)
		{
			m_CamShow[i].SetBorderColor(RGB(0,255,255));
			m_CamInfo[i].CamLabel.SetForeColor(RGB(0,255,255));
		}
		m_bNetCamInitFinish = TRUE;
		if (m_bUSBCamInitFinish)
		{
			m_bEnableOk = TRUE;
			m_BtBaseClose.SetEnabled(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateOK)->EnableWindow(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateCancel)->EnableWindow(m_bEnableOk);
		}
	}
	return 0;
}

afx_msg LRESULT CCreateProject::OnGmsgusbcamshowinitfinish(WPARAM wParam, LPARAM lParam)
{
	m_nUSBCamInitFinish++;

	const size_t nSize = m_pUSBCamMgr->m_vFreeCamVIDPID.size();

	if (m_nUSBCamInitFinish >= nSize)
	{
		for (size_t i = 0; i < nSize; i++)
		{
			m_USBCamShow[i].SetBorderColor(RGB(0,255,255));
			m_USBCamInfo[i].CamLabel.SetForeColor(RGB(0,255,255));
		}

		m_bUSBCamInitFinish = TRUE;
		if (m_bNetCamInitFinish)
		{
			m_bEnableOk = TRUE;
			m_BtBaseClose.SetEnabled(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateOK)->EnableWindow(m_bEnableOk);
			GetDlgItem(IDC_BL_CreateCancel)->EnableWindow(m_bEnableOk);
		}
	}
	return 0;
}


void CCreateProject::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!m_bEnableOk)
	{
		return;
	}

	m_pCamMgr->Release();

	for (size_t i = 0; i < m_pUSBCamMgr->m_vFreeCamVIDPID.size(); i++)
	{
		m_USBCamShow[i].m_bCloseFinish = FALSE;
		m_USBCamShow[i].m_bIsShow = FALSE;
		m_USBCamShow[i].m_bCancel = TRUE;
	}

	for (size_t i = 0; i < m_pUSBCamMgr->m_vFreeCamVIDPID.size(); i++)
	{
		while (!m_USBCamShow[i].m_bCloseFinish)
		{
			Sleep(5);
		}
		Sleep(10);
	}
	
	UnregisterHotKey(GetSafeHwnd(), 1);

	CTpLayerWnd::OnCancel();
}
BEGIN_EVENTSINK_MAP(CCreateProject, CTpLayerWnd)
	ON_EVENT(CCreateProject, IDC_BL_CreateCancel, 1, CCreateProject::LBtClickedBlCreatecancel, VTS_I4)
	ON_EVENT(CCreateProject, IDC_BL_CeateProjectList, 5, CCreateProject::LBtDbClickBlCeateprojectlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CCreateProject, IDC_BL_CreateOK, 1, CCreateProject::LBtClickedBlCreateok, VTS_I4)
END_EVENTSINK_MAP()


void CCreateProject::LBtClickedBlCreatecancel(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	OnCancel();
}

void CCreateProject::LBtClickedBlCreateok(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	
	if (nFlags & MK_CONTROL)
	{

	}
	else
	{
		CMsgBox MsgBox(this);

		const CString strName = ((CBL_Edit *)(GetDlgItem(IDC_BL_WindowName)))->GetValueText();//���f�M�����Q
		HWND hWnd = ::FindWindow(NULL, strName);//����Ŀ�괰��
		if(hWnd != NULL)
		{
			MsgBox.ShowMsg(_T("�������Q�Ѵ��ڣ�Ո����ݔ��"), _T("����������"), MB_OK);
			((CBL_Edit *)(GetDlgItem(IDC_BL_WindowName)))->SetValueText(_T(""));
			return;
		}
		m_strWindowName = strName;

		BOOL bChooseCam = FALSE;
		for (int j = 0; j < MAX_CAM; j++)
		{
			if (m_CamInfo[j].CamChoose.GetStatus())
			{
				bChooseCam = TRUE;
				break;
			}
		}
		for (int i = 0; i < MAX_CAM; i++)
		{
			if (m_USBCamInfo[i].CamChoose.GetStatus())
			{
				bChooseCam = TRUE;
				break;
			}
		}
		if (!bChooseCam)
		{
			MsgBox.ShowMsg(_T("δ�x��z�y���C��"), _T("���Cδ�x��"), MB_OK | MB_ICONWARNING);
			return;
		}

		for (int i = 0; i < MAX_CAM; i++)
		{
			if(((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose0 + i)))->GetStatus())
			{
				m_strCamSel[i] = ((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose0 + i)))->GetCaption();
			}
			else
			{
				m_strCamSel[i] = _T("---");
			}
		}

		for (int i = 0; i < MAX_CAM; i++)
		{
			if(((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose6 + i)))->GetStatus())
			{
				m_strUSBCamSel[i] = ((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose6 + i)))->GetCaption();
			}
			else
			{
				m_strUSBCamSel[i] = _T("---");
			}
		}
	}

	for (size_t i = 0; i < m_pUSBCamMgr->m_vFreeCamVIDPID.size(); i++)
	{
		m_USBCamShow[i].m_bCloseFinish = FALSE;
		m_USBCamShow[i].m_bIsShow = FALSE;
		m_USBCamShow[i].m_bCancel = TRUE;
	}

	for (size_t i = 0; i < m_pUSBCamMgr->m_vFreeCamVIDPID.size(); i++)
	{
		while (!m_USBCamShow[i].m_bCloseFinish)
		{
			Sleep(5);
		}
		Sleep(10);
	}

	UnregisterHotKey(GetSafeHwnd(), 1);
	OnOK();
}

void CCreateProject::LBtDbClickBlCeateprojectlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	if (nCol == 0)
	{
		* pnParam = 2;
		m_BL_CreateProjectList.SetDropDownData(_T("��λ��;���a;�_�L"));
	}
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_CreateProjectList.SetDropDownData(m_strValidCam);
	}
}



afx_msg LRESULT CCreateProject::OnMsgcheckbox(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < MAX_CAM; i++)
	{
		if (((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose0 + i)))->IsMsgSrc())
		{
			m_strCamSel[i] = ((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose0 + i)))->GetCaption();
			break;
		}
	}
	return 0;
}

afx_msg LRESULT CCreateProject::OnMsgcheckboxUsb(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < MAX_CAM; i++)
	{
		if (((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose6 + i)))->IsMsgSrc())
		{
			m_strUSBCamSel[i] = ((CBL_CheckBox *)(GetDlgItem(IDC_BL_CamChoose6 + i)))->GetCaption();
			break;
		}
	}
	return 0;
}


void CCreateProject::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CTpLayerWnd::OnOK();
}

