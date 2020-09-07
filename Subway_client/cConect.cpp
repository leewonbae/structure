#include "cConect.h"
 

cConect::cConect()
{

}

cConect::~cConect()
{
    closesocket(mSOCK);
    WSACleanup();
}
void cConect::InitServer()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << " error" << endl;
    }

    mSOCK = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

    connect(mSOCK, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

}


void cConect::OnRecv()
{
    recv(mSOCK, mRecvBuf, BUFFER_SIZE, 0);
    PACKET_HEAD phead;
    memcpy(&phead, mRecvBuf, sizeof(PACKET_HEAD));

    RecvParsing(phead.mCmd,mRecvBuf);
    

}
void cConect::OnSend(char* _inputdata)
{
    send(mSOCK, _inputdata, BUFFER_SIZE, 0);
}
 