#include"saber/saber.h"
#include"saber/iomanager.h"
using namespace saber;
using namespace std;
Logger::ptr g_logger=LOG_NEW("root");

void test_fiber(){
    LOG_INFO(g_logger)<<"test logger"<<endl;
}

void test1(){
    IOManager iom;
    iom.schedule(&test_fiber);
}
int main(int argc,char** argv){
    test1();
    return 0; 
}
