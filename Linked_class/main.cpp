
#include "resource.h"
#include "cLinked.h"
int main()
{
	cLinked link;
	int num;
	cout << "������ �Է�" << endl;
	for (int i = 0;i < 5;i++)
	{
		cin >> num;
		link.InsertNum(num);
	}
	link.ShowNum();

	cout << "������ ���� ����" << endl;
	cin >> num;
	link.DeleteNum(num);

	cout << "��ȭ�� ����Ʈ ���" << endl;
	link.ShowNum();
	return 0;
}