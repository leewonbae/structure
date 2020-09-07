#include "cQueue.h"
cQueue::cQueue()
{
	mFront = NULL;
	mRear = NULL;
}
cQueue::~cQueue()
{

}
void cQueue::Enqueue(int _num)
{
	NODE* newnode = new NODE;
	newnode->mNum = _num;
	newnode->mNextNode = NULL;
	newnode->mPrevNode = NULL;

	if (mFront == NULL)
	{
		mFront = newnode;
		
	}
	else
	{
		mRear->mNextNode = newnode;
		newnode->mPrevNode = mRear;
	
	}

	mRear = newnode;
}
void cQueue::ShowData()
{
	NODE* cur = mFront;
	while (cur !=NULL)
	{
		cout << cur->mNum << endl;
		cur = cur->mNextNode;
	}
}
int cQueue::Dequeue()
{
	NODE* temp = mFront;
	mFront = mFront->mNextNode;
	return temp->mNum;
}