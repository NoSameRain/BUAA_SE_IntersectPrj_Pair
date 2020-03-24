#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

vector < line > coor_4_line; //每条线的坐标
map<string, int> intersection; //所有交点
set<Point> points;

int N;
int p_cnt = 0;

vector<WFLine> wflines;
int linenum = 0;

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
	for (i = 0; i < N; i++)
		for (j = i + 1; j < N; j++)
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
					DealwithKexist(coor_4_line[i], coor_4_line[j]);
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

	if (fabs(x) == 0) {
		x = 0;
	}
	if (fabs(y) == 0) {
		y = 0;
	}
	if (JudgeType(i, j, x, y))
	{
		//string coor = to_string(x) + to_string(y); //shit
		//intersection.insert(pair<string, int>(coor, 0));
		Point px;
		px.Xpoint = x;
		px.Ypoint = y;
		points.insert(px);
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
				if (JudgeSegment(i, x, y)) flag = 1;
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

int JudgeRadial(int i, double x, double y)
{
	double t1 = (double(coor_4_line[i].x1) - double(coor_4_line[i].x2)) * 1.0 * (double(coor_4_line[i].x1) - x);
	double t2 = (double(coor_4_line[i].y1) - double(coor_4_line[i].y2)) * 1.0 * (double(coor_4_line[i].y1) - y);
	if (t1 >= 0 && t2 >= 0) return 1;
	else return 0;
}

int JudgeSegment(int i, double x, double y)
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
		//string coor = to_string(x) + to_string(y); //shit
		//intersection.insert(pair<string, int>(coor, 0));
		Point px;
		px.Xpoint = x;
		px.Ypoint = y;
		points.insert(px);
	}
}

void DealwithKexist(line l1, line l2) {
	int flag = 0;
	double x, y;
	if (l1.type == "S" && l2.type == "S") {
		//(x1,y1) == (x1,y1)|(x2,y2)
		if ((l1.x1 == l2.x1 && l1.y1 == l2.y1) || (l1.x1 == l2.x2 && l1.y1 == l2.y2)) {
			x = 1.0 * l1.x1;
			y = 1.0 * l1.y1;
			flag = 1;
		}//(x2,y2) == (x1,y1)|(x2,y2)
		else if ((l1.x2 == l2.x1 && l1.y2 == l2.y1) || (l1.x2 == l2.x2 && l1.y2 == l2.y2)) {
			x = l1.x2 * 1.0;
			y = l1.y2 * 1.0;
			flag = 1;
		}
	}
	else if (l1.type == "S" && l2.type == "R") {
		if (l1.x1 == l2.x1 && l1.y1 == l2.y1) {
			x = 1.0 * l1.x1;
			y = 1.0 * l1.y1;
			flag = 1;
		}
		else if (l1.x2 == l2.x1 && l1.y2 == l2.y1) {
			x = l1.x2 * 1.0;
			y = l1.y2 * 1.0;
			flag = 1;
		}
	}
	else if (l1.type == "R" && l2.type == "S") {
		if ((l1.x1 == l2.x1 && l1.y1 == l2.y1) || (l1.x1 == l2.x2 && l1.y1 == l2.y2)) {
			x = 1.0 * l1.x1;
			y = 1.0 * l1.y1;
			flag = 1;
		}
	}
	else if (l1.type == "R" && l2.type == "R") {
		if (l1.x1 == l2.x1 && l1.y1 == l2.y1) {
			x = 1.0 * l1.x1;
			y = 1.0 * l1.y1;
			flag = 1;
		}
	}
	if (flag == 1) {
		//string coor = to_string(x) + to_string(y); //shit
		//intersection.insert(pair<string, int>(coor, 0));
		Point px;
		px.Xpoint = x;
		px.Ypoint = y;
		points.insert(px);
	}
}

