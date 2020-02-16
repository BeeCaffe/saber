#include"../saber/log.h"
#include<string>
#include<iostream>
#include<ctime>
using namespace saber;
int main(){
		//test 1
		/*
		Logger::ptr logger(new Logger("root"));
		LogLevel::Level level=LogLevel::Level::DEBUG;
		LogFormatter::ptr fmt(new LogFormatter());
		logger->setFormatter(fmt);
		LogAppender::ptr std_app(new StdOutAppender());
		LogAppender::ptr file_app(new FileAppender("../log/root.txt"));
		LogEvent::ptr event1(new LogEvent(level,__LINE__,__FILE__,0,0,time(0),0,logger,"id4"));		
		LogEvent::ptr event2(new LogEvent(level,__LINE__,__FILE__,0,0,time(0),0,logger,"id3"));
		logger->addAppender(std_app);
		logger->addAppender(file_app);
		event1->getMsg()<<"hello world";
		LogEventWarp(LogEvent::ptr(new LogEvent(level,__LINE__,__FILE__,0,0,time(0),0,logger,"id4"))).getMsg()<<"I am leiqinghua";
		LogManager::ptr mgr(new LogManager());
		Logger::ptr root(mgr->getRoot());*/

		//test 2
		//LOG_DEBUG(LOG_ROOT)<<"HELLO WORLD";
		//LOG_DEBUG(LOG_ROOT)<<"I am Lei qinghua";
		//LOG_DEBUG(LOG_ROOT)<<"HELLO WORLD";
		//LOG_DEBUG(LOG_ROOT)<<"HELLO WORLD";
		//LOG_DEBUG(LOG_ROOT)<<"HELLO WORLD";
		/*Logger::ptr logger(LogMng::Instance()->getLogger("log"));
		LogLevel::Level level=LogLevel::Level::INFO;
		if(level>=logger->getLevel()){
		LogEventWarp(LogEvent::ptr(new LogEvent(level,__LINE__,__FILE__,saber::GetPid(),saber::GetFiberId(),time(0),saber::GetElapse(),logger,"no name"))).getMsg()<<"New test";
		}*/
		//test 3
		LOG_INFO(LOG_NEW("log"))<<"HELLO WORLD";
		return 0;
}

