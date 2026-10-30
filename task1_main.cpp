#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

class Config
{
public:
    void  add(const string &filename)
    {
        
        try
        {
            YAML::Node config=YAML::LoadFile (filename);
            if(!config["a"]||!config["b"]||config["a"].IsNull()||config["b"].IsNull())
            {
                cout<<"错误：参数缺失"<<endl;
                return;
            }
            int a=config["a"].as<int>();
            int b=config["b"].as<int>();
            cout<<"a+b="<<a+b<<endl;
        }
        catch(const YAML::BadFile &)
        {
            cout<<"错误：文件"<<filename<<"不存在"<<endl;
        }
        catch(const YAML::TypedBadConversion <int>&)
        {
            cout<<"错误：参数类型错误"<<endl;
        }
        catch(const exception &)
        {
            cout<<"错误:YAML格式错误"<<endl;
        }
    }

};

int main()
{
    Config C1;
   
    
   while(true)
    {
        system("clear");
        cout<<"正在监控配置文件"<<endl;
        C1.add("config.yaml");
        sleep(2);
    }
   return 0;
 }