//int main(int argc, char** argv)
//{
//	string inputFilename;
//	string outputFilename;
//
//	if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[3][0] == '-' && argv[3][1] == 'o') {
//		inputFilename = argv[2];
//		outputFilename = argv[4];
//	}
//	else if (argv[1][0] == '-' && argv[1][1] == 'o' && argv[3][0] == '-' && argv[3][1] == 'i') {
//		inputFilename = argv[4];
//		outputFilename = argv[2];
//	}
//	ifstream fin(inputFilename);
//	ofstream out(outputFilename);
//
//	//test();性能测试
//
//	int i = 0;
//	fin >> N;
//	fin.get();//用于吃掉回车
//	while (i < N)
//	{
//		string str;
//		line coor;
//		getline(fin, str);
//		coor.store_coor(str);
//		coor_4_line.push_back(coor);
//		i++;
//	}
//	if (N > 1)
//	{
//		cnt_coor_num();
//		p_cnt = intersection.size();
//	}
//	cout << p_cnt << endl;
//	out << p_cnt << endl;
//	cout << points.size() << endl;
//
	//for (map<string, int>::iterator iter = intersection.begin(); iter != intersection.end(); iter++)
	//	cout << iter->first << iter->second << endl;

	//double x = 0.0000000000000;
	//cout << x << endl;
	//cout << fabs(x) << endl;
	//cout << (fabs(x)==0) << endl;
//}

void clear() {
	intersection.clear();
	coor_4_line.clear();
	points.clear();

	wflines.clear();
	N = 0;
	linenum = 0;
}

set<Point> getPoints() {
	return points;
}

vector<line> getLine() {
	return coor_4_line;
}

void readin(string FileName) {
	string inputFilename;
	inputFilename = FileName;
	ifstream fin(inputFilename);
	int i = 0;
	fin >> N;
	fin.get();//用于吃掉回车
	while (i < N)
	{
		string str;
		line coor;
		getline(fin, str);
		coor.store_coor(str);
		coor_4_line.push_back(coor);
		i++;
	}
}

void addLine(line l) {
	coor_4_line.push_back(l);
	Point pt1, pt2;
	pt1.Xpoint = l.x1;
	pt1.Ypoint = l.y1;
	pt2.Xpoint = l.x2;
	pt2.Ypoint = l.y2;
	WFLine l1 = l1.getLine(pt1, pt2, l.type.at(0));
	wflines.push_back(l1);
	linenum++;
	N++;
}

void delLine(line l) {
	vector<line>::iterator it;
	for (it = coor_4_line.begin(); it != coor_4_line.end();)
	{
		if (it->x1 == l.x1 && it->x2 == l.x2 && it->y1 == l.y1 && it->y2 == l.y2 && it->type == l.type)
			it = coor_4_line.erase(it);    //删除元素，返回值指向已删除元素的下一个位置    
		else
			++it;    //指向下一个位置
	}
	vector<WFLine>::iterator it2;
	for (it2 = wflines.begin(); it2 != wflines.end();) {
		if (it2->p1.Xpoint == l.x1 && it2->p2.Xpoint == l.x2 && it2->p1.Ypoint == l.y1 && it2->p2.Ypoint == l.y2
			&& it2->type == l.type.at(0))
			it2 = wflines.erase(it2);    //删除元素，返回值指向已删除元素的下一个位置    
		else
			++it2;
	}
	linenum--;
	N--;
}

void solve() {
	intersection.clear();
	points.clear();
	cnt_coor_num();
	p_cnt = points.size();//!!
}

int getInterNum() {
	return intersection.size();
}

int getPointNum() {
	return points.size();
}

int getP_cnt() {
	return p_cnt;
}

void write(string FileName) {
	ofstream out(FileName);
	out << p_cnt << endl;
}

WFLine WFLine::getLine(Point pt1, Point pt2, char type) {
	WFLine result;
	/*
	a = y1-y2
	b = x2-x1
	c = x1*y2-x2*y1
	l = ax+by+c=0
	*/
	result.a = pt1.Ypoint - pt2.Ypoint;
	result.b = pt2.Xpoint - pt1.Xpoint;
	result.c = pt1.Xpoint * pt2.Ypoint - pt2.Xpoint * pt1.Ypoint;
	result.type = type;
	result.p1 = pt1;
	result.p2 = pt2;
	return result;
}

