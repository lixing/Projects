// DownloadHelper.h: interface for the DownloadHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADHELPER_H__18F50BBB_1DDB_48EB_A2CB_C83DF36DD960__INCLUDED_)
#define AFX_DOWNLOADHELPER_H__18F50BBB_1DDB_48EB_A2CB_C83DF36DD960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "Thread.h"

//ÿ�������߳���
#define THREAD_COUNT 3
//����ʱ��
#define RECONNECT_INTERVAL 10000	

class DownloadHelper: public Thread
{
public:
	void * run(void *);
	bool startDownload();
	bool addDownloadTask(const char* remoteUrl, const char* localFolder);
	DownloadHelper();
	virtual ~DownloadHelper();
	//���뺯��ָ�룬������ɺ����
	void setOnFinish(void (*func)());
private:
	//�ж������б���ļ��Ƿ��Ѿ�����
//����index��downloadListRemoteURLs���±�
	bool exist(int index);
	//�ļ�����url·��
	vector<string> downloadListRemoteURLs;
	//�ļ��ڱ��ر����Ŀ¼
	vector<string> downloadListLocalFolders;
	//��ɺ���õĺ���
	void (*onFinish)();

};

bool existInVector(vector<string>& array, string& str);

#endif 
