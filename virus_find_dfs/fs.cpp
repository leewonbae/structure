#include "fs.h"

fs::fs()
{
	node_count = 0;
	match_count = 0;
	virus_count = 0;
	stack_count = 0;
	stack = new int[stack_count];
	visitflag = new bool[node_count];
	
}
fs::~fs()
{

}
void fs::visit_init(bool* _flag)
{
	for (int i = 1;i < node_count + 1;i++)
	{
		_flag[i] = false;
	}
}
void fs::input_count(int _node_count, int _match_count)
{
	node* s_node;
	s_node = new node[_node_count+1];

	int a = 0;
	int from;
	int to;
	while (a < _match_count)
	{
		cin >> from;
		cin >> to;
		
		list_input(s_node,from,to);
		list_input(s_node, to, from);
		a=a+1;
	}
	show(_node_count, s_node);
	int virus;
	cout << "감염 컴퓨터를 입력" << endl;
	cin >> virus;
	virus_show(s_node, virus, &virus_count);
}
void fs::list_input(node* main_node,int fromV, int toV)
{
	node* newobject = new node;
	newobject->data = toV;
	newobject->next_node = NULL;
	if (main_node[fromV].main_head==NULL)
	{
		main_node[fromV].main_head = newobject;
	
	}
	else
	{
		main_node[fromV].main_tail->next_node = newobject;
		
	}
	main_node[fromV].main_tail = newobject;
	
	cout << "입력 되었습니다." << fromV << "부터 " << toV << "까지" << endl;
}
void fs::show(int _node_count, node* main_node)
{
	node* cur;
	 
	for (int i = 1;i < _node_count+1;i++)
	{
		cout << i << " 번   노드" << endl;
		cur = main_node[i].main_head;
		
		cout << cur->data << endl;

		while (cur->next_node != NULL)
		{
			 
			
			cur = cur->next_node;
			cout << cur->data << endl;
			
			
		}
		 
	}
}
void fs::stack_input(int _data)
{
	stack[stack_count] = _data;
	cout << "데이터 " << _data << "가 " << stack_count << "에 저장되었습니다." << endl;
	stack_count++;
}
int fs::pop()
{
	int last_pop;
	last_pop = stack[stack_count-1];
	
	return last_pop;
	
}
void fs:: virus_show(node* main_node, int _virus, int* count)
{
	visit_init(visitflag);
	node* cur;
	cur = main_node[_virus].main_head;
	stack_input( _virus);
	while (stack_count > 0)
	{
		int return_pop = pop();
		
		cur = main_node[return_pop].main_head;
		if (visitflag[return_pop] == false)
		{
			
			visitflag[return_pop] = true;
			if (find_stack(cur->data)== false)
			{
			 
				stack_input( cur->data);
				*count = *count + 1;
				
				
			}
			
			while (cur->next_node != NULL)
			{
				cur = cur->next_node;
				
				if (find_stack(cur->data) == false && visitflag[cur->data] == false)
				{
					stack_input( cur->data);
					*count = *count + 1;
					
				}
				
			}
		}
		else
		{
			cout << "전 노드를 봅니다." << endl;
			stack_count = stack_count - 1;

		}
	}
	cout << " 감염 count = " << *count << endl;
	
}
int fs::find_stack(int _data)
{
	for (int i = 0;i < stack_count;i++)
	{	
		
		
		if (stack[i] == _data)
		{
			
			return true;
			continue;
		}
	
	
	}
	return false;
	
}
void fs::menu()
{
	cout << " 노드의 갯수를 입력해라" << endl;
	cin >> node_count;
	cout << "짝의 갯수를 입력해라" << endl;
	cin >> match_count;
	input_count(node_count, match_count);

	
	

}