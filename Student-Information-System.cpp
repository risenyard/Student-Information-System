#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

/*********************相关结构体声明********************/

struct  gak   //建立学生信息结构体
{
    long long id;  //学号
    string name;   //姓名
    int am;  //高等数学成绩
    int ci;  //计算机导论成绩
    int dm;  //离散数学成绩
    int pd;  //程序设计成绩
    int ds;  //数据结构成绩
    int cp;  //计算机原理成绩
    int dp;  //数据库原理成绩
    int sum; //总成绩
};

struct node//二叉树结点
{
    int data;//数据
    int mark;//标识符
    node* parent;//两亲
    node* lchild;//左孩子
    node* rchild;//右孩子
};

struct arcnode//邻接表边表结点
{
    int adj;
    arcnode* next;
};

struct vertexnode//邻接表顶点表结点
{
    int in;
    string vertex;
    arcnode* firstedge;
};

/**********************相关类声明************************/

class list//存储学生信息线性表类
{
  public:
     list(int n); //构造函数（读取文本）
     ~list();     //析构函数
     void Find(long long y);  //通过学号查找（查）
     void Change(long long t);   //通过学号改变信息（改）
     void Insert(); //插入学生信息（增）
     void Delete(string t);  //按名字删除学生信息（删）
     void PrintList();   //打印列表
     int getlength(); //获取表长度
     void choicemachine();//排序标准选择器
     void shiersort();   //希尔排序
     void kaisoukusort(int first, int end);//快速排序
     void heapsort();//堆排序
     friend class bisorttree;//排序二叉树友元类
     friend class bibantree;//平衡二叉树友元类
  private:
     gak *data;   //动态数组存放数据
     int *tem;   //暂时存放成绩
     int length;  //表长度
     int partition(int first,int end);//快速排序调用一次划分函数
     void sift(int k,int m);//堆排序调用堆调整函数
};


class bisorttree //排序二叉树友元类
{
  public:
    bisorttree(list &l);//构造排序二叉树
    void searchbst(int k,list &l);//查找
  private:
    node* root;//根结点
    void insertbst(node**r,int b,int i);//插入结点
    void forsearchbst(node* r,int k,list &l);//查找调用
};

class bibantree //平衡二叉树友元类
{
  public:
    bibantree(list &l);//构造排序二叉树
    void searchbbt(int k,list &l);//查找函数
    void leverorder(list &l);//层序遍历
  private:
    node* root;//根结点
    node* insertbbt(node**r,node**r2,int b,int i);//插入结点
    void forsearchbbt(node* r,int k,list &l);//查找函数调用
    void forsearchbbt2(node* r,int k,list &l);//查找函数调用2
    node* balance(node* r);//计算平衡因子
    int depth(node* r);//计算深度
    void ll(node**r2);//LL型旋转
    void rr(node**r2);//RR型旋转
    void lr(node**r2);//LR型旋转
    void rl(node**r2);//RL型旋转
};

class algraph //构建AOV网的邻接表
{
  public:
      algraph(string a[],int b[],int c[],int n,int e);//构造函数
      ~algraph();//析构函数
      void search();//查询必要科目
      void tuopu();//拓扑排序
  private:
    vertexnode *adjlist;
    int vertexnum,arcnum;

};


/***********************线性表类函数***********************/

 list::list(int n)//构造函数
{
    data=new gak[n+10];tem=new int[n+10];int i=1;
    ifstream infile("list.txt"); //写入文件
	if(!infile)
    {
        cerr << "open error!" << endl;
    }
    while(!infile.eof())
    {
        infile>>data[i].id>>data[i].name>>data[i].am
        >>data[i].ci>>data[i].dm>>data[i].pd>>data[i].ds
        >>data[i].cp>>data[i].dp>>data[i].sum;
        i++;
    }
    infile.close();
    length=n;
}

list::~list()//析构函数
{
    delete[] data;
    delete[] tem;
}

