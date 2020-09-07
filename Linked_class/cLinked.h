#pragma once
#include "resource.h"
class cLinked
{
public:
	cLinked();
	~cLinked();
	void InsertNum(int _num);
	void ShowNum();
	void DeleteNum(int _num);
private:
	NODE* mHead;
	NODE* mTail;
};

