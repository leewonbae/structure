#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
enum { wall = 0, road, start, goal };
#define garo_size 20
#define sero_size 20
class treenode {
private:
	int top_left;
	int top_right;
	int bottom_left;
	int bottom_right;
public:
	treenode()
	{
		top_left = 0;
		top_right = 0;
		bottom_left = 0;
		bottom_right = 0;

	}
	~treenode()
	{ 
	}
	void set_data(int _top_left, int _top_right, int _bottom_left, int _bottom_right)
	{
		top_left = _top_left;
		top_right = _top_right;
		bottom_left = _bottom_left;
		bottom_right = _bottom_right;
	}
	int garo_division_data()
	{
		int g_data;
		g_data = (bottom_right - top_right) /2;
		return g_data;
	}
	int sero_division_data()
	{
		int s_data;
		s_data = (bottom_left - top_left) / 2;
		return s_data;
	}
	void garo_division_set_data(treenode* main, bool mode)
	{
		int g_data;
		g_data = main->garo_division_data();
		if (mode == true)
		{
		 
			this->set_data(main->top_left, main->top_right, main->bottom_left, main->bottom_right-g_data);
		}
		else
		{
			 
			this->set_data(main->top_left, main->top_right+g_data, main->bottom_left, main->bottom_right);

		}
	}
	void sero_division_set_data(treenode* main, bool mode)
	{
		int s_data;
		s_data = main->sero_division_data();
		if (mode == true)
		{
		 
			this->set_data(main->top_left, main->top_right, main->bottom_left - s_data, main->bottom_right );
		}
		else
		{
		 
			this->set_data(main->top_left + s_data, main->top_right, main->bottom_left, main->bottom_right);

		}
	}
	void show_data()
	{
		cout << top_left << endl;
		cout << top_right << endl;
		cout << bottom_left << endl;
		cout << bottom_right << endl;
	}
	int start_x()
	{
		return top_left;
	}
	int start_y()
	{
		return top_right;
	}
	int end_x()
	{
		return bottom_left;
	}
	int end_y()
	{
		return bottom_right;
	}
};
 


class maze {
private:
	int map[garo_size][sero_size];
	int division_count;
	int horizon;
	int vertical;
	int map_object_count;
	int node_count ;
	int map_list_count;
	int temp;
	int count;
	treenode main_map_data;// 필요 없을 듯
	treenode* main_tree_list;
	
	
public:
	maze();
	~maze();
	
	void maze_init();// 20 x 20 짜리 칸 만들기
	void maze_change_block(); // 숫자를 블록으로 바꿔주기
	void map_division(int _input_division,int rand_mode);// 맵 분할 
	void show_maze_main(); // 맵출력
	int check_block();// 위 아래 앞 블록 체크
	void change_block(int _temp);
	int make_rode(int mode, int _start_x, int _start_y, int _end_x, int _end_y);
	void compare(int* axis_data_arr, int* fix_data_arr, int _temp);
};