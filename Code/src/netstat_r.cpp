#include<netstat_r.h>
#include <client.h>
#include <server.h>

void getRoutingTable() //Capture the output of the commands in a file
{
		if(fork()==0)
		{
			int file=open("rtFile.txt",O_WRONLY | O_CREAT ,0777);
			dup2(file,STDOUT_FILENO); //redireting the output of STDOUT  to our file.
			close(file);
			char* cmd="netstat";
			char *args[]={"netstat","-r",NULL};	
			sl<<"WARNING : String to Const char*"<<endl;
			sl<<"INFO : RT file Created"<<endl;
			execvp(cmd,args);
			exit(EXIT_SUCCESS);
		}
		wait(0);	
}

string storeRoutingTable() //read each records from file and return a appended string seperated by |
{
	sl<<"INFO : In Store Routing Table"<<endl;
	getRoutingTable();
	fstream fs;
	string totalData;
	fs.open("rtFile.txt",ios::in|ios::out);
	if(!fs)
	{
		sl<<"ERROR : No such File"<<endl;
	}
	else
	{
		int count =0;
		string line;
		while(getline(fs,line))			//reading each line from the file and appending it
		{
			count++;
			if(count>2)
				totalData+=line+"|";
			else
				continue;
		}
	}
	fs.close();
	sl<<"INFO : Ended Store Routing Table"<<endl;
	return totalData;

}

void RTdriver(string totalData)  //main driver function responsible for execution
{

	cl<<"INFO : In RTdriver"<<endl;
	char data[8][20];
	list<string> myData;

	string record;
	stringstream str(totalData);
	while(getline(str,record,'|'))		//breaking the rawData to store in an STL
	{
		myData.push_back(record);
	}
	
	int size=myData.size();
	int i=0;
	RoutingTable rt[size];

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
					strcpy(data[j],temp.c_str()); //parse again to store values into different attributes
					j++;
				}
			}
			rt[i].setDestination(data);
			rt[i].setGateway(data);
			rt[i].setGenmask(data);
			rt[i].setFlags(data);
			rt[i].setMss(data);
			rt[i].setWindow(data);
			rt[i].setirtt(data);
			rt[i].setIface(data);

			i++;
	}
	
	for(int i=0;i<size;i++) //displaying respect to objects
	{
		cout<<"-------------- Kernel Routing Table DataSet "<<i+1<<"------------------"<<endl;
		cout<<"\tDESTINATION :"<<rt[i].getDestination()<<endl;
		cout<<"\tGATEWAY :"<<rt[i].getGateway()<<endl;
		cout<<"\tGENMASK :"<<rt[i].getGenmask()<<endl;
		cout<<"\tFLAGS :"<<rt[i].getFlags()<<endl;
		cout<<"\tMSS :"<<rt[i].getMss()<<endl;
		cout<<"\tWINDOW :"<<rt[i].getWindow()<<endl;
		cout<<"\tIRTT :"<<rt[i].getirtt()<<endl;
		cout<<"\tIFACE :"<<rt[i].getIface()<<endl;
		cout<<"----------------------------------------------"<<endl;
	}

	cl<<"INFO : Finished Executions"<<endl;

}

RoutingTable :: RoutingTable()
{}

void RoutingTable :: setDestination(char data[][20])
{
	Destination=data[0];	
}
string RoutingTable :: getDestination()
{
	return Destination;
}
void RoutingTable :: setGateway(char data[][20])
{
	Gateway=data[1];
}
string RoutingTable :: getGateway()
{
	return Gateway;
}
void RoutingTable :: setGenmask(char data[][20])
{
	Genmask=data[2];
}
string RoutingTable :: getGenmask()
{
	return Genmask;
}
void RoutingTable :: setFlags(char data[][20])
{
	Flags=data[3];
}
string RoutingTable :: getFlags()
{
	return Flags;
}
void RoutingTable :: setMss(char data[][20])
{
	Mss=data[4];
}
string RoutingTable :: getMss()
{
	return Mss;
}
void RoutingTable :: setWindow(char data[][20])
{
	Window=data[5];
}
string RoutingTable :: getWindow()
{
	return Window;
}
void RoutingTable :: setirtt(char data[][20])
{
	irtt=data[6];
}
string RoutingTable :: getirtt()
{
	return irtt;
}
void RoutingTable :: setIface(char data[][20])
{
	Iface=data[7];
}
string RoutingTable :: getIface()
{
	return Iface;
}

RoutingTable::~RoutingTable()
{}
