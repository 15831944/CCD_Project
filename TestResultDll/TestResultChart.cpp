// TestResultChart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestResultChart.h"
#include "afxdialogex.h"

int g_nColWidth = 0;

BOOL CTestResultChart::m_bSaveData = FALSE;
// CTestResultChart �Ի���

IMPLEMENT_DYNAMIC(CTestResultChart, CTpLayerWnd)

CTestResultChart::CTestResultChart(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CTestResultChart::IDD, pParent)
	, m_nScreenPhysicsWidth(0)
	, m_nScreenPhysicsHeight(0)
	, m_nScreenPixelWidth(0)
	, m_nScreenPixelHeight(0)
	, m_nDisplayFrequency(0)
	, m_nScreenPixelWidthNoTask(0)
	, m_nScreenPixelHeightNoTask(0)
	, m_fValueMax(300)
	, m_nCurRow(-1)
	, m_nTestGroup(-1)
	, m_nTestProject(-1)
{
	m_vvfShowData.resize(DATA_SUM);
	for (size_t i = 0; i < DATA_SUM; i++)
	{
		m_vvfShowData[i].resize(24);
		for (int j = 0; j < 24; j++)
		{
			m_vvfShowData[i][j] = 0;
		}
	}
}

CTestResultChart::CTestResultChart(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nScreenPhysicsWidth(0)
	, m_nScreenPhysicsHeight(0)
	, m_nScreenPixelWidth(0)
	, m_nScreenPixelHeight(0)
	, m_nDisplayFrequency(0)
	, m_nScreenPixelWidthNoTask(0)
	, m_nScreenPixelHeightNoTask(0)
	, m_fValueMax(300)
	, m_nCurRow(-1)
	, m_nTestGroup(-1)
	, m_nTestProject(-1)
{
	m_vvfShowData.resize(DATA_SUM);
	for (size_t i = 0; i < DATA_SUM; i++)
	{
		m_vvfShowData[i].resize(24);
		for (int j = 0; j < 24; j++)
		{
			m_vvfShowData[i][j] = 0;
		}
	}
}



CTestResultChart::~CTestResultChart()
{
}

void CTestResultChart::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ltTestResult_AM, m_BL_ltTestResult_AM);
}


BEGIN_MESSAGE_MAP(CTestResultChart, CTpLayerWnd)
	ON_REGISTERED_MESSAGE(gMsgTestDataUpdate, &CTestResultChart::OnGmsgTestDataUpdate)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTestResultChart ��Ϣ�������
BOOL CTestResultChart::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_BtBaseOk.ShowWindow(FALSE);
	m_BtBaseCancel.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestResultChart::_UpdateUI()
{
	CRect rcClient;
	GetClientRect(rcClient);


	m_BL_ltTestResult_AM.SetHeaderHeight(35);
	m_BL_ltTestResult_AM.SetHeaderBkColor(RGB(45, 50, 55));
	
	m_BL_ltTestResult_AM.MoveWindow(25, 40, rcClient.Width() - 50, int(rcClient.Height() * 0.3));

	m_rcDraw.TopLeft().x = 0;
	m_rcDraw.TopLeft().y = int(rcClient.Height() * 0.3) + 40;
	m_rcDraw.BottomRight() = rcClient.BottomRight();

	m_BL_ltTestResult_AM.GetClientRect(rcClient);

	m_BL_ltTestResult_AM.AppendColumn(_T("�������Q"), DT_CENTER, 100, FALSE);
	g_nColWidth = int(((double)rcClient.Width() - 100 - 40) / 24);

	for (int i = 0; i < 24; i++)
	{
		CString strTemp;
		strTemp.Format(_T("%d-%d"), i, i+1);
		m_BL_ltTestResult_AM.AppendColumn(strTemp, DT_CENTER, g_nColWidth, FALSE);
		m_BL_ltTestResult_AM.SetColumnReadOnly(i + 1, TRUE);
	}
	m_BL_ltTestResult_AM.AppendColumn(_T("�@ʾ"), DT_CENTER, 40, FALSE);
	m_BL_ltTestResult_AM.SetColumnReadOnly(25, TRUE);

	for (int i = 0; i < 4; i++)
	{
		m_BL_ltTestResult_AM.AppendRow(TRUE);
		switch (i)
		{
		case 0:
			m_BL_ltTestResult_AM.SetItemReadOnly(i, 0, TRUE);
			m_BL_ltTestResult_AM.SetItemText(i, 0, _T("�yԇ����"));
			m_BL_ltTestResult_AM.SetItemTextColor(i, 25, RGB(255,255,255));
			break;
		case 1:
			m_BL_ltTestResult_AM.SetItemReadOnly(1, 0, TRUE);
			m_BL_ltTestResult_AM.SetItemText(1, 0, _T("��Ʒ����"));
			m_BL_ltTestResult_AM.SetItemTextColor(1, 25, RGB(0,255,0));
			break;
		case 2:
			m_BL_ltTestResult_AM.SetItemReadOnly(2, 0, TRUE);
			m_BL_ltTestResult_AM.SetItemText(2, 0, _T("��������"));
			m_BL_ltTestResult_AM.SetItemTextColor(2, 25, RGB(255,0,0));
			break;
		case 3:
			m_BL_ltTestResult_AM.SetItemReadOnly(3, 0, TRUE);
			m_BL_ltTestResult_AM.SetItemText(3, 0, _T("��λʧ������"));
			m_BL_ltTestResult_AM.SetItemTextColor(3, 25, RGB(0,0,0));
			break;
		default:
			break;
		}
	}
}

