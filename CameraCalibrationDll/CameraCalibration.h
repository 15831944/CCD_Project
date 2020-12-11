#pragma once
#include "resource.h"
//���C�˶�
// CCameraCalibration �Ի���

#include<iostream>
#include<fstream>

#include <math.h>
#include <iostream>
#include <io.h>

#include "..\CRCDll\\ValueCalculate.h"
#include "..\ImgProcDll\ImgBox.h"
#include "..\ImgProcDll\ImgProc.h"
#include "..\BlendWndDll\MsgBox.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ImgProcDll.lib")
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")

#else
#pragma comment(lib, "..\\Release\\ImgProcDll.lib")
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")

#endif

#include <math.h>

using namespace std;

class AFX_EXT_CLASS CCameraCalibration : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraCalibration)

public:
	CCameraCalibration(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraCalibration();

// �Ի�������
	enum { IDD = IDD_CAMERACALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL _CameraCalibration();
};
