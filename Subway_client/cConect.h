#pragma once
#include "resource.h"
class cConect
{
public:
	cConect();
	~cConect();
	void InitServer();
 
	void OnSend(char* _inputdata);
	void OnRecv();

	 
	virtual void RecvParsing(int _pasingnum,char* _ptr)=0;
private:
	char mRecvBuf[BUFFER_SIZE];
	SOCKET mSOCK;

};