void list::Find(long long y) //通过学号查找（查）
{
    cout<<"请输入学号"<<endl;
    cin>>y;
    int m=0;
    for (int i=1; i<=length; i++)//遍历匹配
    {
        if (data[i].id == y)
        {
            cout<<"姓名:"<<data[i].name<<" "<<
            "高等数学成绩:"<<data[i].am<<" "<<
            "计算机导论成绩:"<<data[i].ci<<" "<<
            "离散数学成绩:"<<data[i].dm<<" "<<
            "程序设计成绩:"<<data[i].pd<<" "<<
            "数据结构成绩:"<<data[i].ds<<" "<<
            "计算机原理成绩:"<<data[i].cp<<" "<<
            "数据库原理成绩:"<<data[i].dp<<" "<<
            "总成绩"<<data[i].sum<<endl;
        }
        else m++;
    }
    if(m==length) cout<<"没有你要找的人！"<<endl;

}

void list ::Change(long long t) //通过学号改变信息（改）
{   cout<<"请输入学号"<<endl;
    cin>>t;
    string nam,maj;
    int m=0;int a;int s;
    for(int i=1;i<=length;i++)
    {
        if(data[i].id==t)
        {
            cout<<"请按下以下选项前的数字修改对应信息"<<endl;
            cout<<"1.学号 "<<"2.姓名 "<<"3. 高等数学成绩 "<<"4.计算机导论成绩 "
            <<"5.离散数学成绩 "<<endl<<"6.程序设计成绩 "<<"7.数据结构成绩 "<<
            "8.计算机原理成绩 "<<"9.数据库原理成绩 "<<"0.退出修改 "<<endl;
            cin>>s;
            while(s!=0)
            {
                switch(s)
                {
                    case 1:cout<<"输入新学号"<<endl;cin>>data[i].id;break;
                    case 2:cout<<"输入新姓名"<<endl;cin>>data[i].name;break;
                    case 3:cout<<"输入新成绩"<<endl;cin>>data[i].am;break;
                    case 4:cout<<"输入新成绩"<<endl;cin>>data[i].ci;break;
                    case 5:cout<<"输入新成绩"<<endl;cin>>data[i].dm;break;
                    case 6:cout<<"输入新成绩"<<endl;cin>>data[i].pd;break;
                    case 7:cout<<"输入新成绩"<<endl;cin>>data[i].ds;break;
                    case 8:cout<<"输入新成绩"<<endl;cin>>data[i].cp;break;
                    case 9:cout<<"输入新成绩"<<endl;cin>>data[i].dp;break;
                    default:cout<<"识别不能"<<endl;
                }
                data[i].sum=data[i].am+data[i].ci+data[i].dm
                +data[i].pd+data[i].ds+data[i].cp+data[i].dp;
                cout<<"请按下以下选项前的数字修改对应信息"<<endl;
                cout<<"1.学号 "<<"2.姓名 "<<"3. 高等数学成绩 "<<"4.计算机导论成绩 "
                <<"5.离散数学成绩 "<<endl<<"6.程序设计成绩 "<<"7.数据结构成绩 "<<
                "8.计算机原理成绩 "<<"9.数据库原理成绩 "<<"0.退出修改 "<<endl;
                cin>>s;
            }
            break;
        }
        else m++;
    }
    if(m==length) cout<<"没有你要找的人！"<<endl;
}

void list ::Insert()  //插入学生信息（增）
{
    int i;gak x;
    cout<<"请输入插入位置的序号"<<endl;cin>>i;
    cout<<"请输入学号:"<<endl;cin>>x.id;
    cout<<"请输入姓名:"<<endl;cin>>x.name;
    cout<<"请输入高等数学成绩:"<<endl;cin>>x.am;
    cout<<"请输入计算机导论成绩:"<<endl;cin>>x.ci;
    cout<<"请输入离散数学成绩:"<<endl;cin>>x.dm;
    cout<<"请输入程序设计成绩:"<<endl;cin>>x.pd;
    cout<<"请输入数据结构成绩:"<<endl;cin>>x.ds;
    cout<<"请输入计算机原理成绩:"<<endl;cin>>x.cp;
    cout<<"请输入数据库原理成绩:"<<endl;cin>>x.dp;

    if (i < 1 || i > length + 1) throw "ERROR";
    else
    {
        for (int j = length+1; j>i; j--) data[j] = data[j-1];
        data[i] = x;
        data[i].sum=data[i].am+data[i].ci+data[i].dm+
        data[i].pd+data[i].ds+data[i].cp+data[i].dp;
        length++;
    }

}