string inputHandler(string FileName) {
	string result = "Everything is ok!";
	int Nnum = 0;
	ifstream inputh;
	inputh.open(FileName);
	if (!inputh.is_open()) {
		//文件不存在
		result = "File is Not Found.";
		return result;
		//cout << "File is Not Found." << endl;
		//exit(0);

	}
	while (!inputh.eof())
	{
		string str;
		getline(inputh, str);
		linenum++;
		if (linenum == 1) {//第一行是否是整数
			string s = NisNum(str);
			if (s != "OK!") {
				result = s;
				return s;
			}
			else {
				Nnum = atoi(str.c_str());
				continue;
			}
		}
		else {
			if (str.size() == 0) {//处理最后一行的换行
				linenum--;
				continue;
			}
			if (str.size() < 9) {
				//输入数据过短
				result = "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.at line" + to_string(linenum);
				return result;
				//cout << "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.at line" << linenum << endl;
				//exit(0);
			}
			//输入的类型不是L S R
			if (str.at(0) != 'L' && str.at(0) != 'R' && str.at(0) != 'S') {
				result = "Please input line type as \"L\",\"S\",\"R\" at line" + to_string(linenum);
				return result;
				//cout << "Please input line type as \"L\",\"S\",\"R\" at line" << linenum << endl;
				//exit(0);
			}
			if (!isspace(str.at(1))) {
				//L\S\R 和数字之间没有空格
				result = "Make sure there is a SPACE between number and letter at line" + to_string(linenum);
				return result;
				//cout << "Make sure there is a SPACE between number and letter at line" << linenum << endl;
				//exit(0);
			}
			vector<string> strs;
			stringstream temp(str); //str以空格分割
			string res;
			//依次输出到res中，并存入strs中 
			while (temp >> res)
				strs.push_back(res);
			//输出res 
			//cout << "size is" << strs.size() << endl;L 0 0 1 1 SIZE=5
			if (strs.size() > 5) {
				//输入元素过多
				result = "TOO LONG!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" + to_string(linenum);
				return result;
				//cout << "TOO LONG!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" << linenum << endl;
				//exit(0);
			}
			if (strs.size() < 5) {
				//输入元素过少
				result = "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" + to_string(linenum);
				return result;
				//cout << "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" << linenum << endl;
				//exit(0);
			}
			for (int i = 1; i < strs.size(); i++) {
				//分割 正确为四个数字
				//cout << strs[i] <<endl;
				//数字判断
				string s = handleNum(strs[i]);
				if (s != "OK!") {
					result = s;
					return result;
				}
			}
			int x1 = atoi(strs[1].c_str());
			int y1 = atoi(strs[2].c_str());
			int x2 = atoi(strs[3].c_str());
			int y2 = atoi(strs[4].c_str());
			if (x1 == x2 && y1 == y2) {
				result = "Please input two different points.Error at line" + to_string(linenum);
				return result;
				//cout << "Please input two different points.Error at line" << linenum << endl;
				//exit(0);
			}
			Point pt1, pt2;
			pt1.Xpoint = x1;
			pt1.Ypoint = y1;
			pt2.Xpoint = x2;
			pt2.Ypoint = y2;
			//pt1 pt2 type
			WFLine l1 = l1.getLine(pt1, pt2, strs[0].at(0));
			wflines.push_back(l1);
		}
	}
	if ((linenum - 1) != Nnum) {//所有行数-1 = N
		result = "N does not match the number of lines.";
		return result;
		//cout << "N does not match the number of lines." << endl;
		//exit(0);
	}

	//InfinitePoints();
	inputh.close();
	return result;

}

string  NisNum(string str) {
	string result = "OK!";
	if (str.at(0) == '0' && str.size() > 1) {//出现以0开始的数字
		result = "A number that begins with 0 at line" + to_string(linenum);
		return result;
		//cout << "A number that begins with 0 at line" << linenum << endl;
		//exit(0);
	}
	for (int i = 0; i < str.size(); i++) {//N不是数字
		if (str.at(i) > '9' || str.at(i) < '0') {
			result = "Make sure the first line is an Integer that greater than or equal to 1.";
			return result;
		}
	}
	if (atoi(str.c_str()) < 1) {//N<1
		result = "Make sure N is an integer greater than or equal to 1";
		return result;
		//cout << "Make sure N is an integer greater than or equal to 1" << endl;
		//exit(0);
	}
	return result;
}

