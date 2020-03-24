#include "line.h"
using namespace std;

vector < line > coor_4_line; //ÿ���ߵ�����
map<string, int> intersection; //���н���
set<Point> points;

vector<WFLine> wflines;

int N;
int p_cnt = 0;
int linenum = 0;

void line::store_coor(string str)
{
	vector<string> res;//���ڴ�ŷָ����ַ��� 
	string result;//�ݴ��str�ж�ȡ���ַ��� 
	stringstream input(str);//���ַ�������input�� 
	while (input >> result)
		res.push_back(result);//���������result�У�������res�� 
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
				{//һ���� һ��û��
					calcu_coor(i, j);
				}
				else { //��û��б��
					if (coor_4_line[i].x1 == coor_4_line[j].x1) {
						Dealwith(coor_4_line[i], coor_4_line[j]);//б�ʲ����ڵ�SS SR RR
					}
				}
			}
			else //����б��
			{
				if (coor_4_line[i].k != coor_4_line[j].k)//�����Ҳ����
				{
					calcu_coor(i, j);
				}
				else //��������ȣ����S R)
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
		//string coor = to_string(x) + to_string(y); //shit
		//intersection.insert(pair<string, int>(coor, 0));
		Point px;
		px.Xpoint = x;
		px.Ypoint = y;
		points.insert(px);
	}
}

