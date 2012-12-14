#include "MyDownload.h"
#include <sys/stat.h>  

#include <iostream>
using namespace std;

#ifdef _MANAGED
#pragma managed(pop)
#endif


int CHttpGet::m_nCount;
DWORD CHttpGet::m_nFileLength = 0;

unsigned long rdownloaded = 0;

void ParseURL(CString URL,CString &host,CString &path,CString &filename)
{
   URL.TrimLeft();
   URL.TrimRight();
   CString str=URL;
   CString strFind=_T("http://");
   int n=str.Find(strFind);
   if(n!=-1){
      str.Delete(0, n+strFind.GetLength());
   }

   n=str.Find('/');
   host = str.Left(n);
   n=URL.ReverseFind('/');
   path = URL.Left(n+1);
   filename = URL.Right(URL.GetLength()-n-1);
}

void Getname(string& pOut,char *pText, int pLen)
{
    char buf[4];
    int nLength = pLen* 3;
    char* rst = new char[nLength];
    
    memset(buf,0,4);
    memset(rst,0,nLength);
    
    int i = 0;
    int j = 0;      
    while(i < pLen)
    {
            if( *(pText + i) >= 0)
            {
                    rst[j++] = pText[i++];
            }
          
    }
    rst[j] = '\0';

    pOut = rst;             
    delete []rst;   
    
    return;
}

bool fnMyDownload(CString strUrl,
								 CString strWriteFileName,
								 unsigned long *& downloaded,
								 unsigned long & totalSize,
                                 CString strProxy,
								 int nProxyPort,
								 int nThread
								 )
{
	CHttpGet b;
	CString strHostAddr;
	CString strHttpAddr;
	CString strHttpFilename;

	downloaded = &rdownloaded;

	ParseURL(strUrl,strHostAddr,strHttpAddr,strHttpFilename);
	strWriteFileName += strHttpFilename;	
	
	string remoteFileName;		//File name
	Getname(remoteFileName, (char*)strHttpFilename.GetBuffer(strHttpFilename.GetLength()), strHttpFilename.GetLength());
	strHttpFilename = remoteFileName.c_str();
	string remoteFilePath;		//File path 
	Getname(remoteFilePath, (char*)strHttpAddr.GetBuffer(strHttpAddr.GetLength()), strHttpAddr.GetLength());
	strHttpAddr = remoteFilePath.c_str();

    
	if(strProxy != ""){
		if(!b.HttpDownLoadProxy(strProxy,nProxyPort,strHostAddr,strHttpAddr,strHttpFilename,strWriteFileName,nThread,totalSize))
			return false;
	}
	else{
		if(!b.HttpDownLoadNonProxy(strHostAddr,strHttpAddr,strHttpFilename,strWriteFileName,nThread,totalSize))
			return false;
	}
	return true;
}

   


//---------------------------------------------------------------------------
CHttpGet::CHttpGet()
{
	m_nFileLength=0;
}

//---------------------------------------------------------------------------
CHttpGet::~CHttpGet()
{
}

//---------------------------------------------------------------------------
BOOL CHttpGet::HttpDownLoadProxy(
			CString strProxyAddr,
			int nProxyPort,
		    CString strHostAddr,
			CString strHttpAddr,
			CString strHttpFilename,
			CString strWriteFileName,
			int nSectNum,
			DWORD &totalSize
			)
{
	SOCKET hSocket;
	hSocket=ConnectHttpProxy(strProxyAddr,nProxyPort);
	if(hSocket == INVALID_SOCKET) return 1;

	//Sent the header and calculate the size
	SendHttpHeader(hSocket,strHostAddr,strHttpAddr,strHttpFilename,0);
 	closesocket(hSocket);

	totalSize = CHttpGet::m_nFileLength;


    if(!HttpDownLoad(strProxyAddr,nProxyPort,strHostAddr,80,strHttpAddr,strHttpFilename,strWriteFileName,nSectNum,true))
		return FALSE;

	return TRUE;
}

