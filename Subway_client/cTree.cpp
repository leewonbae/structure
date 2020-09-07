#include "cTree.h"

cTree::cTree()
{
	mCheckNodeCount = 0;
}
cTree::~cTree()
{

}
void cTree::getFileData()
{
	mFP = fopen("textfile.txt", "r");

	
	int first;
	int last;
	fscanf(mFP, "%d", &first);
	while (!feof(mFP))
	{
		fscanf(mFP, "%d", &first);
		fscanf(mFP, "%d", &last);
		MakeTree(first, last);
	}
	cout << "��ü �ε�" << endl;
	ShowNode();
	fclose(mFP);
}
void cTree::MakeTree(int _first, int _last)
{
	if (mNodeArray[_first] == NULL && mNodeArray[_last] == NULL)
	{
		NODE* newobject = new NODE;
		newobject->mData = _first;
		newobject->mHeadNode = NULL;
		newobject->mLeftNode = NULL;
		newobject->mRightNode = NULL;
		mNodeArray[_first] = newobject;
		NODE* subobject = new NODE;
		subobject->mData = _last;
		subobject->mHeadNode = NULL;
		subobject->mLeftNode = NULL;
		subobject->mRightNode = NULL;
		mNodeArray[_last] = subobject;
	}
	else if (mNodeArray[_first] == NULL)
	{
		NODE* newobject = new NODE;
		newobject->mData = _first;
		newobject->mHeadNode = NULL;
		newobject->mLeftNode = NULL;
		newobject->mRightNode = NULL;
		mNodeArray[_first] = newobject;
	}
	else
	{
		NODE* newobject = new NODE;
		newobject->mData = _last;
		newobject->mHeadNode = NULL;
		newobject->mLeftNode = NULL;
		newobject->mRightNode = NULL;
		mNodeArray[_last] = newobject;
	}
	if (mNodeArray[_first]->mLeftNode == NULL)
	{
		mNodeArray[_first]->mLeftNode = mNodeArray[_last];
		mNodeArray[_last]->mHeadNode = mNodeArray[_first];
	}
	else
	{
		mNodeArray[_first]->mRightNode = mNodeArray[_last];
		mNodeArray[_last]->mHeadNode = mNodeArray[_first];
	}
}
void cTree::ShowNode()
{
	for (int i = 0;i < 10;i++)
	{
		if (mNodeArray[i] != NULL)
		{
			cout << mNodeArray[i]->mData <<"	"<< endl;
		}
	}
}
void cTree::FindNode()
{
	int start;
	int destination;
	
	cout << "�����" << endl;
	cin >> start;
	cout << "������" << endl;
	cin >> destination;

	mCheckNodeCount++;
	mNodeCheck[start] = 1;
	NODE* cur = mNodeArray[start];
	while (1)
	{
		if (cur != mNodeArray[destination])
		{
			if (cur->mLeftNode != NULL && mNodeCheck[cur->mLeftNode->mData]==0)
			{
				cur = cur->mLeftNode;


			}
			else if (cur->mRightNode != NULL && mNodeCheck[cur->mRightNode->mData] == 0)
			{
				cur = cur->mRightNode;

			}
			else
			{
				cur = cur->mHeadNode;

			}
			mCheckNodeCount++;
			mNodeCheck[cur->mData] = 1;
		}
		else
		{
			
			cout << "���� ī��Ʈ���� " << mCheckNodeCount << endl;
			price = mCheckNodeCount * 1000;
			break;
		}
	}
	for(int i=0;i<10;i++)
	{
		mNodeCheck[i] = 0;
	}
	
	mCheckNodeCount = 0;
}
int cTree::getPrice()
{
	return price;
}