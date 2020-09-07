#include <iostream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
#define buffer_size 1024
#define port 7296
#define max_x 10
#define max_y 10
using namespace std;

struct node_info
{
	int node_a;
	int node_b;
};
struct user_info
{
	SOCKET sock;
	int node_count;
	
};
SOCKET init_sock();
void dfs(SOCKET in_sock,int mat[][max_x],int start, int* dfs_visit);
void make_rode_information(int matrix[][max_x],node_info n_info);
void event_select(SOCKET sock);
void add_array(user_info* s_array, SOCKET client_sock, int& num, WSAEVENT* e_array);
int main()
{
	SOCKET sock= init_sock();
	event_select(sock);

	closesocket(sock);
	WSACleanup();
	return 0;
}

void add_array(user_info* s_array,SOCKET client_sock, int &num, WSAEVENT* e_array)
{
	user_info* new_user_info = new user_info;
	new_user_info->sock = client_sock;
	new_user_info->node_count = 0;
	

	s_array[num] = *new_user_info;
	WSAEVENT new_event = WSACreateEvent();
	e_array[num] = new_event;
	num++;
}
void event_select(SOCKET sock)
{
	SOCKET listen_sock = sock;
	SOCKET client_sock;
	SOCKADDR client_addr;
	int total_num = 0;
	user_info sockarray[FD_SETSIZE];
	WSAEVENT eventarray[FD_SETSIZE];
	int mat[10][10] = {0};
	int visit[10] = {0};
	WSANETWORKEVENTS find_event;
	add_array(sockarray,listen_sock ,total_num, eventarray);
	WSAEventSelect(listen_sock, eventarray[total_num - 1], FD_ACCEPT | FD_CLOSE);
	int index;
	int addrlen;
	int m_node_count;
	int start;
	
	while (1)
	{
		
		addrlen = sizeof(client_addr);
		index=WSAWaitForMultipleEvents(total_num, eventarray, false, WSA_INFINITE, false);
		index -= WSA_WAIT_EVENT_0;
		WSAEnumNetworkEvents(sockarray[index].sock, eventarray[index], &find_event);
		
		if (find_event.lNetworkEvents & FD_ACCEPT)
		{
			cout << "accept ok" << endl;
			client_sock = accept(listen_sock, (SOCKADDR*)&client_addr, &addrlen);
			
			add_array(sockarray, client_sock, total_num, eventarray);
			WSAEventSelect(client_sock, eventarray[total_num - 1], FD_READ | FD_WRITE | FD_CLOSE);

		}
		if (find_event.lNetworkEvents & FD_READ)
		{
			if (sockarray[index].node_count == 0)
			{
				mat[10][10] = { 0 };
				visit[10] = { 0 };
				start = 0;
				recv(sockarray[index].sock, (char*)&m_node_count, sizeof(int), 0);
				sockarray[index].node_count = m_node_count;
				cout << m_node_count << "  노드 개수" << endl;
				
			}
			else
			{
				if (start == 0)
				{
					recv(sockarray[index].sock, (char*)&start, sizeof(int), 0);
					cout << "start" << start << endl;
					continue;
				}

				node_info newobject;
				cout << "노드 정보" << endl;
				recv(sockarray[index].sock, (char*)&newobject, sizeof(node_info),0);
				cout << newobject.node_a << endl;
				cout << newobject.node_b << endl;
				if (newobject.node_a == -1 && newobject.node_b == -1)
				{
					cout << "길찾기 시작" << endl;
					dfs(sockarray[index].sock,mat, start, visit);
					sockarray[index].node_count=0;
					
				}
				else
				{
					make_rode_information(mat, newobject);

				}
				
				
				
			}
			
		}
		if (find_event.lNetworkEvents & FD_CLOSE)
		{
			cout << "종료" << endl;
		}
	}

}
void dfs(SOCKET in_sock,int mat[][max_x],int start,int* dfs_visit)
{
	cout << "dfs" << endl;
	for (int a = 0;a < 10;a++)
	{
		for (int b = 0;b < 10;b++)
		{
			cout << mat[a][b];
		}
		cout << endl;
	}
	dfs_visit[start] = 1;
	cout << start << endl;
	send(in_sock, (char*)&start, sizeof(int), 0);
		for (int j = 0;j < 10;j++)
		{
			if (mat[start][j] == 1  && dfs_visit[j]==0)
			{
				dfs(in_sock,mat, j, dfs_visit);

			}
		}
		
	
	
}
void make_rode_information(int matrix[][max_x],node_info n_info)
{
	matrix[n_info.node_a][n_info.node_b] = matrix[n_info.node_b][n_info.node_a]= 1;
}
SOCKET init_sock()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);

	if (bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout << "bind error" << endl;
	}
	else
		cout << "bind ok" << endl;
	if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "listen error" << endl;
	}
	else
		cout << "listen ok" << endl;

	return listen_sock;
}