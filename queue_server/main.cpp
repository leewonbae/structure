#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

#define port 7296
#define buffer_size 1024

SOCKET init_server();
void re_sort(int* arry,int total_count);
void event_select(SOCKET sock);
void add_sock(SOCKET sock, SOCKET* sock_array,  WSAEVENT* event_array,int& total_client_num);
void make_array(int* arry, int num, int& total_count);

int main()
{
	SOCKET listen_sock;
	listen_sock=init_server();



	event_select(listen_sock);
	
	
	
	
	
	closesocket(listen_sock);
	WSACleanup();
	return 0;
}
SOCKET init_server()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "error" << endl;
	}
	else
		cout << "init ok" << endl;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);

	if (bind(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout << "bind error" << endl;
	}
	else
		cout << "bind ok" << endl;
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "listen error" << endl;
	}
	else
		cout << "listen ok" << endl;


	return sock;
}

void event_select(SOCKET sock)
{
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	WSANETWORKEVENTS networkevent;
	SOCKET sock_arry[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT event_arry[WSA_MAXIMUM_WAIT_EVENTS];
	
	int num_array[buffer_size];
	int total_client_num = 0;
	int index;
	int total_count=0;
	int count;
	int num;
	add_sock(sock, sock_arry, event_arry, total_client_num);
	// 0번지에는 listen_sock 이 들어가 잇음
	WSAEventSelect(sock, event_arry[total_client_num - 1], FD_ACCEPT | FD_CLOSE);
	
	while (1)
	{
	 
			
		cout << "total_num"<<total_client_num << endl;
		
		index=WSAWaitForMultipleEvents(total_client_num, event_arry, false, WSA_INFINITE, false);
		
		index -= WSA_WAIT_EVENT_0;
		WSAEnumNetworkEvents(sock_arry[index], event_arry[index], &networkevent);
		if (networkevent.lNetworkEvents & FD_ACCEPT)
		{
			int addlen = sizeof(client_addr);
			client_sock = accept(sock_arry[index], (SOCKADDR*)&client_addr, &addlen);
			cout << "클라이언트 접속" << endl;
			add_sock(client_sock, sock_arry, event_arry, total_client_num);
			WSAEventSelect(client_sock, event_arry[total_client_num - 1], FD_READ | FD_WRITE | FD_CLOSE);
		}
		if (networkevent.lNetworkEvents & FD_CLOSE)
		{
			cout << "클라이언트 종료" << endl;
		}
		if (networkevent.lNetworkEvents & FD_READ)
		{
		
			
			if (total_count==0)
			{
				recv(sock_arry[index], (char*)&num, sizeof(int), 0);
				
				count = num;
				cout << "카운트 " << count;
				total_count++;
			}
			else
			{
				recv(sock_arry[index], (char*)&num, sizeof(int), 0);
				cout << "NUM = " << num;
				make_array(num_array, num, total_count);
			}
			
			if (total_count > count)
			{
				re_sort(num_array, count);
				for (int i = 0;i < count;i++)
				{
					send(sock_arry[index], (char*)&num_array[i], sizeof(int), 0);
				}
				total_count = 0;
			}

		}
		
	}
}
void make_array(int *arry,int num,int& total_count)
{
	arry[total_count-1] = num;
	total_count++;
}
void re_sort(int* arry, int total_count)
{
	cout << "sort" << endl;
	cout << "sort count" << total_count<<endl;
	int r_index=0;
	int temp;
	int min;
	for (int k = 0;k < total_count-1;k++)
	{
		
		min = arry[k];
		temp = arry[k];
		for (int i = k+1;i < total_count ;i++)
		{
			if (min > arry[i])
			{
				min = arry[i];
				r_index = i;
			}
		}
		if (min != temp)
		{
			arry[k] = min;
			arry[r_index] = temp;
		}
		
	}
	for (int t = 0;t < total_count;t++)
	{
		cout << arry[t] << endl;
		
	}
}
void add_sock(SOCKET sock,SOCKET *sock_array,WSAEVENT *event_array, int& total_client_num)
{
	SOCKET* new_sock = new SOCKET;
	*new_sock = sock;
	WSAEVENT hevent = WSACreateEvent();

	sock_array[total_client_num] = *new_sock;
	event_array[total_client_num] = hevent;

	total_client_num++;

}

 
