#pragma once

#include<iostream>
#include<fstream>
#include <afxmt.h>
#include <time.h>

using namespace std;
class AFX_EXT_CLASS COperateFile
{
public:
	COperateFile(void);
	~COperateFile(void);
public:
	BOOL _RecycleFileOrFolder(CString strPath, BOOL bDelete = TRUE);


/*================================================================
����: д�����ݵ�txt�ļ�
�������:	
	1. strPath: �ļ���·��
	2. strFileName: �ļ�����
	3. strInfo: д�����Ϣ
	4. bTime: �Ƿ�д��ʱ��
����ֵ: ��
================================================================*/
	BOOL _Write2TxtFile(CString strPath, CString strFileName, CString strInfo, BOOL bTime = TRUE);//������Ϣ��txt�ļ�

public:
	CSemaphore m_seWrite;//�����i��ʹ�öྀ�̕r����ֹ��Ϣ�nͻ	
};

