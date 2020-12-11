#pragma once

#include "resource.h"

#include "..\CRCDll\\ValueCalculate.h"
#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"
#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

// CQrParse �Ի���
using namespace std;

class AFX_EXT_CLASS CQrParse : public CDialogEx
{
	DECLARE_DYNAMIC(CQrParse)

public:
	CQrParse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQrParse();

// �Ի�������
	enum { IDD = IDD_QRPARSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int FindQrPoint(CSmartImage * pImgSrc, vector<vector<Point2i>> & qrPoint);//���Ҷ�ά���ǵ�

	BOOL IsQrPoint(vector<Point2i> & contour, CSmartImage & img);//�ж��Ƿ��Ƕ�ά���ǵ㣨���㣩

	BOOL IsQrColorRate(CSmartImage & image, int flag);//���ݻ�ȡ����ͼ���жϱ����Ƿ�Ϊ1��1��3��1��1

	BOOL IsQrColorRateX(CSmartImage & image, int flag);//�жϺ������

	BOOL IsQrRate(float rate);//ȷ�ϱ��������ǲ�������ȫһ�£�������һ���ݲ�

	BOOL AdjustQrPoint(Point2i * pointSrc, Point2i * pointDest);//�ҵ���ά�����ϽǵĶ���

};
