#ifndef __SABER_LOG_H
#define __SABER_LOG_H
#include<iostream>
#include<sstream>
#include<memory>
#include<ctime>
#include<vector>
#include<fstream>
#include"utils.h"
#include<map>
#include"singleton.h"
#include"thread.h"

namespace saber{
////get root logger, with only one instance
#define LOG_ROOT\
		saber::LogMng::Instance()->getRoot()
////get a new logger, with only one instance
#define LOG_NEW(name)\
	saber::LogMng::Instance()->getLogger(name)

////call logger
#define LOG_LOG(logger,level)\
	if(level>=logger->getLevel())\
	saber::LogEventWarp(saber::LogEvent::ptr(new saber::LogEvent(level,__LINE__,__FILE__,saber::GetThreadId(),saber::GetFiberId(),time(0),saber::GetElapse(),logger,"no name"))).getMsg()
////deifferent log
#define LOG_DEBUG(logger)\
		LOG_LOG(logger,saber::LogLevel::Level::DEBUG)
#define LOG_INFO(logger)\
		LOG_LOG(logger,saber::LogLevel::Level::INFO)
#define LOG_WARN(logger)\
		LOG_LOG(logger,saber::LogLevel::Level::WARN)
#define LOG_ERROR(logger)\
		LOG_LOG(logger,saber::LogLevel::Level::ERROR)
#define LOG_FATAL(logger)\
		LOG_LOG(logger,saber::LogLevel::Level::FATAL)

#define FIND_LOG(name)\
	saber::LogMng::Instance()->getLogger(name)

