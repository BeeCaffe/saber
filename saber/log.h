#ifndef __SABER_LOG_H
#define __SABER_LOG_H
#include<string>
#include<vector>
#include<memory>
#include<time.h>
#include<stdio.h>
#include<sstream>
#include<string.h>
#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include"utils.h"

////according to name new a logger
#define SABER_LOG_NEW(name)\
		saber::LogConfig::ptr(new LogConfig(Logger::ptr(new Logger(LogLevel::DEBUG,#name))))->getRootLogger()


////get and set root logger
#define SABER_LOG_ROOT\
	saber::LogConfig::ptr(new LogConfig(Logger::ptr(new Logger(LogLevel::DEBUG,"Root"))))->getRootLogger()


////print log, before that you should set logger's configurations ahead
#define SABER_LOG_EVENT(logger,level)\
	if(level>=logger->getLevel())\
		saber::LogEventWarp(saber::LogEvent::ptr(new saber::LogEvent(\
		__FILE__,__LINE__,level,saber::GetPid(),saber::GetFiberId(),\
		saber::GetElapse(),time(0),"no thread name",logger))).getSS()

//// print debug level log
#define SABER_LOG_DEBUG(logger)\
	SABER_LOG_EVENT(logger,LogLevel::DEBUG)

//// print info level log
#define SABER_LOG_INFO(logger)\
	SABER_LOG_EVENT(logger,LogLevel::INFO)

////print warn level log
#define SABER_LOG_WARN(logger)\
	SABER_LOG_EVENT(logger,LogLevel::WARN)

////print error level log
#define SABER_LOG_ERROR(logger)\
	SABER_LOG_EVENT(logger,LogLevel::ERROR)

////print fatal level log
#define SABER_LOG_FATAL(logger)\
	SABER_LOG_EVENT(logger,LogLevel::FATAL)
	
namespace saber{

	class Logger;

	class LogEvent;


	/*
	 *@brief class LogLvel
	 */
	class LogLevel{
		public:
				enum Level{
					UNKNOWN=0,
					DEBUG=1,
					INFO=2,
					WARN=3,
					ERROR=4,
					FATAL=5
				};
	};
	/*
	 *@brief class LogEvent
	 */
	class LogEvent{
		public:
			typedef std::shared_ptr<LogEvent> ptr;
			
			LogEvent(std::string m_file,uint32_t line,
					 LogLevel::Level level,uint32_t thread_id,
					 uint32_t fiber_id,uint32_t elapse,
					 time_t time,std::string thread_name,
					 std::shared_ptr<Logger> logger);
			
			~LogEvent(){};
			
			const std::string getFile() const {return m_file;}

			const uint32_t getThreadId() const {return m_threadId;}

			const uint32_t getFiberId() const{return m_fiberId;}

			const uint32_t getElapse() const {return m_elapse;}

			time_t getTime() {return m_time;}

			const uint32_t getLine() const {return m_line;}

			const std::string getThreadName() const{return m_threadName;}

			const std::shared_ptr<Logger> getLogger() const {return m_logger;}

			const LogLevel::Level getLevel() const {return m_level;}

			const std::string getMsg() const {return m_message;}

			std::stringstream& getSS() {return m_ss;}

			void setMsg(std::string& msg){m_message=msg;}
			
			const bool getHasPirnt() const {return hasPirnt;}

			void setHasPrint(bool status){hasPirnt=status;}

		private:

			std::string m_file;		//file name
			
			uint32_t m_threadId=0;	//thread id
			
			uint32_t m_fiberId=0;	//fiber id
			
			uint32_t m_elapse=0;	//elapse
			
			time_t m_time=0;		//time 
			
			uint32_t m_line=0;		//line
			
			std::string m_threadName;//thread name
			
			std::shared_ptr<Logger> m_logger;//logger
			
			LogLevel::Level m_level=LogLevel::DEBUG;//log level
			
			std::string m_message;	//log content
			
			std::stringstream m_ss;

			bool hasPirnt=false;
	};
	/*
	 *@brief class LogFormatter
	 */
	class LogFormatter{
		public:
			typedef std::shared_ptr<LogFormatter> ptr;

			LogFormatter()=default;

			LogFormatter(std::string pattern);

			~LogFormatter(){}

			std::string format(std::shared_ptr<Logger> &logger,std::shared_ptr<LogEvent> &event);

			std::string parsePattern(std::shared_ptr<LogEvent> &event,const std::string &pattern,std::shared_ptr<Logger> &logger);

		public:
			std::string pMsg(std::shared_ptr<LogEvent> &event);
			std::string pLevel(std::shared_ptr<LogEvent> &event);
			std::string pElapse(std::shared_ptr<LogEvent> &event);
			std::string pLogName(std::shared_ptr<LogEvent> &event,std::shared_ptr<Logger> &logger);
			std::string pthreadId(std::shared_ptr<LogEvent> &event);
			std::string pNewLine(std::shared_ptr<LogEvent> &event);
			std::string pTime(std::shared_ptr<LogEvent> &event,std::string &fmt);
			std::string pFileName(std::shared_ptr<LogEvent> &event);
			std::string pLine(std::shared_ptr<LogEvent> &event);
			std::string pTab(std::shared_ptr<LogEvent> &event);
			std::string pFiberId(std::shared_ptr<LogEvent> &event);
			std::string pThreadName(std::shared_ptr<LogEvent> &event);

		private:
			std::string m_pattern="%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n";
	};
	/*
	 *@brief class LogAppender
	 */
	class LogAppender{
		public:
				typedef std::shared_ptr<LogAppender> ptr;

				LogAppender()=default;

				LogAppender(LogLevel::Level level,LogFormatter::ptr formatter):m_level(level),m_formatter(formatter){}

				virtual ~LogAppender(){}

				virtual void log(std::shared_ptr<Logger> &logger, LogLevel::Level level,LogEvent::ptr &event)=0;
				
				void setLevel(LogLevel::Level level){m_level=level;}

				void setFormatter(LogFormatter::ptr &formatter){m_formatter=formatter;}

		protected:
				LogLevel::Level m_level=LogLevel::DEBUG;

				LogFormatter::ptr m_formatter;

				bool hasFormatter=false;

	};

	class StdOutAppender: public LogAppender{
		public:
				typedef std::shared_ptr<StdOutAppender> ptr;
				////constrcutor
				StdOutAppender(LogLevel::Level level,LogFormatter::ptr formatter):LogAppender(level,formatter){}

				~StdOutAppender(){}

				void log(std::shared_ptr<Logger> &logger,LogLevel::Level level, LogEvent::ptr &event) override;
		private:
	};

	class FileAppender:public LogAppender{
			public:
					typedef std::shared_ptr<FileAppender> ptr;

					FileAppender(LogLevel::Level level,LogFormatter::ptr formatter,std::string file);

					FileAppender(std::string file);

					~FileAppender(){}

					void log(std::shared_ptr<Logger> &logger,LogLevel::Level level, LogEvent::ptr &event) override;

			private:

					std::string m_file="../log/dlogger.txt";

					std::ofstream m_os;
	};
	/*
	 *@brief class Logger
	 */
	class Logger:public std::enable_shared_from_this<Logger>{
		public:
				typedef std::shared_ptr<Logger> ptr;

				Logger(std::string name):m_name(name){}

				Logger(LogLevel::Level level,std::string name):m_level(level),m_name(name){}

				const std::string getName() const {return m_name;}
				
				void addAppender(LogAppender::ptr &appender){
					m_appenders.push_back(appender);
				}

				std::vector<LogAppender::ptr> getAppenders(){return m_appenders;}
				
				void delAppender();

				void clearAppender();

				void log(LogLevel::Level level,LogEvent::ptr &event);

				void debug(LogEvent::ptr &event);

				void info(LogEvent::ptr &event);

				void warn(LogEvent::ptr &event);

				void error(LogEvent::ptr &event);

				void fatal(LogEvent::ptr &event);

				const LogLevel::Level getLevel() const {return m_level;}

				LogLevel::Level getLevel(){return m_level;}

				std::string getName(){return m_name;}

				Logger(const Logger::ptr logger):m_name(logger->getName()),m_appenders(logger->getAppenders()),m_level(logger->getLevel()){}
				
		private:
			std::string m_name="root";

			std::vector<LogAppender::ptr> m_appenders;

			LogLevel::Level m_level=LogLevel::DEBUG;
	};

	class LogEventWarp{
	
		public:

			typedef	std::shared_ptr<LogEventWarp> ptr;

			LogEventWarp(LogEvent::ptr event):m_event(event){}

			~LogEventWarp(){
					if(!m_event->getHasPirnt()){

						m_event->getLogger()->log(m_event->getLevel(),m_event);
						m_event->setHasPrint(true);
					}
			}

			std::stringstream& getSS(){return m_event->getSS();};
			
			LogEvent::ptr getEvent(){return m_event;}

		private:

			LogEvent::ptr m_event;
	};

	class LogConfig{
		public:
				typedef std::shared_ptr<LogConfig> ptr;

				LogConfig(Logger::ptr logger):m_logger(logger){}

				~LogConfig(){};
				
				Logger::ptr getLogger(){return m_logger;}

				void addAppender(LogAppender::ptr &app){m_logger->addAppender(app);}
				void setFormatter(LogFormatter::ptr &fmt);

				Logger::ptr& getRootLogger();
		private:
				

				Logger::ptr m_logger;


	};

};
#endif
