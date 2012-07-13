/*
   强连通




   在 计算机图论中,强连通（Strongly Connected）是指有向图G（Directed Graph）中任意两点v1、v2之间都存在着v1到v2的路径(path,若途径的点和边都不重复,则称为路径)及v2到v1的路径。
   定理：
   一个有向图是强连通的，当且仅当G中有一个回路，它至少包含每个节点一次。
   证明：
   充分性
   如果G中有一个回路，它至少包含每个节点一次，则G中任两个节点都是互相可达的，故G是强连通 图。
   必要性
   如果有向图是强连通的，则任两个节点都是相互可达。故必可做一回路经过图中所有各点。若不然则 必有一回路不包含某一结点v，并且v与回路上的个节点就不是相互可达，与强连通条件矛盾
   强连通分量
   目录
   一、 Kosaraju算法1. 算法思路
   2. 伪代码
   3. 实现代码

   二、 Tarjan算法1. 算法思路
   2. 伪代码
   3. 实现代码

   三、 Gabow算法1. 思路分析
   2. 伪代码
   3. 实现代码

   四、 总结
   一、 Kosaraju算法1. 算法思路
   2. 伪代码
   3. 实现代码

   二、 Tarjan算法1. 算法思路
   2. 伪代码
   3. 实现代码

   三、 Gabow算法1. 思路分析
   2. 伪代码
   3. 实现代码

   四、 总结


   有向图中, u可达v不一定意味着v可达u. 相互可达则属于同一个强连通分量(Strongly Connected Component, SCC)
   最关键通用部分：强连通分量一定是图的深搜树的一个子树。
   一、 Kosaraju算法


   1. 算法思路


   基本思路：
   这个算法可以说是最容易理解，最通用的算法，其比较关键的部分是同时应用了原图G和反图 GT。(步骤1)先用对原图G进行深搜形成森林(树)，（步骤2）然后任选一棵树对其进行深搜(注意这次深搜节点A能往子节点B走的要求是EAB存在于反 图GT)，能遍历到的顶点就是一个强连通分量。余下部分和原来的森林一起组成一个新的森林，继续步骤2直到 没有顶点为止。
   改进思路：
   当然，基本思路实现起来是比较麻烦的(因为步骤2每次对一棵树进行深搜时，可能深搜到其他树上 去，这是不允许的，强连通分量只能存在单棵树中(由开篇第一句话可知))，我们当然不这么做，我们可以巧妙的选择第二深搜选择的树的顺序，使其不可能深搜 到其他树上去。想象一下，如果步骤2是从森林里选择树，那么哪个树是不连通(对于GT来说)到其他树上的呢？就是最后遍历出来的树，它的根节点在步骤1的 遍历中离开时间最晚，而且可知它也是该树中离开时间最晚的那个节点。这给我们提供了很好的选择，在第一次深搜遍历时，记录时间i离开的顶点j，即 numb[i]=j。那么，我们每次只需找到没有找过的顶点中具有最晚离开时间的顶点直接深搜(对于GT来说)就可以了。每次深搜都得到一个强连通分量。
   隐藏性质:
   分析到这里，我们已经知道怎么求强连通分量了。但是，大家有没有注意到我们在第二次深搜选择树 的顺序有一个特点呢？如果在看上述思路的时候，你的脑子在思考，相信你已经知道了！！！它就是：如果我们把求出来的每个强连通分量收缩成一个点，并且用求 出每个强连通分量的顺序来标记收缩后的节点，那么这个顺序其实就是强连通分量收缩成点后形成的有向无环图的拓扑序列。为什么呢？首先，应该明确搜索后的图 一定是有向无环图呢？废话，如果还有环，那么环上的顶点对应的所有原来图上的顶点构成一个强连通分量，而不是构成环上那么多点对应的独自的强连通分量了。 然后就是为什么是拓扑序列，我们在改进分析的时候，不是先选的树不会连通到其他树上（对于反图GT来说），也就是后选的树没有连通到先选的树，也即先出现 的强连通分量收缩的点只能指向后出现的强连通分量收缩的点。那么拓扑序列不是理所当然的吗？这就是Kosaraju算法的一个隐藏性质。

   2. 伪代码


Kosaraju_Algorithm:
step1：对原图G进行深度优先遍历，记录每个节点的离开时间。
step2：选择具有最晚离开时间的顶点，对反图GT进行遍历，删除能够遍历到的顶点，这些顶 点构成一个强连通分量。
step3：如果还有顶点没有删除，继续step2，否则算法结束。

3. 实现代码

*/
#include <iostream>
using namespace std;
const int MAXN = 110;
typedef int AdjTable[MAXN]; //邻接表类型
int n;
bool flag[MAXN]; //访问标志数组
int belg[MAXN]; //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int numb[MAXN]; //结束时间标记,其中numb[i]表示离开时间为i的顶点
AdjTable adj[MAXN], radj[MAXN]; //邻接表,逆邻接表
//用于第一次深搜,求得numb[1..n]的值
void VisitOne(int cur, int &sig)
{
   flag[cur] = true;
   for ( int i=1; i<=adj[cur][0]; ++i )
   {
      if ( false==flag[adj[cur][i]] )
      {
         VisitOne(adj[cur][i],sig);
      }
   }
   numb[++sig] = cur;
}
//用于第二次深搜,求得belg[1..n]的值
void VisitTwo(int cur, int sig)
{
   flag[cur] = true;
   belg[cur] = sig;　	　	for ( int i=1; i<=radj[cur][0]; ++i )
   {
      if ( false==flag[radj[cur][i]] )　			{
         VisitTwo(radj[cur][i],sig);　		　  }　	　	}
}
//Kosaraju算法,返回为强连通分量个数
int Kosaraju_StronglyConnectedComponent()
{
   int i, sig;    //第一次深搜
   memset(flag+1,0,sizeof(bool)*n);
   for ( sig=0,i=1; i<=n; ++i )
   {
      if ( false==flag[i] )
      {　			　	VisitOne(i,sig);　			}　		}
      //第二次深搜　		memset(flag+1,0,sizeof(bool)*n);
      for ( sig=0,i=n; i>0; --i )
      {
         if ( false==flag[numb[i]] )
         {
            VisitTwo(numb[i],++sig);
         }
      }
      return sig;
}
/*
   二、 Tarjan算法


   1. 算法思路


   这个算法思路不难理解，由开篇第一句话可知，任何一个强连通分量，必定是对原图的深度优先搜索 树的子树。那么其实，我们只要确定每个强连通分量的子树的根，然后根据这些根从树的最低层开始，一个一个的拿出强连通分量即可。那么身下的问题就只剩下如 何确定强连通分量的根和如何从最低层开始拿出强连通分量了。
   那么如何确定强连通分量的根，在这里我们维护两个数组，一个是indx[1..n]，一个是 mlik[1..n]，其中indx[i]表示顶点i开始访问时间，mlik[i]为与顶点i邻接的顶点未删除顶点j的mlik[j]和mlik[i]的 最小值(mlik[i]初始化为indx[i])。这样，在一次深搜的回溯过程中，如果发现mlik[i]==indx[i]那么，当前顶点就是一个强连 通分量的根，为什么呢？因为如果它不是强连通分量的根，那么它一定是属于另一个强连通分量，而且它的根是当前顶点的祖宗，那么存在包含当前顶点的到其祖宗 的回路，可知mlik[i]一定被更改为一个比indx[i]更小的值。
   至于如何拿出强连通分量，这个其实很简单，如果当前节点为一个强连通分量的根，那么它的强连通 分量一定是以该根为根节点的(剩下节点)子树。在深度优先遍历的时候维护一个堆栈，每次访问一个新节点，就压入堆栈。现在知道如何拿出了强连通分量了吧？ 是的，因为这个强连通分量时最先被压人堆栈的，那么当前节点以后压入堆栈的并且仍在堆栈中的节点都属于这个强连通分量。当然有人会问真的吗？假设在当前节 点压入堆栈以后压入并且还存在，同时它不属于该强连通分量，那么它一定属于另一个强连通分量，但当前节点是它的根的祖宗，那么这个强连通分量应该在此之前 已经被拿出。现在没有疑问了吧，那么算法介绍就完了。

   2. 伪代码


Tarjan_Algorithm:
step1:
找一个没有被访问过的节点v，goto step2(v)。否则，算法结束。
step2(v):
初始化indx[v]和mlik[v]
对于v所有的邻接顶点u：
1) 如果没有访问过，则step2(u),同时维护mlik[v]
2) 如果访问过，但没有删除，维护mlik[v]
如果indx[v]==mlik[v]，那么输出相应的强连通分量

3. 实现代码
*/
#include <iostream>
using namespace std;
const int MAXN = 110;
const char NOTVIS = 0x00; //顶点没有访问过的状态
const char VIS = 0x01; //顶点访问过,但没有删除的状态
const char OVER = 0x02; //顶点删除的状态
typedef int AdjTable[MAXN]; //邻接表类型
int n;
char flag[MAXN]; //用于标记顶点状态,状态有NOTVIS,VIS,OVER
int belg[MAXN]; //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int stck[MAXN]; //堆栈,辅助作用
int mlik[MAXN]; //很关键,与其邻接但未删除顶点地最小访问时间
int indx[MAXN]; //顶点访问时间
AdjTable adj[MAXN]; //邻接表
//深搜过程,该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   stck[++stck[0]] = cur; flag[cur] = VIS;
   mlik[cur] = indx[cur] = ++sig;
   for ( i=1; i<=adj[cur][0]; ++i )
   {
      if ( NOTVIS==flag[adj[cur][i]] )
      {
         Visit(adj[cur][i],sig,scc_num);
         if ( mlik[cur]>mlik[adj[cur][i]] )　				{
            mlik[cur] = mlik[adj[cur][i]];
         }
      }
      else if ( VIS==flag[adj[cur][i]] )　			{
         if ( mlik[cur]>indx[adj[cur][i]] ) //该部分的indx应该是mlik,但是根据算法的属性,使用indx也可以,且时间更少
         {
            mlik[cur] = indx[adj[cur][i]];
         }
      }
   }
   if ( mlik[cur]==indx[cur] )
   {
      ++ scc_num;
      do{
         belg[stck[stck[0]]] = scc_num;
         flag[stck[stck[0]]] = OVER;
      }while ( stck[stck[0]--]!=cur );
   }
}
//Tarjan算法,求解belg[1..n],且返回强连通分量个数,
int Tarjan_StronglyConnectedComponent()
{
   int i, sig, scc_num;
   memset(flag+1,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
         Visit(i,sig,scc_num);
      }
   }
   return scc_num;
}
/*
   三、 Gabow算法


   1. 思路分析


   这个算法其实就是Tarjan算法的变异体，我们观察一下，只是它用第二个堆栈来辅助求出强连 通分量的根，而不是Tarjan算法里面的indx[]和mlik[]数组。那么，我们说一下如何使用第二个堆栈来辅助求出强连通分量的根。
   我们使用类比方法，在Tarjan算法中，每次mlik[i]的修改都是由于环的出现(不 然，mlik[i]的值不可能变小)，每次出现环，在这个环里面只剩下一个mlik[i]没有被改变(深度最低的那个)，或者全部被改变，因为那个深度最 低的节点在另一个环内。那么Gabow算法中的第二堆栈变化就是删除构成环的节点，只剩深度最低的节点，或者全部删除，这个过程是通过出栈来实现，因为深 度最低的那个顶点一定比前面的先访问，那么只要出栈一直到栈顶那个顶点的访问时间不大于深度最低的那个顶点。其中每个被弹出的节点属于同一个强连通分量。 那有人会问：为什么弹出的都是同一个强连通分量？因为在这个节点访问之前，能够构成强连通分量的那些节点已经被弹出了，这个对Tarjan算法有了解的都 应该清楚，那么Tarjan算法中的判断根我们用什么来代替呢？想想，其实就是看看第二个堆栈的顶元素是不是当前顶点就可以了。
   现在，你应该明白其实Tarjan算法和Gabow算法其实是同一个思想的不同实现，但 是，Gabow算法更精妙，时间更少(不用频繁更新mlik[])。

   2. 伪代码


Gabow_Algorithm:
step1:
找一个没有被访问过的节点v，goto step2(v)。否则，算法结束。
step2(v):
将v压入堆栈stk1[]和stk2[]
对于v所有的邻接顶点u：
1) 如果没有访问过，则step2(u)
2) 如果访问过，但没有删除，维护stk2[](处理环的过程)
如果stk2[]的顶元素==v，那么输出相应的强连通分量

3. 实现代码

*/
#include <iostream>
using namespace std;
const int MAXN = 110;
typedef int AdjTable[MAXN]; //邻接表类型
int n;
int intm[MAXN]; //标记进入顶点时间
int belg[MAXN]; //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int stk1[MAXN]; //辅助堆栈
int stk2[MAXN]; //辅助堆栈
AdjTable adj[MAXN]; //邻接表
//深搜过程,该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   intm[cur] = ++sig;
   stk1[++stk1[0]] = cur;
   stk2[++stk2[0]] = cur;
   for ( i=1; i<=adj[cur][0]; ++i )
   {
      if ( 0==intm[adj[cur][i]] )
      {
         Visit(adj[cur][i],sig,scc_num);
      }
      else if ( 0==belg[adj[cur][i]] )
      {
         while ( intm[stk2[stk2[0]]]>intm[adj[cur][i]] )
         {
            -- stk2[0];
         }
      }
   }
   if ( stk2[stk2[0]]==cur )
   {
      -- stk2[0]; ++ scc_num;
      do
      {
         belg[stk1[stk1[0]]] = scc_num;
      }
      while ( stk1[stk1[0]--]!=cur );
   }
}
//Gabow算法,求解belg[1..n],且返回强连通分量个数,
int Gabow_StronglyConnectedComponent()
{
   int i, sig, scc_num;
   memset(belg+1,0,sizeof(int)*n);
   memset(intm+1,0,sizeof(int)*n);
   sig = 0; scc_num = 0; stk1[0] = 0; stk2[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( 0==intm[i] )
      {
         Visit(i,sig,scc_num);
      }
   }
   return scc_num;
}
/*
   四、 总结

   写到这里，做一个总结：Kosaraju算法的第二次深搜隐藏了一个拓扑性质，而Tarjan算法 和Gabow算法省略了第二次深搜，所以，它们不具有拓扑性质。Tarjan算法用堆栈和标记，Gabow用两个堆栈（其中一个堆栈的实质是代替了 Tarjan算法的标记部分）来代替Kosaraju算法的第二次深搜，所以只用一次深搜，效率比Kosaraju算法高。
   */