void list ::Delete(string t) //删除学生信息（删）
{
    cout<<"请输入姓名"<<endl;cin>>t;
    int m=0,len=length;
    for(int i=1;i<=length;i++)
    {
        if(data[i].name==t)
        {
            for(int j=i;j<length;j++) data[j]=data[j+1];
            length--;
            break;
        }
        else m++;
    }
    if(m==len)
    cout<<"输入姓名有误！"<<endl;
}

void list ::PrintList()   //打印成绩单至屏幕
{
    cout<<"学号"<<"           "<<"姓名"<<"    "<<"成绩:"<<"    "<<
    "高等数学"<<"   "<<"计算机导论"<<"   "<<"离散数学"<<"    "
    "程序设计"<<"   "<<"数据结构"<<"  "<<"计算机原理"<<
    "  "<<"数据库原理"<<"   "<<"总成绩"<<endl;
    for(int i=1;i<=length;i++)
    cout<<data[i].id<<"    "<<data[i].name<<"             "
    <<data[i].am<<"        "<<data[i].ci<<"              "<<data[i].dm
    <<"         "<<data[i].pd<<"         "<<data[i].ds<<"            "
    <<data[i].cp<<"          "<<data[i].dp<<"    "<<data[i].sum<<endl;

}

int  list::getlength() //获取表长度
{
    return length;
}

void list ::choicemachine() //排序标准选择器
{
    int n;
    cout<<"请按下数字选择您要排序的科目"<<endl;
    cout<<"1.高等数学成绩 "<<"2.计算机导论成绩 "<<"3.离散数学成绩 "
    <<endl<<"4.程序设计成绩 "<<"5.数据结构成绩 "<<"6.计算机原理成绩 "
    <<endl<<"7.数据库原理成绩 "<<"!其它数字按键视为排序总成绩"<<endl;
    cin>>n;
    switch(n)
    {
        case 1:for(int i=1;i<=length;i++)
               tem[i]=data[i].am;
               break;
        case 2:for(int i=1;i<=length;i++)
               tem[i]=data[i].ci;
               break;
        case 3:for(int i=1;i<=length;i++)
               tem[i]=data[i].dm;
               break;
        case 4:for(int i=1;i<=length;i++)
               tem[i]=data[i].pd;
               break;
        case 5:for(int i=1;i<=length;i++)
               tem[i]=data[i].ds;
               break;
        case 6:for(int i=1;i<=length;i++)
               tem[i]=data[i].cp;
               break;
        case 7:for(int i=1;i<=length;i++)
               tem[i]=data[i].dp;
               break;
        default:for(int i=1;i<=length;i++)
               tem[i]=data[i].sum;
               break;
    }
}

void list ::shiersort()   //希尔排序
{
    int j;
    for(int d=length/2;d>=1;d=d/2)
    {
        for(int i=d+1;i<=length;i++)//以d为增量，进行组内直接插入排序
        {
            tem[0]=tem[i];//暂存即将插入记录
            data[0]=data[i];
            j=i-d;//j指向子序列最后一个记录
            while(j>0&&tem[0]>tem[j])
            {
                data[j+d]=data[j];//记录后移d个位置
                tem[j+d]=tem[j];
                j=j-d; //比较同一子序列的前一个记录
            }
            data[j+d]=data[0];
            tem[j+d]=tem[0];
        }
    }

}

void list ::kaisoukusort(int first,int end)//快速排序
{
    if(first<end)
    {
        int central=partition(first,end);//一次划分
        kaisoukusort(first,central-1);//对前一个子序列进行快速排序
        kaisoukusort(central+1,end);//对后一个子序列进行快速排序
    }

}