void CTestResultChart::DrawElement(CDC * pDC, CRect rcDraw)
{
 	CRect rcClient;
 	GetClientRect(rcClient);
 
 	CRect rcList;
 
 	m_BL_ltTestResult_AM.GetClientRect(rcList);
 
 	int nPenSize = 2; 
 
 
 	CPen pen_Axis(PS_SOLID, nPenSize, RGB(0,255,230));
 
 	pDC->SelectStockObject(NULL_BRUSH);
 	pDC->SelectObject(pen_Axis);
 
 
 	const int nAxisWidth  = g_nColWidth * 24;
 
 	pDC->MoveTo(rcList.left + 100 + 30, rcClient.Height() - 40);
 	pDC->LineTo(rcList.left + 100 + 30 + g_nColWidth * 24 + 15, rcClient.Height() - 40);
 
 	pDC->MoveTo(rcList.left + 100 + 30 + g_nColWidth * 24 + 15, rcClient.Height() - 40);
 	pDC->LineTo(rcList.left + 100 + 30 + g_nColWidth * 24 + 15 - 6, rcClient.Height() - 40 - 6);
 
 	pDC->MoveTo(rcList.left + 100 + 30 + g_nColWidth * 24 + 15, rcClient.Height() - 40);
 	pDC->LineTo(rcList.left + 100 + 30 + g_nColWidth * 24 + 15 - 6, rcClient.Height() - 40 + 6);
 
 
 
 	pDC->MoveTo(rcList.left + 100 + 30, rcClient.Height() - 40);
 	pDC->LineTo(rcList.left + 100 + 30, 40 + rcList.Height() + 30);
 
 	pDC->MoveTo(rcList.left + 100 + 30, 40 + rcList.Height() + 30);
 	pDC->LineTo(rcList.left + 100 + 30 - 6, 40 + rcList.Height() + 30 + 6);
 
 	pDC->MoveTo(rcList.left + 100 + 30, 40 + rcList.Height() + 30);
 	pDC->LineTo(rcList.left + 100 + 30 + 6, 40 + rcList.Height() + 30 + 6);
 
 	CRect rcText;
 	static CFont fontGrade;
	static CFont fontGradeMin;
 	CString strText;
 	static BOOL bFontCreate = FALSE;


 
 	if (!bFontCreate)
 	{
 		fontGrade.CreatePointFont(120, L"Tahoma");
		fontGradeMin.CreatePointFont(90, L"Tahoma");
 		bFontCreate = TRUE;
 	}
 
 	for (int i = 0; i < 25; i++)
 	{
 		pDC->SelectObject(fontGrade);
 		pDC->SetTextColor(RGB(0,255,230));
 		strText.Format(_T("%d"), i);
 
 		if (i > 0)
 		{
 			pDC->MoveTo(rcList.left + 100 + 30 + i * g_nColWidth, rcClient.Height() - 40);
 			pDC->LineTo(rcList.left + 100 + 30 + i * g_nColWidth, rcClient.Height() - 40 - 5);
 		}
 
 		rcText.TopLeft().x = rcList.left + 100 + 30 + i * g_nColWidth - 10;
 		rcText.TopLeft().y = rcClient.Height() - 40 + 3;
 		rcText.BottomRight().x = rcList.left + 100 + 30 + i * g_nColWidth + 15;
 		rcText.BottomRight().y = rcClient.Height() - 40 + 30;
 
 		if (i < 10)
 		{
 			rcText.TopLeft().x = rcList.left + 100 + 30 + i * g_nColWidth - 6;
 			rcText.BottomRight().x = rcList.left + 100 + 30 + i * g_nColWidth + 15;
 		}
 
 		pDC->DrawText(strText, &rcText, DT_EDITCONTROL|DT_LEFT|DT_NOPREFIX);
 		
 	}
 
 	//���±����ݣ��ҵ����ֵ
 	CONST int nShowSum = m_BL_ltTestResult_AM.GetRows() > DATA_SUM ? DATA_SUM : m_BL_ltTestResult_AM.GetRows();
 
 	m_fValueMax = 0;
 
 	for (int i = 0; i < nShowSum; i++)
 	{
 		for (int j = 1; j < 25; j++)
 		{
 			CString strTemp;
 			m_fValueMax = m_vvfShowData[i][j - 1] > m_fValueMax ? m_vvfShowData[i][j - 1] : m_fValueMax;
 			strTemp.Format(_T("%.1f"), m_vvfShowData[i][j - 1]);
 			m_BL_ltTestResult_AM.SetItemFloatNumber(i, j, TRUE);
 			m_BL_ltTestResult_AM.SetItemText(i, j, strTemp);
 		}
 	}
 	
 	//�L�u�v�S
 	int nValueMax = 0;
 	const int nAxisHeight = rcClient.Height() - 40 - (40 + rcList.Height() + 10) - 40;
 	for (int i = 1; i < 6; i++)
 	{
 		pDC->SelectObject(fontGrade);
 		pDC->SetTextColor(RGB(0,255,230));
 		for (int j = 1; j < 1000; j++)
 		{
 			if (m_fValueMax <= 200 * j)
 			{
 				nValueMax = 200 * j;
 				break;
 			}
 		}
 
 		pDC->MoveTo(rcList.left + 100 + 30, rcClient.Height() - 40 - i * (nAxisHeight / 5));
 		pDC->LineTo(rcList.left + 100 + 30 + 5, rcClient.Height() - 40 - i * (nAxisHeight / 5));
 
 
 		strText.Format(_T("%d"), i * nValueMax / 5);
 		rcText.TopLeft().x = rcList.left + 100 + 30 - 100;
 		rcText.TopLeft().y = rcClient.Height() - 40 - i * (int)(nAxisHeight / 5) - 15;
 		rcText.BottomRight().x = rcList.left + 100 + 30 - 5;
 		rcText.BottomRight().y = rcClient.Height() - 40 - i * (int)(nAxisHeight / 5) + 15;
 		pDC->DrawText(strText, &rcText, DT_EDITCONTROL|DT_RIGHT|DT_NOPREFIX);
 
 	}
 
 	//�L�u�c���D
	vector<CRect> vrcData;//��������
	vector<float> vfData;

 	for (int i = 0; i < nShowSum; i++)
 	{
 		if (m_BL_ltTestResult_AM.GetItemText(i, 25) == _T(""))
 		continue;
 
 		COLORREF color = m_BL_ltTestResult_AM.GetItemTextColor(i, 25);
 
 		nPenSize = 1;
 
 		if (i == m_nCurRow)
 		{
 			nPenSize = 3;
 		}
 		CPen penDraw(PS_SOLID, nPenSize, color);
 		CBrush brDraw(color);
 
 		pDC->SelectObject(penDraw);
 		int nStar = -1, nEnd = -1;
 		for (int j = 0; j < 24; j++)
 		{
 			if (m_vvfShowData[i][j] != 0)
 			{
 				nStar = j;
 				break;
 			}
 		}
 		for (int j = 23; j >= 0; j--)
 		{
 			if (m_vvfShowData[i][j] != 0)
 			{
 				nEnd = j;
 				break;
 			}
 		}
 		if (nStar >= 0)
 		{
 			CPoint ptDraw;
 			ptDraw.x = rcList.left + 100 + 30 + (int)((nStar + 0.5) * g_nColWidth);
 			ptDraw.y = rcClient.Height() - 40 - (int)(nAxisHeight *  m_vvfShowData[i][nStar] / nValueMax);
 			pDC->MoveTo(ptDraw);
 
 			pDC->SelectObject(brDraw);
 			const int nLength = 3;

			const CRect rcStar(ptDraw.x - nLength, ptDraw.y - nLength, ptDraw.x + nLength, ptDraw.y + nLength);
 			pDC->Rectangle(rcStar);
			vrcData.push_back(rcStar);
			vfData.push_back(m_vvfShowData[i][nStar]);

 			pDC->SelectStockObject(NULL_BRUSH);
 
 			if (nStar != nEnd)
 			{
 				for (int j = nStar + 1; j <= nEnd; j++)
 				{
 					ptDraw.x = rcList.left + 100 + 30 + (int)((j + 0.5) * g_nColWidth);
 					ptDraw.y = rcClient.Height() - 40 - (int)(nAxisHeight *  m_vvfShowData[i][j] / nValueMax);
 					pDC->LineTo(ptDraw);
 
 					pDC->SelectObject(brDraw);

					const CRect rcData(ptDraw.x - nLength, ptDraw.y - nLength, ptDraw.x + nLength, ptDraw.y + nLength);
 					pDC->Rectangle(rcData);
					vrcData.push_back(rcData);
					vfData.push_back(m_vvfShowData[i][j]);

 					pDC->SelectStockObject(NULL_BRUSH);
 				}
 			}
 		}
 	}

	if (vrcData.size() == vfData.size())
	{
		for (size_t i = 0; i < vrcData.size(); i++)
		{
			if (vrcData[i].PtInRect(m_ptMouse))
			{
				pDC->SelectObject(fontGradeMin);
				pDC->SetTextColor(RGB(255,255,255));
				strText.Format(_T("%.1f"), vfData[i]);

				rcText.TopLeft().x = vrcData[i].right + 5;
				rcText.TopLeft().y = vrcData[i].TopLeft().y - 5;
				rcText.BottomRight().x = rcText.TopLeft().x + 100;
				rcText.BottomRight().y = rcText.TopLeft().y + 50;
				pDC->DrawText(strText, &rcText, DT_EDITCONTROL|DT_LEFT|DT_NOPREFIX);
				break;
			}
		}
	}
}


