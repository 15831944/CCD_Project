// ParamCopy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParamCopy.h"
#include "afxdialogex.h"


// CParamCopy �Ի���

IMPLEMENT_DYNAMIC(CParamCopy, CTpLayerWnd)

CParamCopy::CParamCopy(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CParamCopy::IDD, pParent)
	, m_nMax(0)
	, m_nMax_SP(100)
{

}

CParamCopy::CParamCopy(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nMax(0)
	, m_nMax_SP(100)
{
}

CParamCopy::~CParamCopy()
{
}

void CParamCopy::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParamCopy, CTpLayerWnd)
END_MESSAGE_MAP()


// CParamCopy ��Ϣ�������
BEGIN_EVENTSINK_MAP(CParamCopy, CTpLayerWnd)
	ON_EVENT(CParamCopy, IDC_BL_ParamCopyPart, 1, CParamCopy::StatusChangedBlParamcopypart, VTS_BOOL)
	ON_EVENT(CParamCopy, IDC_BL_ParamCopyAll, 1, CParamCopy::StatusChangedBlParamcopyall, VTS_BOOL)
	ON_EVENT(CParamCopy, IDC_BL_ParamCopyPart_SP, 1, CParamCopy::StatusChangedBlParamcopypartSp, VTS_BOOL)
	ON_EVENT(CParamCopy, IDC_BL_ParamCopyAll_SP, 1, CParamCopy::StatusChangedBlParamcopyallSp, VTS_BOOL)
END_EVENTSINK_MAP()


void CParamCopy::StatusChangedBlParamcopypart(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!bNewStatus)
		return;

	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData)))->SetEnabled(bNewStatus);
	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll)))->SetSelect(!bNewStatus);
}


void CParamCopy::StatusChangedBlParamcopyall(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!bNewStatus)
		return;

	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData)))->SetEnabled(!bNewStatus);
	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart)))->SetSelect(!bNewStatus);
}

void CParamCopy::StatusChangedBlParamcopypartSp(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!bNewStatus)
		return;

	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData_SP)))->SetEnabled(bNewStatus);
	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll_SP)))->SetSelect(!bNewStatus);
}


void CParamCopy::StatusChangedBlParamcopyallSp(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!bNewStatus)
		return;

	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData_SP)))->SetEnabled(!bNewStatus);
	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart_SP)))->SetSelect(!bNewStatus);
}