int list ::partition(int first,int end)//快速排序调用一次划分函数
{
    int i=first;int j=end;
    while(i<j)
    {
       while (i<j && tem[i]>=tem[j]) j--;  //右侧扫描
       if (i<j)
       {
          tem[0]=tem[j];data[0]=data[j];//将较大记录交换到前面
          tem[j]=tem[i];data[j]=data[i];
          tem[i]=tem[0];data[i]=data[0];
          i++;
       }
       while (i<j && tem[i]>=tem[j]) i++;  //左侧扫描
       if (i<j)
       {
          tem[0]=tem[j];data[0]=data[j];//将较小记录交换到后面
          tem[j]=tem[i];data[j]=data[i];
          tem[i]=tem[0];data[i]=data[0];
          j--;
       }
    }
    return i;

}

void list ::heapsort()//堆排序
{
    for(int i=length/2;i>=1;i--)//由无序序列建堆（i初始值为最后一个结点的双亲）
       sift(i,length);
    for(int i=1;i<length;i++)
    {
       tem[0]=tem[1];data[0]=data[1];//移走堆顶
       tem[1]=tem[length-i+1];data[1]=data[length-i+1];
       tem[length-i+1]=tem[0];data[length-i+1]=data[0];
       sift(1,length-i);      //重建堆
    }

}

void list ::sift(int k,int m)//堆排序调用堆调整函数（从已有堆建造新小根堆）
{
    int i=k;int j=2*i;//要筛选结点的编号为k，j为k左孩子，堆中最后一个结点的编号为m
    while(j<=m)//筛选还没有进行到叶子
    {
        if(j<m&&tem[j]>tem[j+1]) j++;//左右孩子获得较小值
        if(tem[i]<tem[j]) break;//比较输入结点和较大子节点
        else
        {
            tem[0]=tem[j];data[0]=data[j];//交换
            tem[j]=tem[i];data[j]=data[i];
            tem[i]=tem[0];data[i]=data[0];
            i=j;j=2*i;//从该子节点开始重新调整直到筛选到叶子
        }
    }

}

/*********************二叉排序树类函数***********************/


bisorttree::bisorttree(list &l)//二叉排序树构造函数
{
    node* s;int n;int *a=new int[l.length+10];
    cout<<"请按下数字选择您通过二叉排序树要排序的科目"<<endl;
    cout<<"1.高等数学成绩 "<<"2.计算机导论成绩 "<<"3.离散数学成绩 "
    <<endl<<"4.程序设计成绩 "<<"5.数据结构成绩 "<<"6.计算机原理成绩 "
    <<endl<<"7.数据库原理成绩 "<<"!其它数字按键视为排序总成绩"<<endl;
    cin>>n;
    switch(n)
    {
        case 1:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].am;
               break;
        case 2:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].ci;
               break;
        case 3:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].dm;
               break;
        case 4:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].pd;
               break;
        case 5:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].ds;
               break;
        case 6:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].cp;
               break;
        case 7:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].dp;
               break;
        default:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].sum;
               break;
    }

    root=NULL;
    for (int i=1; i<=l.length; i++)//构造调用
    {
       insertbst(&root,a[i],i);
    }
    delete[] a;
}

void bisorttree::insertbst(node**r,int b,int i)//构造使用的插入结点函数
{
    if (*r==NULL) //创建结点
    {
        *r=new node;
        (*r)->lchild=(*r)->rchild=NULL;
        (*r)->data=b;(*r)->mark=i;
    }
    else if (b<(*r)->data) //递归
         insertbst(&((*r)->lchild),b,i);
    else insertbst(&((*r)->rchild),b,i);
}

void bisorttree::searchbst(int k,list &l)//二叉排序树查找
{

    forsearchbst(root,k,l);
}

void bisorttree::forsearchbst(node* r,int k,list &l)//二叉排序树查找调用函数
{
    if (r==NULL)
       cout<<"无法找到对应的人！"<<endl;
    else if (r->data == k)
    {
        do
        {
            cout<<"找到学生 "<<"姓名："<<l.data[r->mark].name
            <<"  "<<"学号："<<l.data[r->mark].id<<endl;
            r=r->rchild;
        }
        while(r!=NULL&&r->data == k);
    }
    else if (k < r->data)
         forsearchbst(r->lchild,k,l);
    else forsearchbst(r->rchild,k,l);

}