void CTestResultChart::_GetDisplayScreenInfo()
{
	// ��ȡ�@ʾ������ߴ�
	HDC hdcScreen = ::GetDC(NULL);   
	m_nScreenPhysicsWidth = ::GetDeviceCaps(hdcScreen, HORZSIZE);
	m_nScreenPhysicsHeight = ::GetDeviceCaps(hdcScreen, VERTSIZE);
	::ReleaseDC(NULL, hdcScreen);

	// ��ȡ��ǰ���سߴ��ˢ��Ƶ��
	DEVMODE   dm;
	dm.dmSize = sizeof(DEVMODE);
	::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

	m_nScreenPixelWidth = dm.dmPelsWidth;
	m_nScreenPixelHeight = dm.dmPelsHeight;
	m_nDisplayFrequency = dm.dmDisplayFrequency;

	// 1in(Ӣ��) = 25.4mm(����)
	const double MILLIMETRE_2_INCH = 1 / 25.4;
	// ����Խ��߳���
	double diagonalLen = sqrt(m_nScreenPhysicsWidth * m_nScreenPhysicsWidth + m_nScreenPhysicsHeight * m_nScreenPhysicsHeight);
	//printf("��Ļ�Խ��߳�Ϊ��%.2lf mm, Լ %.2lf in.\n", diagonalLen, diagonalLen * MILLIMETRE_2_INCH);

	RECT rc;  
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &rc, 0);  

	m_nScreenPixelWidthNoTask = rc.right-rc.left;
	m_nScreenPixelHeightNoTask = rc.bottom-rc.top;

}
BEGIN_EVENTSINK_MAP(CTestResultChart, CTpLayerWnd)
	ON_EVENT(CTestResultChart, IDC_BL_ltTestResult_AM, 2, CTestResultChart::ItemChangedBllttestresultAm, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CTestResultChart, IDC_BL_ltTestResult_AM, 5, CTestResultChart::LBtDbClickBllttestresultAm, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CTestResultChart, IDC_BL_ltTestResult_AM, 1, CTestResultChart::RowsChangedBllttestresultAm, VTS_I4 VTS_I4 VTS_BOOL)
	ON_EVENT(CTestResultChart, IDC_BL_ltTestResult_AM, 4, CTestResultChart::SelectChangedBllttestresultAm, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CTestResultChart::ItemChangedBllttestresultAm(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	for (int i = 0; i < m_BL_ltTestResult_AM.GetRows(); i++)
	{
		for (int j = 1; j < 25; j++)
		{
			m_vvfShowData[i][j - 1] = _ttof(m_BL_ltTestResult_AM.GetItemText(i, j));
		}
	}

	InvalidateRect(m_rcDraw, FALSE);
}


void CTestResultChart::LBtDbClickBllttestresultAm(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	if (nCol == 25)
	{
		if (nFlags & MK_CONTROL)
		{
			COLORREF color = RGB(255, 0, 0);      // ��ɫ�Ի���ĳ�ʼ��ɫΪ��ɫ  
			CColorDialog colorDlg(color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ   

			if (IDOK == colorDlg.DoModal())       // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����   
			{   
				color = colorDlg.GetColor();      // ��ȡ��ɫ�Ի�����ѡ�����ɫֵ   
				long nCol_R = GetRValue(color);
				long nCol_G = GetGValue(color);
				long nCol_B = GetBValue(color);

				m_BL_ltTestResult_AM.SetItemTextColor(nRow, nCol, color);

				if (m_BL_ltTestResult_AM.GetItemText(nRow, nCol) != _T(""))
				{
					InvalidateRect(m_rcDraw, FALSE);
				}
			}   
		}
		else
		{
			if (m_BL_ltTestResult_AM.GetItemText(nRow, nCol) == _T(""))
			{
				m_BL_ltTestResult_AM.SetItemText(nRow, nCol, _T("��"));
			}
			else
			{
				m_BL_ltTestResult_AM.SetItemText(nRow, nCol, _T(""));
			}
			InvalidateRect(m_rcDraw, FALSE);
		}
		
	}
}


void CTestResultChart::RowsChangedBllttestresultAm(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: �ڴ˴������Ϣ����������
	//�Д��l��׃�������Mͬ��׃��

	if (nOldRows > nNewRows)//�h����
	{
		const int nDeletRow = m_nCurRow;//�h����̖
		m_vvfShowData.erase(m_vvfShowData.begin() + nDeletRow);


		vector<float> vnTemp;
		vnTemp.resize(24);
		for (size_t i = 0; i < 24; i++)
		{
			vnTemp[i] = 0;
		}
		m_vvfShowData.push_back(vnTemp);
		m_nCurRow = m_BL_ltTestResult_AM.GetCurRow();
	}
	else//�����
	{
		m_nCurRow = m_BL_ltTestResult_AM.GetCurRow();
		if (m_nCurRow != m_BL_ltTestResult_AM.GetRows() - 1)//������
		{
			vector<float> vnTemp;
			vnTemp.resize(24);
			for (size_t i = 0; i < 24; i++)
			{
				vnTemp[i] = 0;
			}
			m_vvfShowData.insert(m_vvfShowData.begin() + m_nCurRow, vnTemp);
			m_vvfShowData.pop_back();
		}
	}
	
	InvalidateRect(m_rcDraw, FALSE);
}


void CTestResultChart::SelectChangedBllttestresultAm(long nOldSels, long nNewSels)
{
	// TODO: �ڴ˴������Ϣ����������
	m_nCurRow = m_BL_ltTestResult_AM.GetCurRow();

	InvalidateRect(m_rcDraw, FALSE);
	
}


afx_msg LRESULT CTestResultChart::OnGmsgTestDataUpdate(WPARAM wParam, LPARAM lParam)
{
	SYSTEMTIME st = {0};
	GetLocalTime(&st);
	const int nHour = st.wHour;
	m_vvfShowData[wParam][nHour] += lParam;

	InvalidateRect(m_rcDraw, FALSE);
	return 0;
}


void CTestResultChart::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptMouse = point;
	InvalidateRect(m_rcDraw, FALSE);
	CTpLayerWnd::OnMouseMove(nFlags, point);
}



void CTestResultChart::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		if (m_nTestGroup != -1 && m_nTestProject != -1 && m_bSaveData)
		{
			CString strYear;
			CString strMouth;
			CString strDay;
			CString strHour;
			CString strMinute;
			CString strSeconds;

			_GetSystemTime(strYear, strMouth, strDay, strHour, strMinute, strSeconds);

			CString strTemp;
			strTemp.Format(_T("G%d - T%d"), m_nTestGroup + 1, m_nTestProject + 1);

			CString strPath;
			strPath = m_strExePath + _T("\\Data\\") + strYear + strMouth + strDay + _T("_") + strTemp + _T(".data");

			CFile file;
			CFileException FileEX;
			if (!file.Open(strPath,CFile::modeWrite| CFile::modeCreate,&FileEX))
			{
				FileEX.ReportError();
				SetTimer(0, DATA_CYCLE, nullptr);
				return;
			}	
			CArchive ar(&file,CArchive::store);
			Serialize(ar);
			ar.Flush();
			ar.Close();
 			file.Close();
		}
			
		SetTimer(0, DATA_CYCLE, nullptr);
		break;
	default:
		break;
	}
	CTpLayerWnd::OnTimer(nIDEvent);
}