string handleNum(string str) {
	string result = "OK!";
	if (str.at(0) == '0' && str.size() > 1) {//出现以0开始的数字
		result = "A number that begins with 0 at line" + to_string(linenum);
		return result;
		//cout << "A number that begins with 0 at line" << linenum << endl;
		//exit(0);
	}
	int minus = 0;//负号只能有一开始的哪一个
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == '-' && minus == 0) {//负数
			minus++;
			if (str.size() > 1) {
				continue;
			}
			else if (str.size() == 1) {//只有一个负号
				result = "Make sure ‘-’ is followed by number.Error at line" + to_string(linenum);
				return result;
				//cout << "Make sure ‘-’ is followed by number.Error at line" << linenum << endl;
				//exit(0);
			}
		}
		if (str.at(i) > '9' || str.at(i) < '0') {//不是整数
			result = "Please input integers.Error at line" + to_string(linenum);
			return result;
			//cout << "Please input integers.Error at line" << linenum << endl;
			//exit(0);
		}
	}
	if (atoi(str.c_str()) > 100000 || atoi(str.c_str()) < -100000) {//坐标范围超限
		result = "Make sure that the range of points is(-100000,100000).Error at line" + to_string(linenum);
		return result;
		//cout << "Make sure that the range of points is(-100000,100000).Error at line" << linenum << endl;
		//exit(0);
	}
	return result;
}

