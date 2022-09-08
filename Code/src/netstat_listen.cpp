#include<netstat_listen.h>
#include <client.h>
#include <server.h>

void getListen() //piping two process to perform pipe operation and capture the output of command
{
	int fd[2];
	if(pipe(fd) == -1)
	{
		return perror("pipe");
	}
	int pid1=fork();
	if(pid1==0)
	{
		dup2(fd[1],STDOUT_FILENO);

		close(fd[0]);
		close(fd[1]);

		char* cmd="netstat";
		char *args[]={"netstat","-tanp",NULL};
		cl<<"WARNING : String to Const char*"<<endl;
		execvp(cmd,args);
		exit(EXIT_SUCCESS);
	}
	int pid2=fork();
	if(pid2==0)
	{
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);

		int file=open("listen_File.txt",O_WRONLY | O_CREAT ,0777);
        dup2(file,STDOUT_FILENO);
        close(file);


		char *cmd="grep";
		char *args[]={"grep","-i","LISTEN",NULL};
		execvp(cmd,args);
		exit(EXIT_SUCCESS);
	}
		
		close(fd[0]);
		close(fd[1]);
		
		waitpid(pid1,NULL,0);
        waitpid(pid2,NULL,0);
        sl<<"WARNING : String to Const char*"<<endl;	
		sl<<"INFO : Listen File Created"<<endl;
}

string storeListen()  //read each records from file and return a appended string seperated by |
{
	sl<<"INFO :In StoreListen"<<endl;
	getListen();
	fstream fs;
	string totalData;
	fs.open("listen_File.txt",ios::in|ios::out);
	if(!fs)
	{
		 cout<<"No such File"<<endl;
	}
	else
	{
		string line;				//reading each record to append it
		while(getline(fs,line))
		{
				totalData+=line+"|";
		}
	}
	fs.close();
	return totalData;
	sl<<"INFO :Ended StoreListen"<<endl;
}
void listendriver(string listenData) //main driver dunc responsible for execution
{
	cl<<"INFO : In listenDriver "<<endl;
	list<string> myData;
	char data[7][20];

		string record;
		stringstream str(listenData);			//breaking the appended data and store it in STL
		while(getline(str,record,'|'))
		{
			myData.push_back(record);
		}

		int size=myData.size();
		int i=0;
		netstat_Listen ls[size];

		for(auto it=myData.begin();it!=myData.end();it++)
		{
			string str=*it;
			stringstream st(str);
			string temp;
			int j=0;
			while(st)
			{
				st>>temp;
				if(st)
				{
					strcpy(data[j],temp.c_str());			//parsing again to store into different attributes
					j++;
				}
			}
			ls[i].setProto(data);
			ls[i].setRecv(data);
			ls[i].setSend(data);
			ls[i].setLocal_Address(data);
			ls[i].setForeign_Address(data);
			ls[i].setState(data);
			ls[i].setOthers(data);

			i++;
		}

		for(int i=0;i<size;i++)   //displaying records
		{
			cout<<"-------------- Kernel TCP Table with Listen state dataset "<<i+1<<" ------------------"<<endl;
			cout<<"\tProto :"<<ls[i].getProto()<<endl;
			cout<<"\tRecv-Q :"<<ls[i].getRecv()<<endl;
			cout<<"\tSend-Q :"<<ls[i].getSend()<<endl;
			cout<<"\tLocal Address :"<<ls[i].getLocal_Address()<<endl;
			cout<<"\tForeign Address :"<<ls[i].getForeign_Address()<<endl;
			cout<<"\tState :"<<ls[i].getState()<<endl;
			cout<<"\tOthers :"<<ls[i].getOthers()<<endl;
			cout<<"----------------------------------------------------------"<<endl;
		}

			cl<<"INFO : Ended listenDriver execution "<<endl;
		
}

netstat_Listen :: netstat_Listen()
{}

void netstat_Listen:: setProto(char data[][20])
{
	Proto = data[0];
}
string netstat_Listen:: getProto()
{
	return Proto;
}
void netstat_Listen :: setRecv(char data[][20])
{
	Recv=data[1];
}
string netstat_Listen :: getRecv()
{
	return Recv;
}
void netstat_Listen:: setSend(char data[][20])
{
	 Send=data[2];
}
string netstat_Listen :: getSend()
{
	return Send;
}
void netstat_Listen :: setLocal_Address(char data[][20])
{
	Local_Address=data[3];
}
string netstat_Listen :: getLocal_Address()
{
	return Local_Address;
}
void netstat_Listen :: setForeign_Address(char data[][20])
{
	Foreign_Address=data[4];
}
string netstat_Listen :: getForeign_Address()
{
	return Foreign_Address;
}
void netstat_Listen :: setState(char data[][20])
{
	State=data[5];
}
string netstat_Listen :: getState()
{
	return State;
}
void netstat_Listen :: setOthers(char data[][20])
{
	Others=data[6];
}
string netstat_Listen :: getOthers()
{
	return Others;
}
netstat_Listen ::~netstat_Listen()
{}

