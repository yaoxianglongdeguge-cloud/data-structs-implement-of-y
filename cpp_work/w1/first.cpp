#include<iostream>
#include<initializer_list>
#include<stdlib.h>


class matrix_{
private:
double ** data=nullptr;
int row=0;
int column=0;


void reallocate(int row, int column) ;//内存分配函数
void matrix_swap(const matrix_ &a);//矩阵交换函数；

public:
//构造析构函数
matrix_();
matrix_(int row,int column);
matrix_(const matrix_ &a);
matrix_(std::initializer_list<std::initializer_list<double>>list);
~matrix_();


//运算符重载
matrix_ & operator=(const matrix_ &other);


//判断函数
bool empty() const;//矩阵为空判断
bool equal_rc(const matrix_ &a) const;//两矩阵相等判断




//增删改查函数
void push_back(int a);
void change(int row,int column,int a);
void remove(int row,int column);
void remove();
int check_row() const //const引用参数只能调用const函数
{
    return this->row;
}
int check_column() const
{
    return this->column;
}
double find(int row,int column);




//遍历函数
void visit()
{
    for(int i=0;i<this->row;i++)
    {
        for(int j=0;j<this->column;j++)
        {
            std::cout<<this->data[i][j]<<std::endl;
        }
    }
    
}

};
//矩阵类



//private函数
//数组内存分配
void matrix_:: reallocate (const int row,const int column) 
{
    
    if(this->empty()!=true)
    {
        for(int i=0;i<this->row;i++)
        {
            delete[] data[i];

        }
        delete[] data;
    }

    this->data=new double*[row];
    for(int i=0;i<row;i++)
    {
        this->data[i]=new double[column];
    }
    
} 
//交换两个矩阵
void matrix_::matrix_swap(const matrix_& a)
{
    matrix_ tem(a);
    matrix_ tem2;
    tem2.data=this->data;
    tem2.row=this->row;
    tem2.column=this->column;
    

    this->data=tem.data;
    this->row=tem.row;
    this->column=tem.column;
   

    


}





//public函数
//构造函数
matrix_:: matrix_(){}
matrix_::matrix_(int row,int column):data(nullptr),row(0),column(0){}
matrix_::matrix_(const matrix_ &a)
{
    
    this->reallocate(a.check_row(), a.check_column());
    for(int j=0;j<this->row;j++)
    {
        for(int i=0;i<this->column;i++)
        {
            this->data[j][i]=a.data[j][i];
        }
    }


}//拷贝构造函数
matrix_::matrix_(std::initializer_list<std::initializer_list<double>>list)
{

    this->matrix_(list.size(),list.begin()->size());
    std::initializer_list<std::initializer_list<double>>::iterator it1=list.begin();
  
    int count = list.begin()->size();

    while(it1!=list.end())
    {
        if(it1->size()!=count)
        {
            std::exit(1);
        }
        else
        {
            it1++;
        }

    }
    it1=list.begin();
    
   
    this->row=list.size();
    this->column=list.begin()->size();
    this->reallocate(this->row,this->column);
    for(int k=0;k<this->row;k++)
    {
        std::initializer_list<double>::iterator it2=it1->begin();
   
        for(int j=0;j<this->column;j++)
        {
            this->data[k][j]=*it2;
            it2++;

        }
        it1++;
    }


}//初始化列表构造函数


//析构函数
matrix_::~matrix_()
{
    for(int i=0;i<this->row;i++)
        {
            delete[] data[i];

        }
        delete[] data;
}




//判断两矩阵行列是否对应相等函数
bool matrix_::equal_rc(const matrix_ &a) const
{
    if(this->row==a.check_row()&&this->column==a.check_column())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool matrix_::empty() const{ return !(row==0||column==0||data==nullptr); }




//运算符重载函数
//矩阵赋值
matrix_ & matrix_::operator=(const matrix_ &other)
{
    if(other.data!=this->data)
    {
    if(this->equal_rc(other))
    {
       matrix_swap(other);
    }
    else
    {
       
            std::exit(1);

    }
    }
  else
    {
   
            std::exit(1);
    }

  return *this;
}




//增删查改函数
void matrix_::change(int row,int column,int a){}

void matrix_::remove(int row,int column){}

void matrix_::remove(){}