/*********************平衡二叉树类函数***********************/


bibantree::bibantree(list &l)//平衡二叉树构造函数
{
    node* s;int n;int* a=new int[l.length+10];
    cout<<"请按下数字选择您通过平衡二叉树要排序的科目"<<endl;
    cout<<"1.高等数学成绩 "<<"2.计算机导论成绩 "<<"3.离散数学成绩 "
    <<endl<<"4.程序设计成绩 "<<"5.数据结构成绩 "<<"6.计算机原理成绩 "
    <<endl<<"7.数据库原理成绩 "<<"!其它数字按键视为排序总成绩"<<endl;
    cin>>n;
    switch(n)
    {
        case 1:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].am;
               break;
        case 2:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].ci;
               break;
        case 3:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].dm;
               break;
        case 4:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].pd;
               break;
        case 5:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].ds;
               break;
        case 6:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].cp;
               break;
        case 7:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].dp;
               break;
        default:for(int i=1;i<=l.length;i++)
               a[i]=l.data[i].sum;
               break;
    }

    root=NULL;node* w;node* e;node *test=NULL;
    for (int i=1; i<=l.length; i++) //构造主体
    {
       w=insertbbt(&root,&test,a[i],i);//插入结点
       e=balance(w);//验证是否为平衡二叉树

       if(e!=NULL)//如果不是，则进行旋转操作
       {

           if(e->lchild!=NULL&&e->rchild!=NULL)
           {
               while(w!=e->lchild->lchild&&w!=e->rchild->rchild&&w!=e->lchild->rchild&&w!=e->rchild->lchild)
               {w=w->parent;}
               if(w==e->lchild->lchild) ll(&e);
               else if(w==e->rchild->rchild) rr(&e);
               else if(w==e->lchild->rchild) lr(&e);
               else if(w==e->rchild->lchild) rl(&e);
           }
           else if(e->lchild!=NULL&&e->rchild==NULL)
           {
               while(w!=e->lchild->lchild&&w!=e->lchild->rchild)
               {w=w->parent;}
               if(w==e->lchild->lchild) ll(&e);
               else if(w==e->lchild->rchild) lr(&e);
           }
           else if(e->lchild==NULL&&e->rchild!=NULL)
           {
               while(w!=e->rchild->lchild&&w!=e->rchild->rchild)
               {w=w->parent;}
               if(w==e->rchild->lchild) rl(&e);
               else if(w==e->rchild->rchild) rr(&e);
           }
        }

    }
    delete[] a;
}


node* bibantree::insertbbt(node**r,node**r2,int b,int i)//平衡二叉树构造使用的插入结点函数
{
    if (*r==NULL)
    {
        *r=new node;
        (*r)->lchild=(*r)->rchild=NULL;
        (*r)->data=b;(*r)->mark=i;
        (*r)->parent=*r2;
        return *r;
    }
    else if (b<(*r)->data)
         insertbbt(&((*r)->lchild),&(*r),b,i);
    else insertbbt(&((*r)->rchild),&(*r),b,i);
}

node* bibantree::balance(node* r)//求平衡因子函数
{
    int ban=0;
    while(ban<2&&r->parent!=NULL)
    {
        ban=abs(depth(r->parent->lchild)-depth(r->parent->rchild));
        r=r->parent;
    }
    if(ban==2) return r;
    if(r->parent==NULL) return NULL;

}

int bibantree::depth(node* r)//求深度函数
{
    int hl,hr;
    if (r== NULL) return 0;
    else
    {
        hl= depth(r->lchild);
        hr= depth(r->rchild);
        return max(hl, hr)+1;
    }
}

