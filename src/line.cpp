#include "line.h"
using namespace std;

vector < line > coor_4_line; //每条线的坐标
map<string, int> intersection; //所有交点
int N;
int p_cnt = 0;

void line::store_coor(string str)
{
	vector<string> res;//用于存放分割后的字符串 
	string result;//暂存从str中读取的字符串 
	stringstream input(str);//将字符串读到input中 
	while (input >> result)
		res.push_back(result);//依次输出到result中，并存入res中 
	type = res[0];
	x1 = stoi(res[1], 0, 10);
	y1 = stoi(res[2], 0, 10);
	x2 = stoi(res[3], 0, 10);
	y2 = stoi(res[4], 0, 10);;
	x2_x1 = stoi(res[3], 0, 10) - stoi(res[1], 0, 10);
	y2_y1 = stoi(res[4], 0, 10) - stoi(res[2], 0, 10);
	if (x2_x1 == 0)
	{
		ulimited = true;
	}
	else
	{
		k = y2_y1 * 1.0 / x2_x1;
	}
}

void cnt_coor_num()
{
	int i, j;
	for (i = 0;i < N;i++)
		for (j = i + 1;j < N;j++)
		{
			if (coor_4_line[i].ulimited == true || coor_4_line[j].ulimited == true) 
			{
				if (coor_4_line[i].ulimited != coor_4_line[j].ulimited)
				{//一个有 一个没有
					calcu_coor(i, j);
				}
				else { //都没有斜率
					if (coor_4_line[i].x1 == coor_4_line[j].x1) {
						Dealwith(coor_4_line[i], coor_4_line[j]);//斜率不存在的SS SR RR
					}
				}
			}
			else //都有斜率
			{
				if (coor_4_line[i].k != coor_4_line[j].k)//都有且不相等
				{
					calcu_coor(i, j);
				}
				else //都有且相等（针对S R)
				{
					Dealwith(coor_4_line[i], coor_4_line[j]);
				}
			}
		}
}

void calcu_coor(int i, int j)
{
	double x, y, xa;
	int ya, yb, xb;
	xa = 0;
	ya = ((-coor_4_line[i].y2_y1) * (coor_4_line[j].y2_y1) * coor_4_line[i].x1 +
		(coor_4_line[j].y2_y1) * (coor_4_line[i].x2_x1) * coor_4_line[i].y1 +
		(coor_4_line[i].y2_y1) * (coor_4_line[j].y2_y1) * coor_4_line[j].x1 +
		(-coor_4_line[j].x2_x1) * (coor_4_line[i].y2_y1) * coor_4_line[j].y1);
	yb = coor_4_line[i].x2_x1 * coor_4_line[j].y2_y1 + (-coor_4_line[i].y2_y1) * coor_4_line[j].x2_x1; 

	y = ya * 1.0 / yb;

	int m = j;
	if (coor_4_line[j].k == 0) {
		m = i;
	}
	xb = -coor_4_line[m].y2_y1;
	if (xb == 0)
	{
		if (coor_4_line[m].x2_x1 == 0) xa = y - coor_4_line[m].y2;
		else if ((y - coor_4_line[m].y2) == 0) xa = -coor_4_line[m].x2_x1;
	}
	else xa = -coor_4_line[m].x2_x1 * (y - coor_4_line[m].y2) / xb;
	x = coor_4_line[m].x2 + xa;

	if (JudgeType(i, j, x, y))
	{
		string coor = to_string(x) + to_string(y); //shit
		intersection.insert(pair<string, int>(coor, 0));
	}
}

