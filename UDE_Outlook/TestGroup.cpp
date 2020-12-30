// TestGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "TestGroup.h"
#include "afxdialogex.h"


// CTestGroup �Ի���

IMPLEMENT_DYNAMIC(CTestGroup, CDialogEx)

CTestGroup::CTestGroup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestGroup::IDD, pParent)
	, m_nMousePos(0)
	, m_nFocusGroup(16)
	, m_nCurGroup(16)
	, m_bDraw(FALSE)
	, m_pTestGroup(nullptr)
	, m_nCurRow(-1)
	, m_nOldGroup(0)
	, m_bAutoAdd(FALSE)
	, m_bGroupChange(FALSE)
	, m_bItemInputFinish(TRUE)
	, m_bTesting(FALSE)
	, m_bLock(FALSE)
{
	m_strAllInfo.clear();
	m_vnUsedCam.clear();
	m_vbMergeResult.resize(MAX_GROUP);
	for (size_t i = 0; i < MAX_GROUP; i++)
	{
		m_vbMergeResult[i] = FALSE;
	}
}


CTestGroup::~CTestGroup()
{
}

void CTestGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_TestProjectList, m_BL_TestProjectList);
	DDX_Control(pDX, IDC_BL_StartCode, m_BL_StartCode);
	DDX_Control(pDX, IDC_BL_RunGroup, m_BL_RunGroup);
	DDX_Control(pDX, IDC_BL_Delete, m_BL_Delete);
	DDX_Control(pDX, IDC_BL_Add, m_BL_Add);
	
}