void CTestResultChart::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_ltTestResult_AM.GetRows();
		for (int i = 0; i < m_BL_ltTestResult_AM.GetRows(); i++)
		{
			ar << m_BL_ltTestResult_AM.GetItemText(i, 0);
			ar << m_BL_ltTestResult_AM.GetItemText(i, m_BL_ltTestResult_AM.GetColumns() - 1);
		}

		for (size_t i = 0; i < DATA_SUM; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				ar << m_vvfShowData[i][j];
			}
		}

	}
	else
	{	// loading code
		for (int i = m_BL_ltTestResult_AM.GetRows() - 1; i >= 0 ; i--)
		{
			m_BL_ltTestResult_AM.DeleteRow(i, TRUE);
		}
		int nAr = 0;
		CString strAr;
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_ltTestResult_AM.AppendRow(TRUE);

			switch (i)
			{
			case 0:
				m_BL_ltTestResult_AM.SetItemReadOnly(i, 0, TRUE);
				m_BL_ltTestResult_AM.SetItemText(i, 0, _T("�yԇ����"));
				m_BL_ltTestResult_AM.SetItemTextColor(i, 25, RGB(255,255,255));
				break;
			case 1:
				m_BL_ltTestResult_AM.SetItemReadOnly(1, 0, TRUE);
				m_BL_ltTestResult_AM.SetItemText(1, 0, _T("��Ʒ����"));
				m_BL_ltTestResult_AM.SetItemTextColor(1, 25, RGB(0,255,0));
				break;
			case 2:
				m_BL_ltTestResult_AM.SetItemReadOnly(2, 0, TRUE);
				m_BL_ltTestResult_AM.SetItemText(2, 0, _T("��������"));
				m_BL_ltTestResult_AM.SetItemTextColor(2, 25, RGB(255,0,0));
				break;
			case 3:
				m_BL_ltTestResult_AM.SetItemReadOnly(3, 0, TRUE);
				m_BL_ltTestResult_AM.SetItemText(3, 0, _T("��λʧ������"));
				m_BL_ltTestResult_AM.SetItemTextColor(3, 25, RGB(0,0,0));
				break;
			default:
				break;
			}
			
			ar >> strAr;
			m_BL_ltTestResult_AM.SetItemText(i, 0, strAr);
			ar >> strAr;
			m_BL_ltTestResult_AM.SetItemText(i, m_BL_ltTestResult_AM.GetColumns() - 1, strAr);
		}

		for (size_t i = 0; i < DATA_SUM; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				ar >> m_vvfShowData[i][j];
			}
		}
	}
}

