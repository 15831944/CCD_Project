// VerisonManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VerisonManage.h"
#include "afxdialogex.h"


// CVerisonManage �Ի���

IMPLEMENT_DYNAMIC(CVerisonManage, CTpLayerWnd)

CVerisonManage::CVerisonManage(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CVerisonManage::IDD, pParent)
{

}

CVerisonManage::CVerisonManage(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CVerisonManage::~CVerisonManage()
{
}

void CVerisonManage::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_btVersion, m_BL_btVersion);
	DDX_Control(pDX, IDC_BL_UpdateInfoList, m_BL_ltUpdateInfo);
}


BEGIN_MESSAGE_MAP(CVerisonManage, CTpLayerWnd)
END_MESSAGE_MAP()


// CVerisonManage ��Ϣ�������
void CVerisonManage::_DefaultFocus(void)
{
	//m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}

void CVerisonManage::_ShowInfo()
{
	m_BL_ltUpdateInfo.DeleteAll(FALSE);

	m_BL_ltUpdateInfo.AppendColumn(_T("No."),DT_LEFT,30,FALSE);

	struct UpdateInfo
	{
		CString strUpdateDate;
		CString strUpdateInfo;
	};

	deque<UpdateInfo> deUpdateInfo;

	UpdateInfo UpdateInfoTemp;

	UpdateInfoTemp.strUpdateDate = _T("V1.6    �޸ĕr�g��2020��08��24��");
	UpdateInfoTemp.strUpdateInfo = _T("1.����IPQC�c�z����;2.�޸��ַ��z�y�Y�������w��ʽ;3.���Ӹ��yԇ�Y����ʼ�����a");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.6    �޸ĕr�g��2020��09��02��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�޸����½��n����δ�x��Ⱥ�M���o����Ӝyԇ�Ŀ;2.��Q�D��̎���_���Д�����O���Д���ܛ���������}");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.6    �޸ĕr�g��2020��09��23��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�޸��ᣬ��˿����ⷽ���L�u����;2.�����h�����И�ӛ����;3.��Q��������L�u��ɵĳ���������}");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.6    �޸ĕr�g��2020��12��08��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�ַ��и�D�񱣴���exe·���µ�Character�ļ��A;2.�s�p���a��");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.7    �޸ĕr�g��2020��12��14��");
	UpdateInfoTemp.strUpdateInfo = _T("1.��̖ݔ��ģʽ���Ԅәz�y�n������n��;2.��Ӳˆ��ܴa����");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.7    �޸ĕr�g��2020��12��16��");
	UpdateInfoTemp.strUpdateInfo = _T("1.��Q����ܛ��ÿ���_�C��У�����˵Ć��};2.ȡ���P�]ܛ���r�P�]��Դ����");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.7    �޸ĕr�g��2020��12��17��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�޸Ĵ������Q�r����ϵ�y�в�ԃ�Ƿ�����;2.�����D��̎���_���Ŀ�ؐ����");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V1.8    �޸ĕr�g��2020��12��21��");
	UpdateInfoTemp.strUpdateInfo = _T("1.����n����Ϣ�r����������̖ݔ��ģʽ���Ԅәz�y;2.�޸��˳�����BUG");
	deUpdateInfo.push_front(UpdateInfoTemp);

	CValueCalculate ValueCalculate;
	for (size_t i = 0; i < deUpdateInfo.size(); i++)
	{
		m_BL_ltUpdateInfo.AppendRow(TRUE);
		m_BL_ltUpdateInfo.SetItemText(m_BL_ltUpdateInfo.GetRows() - 1, 0, deUpdateInfo[i].strUpdateDate);
		m_BL_ltUpdateInfo.SetItemTextColor(m_BL_ltUpdateInfo.GetRows() - 1, 0, RGB(255, 155, 32));

		vector<CString> vstrTemp = ValueCalculate.CutStringElse(deUpdateInfo[i].strUpdateInfo, ';');

		for (size_t j = 0; j < vstrTemp.size(); j++)
		{
			m_BL_ltUpdateInfo.AppendRow(TRUE);
			
			m_BL_ltUpdateInfo.SetItemText(m_BL_ltUpdateInfo.GetRows() - 1, 0, _T("   ") + vstrTemp[j]);
			m_BL_ltUpdateInfo.SetItemTextColor(m_BL_ltUpdateInfo.GetRows() - 1, 0, RGB(0, 255, 230));
		}
	}
	m_BL_ltUpdateInfo.SelectRow(0);
}