//---------------------------------------------------------------------------
BOOL CHttpGet::HttpDownLoadNonProxy(
		    CString strHostAddr,
			CString strHttpAddr,
			CString strHttpFilename,
			CString strWriteFileName,
			int nSectNum,
			DWORD &totalSize)
{
	int nHostPort=80;

	SOCKET hSocket;
	hSocket=ConnectHttpNonProxy(strHostAddr,nHostPort);
	if(hSocket == INVALID_SOCKET) return 1;
	//Sent the header and calculate the size
	SendHttpHeader(hSocket,strHostAddr,strHttpAddr,strHttpFilename,0);
 	closesocket(hSocket);
	totalSize = CHttpGet::m_nFileLength;

    if(!HttpDownLoad(TEXT(""),80,strHostAddr,nHostPort,strHttpAddr,strHttpFilename,strWriteFileName,nSectNum,false))
			return FALSE;

	return TRUE;
}

//---------------------------------------------------------------------------
BOOL CHttpGet::HttpDownLoad(
			CString strProxyAddr,
			int nProxyPort,
		    CString strHostAddr,
			int nHostPort,
			CString strHttpAddr,
			CString strHttpFilename,
			CString strWriteFileName,
			int nSectNum,
			BOOL bProxy)
{
	ASSERT(nSectNum>0 && nSectNum<=50);

	m_nCount=0;                                  
	sectinfo=new CHttpSect[nSectNum];            
	DWORD nSize= m_nFileLength/nSectNum;           // calculate the size of thread

	cout<<"The file size is "<<m_nFileLength<<endl;
	cout<<"The size of each thread is "<<nSize<<endl;
	int i;

	CWinThread* pthread[50];
	for(i=0;i<nSectNum;i++)
	{
	    sectinfo[i].szProxyAddr=strProxyAddr;      
	    sectinfo[i].nProxyPort =nProxyPort;		   
	    sectinfo[i].szHostAddr =strHostAddr;       
	    sectinfo[i].nHostPort  =nHostPort;		   
	    sectinfo[i].szHttpAddr =strHttpAddr;       
	    sectinfo[i].szHttpFilename=strHttpFilename;
		sectinfo[i].bProxyMode=bProxy;		       

		CString strTempFileName;
		strTempFileName.Format("%s_%d",strWriteFileName, i);
        sectinfo[i].szDesFilename=strTempFileName; 
	
		if(i<nSectNum-1){
			sectinfo[i].nStart=i*nSize;          //The start position for the session
			sectinfo[i].nEnd=(i+1)*nSize;        //The end position for the session
		}
		else{
			sectinfo[i].nStart=i*nSize;          //The start position for the session  
			sectinfo[i].nEnd=m_nFileLength;      //The end position for the session
		}


		pthread[i] = AfxBeginThread(ThreadDownLoad,&sectinfo[i]);
		Sleep(500);
	}

	HANDLE hThread[50];
	for(int ii = 0 ; ii < nSectNum ; ii++)
		hThread[ii] = pthread[ii]->m_hThread;

	WaitForMultipleObjects(nSectNum,hThread,TRUE,INFINITE);

	if(m_nCount != nSectNum)
		return FALSE;
	
	FILE *fpwrite;

 	// Fopen to write the file
	if((fpwrite=fopen(strWriteFileName,"wb"))==NULL){
  		return FALSE;
	}

	for(i=0;i<nSectNum;i++){
		FileCombine(&sectinfo[i],fpwrite);
	}

	fclose(fpwrite);

	delete[] sectinfo;
    
    return TRUE;
}

//---------------------------------------------------------------------------
BOOL CHttpGet::FileCombine(CHttpSect *pInfo, FILE *fpwrite)
{	
	FILE *fpread;
	
	// Open the file
	if((fpread=fopen(pInfo->szDesFilename,"rb"))==NULL)
		return FALSE;

	DWORD nPos=pInfo->nStart;
	
	// Set the pointer's start position.
	fseek(fpwrite,nPos,SEEK_SET);
	
	int c;	
	while((c=fgetc(fpread))!=EOF)
	{
		fputc(c,fpwrite);
		nPos++;
		if(nPos==pInfo->nEnd) break;
	}
	
	fclose(fpread);
	DeleteFile(pInfo->szDesFilename);

	return TRUE;
}

