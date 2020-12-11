#pragma once
#include "Resource.h"

#include "SVMTrainModel.h"
// CMLTrain �Ի���

enum TrainMethod{TRAIN_SVM = 1};


class AFX_EXT_CLASS CMLTrain : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CMLTrain)

public:
	CMLTrain(CWnd* pParent = NULL);   // ��׼���캯��
	CMLTrain(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CMLTrain();

// �Ի�������
	enum { IDD = IDD_MLTRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CBL_List m_BL_ltSampleInfo;
public:
	int m_nTrainMethod;//Ӗ������
	int m_nSampleChnnel;//�D��ͨ��

	DECLARE_EVENTSINK_MAP()
	void SelectChangedBldpmlmethod(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void SelectChangedBldpmlimgchannel(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void LBtClickedBlbtgetsamplepath(long nFlags);

public:
	void _NewSampleInfoList();
	void LBtClickedBlbtmmltrain(long nFlags);
};