void DealwithKexist(line l1,line l2) {
	int flag = 0;
	double x, y;
	if (l1.type == "S" && l2.type == "S") {
		//(x1,y1) == (x1,y1)|(x2,y2)
		if ((l1.x1 == l2.x1 && l1.y1 == l2.y1)||(l1.x1==l2.x2&&l1.y1==l2.y2)) {
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
		string coor = to_string(x) + to_string(y); //shit
		intersection.insert(pair<string, int>(coor, 0));
		Point px;
		px.Xpoint = x;
		px.Ypoint = y;
		points.insert(px);
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

	//test();���ܲ���

	inputHandler(inputFilename);

	int i = 0;
	fin >> N;
	fin.get();//���ڳԵ��س�
	while (i < N)
	{
		string str;
		line coor;
		getline(fin, str);
		coor.store_coor(str);
		coor_4_line.push_back(coor);
		i++;
	}
	if (N > 1)
	{
		cnt_coor_num();
		p_cnt = points.size();
	}
	cout << p_cnt << endl;
	out << p_cnt << endl;
	cout << points.size() << endl;

	//for (map<string, int>::iterator iter = intersection.begin(); iter != intersection.end(); iter++)
	//	cout << iter->first << iter->second << endl;

	//double x = 0.0000000000000;
	//cout << x << endl;
	//cout << fabs(x) << endl;
	//cout << (fabs(x)==0) << endl;
}

void inputHandler(string Filename) {
	int Nnum = 0;
	ifstream inputh;
	inputh.open(Filename);
	if (!inputh.is_open()) {
		//�ļ�������
		cout << "File is Not Found." << endl;
		exit(0);
	}
	while (!inputh.eof())
	{
		string str;
		getline(inputh, str);
		linenum++;
		if (linenum == 1) {//��һ���Ƿ�������
			if (NisNum(str)) {
				Nnum = atoi(str.c_str());
				continue;
			}
			else {
				cout << "Make sure the first line is an Integer that greater than or equal to 1." << endl;
				exit(0);
			}
		}
		else {
			if (str.size() == 0) {//�������һ�еĻ���
				linenum--;
				continue;
			}
			if (str.size() < 9) {
				//�������ݹ���
				cout << "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.at line" << linenum << endl;
				exit(0);
			}
			//��������Ͳ���L S R
			if (str.at(0) != 'L' && str.at(0) != 'R' && str.at(0) != 'S') {
				cout << "Please input line type as \"L\",\"S\",\"R\" at line"<<linenum << endl;
				exit(0);
			}
			if (!isspace(str.at(1))) {
				//L\S\R ������֮��û�пո�
				cout << "Make sure there is a SPACE between number and letter at line" << linenum << endl;
				exit(0);
			}
			vector<string> strs;
			stringstream temp(str); //str�Կո�ָ�
			string res;
			//���������res�У�������strs�� 
			while (temp >> res)
				strs.push_back(res);
			//���res 
			//cout << "size is" << strs.size() << endl;L 0 0 1 1 SIZE=5
			if (strs.size() > 5) {
				//����Ԫ�ع���
				cout << "TOO LONG!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" << linenum << endl;
				exit(0);
			}
			if (strs.size() < 5) {
				//����Ԫ�ع���
				cout << "TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line" << linenum << endl;
				exit(0);
			}
			for (int i = 1; i < strs.size(); i++) {
				//�ָ� ��ȷΪ�ĸ�����
				//cout << strs[i] <<endl;
				//�����ж�
				handleNum(strs[i]);
			}
			int x1 = atoi(strs[1].c_str());
			int y1 = atoi(strs[2].c_str());
			int x2 = atoi(strs[3].c_str());
			int y2 = atoi(strs[4].c_str());
			if (x1 == x2 && y1 == y2) {
				cout << "Please input two different points.Error at line" << linenum << endl;
				exit(0);
			}
			Point pt1, pt2;
			pt1.Xpoint = x1;
			pt1.Ypoint = y1;
			pt2.Xpoint = x2;
			pt2.Ypoint = y2;
			//pt1 pt2 type
			WFLine l1 = l1.getLine(pt1, pt2,strs[0].at(0));
			wflines.push_back(l1);
		}	
	}
	if ((linenum-1) != Nnum) {//��������-1 = N
		cout << "N does not match the number of lines."<< endl;
		exit(0);
	}

	InfinitePoints();

	inputh.close();
}

bool NisNum(string str) {
	if (str.at(0) == '0' && str.size()>1) {//������0��ʼ������
		cout<< "A number that begins with 0 at line"<<linenum<<endl;
		exit(0);
	}
	for (int i = 0; i < str.size(); i++) {//N��������
		if (str.at(i) > '9' || str.at(i) < '0')
			return false;
	}
	if (atoi(str.c_str()) < 1) {//N<1
		cout << "Make sure N is an integer greater than or equal to 1"<< endl;
		exit(0);
	}
	return true;
}

void handleNum(string str) {
	if (str.at(0) == '0' && str.size() > 1) {//������0��ʼ������
		cout << "A number that begins with 0 at line" << linenum << endl;
		exit(0);
	}
	int minus = 0;//����ֻ����һ��ʼ����һ��
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == '-' && minus==0) {//����
			minus++;
			if (str.size() > 1) {
				continue;
			}
			else if (str.size() == 1) {//ֻ��һ������
				cout << "Make sure ��-�� is followed by number.Error at line" << linenum << endl;
				exit(0);
			}
		} 
		if (str.at(i) > '9' || str.at(i) < '0') {//��������
			cout << "Please input integers.Error at line" << linenum << endl;
			exit(0);
		}
	}
	if (atoi(str.c_str()) > 100000 || atoi(str.c_str()) < -100000) {//���귶Χ����
		cout << "Make sure that the range of points is(-100000,100000).Error at line" << linenum << endl;
		exit(0);
	}
}