//---------------------------------------------------------------------------
UINT CHttpGet::ThreadDownLoad(void* pParam)
{
	CHttpSect *pInfo=(CHttpSect*)pParam;
	SOCKET hSocket;

	if(pInfo->bProxyMode){	
		hSocket=ConnectHttpProxy(pInfo->szProxyAddr,pInfo->nProxyPort);
	}
	else{
		hSocket=ConnectHttpNonProxy(pInfo->szHostAddr,pInfo->nHostPort);
	}
	if(hSocket == INVALID_SOCKET) return 1;


	// Calculate the size of the template file, for the use of resume broken transfer
	DWORD nFileSize=myfile.GetFileSizeByName(pInfo->szDesFilename);
    DWORD nSectSize=(pInfo->nEnd)-(pInfo->nStart);


	if(nFileSize==nSectSize){
                                
		CHttpGet::m_nCount++;  


		return 0;
	}

    FILE *fpwrite=myfile.GetFilePointer(pInfo->szDesFilename);
	if(!fpwrite) return 1;


	SendHttpHeader(hSocket,pInfo->szHostAddr,pInfo->szHttpAddr,
		      pInfo->szHttpFilename,pInfo->nStart+nFileSize);
	
	// Set the file write pointer's position and resume broken transfer
	fseek(fpwrite,nFileSize,SEEK_SET);

	DWORD nLen; 
	DWORD nSumLen=0; 
	char szBuffer[1024];

	while(1)
	{
		if(nSumLen>=nSectSize-nFileSize) break;
		nLen=recv(hSocket,szBuffer,sizeof(szBuffer),0);
		
		rdownloaded += nLen;
		
		if (nLen == SOCKET_ERROR){
			TRACE("Read error!\n");
			fclose(fpwrite);
			return 1;
		}

  		if(nLen==0) break;
		nSumLen +=nLen;
		TRACE("%d\n",nLen);

		// write the date		
		fwrite(szBuffer,nLen,1,fpwrite);
	}

    
	fclose(fpwrite);     
	closesocket(hSocket); 
	CHttpGet::m_nCount++; 
	return 0;
}

//---------------------------------------------------------------------------
SOCKET CHttpGet::ConnectHttpProxy(CString strProxyAddr,int nPort)
{
	TRACE("正在建立连接\n");
	
  	CString sTemp;
	char cTmpBuffer[1024];
	SOCKET hSocket=dealsocket.GetConnect(strProxyAddr,nPort);

    if(hSocket == INVALID_SOCKET)
    {
		TRACE("连接http服务器失败！\n");
		return INVALID_SOCKET;
    }

	sTemp.Format("CONNECT %s:%d HTTP/1.1\r\nUser-Agent:\
		           MyApp/0.1\r\n\r\n",strProxyAddr,nPort);
	
	if(!SocketSend(hSocket,sTemp))
	{
		TRACE("连接代理失败\n");
		return INVALID_SOCKET;
	}

	int nLen=GetHttpHeader(hSocket,cTmpBuffer);
	sTemp=cTmpBuffer;
	if(sTemp.Find("HTTP/1.0 200 Connection established",0)==-1)
	{
		TRACE("连接代理失败\n");
		return INVALID_SOCKET;
	}

	TRACE(sTemp);
	TRACE("代理连接完成\n");
	return hSocket; 
}