BEGIN_MESSAGE_MAP(CTestGroup, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CTestGroup ��Ϣ�������

void CTestGroup::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	m_BL_TestProjectList.SetNoRtMenu(TRUE);

	_SetLockStatus();

	if (m_bItemInputFinish)
	{
		CRect  ClientRect;
		if (!m_bDraw)
		{
			GetClientRect(ClientRect);
			//ScreenToClient(ClientRect);
		}
		else
		{
			CRect rc_New(0,0,610,31);
			ClientRect = rc_New;
		}

		CDC MemDC; 

		CBitmap MemBitmap;

		MemDC.CreateCompatibleDC(&dc);  
		MemBitmap.CreateCompatibleBitmap(&dc, ClientRect.Width(), ClientRect.Height()); 
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);         

		MemDC.FillSolidRect(0, 0, ClientRect.Width(), ClientRect.Height(), RGB(64,64,64)); 


		CPen pen(PS_SOLID, 1, RGB(0,255,255));
		CPen pen_0(PS_SOLID, 1, RGB(255,155,32));

		MemDC.SelectStockObject(NULL_BRUSH);
		MemDC.SelectObject(pen);

		//MemDC.Rectangle(rc);

		if (m_rcGroup.size() == 0)//�����ڜyԇȺ�M
		{
			CPoint pt_RcAdd_0(12,5);
			CPoint pt_RcAdd_1(42,30);

			m_rcAdd.TopLeft() = pt_RcAdd_0;
			m_rcAdd.BottomRight() = pt_RcAdd_1;

			//���߅��
			MemDC.MoveTo(12,30);
			MemDC.LineTo(12,5);
			MemDC.LineTo(42,5);
			MemDC.LineTo(42,30);
			MemDC.LineTo(610,30);

			m_BL_TestProjectList.ShowWindow(SW_HIDE);
			m_BL_Delete.ShowWindow(SW_HIDE);
			m_BL_StartCode.ShowWindow(SW_HIDE);
			m_BL_RunGroup.ShowWindow(SW_HIDE);
			m_BL_Add.ShowWindow(SW_HIDE);
			((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->ShowWindow(SW_HIDE);

			//����̖
			if (m_nMousePos == MOUSE_IN_ADD)
			{
				MemDC.SelectObject(pen_0);
			}
			else
			{
				MemDC.SelectObject(pen);
			}
			MemDC.MoveTo(19,17);
			MemDC.LineTo(35,17);

			MemDC.MoveTo(27,10);
			MemDC.LineTo(27,26);
		}
		else//�МyԇȺ�M
		{
			m_BL_TestProjectList.ShowWindow(SW_SHOW);
			m_BL_Delete.ShowWindow(SW_SHOW);
			//m_BL_StartCode.ShowWindow(SW_SHOW);
			m_BL_RunGroup.ShowWindow(SW_SHOW);
			m_BL_Add.ShowWindow(SW_SHOW);
			((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->ShowWindow(SW_SHOW);

			CPoint pt_RcAdd_0(m_rcGroup[m_rcGroup.size() - 1].right, 5);
			CPoint pt_RcAdd_1(m_rcGroup[m_rcGroup.size() - 1].right + 30, 30);

			m_rcAdd.TopLeft() = pt_RcAdd_0;
			m_rcAdd.BottomRight() = pt_RcAdd_1;

			CFont fontGrade;
			fontGrade.CreatePointFont(115, L"Tahoma");
			MemDC.SetTextColor(RGB(0,255,255));
			CString strGroup;
			for (size_t i = 0; i < m_rcGroup.size(); i++)
			{
				strGroup.Format(_T("G%d"), i + 1);
				MemDC.SelectObject(&fontGrade);
				if (!m_bLBtClick[i])
				{
					MemDC.MoveTo(m_rcGroup[i].BottomRight());
					MemDC.LineTo(m_rcGroup[i].left,m_rcGroup[i].bottom);
					MemDC.LineTo(m_rcGroup[i].TopLeft());
					MemDC.LineTo(m_rcGroup[i].right,m_rcGroup[i].top);

					if (m_nMousePos == MOUSE_IN_GROUP)
					{
						if (m_nFocusGroup == i)
						{
							MemDC.SetTextColor(RGB(255,69,0));
						}
						else
						{
							MemDC.SetTextColor(RGB(0,255,255));
						}
					}
					CRect rcPart(m_rcGroup[i].left, m_rcGroup[i].top + 3, m_rcGroup[i].right, m_rcGroup[i].bottom + 3);
					MemDC.DrawTextW(strGroup, &rcPart, DT_EDITCONTROL|DT_CENTER|DT_NOPREFIX);
				}
				else
				{
					MemDC.MoveTo(m_rcGroup[i].right,m_rcGroup[i].top);
					MemDC.LineTo(m_rcGroup[i].right,m_rcGroup[i].top - 5);
					MemDC.LineTo(m_rcGroup[i].left, m_rcGroup[i].top - 5);
					MemDC.LineTo(m_rcGroup[i].left,m_rcGroup[i].bottom);

					CRect rcPart_0(m_rcGroup[i].left + 1, m_rcGroup[i].top - 4, m_rcGroup[i].right, m_rcGroup[i].bottom + 1);
					CBrush brPart(RGB(80,80,80));
					MemDC.FillRect(&rcPart_0, &brPart);

					if (m_nMousePos == MOUSE_IN_GROUP)
					{
						MemDC.SetTextColor(RGB(0,255,255));
					}

					CRect rcPart(m_rcGroup[i].left, m_rcGroup[i].top, m_rcGroup[i].right, m_rcGroup[i].bottom);
					MemDC.SetBkColor(RGB(80,80,80));
					MemDC.DrawTextW(strGroup, &rcPart, DT_EDITCONTROL|DT_CENTER|DT_NOPREFIX);
					MemDC.SetBkColor(RGB(64,64,64));
				}
			}

			if (m_rcGroup.size() < MAX_GROUP)
			{
				MemDC.MoveTo(m_rcGroup[m_rcGroup.size() - 1].right + 30, 30);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].BottomRight());
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right,5);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right + 30,5);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right + 30,30);
				MemDC.LineTo(610,30);

				//����̖
				if (m_nMousePos == MOUSE_IN_ADD)
				{
					MemDC.SelectObject(pen_0);
				}
				else
				{
					MemDC.SelectObject(pen);
				}
				MemDC.MoveTo(m_rcGroup[m_rcGroup.size() - 1].right + 7,17);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right + 23,17);

				MemDC.MoveTo(m_rcGroup[m_rcGroup.size() - 1].right + 15,10);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right + 15,26);
			}
			else
			{
				MemDC.MoveTo(m_rcGroup[m_rcGroup.size() - 1].right, 5);
				MemDC.LineTo(m_rcGroup[m_rcGroup.size() - 1].right,30);
				MemDC.LineTo(610,30);
			}
		}

		//���w߅��
		MemDC.SelectObject(pen);
		MemDC.MoveTo(12,30);
		MemDC.LineTo(3,30);

		dc.BitBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &MemDC, 0, 0, SRCCOPY);    

		MemDC.SelectObject(pOldBit);  

		::ReleaseDC(this->m_hWnd, MemDC);

		MemBitmap.DeleteObject(); 

		dc.SelectObject(pen);
		dc.MoveTo(3,30);
		dc.LineTo(3,330);
		dc.LineTo(610,330);
		dc.LineTo(610,30);
		m_bDraw = TRUE;
	}
	
}


