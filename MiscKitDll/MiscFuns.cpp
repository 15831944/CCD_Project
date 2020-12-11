#include "stdafx.h"
#include "MiscFuns.h"


DWORD GetLastErrInfo(CString * pErr)
{
	const DWORD nErr = GetLastError();

	if (nullptr == pErr)
	{
		return nErr;
	}

	CString &strTmp = *pErr;

	if (nErr >= INTERNET_ERROR_BASE)
	{
		WCHAR szErr[512] = {0};
		DWORD dwSize = 512;
		DWORD dwLastErr = 0;

		switch (nErr)
		{
		case ERROR_INTERNET_CANNOT_CONNECT:
			strTmp.Format(_T("Err:%d\n%s"), nErr, _T("The attempt to connect to the server failed."));
			break;

		case ERROR_FTP_DROPPED:
			strTmp.Format(_T("Err:%d\n%s"), nErr, _T("The FTP operation was not completed because the session was aborted."));
			break;			

		default:
			InternetGetLastResponseInfo(&dwLastErr, szErr, &dwSize);
			strTmp.Format(_T("Err:%d\n%s"), nErr, szErr);

			break;
		}
	}
	else
	{
		LPVOID lpMsgBuf = nullptr;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			nErr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			nullptr);

		strTmp.Format(_T("Err:%d\n%s"), nErr, lpMsgBuf);

		LocalFree(lpMsgBuf);
	}

	const int nLength = strTmp.GetLength();

	if ('\r' == strTmp[nLength - 2] && '\n' == strTmp[nLength - 1])
	{
		strTmp.Delete(nLength - 2, 2);
	}

	TRACE(_T("\n") + strTmp);

	return nErr;
}


BOOL UserDetect(const CString & strUser)
{
#ifdef _DEBUG
	return TRUE;
#else
	const CString strName = GetCurUserName(nullptr);

	return strName == strUser;
#endif
}


BOOL IsCtrlDown(void)
{
	const BOOL bCtrlDown = GetAsyncKeyState(VK_CONTROL) & 0x8000;

	return bCtrlDown? TRUE: FALSE;
}


BOOL IsShfitDown(void)
{
	const BOOL bCtrlDown = GetAsyncKeyState(VK_SHIFT) & 0x8000;

	return bCtrlDown? TRUE: FALSE;
}


BOOL IsAlpha(TCHAR t)
{
	if (t > 255)
	{
		return TRUE;
	}
	
	return isalpha(t)? TRUE: FALSE;
}


BOOL IsDigit(TCHAR t)
{
	if (t > 255)
	{
		return FALSE;
	}
	
	return isdigit(t)? TRUE: FALSE;
}


BOOL IsAlphaDigit(TCHAR t)
{
	if (t > 255)
	{
		return TRUE;
	}

	return isalnum(t)? TRUE: FALSE;
}


void TrimAndUpper(CString & strSrc)
{
	strSrc.Trim();
	strSrc.MakeUpper();
}


std::vector<CString> GetSegInfo(const CString & strInfo, TCHAR nMark)
{
	std::vector<CString> vRetVal;

	int nStart = 0;
	int nPos = -1;

	while (TRUE)
	{
		nPos = strInfo.Find(nMark, nStart);

		if (nPos >= 0)
		{
			vRetVal.push_back(strInfo.Mid(nStart, nPos - nStart));
			nStart = nPos + 1;
		}
		else
		{
			const int nLen = strInfo.GetLength();

			if (nStart < nLen)
			{
				vRetVal.push_back(strInfo.Mid(nStart, nLen - nStart));
			}

			break;
		}
	}

	return vRetVal;
}


std::vector<CString> GetSegInfoEx(const CString & strInfo, TCHAR nMarks, ...)
{
	va_list ap = nullptr;
	va_start(ap, nMarks);

	CNewPtr<TCHAR> NewPtr(nMarks);

	for (int i = 0; i < nMarks; i++)
	{
		NewPtr[i] = va_arg(ap, TCHAR);
	}

	va_end(ap);

	CString strSrc = strInfo;

	std::vector<CString> vRetVal;

	const int nLength = strInfo.GetLength();

	int k = 0;

	for (int i = 0; i < nLength; i++)
	{
		BOOL bFind = FALSE;

		for (int j = 0; j < nMarks; j++)
		{
			if (strInfo[i] == NewPtr[j])
			{
				bFind = TRUE;
				break;
			}
		}

		if (bFind)
		{
			const CString strTmp = strInfo.Mid(k, i - k);

			if (FALSE == strTmp.IsEmpty())
			{
				vRetVal.push_back(strTmp);
			}

			k = i + 1;
		}
	}

	if (k < nLength)
	{
		const CString strTmp = strInfo.Mid(k, nLength - k);

		if (FALSE == strTmp.IsEmpty())
		{
			vRetVal.push_back(strTmp);
		}
	}

	return vRetVal;
}


BOOL IsFileExist(const CString & strFile)
{
	const DWORD dwAttrib = GetFileAttributes(strFile);

	return (INVALID_FILE_ATTRIBUTES != dwAttrib);
}


BOOL CreateFileDir(CString strPath)
{
	if (PathIsDirectory(strPath))
	{
		return TRUE;
	}

	const std::vector<CString> vDir = GetSegInfo(strPath, '\\');

	const int nDirs = vDir.size();

	strPath.Empty();

	for (int i = 0; i < nDirs; i++)
	{
		strPath.Append(vDir[i]);

		if (!PathIsDirectory(strPath))
		{
			if (!CreateDirectory(strPath, nullptr))
			{
				return FALSE;
			}
		}

		if (i < nDirs - 1)
		{
			strPath.AppendChar('\\');
		}
	}

	return TRUE;
}


