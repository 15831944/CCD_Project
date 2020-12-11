#pragma once

#include "NewPtr.h"
#include "ValRst.h"
#include "SyncCtrl.h"
#include "GdiplusText.h"

#include <math.h>			// ��ѧ��ʽ
#include <regex>			// ����������ʽ
#include <algorithm>		// �㷨ͷ�ļ�

#include <wininet.h>		// ����Э��
#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "wininet.lib")

#ifndef IS_ODD
#define IS_ODD(v)			((v) & 0x01)
#endif // !IS_ODD

#ifndef IS_EVENT
#define IS_EVENT(v)			(!IS_ODD(v))
#endif // !IS_EVENT

// 180 / PI;
#ifndef _180_PI
#define _180_PI				57.295779513082320876798154814105
#endif // !_180_PI

// PI / 180;
#ifndef _PI_180
#define _PI_180				0.0174532925199432957692369076848
#endif // !_PI_180

#ifndef VEC2_MODULUS
#define VEC2_MODULUS(vec2)	sqrt(vec2.x * vec2.x + vec2.y * vec2.y)
#endif // !VEC2_MODULUS


#define MISC_FUN			AFX_API_EXPORT

enum 
{
	FIND_NN_DEC = 0,
	FIND_NN_FLOAT,
	FIND_NN_HEX_0X,
	FIND_NN_HEX
};

enum
{
	EXP_CONSTANT = 1,
	EXP_VARIABLE = 2,
	EXP_NEGTIVE	 = 4,
	EXP_POSITIVE = 8,
	EXP_OPERATOR = 16,
	EXP_ROUND_LEFT = 32,
	EXP_ROUND_RIGHT = 64,
	EXP_SQUARE_LEFT = 128,
	EXP_SQUARE_RIGHT = 256
};


typedef struct _tagFolderInfo
{
	CString strPath;

	BOOL bFolder;
	BOOL bSysFile;
	BOOL bHidden;
	BOOL bReadOnly;
	BOOL bTemporary;
}FOLDER_INFO;

typedef struct _tagExpCalcItem
{
	int nType;		// ����
	int nOps;		// ����������
	int nLevel;		// ���ȼ�
	CString strVal; // ֵ
}EXP_CALC_ITEM;

const int g_nOps = 26;
const CString g_strOp[g_nOps] = {_T("="),  _T("||"), _T("$$"), _T("|"),  _T("^"), _T("$"),
								 _T("=="), _T("!="), _T("<"),  _T("<="), _T(">"), _T(">="),
								 _T("<<"), _T(">>"), _T("+"),  _T("-"),  _T("*"), _T("/"),
								 _T("%"),  _T("!"),  _T("~"),  _T("("),  _T(")"), _T("["), _T("]"),
								 _T(".")};

MISC_FUN DWORD GetLastErrInfo(CString * pErr);		// ȡ�ô�����Ϣ

MISC_FUN BOOL UserDetect(const CString & strUser);	// ������ʹ��������

MISC_FUN BOOL IsCtrlDown(void);						// Ctrl���Ƿ񱻰���
MISC_FUN BOOL IsShfitDown(void);					// Shift���Ƿ񱻰���

MISC_FUN BOOL IsAlpha(TCHAR t);						// �ж��ǲ�����ĸ
MISC_FUN BOOL IsDigit(TCHAR t);						// �ж��ǲ�������
MISC_FUN BOOL IsAlphaDigit(TCHAR t);				// �ж��ǲ�����ĸ������
MISC_FUN void TrimAndUpper(CString & strSrc);		// ȥ����β�ո�ת���ɴ�д

MISC_FUN std::vector<CString> GetSegInfo(const CString & strInfo, TCHAR nMark);			// ȡ�÷ָ��ַ���
MISC_FUN std::vector<CString> GetSegInfoEx(const CString & strInfo, TCHAR nMarks, ...);	// ȡ�÷ָ��ַ���

MISC_FUN BOOL IsFileExist(const CString & strFile);	// �ж��ļ��Ƿ����	
MISC_FUN BOOL CreateFileDir(CString strPath);		// �����ļ���
MISC_FUN BOOL ClearFolder(CString strPath);			// ����ļ���
MISC_FUN BOOL DeleteFolder(CString strPath);		// ɾ���ļ���

MISC_FUN void TraversalFile(const CString & strPath, std::vector<FOLDER_INFO> & vFiles, int nOrder = 0);		// �����ļ����е��ļ�

MISC_FUN BOOL FtpTraversalFile(const CString & strUrl, int nPort,
							   CString strPath, std::vector<FOLDER_INFO> & vFiles,
							   int nOrder = 0, CString * pErr = nullptr);	// �����������ļ����е��ļ�

MISC_FUN void FolderForword(std::vector<FOLDER_INFO> & vFiles);				// �������ļ�������ǰ

MISC_FUN BOOL DownloadFile(const CString & strUrl, const CString & strSavePath, CString * pErr);	// �ӷ����������ļ�������
MISC_FUN BOOL DownloadFile(const CString & strUrl, CNewPtr<char> & Mem, CString * pErr);			// �ӷ����������ļ����ڴ�

MISC_FUN CString GetFileName(const FOLDER_INFO & Info);						// ȡ���ļ���
MISC_FUN void TraceFiles(const std::vector<FOLDER_INFO> & vFiles);			// ��������ļ����

MISC_FUN int Rand(int nMin, int nMax);				// ����һ���������

MISC_FUN void DelayUs(long nTime);					// ��ʱ��λΪuS�ĺ���
MISC_FUN void DelayMs(long nTime);					// ��ʱ��λΪmS�ĺ���

MISC_FUN std::vector<int> GetIndex(CString strText, TCHAR nMark);			// ȡ���������
MISC_FUN CString GetKilobitStr(int nData);									// ȡ����ǧ��λ�ָ����ַ���

MISC_FUN int FindNonNumber(const CString & strData, int nMode);				// �ҳ��������ַ�
MISC_FUN void DeleteSpace(CString & strData);		// ɾ���ַ����еĿո�
MISC_FUN void DeleteZeros(CString & strData);		// ȥ����ͷ���ߵ�С���������0

MISC_FUN int HexStr2int(CString strHex);			// ��ʮ�������ַ���ת��������
MISC_FUN int GetDataMode(const CString & strData);	// ����ֵ: -1. ��������� 0. ʮ�������� 1. ��0x��ʼ��ʮ������ 2. ����0x��ʼ��ʮ������

MISC_FUN CString GetComputerName(CString * pErr);	// ȡ�ü��������
MISC_FUN CString GetCurUserName(CString * pErr);	// ȡ�õ�ǰ������û�����

MISC_FUN CString GetCurTime(void);					// ȡ�õ�ǰϵͳʱ��
MISC_FUN CString GetAppExePath(void);				// ȡ��Ӧ�ó���·��
MISC_FUN CString GetAppIniPath(void);				// ȡ��Ӧ�ó���ini�ļ�·��(Ӧ�ó���·����)
MISC_FUN CString GetSysFontPath(void);				// ȡ��ϵͳ����·��
MISC_FUN int GetDiskFreeSpace(const CString & strPath);		// ��ȡ���̿��ÿռ䵥λ:MB

MISC_FUN int GetOperatorPriority(const CString & op);		// �ж���������ȼ�
MISC_FUN std::vector<EXP_CALC_ITEM> InfixToSuffix(CString strExp, int (*priority)(const CString & o),
												  BOOL (*var)(const CString & v, CString * pInfo), CString * pErr);	// ת�����沨��ʽ
MISC_FUN double CalcRepolish(std::vector<EXP_CALC_ITEM> vItems,
							 double (*var)(const CString & v)) throw(std::out_of_range);			// �����沨����ֵ

MISC_FUN BOOL CalcExpression(const CString & strExp,
							 int (*priority)(const CString & o),
							 BOOL (*varfind)(const CString & v, CString * pInfo),
							 double (*varget)(const CString & v), double & dVal, CString * pErr);	// ������ʽ��ֵ