//---------------------------------------------------------------------------
SOCKET CHttpGet::ConnectHttpNonProxy(CString strHostAddr,int nPort)
{
	TRACE("正在建立连接\n");
    SOCKET hSocket=dealsocket.GetConnect(strHostAddr,nPort);
	if(hSocket == INVALID_SOCKET)
		return INVALID_SOCKET;
    
	return hSocket;
}
//Down load start
BOOL CHttpGet::SendHttpHeader(SOCKET hSocket,CString strHostAddr,
				CString strHttpAddr,CString strHttpFilename,DWORD nPos)
{

	static CString sTemp;
	char cTmpBuffer[1024];
	CString sHA;

	strHttpAddr.TrimLeft();
	strHttpAddr.TrimRight();
	CString str=strHttpAddr;
	CString strFind=_T("http://");
   int n=str.Find(strFind);
   if(n!=-1){
      str.Delete(0, n+strFind.GetLength());
   }

   n=str.Find('/');
   sHA = strHttpAddr.Right(strHttpAddr.GetLength()-7-n);
   CString cSTemp;

	sTemp.Format("GET %s%s HTTP/1.1\r\n",sHA,strHttpFilename);
	cSTemp = sTemp;

	sTemp.Format("Host: %s\r\n",strHostAddr);
	cSTemp += sTemp;

	sTemp.Format("Accept: \r\n");
	cSTemp += sTemp;

    sTemp.Format("Referer: %s\r\n",strHttpAddr); 
	cSTemp += sTemp;

	sTemp.Format("User-Agent: Mozilla/4.0 \
		(compatible; MSIE 5.0; Windows NT; DigExt; DTS Agent;)\r\n");
	cSTemp += sTemp;

	sTemp.Format("Range: bytes=%d-\r\n",nPos);
	cSTemp += sTemp;
	TRACE(sTemp);

	sTemp.Format("\r\n");
	cSTemp += sTemp;
	if(!SocketSend(hSocket,cSTemp)) return FALSE;

	int i=GetHttpHeader(hSocket,cTmpBuffer);
	if(!i)
	{
		TRACE("获取HTTP头出错!\n");
		return 0;
	}
	
	sTemp=cTmpBuffer;
	if(sTemp.Find("404")!=-1) return FALSE;

	m_nFileLength=GetFileLength(cTmpBuffer);


    TRACE(CString(cTmpBuffer).GetBuffer(200));

	return TRUE;
}

//---------------------------------------------------------------------------
DWORD CHttpGet::GetHttpHeader(SOCKET sckDest,char *str)
{
	BOOL bResponsed=FALSE;
	DWORD nResponseHeaderSize;
	
	if(!bResponsed)
	{
		char c = 0;
		int nIndex = 0;
		BOOL bEndResponse = FALSE;
		while(!bEndResponse && nIndex < 1024)
		{
			recv(sckDest,&c,1,0);
			str[nIndex++] = c;
			if(nIndex >= 4)
			{
				if( str[nIndex - 4] == '\r' && 
					str[nIndex - 3] == '\n' && 
					str[nIndex - 2] == '\r' && 
					str[nIndex - 1] == '\n')
					bEndResponse = TRUE;
			}
		}

		str[nIndex]=0;
		nResponseHeaderSize = nIndex;
		bResponsed = TRUE;
	}
	
	return nResponseHeaderSize;
}

//---------------------------------------------------------------------------
DWORD CHttpGet:: GetFileLength(char *httpHeader)
{
	CString strHeader;
	CString strFind=_T("Content-Length:");
	int local;
	strHeader=CString(httpHeader);
	local=strHeader.Find(strFind,0);
	local+=strFind.GetLength();
	strHeader.Delete(0,local);
	local=strHeader.Find("\r\n");
	
	if(local!=-1){
      strHeader=strHeader.Left(local);
	}

	return atoi(strHeader);
}

//---------------------------------------------------------------------------
BOOL CHttpGet::SocketSend(SOCKET sckDest,CString szHttp)
{
	int iLen=szHttp.GetLength();
	if(send (sckDest,szHttp,iLen,0)==SOCKET_ERROR)
	{
		closesocket(sckDest);
		TRACE("发送请求失败!\n");
		return FALSE;
	}
	
	return TRUE;
}


CDealSocket dealsocket;

//---------------------------------------------------------------------------
CDealSocket::CDealSocket()
{

	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	
	if (WSAStartup(wVersionRequested, &wsaData)!=0)
	{
		TRACE("WSAStartup\n");
		return;
	}

	if (wsaData.wVersion != wVersionRequested)
	{
		TRACE("WinSock version not supported\n");
		WSACleanup();
		return;
	}
}

//---------------------------------------------------------------------------
CDealSocket::~CDealSocket()
{

	WSACleanup();
}

//---------------------------------------------------------------------------
CString CDealSocket::GetResponse(SOCKET hSock)
{
	char szBufferA[MAX_RECV_LEN];  	
	int	iReturn;					
	
	CString szError;
	CString strPlus;
	strPlus.Empty();

	while(1)
	{
		iReturn = recv (hSock, szBufferA, MAX_RECV_LEN, 0);
		szBufferA[iReturn]=0;
		strPlus +=szBufferA;

		TRACE(szBufferA);

		if (iReturn == SOCKET_ERROR)
		{
			szError.Format("No data is received, recv failed. Error: %d",
				WSAGetLastError ());
			MessageBox (NULL, szError, TEXT("Client"), MB_OK);
			break;
		}
		else if(iReturn<MAX_RECV_LEN){
			TRACE("Finished receiving data\n");
			break;
		}
	}

	return strPlus;
}

