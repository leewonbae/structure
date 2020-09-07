#pragma once
#include<iostream>
using namespace std;

struct node {
	int data;
	node* next_node;
	node* main_head;
	node* main_tail;
	//node* right;
	node()
	{
		data = 0;
		next_node = NULL;
		main_head = NULL;
		main_tail = NULL;

	}
	~node()
	{

	}
};
class fs {
private:
	bool* visitflag;
	int node_count;
	int match_count;
	int virus_count;
	int* stack;
	int stack_count;
public:
	fs();
	~fs();
	void visit_init(bool* _flag);
	void input_count(int _node_count, int _match_count);
	void menu();
	void list_input(node* main_node,int fromV, int toV);
	void show(int _node_count, node* main_node);
	void virus_show(node* main_node, int _virus,int* count);
	void stack_input( int _data);
	int pop( );
	int find_stack(int _data);
};