void CTestGroup::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_rcAdd.PtInRect(point))
	{
		m_nMousePos = MOUSE_IN_ADD;
	}
	else
	{
		m_nMousePos = MOUSE_OUT_ADD;
	}
	for (size_t i = 0; i < m_rcGroup.size(); i++)
	{
		if (m_rcGroup[i].PtInRect(point))
		{
			m_nFocusGroup= i;
			m_nMousePos = MOUSE_IN_GROUP;
			break;
		}
	}
	Invalidate(FALSE);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CTestGroup::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bItemInputFinish)
	{
		if (m_rcAdd.PtInRect(point))
		{
			if (!m_bTesting && !m_bLock)
			{
				if (m_rcGroup.size() < MAX_GROUP)
				{
					CRect rcGroup(12 + 55 * m_rcGroup.size(), 5, 12 + 55 * (m_rcGroup.size() + 1), 30);
					m_rcGroup.push_back(rcGroup);
					m_bLBtClick.push_back(FALSE);
					m_nListRowsCounter.push_back(0);
					m_nStartCode.push_back(0);

					//���ͱ���M����������������b�����
					vector<CString> strColInfo;//�������Ϣ
					vector<vector<CString>> strListInfo;//���������Ϣ

					for (int nCounter = 0; nCounter < COL_MAX; nCounter++)
					{
						strListInfo.push_back(strColInfo);
					}
					m_strAllInfo.push_back(strListInfo);

					//���®���
					Invalidate(FALSE);
					//====ÿ���һ��Ⱥ�M������Ҫ�ڱ����Д�����������Ӄ���,�����ʱ�������ʼ������====//
					m_pTestGroup->PostMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_ADD);//���Ⱥ����Ϣ
					return;
				}
			}
		}
		if (m_rcGroup.size() > 0)//ѡ��Ⱥ��ı�
		{
			CRect rcAllGroup(m_rcGroup[0].left, m_rcGroup[0].top, m_rcGroup[m_rcGroup.size() - 1].right, m_rcGroup[m_rcGroup.size() - 1].bottom);
			if (rcAllGroup.PtInRect(point))
			{
				static int nGroupOld = -1;
				for (size_t i = 0; i < m_rcGroup.size(); i++)
				{
					m_bLBtClick[i] = FALSE;
				}
				for (size_t i = 0; i < m_rcGroup.size(); i++)
				{
					if (m_rcGroup[i].PtInRect(point))
					{
						m_nOldGroup = m_nCurGroup;
						if (m_nCurGroup <= 9)
						{
							m_nStartCode[m_nCurGroup] = _ttoi(m_BL_StartCode.GetValueText());
						}
						m_nCurGroup = i;
						m_bLBtClick[i] = TRUE;
						m_BL_StartCode.SetValue(m_nStartCode[m_nCurGroup]);
						UpdateList();
						Invalidate(FALSE);
						m_BL_TestProjectList.ShowWindow(SW_SHOW);
						m_BL_Delete.ShowWindow(SW_SHOW);
						//m_BL_StartCode.ShowWindow(SW_SHOW);
						m_BL_RunGroup.ShowWindow(SW_SHOW);
						m_BL_Add.ShowWindow(SW_SHOW);
						((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->ShowWindow(SW_SHOW);
						if (nGroupOld != (int)i)
						{
							m_pTestGroup->PostMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_CHANGE);//���Ⱥ����Ϣ
							nGroupOld = (int)i;
						}
						break;
					}
				}
				((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetStatus(m_vbMergeResult[m_nCurGroup]);
			}
		}
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CTestGroup::UpdateList()
{
	if (m_BL_TestProjectList.GetRows() > 0)
	{
		m_nListRowsCounter[m_nOldGroup] = m_BL_TestProjectList.GetRows();
		vector<CString> strPart;
		strPart = m_strAllInfo[m_nOldGroup][COL_MAX - 1];
		for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
		{
			m_strAllInfo[m_nOldGroup][nColCounter].clear();
			if (nColCounter < COL_MAX - 1)
			{
				for (int nRowCounter = 0; nRowCounter < m_BL_TestProjectList.GetRows(); nRowCounter++)
				{
					m_strAllInfo[m_nOldGroup][nColCounter].push_back(m_BL_TestProjectList.GetItemText(nRowCounter, nColCounter));
				}
			}
			if (nColCounter == COL_MAX - 1)
			{
				for (size_t i = 0; i < strPart.size(); i++)
				{
					m_strAllInfo[m_nOldGroup][nColCounter].push_back(strPart[i]);
				}
			}
		}
	}

	m_BL_TestProjectList.DeleteAll(FALSE);
	m_BL_TestProjectList.AppendColumn(_T("��̖"), DT_CENTER, 45, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("�z�y���"), DT_CENTER, 80, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("�z�y�Ŀ"), DT_CENTER, 130, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("���C��̖"), DT_CENTER, 80, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("�Ŀ��B"), DT_CENTER, 80, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("��λ��ʽ"), DT_CENTER, 80, FALSE);
	m_BL_TestProjectList.AppendColumn(_T("�yԇ�Y��"), DT_CENTER, 80, FALSE);
	m_BL_TestProjectList.SetNoHotKey(TRUE);
	m_BL_TestProjectList.SetColumnReadOnly(0, TRUE);
	m_BL_TestProjectList.SetColumnReadOnly(COL_MAX - 1, TRUE);
	m_bAutoAdd = TRUE;
	for (int nCounter = 0; nCounter < m_nListRowsCounter[m_nCurGroup]; nCounter++)
	{
		m_BL_TestProjectList.AppendRow(FALSE);
	}
	if (m_BL_TestProjectList.GetRows() > 0)//���������Ѓ���
	{
		for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
		{
			for (int nRowCounter = 0; nRowCounter < m_BL_TestProjectList.GetRows(); nRowCounter++)
			{
				m_BL_TestProjectList.SetItemText(nRowCounter, nColCounter, m_strAllInfo[m_nCurGroup][nColCounter][nRowCounter]);
			}
		}
		m_bGroupChange = TRUE;
		m_BL_TestProjectList.SelectRow(0);
	}
	else
	{
		m_pTestGroup->SendMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_NO_ROWS);//Ⱥ�M�ГQ��������Пo����
	}
	m_bAutoAdd = FALSE;
}


BEGIN_EVENTSINK_MAP(CTestGroup, CDialogEx)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 1, CTestGroup::RowsChangedBlTestprojectlist, VTS_I4 VTS_I4 VTS_BOOL)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 4, CTestGroup::SelectChangedBlTestprojectlist, VTS_I4 VTS_I4)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 5, CTestGroup::LBtDbClickBlTestprojectlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 2, CTestGroup::ItemChangedBlTestprojectlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 6, CTestGroup::ItemEditFinishBlTestprojectlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CTestGroup, IDC_BL_RunGroup, 1, CTestGroup::LBtClickedBlRungroup, VTS_I4)
	ON_EVENT(CTestGroup, IDC_BL_ckMergeResult, 1, CTestGroup::StatusChangedBlckmergeresult, VTS_I2)
	ON_EVENT(CTestGroup, IDC_BL_TestProjectList, 7, CTestGroup::RButtonUpBlTestprojectlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2 VTS_I2)
	ON_EVENT(CTestGroup, IDC_BL_Delete, 1, CTestGroup::LBtClickedBlDelete, VTS_I4)
	ON_EVENT(CTestGroup, IDC_BL_Add, 1, CTestGroup::LBtClickedBlAdd, VTS_I4)
