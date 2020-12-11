// SVMTrainModel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SVMTrainModel.h"
#include "afxdialogex.h"


#include "opencv2/opencv.hpp"
#include "opencv2/ml.hpp"


using namespace cv;
using namespace std;

int CSVMTrainModel::m_snTestImgLab = 0;

HANDLE hMutex;	//���廥�������


// CSVMTrainModel �Ի���

IMPLEMENT_DYNAMIC(CSVMTrainModel, CTpLayerWnd)


CSVMTrainModel::CSVMTrainModel(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSVMTrainModel::IDD, pParent)
	, m_bSVMLoad(FALSE)
{
	hMutex = CreateMutex(NULL, false, _T("mutex"));		//�����������
}

CSVMTrainModel::CSVMTrainModel(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{
}

CSVMTrainModel::~CSVMTrainModel()
{
}

void CSVMTrainModel::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSVMTrainModel, CTpLayerWnd)
END_MESSAGE_MAP()


BOOL CSVMTrainModel::SVMTrain(vector<CString> vstrImagePath, vector<int> vnImageLable, int nImgChannel, int & nErrCode)//�΂��ַ��W��
{
	m_bSVMLoad = FALSE;
	Mat classes;
	Mat trainingData;

	m_TrainingImages.release();
	m_vnTrainingLabels.clear();

	for (size_t i = 0; i < vstrImagePath.size(); i++)
	{
		const int nImageCounter = _GetFileCounter(vstrImagePath[i]);
		vector<CString> vstrFilePath = _GetFilePath(vstrImagePath[i]);
		USES_CONVERSION;
		for (int j = 0; j < nImageCounter; j++)
		{
			Mat SrcImage = imread(W2A(vstrFilePath[j]));
// 			const int nChannel = SrcImage.channels();
// 			if (SrcImage.channels() != nImgChannel)
// 			{
// 			nErrCode = IMG_CHANNEL_ERR;
// 			return FALSE;
// 			}
			resize(SrcImage, SrcImage, cv::Size(50,50));

			SrcImage = SrcImage.reshape(1, 1);
			m_TrainingImages.push_back(SrcImage);
			m_vnTrainingLabels.push_back(vnImageLable[i]);
		}
	}

	Mat(m_TrainingImages).copyTo(trainingData);
	nImgChannel == IMG_GRAY ? trainingData.convertTo(trainingData, CV_32FC1) : trainingData.convertTo(trainingData, CV_32FC3);

	Mat(m_vnTrainingLabels).copyTo(classes);
	//����SVMѵ��������
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	SVM_params.kernel_type = CvSVM::LINEAR; 
	SVM_params.degree = 0;
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0;
	SVM_params.C = 1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 10000, 0.0001);
	//ѵ��
	//CvSVM svm;
	m_svmTrain.clear();
	m_svmTrain.train(trainingData, classes, Mat(), Mat(), SVM_params);
	return TRUE;
	//����ģ��
	//svm.save("C:\\Users\\zyp0102\\Desktop\\SVM\\svm.xml");
	//m_svmTrain.save("C:\\Users\\zyp0102\\Desktop\\���c�ӱ�\\Dots_svm.xml");
	
}


char CSVMTrainModel::Test_SVM(CSmartImage ImgSrc, const CString strPath, int nImgChannel)
{
	USES_CONVERSION;

	if (!m_bSVMLoad)
	{
		m_svmTrainRes.clear();
		m_svmTrainRes.load(W2A(strPath));
		m_bSVMLoad = TRUE;
	}

	static BOOL bImg = FALSE;
	static CString strImgTempPath = _T("");
	WaitForSingleObject(hMutex, INFINITE);
	if (!bImg)
	{
		strImgTempPath = g_strExePath + _T("\\Temp.bmp");
		bImg = TRUE;
	}
	ImgSrc.SaveWithPath(strImgTempPath);
	Mat SrcImage = imread(W2A(strImgTempPath));
	ReleaseMutex(hMutex);
	/*if (SrcImage.channels() != nImgChannel)
	return 0;*/
	
	Mat p = SrcImage.reshape(1, 1);
	nImgChannel == IMG_GRAY ? p.convertTo(p, CV_32FC1) : p.convertTo(p, CV_32FC3);

	float fRes = m_svmTrainRes.predict(p);//�A�y����;
	char response = (int)m_svmTrainRes.predict(p);//�A�y����
	p.release();

	return response;

}

void CSVMTrainModel::Load_SVM(const CString strPath)
{
	USES_CONVERSION;

	if (!m_bSVMLoad)
	{
		m_svmTrainRes.clear();
		m_svmTrainRes.load(W2A(strPath));
		//m_svmTrainRes.load("C:\\Users\\zyp0102\\Desktop\\SVM\\svm.xml");
		m_bSVMLoad = TRUE;
	}
}

