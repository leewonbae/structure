#include "maze_make.h"
maze::maze()
{
	srand((unsigned int)time(NULL));
	maze_init();
	division_count = 0;
	horizon = garo_size;
	vertical = sero_size;
	map_object_count = 1;
	node_count = 1;
	main_map_data.set_data(0, 0, garo_size, sero_size);
	map_list_count = 1;
	main_tree_list = new treenode[100];
	temp = 0;
	count = 0;
}
maze::~maze()
{
	 
}
int maze::check_block()
{
	// 위 아래 앞 
	 
	return true;
}// 구현 해야함
void maze::maze_init()
{
	for (int i = 0;i < garo_size;i++)
	{
		for (int j = 0;j < sero_size;j++)
		{
			map[i][j] = wall;
		}
	}
}

void maze::maze_change_block()
{
	for (int i = 0;i < garo_size;i++)
	{
		for (int j = 0;j < sero_size;j++)
		{
			
			if (map[i][j] == wall)
			{
				cout << "■" ;
			}
			if(map[i][j]== road)
			{
				cout <<"  " ;
			}
			
		}
		cout << endl;
	}
}



void maze::map_division(int _input_division, int rand_mode)
{
 
	
	
	if (division_count == _input_division)
	{
	 
		
		change_block(temp);
		maze_change_block();
		return ;
	}
 
	int cur = (node_count + 1) / 2;
 
	temp = cur*2;
	bool mode_check = true;
	
	
	if (map_object_count == 1)
	{
	
		main_tree_list[map_list_count] = main_map_data ;
		map_list_count++;
	}
	
	 
		map_object_count = map_object_count * 2;
		
	 
		treenode* newobject = new treenode[map_object_count];
	 
		node_count = node_count + map_object_count;
	 
		if (rand_mode == 1)
		{
			
		 
			for (int a = 0;a < map_object_count; a++)
			{
				if (mode_check)
				{
				
					newobject[a].garo_division_set_data(&main_tree_list[cur], mode_check);
					 
					mode_check = false;
				}
				else 
				{
					
					newobject[a].garo_division_set_data(&main_tree_list[cur], mode_check);
					 
					cur = cur + 1;
					
					mode_check = true;
				}
				
				main_tree_list[map_list_count ] = newobject[a];
				map_list_count++;
				
				
				
			}
			division_count++;
			delete[] newobject;
			map_division(_input_division, 2);
		}
		else
		{
			 
			for (int a = 0; a < map_object_count; a++)
			{
				if (mode_check)
				{
					
					newobject[a].sero_division_set_data(&main_tree_list[cur], mode_check);
					 
					mode_check = false;
				}
				else
				{
			
					newobject[a].sero_division_set_data(&main_tree_list[cur], mode_check);
					 
					cur = cur + 1;
					mode_check = true;
				}

				main_tree_list[map_list_count] = newobject[a];
				map_list_count++;
				


			}
			division_count++;
			delete[] newobject;
			map_division(_input_division, 1);
		}
	
	

}
int maze::make_rode(int mode,int _start_x,int _start_y, int _end_x,int _end_y)
{
	int x = _end_x - _start_x-2;
	int y = _end_y - _start_y-2;
	int num;
	count++;
	cout <<"count" <<count << endl;
	if (mode == 1)
	{
		num = rand() % y+1;
		cout <<"num"<< num<<endl;
		return num;
	}
	else if (mode == 2)
	{
		num = rand() % x+1;
		cout <<"num"<< num << endl;;
		return num;
	}
	
}
void maze::change_block(int _temp)
{
	if (_temp < 1)
	{
		cout << "탈출" << endl;
		return;
	}
	int change_cur = _temp;
	
	 
	
	for (int all=0; all < _temp;all++)
	{
		int rand_num = rand() % 2 + 1;
		cout << rand_num << "random num" << endl;
		int start_x = main_tree_list[change_cur].start_x();
		int start_y = main_tree_list[change_cur].start_y();
		int end_x = main_tree_list[change_cur].end_x();
		int end_y = main_tree_list[change_cur].end_y();
		int fix_num = make_rode(rand_num, start_x, start_y, end_x, end_y);
		
		for (int a=start_y+1;a<(end_y)-1;a++)
		{
			for (int b=start_x+1;b<(end_x)-1;b++)
			{
				if (rand_num == 1 && a== (start_y + fix_num))//여기가 픽스되면 가로 
				{
					
					map[a][b] = road;
				
				}
				else if (rand_num == 2 && b== (start_x +fix_num))// 여기가 픽스되면 세로
				{
					
					map[a][b] = road;
				
				}
				
				
			}
			 
		}
		change_cur++;
	
	 
	}
	change_block(_temp / 2);
}
void maze::compare(int* axis_data_arr, int* fix_data_arr, int _temp)
{
	int a = 0;
	for (int a = 0;a < _temp;a++)
	{
		if (axis_data_arr[a] == 1 && axis_data_arr[a + 1] == 2)
		{

		}
		if (axis_data_arr[a] == 2 && axis_data_arr[a + 1] == 1)
		{

		}
		if (axis_data_arr[a] == 2 && axis_data_arr[a + 1] == 2)
		{

		}
		if (axis_data_arr[a] == 1 && axis_data_arr[a + 1] == 1)
		{

		}
	}
}
void maze::show_maze_main()
{
	maze_init();
	maze_change_block();
	int input_division;
	int mode = 1;//rand() % 2 + 1;// 1은가로2는 세로 
	cout << "나눌 횟수 입력 가로 부터" << endl;
	cin >> input_division;
	map_division(input_division, mode);
	
	
	

}