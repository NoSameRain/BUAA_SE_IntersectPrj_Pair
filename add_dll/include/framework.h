#pragma once

#define DLL_API __declspec(dllexport) 
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <fstream>
#include <set>
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

class Point {
public:
	double Xpoint = 0;
	double Ypoint = 0;

public:
	Point() {}
	Point(double x, double y) {
		Xpoint = x;
		Ypoint = y;
	}
	string showPoint();
	bool operator<(const Point& a)const
	{
		if (Xpoint != a.Xpoint) {
			return Xpoint < a.Xpoint;
		}
		else {
			return Ypoint < a.Ypoint;
		}
	}

	bool operator == (const Point& p) const
	{
		if (Xpoint != p.Xpoint) {
			return false;
		}
		else {
			return Ypoint == p.Ypoint;
		}
	}
};


class WFLine :public Point {
public:
	char type='L';
	double a = 0;
	double b = 0;
	double c = 0;
	Point p1;
	Point p2;
public:
	//计算a,b,c
	WFLine getLine(Point pt1, Point pt2, char type);
	//获得交点
	bool operator < (const WFLine& lx) const
	{
		if (a != lx.a) {
			return a < lx.a;
		}
		else if (b != lx.b) {
			return b < lx.b;
		}
		else {
			return c < lx.c;
		}
	}

};
extern map<string, int> intersection; //所有交点
extern vector <line> coor_4_line; //每条线的坐标
extern vector < vector<double> > new_inter;
extern set<Point> points;
extern int p_cnt, N;

extern int linenum;
extern vector<WFLine> wflines;//wf NEW ADD


void calcu_coor(int i, int j);
void test();
void duplicate_remove(double x, double y);
int get_random();
int JudgeType(int i, int j, double x, double y);
int JudgeRadial(int i, double x, double y);
int JudgeSegment(int i, double x, double y);
void Dealwith(line l1, line l2);
void DealwithKexist(line l1, line l2);

DLL_API void clear();//	intersection.clear();coor_4_line.clear();points.clear();	wflines.clear();N = 0;linenum = 0;
DLL_API void cnt_coor_num(); //计算交点个数
DLL_API set<Point> getPoints();//返回交点
DLL_API vector<line> getLine();//返回直线集合
DLL_API void readin(string FileName);//读入数据
DLL_API void addLine(line l);//添加直线
DLL_API void delLine(line l);//删除直线
DLL_API void solve();//求解
DLL_API int getP_cnt();//获得交点个数
DLL_API int getInterNum();//intersection size
DLL_API int getPointNum();//points size
DLL_API void write(string FileName);//写入文件
DLL_API string inputHandler(string FileName);//从文件读入数据时进行错误处理 正常应返回 "Everything is ok!"
DLL_API string InfinitePoints();//判断线之间是否重合 正常应返回"NO InfinitePoints!"

string NisNum(string str);//处理N
string handleNum(string str);//处理点的形式 //此两个个函数由inputHandler进行调用

