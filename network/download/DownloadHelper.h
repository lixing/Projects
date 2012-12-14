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

//每个任务线程数
#define THREAD_COUNT 3
//重连时间
#define RECONNECT_INTERVAL 10000	

class DownloadHelper: public Thread
{
public:
	void * run(void *);
	bool startDownload();
	bool addDownloadTask(const char* remoteUrl, const char* localFolder);
	DownloadHelper();
	virtual ~DownloadHelper();
	//传入函数指针，下载完成后调用
	void setOnFinish(void (*func)());
private:
	//判断下载列表的文件是否已经存在
//传入index是downloadListRemoteURLs的下标
	bool exist(int index);
	//文件网络url路径
	vector<string> downloadListRemoteURLs;
	//文件在本地保存的目录
	vector<string> downloadListLocalFolders;
	//完成后调用的函数
	void (*onFinish)();

};

bool existInVector(vector<string>& array, string& str);

#endif 
