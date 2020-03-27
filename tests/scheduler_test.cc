#include"../saber/saber.h"
#include"../saber/scheduler.h"
#include<iostream>
using namespace std;
static saber::Logger::ptr g_logger=LOG_ROOT;
void test_fiber(){
    for(int i=0;i<10;++i) LOG_INFO(g_logger)<<"test in fiber";
}

int main(){
    LOG_INFO(g_logger)<<"start";
    saber::Scheduler sc(3,false,"test");
    sc.schedule(&test_fiber);
    sc.schedule([](){
                cout<<"here is task 2 running";
                });
    sc.start();
    sc.stop();
    LOG_INFO(g_logger)<<"over";
    return 0;
}
