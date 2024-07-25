#include"../setting/precmd.ini"
#include"../setting/port.ini"
#include"../include/lzmsocket.h"
#include"../include/andycolor.h"
#include<unordered_map>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
using namespace color;
using namespace std;
char ch,op[1010],tmp[1010],msg[1010],opt[1010],buff[1010],ccc[1000]="failed",sss[1000],scwd[1000],ccwd[1000],*cip;
SOCKET s,c;
unordered_map<string,bool>bstty;
unordered_map<string,int>istty;
unordered_map<string,double>rstty;
unordered_map<string,string>sstty;
void initstty(){
	bstty["echo_path"]=true;
	bstty["echo_input"]=true;
	istty["window_alpha"]=192;
}
bool get(char *str,int len){
	memset(str,0,1000);
	int n=0;
	do{ch=cin.get();}while(ch==' ');
	if(ch=='\"'){
		ch=cin.get();
		do{
			if(n>len)return 1;
			str[n++]=ch;
			ch=cin.get();
			if(ch=='\\'){
				if(cin.get()=='\"')
					str[n++]='\"',ch=cin.get();
				else cin.unget();
			}
			if(ch=='\n'){
				cin.unget();
				return 1;
			}
		}while(ch!='\"');
	}else{
		do{
			if(n>len)return 1;
			str[n++]=ch;
			ch=cin.get();
			if(ch=='\\'){
				if(cin.get()=='\"')
					str[n++]='\"',ch=cin.get();
				else cin.unget();
			}
		}while(ch!=' '&&ch!='\n');
		cin.unget();
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	system((char*)SERVER_COMMAND);
	initstty();
	SetLayeredWindowAttributes(GetForegroundWindow(),0,istty["window_alpha"],LWA_ALPHA);
	SetCurrentDirectory(getenv("userprofile"));
	setfgConsoleColor(fgLoWhite);
	cout<<"Waiting..."<<endl;
	s=init();
	if(!init_server(s,PORT)){
		setfgConsoleColor(fgHiRed);
		cout<<"Failed to init server."<<endl;
		system("pause");
		closesocket(s),cleansocket();return 0;
	}
	SOCKADDR_IN sad;
	c=getclient(s,&sad);
	setfgConsoleColor(fgLoWhite);
	cip=getip(sad);
	cout<<"Connected client "<<cip<<" successfully."<<endl;
	while(true){
		static bool flag=true,exel=bstty["echo_input"];
		if(bstty["echo_path"]){
			_getcwd(scwd,1000);sendmsg(c,(char*)"cwd",1000);getmsg(c,ccwd,1000);
			setfgConsoleColor(fgLoGreen);
			cout<<"localhost["<<scwd<<"] <=> "<<cip<<"["<<ccwd<<"]\n$ "<<flush;
		}
		setfgConsoleColor(fgLoWhite);cout<<flush;
		scanop:;char ch=cin.get();
		while(ch==' ')ch=cin.get();
		if(ch=='\n')continue;
		cin.unget();get(op,1000);
		if(strcmp(op,"cmdl")==0){
			get(msg,1000);
			if(!exel)cout<<endl;
			system(msg);
		}else if(strcmp(op,"cmdv")==0){
			get(msg,1000);
			if(!exel)cout<<endl;
			sendmsg(c,(char*)"cmdv",1000);
			sendmsg(c,msg,1000);
		}else if(strcmp(op,"cmdd")==0||strcmp(op,"cmd")==0){
			get(msg,1000);
			if(!exel)cout<<endl;
			sendmsg(c,(char*)"cmdd",1000);
			sendmsg(c,msg,1000);
			setfgConsoleColor(fgHiWhite);
			memset(buff,0,1000);
			getmsg(c,buff,1000);
			while(strcmp(buff,"continue")==0){
				memset(buff,0,1000);
				getmsg(c,buff,1000);
				cout<<buff;
				memset(buff,0,1000);
				getmsg(c,buff,1000);
			}
		}else if(strcmp(op,"pull")==0){
			get(msg,1000);get(tmp,1000);
			if(!exel)cout<<endl;
			//msg:From path(on the other computer)
			//tmp:To path(on your own computer)
			sendmsg(c,(char*)"pull",1000);
			sendmsg(c,msg,1000);
			getmsg(c,buff,1000);
			if(strcmp(buff,"OK")!=0){
				setfgConsoleColor(fgHiRed);
				cout<<"Cannot find the file."<<endl;
				flag=false;
			}else{
				FILE *f=fopen(tmp,"wb");
				if(f==nullptr){
					setfgConsoleColor(fgHiRed);
					cout<<"Cannot open the file."<<endl;
					flag=false;
				}else{
					getmsg(c,buff,1000);
					while(strcmp(buff,"0")!=0){
						int len;sscanf(buff,"%d",&len);
						getmsg(c,buff,1000);
						fwrite(buff,1,len,f);
						getmsg(c,buff,1000);
					}
					fclose(f);
				}
			}
		}else if(strcmp(op,"push")==0){
			get(tmp,1000);get(msg,1000);
			if(!exel)cout<<endl;
			//tmp:From path(on your own computer)
			//msg:To path(on the other computer)
			sendmsg(c,(char*)"push",1000);
			FILE *f=fopen(tmp,"rb");
			if(f==nullptr){
				setfgConsoleColor(fgHiRed);
				cout<<"Cannot find the file."<<endl;
				sendmsg(c,ccc,1000);
				flag=false;
			}else{
				sendmsg(c,msg,1000);
				int len=512;
				while(len==512){
					memset(buff,0,1000);
					memset(sss,0,1000);
					len=fread(buff,1,512,f);
					sprintf(sss,"%d",len);
					if(!len||len==EOF)break;
					sendmsg(c,sss,1000);
					sendmsg(c,buff,1000);
				}
				memset(sss,0,1000);sss[0]='0';
				sendmsg(c,sss,1000);fclose(f);
			}
		}else if(strcmp(op,"cdl")==0){
			get(tmp,1000);
			if(!exel)cout<<endl;
			if(_access(tmp,0)==-1){
				setfgConsoleColor(fgHiRed);
				cout<<"Cannot find the path."<<endl;
				flag=false;
			}else SetCurrentDirectory(tmp);
		}else if(strcmp(op,"cdc")==0||strcmp(op,"cd")==0){
			get(tmp,1000);
			if(!exel)cout<<endl;
			sendmsg(c,(char*)"cdc",1000);
			sendmsg(c,tmp,1000);
			getmsg(c,buff,1000);
			if(strcmp(buff,"-1")==0){
				setfgConsoleColor(fgHiRed);
				cout<<"Cannot find the path."<<endl;
				flag=false;
			}
		}else if(strcmp(op,"msg")==0){
			get(msg,1000);get(tmp,1000);get(opt,1000);
			if(!exel)cout<<endl;
			sendmsg(c,(char*)"msg",1000);
			sendmsg(c,msg,1000);
			sendmsg(c,tmp,1000);
			sendmsg(c,opt,1000);
		}else if(strcmp(op,"stty")==0){
			get(tmp,1000);
			if(!exel)cout<<endl;
			char tp=tmp[0];
			if(tp=='+'||tp=='-'){
				bool val=tp^'-';
				memcpy(opt,tmp+1,1000);
				if(!bstty.count(opt)){
					setfgConsoleColor(fgHiRed);
					cout<<"Unknown setting item."<<endl;
					flag=false;
				}else{
					bstty[opt]=val;
					if(strcmp(opt,"echo_input")==0){
						SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),(val?ENABLE_ECHO_INPUT:0)|ENABLE_INSERT_MODE|ENABLE_LINE_INPUT|ENABLE_MOUSE_INPUT|ENABLE_PROCESSED_INPUT|ENABLE_QUICK_EDIT_MODE );
					}
				}
			}else if(tp=='I'){
				int val;
				sscanf(tmp+1,"%[^=]=%d",opt,&val);
				if(!istty.count(opt)){
					setfgConsoleColor(fgHiRed);
					cout<<"Unknown setting item."<<endl;
					flag=false;
				}else{
					istty[opt]=val;
					if(strcmp(opt,"window_alpha")==0){
						SetLayeredWindowAttributes(GetForegroundWindow(),0,val,LWA_ALPHA);
					}
				}
			}else if(tp=='R'){
				double val;
				sscanf(tmp+1,"%[^=]=%lf",opt,&val);
				if(!rstty.count(opt)){
					setfgConsoleColor(fgHiRed);
					cout<<"Unknown setting item."<<endl;
					flag=false;
				}else{
					rstty[opt]=val;
				}
			}else if(tp=='S'){
				char val[1010];
				sscanf(tmp+1,"%[^=]=%s",opt,val);
				if(!sstty.count(opt)){
					setfgConsoleColor(fgHiRed);
					cout<<"Unknown setting item."<<endl;
					flag=false;
				}else{
					sstty[opt]=val;
				}
			}else{
				setfgConsoleColor(fgHiRed);
				cout<<"Unknown setting type."<<endl;
				flag=false;
			}
		}else if(strcmp(op,"exit")==0){
			sendmsg(c,(char*)"exit",1000);
			break;
		}else{
			if(!exel)cout<<endl;
			setfgConsoleColor(fgHiRed);
			cout<<"Unknown Command."<<endl;
			flag=false;
		}
		if(strcmp(op,"cmdl"))cout<<endl;
		ch=cin.get();
		while(ch!='\n'&&ch!=';'&&ch!='&'&&ch!='|')ch=cin.get();
		if(ch!='\n'){
			if(ch==';')goto scanop;
			if(ch=='&'&&flag==1)goto scanop;
			if(ch=='|'&&flag==0)goto scanop;
			while(ch!='\n')ch=cin.get();
		}
	}
	closesocket(s),closesocket(c),cleansocket();
	return 0;
}
