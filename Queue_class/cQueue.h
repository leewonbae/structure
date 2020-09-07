#pragma once
#include "resource.h"
class cQueue
{
public:
	cQueue();
	~cQueue();
	void Enqueue(int _num);
	int Dequeue();
	void ShowData();
private:
	NODE* mFront;
	NODE* mRear;

};