void CTestResultChart::_GetSystemTime(CString & strYear, CString & strMouth, CString & strDay, CString & strHour, CString & strMinute, CString & strSeconds)
{
	CTime time = CTime::GetCurrentTime(); ///����CTime����  
	const int nYear = time.GetYear(); ///��  
	const int nMonth = time.GetMonth(); ///��  
	const int nDay = time.GetDay(); ///�� 
	const int nHour = time.GetHour();
	const int nMin = time.GetMinute();
	const int nSec = time.GetSecond();

	strYear.Format(_T("%d"), nYear);
	strMouth.Format(_T("%d"), nMonth);
	strDay.Format(_T("%d"), nDay);
	strHour.Format(_T("%d"), nHour);
	strMinute.Format(_T("%d"), nMin);
	strSeconds.Format(_T("%d"), nSec);

	while (strMouth.GetLength() < 2)
	{
		strMouth.Insert(0, '0');
	}

	while (strDay.GetLength() < 2)
	{
		strDay.Insert(0, '0');
	}
	while (strHour.GetLength() < 2)
	{
		strHour.Insert(0, '0');
	}
	while (strMinute.GetLength() < 2)
	{
		strMinute.Insert(0, '0');
	}
	while (strMinute.GetLength() < 2)
	{
		strMinute.Insert(0, '0');
	}
	while (strSeconds.GetLength() < 2)
	{
		strSeconds.Insert(0, '0');
	}

}

void CTestResultChart::_LoadData()
{
	CString strYear;
	CString strMouth;
	CString strDay;
	CString strHour;
	CString strMinute;
	CString strSeconds;

	_GetSystemTime(strYear, strMouth, strDay, strHour, strMinute, strSeconds);

	CString strTemp;
	strTemp.Format(_T("G%d - T%d"), m_nTestGroup + 1, m_nTestProject + 1);

	CString strPath;
	strPath = m_strExePath + _T("\\Data\\") + strYear + strMouth + strDay + _T("_") + strTemp + _T(".data");


	if (!PathFileExists(strPath))
	{
		SetTimer(0, DATA_CYCLE, nullptr);
		return;
	}

	CFile file;
	CFileException FileEx;

	if (!file.Open(strPath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();
		return ;
	}
	CArchive ar(&file, CArchive::load);

	Serialize(ar);
	ar.Flush();
	ar.Close();
	file.Close();

	InvalidateRect(m_rcDraw, FALSE);

	SetTimer(0, DATA_CYCLE, nullptr);
}