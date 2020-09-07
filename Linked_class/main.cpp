
#include "resource.h"
#include "cLinked.h"
int main()
{
	cLinked link;
	int num;
	cout << "데이터 입력" << endl;
	for (int i = 0;i < 5;i++)
	{
		cin >> num;
		link.InsertNum(num);
	}
	link.ShowNum();

	cout << "임의의 숫자 제거" << endl;
	cin >> num;
	link.DeleteNum(num);

	cout << "변화된 리스트 출력" << endl;
	link.ShowNum();
	return 0;
}