END_EVENTSINK_MAP()


void CTestGroup::RowsChangedBlTestprojectlist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!m_bAutoAdd && bAppend)
	{
		m_nCurRow = m_BL_TestProjectList.GetCurRow();
		for (size_t i = 0; i < COL_MAX; i++)
		{
			m_strAllInfo[m_nCurGroup][i].push_back(_T(""));
		}
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, ROWS_ADD);//����������Ϣ���������͸������
		
	}
}


void CTestGroup::SelectChangedBlTestprojectlist(long nOldSels, long nNewSels)
{
	/*m_BL_TestProjectList.IsRowSelected();*/
	int nSel = m_nCurRow;
	m_nCurRow = m_BL_TestProjectList.GetCurRow();
	if ((m_bGroupChange || (nSel != m_nCurRow)))
	{
		if (m_nCurRow >= 0)
		{
			m_pTestGroup->SendMessage(WM_LISTCHANGE, m_nCurGroup, ROWS_SELECT);//������л���Ϣ�������л�͸���Ի���
		}
		else
		{
			m_pTestGroup->SendMessage(WM_LISTCHANGE, m_nCurGroup, NO_ROWS_SELECT);//������л���Ϣ�������л�͸���Ի���
		}
		m_bGroupChange = FALSE;
	}
	
	// TODO: �ڴ˴������Ϣ����������
}


