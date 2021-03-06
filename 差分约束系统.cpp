#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    差分约束系统的求解是可满足性问题的一种.数学上属于线性规划.
*    基本模型：
*    给定n个变量和m个约束条件,每个约束条件形式都是:di - dj <= bk  i,j∈[1,n],k∈[1,m].
*    这就构成了差分约束系统,目标是判断系统有没有解,有的话要给出一个解.
*    考虑到最短路的松弛条件是d[v]-d[u]<=w(u,v),和约束条件形式类似,于是得到一个解法:
*    (I)-建图
*        对于约束条件di-dj<=bk,建立有向边 j->i,其权是bk.
*        这样一来就变成了图的问题.
*        如果形式不一样,就把不等式变形就好了,让约束形式一致.
*    (II)-求最短路
*        先给之前建的图安置一个"超级结点",以便检测图上有没有负圈.
*        之后调用SPFA就可以完成求解,各个d[u]的值就是解,图上有负圈表示给出的系统无解.
*    有两种约束形式可以选用,分别对应求最短路和最长路的松弛条件.
*    下面仅介绍几种相关问题进行拓展,不再给出实现(因为和求最短路完全一样,重点在于建图)
*/

/**
*    (一)线性约束
*    有n个点排成一列,从左向右编号.给出一些条件:两点间距离限制.求出各点位置安排的一个解.
*    这个问题是很明显的差分约束,约束形式可以直接套用.设d(i)是物体的坐标(就是到原点的距离)
*    由于不能重叠,所以要加上自然约束:d(i-1) - d(i) <= -1 (写成<=的形式来保持一致)
*    再根据给出的条件建图,建好图后就成了完全抽象的最基本模型.
*/

/**
*    (二)区间约束
*    给定几个条件,每个为(ai,bi,ci).表示在区间[ai,bi]之间至少要选ci个点.
*    整体范围是[0,M],求一下总共至少要选多少个点.
*    这个问题有点递推的味道.定义状态d(x)是[0,x]之间选几个点.
*    于是对各个条件有不等式 d(bi)-d(ai-1)>=ci 变形为: d(ai-1)-d(bi) <= -ci.
*    按不等方程组建图,再加上自然约束: 0<= d[i]-d[i-1] <=1.(有向图中再加2M条边)
*    建好图后就成了完全抽象的最基本模型.执行算法后,对应结果是d[M];
*/

/**
*    (三)未知条件约束    
*    对这种变形,边上的权值bk不确定.例题:
*    公司招聘,有n个人申请.给出每个人开始工作的时间.已知每个人能连续工作p小时.
*    给定约束条件：i时刻至少得有R(i)个人坐班.(0<=i<=23)
*    从给出的信息求一下应该至少雇多少人才可以满足这些条件.
*    分析:这个变形本质上也是区间约束,但是约束值未知,可以进行枚举(枚举量较小所以没什么问题).
*    设从i时刻开始工作的人雇了a(i)个.进一步记d(i)=a(0)+a(1)+...+a(i);
*    设b(i)是i时刻最多可能的工作人数.
*    我们想要求得的值就是d(23),设其为T.于是有,
*    (0<=i<=7)  d(i)-d(i+16)>=R(i)-T;
*    (i>7)      d(i)-d(i-8)>=R(i);
*    再加上自然条件: 0<= d(i)-d(i-1)<= b(i);
*    然后开始从max{R(i)}向上枚举T,每次根据不等式方程组建好图后求解,直到可以得到一个解为止.
*/