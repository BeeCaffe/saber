#include"../saber/saber.h"
static saber::Logger::ptr g_logger=LOG_ROOT;
void test_fiber(){
    LOG_INFO(g_logger)<<"test in fiber";
}

int main(){
    LOG_INFO(g_logger)<<"start";
    saber::Scheduler sc;
    sc.schedule(&test_fiber);
    sc.start();
    sc.stop();
    sc.schedule(&test_fiber);
    LOG_INFO(g_logger)<<"over";
    return 0;
}
