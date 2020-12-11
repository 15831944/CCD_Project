#pragma once

#include "YxSocket.h"
#include "CoilRegSpy.h"

#pragma comment(lib, "iphlpapi.lib")

enum
{
	NET_SVR_LOAD_FILE = 0,		// ���ص���
	NET_SVR_SAVE_FILE,			// ���浵��
	NET_SVR_ATM_PIN_OFST,		// ��ȡATM��λʱPinƫ����
	NET_SVR_PAD_LOGIN,			// Զ�̵�½
	NET_SVR_KEEP_ALIVE,			// �ֱ۵�ǰ״̬
	NET_SVR_SET_CUS_VAL,		// �����Զ������ֵ
	NET_SVR_GET_CUS_VAL,		// ��ȡ�Զ������ֵ
	NET_SVR_SET_ROB_POS,		// �����ֱ۵�λ
	NET_SVR_GET_ROB_POS,		// ��ȡ�ֱ۵�λ
	NET_SVR_FILE_LIST,			// ��ȡ�����б�
	NET_SVR_OPEN_FILE,			// �򿪵���
	NET_SVR_SAVE_CHANGE,		// �����ĵ�
	NET_SVR_ROBS_LIST,			// ȡ���ֱ��б�
	NET_SVR_ROB_SLECT,			// ѡ���ֱ�
	NET_SVR_ROB_CHANGE,			// �޸��ֱ۵�ַ������
	NET_SVR_CONNECT_CTRL,		// ���ӵ�������
	NET_SVR_CLAER_ERR,			// ���������Ϣ
	NET_SVR_GET_ERR,			// ȡ�ô�����Ϣ
	NET_SVR_MANUAL_INFO,		// ȡ���ֱ�״̬�µ���Ϣ
	NET_SVR_SET_MOTOR,			// ���õ��״̬
	NET_SVR_CHANGE_SYS,			// �л�����ϵ
	NET_SVR_CHANGE_SPD,			// �����ٶ�
	NET_SVR_CHANGE_STEP,		// �޸��ƶ�����
	NET_SVR_QUERY_POS,			// ȡ�õ�ǰλ��
	NET_SVR_READ_POS,			// ȡ��ָ��λ��
	NET_SVR_WRITE_POS,			// д��ָ��λ��
	NET_SVR_GO_DST,				// �ƶ���Ŀ���
	NET_SVR_JOG_OPERATION,		// �̵�������
	NET_SVR_IO_LIST,			// ȡ���б�
	NET_SVR_QUERY_IO,			// ȡ��IO״̬
	NET_SVR_SET_IO,				// ����IO״̬
	NET_SVR_SET_CLAMP,			// ��������״̬
	NET_SVR_CHANGE_STATUS,		// �ı�����״̬
	NET_SVR_STOP_ROBOT,			// ֹͣ�ֱ�
	NET_SVR_RESET_ROBOT,		// ��λ�ֱ�
	NET_SVR_QUERY_CONDITION,	// ��ȡ�ֱ۲���
	NET_SVR_SET_CONDITION		// �����ֱ۲���
};

enum
{
	NET_TYPE_SERVER = 0,		// ������
	NET_TYPE_CLIENT,			// �ͻ���
	NET_TYPE_SUM
};

enum
{
	NET_PROTOCOL_TCP = 0,		// TCPЭ��
	NET_PROTOCOL_UDP,			// UDPЭ��
	NET_PROTOCOL_MODBUS,		// MODBUSЭ��
	NET_PROTOCOL_SUM,
	NET_MODBUS_PORT = 502		// MODBUS�˿�
};

enum
{
	NET_DATA_MODE_ASCII = 0,	// ASCII��ʽ
	NET_DATA_MODE_HEX,			// ʮ������
	NET_DATA_MODE_DEC,			// ʮ����
	NET_DATA_MODE_SUM
};

typedef struct _tagEthernetParam
{
	int nType;				// ��������ͻ���
	int nPort;				// �˿�
	int nProtocol;			// Э��
	int nDevId;				// �豸ID
	CString strIp;			// IP��ַ
}ETHERNET_PARAM;

// Smart-Robots	8888
// Smart-Dot	8889
// Twist-Brain	8890
// Smart-LED	8891
// Pin-Brain	8892

#define NET_SVR_DEFAULT_PORT	8892	// ���ʹ��ModBus, ��˿ں���502
#define STR_NET_INFO			_T("#NET_INFO#")
#define STR_NET_BACK			_T("#NET_BACK#")
#define APP_NET_CLOSE			_T("#NET_CLOSE#")
#define STR_NET_OK				_T("OK")
#define STR_NET_NG				_T("NG")

const UINT gMsgAppNetServerInfo = RegisterWindowMessage(_T("gMsgAppNetServerInfo"));
const UINT gMsgAppNetClientInfo = RegisterWindowMessage(_T("gMsgAppNetClientInfo"));

// CEthernet �Ի���

class AFX_EXT_CLASS CEthernet : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CEthernet)

