#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineTest1
{
	TEST_CLASS(LineTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			line l1;
			l1.store_coor("L 0 0 1 1");
			Assert::AreEqual(l1.type, (string)"L");
			Assert::AreEqual(l1.k, (double)1);
			Assert::AreEqual(l1.ulimited, false);

			line l2;
			l2.store_coor("L 1 1 1 4");
			Assert::AreEqual(l2.type, (string)"L");
			Assert::AreEqual(l2.ulimited, true);
		}

		TEST_METHOD(TestMethod2) {
			line l1;
			l1.store_coor("R 0 1 1 0");
			Assert::AreEqual(l1.type, (string)"R");
			Assert::AreEqual(l1.k, (double)-1);
			Assert::AreEqual(l1.ulimited, false);

			line l2;
			l2.store_coor("S -1 -1 0 1");
			Assert::AreEqual(l2.type, (string)"S");
			Assert::AreEqual(l2.k, (double)2);
			Assert::AreEqual(l2.ulimited, false);
		}

		TEST_METHOD(TestMethod3) {
			line l1;
			l1.store_coor("L 0 0 1 1");
			line l2;
			l2.store_coor("L 1 0 0 1");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			calcu_coor(0, 1);
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod4) {//斜率为0
			clear();
			N = 2;
			line l1;
			line l2;
			l1.store_coor("L 4 5 -2 5");
			l2.store_coor("R 3 -2 4 -2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)0);
		}

		TEST_METHOD(testMethod5) {//垂直
			clear();
			N = 2;
			line l1;
			line l2;
			l1.store_coor("L 0 3 -2 3");
			l2.store_coor("L 1 4 1 -7");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);

		}

		TEST_METHOD(testMethod6) {
			clear();
			N = 2;
			line l1;
			line l2;
			l1.store_coor("L 0 1 0 2");
			l2.store_coor("R 1 0 2 1");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			cnt_coor_num();
			int k = intersection.size();
			Assert::AreEqual(k, 0);
		}

		TEST_METHOD(testMethod7) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("L -1 0 0 1");
			l2.store_coor("R -2 0 1 1");
			l3.store_coor("S 0 5 5 0");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)3);
		}

		TEST_METHOD(testMethod8) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S -1 3 2 -1");
			l2.store_coor("L -2 2 3 0");
			l3.store_coor("R -3 0 4 2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod9) {
			clear();
			N = 4;
			line l1, l2, l3, l4;
			l1.store_coor("L -2 0 0 -2");
			l2.store_coor("R 1 1 2 2");
			l3.store_coor("R 1 0 0 2");
			l4.store_coor("S -2 0 1 4");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			coor_4_line.push_back(l4);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)2);
		}

		TEST_METHOD(testMethod10) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("R -1 1 0 9");
			l2.store_coor("S -1 0 0 -1");
			l3.store_coor("S 0 0 1 3");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)0);
		}

		TEST_METHOD(testMethod11) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S 1 1 1 9");
			l2.store_coor("S 1 9 1 12");
			l3.store_coor("S 1 -3 1 1");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)2);
		}

		TEST_METHOD(testMethod12) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S 3 2 3 1");
			l2.store_coor("R 3 2 3 4");
			l3.store_coor("S 3 -1 3 -2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod13) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("R 4 4 4 -2");
			l2.store_coor("S 4 12 4 4");
			l3.store_coor("S 3 -1 3 -2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod14) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("R 2 2 2 8");
			l2.store_coor("R 2 2 2 -1");
			l3.store_coor("S 3 1 8 9");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod15) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("L 100000 100000 -3 19999");
			l2.store_coor("L 99999 100000 4 8366");
			l3.store_coor("L -6542 768 9999 -4");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)3);
		}
		TEST_METHOD(testMethod16) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S 1 2 4 5");
			l2.store_coor("S 2 5 3 1");
			l3.store_coor("R 1 0 5 2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)2);
		}

		TEST_METHOD(testMethod17) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S -5 1 -2 4");
			l2.store_coor("R -5 -1 -6 1");
			l3.store_coor("L -8 2 -8 1");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod18) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("R -2 -4 -3 -7");
			l2.store_coor("R -4 -5 -5 -4");
			l3.store_coor("R -9 -2 -4 1");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod19) {
			clear();
			N = 3;
			line l1, l2, l3;
			l1.store_coor("S 2 -3 4 -1");
			l2.store_coor("S 4 -3 6 -1");
			l3.store_coor("S 1 -3 3 -5");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)0);
		}

		TEST_METHOD(testMethod20) {
			clear();
			N = 4;
			line l1, l2, l3, l4;
			l1.store_coor("R -1 1 1 3");
			l2.store_coor("L 1 0 0 3");
			l3.store_coor("S -2 4 2 2");
			l4.store_coor("L -3 0 4 -5");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			coor_4_line.push_back(l4);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)4);
		}

		TEST_METHOD(testMethod21) {//有斜率且斜率相同端点相交的SS
			clear();
			N = 2;
			line l1;
			line l2;
			l1.store_coor("S 0 0 1 1");
			l2.store_coor("S 1 1 2 2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)1);
		}

		TEST_METHOD(testMethod22) {//其中一个垂直且假交点在垂直延伸线上的ss
			clear();
			N = 2;
			line l1;
			line l2;
			l1.store_coor("S 1 0 0 1");
			l2.store_coor("S 1 1 1 2");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)0);
		}

		TEST_METHOD(testMethod_sum) {
			clear();
			N = 11;
			line l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,
				l14,l15,l16,l17,l18,l19,l20,l21,l22,l23;
			l1.store_coor("R -1 1 1 3");
			l2.store_coor("L 1 0 0 3");
			l3.store_coor("S -2 4 2 2");
			l4.store_coor("L -3 0 4 -5");
			l5.store_coor("S 2 0 2 2");
			l6.store_coor("S 2 0 2 -1");
			l7.store_coor("S 3 0 3 2");
			l8.store_coor("R 0 -5 1 -5");
			l9.store_coor("R 0 -5 -1 -5");
			l10.store_coor("R 0 -7 -1 -8");
			l11.store_coor("S 0 -7 1 -6");
			coor_4_line.push_back(l1);
			coor_4_line.push_back(l2);
			coor_4_line.push_back(l3);
			coor_4_line.push_back(l4);
			coor_4_line.push_back(l5);
			coor_4_line.push_back(l6);
			coor_4_line.push_back(l7);
			coor_4_line.push_back(l8);
			coor_4_line.push_back(l9);
			coor_4_line.push_back(l10);
			coor_4_line.push_back(l11);
			cnt_coor_num();
			Assert::AreEqual(intersection.size(), (size_t)10);
		}

		void clear()
		{
			coor_4_line.clear();
			intersection.clear();
		}
	};
}