MISC_FUN CArchive & operator << (CArchive & ar, const std::vector<std::vector<CString>> & vv);	// �洢����ַ���
MISC_FUN CArchive & operator >> (CArchive & ar, std::vector<std::vector<CString>> & vv);		// ���ر���ַ���

template<typename T>
MISC_FUN int FindElement(std::vector<T> & vSrc, const T & val)						// �������в���ָ��Ԫ���Ƿ���
{
	const vector<T>::iterator it = std::find(vSrc.begin(), vSrc.end(), val);

	if (it == vSrc.end())
	{
		return -1;
	}

	return std::distance(vSrc.begin(), it);
}

template<typename T>
MISC_FUN int EraseElement(std::vector<T> & vSrc, const std::vector<int> & vIndex)	// ɾ�������ж��ָ��Ԫ��
{
	const int nSize = vSrc.size();

	std::vector<int> vTmp = vIndex;

	if (vTmp.size() < 1 || nSize < 1)
	{
		return nSize;
	}

	sort(vTmp.begin(), vTmp.end());

	// unique����ֻ�ǰ��ظ���Ԫ�طŵ���������ĩβ
	vTmp.erase(unique(vTmp.begin(), vTmp.end()), vTmp.end());

	const int nErase = vTmp.size();

	for (int i = nErase - 1; i >= 0; i--)
	{
		if (vTmp[i] < nSize)
		{
			vSrc.erase(vSrc.begin() + vTmp[i]);
		}
	}

	return (int)vSrc.size();
}

template<typename T1, typename T2>
MISC_FUN double Get2PtsAngle(T1 pt1, T2 pt2, BOOL bInverseY)			// ����������֮��ˮƽ�߼�ĽǶ�, ʹ�õѿ�������ϵ, Y����Ϊ��
{
	const double dOfst_X = pt2.x - pt1.x;
	const double dOfst_Y = bInverseY? (-pt2.y + pt1.y): (pt2.y - pt1.y);

	const double r = max(sqrt(dOfst_X * dOfst_X + dOfst_Y * dOfst_Y), 0.0001);

	double dAngle = acos(fabs(dOfst_X) / r) * _180_PI;

	if (dOfst_X >= 0)
	{
		if (dOfst_Y < 0)
		{
			dAngle = 360.0 - dAngle;
		}
	}
	else if (dOfst_Y >= 0)
	{
		dAngle = 180.0 - dAngle;
	}
	else
	{
		dAngle = 180.0 + dAngle;
	}
	
	return dAngle;
}


template <typename T1, typename T2>
MISC_FUN T1 PtRotate(const T1 & ptSrc, const T2 & ptCenter, double dAngle, BOOL bInverseY)
{
	const double dRad = dAngle * _PI_180;
	const double dSin = sin(dRad);
	const double dCos = cos(dRad);

	const Point2d ptOfst(ptSrc.x - ptCenter.x, (bInverseY? (-ptSrc.y + ptCenter.y): (ptSrc.y - ptCenter.y)));
	
	Point2d ptDelta(ptOfst.x * dCos - ptOfst.y * dSin, ptOfst.x * dSin + ptOfst.y * dCos);

	if (bInverseY)
	{
		ptDelta.y = -ptDelta.y;
	}

	if (typeid(ptSrc.x) == typeid(double))
	{
		return T1(ptCenter.x + ptDelta.x, ptCenter.y + ptDelta.y);
	}
	else if (typeid(ptSrc.x) == typeid(float))
	{
		return T1((float)(ptCenter.x + ptDelta.x), (float)(ptCenter.y + ptDelta.y));
	}

	return T1(cvRound(ptCenter.x + ptDelta.x), cvRound(ptCenter.y + ptDelta.y));
}


template <typename T1, typename T2>
MISC_FUN double _PointDistance(const T1 & pt1, const T2 & pt2)
{
	const double dx = pt2.x - pt1.x;
	const double dy = pt2.y - pt1.y;
	
	return sqrt(dx * dx + dy * dy);
}
