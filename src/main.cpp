#include "./include/pch.h"

int main(int argc, char** argv) {
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
	string s = inputHandler(inputFilename);
	if (s != "Everything is ok!") {
		cout << s << endl;
		exit(0);
	}
	string ss = InfinitePoints();
	if (ss != "NO InfinitePoints!") {
		cout << ss << endl;
		exit(0);
	}
	readin(inputFilename);
	solve();
	//cout << p_cnt << endl;
	out << p_cnt << endl;

	//line l1, l2, l3, l4;
	//l1.store_coor("L 0 0 1 1");
	//addLine(l1);
	//string right = InfinitePoints();//add后需要判断是否重合
	//cout << right << endl;
	//if (right != "NO InfinitePoints!") {
	//	exit(0);
	//}
	//solve();
	//cout << p_cnt << endl;

	//l2.store_coor("L 3 0 3 2");
	//addLine(l2);
	//string right1 = InfinitePoints();//add后需要判断是否重合
	//cout << right1 << endl;
	//if (right1 != "NO InfinitePoints!") {
	//	exit(0);
	//}
	//solve();
	//cout << p_cnt << endl;

	//delLine(l2);
	//solve();
	//cout << p_cnt << endl;
	//delLine(l4);
	//vector<line> lines = getLine();
	//int num = lines.size();
	//cout << num << endl;
	//solve();
	//cout << p_cnt << endl;
	//
	//set<Point> pts = getPoints();
	//for (set<Point>::iterator iter = pts.begin(); iter != pts.end(); iter++)
	//cout << iter->Xpoint<<iter->Ypoint << endl;
}