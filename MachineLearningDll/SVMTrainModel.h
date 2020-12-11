#pragma once

#include "Resource.h"

#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"
#include "..\BlendWndDll\MsgBox.h"
#include "..\CRCDll\\ValueCalculate.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

#include <math.h>


#include <windows.h>
#include <stdlib.h>
#include <iostream>

#include <thread>

using namespace cv;
using namespace std;

// CSVMTrainModel �Ի���

enum Img_Channel{IMG_GRAY = 1, IMG_RGB = 3};

enum SVM_TrainErrCode{IMG_CHANNEL_ERR = 1};

#define SVM_SAMPLE_COUNTER  30//SVM�ӱ�����


class AFX_EXT_CLASS CSVMTrainModel : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSVMTrainModel)

public:
	CSVMTrainModel(CWnd* pParent = NULL);   // ��׼���캯��
	CSVMTrainModel(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CSVMTrainModel();

// �Ի�������
	enum { IDD = IDD_SVMTRAINMODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:

	Mat m_TrainingImages;
	vector<int> m_vnTrainingLabels;

	BOOL m_bSVMLoad;//�Ƿ���dӖ����
	CvSVM m_svmTrainRes;//�ѽ���ɵ�SVMӖ����������A�y�r���d

	CvSVM m_svmTrain;//Ӗ���������Ӗ��ʹ��

	/*
	trainingImages--Ӗ���D�񼯺�
	trainingLabels--Ӗ���D��ı�ǩ����ʾ���ͼ����ַ��� ��ASC���ʾ
	*/

	BOOL SVMTrain(vector<CString> vstrImagePath, vector<int> vnImageLable, int nImgChannel, int & nErrCode);

	char Test_SVM(CSmartImage ImgSrc, const CString strPath, int nImgChannel);//exe��·�����Á�@ȡSVM�ļ���·�����R�r�D��·��

	void Load_SVM(const CString strPath);//ʹ��·�����dSVM�ļ��������ǰ���d�������yԇ�ٶ�

	void MakeImgSameSize();

	static int m_snTestImgLab;//��출yԇ���R�r�D��̖����������}��ʹ���o�B�ɆT׃��

/*1.strImgSrcPath -- Դ�D��·����Դ�D�����Ƕ�ֵ�D��
  2.strImgDstPath -- Ŀ�ˈD��·��
  3.nWeightResize -- �s�ź�ĈD���L��
  4.nHeightResize -- �s�ź�ĈD�񌒶�
  5.nContours -- ������݆������  nContours = 1 ȡ��e���݆��
  6.bMid -- ݆���Ƿ����
  
  */
	void GetImgModel(CString strImgSrcPath, CString strImgDstPath, int nWeightResize, int nHeightResize, int nContours = 1, BOOL bMid = TRUE);//����ֵ�D����к󣬿s�����O�ô�С
	void GetImgModel(CSmartImage * pImgSrc, CSmartImage * pImgDst, int nWeightResize, int nHeightResize);
	

	/*bAll = TRUE �����ļ��A���������ļ��A���е��ļ�����
	  bAll = FALSE ֻ����ԓ�ļ��A�е��ļ�����*/
	int _GetFileCounter(CString strPath, BOOL bAll = FALSE);

	vector<CString> _GetFilePath(CString strPath);
};





