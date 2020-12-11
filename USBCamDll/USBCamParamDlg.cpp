// USBCamParamDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USBCamParamDlg.h"
#include "afxdialogex.h"


// CUSBCamParamDlg �Ի���

IMPLEMENT_DYNAMIC(CUSBCamParamDlg, CTpLayerWnd)

CUSBCamParamDlg::CUSBCamParamDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CUSBCamParamDlg::IDD, pParent)
	, m_dUSBCamExposureValue(-2)
	, m_dUSBCamExposureValue_H(2)
	, m_dUSBCamExposureValue_L(-12)
	, m_bUSBCamBalance(FALSE)
	, m_nUSBCamFPS(0)
{

}

CUSBCamParamDlg::CUSBCamParamDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_dUSBCamExposureValue(-2)
	, m_dUSBCamExposureValue_H(2)
	, m_dUSBCamExposureValue_L(-12)
	, m_bUSBCamBalance(FALSE)
	, m_nUSBCamFPS(0)
{

}

CUSBCamParamDlg::~CUSBCamParamDlg()
{
}

void CUSBCamParamDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_BL_btUSBCamInfo, m_BL_btUSBCamInfo);
	DDX_Control(pDX, IDC_BL_slUSBCamExposureValue, m_BL_slExposureValue);
	DDX_Control(pDX, IDC_BL_swUSBCamBalance, m_BL_swUSBCamBalance);

	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUSBCamParamDlg, CTpLayerWnd)
	ON_REGISTERED_MESSAGE(gMsgUSBCamImgShow, &CUSBCamParamDlg::OnGmsgusbcamimgshow)
END_MESSAGE_MAP()


// CUSBCamParamDlg ��Ϣ�������


BOOL CUSBCamParamDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	SetTitle(_T("���C�O��"));

	GetDlgItem(IDC_USBCamParamImgShow)->GetWindowRect(m_rcImgShow);
	ScreenToClient(m_rcImgShow);

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}

void CUSBCamParamDlg::DrawElement(CDC * pDC, CRect rcDraw)
{
	if (!m_USBCamImgShow.empty())
	{
		m_USBCamImgShow.Draw2DC(pDC, m_rcImgShow);
	}
	
	CPen penDraw(PS_SOLID, 1, RGB(0, 255, 255));
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SelectObject(penDraw);
	pDC->Rectangle(m_rcImgShow);

}


BEGIN_EVENTSINK_MAP(CUSBCamParamDlg, CTpLayerWnd)
	ON_EVENT(CUSBCamParamDlg, IDC_BL_swUSBCamBalance, 1, CUSBCamParamDlg::StatusChangedBlswusbcambalance, VTS_BOOL)
	ON_EVENT(CUSBCamParamDlg, IDC_BL_slUSBCamExposureValue, 1, CUSBCamParamDlg::PosChangedBlslusbcamexposurevalue, VTS_I4)
END_EVENTSINK_MAP()


void CUSBCamParamDlg::StatusChangedBlswusbcambalance(BOOL bStatus)
{
	m_bUSBCamBalance = m_BL_swUSBCamBalance.GetStatus();
	m_pUSBCamParamDlg->PostMessage(gMsgUSBCamInfoChange, VALUE_CHANGE);
	// TODO: �ڴ˴������Ϣ����������
}


afx_msg LRESULT CUSBCamParamDlg::OnGmsgusbcamimgshow(WPARAM wParam, LPARAM lParam)
{
	InvalidateRect(m_rcImgShow, FALSE);

	CString strFPS;
	strFPS.Format(_T("%d"), m_nUSBCamFPS);

	((CBL_Edit *)(GetDlgItem(IDC_BL_edUSBCamFPS)))->SetValue(m_nUSBCamFPS);
	return 0;
}


void CUSBCamParamDlg::PosChangedBlslusbcamexposurevalue(long nNewPos)
{
	// TODO: �ڴ˴������Ϣ����������
	m_dUSBCamExposureValue = m_BL_slExposureValue.GetCurPos();
	m_pUSBCamParamDlg->PostMessage(gMsgUSBCamInfoChange, VALUE_CHANGE);
}


void CUSBCamParamDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_bUSBCamBalance = m_BL_swUSBCamBalance.GetStatus();
	m_dUSBCamExposureValue = m_BL_slExposureValue.GetCurPos();
	m_pUSBCamParamDlg->PostMessage(gMsgUSBCamInfoChange, BUTTON_OK);
	CTpLayerWnd::OnOK();
}


void CUSBCamParamDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pUSBCamParamDlg->PostMessage(gMsgUSBCamInfoChange, BUTTON_CANCEL);
	CTpLayerWnd::OnCancel();
}
