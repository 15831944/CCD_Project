// MLTrain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MLTrain.h"
#include "afxdialogex.h"


// CMLTrain �Ի���

IMPLEMENT_DYNAMIC(CMLTrain, CTpLayerWnd)

CMLTrain::CMLTrain(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CMLTrain::IDD, pParent)
	, m_nTrainMethod(0)
	, m_nSampleChnnel(0)
{

}

CMLTrain::CMLTrain(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nTrainMethod(0)
	, m_nSampleChnnel(0)
{
}


CMLTrain::~CMLTrain()
{
}

void CMLTrain::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ltSampleInfo, m_BL_ltSampleInfo);
}


BEGIN_MESSAGE_MAP(CMLTrain, CTpLayerWnd)
END_MESSAGE_MAP()


// CMLTrain ��Ϣ�������


BOOL CMLTrain::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BtBaseOk.ShowWindow(FALSE);
	m_BtBaseCancel.ShowWindow(FALSE);

	SetTitle(_T("�C���W��"));

	_NewSampleInfoList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_EVENTSINK_MAP(CMLTrain, CTpLayerWnd)
	ON_EVENT(CMLTrain, IDC_BL_dpMLMethod, 3, CMLTrain::SelectChangedBldpmlmethod, VTS_BSTR VTS_BSTR VTS_I2)
	ON_EVENT(CMLTrain, IDC_BL_dpMLImgChannel, 3, CMLTrain::SelectChangedBldpmlimgchannel, VTS_BSTR VTS_BSTR VTS_I2)
	ON_EVENT(CMLTrain, IDC_BL_btGetSamplePath, 1, CMLTrain::LBtClickedBlbtgetsamplepath, VTS_I4)
	ON_EVENT(CMLTrain, IDC_BL_btMMLTrain, 1, CMLTrain::LBtClickedBlbtmmltrain, VTS_I4)
END_EVENTSINK_MAP()


void CMLTrain::SelectChangedBldpmlmethod(LPCTSTR strOld, LPCTSTR strNew, short nPos)
{
	// TODO: �ڴ˴������Ϣ����������
	const CString strInfo = strNew;
	if (strInfo == _T("SVM"))
		{m_nTrainMethod = TRAIN_SVM;}
}


void CMLTrain::SelectChangedBldpmlimgchannel(LPCTSTR strOld, LPCTSTR strNew, short nPos)
{
	// TODO: �ڴ˴������Ϣ����������
	const CString strInfo = strNew;
	m_nSampleChnnel = strInfo == _T("�ҶȈD��") ? IMG_GRAY : IMG_RGB;
}


void CMLTrain::LBtClickedBlbtgetsamplepath(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);

	USES_CONVERSION;
	const CString strDir = ((CBL_Edit *)(GetDlgItem(IDC_BL_edSampleDir)))->GetValueText();

	if (!PathIsDirectory(strDir))
	{
		MsgBox.ShowMsg(_T("�ӱ�Ŀ��e�`���o���@ȡ�ӱ���Ϣ��"), _T("�@ȡʧ��"), MB_ICONERROR | MB_OK);
		return;
	}
	
	int nDirCounter = 0;
	int nFileCounter = 0;
	deque<CString> dstrDirName;
	CFileFind  find;
	SetCurrentDirectory(strDir);//���õ�ǰĿ¼
	BOOL ret = find.FindFile();
	while (ret)
	{
		ret = find.FindNextFile();
		if (find.IsDots())
			continue;
		else if (find.IsDirectory())//�ж���Ŀ¼
		{
			nDirCounter++;
			dstrDirName.push_back(find.GetFileName());
		}
		else nFileCounter++;//�ļ�������
	}find.Close();//�ر�find
	SetCurrentDirectory(_T("L:\\"));//�ú�����ռ���ļ�����Ȩ��Ϊ�����ͻӦ��������Ϊ�޹�Ŀ¼

	m_BL_ltSampleInfo.DeleteAll(FALSE);

	_NewSampleInfoList();

	while (dstrDirName.size())
	{
		m_BL_ltSampleInfo.AppendRow(TRUE);
		m_BL_ltSampleInfo.SetItemText(m_BL_ltSampleInfo.GetRows() - 1, 1, strDir + _T("\\") + dstrDirName[0]);
		char chTemp = dstrDirName[0][dstrDirName[0].GetLength() - 1];
		CString strTemp;
		strTemp += chTemp;
		//char a = strTemp[0];
		m_BL_ltSampleInfo.SetItemText(m_BL_ltSampleInfo.GetRows() - 1, 2, strTemp);
		dstrDirName.pop_front();
	}
}


