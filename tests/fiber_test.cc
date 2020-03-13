#include"../saber/fiber.h"
#include"../saber/log.h"
#include<iostream>
using namespace saber;

static Logger::ptr g_logger=LOG_NEW("system");

void func(){
    LOG_INFO(g_logger)<<"hello world";
    Fiber::YeildToHold();
    LOG_INFO(g_logger)<<"hello world";
    Fiber::YeildToHold();
}

void test_fiber(){
    Fiber::GetThis();
    {
        Fiber::ptr fbr(new Fiber(std::function<void()>(func),0));
        fbr->swapIn();
        fbr->swapIn();
        LOG_INFO(g_logger)<<"main fiber end!";

        fbr->swapIn();
    }
    LOG_INFO(g_logger)<<"main fiber end2!";

}

int main(){
    std::vector<saber::Thread::ptr> threads;
    for(int i=0;i<3;++i){
        threads.push_back(saber::Thread::ptr(new saber::Thread(&test_fiber,"thread_"+std::to_string(i))));
    }

    for(auto i:threads){
       i->join(); 
    }
    return 0;
}
