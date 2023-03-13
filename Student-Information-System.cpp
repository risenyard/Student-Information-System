#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

/*********************��ؽṹ������********************/

struct  gak   //����ѧ����Ϣ�ṹ��
{
    long long id;  //ѧ��
    string name;   //����
    int am;  //�ߵ���ѧ�ɼ�
    int ci;  //��������۳ɼ�
    int dm;  //��ɢ��ѧ�ɼ�
    int pd;  //������Ƴɼ�
    int ds;  //���ݽṹ�ɼ�
    int cp;  //�����ԭ��ɼ�
    int dp;  //���ݿ�ԭ��ɼ�
    int sum; //�ܳɼ�
};

struct node//���������
{
    int data;//����
    int mark;//��ʶ��
    node* parent;//����
    node* lchild;//����
    node* rchild;//�Һ���
};

struct arcnode//�ڽӱ�߱���
{
    int adj;
    arcnode* next;
};

struct vertexnode//�ڽӱ������
{
    int in;
    string vertex;
    arcnode* firstedge;
};

/**********************���������************************/

class list//�洢ѧ����Ϣ���Ա���
{
  public:
     list(int n); //���캯������ȡ�ı���
     ~list();     //��������
     void Find(long long y);  //ͨ��ѧ�Ų��ң��飩
     void Change(long long t);   //ͨ��ѧ�Ÿı���Ϣ���ģ�
     void Insert(); //����ѧ����Ϣ������
     void Delete(string t);  //������ɾ��ѧ����Ϣ��ɾ��
     void PrintList();   //��ӡ�б�
     int getlength(); //��ȡ����
     void choicemachine();//�����׼ѡ����
     void shiersort();   //ϣ������
     void kaisoukusort(int first, int end);//��������
     void heapsort();//������
     friend class bisorttree;//�����������Ԫ��
     friend class bibantree;//ƽ���������Ԫ��
  private:
     gak *data;   //��̬����������
     int *tem;   //��ʱ��ųɼ�
     int length;  //����
     int partition(int first,int end);//�����������һ�λ��ֺ���
     void sift(int k,int m);//��������öѵ�������
};


class bisorttree //�����������Ԫ��
{
  public:
    bisorttree(list &l);//�������������
    void searchbst(int k,list &l);//����
  private:
    node* root;//�����
    void insertbst(node**r,int b,int i);//������
    void forsearchbst(node* r,int k,list &l);//���ҵ���
};

class bibantree //ƽ���������Ԫ��
{
  public:
    bibantree(list &l);//�������������
    void searchbbt(int k,list &l);//���Һ���
    void leverorder(list &l);//�������
  private:
    node* root;//�����
    node* insertbbt(node**r,node**r2,int b,int i);//������
    void forsearchbbt(node* r,int k,list &l);//���Һ�������
    void forsearchbbt2(node* r,int k,list &l);//���Һ�������2
    node* balance(node* r);//����ƽ������
    int depth(node* r);//�������
    void ll(node**r2);//LL����ת
    void rr(node**r2);//RR����ת
    void lr(node**r2);//LR����ת
    void rl(node**r2);//RL����ת
};

class algraph //����AOV�����ڽӱ�
{
  public:
      algraph(string a[],int b[],int c[],int n,int e);//���캯��
      ~algraph();//��������
      void search();//��ѯ��Ҫ��Ŀ
      void tuopu();//��������
  private:
    vertexnode *adjlist;
    int vertexnum,arcnum;

};


