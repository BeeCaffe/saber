#include"../saber/log.h"
#include<string>
#include<iostream>
using namespace saber;
int main(){
		/*
		 * test 1
		std::shared_ptr<Logger>  logger(new Logger("MyLog"));
		
		std::shared_ptr<LogFormatter> fmt(new LogFormatter());
		
		//std::shared_ptr<LogEvent> event(new LogEvent(__FILE__,__LINE__,LogLevel::Level::DEBUG,0,0,0,0,"thread 1",logger,"false"));
		LOG_EVENT(logger,LogLevel::DEBUG);

		LogAppender::ptr std_app(new StdOutAppender(LogLevel::DEBUG,fmt));
		LogAppender::ptr file_app(new FileAppender(LogLevel::DEBUG,fmt,"../log/mynewlog.txt"));

		logger->addAppender(std_app);
		logger->addAppender(file_app);
		logger->debug(event);
		*/
		/*
		 * test 2
		Logger::ptr log(new Logger(LogLevel::DEBUG,"TestLog"));
		saber::LogConfig::ptr logger(new LogConfig(log));
		Logger::ptr root(new Logger(logger->getRootLogger()));
		SABER_LOG_DEBUG(root)<<"this is a test";
		*/
		SABER_LOG_DEBUG(SABER_LOG_ROOT)<<"hello world";
	return 0;
}

