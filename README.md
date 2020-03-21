BUAA_SE_IntersectPrj_Pair

BUAA软工结对项目

3.19 封装成dll，lib文件

使用方法：

1、新建工程

2、在工程目录下新建include目录和lib目录，

framework.h和pch.h加入include文件夹

Dllwork.dll和Dllwork.lib加入lib文件夹

3、配置工程属性如下：

配置属性-> C/C++ -> 常规 ：附加包含目录：.\include

配置属性->链接器 ->  常规 ：附加库目录：.\lib

配置属性->链接器->输入->附加依赖项：Dllwork.lib

4、添加源文件main.cpp

头文件中加入：#include "./include/pch.h"

接口定义：

```c++
DLL_API void clear();
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
DLL_API void write(string FileName);
```

**以大小写字母，数字，空格，-，\n 组成的文本**

错误处理类型

“坐标范围超限”，“直线定义中两点重合”或“有无穷多交点”

| 错误类型               | 输出                                                         | 测试样例                                                     |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **类型不符合L S R**    | Please input line type as \"L\",\"S\",\"R\" at line          | 2<br>K 1 2 4 5<br>a 0 0 1 1                                  |
| **‘-’后未紧跟数字**    | Make sure ‘-’ is followed by number.Error at line            | 3
<br/>L 0 0 1 1
R 3 2 0 5
S 9 - 7 8                            |
| **坐标范围超限**       | Make sure that the range of points is(-100000,100000).Error at line | 2
L 1000001 4 5 1
R 3 2 0 5<br/>2<br>L 1 4 5 1
R 3 2 0 -18236862 |
| **line中两点重合**     | Please input two different points.Error at line              | 3
<br/>L 1 4 5 1
R 3 2 0 3
S 7 8 7 8                            |
| **有无穷多交点**       | Infinitely many intersections                                |                                                              |
| **输入数据不完整**     | TOO SHORT!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.at line | 4
<br/>L 1 4 5 1
R 3 2 0 3
L 6 4 3 2
S 9 7 5                     |
| **输入过多元素**       | TOO LONG!Please input as \"L\\S\\R int_x1 int_y1 int_x2 int_y2\" for each line.Error at line | 3
<br/>L 0 0 1 1
R 3 2 0 5
S 9 5 6 7 8                          |
| **输入非整数**         | Please input integers.Error at line                          | 3
<br/>L 0 0 1 1
R 3 2 0 5
S 9 5 6 7
R 4.45 6 7 6                |
|                        |                                                              | 3
<br/>L 0 0 1 1
R 3 2 0 5
S 9 5 6 7
R 4 ask 7 6                 |
| **找不到输入文件**     | File is Not Found                                            | input.txt移除                                                |
| **第一行不是整数**     | Make sure the first line is an Integer that greater than or equal to 1. | a
<br/>L 0 0 1 1
R 3 2 0 5                                     |
| **第一行小于1**        | Make sure N is an integer greater than or equal to 1         | 0
<br/>L 0 0 1 1
R 3 2 0 5                                     |
| **type和数字没有空格** | Make sure there is a SPACE between number and letter at line | 2
<br/>L0 0 1 1 3
R 3 2 0 5                                    |
| **N和直线数目不匹配**  | N does not match the number of lines.                        | 2
<br/>L 0 1 1 3
R 3 2 0 5
R 0 0 1 1                            |
| **出现以0开始的数字**  | A number that begins with 0 at line                          | 4
<br/>L 0 1 1 3
R 3 2 0 5
R 0 0 1 1
S 012 3 4 5                 |

不止一个交点，即L\S\R 出现重合情况

| **输入**                             | **输出**                                         |
| ------------------------------------ | ------------------------------------------------ |
| 2
<br/>L 1 0 2 1
L 0 -1 -1 -2          | Infinitely intersections between line L 0 and 1  |
| 3
<br/>L 1 0 2 1
S 1 2 3 4
S 2 3 4 5    | Infinitely intersections between line SS 1 and 2 |
| 3
<br/>L 1 0 2 1
R 1 2 3 4
S 2 3 4 5    | Infinitely intersections between line RS 1 and 2 |
| 3
<br/>L 1 0 2 1
R 2 3 1 2
S 3 4 4 5    | 0                                                |
| 2
<br/>S 2 3 1 2
S 3 4 4 5             | 0                                                |
| 2
<br/>R 3 4 2 3
S 2 3 4 5             | Infinitely intersections between line RS 0 and 1 |
| 2
<br/>S 3 4 2 3
R 2 3 4 5             | Infinitely intersections between line SR 0 and 1 |
| 2
<br/>S 2 -1 1 0
R 0 1 -1 2           | 0                                                |
| 2
<br/>S 2 -1 1 0
R -1 2 0 1           | Infinitely intersections between line SR 0 and 1 |
| 2
<br/>S -2 3 -1 2
R -1 2 0 1          | 1                                                |
| 2
<br/>S -2 3 -1 2
R 1 0 0 1           | Infinitely intersections between line SR 0 and 1 |
| 3
<br/>L 0 0 1 1
R 0 1 1 0
R 0 1 -1 2   | 2                                                |
| 3
<br/>L 4 5 6 7
R 0 1 2 -1
R 1 0 -1 2  | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 0 1 2 -1
R -2 3 -1 2 | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 0 1 -2 3
R 1 0 -1 2  | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
S 1 2 1 3
S 1 -2 1 -3  | 1                                                |
| 3
<br/>L 4 5 6 7
S 1 3 1 5
S 1 4 1 6    | Infinitely intersections between line SS 1 and 2 |
| 3
<br/>L 4 5 6 7
L 1 3 1 5
S 1 4 1 6    | Infinitely intersections between line L 1 and 2  |
| 3
<br/>L 4 5 6 7
S 1 3 1 7
S 1 4 1 6    | Infinitely intersections between line SS 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 3 1 7
S 1 4 1 6    | Infinitely intersections between line RS 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 5 1 7
S 1 3 1 6    | Infinitely intersections between line RS 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 1 1 -2
S 1 3 1 5   | 0                                                |
| 3
<br/>L 4 5 6 7
R 1 1 1 -2
S 1 1 1 -2  | Infinitely intersections between line RS 1 and 2 |
| 3
<br/>L 4 5 6 7
S 1 1 1 -2
R 1 3 1 2   | Infinitely intersections between line SR 1 and 2 |
| 3
<br/>L 4 5 6 7
S 1 1 1 -2
R 1 -2 1 -4 | 1                                                |
| 3
<br/>L 4 5 6 7
S 1 1 1 -2
R 1 -3 1 -4 | 0                                                |
| 3
<br/>L 4 5 6 7
S 1 1 1 -2
R 1 -3 1 5  | Infinitely intersections between line SR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 3 1 5
R 1 1 1 -2   | 0                                                |
| 3
<br/>L 4 5 6 7
R 1 3 1 5
R 1 1 1 2    | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 5 1 3
R 1 1 1 -2   | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 1 1 5
R 1 3 1 -2   | Infinitely intersections between line RR 1 and 2 |
| 3
<br/>L 4 5 6 7
R 1 3 1 -3
R 1 -2 1 7  | Infinitely intersections between line RR 1 and 2 |

11
R -1 1 1 3
L 1 0 0 3
S -2 4 2 2
L -3 0 4 -5
S 2 0 2 2
S 2 0 2 -1
S 3 0 3 2
R 0 -5 1 -5
R 0 -5 -1 -5
R 0 -7 -1 -8
S 0 -7 1 -6