/***********************���Ա��ຯ��***********************/

 list::list(int n)//���캯��
{
    data=new gak[n+10];tem=new int[n+10];int i=1;
    ifstream infile("list.txt"); //д���ļ�
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

list::~list()//��������
{
    delete[] data;
    delete[] tem;
}

void list::Find(long long y) //ͨ��ѧ�Ų��ң��飩
{
    cout<<"������ѧ��"<<endl;
    cin>>y;
    int m=0;
    for (int i=1; i<=length; i++)//����ƥ��
    {
        if (data[i].id == y)
        {
            cout<<"����:"<<data[i].name<<" "<<
            "�ߵ���ѧ�ɼ�:"<<data[i].am<<" "<<
            "��������۳ɼ�:"<<data[i].ci<<" "<<
            "��ɢ��ѧ�ɼ�:"<<data[i].dm<<" "<<
            "������Ƴɼ�:"<<data[i].pd<<" "<<
            "���ݽṹ�ɼ�:"<<data[i].ds<<" "<<
            "�����ԭ��ɼ�:"<<data[i].cp<<" "<<
            "���ݿ�ԭ��ɼ�:"<<data[i].dp<<" "<<
            "�ܳɼ�"<<data[i].sum<<endl;
        }
        else m++;
    }
    if(m==length) cout<<"û����Ҫ�ҵ��ˣ�"<<endl;

}

void list ::Change(long long t) //ͨ��ѧ�Ÿı���Ϣ���ģ�
{   cout<<"������ѧ��"<<endl;
    cin>>t;
    string nam,maj;
    int m=0;int a;int s;
    for(int i=1;i<=length;i++)
    {
        if(data[i].id==t)
        {
            cout<<"�밴������ѡ��ǰ�������޸Ķ�Ӧ��Ϣ"<<endl;
            cout<<"1.ѧ�� "<<"2.���� "<<"3. �ߵ���ѧ�ɼ� "<<"4.��������۳ɼ� "
            <<"5.��ɢ��ѧ�ɼ� "<<endl<<"6.������Ƴɼ� "<<"7.���ݽṹ�ɼ� "<<
            "8.�����ԭ��ɼ� "<<"9.���ݿ�ԭ��ɼ� "<<"0.�˳��޸� "<<endl;
            cin>>s;
            while(s!=0)
            {
                switch(s)
                {
                    case 1:cout<<"������ѧ��"<<endl;cin>>data[i].id;break;
                    case 2:cout<<"����������"<<endl;cin>>data[i].name;break;
                    case 3:cout<<"�����³ɼ�"<<endl;cin>>data[i].am;break;
                    case 4:cout<<"�����³ɼ�"<<endl;cin>>data[i].ci;break;
                    case 5:cout<<"�����³ɼ�"<<endl;cin>>data[i].dm;break;
                    case 6:cout<<"�����³ɼ�"<<endl;cin>>data[i].pd;break;
                    case 7:cout<<"�����³ɼ�"<<endl;cin>>data[i].ds;break;
                    case 8:cout<<"�����³ɼ�"<<endl;cin>>data[i].cp;break;
                    case 9:cout<<"�����³ɼ�"<<endl;cin>>data[i].dp;break;
                    default:cout<<"ʶ����"<<endl;
                }
                data[i].sum=data[i].am+data[i].ci+data[i].dm
                +data[i].pd+data[i].ds+data[i].cp+data[i].dp;
                cout<<"�밴������ѡ��ǰ�������޸Ķ�Ӧ��Ϣ"<<endl;
                cout<<"1.ѧ�� "<<"2.���� "<<"3. �ߵ���ѧ�ɼ� "<<"4.��������۳ɼ� "
                <<"5.��ɢ��ѧ�ɼ� "<<endl<<"6.������Ƴɼ� "<<"7.���ݽṹ�ɼ� "<<
                "8.�����ԭ��ɼ� "<<"9.���ݿ�ԭ��ɼ� "<<"0.�˳��޸� "<<endl;
                cin>>s;
            }
            break;
        }
        else m++;
    }
    if(m==length) cout<<"û����Ҫ�ҵ��ˣ�"<<endl;
}

void list ::Insert()  //����ѧ����Ϣ������
{
    int i;gak x;
    cout<<"���������λ�õ����"<<endl;cin>>i;
    cout<<"������ѧ��:"<<endl;cin>>x.id;
    cout<<"����������:"<<endl;cin>>x.name;
    cout<<"������ߵ���ѧ�ɼ�:"<<endl;cin>>x.am;
    cout<<"�������������۳ɼ�:"<<endl;cin>>x.ci;
    cout<<"��������ɢ��ѧ�ɼ�:"<<endl;cin>>x.dm;
    cout<<"�����������Ƴɼ�:"<<endl;cin>>x.pd;
    cout<<"���������ݽṹ�ɼ�:"<<endl;cin>>x.ds;
    cout<<"����������ԭ��ɼ�:"<<endl;cin>>x.cp;
    cout<<"���������ݿ�ԭ��ɼ�:"<<endl;cin>>x.dp;

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

void list ::Delete(string t) //ɾ��ѧ����Ϣ��ɾ��
{
    cout<<"����������"<<endl;cin>>t;
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
    cout<<"������������"<<endl;
}

void list ::PrintList()   //��ӡ�ɼ�������Ļ
{
    cout<<"ѧ��"<<"           "<<"����"<<"    "<<"�ɼ�:"<<"    "<<
    "�ߵ���ѧ"<<"   "<<"���������"<<"   "<<"��ɢ��ѧ"<<"    "
    "�������"<<"   "<<"���ݽṹ"<<"  "<<"�����ԭ��"<<
    "  "<<"���ݿ�ԭ��"<<"   "<<"�ܳɼ�"<<endl;
    for(int i=1;i<=length;i++)
    cout<<data[i].id<<"    "<<data[i].name<<"             "
    <<data[i].am<<"        "<<data[i].ci<<"              "<<data[i].dm
    <<"         "<<data[i].pd<<"         "<<data[i].ds<<"            "
    <<data[i].cp<<"          "<<data[i].dp<<"    "<<data[i].sum<<endl;

}

int  list::getlength() //��ȡ����
{
    return length;
}

void list ::choicemachine() //�����׼ѡ����
{
    int n;
    cout<<"�밴������ѡ����Ҫ����Ŀ�Ŀ"<<endl;
    cout<<"1.�ߵ���ѧ�ɼ� "<<"2.��������۳ɼ� "<<"3.��ɢ��ѧ�ɼ� "
    <<endl<<"4.������Ƴɼ� "<<"5.���ݽṹ�ɼ� "<<"6.�����ԭ��ɼ� "
    <<endl<<"7.���ݿ�ԭ��ɼ� "<<"!�������ְ�����Ϊ�����ܳɼ�"<<endl;
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

void list ::shiersort()   //ϣ������
{
    int j;
    for(int d=length/2;d>=1;d=d/2)
    {
        for(int i=d+1;i<=length;i++)//��dΪ��������������ֱ�Ӳ�������
        {
            tem[0]=tem[i];//�ݴ漴�������¼
            data[0]=data[i];
            j=i-d;//jָ�����������һ����¼
            while(j>0&&tem[0]>tem[j])
            {
                data[j+d]=data[j];//��¼����d��λ��
                tem[j+d]=tem[j];
                j=j-d; //�Ƚ�ͬһ�����е�ǰһ����¼
            }
            data[j+d]=data[0];
            tem[j+d]=tem[0];
        }
    }

}

void list ::kaisoukusort(int first,int end)//��������
{
    if(first<end)
    {
        int central=partition(first,end);//һ�λ���
        kaisoukusort(first,central-1);//��ǰһ�������н��п�������
        kaisoukusort(central+1,end);//�Ժ�һ�������н��п�������
    }

}

int list ::partition(int first,int end)//�����������һ�λ��ֺ���
{
    int i=first;int j=end;
    while(i<j)
    {
       while (i<j && tem[i]>=tem[j]) j--;  //�Ҳ�ɨ��
       if (i<j)
       {
          tem[0]=tem[j];data[0]=data[j];//���ϴ��¼������ǰ��
          tem[j]=tem[i];data[j]=data[i];
          tem[i]=tem[0];data[i]=data[0];
          i++;
       }
       while (i<j && tem[i]>=tem[j]) i++;  //���ɨ��
       if (i<j)
       {
          tem[0]=tem[j];data[0]=data[j];//����С��¼����������
          tem[j]=tem[i];data[j]=data[i];
          tem[i]=tem[0];data[i]=data[0];
          j--;
       }
    }
    return i;

}

void list ::heapsort()//������
{
    for(int i=length/2;i>=1;i--)//���������н��ѣ�i��ʼֵΪ���һ������˫�ף�
       sift(i,length);
    for(int i=1;i<length;i++)
    {
       tem[0]=tem[1];data[0]=data[1];//���߶Ѷ�
       tem[1]=tem[length-i+1];data[1]=data[length-i+1];
       tem[length-i+1]=tem[0];data[length-i+1]=data[0];
       sift(1,length-i);      //�ؽ���
    }

}

void list ::sift(int k,int m)//��������öѵ��������������жѽ�����С���ѣ�
{
    int i=k;int j=2*i;//Ҫɸѡ���ı��Ϊk��jΪk���ӣ��������һ�����ı��Ϊm
    while(j<=m)//ɸѡ��û�н��е�Ҷ��
    {
        if(j<m&&tem[j]>tem[j+1]) j++;//���Һ��ӻ�ý�Сֵ
        if(tem[i]<tem[j]) break;//�Ƚ�������ͽϴ��ӽڵ�
        else
        {
            tem[0]=tem[j];data[0]=data[j];//����
            tem[j]=tem[i];data[j]=data[i];
            tem[i]=tem[0];data[i]=data[0];
            i=j;j=2*i;//�Ӹ��ӽڵ㿪ʼ���µ���ֱ��ɸѡ��Ҷ��
        }
    }

}

/*********************�����������ຯ��***********************/


bisorttree::bisorttree(list &l)//�������������캯��
{
    node* s;int n;int *a=new int[l.length+10];
    cout<<"�밴������ѡ����ͨ������������Ҫ����Ŀ�Ŀ"<<endl;
    cout<<"1.�ߵ���ѧ�ɼ� "<<"2.��������۳ɼ� "<<"3.��ɢ��ѧ�ɼ� "
    <<endl<<"4.������Ƴɼ� "<<"5.���ݽṹ�ɼ� "<<"6.�����ԭ��ɼ� "
    <<endl<<"7.���ݿ�ԭ��ɼ� "<<"!�������ְ�����Ϊ�����ܳɼ�"<<endl;
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
    for (int i=1; i<=l.length; i++)//�������
    {
       insertbst(&root,a[i],i);
    }
    delete[] a;
}

void bisorttree::insertbst(node**r,int b,int i)//����ʹ�õĲ����㺯��
{
    if (*r==NULL) //�������
    {
        *r=new node;
        (*r)->lchild=(*r)->rchild=NULL;
        (*r)->data=b;(*r)->mark=i;
    }
    else if (b<(*r)->data) //�ݹ�
         insertbst(&((*r)->lchild),b,i);
    else insertbst(&((*r)->rchild),b,i);
}

void bisorttree::searchbst(int k,list &l)//��������������
{

    forsearchbst(root,k,l);
}

void bisorttree::forsearchbst(node* r,int k,list &l)//�������������ҵ��ú���
{
    if (r==NULL)
       cout<<"�޷��ҵ���Ӧ���ˣ�"<<endl;
    else if (r->data == k)
    {
        do
        {
            cout<<"�ҵ�ѧ�� "<<"������"<<l.data[r->mark].name
            <<"  "<<"ѧ�ţ�"<<l.data[r->mark].id<<endl;
            r=r->rchild;
        }
        while(r!=NULL&&r->data == k);
    }
    else if (k < r->data)
         forsearchbst(r->lchild,k,l);
    else forsearchbst(r->rchild,k,l);

}


/*********************ƽ��������ຯ��***********************/


bibantree::bibantree(list &l)//ƽ����������캯��
{
    node* s;int n;int* a=new int[l.length+10];
    cout<<"�밴������ѡ����ͨ��ƽ�������Ҫ����Ŀ�Ŀ"<<endl;
    cout<<"1.�ߵ���ѧ�ɼ� "<<"2.��������۳ɼ� "<<"3.��ɢ��ѧ�ɼ� "
    <<endl<<"4.������Ƴɼ� "<<"5.���ݽṹ�ɼ� "<<"6.�����ԭ��ɼ� "
    <<endl<<"7.���ݿ�ԭ��ɼ� "<<"!�������ְ�����Ϊ�����ܳɼ�"<<endl;
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
    for (int i=1; i<=l.length; i++) //��������
    {
       w=insertbbt(&root,&test,a[i],i);//������
       e=balance(w);//��֤�Ƿ�Ϊƽ�������

       if(e!=NULL)//������ǣ��������ת����
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


node* bibantree::insertbbt(node**r,node**r2,int b,int i)//ƽ�����������ʹ�õĲ����㺯��
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

node* bibantree::balance(node* r)//��ƽ�����Ӻ���
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

int bibantree::depth(node* r)//����Ⱥ���
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

void bibantree::leverorder(list &l)//�������
{
    int front,rear;node* q;node** Q=new node*[l.length+10];
    front = rear = -1;        //����˳����У����ٶ����ᷢ������
    if (root == NULL) return;        //������Ϊ�գ��㷨����
    Q[++rear]= root;                      //��ָ�����
    while (front != rear)                  //�����зǿ�ʱ
    {
        q = Q[++front];                    //����
        cout <<"("<<q->data<<")";
        if (q->lchild != NULL)  Q[++rear] = q->lchild;
        if (q->rchild != NULL)  Q[++rear] = q->rchild;
    }
    delete[] Q;
}

void bibantree::ll(node** r2)//LL���
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

void bibantree::rr(node** r2)//RR���
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

void bibantree::lr(node** r2)//LR���
{
    node* c;c=(*r2)->lchild;
    rr(&c);
    ll(r2);
}

void bibantree::rl(node** r2)//RL���
{
    node* c;c=(*r2)->rchild;
    ll(&c);rr(r2);
}

void bibantree::searchbbt(int k,list &l)//ƽ�����������
{
    int p;
    cout<<"���������ģʽ"<<endl<<"1.����ƽ������������㷨���ظ�ֵ���ܲ��Ҳ�ȫ"
    <<endl<<"2.���ҳ�ȫ���ظ�ֵ����Ҫ����ƽ������������㷨��ʱ������"<<endl;
    cin>>p;
    if(p==1) forsearchbbt(root,k,l);
    if(p==2) forsearchbbt2(root,k,l);
}

void bibantree::forsearchbbt(node* r,int k,list &l)//ƽ����������ҵ��ú���
{
    if (r==NULL)
       cout<<"�޷��ҵ���Ӧ���ˣ�"<<endl;
    else if (r->data == k)
    {
        do
        {
            cout<<"�ҵ�ѧ�� "<<"������"<<l.data[r->mark].name
            <<"  "<<"ѧ�ţ�"<<l.data[r->mark].id<<endl;
            r=r->rchild;
        }
        while(r!=NULL&&r->data == k);
    }
    else if (k < r->data)
         forsearchbbt(r->lchild,k,l);
    else forsearchbbt(r->rchild,k,l);

}

void bibantree::forsearchbbt2(node* r,int k,list &l)//ƽ����������ҵ��ú���2
{
    if (r==NULL)
       cout<<"ĳ�����Ҳ����޷��ҵ���Ӧ���ˣ�"<<endl;
    else if (r->data == k)
    {
        cout<<"�ҵ�ѧ�� "<<"������"<<l.data[r->mark].name
        <<"  "<<"ѧ�ţ�"<<l.data[r->mark].id<<endl;
        if(r->lchild!=NULL) forsearchbbt2(r->lchild,k,l);
        if(r->rchild!=NULL) forsearchbbt2(r->rchild,k,l);
    }
    else if (k <r->data)
         forsearchbbt2(r->lchild,k,l);
    else if (k >r->data)
         forsearchbbt2(r->rchild,k,l);

}


/***********************�ڽӱ��ຯ��**************************/

algraph::algraph(string a[],int b[],int c[],int n,int e)//�ڽӱ��캯��
{
    vertexnum=n;arcnum=e;arcnode* s;int ss=0;
    adjlist=new vertexnode[n];
    for(int i=0;i<vertexnum;i++)//��ʼ�������
    {
        adjlist[i].vertex=a[i];
        adjlist[i].firstedge=NULL;
        adjlist[i].in=b[i];
    }
    for(int k=0;k<arcnum;k++)//����߱�
    {
        s=new arcnode;
        s->next=adjlist[c[ss]].firstedge;
        adjlist[c[ss]].firstedge=s;ss++;
        s->adj=c[ss];ss++;
    }

}

algraph::~algraph()//��������
{
    delete[] adjlist;
}

void algraph::search()//��ѯ��Ҫ��Ŀ
{
    string a;arcnode* p;int i=0;int k;
    cout<<"Ҫ��ѯ��Ҫ��Ŀ,������0,�����������ֽ����ý���(�벻Ҫ�������������ָʾ��"<<endl;cin>>k;
    if(k!=0) return;
    cout<<"�밴��������γ�����"<<endl;cin>>a;
    for(i;i<vertexnum;i++)
    {
        if(adjlist[i].vertex==a)
        {
            p=adjlist[i].firstedge;
            if(p==NULL) cout<<"�ÿγ̲��������γ��޶��ı�Ҫ����"<<endl;
            else
            {
                cout<<"����ÿγ���һ�������޶����¿γ̣�"<<endl;
                while(p!=NULL)
                {
                    cout<<adjlist[p->adj].vertex<<endl;
                    p=p->next;
                }
            }
            break;
        }

    }if(i==vertexnum) cout<<"��������"<<endl;
}

void algraph::tuopu()//��������
{
    vertexnode a[vertexnum];arcnode* p;int count=0;int rear=0;
    for(int i=0;i<vertexnum;i++)//ɨ�趥�����û��ǰ���Ķ������ջ
    {
        if(adjlist[i].in==0) a[rear++]=adjlist[i];
    }
    if(rear>0) cout<<"��������Ϊ: ";
    while(rear>0)//ջ�ǿգ�ѭ������
    {
        cout<<a[--rear].vertex<<" ";//��ջ
        count++;p=a[rear].firstedge;
        while(p!=NULL)
        {
            adjlist[p->adj].in--;//������ĸ����ڽӵ����ȼ�1
            if(adjlist[p->adj].in==0) a[rear++]=adjlist[p->adj];//���µ����Ϊ0�Ķ�����ջ
            p=p->next;
        }
    }
    if (count<vertexnum) cout<<endl<<"�����ڻ�·"<<endl<<endl;
    else cout<<endl<<"������֤�ɹ������ڻ�·"<<endl<<endl;
}

/***********************��������******************************/

void badboyschoice(list z)   //ִ�в˵�
{
    srand((unsigned)time(NULL));//����
    int s;string t;long long y;int gr;int sa;
    string a[7]={"�ߵ���ѧ","���������","��ɢ��ѧ","�������","���ݽṹ","�����ԭ��","���ݿ�ԭ��"};
    int c[20]={0,2,0,3,1,3,1,5,2,4,3,4,3,5,3,6,4,6,5,6};
    int b[7]={0,0,1,2,2,2,3};//����AOV������
    cout<<"***********************************"<<endl<<"�������ѡ��(�������Ӧѡ��������)"<<
    endl<<"1.����һλѧ��"<<endl<<"2.ɾ��һλѧ��"<<endl<<"3.�ı���Ϣ"<<
    endl<<"4.ͨ��ѧ�Ų�����Ϣ"<<endl<<"5.��ӡ�б�"<<endl<<"6.������������������"
    <<endl<<"7.��������ƽ��������"<<endl<<"8.����ϣ������"<<endl<<"9.���п�������"
    <<endl<<"10.���ж�����"<<endl<<"11.����AOV��"<<endl<<"12.�˳�"<<endl
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
                       cout<<"������Ҫ���ҵķ���"<<endl;cin>>gr;
                       mytree->searchbst(gr,z);delete mytree;
                       break;
                case 7:bibantree *bantree;bantree=new bibantree(z);
                       cout<<"������Ҫ���ҵķ���"<<endl;
                       cin>>gr;
                       bantree->searchbbt(gr,z);delete bantree;
                       cout<<endl;
                       break;
                case 8:z.choicemachine();
                       z.shiersort();
                       cout<<endl<<"��������ɹ������ӡ�б�鿴�����"<<endl;
                       break;
                case 9:z.choicemachine();
                       z.kaisoukusort(1,z.getlength());
                       cout<<endl<<"��������ɹ������ӡ�б�鿴�����"<<endl;
                       break;
                case 10:z.choicemachine();
                       z.heapsort();
                       cout<<endl<<"��������ɹ������ӡ�б�鿴�����"<<endl;break;
                case 11:algraph *aov;aov=new algraph(a,b,c,7,10);
                       aov->tuopu();aov->search();delete aov;break;
                default:cout<<"cannot get you"<<endl;break;
            }
             cout<<"***********************************"<<endl<<"�������ѡ��(�������Ӧѡ��������)"<<
             endl<<"1.����һλѧ��"<<endl<<"2.ɾ��һλѧ��"<<endl<<"3.�ı���Ϣ"<<
             endl<<"4.ͨ��ѧ�Ų�����Ϣ"<<endl<<"5.��ӡ�б�"<<endl<<"6.������������������"
             <<endl<<"7.��������ƽ��������"<<endl<<"8.����ϣ������"<<endl<<
             "9.���п�������"<<endl<<"10.���ж�����"<<endl<<"11.����AOV��"<<endl
             <<"12.�˳�"<<endl<<"***********************************"<<endl;
             cin>>s;
         }
    cout<<"thank you boy, bye!"<<endl;
}

void randome(int n) //�������ѧ����Ϣ��д���ı�
{

    gak *umare;umare=new gak[n];int*a=new int[n];//��������
    string ln[446];string fn[600];int c1=0;int c2=0;//������������
    ifstream infile("Surname.txt");//����������Ϣ
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
    for(int i=0;i<n;i++) a[i]=i;//����˳��ѧ�ź��������
    for(int i=n-1;i>0;i--) swap(a[i],a[rand()%i]);
    for(int i=0;i<n;i++)        //д����Ϣ������
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
    ofstream outfile;   //���������Ϣд���ı�
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


/**********************������******************************/
int main()
{
    int n;cout<<"������ѧ������"<<endl;
    cin>>n;//����ѧ������
    randome(n);//�������ѧ����Ϣ
    list mylist(n);     //���캯��
    badboyschoice(mylist);  //ִ�в˵�
    return 0;
}
