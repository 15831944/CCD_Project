// QrParse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QrParse.h"
#include "afxdialogex.h"


// CQrParse �Ի���

IMPLEMENT_DYNAMIC(CQrParse, CDialogEx)

CQrParse::CQrParse(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQrParse::IDD, pParent)
{

}

CQrParse::~CQrParse()
{
}

void CQrParse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQrParse, CDialogEx)
END_MESSAGE_MAP()


// CQrParse ��Ϣ�������

int CQrParse::FindQrPoint(CSmartImage * pImgSrc, vector<vector<Point2i>> & vvPtQr)
{
	if (pImgSrc->channels() > 1)
	{
		return 0;
	}

	CSmartImage ImgTarget;
	CSmartImage ImgDst;

	ImgTarget.Clone(pImgSrc);
	ImgDst.Clone(pImgSrc);

	//���ò�����������
	vector<vector<Point2i> > contours;
	vector<Vec4i> hierarchy;
	findContours(ImgTarget, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);

	//ͨ����ɫ��λ����Ϊ�����������������������ص㣬ɸѡ��������λ��
	int nCurContourIndex = -1;//��ǰ݆����̖
	int nInsideCounter = 0;//��݆������

	for (size_t i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][2] != -1 && nInsideCounter == 0)
		{
			nCurContourIndex = i;
			nInsideCounter++;
		}
		else if (hierarchy[i][2] != -1)
		{
			nInsideCounter++;
		}
		else if (hierarchy[i][2] == -1)
		{
			nInsideCounter = 0;
			nCurContourIndex = -1;
		}

		//���������������Ƕ�ά��Ķ���
		if (nInsideCounter >= 2)
		{
			BOOL isQr = IsQrPoint(contours[nCurContourIndex], ImgDst);

			//�����ҵ���������ɫ��λ��
			if (isQr)
			vvPtQr.push_back(contours[nCurContourIndex]);

			nInsideCounter = 0;
			nCurContourIndex = -1;
		}
	}

	return 0;
}


BOOL CQrParse::IsQrPoint(vector<Point2i> & contour, CSmartImage & ImgSrc)
{
	//��С��С�޶�
	RotatedRect rotatedRect = minAreaRect(contour);
	if (rotatedRect.size.height < 10 || rotatedRect.size.width < 10)
	return FALSE;
	const float fRate = rotatedRect.size.width / rotatedRect.size.height;//�L������
	if (fRate > 1.15 || fRate < 0.85)
	return FALSE;

	//���D�����D���ᣬȡ�����΅^��
	const float fRotateAngle = abs(rotatedRect.angle);//�D�����D�Ƕ�

	//ָ����ת����  
	cv::Size src_sz = ImgSrc.size();  
	cv::Size dst_sz(src_sz.width, src_sz.height);  
	cv::Point2d center(src_sz.width / 2., src_sz.height / 2.); 

	//��ȡ��ת����2x3����  
	cv::Mat rot_mat = cv::getRotationMatrix2D(center, fRotateAngle, 1.0);  

	//������ת������з���任  
	CSmartImage ImgDst;//���D��D��
	CSmartImage ImgLocalDst;

	cv::warpAffine(ImgSrc, ImgDst, rot_mat, dst_sz);  

	CRect rcTemp;
	GetSubImage(&ImgDst, &ImgLocalDst, rcTemp, FALSE);
	//����ά�������ͼ�Ͽٳ���
	//cv::Mat cropImg = CropImage(ImgSrc, rotatedRect);
	//int flag = i++;

	//����ڰױ���1:1:3:1:1
	//BOOL bResult = IsQrColorRate(cropImg, flag);
	//return bResult;
	return TRUE;
}

BOOL CQrParse::IsQrColorRate(CSmartImage & ImgSrc, int flag)
{
	/*BOOL x = IsQrColorRateX(ImgSrc, flag);
	if (!x)
	return false;*/

	return IsQrColorRateX(ImgSrc, flag);
	//bool y = IsQrColorRateY(image, flag);
	//return y;
}


BOOL CQrParse::IsQrColorRateX(CSmartImage & ImgSrc, int flag)
{
	int nr = ImgSrc.rows / 2;
	int nc = ImgSrc.cols * ImgSrc.channels();

	vector<int> vValueCount;
	vector<uchar> vColor;
	int count = 0;
	uchar lastColor = 0;

	uchar* data = ImgSrc.ptr<uchar>(nr);
	for (int i = 0; i < nc; i++)
	{
		vColor.push_back(data[i]);
		uchar color = data[i];
		if (color > 0)
			color = 255;

		if (i == 0)
		{
			lastColor = color;
			count++;
		}
		else
		{
			if (lastColor != color)
			{
				vValueCount.push_back(count);
				count = 0;
			}
			count++;
			lastColor = color;
		}
	}

	if (count != 0)
		vValueCount.push_back(count);

	if (vValueCount.size() < 5)
		return false;

	//����ڰױ���1:1:3:1:1
	int index = -1;
	int maxCount = -1;
	for (size_t i = 0; i < vValueCount.size(); i++)
	{
		if (i == 0)
		{
			index = i;
			maxCount = vValueCount[i];
		}
		else
		{
			if (vValueCount[i] > maxCount)
			{
				index = i;
				maxCount = vValueCount[i];
			}
		}
	}

	//��� �ұ� ��������ֵ������
	if (index < 2)
		return false;
	if ((vValueCount.size() - index) < 3)
		return false;

	//�ڰױ���1:1:3:1:1
	float rate = ((float)maxCount) / 3.00;

	cout << "flag:" << flag << " ";

	float rate2 = vValueCount[index - 2] / rate;
	cout << rate2 << " ";
	if (!IsQrRate(rate2))
		return false;

	rate2 = vValueCount[index - 1] / rate;
	cout << rate2 << " ";
	if (!IsQrRate(rate2))
		return false;

	rate2 = vValueCount[index + 1] / rate;
	cout << rate2 << " ";
	if (!IsQrRate(rate2))
		return false;

	rate2 = vValueCount[index + 2] / rate;
	cout << rate2 << " ";
	if (!IsQrRate(rate2))
		return false;

	return true;
}


BOOL CQrParse::IsQrRate(float rate)
{
	//��ű��� ����̫�ϸ�
	return rate > 0.6 && rate < 1.9;
}


BOOL CQrParse::AdjustQrPoint(Point2i * pointSrc, Point2i * pointDest)
{
	bool clockwise = false;
	int index1[3] = { 2,1,0 };
	int index2[3] = { 0,2,1 };
	int index3[3] = { 0,1,2 };

	for (int i = 0; i < 3; i++)
	{
		int *n = index1;
		if(i==0)
			n = index1;
		else if (i == 1)
			n = index2;
		else 
			n = index3;

		double angle = 90;// = QrParse::Angle(pointSrc[n[0]], pointSrc[n[1]], pointSrc[n[2]], clockwise);
		if (angle > 80 && angle < 99)
		{
			pointDest[0] = pointSrc[n[2]];
			if (clockwise)
			{
				pointDest[1] = pointSrc[n[0]];
				pointDest[2] = pointSrc[n[1]];
			}
			else
			{
				pointDest[1] = pointSrc[n[1]];
				pointDest[2] = pointSrc[n[0]];
			}
			return true;
		}
	}
	return true;
}