BOOL ClearFolder(CString strPath)
{
	CFileFind Finder;

	BOOL bFind = Finder.FindFile(strPath + _T("\\*.*"));

	while (bFind)
	{
		bFind = Finder.FindNextFile();

		if (Finder.IsDirectory())	// �����ļ����е��ļ�
		{
			if (Finder.IsDots())
			{
				continue;
			}

			const CString strFile = Finder.GetFilePath();

			ClearFolder(Finder.GetFilePath());		// �ݹ�ɾ���ļ���

			if (!RemoveDirectory(strFile))
			{
				return FALSE;
			}
		}
		else // ɾ���ļ�
		{
			const CString strFile = Finder.GetFilePath();

			if (!DeleteFile(strFile))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}


BOOL DeleteFolder(CString strPath)
{
	if (!ClearFolder(strPath))
	{
		return FALSE;
	}

	if (!RemoveDirectory(strPath))
	{
		return FALSE;
	}

	return TRUE;
}


void TraversalFile(const CString & strPath, std::vector<FOLDER_INFO> & vFiles, int nOrder)
{
	FOLDER_INFO Info;

	if (strPath.IsEmpty())
	{
		return;
	}

	CFileFind Finder;
	BOOL bNotEmpty = Finder.FindFile(strPath + _T("\\*.*"));	// ���ļ���, ��ʼ����

	while (bNotEmpty)
	{ 
		bNotEmpty = Finder.FindNextFile();	// �����ļ�
		const CString strFileName = Finder.GetFilePath();		// ��ȡ�ļ���·�����������ļ��У��������ļ�

		if (Finder.IsDirectory())
		{
			// �ݹ�����û��ļ���
			if (!Finder.IsDots())
			{
				Info.strPath	= strFileName;

				Info.bFolder	= TRUE;
				Info.bSysFile	= Finder.IsSystem();
				Info.bHidden	= Finder.IsHidden();
				Info.bReadOnly	= Finder.IsReadOnly();
				Info.bTemporary	= Finder.IsTemporary();

				vFiles.push_back(Info);

				TraversalFile(strFileName + _T("\\"), vFiles, nOrder);
			}
		}
		else
		{
			// ������ļ�������ļ��б�
			Info.strPath	= strFileName;

			Info.bFolder	= FALSE;
			Info.bSysFile	= Finder.IsSystem();
			Info.bHidden	= Finder.IsHidden();
			Info.bReadOnly	= Finder.IsReadOnly();
			Info.bTemporary	= Finder.IsTemporary();

			vFiles.push_back(Info);
		}
	}

	if (nOrder < 0)
	{
		sort(vFiles.begin(), vFiles.end(),
			[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath < obj2.strPath;});
	}
	else if (nOrder > 0)
	{
		sort(vFiles.begin(), vFiles.end(),
			[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath > obj2.strPath;});
	}
}


BOOL FtpTraversalFile(const CString & strUrl, int nPort,
					  CString strPath, std::vector<FOLDER_INFO> & vFiles, int nOrder, CString * pErr)
{
	const HINTERNET hSession = InternetOpen(_T("RookIE/1.0"), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);

	if (nullptr == hSession)
	{
		GetLastErrInfo(pErr);

		return FALSE;
	}

	const HINTERNET hUrl = InternetConnect(hSession, strUrl, nPort, nullptr, nullptr,
		INTERNET_SERVICE_FTP, INTERNET_FLAG_EXISTING_CONNECT || INTERNET_FLAG_PASSIVE, 0);

	if (nullptr == hUrl)
	{
		GetLastErrInfo(pErr);
		InternetCloseHandle(hSession);

		return FALSE;
	}

	strPath.Replace('\\', '/');

	WIN32_FIND_DATA fd;
	const HINTERNET hFile = FtpFindFirstFile(hUrl, strPath + _T("/*.*"), &fd, INTERNET_FLAG_RELOAD, 0);

	if (nullptr != hFile)
	{
		FOLDER_INFO Info;

		Info.strPath.Format(_T("%s/%s"), strPath, fd.cFileName);

		Info.bFolder	= fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		Info.bSysFile	= fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
		Info.bHidden	= fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
		Info.bReadOnly	= fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
		Info.bTemporary	= fd.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY;

		vFiles.push_back(Info);

		if (Info.bFolder)
		{
			// �ݹ�����û��ļ���
			FtpTraversalFile(strUrl, nPort, Info.strPath, vFiles, nOrder);
		}

		while (InternetFindNextFile(hFile, &fd))
		{
			Info.strPath.Format(_T("%s/%s"), strPath, fd.cFileName);

			Info.bFolder	= fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			Info.bSysFile	= fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
			Info.bHidden	= fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
			Info.bReadOnly	= fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
			Info.bTemporary	= fd.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY;

			vFiles.push_back(Info);

			if (Info.bFolder)
			{
				// �ݹ�����û��ļ���
				FtpTraversalFile(strUrl, nPort, Info.strPath, vFiles, nOrder);
			}
		}

		InternetCloseHandle(hFile);
	}
	else
	{
		const DWORD dwErr = GetLastErrInfo(pErr);

		if (ERROR_NO_MORE_FILES != dwErr)
		{
			InternetCloseHandle(hUrl);
			InternetCloseHandle(hSession);

			return FALSE;
		}
	}

	InternetCloseHandle(hUrl);
	InternetCloseHandle(hSession);

	if (nOrder < 0)
	{
		sort(vFiles.begin(), vFiles.end(),
			[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath < obj2.strPath;});
	}
	else if (nOrder > 0)
	{
		sort(vFiles.begin(), vFiles.end(),
			[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath > obj2.strPath;});
	}

	return TRUE;
}


void FolderForword(std::vector<FOLDER_INFO> & vFiles)
{
	const int nInfos = vFiles.size();

	if (nInfos < 1)
	{
		return;
	}

	std::vector<FOLDER_INFO> vTmp;

	for (int i = nInfos - 1; i >= 0; i--)
	{
		if (vFiles[i].bFolder)
		{
			vTmp.push_back(vFiles[i]);
			vFiles.erase(vFiles.begin() + i);
		}
	}

	sort(vTmp.begin(), vTmp.end(),
		[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath < obj2.strPath;});

	sort(vFiles.begin(), vFiles.end(),
		[](const FOLDER_INFO & obj1, const FOLDER_INFO & obj2){return obj1.strPath < obj2.strPath;});

	vFiles.insert(vFiles.begin(), vTmp.begin(), vTmp.end());
}


BOOL DownloadFile(const CString & strUrl, const CString & strSavePath, CString * pErr)
{
#define MAX_BLK_SIZE 4094

	const HINTERNET hSession = InternetOpen(_T("RookIE/1.0"), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);

	if (nullptr == hSession)
	{
		GetLastErrInfo(pErr);

		return FALSE;
	}

	const HINTERNET hUrl = InternetOpenUrl(hSession, strUrl, nullptr, 0, INTERNET_FLAG_DONT_CACHE, 0);

	if (nullptr == hUrl)
	{
		GetLastErrInfo(pErr);

		InternetCloseHandle(hSession);

		return FALSE;
	}

	USES_CONVERSION;

	FILE *pf;
	const errno_t err = fopen_s(&pf, W2A(strSavePath), "wb");

	if (nullptr == pf)
	{
		GetLastErrInfo(pErr);

		InternetCloseHandle(hUrl);
		InternetCloseHandle(hSession);

		return FALSE;
	}

	ULONG nNumber = 1;
	CNewPtr<BYTE> Ptr(MAX_BLK_SIZE, 0);

	while (nNumber > 0)
	{
		InternetReadFile(hUrl, Ptr.m_pNew, Ptr.m_nSize - 1, &nNumber);
		fwrite(Ptr.m_pNew, sizeof(char), nNumber, pf);
	}

	fclose(pf);

	InternetCloseHandle(hUrl);
	InternetCloseHandle(hSession);

	return TRUE;
}


BOOL DownloadFile(const CString & strUrl, CNewPtr<char> & Mem, CString * pErr)
{
#define MAX_BLK_SIZE 4094

	const HINTERNET hSession = InternetOpen(_T("RookIE/1.0"), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);

	if (nullptr == hSession)
	{
		GetLastErrInfo(pErr);

		return FALSE;
	}

	const HINTERNET hUrl = InternetOpenUrl(hSession, strUrl, nullptr, 0, INTERNET_FLAG_DONT_CACHE, 0);

	if (nullptr == hUrl)
	{
		GetLastErrInfo(pErr);

		InternetCloseHandle(hSession);

		return FALSE;
	}

	DWORD nNumber = 0;
	CNewPtr<char> NewPtr(MAX_BLK_SIZE, 0);

	do 
	{
		InternetReadFile(hUrl, NewPtr.m_pNew, NewPtr.m_nSize - 1, &nNumber);
		NewPtr.m_nSize = nNumber;
		Mem += NewPtr;

		NewPtr.m_nSize = MAX_BLK_SIZE;
	} while (nNumber > 0);

	InternetCloseHandle(hUrl);
	InternetCloseHandle(hSession);

	return TRUE;
}


CString GetFileName(const FOLDER_INFO & Info)
{
	const std::vector<CString> vSegInfo = GetSegInfoEx(Info.strPath, '\\', '/');

	if (vSegInfo.size())
	{
		return vSegInfo.back();
	}
	else
	{
		return _T("");
	}
}


void TraceFiles(const std::vector<FOLDER_INFO> & vFiles)
{
#ifdef _DEBUG
	const int nInfos = vFiles.size();

	TRACE(_T("\nTraceFiles: %d items."), nInfos);

	for (int i = 0; i < nInfos; i++)
	{
		if (vFiles[i].bFolder)
		{
			TRACE(_T("\nFolder:%s"), vFiles[i].strPath);
		}
		else
		{
			TRACE(_T("\nFile:%s"), vFiles[i].strPath);
		}
	}

	TRACE(_T("\n"));
#else
	return;
#endif // _DEBUG	
}


int Rand(int nMin, int nMax)
{
	if (nMin > nMax)
	{
		std::swap(nMin, nMax);
	}

	srand((unsigned)time(nullptr) + rand());

	const int nRand = rand() % (nMax - nMin + 1) + nMin;

	return nRand;
}


void DelayUs(long nTime)
{
	LARGE_INTEGER lTemp;

	LONGLONG QStart = 0;
	LONGLONG QEnd = 0;
	double dFreq = 0;
	double dTime = 0;

	QueryPerformanceFrequency(&lTemp);
	dFreq = (double)lTemp.QuadPart;

	QueryPerformanceCounter(&lTemp);
	QStart = lTemp.QuadPart;

	do
	{
		QueryPerformanceCounter(&lTemp);
		QEnd = lTemp.QuadPart;
		dTime = (double)(QEnd - QStart) / dFreq;
		dTime *= 1000000;
	} while (dTime < nTime);
}


void DelayMs(long nTime)
{
	LARGE_INTEGER lTemp;

	LONGLONG QStart = 0;
	LONGLONG QEnd = 0;
	double dFreq = 0;
	double dTime = 0;

	QueryPerformanceFrequency(&lTemp);
	dFreq = (double)lTemp.QuadPart;

	QueryPerformanceCounter(&lTemp);
	QStart = lTemp.QuadPart;

	do
	{
		QueryPerformanceCounter(&lTemp);
		QEnd = lTemp.QuadPart;
		dTime = (double)(QEnd - QStart) / dFreq;
		dTime *= 1000;
	} while (dTime < nTime);
}


std::vector<int> GetIndex(CString strText, TCHAR nMark)
{
	strText.Trim();

	std::vector<int> vRetVal;
	std::vector<CString> vValues = GetSegInfo(strText, nMark);

	const int nValues = vValues.size();

	for (int i = 0; i < nValues; i++)
	{
		const int nLine = vValues[i].Find('-');

		if (nLine >= 0)
		{
			const CString strStart = vValues[i].Left(nLine);

			const int nStart = _ttoi(strStart);

			vValues[i].Delete(0, nLine + 1);
			const CString strEnd = vValues[i];

			const int nEnd = _ttoi(strEnd);

			for (int j = nStart; j <= nEnd; j++)
			{
				vRetVal.push_back(j);
			}
		}
		else
		{
			const int nValue = _ttoi(vValues[i]);

			vRetVal.push_back(nValue);
		}
	}

	return vRetVal;
}


CString GetKilobitStr(int nData)
{
	CString strRetVal;
	strRetVal.Format(_T("%d"), nData);

	strRetVal.MakeReverse();

	const int nLength = strRetVal.GetLength();

	for (int i = nLength - (nLength % 3); i >= 3; i -= 3)
	{
		if (nLength > 3)
		{
			strRetVal.Insert(i, ',');
		}
	}

	strRetVal.MakeReverse();

	if (',' == strRetVal[0])
	{
		strRetVal.Delete(0, 1);
	}

	return strRetVal;
}


int FindNonNumber(const CString & strData, int nMode)
{
	const int nLength = strData.GetLength();

	// ���ʮ��������
	if (FIND_NN_HEX_0X == nMode || FIND_NN_HEX == nMode)
	{
		int nStart = 0;

		if (FIND_NN_HEX_0X == nMode && nLength > 2)
		{
			if ('0' != strData[0])
			{
				return strData[0];
			}

			if ('x' != (strData[1] | 32))
			{
				return strData[1];
			}

			nStart = 2;
		}

		for (int i = nStart; i < nLength; i++)
		{
			if (strData[i] < '0' || strData[i] > '9')
			{
				const int nLower = (strData[i] | 32);

				if (nLower < 'a' || nLower > 'f')
				{
					return nLower;
				}
			}
		}
	}
	else
	{
		int nDot = 0;
		int nSign = 0;

		for (int i = 0; i < nLength; i++)
		{
			const int t = strData[i];

			if (t < '0' || t > '9')
			{
				BOOL bContinue = TRUE;

				switch (t)
				{
				case '+':
				case '-':
					nSign++;

					if (i > 0)
					{
						bContinue = FALSE;
					}
					break;

				case '.':
					if (FIND_NN_FLOAT == nMode)
					{
						nDot++;

						if (0 == i || nDot > 1)
						{
							bContinue = FALSE;
						}
						else if (1 == i && 1 == nSign)
						{
							bContinue = FALSE;
						}
					}
					else
					{
						bContinue = FALSE;
					}
					
					break;

				default:
					bContinue = FALSE;

					break;
				}

				if (!bContinue)
				{
					return t;
				}
			}
		}
	}

	return 0;
}


void DeleteSpace(CString & strData)
{
	strData.Remove(' ');
}


void DeleteZeros(CString & strData)
{
	int nLength = strData.GetLength();

	if (0 == nLength)
	{
		return;
	}

	int nStart = 0;

	if ('+' == strData[0] || '-' == strData[0])
	{
		nStart = 1;
	}

	for (int i = nStart; i < nLength - 1; i++)
	{
		if ('0' != strData[i])
		{
			break;
		}

		if (i == nStart)
		{
			CString strHex = strData.Mid(i, 2);
			strHex.MakeLower();

			if (_T("0x") == strHex)
			{
				break;
			}
		}

		if ('0' == strData[i] && '.' != strData[i + 1])
		{
			strData.Delete(i, 1);

			i--;
			nLength--;
		}
	}

	const int nDot = strData.Find('.');

	if (nDot > 0)
	{
		for (int i = nLength - 1; i >= 0; i--)
		{
			if ('0' == strData[i])
			{
				strData.Delete(i, 1);
			}
			else
			{
				if ('.' == strData[i])
				{
					strData.Delete(i, 1);
				}

				break;
			}
		}
	}
}


int HexStr2int(CString strHex)
{
	DeleteSpace(strHex);

	strHex.MakeLower();

	const CString strHead = strHex.Left(2);

	int nOfst = 0;

	if (_T("0x") == strHead)
	{
		nOfst = 2;
	}

	int nRetVal = 0;

	const int nLength = strHex.GetLength();

	for (int i = nOfst; i < nLength; i++)
	{
		int nTmp = 0;

		if (strHex[i] >= 'a' && strHex[i] <= 'f')
		{
			nTmp = strHex[i] - 'a' + 10;
		}
		else if (strHex[i] >= '0' && strHex[i] <= '9')
		{
			nTmp = strHex[i] - '0';
		}
		else
		{
			continue;
		}

		nRetVal <<= 4;
		nRetVal += nTmp;
	}

	return nRetVal;
}


int GetDataMode(const CString & strData)
{
	int nHexMode = 0;

	if ('0' == strData[0] && 'x' == (strData[1] | 32))
	{
		nHexMode = 1;
	}
	
	const int nLen = strData.GetLength();

	for (int i = (nHexMode << 1); i < nLen; i++)
	{
		if (strData[i] < '0' || strData[i] > '9')
		{
			const char nLower = (strData[i] | 32);

			if (nLower < 'a' || nLower > 'f')
			{
				return -1;
			}
			else
			{
				nHexMode = 2;
			}					
		}
	}

	return nHexMode;
}


CString GetComputerName(CString * pErr)
{
	const int MAX_BUFFER_LEN = 500;

	LPWSTR szBuffer = (LPWSTR)malloc(MAX_BUFFER_LEN);
	DWORD dwNameLen = MAX_BUFFER_LEN;

	CString strName;

	if (ERROR_SUCCESS == GetComputerName(szBuffer, &dwNameLen))
	{
		strName = szBuffer;
	}
	else
	{
		GetLastErrInfo(pErr);
	}

	if (nullptr != szBuffer)
	{
		free(szBuffer);
	}

	return strName;
}


CString GetCurUserName(CString * pErr)
{
	const int MAX_BUFFER_LEN = 500;

	LPWSTR szBuffer = (LPWSTR)malloc(MAX_BUFFER_LEN);
	DWORD dwNameLen = MAX_BUFFER_LEN;

	CString strName;

	if (ERROR_SUCCESS == GetUserName(szBuffer, &dwNameLen))
	{
		strName = szBuffer;
	}
	else
	{
		GetLastErrInfo(pErr);
	}

	if (nullptr != szBuffer)
	{
		free(szBuffer);
	}

	return strName;
}


CString GetCurTime(void)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strRetVal;
	strRetVal.Format(_T("%d-%02d-%02d %02d:%02:d%0:2d.%03d"), st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return strRetVal;
}


CString GetAppExePath(void)
{
	CString strPath;
	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer();

	const int nPos = strPath.ReverseFind('\\');

	strPath = strPath.Left(nPos);

	return strPath;
}


CString GetAppIniPath(void)
{
	CString strPath;
	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer();
	strPath.Replace(_T(".exe"), _T(".ini"));

	return strPath;
}


CString GetSysFontPath(void)
{
	TCHAR sWinDir[MAX_PATH];

	GetWindowsDirectory(sWinDir,MAX_PATH);

	CString sFontDir(sWinDir);
	sFontDir += _T("\\Fonts");

	return sFontDir;
}


int GetDiskFreeSpace(const CString & strPath)
{
	const int nPos = strPath.Find(':');

	if (nPos < 1)
	{
		return 0;
	}

	const CString strRoot = strPath.Left(nPos + 1);

	int nSpace = 0;

	WCHAR Drive[MAX_PATH] = {0};				// ��ʼ���������Դ洢�̷���Ϣ
	GetLogicalDriveStrings(MAX_PATH, Drive);	// ��ñ��������̷�����Drive������

	CString strDrive;

	int i = 0;
	while ('\0' != Drive[i - 1] || '\0' != Drive[i])	// �������鳢�Եõ��̷���Ϣ��������߽Է���������������ͷ
	{
		strDrive = L"";
		strDrive = Drive[i];

		strDrive = strDrive + L":";				// ���̷���Ϣ�ĸ�ʽ����Ϊ��C:�����ָ�ʽ������ΪGetDiskFreeSpaceEx�����ĵ�һ������
		i += 4;

		if (strRoot != strDrive)
		{
			continue;
		}

		ULARGE_INTEGER nFreeBytesAvailable;
		ULARGE_INTEGER nTotalNumberOfBytes;
		ULARGE_INTEGER nTotalNumberOfFreeBytes;

		// ����GetDiskFreeSpaceEx�������ָ��������Ϣ
		if (GetDiskFreeSpaceEx(strDrive,
			&nFreeBytesAvailable,
			&nTotalNumberOfBytes,
			&nTotalNumberOfFreeBytes))
		{
			const long nWholespace = (long)(nTotalNumberOfBytes.QuadPart / 1024 / 1024);	// �õ������ܿռ䣬��λΪMB
			const long nFreespace = (long)(nTotalNumberOfFreeBytes.QuadPart / 1024 / 1024);

			nSpace = (int)nFreespace;
		}
	}

	return nSpace;
}


int GetOperatorPriority(const CString & op)
{
	int nLevel = 0;

	if (_T("=") == op)
	{
		nLevel = 2;
	}
	else if (_T("||") == op)
	{
		nLevel = 4;
	}
	else if (_T("$$") == op)
	{
		nLevel = 5;
	}
	else if (_T("|") == op)
	{
		nLevel = 6;
	}
	else if (_T("^") == op)
	{
		nLevel = 7;
	}
	else if (_T("$") == op)
	{
		nLevel = 8;
	}
	else if (_T("==") == op || _T("!=") == op)
	{
		nLevel = 9;
	}
	else if (_T("<") == op || _T("<=") == op || _T(">") == op || _T(">=") == op)
	{
		nLevel = 10;
	}
	else if (_T("<<") == op || _T(">>") == op)
	{
		nLevel = 11;
	}
	else if (_T("+") == op || _T("-") == op)
	{
		nLevel = 12;
	}
	else if (_T("*") == op || _T("/") == op || _T("%") == op)
	{
		nLevel = 13;
	}
	else if (_T("!") == op || _T("~") == op)
	{
		nLevel = 15;
	}
	else if (_T(".") == op)
	{
		nLevel = 16;
	}
	else if (_T("++") == op || _T("--") == op)
	{
		nLevel = 17;
	}
// 	else if (_T("[") == op || _T("]") == op)
// 	{
// 		nLevel = 17;
// 	}
// 	else if (_T("(") == op || _T(")") == op)
// 	{
// 		nLevel = 18;
// 	}

	return nLevel;
}


std::vector<EXP_CALC_ITEM> InfixToSuffix(CString strExp, int (*priority)(const CString & o),
										 BOOL (*var)(const CString & v, CString * pInfo), CString * pErr)
{
#define THROW_ERR_INFO(info)	if (nullptr != pErr) {s1.clear(); *pErr = info; return s1;}

	std::vector<EXP_CALC_ITEM> s1;	// ������ʽ
	std::vector<EXP_CALC_ITEM> s2;	// �ָ��, �����, +, -

// 	DeleteSpace(strExp);
// 
// 	int nLastType = EXP_OPERATOR;
// 	int nNeedRightBracket[2] = {0, 0};
// 
// 	const int nLength = strExp.GetLength();
// 
// 	for (int i = 0; i < nLength; i++)
// 	{
// 		const TCHAR t = strExp[i];
// 
// 		if (IsDigit(t))		// ����, ֱ����s1
// 		{
// 			if (!((EXP_OPERATOR | EXP_NEGTIVE | EXP_POSITIVE | EXP_ROUND_LEFT | EXP_SQUARE_LEFT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("����֮ǰ������������������� �� ����Ž�������"))
// 			}
// 
// 			int nDot = 0;
// 			CString strConst;
// 			strConst.AppendChar(t);
// 
// 			for (int j = i + 1; j < nLength; j++)
// 			{
// 				const TCHAR v = strExp[j];
// 
// 				if (IsDigit(v) || '.' == v)
// 				{
// 					if ('.' == v)
// 					{
// 						nDot++;
// 					}
// 
// 					if (nDot > 1)
// 					{
// 						THROW_ERR_INFO(_T("�������ܰ�����Ա�ָ�����"))
// 					}
// 
// 					strConst.AppendChar(v);
// 
// 					i = j;
// 				}
// 				else
// 				{
// 					break;
// 				}
// 			}
// 
// 			const EXP_CALC_ITEM it = {EXP_CONSTANT, 0, 0, strConst};
// 
// 			s1.push_back(it);
// 		}
// 		else if (IsAlpha(t))	// ����, ֱ����s1
// 		{
// 			if (EXP_CONSTANT == nLastType)
// 			{
// 				THROW_ERR_INFO(_T("���������б�����Ա��"))
// 			}
// 			else if (!((EXP_OPERATOR | EXP_DOT | EXP_NEGTIVE | EXP_POSITIVE | EXP_ROUND_LEFT | EXP_SQUARE_LEFT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("����֮ǰ���������������Ա�ָ����������� �� ����Ž�������"))
// 			}
// 
// 			CString strVar;
// 			strVar.AppendChar(t);
// 
// 			for (int j = i + 1; j < nLength; j++)
// 			{
// 				const TCHAR v = strExp[j];
// 
// 				if (IsAlphaDigit(v) || '_' == v || v > 128)
// 				{
// 					strVar.AppendChar(v);
// 
// 					i = j;
// 				}
// 				else
// 				{
// 					break;
// 				}
// 			}
// 
// 			if (!var(strVar, pErr))
// 			{
// 				s1.clear();
// 
// 				return s1;
// 			}
// 
// 			const EXP_CALC_ITEM it = {EXP_VARIABLE, TRUE, strVar};
// 
// 			if (s1.empty())
// 			{
// 				s1.push_back(it);
// 			}
// 			else
// 			{
// 				EXP_CALC_ITEM &it_back = s1.back();
// 
// 				if (FALSE == it_back.bNumEnd)
// 				{
// 					it_back.nType = EXP_VARIABLE;
// 					it_back.bNumEnd = TRUE;
// 					it_back.strVal.Append(it.strVal);
// 				}
// 				else
// 				{
// 					s1.push_back(it);
// 				}
// 			}
// 
// 			nLastType = EXP_VARIABLE;
// 		}
// 		else if ('.' == t)	// ��Ա�ָ���
// 		{
// 			if (!((EXP_VARIABLE | EXP_SQUARE_RIGHT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("��Ա�ָ���֮ǰ�����Ǳ��� �� ����Ž�������"))
// 			}
// 
// 			const CString strOp = strExp.Mid(i, 1);
// 
// 			const EXP_CALC_ITEM it = {EXP_DOT, TRUE, strOp};
// 
// 			if (s2.empty())	// ���s2Ϊ��, �������ֱ����ջ
// 			{
// 				s2.push_back(it);
// 			}
// 			else
// 			{
// 				const int nCurOp = priority(strOp);
// 
// 				int nTopOp = priority(s2.back().strVal);
// 
// 				if (nCurOp >= nTopOp)  // ��ǰ����������������ȼ���С��s2ջ�������
// 				{
// 					s2.push_back(it);
// 				}
// 				else // ��ǰ����������������ȼ�С��s2ջ�����������ջ�������һֱ��ջѹ��s1��
// 				{
// 					s1.push_back(s2.back());
// 					s2.pop_back();
// 
// 					while (!s2.empty())
// 					{
// 						nTopOp = priority(s2.back().strVal);
// 
// 						if (nCurOp < nTopOp)
// 						{
// 							s1.push_back(s2.back());
// 							s2.pop_back();
// 						}
// 						else
// 						{
// 							break;
// 						}
// 					}
// 
// 					s2.push_back(it);
// 				}
// 			}
// 
// 			nLastType = EXP_DOT;
// 		}
// 		else if ('[' == t)	// ���������Ž���, ����ѹ��s2�ȴ���Ե�������
// 		{
// 			if (!((EXP_VARIABLE) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("����Ž�����֮ǰ�����Ǳ�����"))
// 			}
// 
// 			nNeedRightBracket[0]++;
// 
// 			const EXP_CALC_ITEM it = {EXP_SQUARE_LEFT, TRUE, strExp.Mid(i, 1)};
// 
// 			s2.push_back(it);
// 
// 			nLastType = EXP_SQUARE_LEFT;
// 		}
// 		else if (']' == t)	// ���������Ž���
// 		{
// 			if (!((EXP_CONSTANT | EXP_VARIABLE | EXP_ROUND_RIGHT | EXP_SQUARE_RIGHT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("����Ž�����֮ǰ�����ǳ����������������� �� ����Ž�������"))
// 			}
// 
// 			nNeedRightBracket[0]--;
// 
// 			if (nNeedRightBracket[0] < 0)
// 			{
// 				THROW_ERR_INFO(_T("����Ž�����������Ž�������ƥ�䡣"))
// 			}
// 			else
// 			{
// 				// ���������������Ž���, ��Ҫs2�е������һֱ��ջѹ��s1��
// 				// ֱ����������Ž��������Ҹ��������Ҫ��s1, ����������Ų�һ��
// 				int nLeft = 0;
// 				int nRight = 0;
// 
// 				while (!s2.empty())
// 				{
// 					EXP_CALC_ITEM &it_back = s2.back();
// 
// 					if (_T("[") != it_back.strVal)
// 					{
// 						if (_T("(") == it_back.strVal)
// 						{
// 							nLeft++;
// 						}
// 						else if (_T(")") == it_back.strVal)
// 						{
// 							nRight++;
// 						}
// 
// 						s1.push_back(s2.back());
// 						s2.pop_back();
// 					}
// 					else
// 					{
// 						s1.push_back(s2.back());
// 						s2.pop_back();
// 
// 						break;
// 					}
// 				}
// 
// 				if (nLeft != nRight)
// 				{
// 					THROW_ERR_INFO(_T("�������������Ų�ƥ�䡣"))
// 				}
// 			}
// 
// 			nLastType = EXP_SQUARE_RIGHT;
// 		}
// 		else if ('(' == t)	// �����������, ����ѹ��s2�ȴ���Ե�������
// 		{
// 			if (!((EXP_OPERATOR | EXP_NEGTIVE | EXP_POSITIVE | EXP_ROUND_LEFT | EXP_SQUARE_LEFT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("������֮ǰ������������������� �� ����Ž�������"))
// 			}
// 
// 			nNeedRightBracket[1]++;
// 
// 			const EXP_CALC_ITEM it = {EXP_ROUND_LEFT, TRUE, strExp.Mid(i, 1)};
// 
// 			s2.push_back(it);
// 
// 			nLastType = EXP_ROUND_LEFT;
// 		}
// 		else if (')' == t)	// �����������, ��Ҫ�ж���ǰ�治�������
// 		{
// 			if (!((EXP_CONSTANT | EXP_VARIABLE | EXP_ROUND_RIGHT | EXP_SQUARE_RIGHT) & nLastType))
// 			{
// 				THROW_ERR_INFO(_T("������֮ǰ������������������� �� ����Ž�������"))
// 			}
// 
// 			nNeedRightBracket[1]--;
// 
// 			if (nNeedRightBracket[1] < 0)
// 			{
// 				THROW_ERR_INFO(_T("�������������Ų�ƥ�䡣"))
// 			}
// 			else
// 			{
// 				// �����������������, ��Ҫs2�е������һֱ��ջѹ��s1��
// 				// ֱ�����������ţ����Ǹ������ų�s2ȴ����S1
// 				int nLeft = 0;
// 				int nRight = 0;
// 
// 				while (!s2.empty())
// 				{
// 					EXP_CALC_ITEM &it_back = s2.back();
// 
// 					if (_T("(") != it_back.strVal)
// 					{
// 						if (_T("[") == it_back.strVal)
// 						{
// 							nLeft++;
// 						}
// 						else if (_T("]") == it_back.strVal)
// 						{
// 							nRight++;
// 						}
// 
// 						s1.push_back(s2.back());
// 						s2.pop_back();
// 					}
// 					else
// 					{
// 						s2.pop_back();
// 
// 						break;
// 					}
// 				}
// 
// 				if (nLeft != nRight)
// 				{
// 					THROW_ERR_INFO(_T("����Ž�����������Ž�������ƥ�䡣"))
// 				}
// 			}
// 
// 			nLastType = EXP_ROUND_RIGHT;
// 		}
// 		else // �����
// 		{
// 			CString strOp;
// 			BOOL b2Op = FALSE;
// 
// 			for (int j = 0; j < g_nOps; j++)
// 			{
// 				if (t == g_strOp[j][0])
// 				{
// 					if (i + 1 < nLength)
// 					{
// 						strOp = strExp.Mid(i, 2);
// 
// 						for (int k = 0; k < g_nOps; k++)
// 						{
// 							if (strOp == g_strOp[k])
// 							{
// 								i++;			// ����i
// 
// 								b2Op = TRUE;	// ������������ֽ�
// 								break;
// 							}
// 						}						
// 					}
// 
// 					break;
// 				}
// 			}
// 
// 			if (!b2Op)
// 			{
// 				strOp.Delete(1, 1);
// 			}
// 
// 			const int nAdj = b2Op? 1: 0;
// 			EXP_CALC_ITEM it = {EXP_OPERATOR, TRUE, strExp.Mid(i - nAdj, strOp.GetLength())};
// 
// 			BOOL bOperator = TRUE;
// 
// 			if (_T("-" == strOp) || _T("+") == strOp)
// 			{
// 				if (EXP_ROUND_LEFT == nLastType || true == s1.empty())	// ��ʾ���� �� ����
// 				{
// 					bOperator = FALSE;
// 
// 					it.nType = EXP_CONSTANT | EXP_VARIABLE;
// 					it.bNumEnd = FALSE;
// 
// 					s1.push_back(it);
// 
// 					nLastType = _T("-" == strOp)? EXP_NEGTIVE: EXP_POSITIVE;
// 				}
// 			}
// 
// 			if (bOperator)
// 			{
// 				if (_T("!") == strOp || _T("~") == strOp)
// 				{
// 					if (i > 0)
// 					{
// 						if (!((EXP_ROUND_LEFT | EXP_SQUARE_LEFT) & nLastType))
// 						{
// 							CString strTmp;
// 							strTmp.Format(_T("%s ֮ǰȱ�� ������ �� ����Ž�������"), strOp);
// 
// 							THROW_ERR_INFO(strTmp)
// 						}
// 					}
// 				}
// 				else if (EXP_OPERATOR == nLastType) // �����������������������
// 				{
// 					THROW_ERR_INFO(_T("�����֮��ȱ�ٲ�������"))
// 				}
// 
// 				if (s2.empty())	// ���s2Ϊ��, �������ֱ����ջ
// 				{
// 					s2.push_back(it);
// 				}
// 				else
// 				{
// 					const int nCurOp = priority(strOp);
// 					int nTopOp = priority(s2.back().strVal);
// 
// 					if (nCurOp >= nTopOp)  // ��ǰ����������������ȼ���С��s2ջ�������
// 					{
// 						s2.push_back(it);
// 					}
// 					else // ��ǰ����������������ȼ�С��s2ջ�����������ջ�������һֱ��ջѹ��s1��
// 					{
// 						s1.push_back(s2.back());
// 						s2.pop_back();
// 
// 						while (!s2.empty())
// 						{
// 							nTopOp = priority(s2.back().strVal);
// 
// 							if (nCurOp < nTopOp)
// 							{
// 								s1.push_back(s2.back());
// 								s2.pop_back();
// 							}
// 							else
// 							{
// 								break;
// 							}
// 						}
// 
// 						s2.push_back(it);
// 					}
// 				}
// 
// 				nLastType = EXP_OPERATOR;
// 			}
// 		}
// 	}
// 
// 	if (nNeedRightBracket[0])
// 	{
// 		THROW_ERR_INFO(_T("����Ž�����������Ž�������ƥ�䡣"))
// 	}
// 
// 	if (nNeedRightBracket[1])
// 	{
// 		THROW_ERR_INFO(_T("�������������Ų�ƥ�䡣"))
// 	}
// 
// 	while (!s2.empty())
// 	{
// 		s1.push_back(s2.back());
// 		s2.pop_back();
// 	}
// 
// #ifdef _DEBUG
// 	TRACE(_T("\n"));
// 
// 	const int nItems = s1.size();
// 
// 	for (int i = 0; i < nItems; i++)
// 	{
// 		TRACE(_T("%s "), s1[i].strVal);
// 	}
// 
// #endif // _DEBUG

	return s1;

#undef THROW_ERR_INFO
}


double CalcRepolish(std::vector<EXP_CALC_ITEM> vItems, double (*var)(const CString & v)) throw(std::out_of_range)
{
// 	TRACE(_T("\nCalcRepolish:"));
// 
// 	const double dZero = 0.000001;
// 
// 	int nSize = vItems.size();
// 
// 	for (int i = 0; i < nSize; i++)
// 	{
// 		EXP_CALC_ITEM &it = vItems[i];
// 
// 		if ((EXP_OPERATOR | EXP_SQUARE_LEFT) & it.nType)
// 		{
// 			// ��Ŀ����
// 			if (1 == it.nOps)
// 			{
// 				double dTmp = 0;
// 
// 				const EXP_CALC_ITEM it_val = vItems[i - 1];
// 
// 				if (EXP_CONSTANT == it_val.nType)
// 				{
// 					dTmp = _ttof(it_val.strVal);
// 				}
// 				else if (EXP_VARIABLE == it_val.nType)
// 				{
// 					dTmp = var(it_val.strVal);
// 				}
// 
// 				it.nType = EXP_CONSTANT;
// 
// 				if (_T("!") == it.strVal)
// 				{
// 					if (fabs(dTmp - 0) < dZero)
// 					{
// 						it.strVal = _T("1");
// 					}
// 					else
// 					{
// 						it.strVal = _T("0");
// 					}
// 				}
// 				else if (_T("~") == it.strVal)
// 				{
// 					const int nVal = (int)(dTmp);
// 
// 					it.strVal.Format(_T("%d"), ~nVal);
// 				}
// 
// 				vItems.erase(vItems.begin() + i - 1);
// 
// 				i--;
// 			}
// 			else // ˫Ŀ����
// 			{
// 				int nVal[2] = {0, 0};
// 				double dTmp[2] = {0, 0};
// 				CString strVar[2];
// 
// 				for (int j = 0; j < 2; j++)
// 				{
// 					const EXP_CALC_ITEM it_val = vItems[i - j - 1];
// 
// 					if (EXP_CONSTANT == it_val.nType)
// 					{
// 						dTmp[j] = _ttof(it_val.strVal);
// 					}
// 					else if (EXP_VARIABLE == it_val.nType)
// 					{
// 						strVar[j] = it_val.strVal;
// 
// 						dTmp[j] = var(strVar[j]);
// 					}
// 
// 					nVal[j] = (int)dTmp[j];
// 				}
// 
// 				std::swap(nVal[0], nVal[1]);
// 				std::swap(dTmp[0], dTmp[1]);
// 				std::swap(strVar[0], strVar[1]);
// 
// 				it.nType = EXP_CONSTANT;
// 
// 				// �����������Ա����
// 				if (_T("+") == it.strVal || _T("-") == it.strVal ||
// 					_T("*") == it.strVal || _T("/") == it.strVal || _T("%") == it.strVal ||
// 					_T(".") == it.strVal || _T("[") == it.strVal)
// 				{
// 					if (_T("+") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%f"), dTmp[0] + dTmp[1]);
// 					}
// 					else if (_T("-") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%f"), dTmp[0] - dTmp[1]);
// 					}
// 					else if (_T("*") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%f"), dTmp[0] * dTmp[1]);
// 					}
// 					else if (_T("/") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%f"), dTmp[0] / dTmp[1]);
// 					}
// 					else if (_T("%") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] / nVal[1]);
// 					}
// 					else if (_T(".") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%f"), var(strVar[0] + it.strVal + strVar[1]));
// 					}
// 					else if (_T("[") == it.strVal)
// 					{
// 						it.strVal.Format(_T("%s[%d]"), strVar[0], (int)dTmp[1]);
// 					}
// 				} // ����
// 				else if (_T("||") == it.strVal || _T("$$") == it.strVal)
// 				{
// 					for (int j = 0; j < 2; j++)
// 					{
// 						if (fabs(dTmp[j] - 0.0) < dZero)
// 						{
// 							nVal[j] = 0;
// 						}
// 						else
// 						{
// 							nVal[j] = 1;
// 						}
// 					}
// 
// 					it.strVal.Format(_T("%d"), (_T("||") == it.strVal)? (nVal[0] || nVal[1]): (nVal[0] && nVal[1]));
// 				} // �Ƚ�
// 				else if (_T("==") == it.strVal || _T("!=") == it.strVal ||
// 					     _T("<")  == it.strVal || _T("<=") == it.strVal || _T(">") == it.strVal || _T(">=") == it.strVal)
// 				{
// 					if (_T("==") == it.strVal)
// 					{
// 						if (fabs(dTmp[0] - dTmp[1]) < dZero)
// 						{
// 							it.strVal = _T("1");
// 						}
// 						else
// 						{
// 							it.strVal = _T("0");
// 						}
// 					}
// 					else if (_T("!=") == it.strVal)
// 					{
// 						if (fabs(dTmp[0] - dTmp[1]) > dZero)
// 						{
// 							it.strVal = _T("1");
// 						}
// 						else
// 						{
// 							it.strVal = _T("0");
// 						}
// 					}
// 					else if (_T("<") == it.strVal)
// 					{
// 						it.strVal = (dTmp[0] < dTmp[1])? _T("1"): _T("0");
// 					}
// 					else if (_T("<=") == it.strVal)
// 					{
// 						it.strVal = (dTmp[0] <= dTmp[1])? _T("1"): _T("0");
// 					}
// 					else if (_T(">") == it.strVal)
// 					{
// 						it.strVal = (dTmp[0] > dTmp[1])? _T("1"): _T("0");
// 					}
// 					else if (_T(">=") == it.strVal)
// 					{
// 						it.strVal = (dTmp[0] >= dTmp[1])? _T("1"): _T("0");
// 					}
// 				} // ��λ����
// 				else if (_T("|") == it.strVal || _T("^") == it.strVal || _T("$") == it.strVal)
// 				{
// 					if (_T("|")  == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] | nVal[1]);
// 					}
// 					else if (_T("^")  == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] ^ nVal[1]);
// 					}
// 					else if (_T("$")  == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] & nVal[1]);
// 					}
// 				} // ��λ
// 				else if (_T("<<") == it.strVal || _T(">>") == it.strVal)
// 				{
// 					if (_T("<<")  == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] << nVal[1]);
// 					}
// 					else if (_T(">>")  == it.strVal)
// 					{
// 						it.strVal.Format(_T("%d"), nVal[0] >> nVal[1]);
// 					}
// 				}
// 
// 				vItems.erase(vItems.begin() + i - 1);
// 				vItems.erase(vItems.begin() + i - 2);
// 
// 				i -= 2;
// 			}
// 
// 			nSize = vItems.size();
// 
// #ifdef _DEBUG
// 			TRACE(_T("\n"));
// 
// 			for (int j = 0; j < nSize; j++)
// 			{
// 				TRACE(_T("%s "), vItems[j].strVal);
// 			}
// #endif // _DEBUG
// 		}
// 	}

	const double dRetVal = _ttof(vItems[0].strVal);

	TRACE(_T("\nCalc res: %f"), dRetVal);

	return dRetVal;
}


BOOL CalcExpression(const CString & strExp,
					int (*priority)(const CString & o),
					BOOL (*varfind)(const CString & v, CString * pInfo),
					double (*varget)(const CString & v), double & dVal, CString * pErr)
{
	std::vector<EXP_CALC_ITEM> vItems = InfixToSuffix(strExp, priority, varfind, pErr);

	if (0 == vItems.size())
	{
		return FALSE;
	}

	dVal = CalcRepolish(vItems, varget);

	return TRUE;
}


CArchive & operator << (CArchive & ar, const std::vector<std::vector<CString>> & vv)
{
	const int nRows = vv.size();

	ar << nRows;

	for (int i = 0; i < nRows; i++)
	{
		const int nCols = vv[i].size();

		ar << nCols;

		for (int j = 0; j < nCols; j++)
		{
			ar << vv[i][j];
		}
	}

	return ar;
}


CArchive & operator >> (CArchive & ar, std::vector<std::vector<CString>> & vv)
{
	vv.clear();

	int nRows = 0;
	int nCols = 0;

	ar >> nRows;

	vv.resize(nRows);

	for (int i = 0; i < nRows; i++)
	{
		ar >> nCols;

		vv[i].resize(nCols);

		for (int j = 0; j < nCols; j++)
		{
			ar >> vv[i][j];
		}
	}

	return ar;
}
