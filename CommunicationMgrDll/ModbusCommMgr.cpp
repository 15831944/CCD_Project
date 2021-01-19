// ModbusCommMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModbusCommMgr.h"
#include "afxdialogex.h"


// CModbusCommMgr �Ի���

IMPLEMENT_DYNAMIC(CModbusCommMgr, CTpLayerWnd)

CModbusCommMgr::CModbusCommMgr(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CModbusCommMgr::IDD, pParent)
{

}

CModbusCommMgr::CModbusCommMgr(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}
CModbusCommMgr::~CModbusCommMgr()
{
}

void CModbusCommMgr::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModbusCommMgr, CTpLayerWnd)
END_MESSAGE_MAP()


// CModbusCommMgr ��Ϣ�������

void CModbusCommMgr::_CreateSerialPortBlendWnd(CWnd * pOwner)
{
	if (pOwner == nullptr)
	{
		pOwner = this;
	}
	m_pPort = new CBlender<CSerialPort>;
	m_pPort->CreateBlendWnd(pOwner);
}

INT_PTR CModbusCommMgr::_CreateSerialPortTopWnd(BOOL bModal, BOOL bShowNow)
{
	return m_pPort->CreateTopWnd(bModal, bShowNow);
}