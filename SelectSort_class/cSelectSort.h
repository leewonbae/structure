#pragma once
#include <iostream>
using namespace std;
class cSelectSort
{
public:
	cSelectSort();
	~cSelectSort();
	void InputData();
	void SelectSort();
	void ShowSortData();
private:
	int mNumArray[10];
};

