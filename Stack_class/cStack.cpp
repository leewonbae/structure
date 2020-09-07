#include "cStack.h"
cStack::cStack()
{
	mStackCount = 0;
	mHead = NULL;
	mTail = NULL;
}
cStack::~cStack()
{

}
void cStack::Push(int _num)
{
	NODE* newnode = new NODE;
	newnode->mNum = _num;
	newnode->mNextNode = NULL;
	newnode->mPrevNode = NULL;
	if (mHead == NULL)
	{
		mHead = newnode;
		mTail = newnode;
	}
	else
	{
		newnode->mPrevNode = mTail;
		mTail->mNextNode = newnode;
		mTail = newnode;
	}
	
	mStackCount += 1;
}
int cStack::Pop()
{
	NODE* temp;
	temp = mTail;
	
	if (mTail ==NULL)
	{
		return -1;
	}
	else
	{
		mTail = mTail->mPrevNode;
		return temp->mNum;
		
	}
	
}