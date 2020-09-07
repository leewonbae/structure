#include "resource.h"
#include "cStack.h"
int main()
{
	cStack stack;
	int num;
	int popnum;
	for (int i = 0;i < 5;i++)
	{
		cin >> num;
		stack.Push(num);
	}
	
	while (1)
	{
		popnum = stack.Pop();
		if (popnum == -1)
		{
			break;
		}
		
		cout << popnum << endl;
		
	}

	return 0;
}