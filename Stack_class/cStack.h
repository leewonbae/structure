#pragma once
#include "resource.h"
class cStack
{
public:
	cStack();
	~cStack();
	void Push(int _num);
	int Pop();

private:
	NODE* mHead;
	NODE* mTail;
	int mStackCount;
};

