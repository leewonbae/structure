#include "cSelectSort.h"
cSelectSort::cSelectSort()
{
}
cSelectSort::~cSelectSort()
{

}

void cSelectSort::InputData()
{
	int num;
	for (int i = 0;i < 10;i++)
	{
		cin >> num;
		mNumArray[i] = num;
	}
}
void cSelectSort::SelectSort()
{
	int min;
	int temp;
	for (int i = 0;i < 9;i++)
	{
		min = i;
		for (int j = i+1;j < 10;j++)
		{
			if (mNumArray[min] > mNumArray[j])
			{
				min = j;
			}
		}
		temp = mNumArray[i];
		mNumArray[i] = mNumArray[min];
		mNumArray[min] = temp;
	}

}
void cSelectSort::ShowSortData()
{
	for (int i = 0;i < 10;i++)
	{
		cout << mNumArray[i] << endl;
	}
}