void CTestGroup::LBtDbClickBlTestprojectlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	if (!m_bTesting)
	{
		CString strItemInfo;
		if (nFlags & MK_CONTROL)
		{
			if (m_bLock)
				return;
			if (nCol == 0)
			{
				m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, CHECK_RUN);
			}
			if (nCol == 2)
			{
				m_BL_TestProjectList.SetColumnReadOnly(2, TRUE);
				m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, DCLICK_TEST_NAME_ITEM);//�o�yԇ�Ŀ�޸Ąe��
			}
			if (nCol == 3)
			{
				m_BL_TestProjectList.SetColumnReadOnly(3, TRUE);
				m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, DCLICK_LIGHT_ITEM);
			}
		}
		else if (nFlags & MK_SHIFT)
		{
			if (m_bLock)
				return;
			if (nCol == 0)
			{
				m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, CMP_RUN);
			}
		}
		else
		{
			if (nCol != 0 && nCol != 6 && !m_bLock)
			{
				m_bItemInputFinish = FALSE;
			}
			if (nCol == 0)
			{
				m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, TEST_RUN);
			}
			if (nCol == 1)
			{
				* pnParam = 2;
				strItemInfo = _T("�yԇ;�y��");
				m_BL_TestProjectList.SetDropDownData(strItemInfo);
			}
			if (nCol == 2)
			{
				m_BL_TestProjectList.SetColumnReadOnly(2, FALSE);
				* pnParam = 2;
				strItemInfo = TEST_PROJECT;
				m_BL_TestProjectList.SetDropDownData(strItemInfo);
			}
			if (nCol == 3)
			{
				m_BL_TestProjectList.SetColumnReadOnly(3, FALSE);
				* pnParam = 2;
				CString strPart;
				for (size_t i= 0; i < m_vnUsedCam.size(); i++)
				{
					strPart.Format(_T("%d;"), m_vnUsedCam[i] + 1);
					strItemInfo.Append(strPart);
				}
				strPart = _T("��ǰ�D��");
				strItemInfo.Append(strPart);
				m_BL_TestProjectList.SetDropDownData(strItemInfo);
			}
			if (nCol == 4)
			{
				* pnParam = 2;
				m_BL_TestProjectList.SetDropDownData(_T("�z�y;δ�z�y"));
			}
			if (nCol == 5)
			{
				* pnParam = 2;
				m_BL_TestProjectList.SetDropDownData(_T("MARK��λ;���϶�λ;�Ƅ����C;�o��λ"));
			}
		}
	}
	if (nCol == 6)//�鿴��������
	{
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, SHOW_TEST_RESULT);
	}
}


void CTestGroup::ItemChangedBlTestprojectlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);

	const CString strOldTemp = strOld;
	const CString strNewTemp = strNew;

	if (strOldTemp == strNewTemp)
	{
		return;
	}

	if(nCol == 1)
	{
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, TEST_MODE_CHANGE);
		CString strInfo = strNew;
		if (strInfo == _T("�y��"))
		{
			if (m_vbMergeResult[m_nCurGroup] == TRUE)
			{
				MsgBox.ShowMsg(_T("�Мy���Ŀ��ȡ���ρ�yԇ�Y��"), _T("��ʾ"), MB_ICONINFORMATION | MB_OK);
				((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetStatus(FALSE);
				m_vbMergeResult[m_nCurGroup] = FALSE;
			}
		}
		
	}
	if (nCol == 2)
	{
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, TEST_PROJECT_CHANGE);
	}
	if (nCol == 3)
	{
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, TEST_IMAGE_CHANGE);
	}
	if (nCol == 4)
	{
		if (m_BL_TestProjectList.GetItemText(nRow, nCol) == _T("�z�y"))
		{
			m_BL_TestProjectList.SetItemTextColor(nRow, nCol, RGB(0,255,255));
		}
		else
		{
			m_BL_TestProjectList.SetItemTextColor(nRow, nCol, RGB(211,211,211));
		}
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, TEST_STATUS_CHANGE);
	}
	if (nCol == 5)//��λ��ʽ��׃
	{
		m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, MARK_ITEM_CHANGE);
	}
	m_strAllInfo[m_nCurGroup][nCol][nRow] = strNew;
}

void CTestGroup::RButtonUpBlTestprojectlist(long nRow, long nCol, short* pnParam, short nX, short nY)
{
	// TODO: �ڴ˴������Ϣ����������
	//m_BL_TestProjectList.
	* pnParam = 2;
}


void CTestGroup::LBtClickedBlRungroup(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	UpdateTestInfo();
	m_pTestGroup->PostMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_TEST_RUN);//�_ʼȺ�M�yԇ
}


void CTestGroup::ItemEditFinishBlTestprojectlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bItemInputFinish = TRUE;
}



BOOL CTestGroup::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
			break;
		case VK_ESCAPE:
			return TRUE;
			break;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTestGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		//����ǰ���Ȍ���ǰ�z�y�M��������
		for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
		{
			m_strAllInfo[m_nCurGroup][nColCounter].clear();
			for (int nRowCounter = 0; nRowCounter < m_BL_TestProjectList.GetRows(); nRowCounter++)
			{
				m_strAllInfo[m_nCurGroup][nColCounter].push_back(m_BL_TestProjectList.GetItemText(nRowCounter, nColCounter));
			}
		}
		m_nListRowsCounter[m_nCurGroup] = m_BL_TestProjectList.GetRows();
		//������΂���
		ar << m_rcGroup.size();

		//����ÿ���z�y�M�ı���Д�
		for (size_t nVector3 = 0; nVector3 < m_nListRowsCounter.size(); nVector3++)
		{
			ar << m_nListRowsCounter[nVector3];
		}