public:
	CEthernet(CWnd* pParent = NULL);   // ��׼���캯��
	CEthernet(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CEthernet();

	// �Ի�������
	enum { IDD = IDD_ETHERNET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	BOOL m_bDefSvr;				// Ĭ�Ϸ��������
	CString m_strName;			// �洢Ϊini�ļ�ʱ���ֲ�ͬ������
	ETHERNET_PARAM m_SetData;	// �豸����

	CYxSocket m_Lisener;		// ��������
	CString m_strSvrAnswer;		// �������ظ���Ϣ

	int m_nRevMode;				// ������ʾģʽ
	int m_nSendMode;			// ��������ģʽ

	CBL_List m_ClientList;		// �ͻ��˱��
	CBL_List m_ReceiveList;		// ������Ϣ��ʾ���

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	void UpdateUi(void);
	void LoadDefaultSet(const CString & strName);
	void SaveDefaultSet(void);

	BOOL CreateServer(CString * pErr);
	BOOL CreateServer(const CString & strIp, int nPort, int nProtocol, CString * pErr);
	BOOL ShutDownServer(void);

	BOOL Connect(CString * pErr);
	BOOL Connect(const CString & strIp, int nPort, int nProtocol, CString * pErr);
	BOOL Disconnect(CString * pErr);
	BOOL IsConnected(void);

	BOOL SendData(const CNewPtr<char> * pData, CString * pErr);
	BOOL SendData(const char * pData, int nLength, CString * pErr);
	BOOL SendData(const CString & strData, CString * pErr);

	BOOL SendData(CSocket * pClient, const CNewPtr<char> * pData, CString * pErr);
	BOOL SendData(CSocket * pClient, const char * pData, int nLength, CString * pErr);
	BOOL SendData(CSocket * pClient, const CString & strData, CString * pErr);

	int ModBusWrite(CSocket * pUser, int nAddr, int nFun, const CString & strData, BOOL bWaitAnswer, CNewPtr<char> * pAnswer = nullptr);

	int GetCoil(int nAddr, int nCoil, BOOL & bStatus);
	int GetCoils(int nAddr, int nStart, int nBits, CNewPtr<BOOL> * pStatus);
	int GetCoils(int nAddr, int nStart, int nBits, std::vector<BOOL> * pStatus);

	int SetCoil(int nAddr, int nCoil, BOOL bStatus);
	int SetCoils(int nAddr, int nStart, CNewPtr<BOOL> * pStatus);
	int SetCoils(int nAddr, int nStart, const std::vector<BOOL> * pStatus);
	int SetCoils(int nAddr, int nStart, int nBits, ...);

	int GetHoldRegister(int nAddr, int nReg, USHORT & nValue);
	int GetHoldRegisters(int nAddr, int nStart, int nRegs, CNewPtr<USHORT> * pValue);
	int GetHoldRegisters(int nAddr, int nStart, int nRegs, std::vector<USHORT> * pValue);

	int SetHoldRegister(int nAddr, int nCoil, USHORT nValue);
	int SetHoldRegisters(int nAddr, int nStart, CNewPtr<USHORT> * pValue);
	int SetHoldRegisters(int nAddr, int nStart, const std::vector<USHORT> * pVlaue);
	int SetHoldRegisters(int nAddr, int nStart, int nBytes, ...);

	void AddClient(void);
	void RemoveClient(CYxSocket * pUser);
	void ReceiveData(CYxSocket * pUser);

	BOOL IsServerAnswered(void);
protected:
	BOOL m_bWaitAnswer;
	USHORT m_nModBusCount;	
	CCoilRegSpy *m_pSpyTopWnd;

	CSemaphore m_seSend;
	std::vector<CYxSocket *> m_vClients;

	int m_nCurClient;
	BOOL m_bNetClose;

	ETHERNET_PARAM m_SetDataBkup;

	virtual void _PreShowWnd(void);

	int _ModbusProcess(CSocket * pClient);
	void _ErrReplay(CSocket * pClinet, int nAddr, int nFun, int nErrNo);

	int _GetSockType(void);
	void _ShowRevData(char * pBuffer, int nBytesRead);

	static UINT _ClientRevThread(LPVOID pParam);
	UINT _ClientRevThreadKernel(void);
protected:
	afx_msg LRESULT OnNetRevMode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetSendMode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetClientShow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetUpdateUi(WPARAM wParam, LPARAM lParam);
public:
	void LBtClickedBtNetOpen(long nFlags);
	void LBtClickedBtNetCoilReg(long nFlags);
	void LBtClickedBtNetClearReceive(long nFlags);
	void LBtClickedBtNetSend(long nFlags);
	void SelectChangedDnNetType(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void SelectChangedDnNetProtocol(LPCTSTR strOld, LPCTSTR strNew, short nPos);	
	void TextChangedDnNetIp(LPCTSTR strNew);
	void SelectChangedDnNetIp(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void ValueChangedEditNetPort(LPCTSTR strNew);
	void ValueChangedEditNetDevId(LPCTSTR strNew);
	void SelectChangedListNetClients(long nOldSels, long nNewSels);	
	void TextChangedDnNetSendData(LPCTSTR strNew);
};
