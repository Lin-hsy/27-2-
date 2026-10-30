#include <chrono>
#include <thread>
#include <iostream>
#include <numeric>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;
struct SensorPacket
{
    uint64_t id;
    chrono::steady_clock::time_point sent_time;
    vector<int> values;
};

class SafeQueue//安全队列
{
private:
    queue<SensorPacket> q;
    mutex mtx;
    bool finished=false;
    condition_variable not_empty;
public:
    void push_data(SensorPacket s1)
    {
        {
            lock_guard<mutex>lock (mtx);
            q.push(s1);
        }
        not_empty.notify_one();
    }

    bool pop_data(SensorPacket &s2)
    {
            unique_lock<mutex>lock (mtx);
            not_empty.wait(lock,[this]{return finished||!q.empty();});
            if(q.empty()&&finished) return false;
            s2=q.front();
            q.pop();
            return true;
    }

    void finish()
    {
        {
            lock_guard<mutex>lock (mtx);
            finished=true;
        }
        not_empty.notify_all();
    }
};

SafeQueue Q;

void producer()//采集线程
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int>dist(0,100);
    for(int i=0;i<20;i++)
    {
        SensorPacket s;
        s.id=i;
        for(int j=0;j<5;j++)
        {
            int t=dist(gen);
            s.values.push_back(t);
        }
        s.sent_time=chrono::steady_clock::now();
        Q.push_data(s);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    Q.finish();
}

void consumer()//处理线程
{
    SensorPacket s;
    while(Q.pop_data(s))
    {
        int min=*min_element(s.values.begin(),s.values.end());
        int max=*max_element(s.values.begin(),s.values.end());
        double a=accumulate(s.values.begin(),s.values.end(),0.0)/s.values.size();
        auto now_time=chrono::steady_clock::now();
        auto duration=chrono::duration<double,milli>(now_time-s.sent_time);
        cout<<"[结果] id="<<s.id<<", 数据=[";
        for(int i=0;i<5;i++)
        {
            cout<<s.values[i];
            if(i<4) cout<<",";
        }
        cout<<"], 最小值="<<min<<", 最大值="<<max
            <<", 平均值="<<fixed<<setprecision(2)<<a
            <<", 耗时="<<fixed<<setprecision(2)<<duration.count()<<" ms"<<endl;
    }
    cout<<"采集与处理完成，共处理20组数据，程序退出"<<endl;
}

int main()
{
    cout<<"小洁的传感器监测数据已启动"<<endl;
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}