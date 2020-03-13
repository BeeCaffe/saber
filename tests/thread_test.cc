#include"../saber/saber.h"
#include<iostream>
saber::Logger::ptr g_logger=LOG_ROOT;

int count=0;
//saber::RWMutex s_mutex;
saber::Mutex s_mutex;
void func1(){
	LOG_INFO(g_logger)<<"name: "<<saber::Thread::GetName()
					  <<" this.name: "<<saber::Thread::GetThis()->getName()
					  <<" pid: "<<saber::GetThreadId()
					  <<" thread_id: "<<saber::Thread::GetThis()->getId();
	for(int i=0;i<10000000;++i){
		saber::Mutex::Lock lock(s_mutex);
		++count;
	}
}

void func2(){
	while(true){
		LOG_INFO(g_logger)<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	}
}

void func3(){
	while(true){
		LOG_INFO(g_logger)<<"===================================";
	}
}

int main(){
	LOG_INFO(g_logger)<<"thread test begin";
	std::vector<saber::Thread::ptr> threads;
	for(int i=0;i<2;++i){
		try{
			saber::Thread::ptr thread2(new saber::Thread(&func2,"name_"+std::to_string(i*2)));
			saber::Thread::ptr thread3(new saber::Thread(&func3,"name_"+std::to_string(i*2+1)));
			threads.push_back(thread2);
			threads.push_back(thread3);
		}catch(std::exception& e){
			LOG_DEBUG(g_logger)<<"thread new error";
		}
	}


	for(int i=0;i<2;++i){
		threads[i]->join();
	}

	LOG_INFO(g_logger)<<"thread test end";
	LOG_INFO(g_logger)<<"count="<<count;
	return 0;
}
