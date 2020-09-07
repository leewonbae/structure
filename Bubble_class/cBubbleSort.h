#pragma once
#include <iostream>
using namespace std;
class cBubbleSort
{
public:
	cBubbleSort();
	~cBubbleSort();
	void InputData();
	void BubbleSort();
	void ShowSortData();
private:
	int num[10];
};

