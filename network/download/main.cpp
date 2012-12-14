
#include <afx.h>
#include <afxwin.h>   
#include "Mydownload.h"

#include <iostream>
using namespace std;

#include "DownloadHelper.h"

unsigned long temp = 0;
unsigned long *downloaded = &temp;
unsigned long totalSize = 1024;

void testFunc(){
	cout<<"Finished!!!!"<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	char url[100];
	void (*func)();
	printf("Please Input the URL of the file\n");
	gets(url);
	func = testFunc;
	DownloadHelper downloadHelper;
	downloadHelper.addDownloadTask(url,"c:\\");
	downloadHelper.startDownload();
	downloadHelper.join();

	return 0;
}
