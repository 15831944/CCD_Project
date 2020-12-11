// UdpSvr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YxSocket.h"
#include "Ethernet.h"

// CYxSocket

CYxSocket::CYxSocket()
	: m_pOwner(nullptr)
{
}

CYxSocket::~CYxSocket()
{
}


// CYxSocket ��Ա����

void CYxSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CEthernet *)m_pOwner)->AddClient();

	CSocket::OnAccept(nErrorCode);
}


void CYxSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CEthernet *)m_pOwner)->ReceiveData(this);

	CSocket::OnReceive(nErrorCode);
}


void CYxSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CEthernet *)m_pOwner)->RemoveClient(this);

	CSocket::OnClose(nErrorCode);
}