string InfinitePoints() {
	string result = "NO InfinitePoints!";
	int i, j;
	int Num = linenum - 1;//直线条数
	for (i = 0; i < Num; i++) {
		for (j = i + 1; j < Num; j++) {
			if (wflines[i].b != 0 && wflines[j].b != 0) {//斜率都存在
				double k1 = wflines[i].a / wflines[i].b;
				double b1 = wflines[i].c / wflines[i].b;
				double k2 = wflines[j].a / wflines[j].b;
				double b2 = wflines[j].c / wflines[j].b;
				if (k1 == k2 && b1 == b2) {
					if (wflines[i].type == 'L' || wflines[j].type == 'L') {
						//i j中有一条直线那么一定不止一个交点
						result = "Infinitely intersections between line L " + to_string(i) + to_string(j);
						return result;
						//cout << "Infinitely intersections between line L " << i << " and " << j << endl;
						//exit(0);
					}//都是 LL end
					else {
						double x1 = wflines[i].p1.Xpoint;
						double x2 = wflines[i].p2.Xpoint;
						double x3 = wflines[j].p1.Xpoint;
						double x4 = wflines[j].p2.Xpoint;
						//max(A.start,B.start)<min(A.end,B,end)，即可判断A，B重叠
						double Astart, Aend, Bstart, Bend;
						if (x1 < x2) {
							Astart = x1;
							Aend = x2;
						}
						else {
							Astart = x2;
							Aend = x1;
						}
						if (x3 < x4) {
							Bstart = x3;
							Bend = x4;
						}
						else {
							Bstart = x4;
							Bend = x3;
						}
						if (wflines[i].type == 'S' && wflines[j].type == 'S') {
							double max, min;
							if (Astart > Bstart) {
								max = Astart;
							}
							else {
								max = Bstart;
							}
							if (Aend < Bend) {
								min = Aend;
							}
							else {
								min = Bend;
							}
							if (max < min) {
								result = "Infinitely intersections between line SS " + to_string(i) + to_string(j);
								return result;
								//cout << "Infinitely intersections between line SS " << i << " and " << j << endl;
								//exit(0);
							}
						}//SS
						else if (wflines[i].type == 'S' && wflines[j].type == 'R') {
							//射线向右延伸
							if (wflines[j].p1.Xpoint < wflines[j].p2.Xpoint) {
								if (wflines[j].p1.Xpoint < Aend) {
									result = "Infinitely intersections between line SR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else {//射线向左延伸
								if (wflines[j].p1.Xpoint > Astart) {
									result = "Infinitely intersections between line SR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//SR
						else if (wflines[i].type == 'R' && wflines[j].type == 'S') {
							//射线向右延伸
							if (wflines[i].p1.Xpoint < wflines[i].p2.Xpoint) {
								if (wflines[i].p1.Xpoint < Bend) {
									result = "Infinitely intersections between line RS " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else {//向左延伸
								if (wflines[i].p1.Xpoint > Bstart) {
									result = "Infinitely intersections between line RS " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//RS
						else if (wflines[i].type == 'R' && wflines[j].type == 'R') {
							int line_i_right = 0;
							int line_j_right = 0;
							if (wflines[i].p1.Xpoint < wflines[i].p2.Xpoint) {
								line_i_right = 1;//i向右
							}
							if (wflines[j].p1.Xpoint < wflines[j].p2.Xpoint) {
								line_j_right = 1;//j向右
							}
							if ((line_i_right && line_j_right) || ((line_i_right == 0) && (line_j_right == 0))) {
								result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
								return result;
								//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
								//exit(0);
							}
							else if (line_i_right && (line_j_right == 0)) {//i向右 j向左
								if (wflines[i].p1.Xpoint < wflines[j].p1.Xpoint) {
									result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else if ((line_i_right == 0) && line_j_right) {//i向左 j向右
								if (wflines[j].p1.Xpoint < wflines[i].p1.Xpoint) {
									result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//RR
					}//除去LL情况
				}//end kb相等
			}//end 斜率存在
			else if (wflines[i].b == 0 && wflines[j].b == 0) {//斜率都不存在
				if (wflines[i].p1.Xpoint == wflines[j].p1.Xpoint) {//且X相同
					if (wflines[i].type == 'L' || wflines[j].type == 'L') {
						result = "Infinitely intersections between line L " + to_string(i) + to_string(j);
						return result;
						//cout << "Infinitely intersections between line L " << i << " and " << j << endl;
						//exit(0);
					}
					else {
						double Amax, Amin, Bmax, Bmin;
						double y1 = wflines[i].p1.Ypoint;
						double y2 = wflines[i].p2.Ypoint;
						double y3 = wflines[j].p1.Ypoint;
						double y4 = wflines[j].p2.Ypoint;
						if (y1 > y2) {
							Amax = y1;
							Amin = y2;
						}
						else {
							Amax = y2;
							Amin = y1;
						}
						if (y3 > y4) {
							Bmax = y3;
							Bmin = y4;
						}
						else {
							Bmax = y4;
							Bmin = y3;
						}
						if (wflines[i].type == 'S' && wflines[j].type == 'S') {
							double min, max;
							if (Amax < Bmax) {
								max = Amax;
							}
							else {
								max = Bmax;
							}
							if (Amin > Bmin) {
								min = Amin;
							}
							else {
								min = Bmin;
							}
							if (max > min) {
								result = "Infinitely intersections between line SS " + to_string(i) + to_string(j);
								return result;
								//cout << "Infinitely intersections between line SS " << i << " and " << j << endl;
								//exit(0);
							}
						}
						else if (wflines[i].type == 'S' && wflines[j].type == 'R') {
							if (wflines[j].p1.Ypoint > wflines[j].p2.Ypoint) {//直线向下延申
								if (wflines[j].p1.Ypoint > Amin) {
									result = "Infinitely intersections between line SR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else {
								if (wflines[j].p1.Ypoint < Amax) {
									result = "Infinitely intersections between line SR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//SR
						else if (wflines[i].type == 'R' && wflines[j].type == 'S') {
							if (wflines[i].p1.Ypoint > wflines[i].p2.Ypoint) {
								if (wflines[i].p1.Ypoint > Bmin) {
									result = "Infinitely intersections between line RS " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else {
								if (wflines[i].p1.Ypoint < Bmax) {
									result = "Infinitely intersections between line RS " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//RS
						else if (wflines[i].type == 'R' && wflines[j].type == 'R') {
							int line_i_down = 0;
							int line_j_down = 0;
							if (y1 > y2) {
								line_i_down = 1;
							}
							if (y3 > y4) {
								line_j_down = 1;
							}
							if ((line_i_down && line_j_down) || ((line_i_down == 0) && (line_j_down == 0))) {
								result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
								return result;
								//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
								//exit(0);
							}
							else if (line_i_down && (line_j_down == 0)) {
								if (y1 > y3) {
									result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									//exit(0);
								}
							}
							else if ((line_i_down == 0) && line_j_down) {
								if (y3 > y1) {
									result = "Infinitely intersections between line RR " + to_string(i) + to_string(j);
									return result;
									//cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									//exit(0);
								}
							}
						}//RR
					}
				}//X相同
			}//斜率都不存在
		}//end for
	}
	return result;
}