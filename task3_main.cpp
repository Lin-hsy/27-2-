#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Shape
{
public:
    virtual double area()=0;
    virtual double perimeter()=0;
    virtual ~Shape(){}
};
//三角型
class Triangle:public Shape
{
public:
    Triangle (int a,int b,int c)
    {
        T_a=a;
        T_b=b;
        T_c=c;
    }
    virtual double area()
    {
        double p=(T_a+T_b+T_c)/2.0;
        return sqrt(p*(p-T_a)*(p-T_b)*(p-T_c));
    }
    virtual double perimeter()
    {
        return T_a+T_b+T_c;
    }
private:
    int T_a;
    int T_b;
    int T_c;
};
//矩形
class Rectangle:public Shape
{
public:
    Rectangle(int a,int b)
    {
        R_a=a;
        R_b=b;
    }
    virtual double area()
    {
        return R_a*R_b;
    }
    virtual double perimeter()
    {
        return 2*(R_a+R_b);
    }
private:
    int R_a;
    int R_b;
};
//圆形
class Circle:public Shape
{
public:
    Circle(int r)
    {
        C_r=r;
    }
    virtual double area()
    {
        return M_PI*pow(C_r,2);
    }
    virtual double perimeter()
    {
        return 2*M_PI*C_r;
    }
private:
    int C_r;
};

void test01()
{
    Shape* p=new Triangle(3,4,5);
    //三角形
    cout<<fixed<<setprecision(2)<<"三角形（边长3、4、5）：面积="<<p->area()<<",周长="<<p->perimeter()<<endl;
    delete p;
    p=nullptr;
    //矩形
    p=new Rectangle(4,3);
    cout<<fixed<<setprecision(2)<<"矩形（长 4、宽 3）：面积="<<p->area()<<",周长="<<p->perimeter()<<endl;
    delete p;
    p=nullptr;
    //圆形
    p=new Circle(2);
    cout<<fixed<<setprecision(2)<<"圆形（半径 2）：面积="<<p->area()<<",周长="<<p->perimeter()<<endl;
    delete p;
    p=nullptr;
};
    
int main()
{
    test01();
    return 0;
}