WFLine WFLine::getLine(Point pt1, Point pt2,char type) {
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

void InfinitePoints() {
	int i, j;
	int Num = linenum - 1;//ֱ������
	for (i = 0; i < Num; i++) {
		for (j = i + 1; j < Num; j++) {
			if (wflines[i].b != 0 && wflines[j].b != 0) {//б�ʶ�����
				double k1 = wflines[i].a / wflines[i].b;
				double b1 = wflines[i].c / wflines[i].b;
				double k2 = wflines[j].a / wflines[j].b;
				double b2 = wflines[j].c / wflines[j].b;
				if (k1 == k2 && b1 == b2) {
					if (wflines[i].type == 'L' || wflines[j].type == 'L') {
						//i j����һ��ֱ����ôһ����ֹһ������
						cout << "Infinitely intersections between line L " << i << " and " << j << endl;
						exit(0);
					}//���� LL end
					else {
						double x1 = wflines[i].p1.Xpoint;
						double x2 = wflines[i].p2.Xpoint;
						double x3 = wflines[j].p1.Xpoint;
						double x4 = wflines[j].p2.Xpoint;
						//max(A.start,B.start)<min(A.end,B,end)�������ж�A��B�ص�
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
								cout << "Infinitely intersections between line SS " << i << " and " << j << endl;
								exit(0);
							}
						}//SS
						else if (wflines[i].type == 'S' && wflines[j].type == 'R') {
							//������������
							if (wflines[j].p1.Xpoint < wflines[j].p2.Xpoint) {
								if (wflines[j].p1.Xpoint < Aend) {
									cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									exit(0);
								}
							}
							else {//������������
								if (wflines[j].p1.Xpoint > Astart) {
									cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									exit(0);
								}
							}
						}//SR
						else if (wflines[i].type == 'R' && wflines[j].type == 'S') {
							//������������
							if (wflines[i].p1.Xpoint < wflines[i].p2.Xpoint) {
								if (wflines[i].p1.Xpoint < Bend) {
									cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									exit(0);
								}
							}
							else {//��������
								if (wflines[i].p1.Xpoint > Bstart) {
									cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									exit(0);
								}
							}
						}//RS
						else if (wflines[i].type == 'R' && wflines[j].type == 'R') {
							int line_i_right = 0;
							int line_j_right = 0;
							if (wflines[i].p1.Xpoint < wflines[i].p2.Xpoint) {
								line_i_right = 1;//i����
							}
							if (wflines[j].p1.Xpoint < wflines[j].p2.Xpoint) {
								line_j_right = 1;//j����
							}
							if ((line_i_right && line_j_right) || ((line_i_right==0) && (line_j_right==0))) {
								cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
								exit(0);
							}
							else if (line_i_right && (line_j_right == 0)) {//i���� j����
								if (wflines[i].p1.Xpoint < wflines[j].p1.Xpoint) {
									cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									exit(0);
								}
							}
							else if ((line_i_right == 0) && line_j_right) {//i���� j����
								if (wflines[j].p1.Xpoint < wflines[i].p1.Xpoint) {
									cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									exit(0);
								}
							}
						}//RR
					}//��ȥLL���
				}//end kb���
			}//end б�ʴ���
			else if(wflines[i].b==0 && wflines[j].b==0){//б�ʶ�������
				if (wflines[i].p1.Xpoint == wflines[j].p1.Xpoint) {//��X��ͬ
					if (wflines[i].type == 'L' || wflines[j].type == 'L') {
						cout << "Infinitely intersections between line L " << i << " and " << j << endl;
						exit(0);
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
								cout << "Infinitely intersections between line SS " << i << " and " << j << endl;
								exit(0);
							}
						}
						else if (wflines[i].type == 'S' && wflines[j].type == 'R') {
							if (wflines[j].p1.Ypoint > wflines[j].p2.Ypoint) {//ֱ����������
								if (wflines[j].p1.Ypoint > Amin) {
									cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									exit(0);
								}
							}
							else {
								if (wflines[j].p1.Ypoint < Amax) {
									cout << "Infinitely intersections between line SR " << i << " and " << j << endl;
									exit(0);
								}
							}
						}//SR
						else if (wflines[i].type == 'R' && wflines[j].type == 'S') {
							if (wflines[i].p1.Ypoint > wflines[i].p2.Ypoint) {
								if (wflines[i].p1.Ypoint > Bmin) {
									cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									exit(0);
								}
							}
							else {
								if (wflines[i].p1.Ypoint < Bmax) {
									cout << "Infinitely intersections between line RS " << i << " and " << j << endl;
									exit(0);
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
								cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
								exit(0);
							}
							else if (line_i_down && (line_j_down == 0)) {
								if (y1 > y3) {
									cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									exit(0);
								}
							}
							else if ((line_i_down == 0) && line_j_down) {
								if (y3 > y1) {
									cout << "Infinitely intersections between line RR " << i << " and " << j << endl;
									exit(0);
								}
							}
						}//RR
					}
				}//X��ͬ
			}//б�ʶ�������
		}//end for
	}
}