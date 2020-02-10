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
		LOG_EVENT(logger,LogLevel::DEBUG,"hello debug test");

		LogAppender::ptr std_app(new StdOutAppender(LogLevel::DEBUG,fmt));
		LogAppender::ptr file_app(new FileAppender(LogLevel::DEBUG,fmt,"../log/mynewlog.txt"));

		logger->addAppender(std_app);
		logger->addAppender(file_app);
		logger->debug(event);
		*/

		//Logger::ptr logger(new Logger(LogLevel::DEBUG,"TestLog"));
		Logger::ptr logger(new Logger(LogLevel::FATAL,"TestLog"));
		SABER_LOG_CONF(logger,LogLevel::DEBUG,../log/testlog.txt);
		SABER_LOG_DEBUG(logger,"this debug error");
		SABER_LOG_FATAL(logger,"this is fatal");

	return 0;
}

