#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

struct Node
{
   char data;
   Node * lchild;
   Node * rchild;
};

Node* CreatTree(string pre, string in)
{
   Node * root = NULL;  //树的初始化
   if(pre.length() > 0)
   {
      root = new Node;  //为根结点申请结构体所需要的内存
      root->data = pre[0]; //先序序列的第一个元素为根结点
      int index = in.find(root->data);  //查找中序序列中的根结点位置
      root->lchild = CreatTree(pre.substr(1, index), in.substr(0, index));  //递归创建左子树
      root->rchild = CreatTree(pre.substr(index + 1), in.substr(index + 1)); //递归创建右子树
   }
   return root;
}

void PostOrder(Node * root)  //递归后序遍历
{ 
   if(root != NULL)
   {
      PostOrder(root->lchild);
      PostOrder(root->rchild);
      cout<<root->data;
   }
}

int main()
{
   string pre_str, in_str;
   Node *root;
   while(cin>>pre_str>>in_str)
   {
      root = CreatTree(pre_str, in_str);
      PostOrder(root);
      cout<<endl;
   }
   return 0;
}        