//---------------------------------------------------------------------------
SOCKET CDealSocket::GetConnect(CString host ,int port)
{
    SOCKET hSocket;
	SOCKADDR_IN saServer;          
	PHOSTENT phostent = NULL;	  

	if ((hSocket = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		TRACE("Allocating socket failed. Error: %d\n",WSAGetLastError ());
		return INVALID_SOCKET;
	}
	

	saServer.sin_family = AF_INET;
	
	if ((phostent = gethostbyname (host)) == NULL) 
	{
		TRACE("Unable to get the host name. Error: %d\n",WSAGetLastError ());
		closesocket (hSocket);
		return INVALID_SOCKET;
	}

	memcpy ((char *)&(saServer.sin_addr), 
		phostent->h_addr, 
		phostent->h_length);
	
	saServer.sin_port =htons (port); 

	if (connect (hSocket,(PSOCKADDR) &saServer, 
		sizeof (saServer)) == SOCKET_ERROR) 
	{
		TRACE("Connecting to the server failed. Error: %d\n",WSAGetLastError ());
		closesocket (hSocket);
		return INVALID_SOCKET;
	}

	return hSocket;
}

//---------------------------------------------------------------------------
SOCKET CDealSocket::Listening(int port)
{
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKADDR_IN local_sin;				   
	
	if ((ListenSocket = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
	{
		TRACE("Allocating socket failed. Error: %d\n",WSAGetLastError ());
		return INVALID_SOCKET;
	}
	
	local_sin.sin_family = AF_INET;
	local_sin.sin_port = htons (port); 
	local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
	
	if (bind (ListenSocket, 
		(struct sockaddr *) &local_sin, 
		sizeof (local_sin)) == SOCKET_ERROR) 
	{
		TRACE("Binding socket failed. Error: %d\n",WSAGetLastError ());
		closesocket (ListenSocket);
		return INVALID_SOCKET;
	}
	
	if (listen (ListenSocket, MAX_PENDING_CONNECTS) == SOCKET_ERROR) 
	{
		TRACE("Listening to the client failed. Error: %d\n",	
			WSAGetLastError ());
		closesocket (ListenSocket);
		return INVALID_SOCKET;
	}

	return ListenSocket;
}

CMyFile myfile;

//---------------------------------------------------------------------------
CMyFile::CMyFile()
{
}

//---------------------------------------------------------------------------
CMyFile::~CMyFile()
{
}

//---------------------------------------------------------------------------
BOOL CMyFile::FileExists(LPCTSTR lpszFileName)
{
	DWORD dwAttributes = GetFileAttributes(lpszFileName);
    if (dwAttributes == 0xFFFFFFFF)
        return FALSE;

	if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		 ==	FILE_ATTRIBUTE_DIRECTORY)
	{
			return FALSE;
	}
	else{
		return TRUE;
	}
}

//---------------------------------------------------------------------------
FILE* CMyFile::GetFilePointer(LPCTSTR lpszFileName)
{
    FILE *fp;
	if(FileExists(lpszFileName)){
		fp=fopen(lpszFileName,"r+b");
	}
	else{
		fp=fopen(lpszFileName,"w+b");
	}

	return fp;
}

//---------------------------------------------------------------------------
DWORD CMyFile::GetFileSizeByName(LPCTSTR lpszFileName)
{
	if(!FileExists(lpszFileName)) return 0;
	struct _stat ST; 
	// Get the length of the file
	_stat(lpszFileName, &ST);
	UINT nFilesize=ST.st_size;
	return nFilesize; 
}

//---------------------------------------------------------------------------
CString CMyFile::GetShortFileName(LPCSTR lpszFullPathName)
{
   CString strFileName=lpszFullPathName;
   CString strShortName;
   strFileName.TrimLeft();
   strFileName.TrimRight();
   int n=strFileName.ReverseFind('/');
   strShortName=strFileName.Right(strFileName.GetLength()-n-1);
   return strShortName;
}