#include "./include/pch.h"
using namespace std;

void test_add()
{
	line l1, l2, l3, l4;

	l1.store_coor("L 0 0 1 1");
	l2.store_coor("L 0 1 1 0");
	addLine(l1);
	addLine(l2);
	solve();
	cout << "test_add" << endl;
	cout << p_cnt << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_del()
{
	line l1, l2, l3, l4;

	l1.store_coor("L 0 0 1 1");
	l2.store_coor("L 0 1 1 0");
	l3.store_coor("L 3 0 1 1");
	l4.store_coor("L 5 1 1 0");
	addLine(l1);
	addLine(l2);
	addLine(l3);
	addLine(l4);
	delLine(l3);//删除直线
	delLine(l4);//删除直线
	solve();
	cout << "test_del" << endl;
	cout << p_cnt << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_write()
{
	readin("in.txt");//读入数据
	solve();
	cout << "test_readin" << endl;
	cout << p_cnt << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_if_points_equal()
{
	readin("in.txt");//读入数据
	solve();
	
	int a = getP_cnt();//获得交点个数
	int b = getInterNum();//intersection size
	int c = getPointNum();//points size

	cout << "test_if_points_equal" << endl;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}


void test_intersection_coor()
{
	readin("in.txt");//读入数据
	solve();

	set<Point> pts = getPoints();//返回交点
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_1()
{
	readin("in.txt");//读入数据
	solve();

	set<Point> pts = getPoints();//返回交点
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}


void test_all()
{
	readin("in.txt");//读入数据
	line l1, l2, l3, l4;

	l1.store_coor("L 0 0 1 1");
	l2.store_coor("L 0 1 1 0");
	l3.store_coor("L 3 0 1 1");
	l4.store_coor("L 5 1 1 0");
	addLine(l1);
	addLine(l2);
	addLine(l3);
	addLine(l4);
	delLine(l1);//删除直线
	delLine(l2);//删除直线
	delLine(l3);//删除直线
	delLine(l4);//删除直线
	
	solve();

	int a = getP_cnt();//获得交点个数
	int b = getInterNum();//intersection size
	int c = getPointNum();//points size
	cout << "test_all" << endl;
	cout << "test_if_points_equal" << endl;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	set<Point> pts = getPoints();//返回交点
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;

	write("out.txt");
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

int main()
{
	//test 以下函数要一个一个调用，否则前面的数据会影响后面,可以先清理一下coor_4_line
	test_add();
	test_del();
	test_write();
	test_if_points_equal();
	test_intersection_coor();
	test_all();
}
