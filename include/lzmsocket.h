#ifndef __LZMSOCKET_H__
#define __LZMSOCKET_H__
#include<WinSock2.h>
SOCKET init(){
	static WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2),&wsaData)!=0)
		return INVALID_SOCKET;
	SOCKET s=socket(AF_INET,SOCK_STREAM,0);
	return s;
}
bool init_server(SOCKET s,int port){
	static SOCKADDR_IN serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port);
	serv_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	if(bind(s,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR)return false;
	return listen(s,5)!=SOCKET_ERROR;
}
bool connect_server(SOCKET s,char* addr,int port){
	static SOCKADDR_IN serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = inet_addr(addr);
	return connect(s,(SOCKADDR*)&serv_addr,sizeof(serv_addr))!=SOCKET_ERROR;
}
SOCKET getclient(SOCKET s,SOCKADDR_IN* client_addr){
	SOCKET client;
	int len=sizeof(SOCKADDR);
	client=accept(s,(SOCKADDR*)client_addr,&len);
	if(client==INVALID_SOCKET)return INVALID_SOCKET;
	return client;
}
int getlasterror(){return WSAGetLastError();}
bool sendmsg(SOCKET s,char *buf,int size){return send(s,buf,size,0)!=SOCKET_ERROR;}
bool getmsg(SOCKET s,char *buf,int size){return recv(s,buf,size,0)!=SOCKET_ERROR;}
char* getip(SOCKADDR_IN addr){return inet_ntoa(addr.sin_addr);}
bool cleansocket(){return !WSACleanup();}
#endif
