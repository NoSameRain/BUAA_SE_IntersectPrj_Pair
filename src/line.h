#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <fstream>
#include "stdlib.h"
using namespace std;
class line
{
public:
	string type; //L R S
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int x2_x1 = 0; //x2 - x1
	int y2_y1 = 0; //y2 - y1
	double k = 0;
	bool ulimited = false; //无斜率;

	void store_coor(string str);
};

extern map<string, int> intersection; //所有交点
extern vector < line > coor_4_line; //每条线的坐标
extern vector < vector<double> > new_inter;
extern int p_cnt, N;
void cnt_coor_num(); //计算交点个数
void calcu_coor(int i, int j);
void test();
void duplicate_remove(double x, double y);
int get_random();
int JudgeType(int i, int j, double x, double y);
int JudgeRadial(int i, double x,double y);
int JudgeSegment(int i, double x, double y);
void Dealwith(line l1, line l2);