void bibantree::leverorder(list &l)//层序遍历
{
    int front,rear;node* q;node** Q=new node*[l.length+10];
    front = rear = -1;        //采用顺序队列，并假定不会发生上溢
    if (root == NULL) return;        //二叉树为空，算法结束
    Q[++rear]= root;                      //根指针入队
    while (front != rear)                  //当队列非空时
    {
        q = Q[++front];                    //出队
        cout <<"("<<q->data<<")";
        if (q->lchild != NULL)  Q[++rear] = q->lchild;
        if (q->rchild != NULL)  Q[++rear] = q->rchild;
    }
    delete[] Q;
}

void bibantree::ll(node** r2)//LL变幻
{
    node* b;b=(*r2)->lchild;
    b->parent=(*r2)->parent;
    if((*r2)->parent!=NULL)
    {
        if((*r2)->parent->lchild==*r2) (*r2)->parent->lchild=b;
        if((*r2)->parent->rchild==*r2) (*r2)->parent->rchild=b;
    }

    (*r2)->parent=b;(*r2)->lchild=b->rchild;
    if(b->rchild!=NULL) b->rchild->parent=*r2;
    b->rchild=*r2;
    if(b->parent==NULL) root=b;
}

void bibantree::rr(node** r2)//RR变幻
{
    node* b;b=(*r2)->rchild;
    b->parent=(*r2)->parent;
    if((*r2)->parent!=NULL)
    {
        if((*r2)->parent->lchild==*r2) (*r2)->parent->lchild=b;
        if((*r2)->parent->rchild==*r2) (*r2)->parent->rchild=b;
    }
    (*r2)->parent=b;(*r2)->rchild=b->lchild;
    if(b->lchild!=NULL) b->lchild->parent=*r2;
    b->lchild=*r2;
    if(b->parent==NULL) root=b;
}

void bibantree::lr(node** r2)//LR变幻
{
    node* c;c=(*r2)->lchild;
    rr(&c);
    ll(r2);
}

void bibantree::rl(node** r2)//RL变幻
{
    node* c;c=(*r2)->rchild;
    ll(&c);rr(r2);
}

void bibantree::searchbbt(int k,list &l)//平衡二叉树查找
{
    int p;
    cout<<"请输入查找模式"<<endl<<"1.测试平衡二叉树查找算法，重复值可能查找不全"
    <<endl<<"2.查找出全部重复值，但要牺牲平衡二叉树查找算法的时间优势"<<endl;
    cin>>p;
    if(p==1) forsearchbbt(root,k,l);
    if(p==2) forsearchbbt2(root,k,l);
}

void bibantree::forsearchbbt(node* r,int k,list &l)//平衡二叉树查找调用函数
{
    if (r==NULL)
       cout<<"无法找到对应的人！"<<endl;
    else if (r->data == k)
    {
        do
        {
            cout<<"找到学生 "<<"姓名："<<l.data[r->mark].name
            <<"  "<<"学号："<<l.data[r->mark].id<<endl;
            r=r->rchild;
        }
        while(r!=NULL&&r->data == k);
    }
    else if (k < r->data)
         forsearchbbt(r->lchild,k,l);
    else forsearchbbt(r->rchild,k,l);

}

void bibantree::forsearchbbt2(node* r,int k,list &l)//平衡二叉树查找调用函数2
{
    if (r==NULL)
       cout<<"某个查找部分无法找到对应的人！"<<endl;
    else if (r->data == k)
    {
        cout<<"找到学生 "<<"姓名："<<l.data[r->mark].name
        <<"  "<<"学号："<<l.data[r->mark].id<<endl;
        if(r->lchild!=NULL) forsearchbbt2(r->lchild,k,l);
        if(r->rchild!=NULL) forsearchbbt2(r->rchild,k,l);
    }
    else if (k <r->data)
         forsearchbbt2(r->lchild,k,l);
    else if (k >r->data)
         forsearchbbt2(r->rchild,k,l);

}


/***********************邻接表类函数**************************/

