#pragma once
#include "resource.h"
class cTree
{
public:
	cTree();
	~cTree();
	 
	void MakeTree(int _first,int _last);
	void ShowNode();
	void FindNode( );
	void getFileData();
	int getPrice();
private:
	FILE* mFP;
	int mNodeCheck[10] = {0,};
	int mCheckNodeCount;
	int price;
	NODE* mNodeArray[10] = {NULL,};
	 
};

