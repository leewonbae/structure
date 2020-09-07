#pragma once
#include <iostream>
#include <WinSock2.h>
#include <fstream>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296
#define SERVER_IP "192.168.43.208"

#define FLEG_SEND 1
#define FLEG_RECV 0
#define FLEG_ACCPET 2


#define FIND_PASSWORD_ERROR 1
#define FIND_DATABASE_ERROR 2
#define FIND_OK 3

 

enum  PROTOCOL {
	MSG_NEW_USER_REQ = 0,
	MSG_CHECK_USER_REQ,
	MSG_CHECK_VERSION_REQ,
	MSG_NEW_VERSION_REQ,
	MSG_PAYMENT_REQ,
	MSG_RECHARGE_REQ,


};
struct NODE {
	NODE* mHeadNode;
	int mData;
	NODE* mRightNode;
	NODE* mLeftNode;
};
 
struct PACKET_HEAD {
	int mCmd;
	int mPacketsize;


};
struct PACKET_USERINFO {
	char mName[10];
	int mPassword;
	int mMoney;

};
struct PACKET_FILE {
	char Fdata[100];
	int Fbytes;

};

struct PACKET_USER_CHECK {
	int mCheck;
	// 0 �̻��̸� ������
	// -1 �̸� ���� ����  

};
struct PACKET_VERSION {
	int mVersion;
};