void CMLTrain::_NewSampleInfoList()
{
	if (!m_BL_ltSampleInfo.GetColumns())
	{
		m_BL_ltSampleInfo.AppendColumn(_T("No."),DT_CENTER,30,FALSE);
		m_BL_ltSampleInfo.AppendColumn(_T("�ӱ�·��"),DT_CENTER,480,FALSE);
		m_BL_ltSampleInfo.AppendColumn(_T("�ӱ��˻`"),DT_CENTER,90,FALSE);
	}
}

void CMLTrain::LBtClickedBlbtmmltrain(long nFlags)
{
	USES_CONVERSION;

	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);

	vector<CString> vstrPath;
	vector<int> vnLable;
	set<CString> sstrPath;
	set<int> snLable;
	for (int i = 0; i < m_BL_ltSampleInfo.GetRows(); i++)
	{
		const CString strPath = m_BL_ltSampleInfo.GetItemText(i, 1);
		const CString strLable = m_BL_ltSampleInfo.GetItemText(i, 2);

		if(!PathIsDirectory(strPath))
		{
			m_BL_ltSampleInfo.SelectRow(i);
			MsgBox.ShowMsg(_T("�ӱ�·���e�`��"), _T("Ӗ���e�`"), MB_ICONERROR | MB_OK);
			return;
		}
		if(strLable.GetLength() != 1 || strLable[0] < 0 || strLable[0] > 255)
		{
			m_BL_ltSampleInfo.SelectRow(i);
			MsgBox.ShowMsg(_T("�˻`�e�`���˻`����ǆ΂��ַ��Ҟ�ASCii�ַ���"), _T("Ӗ���e�`"), MB_ICONERROR | MB_OK);
			return;
		}

		vstrPath.push_back(strPath);
		vnLable.push_back(strLable[0]);
		sstrPath.insert(strPath);
		snLable.insert(strLable[0]);
	}
	if (vstrPath.size() != sstrPath.size() || vnLable.size() != snLable.size() || (int)sstrPath.size() != m_BL_ltSampleInfo.GetRows())
	{
		MsgBox.ShowMsg(_T("�����x�ӱ�·�������}�˻`��"), _T("Ӗ���e�`"), MB_ICONERROR | MB_OK);
		return;
	}
	if (vstrPath.size() < 2)
	{
		MsgBox.ShowMsg(_T("�W���ӱ��������횴��1��"), _T("Ӗ���e�`"), MB_ICONERROR | MB_OK);
		return;
	}
	if (m_nTrainMethod == 0 || m_nSampleChnnel == 0)
	{
		MsgBox.ShowMsg(_T("δ�O��Ӗ����ʽ��D��ͨ����"), _T("Ӗ���e�`"), MB_ICONERROR | MB_OK);
		return;
	}

	switch (m_nTrainMethod)
	{
	case TRAIN_SVM:
		{
			CSVMTrainModel Train_SVM;
			int nErrCode = 0;
			const BOOL bTrainRes = Train_SVM.SVMTrain(vstrPath, vnLable, m_nSampleChnnel, nErrCode);
			if (!bTrainRes)
			{
				switch (nErrCode)
				{
				case IMG_CHANNEL_ERR:
					MsgBox.ShowMsg(_T("Ӗ��ʧ�������ژӱ��D��ͨ���c�O�ò�����"), _T("Ӗ��ʧ��"), MB_ICONERROR | MB_OK);
					return;
					break;
				default:
					break;
				}
			}
			MsgBox.ShowMsg(_T("Ӗ����ɣ�Ո����Ӗ��ģ�ͣ�"), _T("Ӗ�����"), MB_ICONINFORMATION | MB_OK);

			CString strSavePath;
			CFileDialog dlgFile(FALSE, _T("*xml"), _T("�o���}"), OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
				_T("Outlook Files(*.xml)|*.xml|All Files(*.*)|*.*||"), this);

			dlgFile.m_pOFN->lpstrTitle = _T("�ļ�����");

			if (IDOK == dlgFile.DoModal())
			{
				strSavePath = dlgFile.GetPathName();
			}
			else
			{
				MsgBox.ShowMsg(_T("�ŗ�����Ӗ��ģ�ͣ�"), _T("Ӗ�����"), MB_ICONINFORMATION | MB_OK);
				return ;
			}

			Train_SVM.m_svmTrain.save(W2A(strSavePath));
		}
		break;
	default:
		break;
	}
	


}