	class Logger;
	class LogFormatter;
	/**********************************************************************
	 *@brief class LogLevel
	 *********************************************************************/
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
		static std::string toString(LogLevel::Level level);
		static LogLevel::Level fromString(const std::string& str);
	};
	/**********************************************************************
	 *@brief class LogEvent
	 *********************************************************************/
	class LogEvent{
	public:
			typedef std::shared_ptr<LogEvent> ptr;
			LogEvent(LogLevel::Level level,
					 uint32_t line,
					 const char* file,
					 uint32_t thread_id,
					 uint32_t fiber_id,
					 uint64_t time,
					 uint32_t elapse,
					 std::shared_ptr<Logger> logger,
					 std::string thread_name
					 );
			////gettter
			const LogLevel::Level getLevel() const{return m_level;}
			const uint32_t getLine() const {return m_line;}
			const char* getFile() const {return m_file;}
			const uint32_t getThreadId() const {return m_threadId;}
			const uint32_t getFiberId() const {return m_fiberId;}
			const uint64_t getTime()const{return m_time;}
			const uint32_t getElapse()const{return m_elapse;}
			std::stringstream& getMsg(){return m_msg;}
			const std::shared_ptr<Logger> getLogger()const{return m_logger;}
			const std::string getThreadName() const{return m_threadName;}
	private:
		LogLevel::Level m_level=LogLevel::Level::DEBUG;
		uint32_t m_line=0;	////file line
		const char* m_file=nullptr;	////file name
		uint32_t m_threadId=0;	////thread id
		uint32_t m_fiberId=0;	////fiber id
		uint64_t m_time=0;		////timestamp 
		uint32_t m_elapse=0;	////program  run time
		std::stringstream m_msg; ////log message
		std::shared_ptr<Logger> m_logger;
		std::string m_threadName;
	};

	/*********************************************************************
	 *@brief class LogAppender
	 *********************************************************************/
	////base class
	class LogAppender{
		public:
				friend class Logger;

				typedef std::shared_ptr<LogAppender> ptr;

				typedef Mutex MutexType;

				LogAppender(){}

				LogAppender(LogLevel::Level level,std::shared_ptr<LogFormatter> formatter):m_level(level),m_formatter(formatter){}

				virtual ~LogAppender(){}

				virtual void log(LogLevel::Level,LogEvent::ptr)=0;
				
				////setter
				
				void setFormatter(const std::shared_ptr<LogFormatter>& fmt);

				void setFormatter(const std::string& pattern);

				const std::shared_ptr<LogFormatter> getFormatter(){
					MutexType::Lock lock(m_mutex);
					return m_formatter;
				}

				void setLevel(LogLevel::Level level){
					m_level=level;
				}

				virtual std::string toYamlString()=0;
		protected:
				LogLevel::Level m_level=LogLevel::Level::DEBUG;	///loglevel
				std::shared_ptr<LogFormatter> m_formatter;	////formatter
				bool m_hasFormatter=false;
				MutexType m_mutex;
	};

	////console appender
	class StdOutAppender:public LogAppender{
		public:
				typedef std::shared_ptr<StdOutAppender> ptr;

				StdOutAppender():LogAppender(){}

				void log(LogLevel::Level,LogEvent::ptr) override;

				virtual std::string toYamlString() override;

	};

	class FileAppender:public LogAppender{
	public:
		typedef std::shared_ptr<FileAppender> ptr;
		FileAppender(LogLevel::Level level,std::string file);
		FileAppender(std::string file);
		void reopen();
		void makeDirs();
		void log(LogLevel::Level level, LogEvent::ptr event) override;
		virtual std::string toYamlString() override;
	private:
		std::string m_file="../log/default_logger.txt";
		LogLevel::Level m_level=LogLevel::Level::DEBUG;
		std::ofstream m_os;
	};

	/**********************************************************************
	 *@brief class LogFormatter
	 *@describe 
	 *	%m -- message
	 *	%p -- level
	 *	%r -- elapse
	 *	%c -- log name
	 *	%t -- thread id
	 *	%n -- new line
	 *	%d -- time
	 *	%f -- file name
	 *	%l -- line
	 *	%T -- Tab
	 *	%F -- fiber id
	 *	%N -- thread name
	 *********************************************************************/
	class LogFormatter{
	public:
			typedef std::shared_ptr<LogFormatter> ptr;
			////constructor
			LogFormatter(std::string pattern):m_pattern(pattern){}
			LogFormatter(){}
			////core funtions
			std::string format(LogEvent::ptr);
			std::string parsePattern(LogEvent::ptr,std::string&);
			std::string timeString(LogEvent::ptr,std::string);
			std::string msgString(LogEvent::ptr);
			std::string levelString(LogEvent::ptr);
			std::string elapseString(LogEvent::ptr);
			std::string logNameString(LogEvent::ptr);
			std::string threadIdString(LogEvent::ptr);
			std::string newLineString(LogEvent::ptr);
			std::string fileNameString(LogEvent::ptr);
			std::string lineString(LogEvent::ptr);
			std::string tabString(LogEvent::ptr);
			std::string fiberIdString(LogEvent::ptr);
			std::string threadNameString(LogEvent::ptr);
			//getter and setter
			std::string getPattern(){return m_pattern;}
	private:
			std::string m_pattern="[%d{%y-%m-%d %H:%M:%S}] [%p] [thread id:%t] [fiber id:%F] [%c] (%f\:%l) - %m%n";
	};

	/**********************************************************************
	 *@brief class Logger
	 *********************************************************************/
	class Logger{
	public:
		typedef std::shared_ptr<Logger> ptr;
		typedef Mutex MutexType;
		Logger(std::string name):
				m_logName(name){
		}
		Logger(std::string name,
			   LogLevel::Level level):
			   m_logName(name),
			   m_level(level){
		}

		Logger(std::string name,
			   LogLevel::Level level,
			   LogFormatter::ptr fmt):
			   m_logName(name),
			   m_level(level),
			   m_formatter(fmt){
			   
		}
		const LogLevel::Level getLevel() const {return m_level;}
		////core functions
		void log(LogEvent::ptr,LogLevel::Level);
		void addAppender(LogAppender::ptr);
		void delAppender(LogAppender::ptr);
		void clearAppenders();
		void setFormatter(LogFormatter::ptr);
		void setFormatter(const std::string& fmt);
		void setLevel(LogLevel::Level level){
			m_level=level;
		}
		void debug(LogEvent::ptr);
		void info(LogEvent::ptr);
		void warn(LogEvent::ptr);
		void error(LogEvent::ptr);
		void fatal(LogEvent::ptr);
		const std::string getName() const {return m_logName;}
		std::string toYamlString();

	private:
		LogLevel::Level m_level=LogLevel::Level::DEBUG;
		std::vector<LogAppender::ptr> m_appenders;	////appenders
		LogFormatter::ptr m_formatter;
		std::string m_logName;
		Logger::ptr m_root;
		MutexType m_mutex;
	};
	/**********************************************************************
	 *@brief LogEventWarp
	 *********************************************************************/
	class LogEventWarp{
	public:
			typedef std::shared_ptr<LogEventWarp> ptr;
			////destruct and print log
			~LogEventWarp(){
					m_event->getLogger()->log(m_event,m_level);
			}
			LogEventWarp(LogEvent::ptr e):m_event(e){}
			LogEventWarp(LogEvent::ptr e,LogLevel::Level lvl):m_event(e),m_level(lvl){}
			std::stringstream& getMsg(){return m_event->getMsg();}
	private:
		LogLevel::Level m_level=LogLevel::Level::DEBUG;
		LogEvent::ptr m_event;
	};
	/*********************************************************************
	 *@brief class LogManager
	 ********************************************************************/
	class LogManager{
	public:
		typedef std::shared_ptr<LogManager> ptr;

		typedef Mutex MutexType;

		void initRoot();

		Logger::ptr getRoot();

		Logger::ptr getLogger(const std::string& log_name);

		Logger::ptr getLogger(const char* log_name){
			std::string s(log_name);
			return getLogger(s);
		}

		void addLogger(std::string log_name);

		std::string toYamlString();

		void init();

	private:
		std::map<std::string,Logger::ptr> m_loggers;

		Logger::ptr root_logger;

		MutexType m_mutex;

	};

	typedef saber::Singleton<LogManager> LogMng;

};
#endif