int JudgeType(int i, int j, double x, double y)
{
	string str1 = coor_4_line[i].type;
	string str2 = coor_4_line[j].type;

	int flag = 0;

	if (str1 != "L" || str2 != "L") //L-R L-S R-R R-L R-S S-S S-L S-R
	{
		if (str1 == "L")
		{
			if (str2 == "R")
			{
				if (JudgeRadial(j, x, y)) flag = 1;
			}
			else if (str2 == "S")
			{
				if (JudgeSegment(j, x, y)) flag = 1;
			}
		}
		else if (str1 == "R")
		{
			if (str2 == "L")
			{
				if (JudgeRadial(i, x, y)) flag = 1;
			}
			else if (str2 == "R")
			{
				if (JudgeRadial(i, x, y) && JudgeRadial(j, x, y)) flag = 1;
			}
			else if (str2 == "S")
			{
				if (JudgeRadial(i, x, y) && JudgeSegment(j, x, y)) flag = 1;
			}
		}
		else if (str1 == "S")
		{
			if (str2 == "L")
			{
				if (JudgeSegment(i, x ,y)) flag = 1;
			}
			else if (str2 == "R")
			{
				if (JudgeSegment(i, x, y) && JudgeRadial(j, x, y)) flag = 1;
			}
			else if (str2 == "S")
			{
				if (JudgeSegment(i, x, y) && JudgeSegment(j, x, y)) flag = 1;
			}
		}
	}
	else //L-L
	{
		flag = 1;
	}
	return flag;
}

int JudgeRadial(int i, double x,double y)
{
	double t1 = (double(coor_4_line[i].x1) - double(coor_4_line[i].x2)) * 1.0 * (double(coor_4_line[i].x1) - x);
	double t2 = (double(coor_4_line[i].y1) - double(coor_4_line[i].y2)) * 1.0 * (double(coor_4_line[i].y1) - y);
	if (t1 >= 0 && t2 >= 0) return 1;
	else return 0;
}

int JudgeSegment(int i, double x,double y)
{
	int flag = 0;

	if ((coor_4_line[i].x1 <= x && x <= coor_4_line[i].x2) || (coor_4_line[i].x1 >= x && x >= coor_4_line[i].x2))
	{
		if ((coor_4_line[i].y1 <= y && y <= coor_4_line[i].y2) || (coor_4_line[i].y1 >= y && y >= coor_4_line[i].y2))
		{
			flag = 1;
		}
	}

	return flag;
}

void Dealwith(line l1, line l2) {
	int flag = 0;
	double x, y;
	x = l1.x1 * 1.0;
	if (l1.type == "S" && l2.type == "S") {
		if (l1.y1 == l2.y1 || l1.y1 == l2.y2) {
			y = l1.y1 * 1.0;
			flag = 1;
		}
		else if (l1.y2 == l2.y1 || l1.y2 == l2.y2) {
			y = l1.y2 * 1.0;
			flag = 1;
		}
	}
	else if (l1.type == "S" && l2.type == "R") {
		if (l1.y1 == l2.y1 || l1.y2 == l2.y1) {
			y = l2.y1 * 1.0;
			flag = 1;
		}
	}
	else if (l1.type == "R" && l2.type == "S") {
		if (l1.y1 == l2.y1 || l1.y1 == l2.y2) {
			y = l1.y1 * 1.0;
			flag = 1;
		}
	}
	else if (l1.type == "R" && l2.type == "R") {
		if (l1.y1 == l2.y1) {
			y = l1.y1 * 1.0;
			flag = 1;
		}
	}
	if (flag == 1) {
		string coor = to_string(x) + to_string(y); //shit
		intersection.insert(pair<string, int>(coor, 0));
	}
}

int main(int argc, char** argv)
{
	string inputFilename;
	string outputFilename;

	if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[3][0] == '-' && argv[3][1] == 'o') {
		inputFilename = argv[2];
		outputFilename = argv[4];
	}
	else if (argv[1][0] == '-' && argv[1][1] == 'o' && argv[3][0] == '-' && argv[3][1] == 'i') {
		inputFilename = argv[4];
		outputFilename = argv[2];
	}
	ifstream fin(inputFilename);
	ofstream out(outputFilename);

	//test();性能测试

	int i = 0;
	fin >> N;
	fin.get();//用于吃掉回车
	while (i < N)
	{
		string str;
		line coor;
		getline(cin, str);
		coor.store_coor(str);
		coor_4_line.push_back(coor);
		i++;
	}
	if (N > 1)
	{
		cnt_coor_num();
		p_cnt = intersection.size();
	}
	cout << p_cnt << endl;
	out << p_cnt << endl;
	return 0;
}