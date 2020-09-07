#pragma once
#include "resource.h"
#include "cConect.h"
#include "cTree.h"
class cUser : public cConect
{
public:
	cUser();
	~cUser();

	void Play();
	void ShowMainMenu();
	void InSUBWAY();
	void InputUserData();
	bool ShowSubwayMenu();
	bool CheckUser(int _check);
	bool VersionCheck();
	void FindLoad();
	void RechargeMoney();
	void SetFile(char* _ptr);
	
	virtual void RecvParsing(int _pasingnum, char* _ptr) ;
private:
	cTree mtree;
	PACKET_HEAD phead;
	PACKET_USERINFO puser;
	FILE* mTextfile;
	bool mSubwayPlay;
	char mDataBuf[BUFFER_SIZE];
	bool mPlayGame;
	char mName[10];
	int mPassword;
	int mSubwayPrice;
	bool mCheckVersion;
	
};