void CSVMTrainModel::MakeImgSameSize()
{
	for (int i = 0; i < SVM_SAMPLE_COUNTER; i++)
	{
		CString strLoadPath;
		strLoadPath.Format(_T("C:\\Users\\zyp0102\\Desktop\\SVM\\1\\%d.bmp"), i + 1);
		
		CString strSavePath;
		strSavePath.Format(_T("C:\\Users\\zyp0102\\Desktop\\svmTest\\1\\%d.bmp"), i + 1);

		GetImgModel(strLoadPath, strSavePath, 50, 50);
	}
}

void CSVMTrainModel::GetImgModel(CString strImgSrcPath, CString strImgDstPath, int nWeightResize, int nHeightResize, int nContours, BOOL bMid)
{
	CSmartImage ImgTemp;
	ImgTemp.Open(strImgSrcPath);

	cvContours vOutline;

	Resize(&ImgTemp, &ImgTemp, nWeightResize ,nHeightResize);

	findContours(ImgTemp, vOutline, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//��ȡ݆��

	const int nMaxTar = GetMaxSizeContour(&vOutline);
	
	drawContours(ImgTemp, vOutline, -1, Scalar::all(0), CV_FILLED);

	int npt_Left = vOutline[nMaxTar][0].x;
	int npt_Right = vOutline[nMaxTar][0].x;
	int npt_Top = vOutline[nMaxTar][0].y;
	int npt_Bottom = vOutline[nMaxTar][0].y;

	for (size_t i = 0; i < vOutline[nMaxTar].size(); i++)
	{
		npt_Right  = npt_Right  <= vOutline[nMaxTar][i].x ? vOutline[nMaxTar][i].x : npt_Right;
		npt_Left   = npt_Left   >= vOutline[nMaxTar][i].x ? vOutline[nMaxTar][i].x : npt_Left;
		npt_Top    = npt_Top    >= vOutline[nMaxTar][i].y ? vOutline[nMaxTar][i].y : npt_Top;
		npt_Bottom = npt_Bottom <= vOutline[nMaxTar][i].y ? vOutline[nMaxTar][i].y : npt_Bottom;
	}

	int nMovWeight = (ImgTemp.Width() - npt_Right + npt_Left) / 2 - npt_Left;
	int nMovHeigtht = (ImgTemp.Height() - npt_Bottom + npt_Top) / 2 - npt_Top;

	drawContours(ImgTemp, vOutline, nMaxTar, Scalar::all(255), CV_FILLED, 8, noArray(), INT_MAX, Point2i(nMovWeight, nMovHeigtht));

	ImgTemp.SaveWithPath(strImgDstPath);
}


int CSVMTrainModel::_GetFileCounter(CString strPath, BOOL bAll)
{
	int nCounter = 0;
	CFileFind Finder;
	BOOL bWorking = Finder.FindFile(strPath + _T("\\*.bmp*"));

	while (bWorking)
	{
		bWorking = Finder.FindNextFile();
		if (Finder.IsDots())
			continue;
		if (bAll)
		{
			if (Finder.IsDirectory())
			{
				nCounter += _GetFileCounter(Finder.GetFilePath());
			}
			else
			{
				nCounter++;
			}
		}
		else
		{
			if (!Finder.IsDirectory())
				nCounter++;
		}
	}
	return nCounter;
}


vector<CString> CSVMTrainModel::_GetFilePath(CString strPath)
{
	vector<CString> vstrFilePath; 
	CString strTmp;   //����ҵ������ļ��� ����ļ���·��

	int nCounter = 0;
	CFileFind Finder;
	BOOL bWorking = Finder.FindFile(strPath + _T("\\*.bmp*"));

	while (bWorking)
	{
		bWorking = Finder.FindNextFile();
		if (Finder.IsDots())
			continue;
		
		if (!Finder.IsDirectory())
		{
			strTmp = Finder.GetFileName(); //�����ļ�����������׺��
			vstrFilePath.push_back(strPath + _T("\\") + strTmp);
		}
	}
	return vstrFilePath;
}


//void feature(Mat dealimage)
//{
//	//��ѵ�������Ŵ�128��128������HOG��ȡ���� 
//// 	Mat trainImg = Mat(Size2i(128, 128), CV_8UC1); 
//// 	resize(dealimage, trainImg, trainImg.size());
//// 	//����HOG���� 
//// 	//��ⴰ��(64,128),��ߴ�(16,16),�鲽��(8,8),cell�ߴ�(8,8),ֱ��ͼbin����9  ����Ҫ�޸�
//// 	HOGDescriptor *hog = new HOGDescriptor(Size2i(128, 128), Size2i(16, 16), Size2i(8, 8), Size2i(8, 8), 9);
//// 	vector<float>descriptors;//��Ž��    ΪHOG����������    
//// 	hog->compute(trainImg, descriptors, Size2i(1, 1), Size2i(0, 0)); //Hog�������㣬��ⴰ���ƶ�����(1,1)     
//// 
//// 	//cout << "HOG����������ά��    : " << descriptors.size() << endl;
//// 
//// 
//// 	for (vector<float>::size_type j = 0; j < descriptors.size(); j++)
//// 	{
//// 		//��һ��ͼ���HOG�������������δ���data_mat�����ͬһ��
//// 		data_mat.at<float>(yangben_data_position, j) = descriptors[j];
//// 	}
//}
