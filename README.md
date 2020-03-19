# BUAA_SE_IntersectPrj_Pair
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