BOOL CParamCopy::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart)))->SetSelect(TRUE);
	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData)))->SetEnabled(TRUE);

	m_nSelectType = PARAM_COPY_PART;//��ؐ��ʽ
	m_strParamCopyData = _T("");

	((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart_SP)))->SetSelect(TRUE);
	((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData_SP)))->SetEnabled(TRUE);

	m_nSelectType_SP = PARAM_COPY_PART;//��ؐ��ʽ
	m_strParamCopyData_SP = _T("");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CParamCopy::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CMsgBox MsgBox(this);

	if (((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart)))->GetSelect() && !((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll)))->GetSelect())//���ֿ�ؐ
	{
		const CString strInfo = ((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData)))->GetValueText();

		CString strErrInfo = _T("ݔ���e�`��\nݔ��ą����������������g�á�,����-�����_����1,2,3 �� 1-3 �ҡ�-��ֻ�ܳ��Fһ��\n��,���͡�-�����ܻ���");

		if (strInfo == _T(""))
		{
			MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
			return;
		}

		for (int j = 0; j < strInfo.GetLength(); j++)
		{
			if (((strInfo[j] < '0') || (strInfo[j] > '9')) && (strInfo[j] != '-') && (strInfo[j] != ','))
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}
		
		vector<CString> vstrTemp;
		CValueCalculate InfoCut;

		if (strInfo.Find(',') >= 0)
		{
			vstrTemp.clear();
			vstrTemp = InfoCut.CutStringElse(strInfo, ',');

			for (size_t k = 0; k < vstrTemp.size(); k++)
			{
				if ((_ttoi(vstrTemp[k]) < 1) || (vstrTemp[k] == _T("")) || (vstrTemp[0] == _T(",")) || (vstrTemp[vstrTemp.size() - 1] == _T(",")))
				{
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
				if (_ttoi(vstrTemp[k]) > m_nMax)
				{
					strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax);
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			if (strInfo.Find('-') >= 0)
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}

		else if (strInfo.Find('-') >= 0)
		{
			BOOL bFind = FALSE;
			vstrTemp.clear();
			vstrTemp = InfoCut.CutStringElse(strInfo, '-');

			for (size_t k = 0; k < vstrTemp.size(); k++)
			{
				if ((_ttoi(vstrTemp[k]) < 1) || (vstrTemp[k] == _T("")) || (vstrTemp[0] == _T("-")) || (vstrTemp[vstrTemp.size() - 1] == _T("-")))
				{
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
				if (_ttoi(vstrTemp[k]) > m_nMax)
				{
					strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax);
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			if (strInfo.Find(',') >= 0)
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
			for (int n = 0; n < strInfo.GetLength(); n++)
			{
				if (strInfo[n] == '-')
				{
					if (bFind)
					{
						MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
						return;
					}
					bFind = TRUE;
				}
			}
		}
		else
		{
			if (_ttoi(strInfo) > m_nMax)
			{
				strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax);
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}

		m_nSelectType = PARAM_COPY_PART;
		m_strParamCopyData = strInfo;
	}
	if (!((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart)))->GetSelect() && ((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll)))->GetSelect())//ȫ�ֿ�ؐ
	{
		m_nSelectType = PARAM_COPY_ALL;
	}


	if (((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart_SP)))->GetSelect() && !((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll_SP)))->GetSelect())//���ֿ�ؐ
	{
		const CString strInfo = ((CBL_Edit *)(GetDlgItem(IDC_BL_ParamCopyData_SP)))->GetValueText();

		CString strErrInfo = _T("ݔ���e�`��\nݔ��ą����������������g�á�,����-�����_����1,2,3 �� 1-3 �ҡ�-��ֻ�ܳ��Fһ��\n��,���͡�-�����ܻ���");

		if (strInfo == _T(""))
		{
			MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
			return;
		}

		for (int j = 0; j < strInfo.GetLength(); j++)
		{
			if (((strInfo[j] < '0') || (strInfo[j] > '9')) && (strInfo[j] != '-') && (strInfo[j] != ','))
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}

		vector<CString> vstrTemp;
		CValueCalculate InfoCut;

		if (strInfo.Find(',') >= 0)
		{
			vstrTemp.clear();
			vstrTemp = InfoCut.CutStringElse(strInfo, ',');

			for (size_t k = 0; k < vstrTemp.size(); k++)
			{
				if ((_ttoi(vstrTemp[k]) < 1) || (vstrTemp[k] == _T("")) || (vstrTemp[0] == _T(",")) || (vstrTemp[vstrTemp.size() - 1] == _T(",")))
				{
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
				if (_ttoi(vstrTemp[k]) > m_nMax_SP)
				{
					strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax_SP);
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			if (strInfo.Find('-') >= 0)
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}

		else if (strInfo.Find('-') >= 0)
		{
			BOOL bFind = FALSE;
			vstrTemp.clear();
			vstrTemp = InfoCut.CutStringElse(strInfo, '-');

			for (size_t k = 0; k < vstrTemp.size(); k++)
			{
				if ((_ttoi(vstrTemp[k]) < 1) || (vstrTemp[k] == _T("")) || (vstrTemp[0] == _T("-")) || (vstrTemp[vstrTemp.size() - 1] == _T("-")))
				{
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
				if (_ttoi(vstrTemp[k]) > m_nMax_SP)
				{
					strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax_SP);
					MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			if (strInfo.Find(',') >= 0)
			{
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
			for (int n = 0; n < strInfo.GetLength(); n++)
			{
				if (strInfo[n] == '-')
				{
					if (bFind)
					{
						MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
						return;
					}
					bFind = TRUE;
				}
			}
		}
		else
		{
			if (_ttoi(strInfo) > m_nMax_SP)
			{
				strErrInfo.Format(_T("ݔ���e�`���������ֵ\n���ֵ��%d"), m_nMax_SP);
				MsgBox.ShowMsg(strErrInfo, _T("ݔ���e�`"), MB_ICONERROR | MB_OK);
				return;
			}
		}

		m_nSelectType_SP = PARAM_COPY_PART;
		m_strParamCopyData_SP = strInfo;
	}
	if (!((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyPart_SP)))->GetSelect() && ((CBL_Radio *)(GetDlgItem(IDC_BL_ParamCopyAll_SP)))->GetSelect())//ȫ�ֿ�ؐ
	{
		m_nSelectType_SP = PARAM_COPY_ALL;
	}

	if (IDCANCEL == MsgBox.ShowMsg(_T("��ؐ��o����ԭ��\n�_�J��ؐ�D��̎���_����"), _T("��ʾ"), MB_ICONINFORMATION | MB_OKCANCEL))
		return;
	
	CTpLayerWnd::OnOK();
}



