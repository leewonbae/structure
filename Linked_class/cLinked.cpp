#include "cLinked.h"
cLinked::cLinked()
{
	mHead = NULL;
	mTail = NULL;
}
cLinked::~cLinked()
{

}
void cLinked::InsertNum(int _num)
{
	NODE* newnode = new NODE;
	newnode->mPrevNode = NULL;
	newnode->mNextNode = NULL;
	newnode->mNum = _num;

	if (mHead == NULL)
	{
		mHead = newnode;
		
	}
	else
	{
		newnode->mPrevNode = mTail;
		mTail->mNextNode = newnode;
	}

	mTail = newnode;
}

void cLinked::ShowNum()
{
	NODE* cur = mHead;
	while (cur != NULL)
	{
		cout << cur->mNum << endl;
		cur = cur->mNextNode;
	}
}

void cLinked::DeleteNum(int _num)
{
	NODE* cur = mHead;
	NODE* temp;
	while (cur != NULL)
	{

		if (cur->mNum == _num)
		{
			temp = cur;
			if (cur == mHead)
			{
				cout << "head" << endl;
				mHead = cur->mNextNode;

			}
			else
			{
				cout << "±×¿Ü" << endl;
				cur->mPrevNode->mNextNode = cur->mNextNode;
				cur->mNextNode->mPrevNode = cur->mPrevNode;
			}
			cur = cur->mNextNode;
			delete temp;
			continue;
		}
		
		cur = cur->mNextNode;
		
	}
}
