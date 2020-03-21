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
	delLine(l3);//ɾ��ֱ��
	delLine(l4);//ɾ��ֱ��
	solve();
	cout << "test_del" << endl;
	cout << p_cnt << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_write()
{
	readin("in.txt");//��������
	solve();
	cout << "test_readin" << endl;
	cout << p_cnt << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_if_points_equal()
{
	readin("in.txt");//��������
	solve();
	
	int a = getP_cnt();//��ý������
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
	readin("in.txt");//��������
	solve();

	set<Point> pts = getPoints();//���ؽ���
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

void test_1()
{
	readin("in.txt");//��������
	solve();

	set<Point> pts = getPoints();//���ؽ���
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}


void test_all()
{
	readin("in.txt");//��������
	line l1, l2, l3, l4;

	l1.store_coor("L 0 0 1 1");
	l2.store_coor("L 0 1 1 0");
	l3.store_coor("L 3 0 1 1");
	l4.store_coor("L 5 1 1 0");
	addLine(l1);
	addLine(l2);
	addLine(l3);
	addLine(l4);
	delLine(l1);//ɾ��ֱ��
	delLine(l2);//ɾ��ֱ��
	delLine(l3);//ɾ��ֱ��
	delLine(l4);//ɾ��ֱ��
	
	solve();

	int a = getP_cnt();//��ý������
	int b = getInterNum();//intersection size
	int c = getPointNum();//points size
	cout << "test_all" << endl;
	cout << "test_if_points_equal" << endl;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	set<Point> pts = getPoints();//���ؽ���
	cout << "test_intersection_coor" << endl;
	for (set<Point>::iterator iter = pts.begin();iter != pts.end();iter++)
		cout << iter->Xpoint << " " << iter->Ypoint << endl;

	write("out.txt");
	cout << "________________________________" << endl;
	//coor_4_line.clear();
}

int main()
{
	//test ���º���Ҫһ��һ�����ã�����ǰ������ݻ�Ӱ�����,����������һ��coor_4_line
	test_add();
	test_del();
	test_write();
	test_if_points_equal();
	test_intersection_coor();
	test_all();
}
