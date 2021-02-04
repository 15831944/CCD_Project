#include "stdafx.h"
#include "SearchFile.h"

CString g_strExePath = _T("");

CSearchFile::CSearchFile(void)
{
}


CSearchFile::~CSearchFile(void)
{
}


BOOL CSearchFile::SearchControllerFile()
{
	const CString strFolderPath = g_strExePath + _T("\\Controller");

	if(!PathIsDirectory(strFolderPath))   
		return CreateDirectory(strFolderPath,NULL);

	return TRUE;
}


BOOL CSearchFile::SearchReportFile()
{
	CString strFolderPath = g_strExePath + _T("\\Report");

	//�ж�·���Ƿ����   
	if(!PathIsDirectory(strFolderPath))   
	{
		if(!CreateDirectory(strFolderPath,NULL))   
		{   
			return FALSE;
		}
	}

	strFolderPath.Empty();
	strFolderPath.Append(g_strExePath);
	strFolderPath.Append(_T("\\Data"));

	if(!PathIsDirectory(strFolderPath))   
	{
		if(!CreateDirectory(strFolderPath,NULL))   
		{   
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CSearchFile::SearchTemplateFile()
{
	const CString strFolderPath = g_strExePath + _T("\\Template");

	//�ж�·���Ƿ����   
	if(!PathIsDirectory(strFolderPath))   
		return CreateDirectory(strFolderPath,NULL);

	return TRUE;

}

BOOL CSearchFile::SearchImageFile()
{
	CString strFolderPath;
	strFolderPath = g_strExePath + _T("\\NG_Img");

	//�ж�·���Ƿ����   
	if(!PathIsDirectory(strFolderPath))   
	{
		if(!CreateDirectory(strFolderPath,NULL))   
		{   
			return FALSE;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		strFolderPath.Format(_T("\\�yԇ�M_%d"), i + 1);
		strFolderPath = g_strExePath + _T("\\NG_Img") + strFolderPath;
		//�ж�·���Ƿ����   
		if(!PathIsDirectory(strFolderPath))   
		{
			CString strMsg;
			if(!CreateDirectory(strFolderPath,NULL))   
			{   
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CSearchFile::SearchLogFile()
{
	const CString strFolderPath = g_strExePath + _T("\\Log");

	//�ж�·���Ƿ����   

	if(!PathIsDirectory(strFolderPath))   
		return CreateDirectory(strFolderPath,NULL);

	return TRUE;
}


BOOL CSearchFile::SearchFile(CString strPath, BOOL & bIfCreate)
{
	CString strFolderPath;
	strFolderPath = g_strExePath + strPath;

	//�ж�·���Ƿ����   
	if(!PathIsDirectory(strFolderPath))   
	{
		CString strMsg;
		if(!CreateDirectory(strFolderPath,NULL))   
		{   
			return FALSE;
		}
		else
		{
			bIfCreate = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}

CString CSearchFile:: GetExePath(void)  
{  
	CString strExePath;  
	GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);  
	strExePath.ReleaseBuffer();  
	strExePath = strExePath.Left(strExePath.ReverseFind(_T('\\')));  
	g_strExePath = strExePath;
	return strExePath;  
}

CString CSearchFile::LoadSignalData(CString strFileName)
{
	CString strFilePath;
	strFilePath = g_strExePath + _T("\\Controller\\") + strFileName + _T(".ini");

	CString strCtrlName;
	CString strCtrlCheckModeName;
	CString strCoilStart;
	CString strCoilEnd;
	CString strRegistersStart;
	CString strRegistersEnd;

	if (GetFileAttributes(strFilePath) != -1) //����ļ�����
	{
		GetPrivateProfileString(strFileName,_T("strCtrlName"),_T(""),strCtrlName.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
		GetPrivateProfileString(strFileName,_T("strCtrlCheckModeName"),_T(""),strCtrlCheckModeName.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
		GetPrivateProfileString(strFileName,_T("strCoilStart"),_T(""),strCoilStart.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
		GetPrivateProfileString(strFileName,_T("strCoilEnd"),_T(""),strCoilEnd.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
		GetPrivateProfileString(strFileName,_T("strRegistersStart"),_T(""),strRegistersStart.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
		GetPrivateProfileString(strFileName,_T("strRegistersEnd"),_T(""),strRegistersEnd.GetBuffer(MAX_PATH + 1),MAX_PATH,strFilePath);
	}
	return strCtrlCheckModeName;
	
}

BOOL CSearchFile::CheckFile(CString strFilePath)//�����Ƿ�����ļ�
{
	if (GetFileAttributes(strFilePath) != -1) //����ļ�����
	{
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
˵����
    ���ļ����в����ļ�������ָ���ļ��в��ң����ݹ飩
������
    fileName:Ҫ���ҵ��ļ�����֧��ͨ���*
    directory:Ҫ���ҵ��ļ����ڵ�Ŀ¼·��
����ֵ��
    pair<string,string>���͵����飬map<�ļ������ļ�·��>
************************************************************************/

vector<pair<CString,CString>> CSearchFile::FindFilesInDirecotry(CString fileName,CString directory, int & filecounter)
{
	vector<pair<CString,CString>> files;

	if(directory.Right(1) != "\\") //��֤Ŀ¼����\��β��
	{  
		directory += "\\";
	}
	directory += fileName;
	CFileFind finder;
	BOOL success = finder.FindFile(directory);
	while(success)
	{
		success = finder.FindNextFile();
		CString name = finder.GetFileName();
		CString path = finder.GetFilePath();
		pair<CString,CString> fileMap(name,path);
		files.push_back(fileMap);
		filecounter++;
	}
	finder.Close();
	filecounter -= 2;
	return files;
}


/************************************************************************
˵����
    ���ļ����еݹ�����ļ�
������
    fileName:Ҫ���ҵ��ļ�����֧��ͨ���*
    directory:Ҫ���ҵ��ļ����ڵ�Ŀ¼·��
    recursionCount:�ݹ���ҵ���ȣ�Ĭ��Ϊ-1����������ȣ�,0��ʾֻ����������directoryĿ¼
����ֵ��
    pair<string,string>���͵����飬map<�ļ������ļ�·��>
************************************************************************/

vector<pair<CString,CString>> CSearchFile::FindFilesInDirecotryRecursion( CString fileName, CString directory, int recursionCount, int & filecounter, vector <CString> & vstrFileName)
{
	vector<pair<CString,CString>> files;
	
	int curRecursionCount = recursionCount;
	int nPart = 0;
	//�ȶԲ������������ļ��в���
	vector<pair<CString,CString>> localFiles =  FindFilesInDirecotry(fileName, directory, nPart);
	files.insert(files.end(),localFiles.begin(),localFiles.end());

	//Ȼ��Դ��ļ�����������ļ��еݹ����
	CFileFind finder;
	if(directory.Right(1) != "\\") //��֤Ŀ¼����\��β��
	{  
		directory += "\\";
	}
	directory += "*.*";

	BOOL res = finder.FindFile(directory);
	while (res)
	{
		res = finder.FindNextFile();
		CString path = finder.GetFilePath();
		CString name = finder.GetFileName();
		curRecursionCount = recursionCount;  //����ͬ��Ŀ¼��ʱ�򽫵�ǰ�������Ϊ����ֵ
		if(finder.IsDirectory() && !finder.IsDots())
		{
			if(curRecursionCount >= 1 || curRecursionCount == -1 )
			{
				if(curRecursionCount >= 1)
				{
					curRecursionCount--;
				}
				localFiles = FindFilesInDirecotryRecursion(fileName, path, curRecursionCount, nPart, vstrFileName); //���Ŀ���Ǹ��ļ��У�������Ƕ��������
				files.insert(files.end(),localFiles.begin(),localFiles.end());
				filecounter++;
			}
		}
	}
	finder.Close();

	vstrFileName.clear();
	m_vstrFileName.push_back(directory);
	vstrFileName = m_vstrFileName;
	return files;
}


vector<CString> CSearchFile::_FindFile(CString strFolderName, CString strFileType)
{
	vector<CString> vstrPath;
	CString m_cstrFileList=_T("");
	CFileFind tempFind;
	BOOL bFound; //�ж��Ƿ�ɹ��ҵ��ļ�
	const CString strPath = strFolderName + _T("\\*.") + strFileType + _T("*");
	bFound = tempFind.FindFile(strPath);  //�޸�" "�����ݸ��޶������ļ�����
	CString strTmp;   //����ҵ������ļ��� ����ļ���·��
	while(bFound)      //���������ļ�
	{
		bFound=tempFind.FindNextFile(); //��һ��ִ��FindNextFile��ѡ�񵽵�һ���ļ����Ժ�ִ��Ϊѡ��
		//����һ���ļ�
		//if(!tempFind.IsDots()) continue; //����ҵ����Ƿ����ϲ��Ŀ¼ ��������β���
		strTmp = tempFind.GetFileName(); //�����ļ�����������׺��
			// �ڴ˴���Ӷ��ҵ��ļ��Ĵ���
		vstrPath.push_back(strFolderName +  + _T("\\") + strTmp);
	}
	tempFind.Close();
	return vstrPath;
}