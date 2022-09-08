#include<netstat_udp.h>
#include<client.h>
#include <server.h>

void getUDP_Table() //Capture the output of the commands in a file
{
	if(fork()==0)
	{
	
		int file=open("udpFile.txt",O_WRONLY | O_CREAT ,0777);
		dup2(file,STDOUT_FILENO); //copyning from one FD to Other
		close(file);
		char* cmd="netstat";
		char *args[]={"netstat","-uan",NULL};	
		sl<<"WARNING : String to Const char*"<<endl;
		sl<<"INFO : UDP File Created"<<endl;
		execvp(cmd,args);
		exit(EXIT_SUCCESS);
	}
	
}

string storeUDP_Table()  //read each records from file and return a appended string seperated by |
{
	sl<<"INFO :In StoreUDPTable"<<endl;
	getUDP_Table();
	fstream fs;
	string totalData;
	fs.open("udpFile.txt",ios::in|ios::out);
	if(!fs)
	{
		cout<<"No such File"<<endl;
	}
	else
	{
		int count =0;
		string line;
		while(getline(fs,line)) //reading the records and appending
		{
			count++;
			if(count>2)
				totalData+=line+"|";
			else
				continue;
		}
	}
	fs.close();
	return totalData;
	sl<<"INFO :Ended StoreUDPTable"<<endl;
}
void UDPdriver(string udpData)			//main driver function responsible for execution
{
	cl<<"INFO :In TCPdriver Execution"<<endl;
	list<string> myData;
	char data[6][20];

		string record;
		stringstream str(udpData);
		while(getline(str,record,'|'))
		{
			myData.push_back(record);
		}

		int size=myData.size();
		int i=0;
		netstatUDP udp[size];

		for(auto it=myData.begin();it!=myData.end();it++)
		{
			string str=*it;
			stringstream st(str);
			string temp;
			int j=0;
			while(st)				//parsing again to store each attributes
			{
				st>>temp;
				if(st)
				{
					strcpy(data[j],temp.c_str());
					j++;
				}
			}
			udp[i].setProto(data);
			udp[i].setRecv(data);
			udp[i].setSend(data);
			udp[i].setLocal_Address(data);
			udp[i].setForeign_Address(data);
			udp[i].setState(data);

			i++;
		}

		for(int i=0;i<size;i++)  //displaying
		{
			cout<<"-------------- Kernel UDP Table Dataset "<<i+1<<" ------------------"<<endl;
			cout<<"\tProto :"<<udp[i].getProto()<<endl;
			cout<<"\tRecv-Q :"<<udp[i].getRecv()<<endl;
			cout<<"\tSend-Q :"<<udp[i].getSend()<<endl;
			cout<<"\tLocal Address :"<<udp[i].getLocal_Address()<<endl;
			cout<<"\tForeign Address :"<<udp[i].getForeign_Address()<<endl;
			cout<<"\tState :"<<udp[i].getState()<<endl;
			cout<<"-----------------------------------------------------"<<endl;
		}

			cl<<"INFO :Ended TCPdriver Execution"<<endl;
}

netstatUDP :: netstatUDP()
{}

void netstatUDP :: setProto(char data[][20])
{
	Proto=data[0];	
}
string netstatUDP :: getProto()
{
	return Proto;
}
void netstatUDP :: setRecv(char data[][20])
{
	Recv=data[1];
}
string netstatUDP :: getRecv()
{
	return Recv;
}
void netstatUDP :: setSend(char data[][20])
{
	Send=data[2];
}
string netstatUDP :: getSend()
{
	return Send;
}
void netstatUDP :: setLocal_Address(char data[][20])
{
	Local_Address=data[3];
}
string netstatUDP :: getLocal_Address()
{
	return Local_Address;
}
void netstatUDP :: setForeign_Address(char data[][20])
{
	Foreign_Address=data[4];
}
string netstatUDP :: getForeign_Address()
{
	return Foreign_Address;
}
void netstatUDP :: setState(char data[][20])
{
	State=data[5];
}
string netstatUDP :: getState()
{
	return State;
}
netstatUDP::~netstatUDP()
{}