// 
// 		//���������ݶ������M�n��
		for (size_t nVector0 = 0; nVector0 < m_rcGroup.size(); nVector0++)
		{
			for (int nVector1 = 0; nVector1 < COL_MAX; nVector1++)
			{
				for (size_t nVector2 = 0; nVector2 < m_strAllInfo[nVector0][nVector1].size(); nVector2++)
				{
					ar << m_strAllInfo[nVector0][nVector1][nVector2];
				}
			}
		}

		//����ÿ���z�y�M�Ć��Ӵa
		m_nStartCode[m_nCurGroup] = _ttoi(m_BL_StartCode.GetValueText());
		for (size_t nVector4 = 0; nVector4 < m_nListRowsCounter.size(); nVector4++)
		{
			ar << m_nStartCode[nVector4];
		}
		for (size_t i = 0; i < MAX_GROUP; i++)
		{
			ar << m_vbMergeResult[i];
		}
	}
	else
	{	// loading code
		//�����z�y�M�������������������ľ���
		CValueCalculate ValueCalculate;
		vector<CString> vstrTem;
		vstrTem = ValueCalculate.CutStringElse(m_strSoftwareVersion, '.');

		int nRCGroupCounter = 0;
		ar >> nRCGroupCounter;
		for (int nCounter = 0; nCounter < nRCGroupCounter; nCounter++)
		{
			CRect rcGroup(12 + 55 * m_rcGroup.size(), 5, 12 + 55 * (m_rcGroup.size() + 1), 30);
			m_rcGroup.push_back(rcGroup);
			m_bLBtClick.push_back(FALSE);
		}
		m_bLBtClick[0] = TRUE;//������む�z�y�M
		Invalidate(FALSE);

		//��ÿ�������Д�ȡ��
		int nListRowsCounter = 0;
		for (size_t nCounter0 = 0;  nCounter0 < m_rcGroup.size(); nCounter0++)
		{
			ar >> nListRowsCounter;
			m_nListRowsCounter.push_back(nListRowsCounter);
		}
// 
// 		//ȡ��������
		vector<CString> strColInfo;//�������Ϣ
		vector<vector<CString>> strListInfo;//���������Ϣ
		strColInfo.clear();
		strListInfo.clear();
		for (size_t nCounter1 = 0; nCounter1 < m_rcGroup.size(); nCounter1++)
		{
			for (int nCounter2 = 0; nCounter2 < COL_MAX; nCounter2++)
			{
				for (int nCounter6 = 0; nCounter6 < m_nListRowsCounter[nCounter1]; nCounter6++)
				{
					strColInfo.push_back(_T(""));
				}
				strListInfo.push_back(strColInfo);
				strColInfo.clear();
			}
			m_strAllInfo.push_back(strListInfo);
			strListInfo.clear();
		}
		
		for (size_t nCounter3 = 0; nCounter3 < m_rcGroup.size(); nCounter3++)
		{
			for (int nCounter4 = 0; nCounter4 < COL_MAX; nCounter4++)
			{
				for (int nCounter5 = 0; nCounter5 < m_nListRowsCounter[nCounter3]; nCounter5++)
				{
					CString strAr;
					ar >> strAr;
					m_strAllInfo[nCounter3][nCounter4][nCounter5] = strAr;
				}
			}
		}
// 
		m_BL_TestProjectList.DeleteAll(FALSE);
		m_BL_TestProjectList.AppendColumn(_T("��̖"), DT_CENTER, 45, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("�z�y���"), DT_CENTER, 80, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("�z�y�Ŀ"), DT_CENTER, 120, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("���C��̖"), DT_CENTER, 80, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("�Ŀ��B"), DT_CENTER, 80, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("��λ��ʽ"), DT_CENTER, 80, FALSE);
		m_BL_TestProjectList.AppendColumn(_T("�yԇ�Y��"), DT_CENTER, 80, FALSE);
		m_BL_TestProjectList.SetNoHotKey(TRUE);
		m_BL_TestProjectList.SetColumnReadOnly(0, TRUE);
		m_BL_TestProjectList.SetColumnReadOnly(COL_MAX - 1, TRUE);
		m_bAutoAdd = TRUE;
		for (int nCounter = 0; nCounter < m_nListRowsCounter[0]; nCounter++)
		{
			m_BL_TestProjectList.AppendRow(FALSE);
		}
		int nRow = m_BL_TestProjectList.GetRows();
		if (m_BL_TestProjectList.GetRows() > 0)//���������Ѓ���
		{
			for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
			{
				for (int nRowCounter = 0; nRowCounter < m_nListRowsCounter[0]; nRowCounter++)
				{
					m_BL_TestProjectList.SetItemText(nRowCounter, nColCounter, m_strAllInfo[0][nColCounter][nRowCounter]);
				}
			}
			m_nCurGroup = 0;
			m_bGroupChange = TRUE;
			m_BL_TestProjectList.SelectRow(0);
		}
		else
		{
			m_pTestGroup->PostMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_NO_ROWS);//Ⱥ�M�ГQ��������Пo����
		}
		m_bAutoAdd = FALSE;

		
		for (size_t nCounter7 = 0; nCounter7 < m_rcGroup.size(); nCounter7++)
		{
			int nStartCodeCounter = 0;
			ar >> nStartCodeCounter;
			m_nStartCode.push_back(nStartCodeCounter);
		}
		m_BL_StartCode.SetValue(m_nStartCode[0]);

		if (_ttoi(vstrTem[1]) >= 15)
		{
			for (size_t i = 0; i < MAX_GROUP; i++)
			{
				ar >> m_vbMergeResult[i];
			}
			((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetStatus(m_vbMergeResult[0]);
		}
	}
}


