#pragma once
#include "Resource.h"

#include "..\SenTechCamDll\StCamera.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\SenTechCamDll.lib")
#else
#pragma comment(lib, "..\\Release\\SenTechCamDll.lib")
#endif


typedef struct _tagNetInterface
{
	int nIndex;						// �������
	BOOL bWithCam;					// �Ƿ����������
	CString strMac;					// Mac��ַ
	CString strIP;					// IP��ַ
	CString strSubnetMask;			// ��������
	int nCamSum;					// �������
	CStCamera *pDevice;				// ���
}NET_INTERFACE;


// CCamMgr �Ի���

class AFX_EXT_CLASS CCamMgr : public CAppBase
{
	DECLARE_DYNAMIC(CCamMgr)

public:
	CCamMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCamMgr();

// �Ի�������
	enum { IDD = IDD_CAMMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nCameras;
	int m_nNetCount;
	NET_INTERFACE *m_pNetInterface;
	vector<ST_INDEX> m_vNetCam;
	vector<ST_INDEX> m_vUsedCam;

	int FindCamera(CWnd * pOwner);

	BOOL CCamMgr::Attach(CStCamera ** ppDevice, const CString & strMac);
	BOOL Attach(CStCamera ** ppDevice, int nNet, int nCam);
	BOOL Attach(CStCamera ** ppDevice, ST_INDEX Index);
	ST_INDEX Attach(CStCamera ** ppDevice);

	BOOL Disconnect(int nNet, int nCam);
	BOOL Disconnect(ST_INDEX Index);

	void DisconnectUnusedCam(void);
	void Release(void);
protected:
	static UINT _DisconnecUnusedThread(LPVOID pParam);
	UINT _DisconnecUnusedKernal(void);
private:
	vector<ST_INDEX> m_vUnusedCam;
};