algraph::algraph(string a[],int b[],int c[],int n,int e)//邻接表构造函数
{
    vertexnum=n;arcnum=e;arcnode* s;int ss=0;
    adjlist=new vertexnode[n];
    for(int i=0;i<vertexnum;i++)//初始化顶点表
    {
        adjlist[i].vertex=a[i];
        adjlist[i].firstedge=NULL;
        adjlist[i].in=b[i];
    }
    for(int k=0;k<arcnum;k++)//构造边表
    {
        s=new arcnode;
        s->next=adjlist[c[ss]].firstedge;
        adjlist[c[ss]].firstedge=s;ss++;
        s->adj=c[ss];ss++;
    }

}

algraph::~algraph()//析构函数
{
    delete[] adjlist;
}

void algraph::search()//查询必要科目
{
    string a;arcnode* p;int i=0;int k;
    cout<<"要查询必要科目,请输入0,输入其它数字结束该进程(请不要输入数字以外的指示）"<<endl;cin>>k;
    if(k!=0) return;
    cout<<"请按汉字输入课程名称"<<endl;cin>>a;
    for(i;i<vertexnum;i++)
    {
        if(adjlist[i].vertex==a)
        {
            p=adjlist[i].firstedge;
            if(p==NULL) cout<<"该课程不是其它课程修读的必要条件"<<endl;
            else
            {
                cout<<"修完该课程下一步才能修读以下课程："<<endl;
                while(p!=NULL)
                {
                    cout<<adjlist[p->adj].vertex<<endl;
                    p=p->next;
                }
            }
            break;
        }

    }if(i==vertexnum) cout<<"输入有误"<<endl;
}

void algraph::tuopu()//拓扑排序
{
    vertexnode a[vertexnum];arcnode* p;int count=0;int rear=0;
    for(int i=0;i<vertexnum;i++)//扫描顶点表，将没有前驱的顶点加入栈
    {
        if(adjlist[i].in==0) a[rear++]=adjlist[i];
    }
    if(rear>0) cout<<"拓扑序列为: ";
    while(rear>0)//栈非空，循环操作
    {
        cout<<a[--rear].vertex<<" ";//弹栈
        count++;p=a[rear].firstedge;
        while(p!=NULL)
        {
            adjlist[p->adj].in--;//将顶点的各个邻接点的入度减1
            if(adjlist[p->adj].in==0) a[rear++]=adjlist[p->adj];//将新的入度为0的顶点入栈
            p=p->next;
        }
    }
    if (count<vertexnum) cout<<endl<<"不存在回路"<<endl<<endl;
    else cout<<endl<<"拓扑验证成功！存在回路"<<endl<<endl;
}

/***********************其它函数******************************/

