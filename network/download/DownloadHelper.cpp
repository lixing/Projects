// DownloadHelper.cpp: implementation of the DownloadHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DownloadHelper.h"
#include "Mydownload.h"
#include <io.h>

DownloadHelper::DownloadHelper()
{
	onFinish = NULL;
}

DownloadHelper::~DownloadHelper()
{

}

//Add the download task
bool DownloadHelper::addDownloadTask(const char* remoteUrl, const char* localFolder)
{
	string remoteUrlString(remoteUrl);
	string localFolderString(localFolder);

	if(!existInVector(downloadListRemoteURLs,remoteUrlString)){
		downloadListRemoteURLs.push_back(remoteUrlString);
		downloadListLocalFolders.push_back(localFolderString);
		return true;
	}else{
		return false;
	}
}
  

bool existInVector(vector<string>& array, string& str){
	for(int k = 0;k<array.size();k++){
		if(array[k].compare(str)==0)
			return true;
	}
	return false;
}

//Download start
bool DownloadHelper::startDownload()
{
	this->start();
	return true;
}


void * DownloadHelper::run(void *)
{	

	unsigned long temp = 0;
	unsigned long *downloaded = &temp;
	unsigned long totalSize = 1024;
	while(downloadListRemoteURLs.size()>0)
	{
		cout<<"Start Downloading from "<<downloadListRemoteURLs[0]<<endl;

		while(true){

			fnMyDownload(downloadListRemoteURLs[0].data(),
				downloadListLocalFolders[0].data(),downloaded,totalSize,"",0,THREAD_COUNT);	
			if(!exist(0)){
			
				
				Sleep(RECONNECT_INTERVAL);	//Reconnect after 10 seconds
			}else{
				
				vector<string>::iterator startIterator = downloadListRemoteURLs.begin();  
				downloadListRemoteURLs.erase( startIterator );
				startIterator = downloadListLocalFolders.begin();  
				downloadListLocalFolders.erase( startIterator );
				printf("Your file has been downloaded to C:\\ \n");                
				printf("Press Enter To Exit");  
		        getchar();
				break;
			}
		}
    }
	if(onFinish!=NULL){
		onFinish();
	}
	return NULL;
}

bool DownloadHelper::exist(int index)
{
	string fileName = downloadListRemoteURLs[index].substr(downloadListRemoteURLs[index].find_last_of("/")+1);
	string file(downloadListLocalFolders[index].data());	//copy
	file.append(fileName);
	return (_access(file.data(), 0) == 0);;
}


void DownloadHelper::setOnFinish(void (*func)()){
	onFinish = func;
}