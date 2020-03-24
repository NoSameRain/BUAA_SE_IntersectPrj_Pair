#pragma once
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
	char type;
	double a = 0;
	double b = 0;
	double c = 0;
	Point p1;
	Point p2;
public:
	//计算a,b,c
	WFLine getLine(Point pt1, Point pt2,char type);
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
extern vector < line > coor_4_line; //每条线的坐标
extern vector < vector<double> > new_inter;
extern set<Point> points;
extern vector<WFLine> wflines;
extern int p_cnt, N;
extern int linenum;

void cnt_coor_num(); //计算交点个数
void calcu_coor(int i, int j);
void test();
void duplicate_remove(double x, double y);
int get_random();
int JudgeType(int i, int j, double x, double y);
int JudgeRadial(int i, double x,double y);
int JudgeSegment(int i, double x, double y);
void Dealwith(line l1, line l2);
void DealwithKexist(line l1, line l2);

void inputHandler(string Filename);
bool NisNum(string str);//处理N
void handleNum(string str);//处理点的形式
void InfinitePoints();