void badboyschoice(list z)   //执行菜单
{
    srand((unsigned)time(NULL));//种子
    int s;string t;long long y;int gr;int sa;
    string a[7]={"高等数学","计算机导论","离散数学","程序设计","数据结构","计算机原理","数据库原理"};
    int c[20]={0,2,0,3,1,3,1,5,2,4,3,4,3,5,3,6,4,6,5,6};
    int b[7]={0,0,1,2,2,2,3};//构建AOV网数据
    cout<<"***********************************"<<endl<<"给出你的选择(请输入对应选项标号数字)"<<
    endl<<"1.增添一位学生"<<endl<<"2.删除一位学生"<<endl<<"3.改变信息"<<
    endl<<"4.通过学号查找信息"<<endl<<"5.打印列表"<<endl<<"6.构建二叉排序树查找"
    <<endl<<"7.构建二叉平衡树查找"<<endl<<"8.进行希尔排序"<<endl<<"9.进行快速排序"
    <<endl<<"10.进行堆排序"<<endl<<"11.构建AOV网"<<endl<<"12.退出"<<endl
    <<"***********************************"<<endl;
    cin>>s;
    while(s!=12)
        {
            switch(s)
            {
                case 1:z.Insert();break;
                case 2:z.Delete(t);break;
                case 3:z.Change(y);break;
                case 4:z.Find(y);break;
                case 5:z.PrintList();break;
                case 6:bisorttree *mytree;mytree=new bisorttree(z);
                       cout<<"输入您要查找的分数"<<endl;cin>>gr;
                       mytree->searchbst(gr,z);delete mytree;
                       break;
                case 7:bibantree *bantree;bantree=new bibantree(z);
                       cout<<"输入您要查找的分数"<<endl;
                       cin>>gr;
                       bantree->searchbbt(gr,z);delete bantree;
                       cout<<endl;
                       break;
                case 8:z.choicemachine();
                       z.shiersort();
                       cout<<endl<<"倒序排序成功！请打印列表查看结果！"<<endl;
                       break;
                case 9:z.choicemachine();
                       z.kaisoukusort(1,z.getlength());
                       cout<<endl<<"倒序排序成功！请打印列表查看结果！"<<endl;
                       break;
                case 10:z.choicemachine();
                       z.heapsort();
                       cout<<endl<<"倒序排序成功！请打印列表查看结果！"<<endl;break;
                case 11:algraph *aov;aov=new algraph(a,b,c,7,10);
                       aov->tuopu();aov->search();delete aov;break;
                default:cout<<"cannot get you"<<endl;break;
            }
             cout<<"***********************************"<<endl<<"给出你的选择(请输入对应选项标号数字)"<<
             endl<<"1.增添一位学生"<<endl<<"2.删除一位学生"<<endl<<"3.改变信息"<<
             endl<<"4.通过学号查找信息"<<endl<<"5.打印列表"<<endl<<"6.构建二叉排序树查找"
             <<endl<<"7.构建二叉平衡树查找"<<endl<<"8.进行希尔排序"<<endl<<
             "9.进行快速排序"<<endl<<"10.进行堆排序"<<endl<<"11.构建AOV网"<<endl
             <<"12.退出"<<endl<<"***********************************"<<endl;
             cin>>s;
         }
    cout<<"thank you boy, bye!"<<endl;
}

void randome(int n) //随机生成学生信息，写入文本
{

    gak *umare;umare=new gak[n];int*a=new int[n];//生成数组
    string ln[446];string fn[600];int c1=0;int c2=0;//姓名基础数组
    ifstream infile("Surname.txt");//导入姓名信息
    while(!infile.eof())
    {
        infile>>ln[c1];
        c1++;
    }
    infile.close();
    ifstream infile2("Firstname.txt");
    while(!infile2.eof())
    {
        infile2>>fn[c2];
        c2++;
    }
    infile2.close();
    for(int i=400;i<600;i++) fn[i]="   ";
    for(int i=0;i<n;i++) a[i]=i;//生成顺序学号后随机交换
    for(int i=n-1;i>0;i--) swap(a[i],a[rand()%i]);
    for(int i=0;i<n;i++)        //写入信息到数组
    {
        umare[i].id=2018000000+a[i];
        umare[i].am=rand()%101;
        umare[i].ci=rand()%101;
        umare[i].dm=rand()%101;
        umare[i].pd=rand()%101;
        umare[i].ds=rand()%101;
        umare[i].cp=rand()%101;
        umare[i].dp=rand()%101;
        umare[i].name=ln[rand()%446]+fn[rand()%400]+fn[rand()%600];
        umare[i].sum=umare[i].am+umare[i].ci+umare[i].dm+
        umare[i].pd+umare[i].ds+umare[i].cp+umare[i].dp;
    }
    ofstream outfile;   //从数组把信息写到文本
    outfile.open("list.txt");
    for(int i=0;i<n;i++)
    {
        outfile<<umare[i].id<<" "<<umare[i].name<<" "<<umare[i].am<<
        " "<<umare[i].ci<<" "<<umare[i].dm<<" "<<umare[i].pd<<" "<<
        " "<<umare[i].ds<<" "<<umare[i].cp<<" "<<umare[i].dp<<" "<<
        umare[i].sum<<"\n";
    }
    outfile.close();
    delete []umare;
    delete []a;
}


/**********************主函数******************************/
int main()
{
    int n;cout<<"请输入学生人数"<<endl;
    cin>>n;//输入学生人数
    randome(n);//随机构建学生信息
    list mylist(n);     //构造函数
    badboyschoice(mylist);  //执行菜单
    return 0;
}
