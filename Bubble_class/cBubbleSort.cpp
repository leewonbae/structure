#include "cBubbleSort.h"
cBubbleSort::cBubbleSort()
{

}
cBubbleSort::~cBubbleSort()
{

}
void cBubbleSort::InputData()
{
	cout << "10 ���� ���ڸ� �Է����ֽÿ�" << endl;
	int inputnum;
	for (int i = 0;i < 10;i++)
	{
		cin >> inputnum;
		num[i] = inputnum;
	}
}
void cBubbleSort::BubbleSort()
{
	int temp;
	
	for (int i = 0;i<10;i++)
	{
		for (int j = 0;j <9 ;j++)
		{
			if (num[j] > num[j+1])
			{
				temp = num[j];
				num[j] = num[j+1];
				num[j+1] = temp;

			}
		}
	}
	
}
void cBubbleSort::ShowSortData()
{
	cout << "���ĵ� ���ڸ� ����մϴ�." << endl;
	for (int i = 0;i < 10;i++)
	{
		cout << num[i] << endl;
	}
}