void CTestGroup::UpdateTestInfo()
{
	for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
	{
		m_strAllInfo[m_nCurGroup][nColCounter].clear();
		for (int nRowCounter = 0; nRowCounter < m_BL_TestProjectList.GetRows(); nRowCounter++)
		{
			m_strAllInfo[m_nCurGroup][nColCounter].push_back(m_BL_TestProjectList.GetItemText(nRowCounter, nColCounter));
		}
	}
	m_nListRowsCounter[m_nCurGroup] = m_BL_TestProjectList.GetRows();
	m_nStartCode[m_nCurGroup] = _ttoi(m_BL_StartCode.GetValueText());
}


void CTestGroup::StatusChangedBlckmergeresult(short nNewStatus)
{
	CMsgBox MsgBox(this);
	
	// TODO: �ڴ˴������Ϣ����������

	const BOOL bStatus = ((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->GetStatus();

	if (bStatus)
	{
		BOOL bErr = FALSE;
		for (int i = 0; i < m_BL_TestProjectList.GetRows(); i++)
		{
			if (m_BL_TestProjectList.GetItemText(i, 1) == _T("�y��"))
			{
				bErr = TRUE;
				break;
			}
		}
		if (!bErr)
		{
			m_vbMergeResult[m_nCurGroup] = TRUE;
		}
		else
		{
			MsgBox.ShowMsg(_T("�Мy���Ŀ���o���ρ�yԇ�Y��"), _T("�e�`"), MB_ICONERROR | MB_OK);
			((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetStatus(FALSE);
		}
	}
	else
	{
		m_vbMergeResult[m_nCurGroup] = FALSE;
	}
}

void CTestGroup::LBtClickedBlAdd(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	m_BL_TestProjectList.AppendRow(FALSE);
}


void CTestGroup::LBtClickedBlDelete(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	if (nFlags & MK_CONTROL)//�h��Ⱥ�M
	{
		m_bDelete = FALSE;

		m_pTestGroup->SendMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_DELETE);
		if (!m_bDelete)
			return;

		const int nDeleteGroup = m_nCurGroup;
		const int nGroupCounter = (int)m_rcGroup.size();

		m_vbMergeResult.erase(m_vbMergeResult.begin() + m_nCurGroup);
		m_vbMergeResult.push_back(FALSE);

		m_nListRowsCounter.erase(m_nListRowsCounter.begin() + m_nCurGroup);
		m_nStartCode.erase(m_nStartCode.begin() + m_nCurGroup);
		m_bLBtClick.erase(m_bLBtClick.begin() + m_nCurGroup);
		m_strAllInfo.erase(m_strAllInfo.begin() + m_nCurGroup);
		m_rcGroup.pop_back();
		m_BL_TestProjectList.DeleteAll(FALSE);

		if (m_rcGroup.size() > 0)//�h��Ⱥ�M����ʣ�NȺ�M
		{
			for (size_t i = 0; i < m_rcGroup.size(); i++)
			{
				m_bLBtClick[i] = FALSE;
			}
			m_nCurGroup = nDeleteGroup == nGroupCounter - 1 ? nDeleteGroup - 1 : nDeleteGroup;//�h������һ��Ⱥ�M��ָ��ǰһ������ָ֮����һ��
			
			m_bLBtClick[m_nCurGroup] = TRUE;
			m_BL_StartCode.SetValue(m_nStartCode[m_nCurGroup]);
			m_pTestGroup->PostMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_CHANGE);//���Ⱥ����Ϣ
			((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetStatus(m_vbMergeResult[m_nCurGroup]);

			m_BL_TestProjectList.AppendColumn(_T("��̖"), DT_CENTER, 45, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("�z�y���"), DT_CENTER, 80, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("�z�y�Ŀ"), DT_CENTER, 130, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("���C��̖"), DT_CENTER, 80, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("�Ŀ��B"), DT_CENTER, 80, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("��λ��ʽ"), DT_CENTER, 80, FALSE);
			m_BL_TestProjectList.AppendColumn(_T("�yԇ�Y��"), DT_CENTER, 80, FALSE);
			m_BL_TestProjectList.SetNoHotKey(TRUE);
			m_BL_TestProjectList.SetColumnReadOnly(0, TRUE);
			m_BL_TestProjectList.SetColumnReadOnly(COL_MAX - 1, TRUE);
			m_bAutoAdd = TRUE;

			for (int nCounter = 0; nCounter < m_nListRowsCounter[m_nCurGroup]; nCounter++)
			{
				m_BL_TestProjectList.AppendRow(FALSE);
			}
			if (m_BL_TestProjectList.GetRows() > 0)//���������Ѓ���
			{
				for (int nColCounter = 0; nColCounter < COL_MAX; nColCounter++)
				{
					for (int nRowCounter = 0; nRowCounter < m_BL_TestProjectList.GetRows(); nRowCounter++)
					{
						m_BL_TestProjectList.SetItemText(nRowCounter, nColCounter, m_strAllInfo[m_nCurGroup][nColCounter][nRowCounter]);
					}
				}
				m_bGroupChange = TRUE;
				m_BL_TestProjectList.SelectRow(0);
				m_bAutoAdd = FALSE;
			}
		}
		else
		{
			m_nCurGroup = 16;
			m_pTestGroup->SendMessage(WM_GROUPCHANGE, m_nCurGroup, GROUP_NO_ROWS);//Ⱥ�M�ГQ��������Пo����
		}
		
		Invalidate(FALSE);
	}
	else if (nFlags & MK_SHIFT)
	{
	
	}
	else//�h���yԇ�Ŀ
	{
		m_bDelete = FALSE;

		_GetSelectRows();
		m_pTestGroup->SendMessage(WM_LISTCHANGE, m_nCurGroup, ROWS_DELETE);
		if (!m_bDelete)
			return;

		const int nRowsBkup = m_BL_TestProjectList.GetRows();

		if ((int)m_vnSelectRows.size() < nRowsBkup)
		{
			if ((int)m_vnSelectRows.size() == 1)
			{
				m_nCurRow = m_vnSelectRows[0] == nRowsBkup - 1 ? m_vnSelectRows[0] - 1 : m_vnSelectRows[0];//�h������һ���Ŀ��ָ��ǰһ������ָ֮����һ��
			}
			else
			{
				m_nCurRow = 0;
			}
		}

		int i = (int)m_vnSelectRows.size() - 1;
		for (; i >= 0; i--)
		{
			m_BL_TestProjectList.DeleteRow(m_vnSelectRows[i], FALSE);
		}
		
		if ((int)m_vnSelectRows.size() < nRowsBkup)
		{
			m_BL_TestProjectList.SelectRow(m_nCurRow);
		}
		else
		{
			m_nCurRow = -1;
			m_pTestGroup->PostMessage(WM_LISTCHANGE, m_nCurGroup, NO_ROWS_SELECT);
		}

		UpdateTestInfo();
	}
}

vector<int> CTestGroup::_GetSelectRows()
{
	m_vnSelectRows.clear();
	for (int i = 0; i < m_BL_TestProjectList.GetRows(); i++)
	{
		if (m_BL_TestProjectList.IsRowSelected(i))
		{
			m_vnSelectRows.push_back(i);
		}
	}
	return m_vnSelectRows;
}


void CTestGroup::_SetLockStatus()
{
	if (m_nCurGroup > (MAX_GROUP - 1) || m_bTesting || m_bLock)//
	{
		m_BL_TestProjectList.SetReadOnly(TRUE);
		m_BL_StartCode.SetEnabled(FALSE);
		m_BL_RunGroup.SetEnabled(FALSE);
		m_BL_Delete.SetEnabled(FALSE);
		m_BL_Add.SetEnabled(FALSE);
		((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetEnabled(FALSE);
	}
	if (m_nCurGroup < (MAX_GROUP - 1) && !m_bTesting && !m_bLock)//
	{
		m_BL_TestProjectList.SetReadOnly(FALSE);
		m_BL_StartCode.SetEnabled(TRUE);
		m_BL_RunGroup.SetEnabled(TRUE);
		m_BL_Delete.SetEnabled(TRUE);
		m_BL_Add.SetEnabled(TRUE);
		((CBL_CheckBox *)(GetDlgItem(IDC_BL_ckMergeResult)))->SetEnabled(TRUE);
	}
}


