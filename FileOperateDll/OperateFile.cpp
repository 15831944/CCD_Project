#include "stdafx.h"
#include "OperateFile.h"


COperateFile::COperateFile(void)
{
}


COperateFile::~COperateFile(void)
{
}


// ɾ���ļ����ڶ�������bDelete��ʾ�Ƿ�ɾ��������վ,Ĭ��ɾ��������վ��  
BOOL COperateFile::_RecycleFileOrFolder(CString strPath, BOOL bDelete/*=FALSE*/)  
{  
	strPath += '\0';  
	SHFILEOPSTRUCT  shDelFile;  
	memset(&shDelFile,0,sizeof(SHFILEOPSTRUCT));  
	shDelFile.fFlags |= FOF_SILENT;             // ����ʾ����  
	shDelFile.fFlags |= FOF_NOERRORUI;          // �����������Ϣ  
	shDelFile.fFlags |= FOF_NOCONFIRMATION;     // ֱ��ɾ����������ȷ��  

	// ����SHFILEOPSTRUCT�Ĳ���Ϊɾ����׼��  
	shDelFile.wFunc = FO_DELETE;        // ִ�еĲ���  
	shDelFile.pFrom = strPath;          // �����Ķ���Ҳ����Ŀ¼��ע�⣺�ԡ�\0\0����β��  
	shDelFile.pTo = NULL;               // ��������ΪNULL  
	if (bDelete) //���ݴ��ݵ�bDelete����ȷ���Ƿ�ɾ��������վ  
	{      
		shDelFile.fFlags &= ~FOF_ALLOWUNDO;    //ֱ��ɾ�������������վ  
	}   
	else   
	{             
		shDelFile.fFlags |= FOF_ALLOWUNDO;    //ɾ��������վ  
	}  

	BOOL bres = SHFileOperation(&shDelFile);    //ɾ��  
	return !bres;  
}


BOOL COperateFile::_Write2TxtFile(CString strPath, CString strFileName, CString strInfo, BOOL bTime)
{
	m_seWrite.Lock();

	CString strTemp = strPath + _T("\\") + strFileName + _T(".txt");
	
	ofstream WriteFile(strTemp,ios::app);//app��ʾÿ�β���ǰ����λ���ļ�ĩβ

	CString strInfoWrite;

	USES_CONVERSION;

	if (bTime)
	{
		TCHAR szFileName[MAX_PATH] = {0};

		SYSTEMTIME st;
		GetLocalTime(&st);

		CString strTime;
		strTime.Format(_T("%04d��%02d��%02d��  %02dʱ%02d��%02d��     "), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		
		strInfoWrite.Append(strTime);
	}
	strInfoWrite.Append(strInfo);

	WriteFile<<W2A(strInfoWrite)<<endl;

	WriteFile.close();

	m_seWrite.Unlock();	
	
	return TRUE;
}