#include "resource.h"
#include "cQueue.h"
int main()
{
	cQueue queue;
	int num;
	for (int i = 0;i < 5;i++)
	{
		cin >> num;
		queue.Enqueue(num);

	}
	cout << "�Է� �� ���� ���" << endl;
	queue.ShowData();
	int dequeNUM;
	cout << "�Է� �� ���� Dequeue" << endl;
	for (int j = 0;j < 5;j++)
	{
		dequeNUM = queue.Dequeue();
		cout << dequeNUM << endl;
	}
	
	return 0;
}