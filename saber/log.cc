#include"log.h"
using namespace saber;
/**
 *@brief class LogEvent functions
 */
saber::LogEvent::LogEvent(std::string file,
						  uint32_t line,
					 	  LogLevel::Level level,
						  uint32_t thread_id,
					 	  uint32_t fiber_id,
						  uint32_t elapse,
					 	  time_t time,
						  std::string thread_name,
					 	  std::shared_ptr<Logger> logger,
						  std::string msg):
					 m_file(file),m_line(line),
					 m_level(level),m_threadId(thread_id),
					 m_fiberId(fiber_id),m_elapse(elapse),
					 m_time(time),m_threadName(thread_name),
					 m_logger(logger),m_message(msg){}

/*
 *@brief class LogFormatter functions
 */
saber::LogFormatter::LogFormatter(std::string pattern):
m_pattern(pattern){}


std::string saber::LogFormatter::parsePattern(std::shared_ptr<LogEvent> &event,const std::string &pattern,std::shared_ptr<Logger> &logger){
	if(pattern.empty()) return "";
	int sz=pattern.size();
	std::stringstream ss;
	for(int i=0;i<sz;++i){
		if(pattern[i]=='%'){
			if((i+1)<sz&&pattern[i+1]=='%'){ 
					ss<<"%";
					continue;
			}else if(i+1<sz&&pattern[i+1]=='d'){//prase time format
				if(i+2<sz&&pattern[i+2]=='{'){
					int n=i+2;
					while(n<sz&&pattern[n]!='}') ++n;
					std::string timefmt=pattern.substr(i+3,n-i-3);
					ss<<pTime(event,timefmt);
					i=n;
				}else{
					ss<<"<<pattern error>>"<<"%d shuld follow with {}\n";
					return ss.str();
				}
			}else if(i+1<sz){//parse others
					char ch=pattern[i+1];
				switch(ch){
#define XX(curch,func)	case curch: \
						ss<<func(event); \
						break;

						XX('m',pMsg)
						XX('p',pLevel)
						XX('t',pthreadId)
						XX('n',pNewLine)
						XX('f',pFileName)
						XX('l',pLine)
						XX('T',pTab)
						XX('F',pFiberId)
						XX('N',pThreadName)
#undef XX
						case 'c':
							ss<<pLogName(event,logger);
							break;
						default:
							ss<<"<<pattern error>> pattern string is illegal";
							break;
				}
				++i;
			}

		}else if(pattern[i]=='['){
				ss<<"[";
				int j=i+1;
				while(j<sz&&pattern[j]!=']') ++j;
				std::string tmp(parsePattern(event,pattern.substr(i+1,j-i-1),logger));
				ss<<tmp;
				ss<<"]";
				i=j;
				
		}else if(isspace(pattern[i])){
			continue;
		}else{
			ss<<pattern[i];
		}
	}
	return ss.str();
}

std::string LogFormatter::format(std::shared_ptr<saber::Logger> &logger,std::shared_ptr<saber::LogEvent> &event){
	std::stringstream ss;
	ss<<parsePattern(event,m_pattern,logger);
	return ss.str();
}
	
std::string saber::LogFormatter::pMsg(std::shared_ptr<LogEvent> &event){
		std::stringstream ss;
		ss<<event->getMsg();
	return ss.str();
}

std::string saber::LogFormatter::pLevel(std::shared_ptr<LogEvent> &event){
		std::stringstream ss;
		LogLevel::Level level = event->getLevel();
		switch(level){
#define XX(level,str) case level:\
				ss<<#str;\
				break;

				XX(0,UNKNOWN)
				XX(1,DEBUG)
				XX(2,INFO)
				XX(3,WARN)
				XX(4,ERROR)
				XX(5,FATAL)
#undef XX
				default:
				ss<<"UNKNOWN";
				break;
		}
	return ss.str();
}

std::string saber::LogFormatter::pElapse(std::shared_ptr<LogEvent> &event){
		std::stringstream ss;
		ss<<event->getElapse();
	return ss.str();
}

std::string saber::LogFormatter::pLogName(std::shared_ptr<LogEvent> &event,std::shared_ptr<Logger> &logger){
		std::stringstream ss;
		ss<<logger->getName();
	return ss.str();
}

std::string saber::LogFormatter::pthreadId(std::shared_ptr<LogEvent> &event){
		std::stringstream ss;
		ss<<event->getThreadId();
	return ss.str();
}

std::string saber::LogFormatter::pNewLine(std::shared_ptr<LogEvent> &event){
	return "\n";
}

std::string saber::LogFormatter::pTime(std::shared_ptr<LogEvent> &event,std::string& fmt){
	if(fmt.empty()){
		fmt="%Y-%m-%d %H:%M:%S";
	}
	struct tm* ptm;
	time_t cur_time = event->getTime();
	//time_t cur_time;
	//time(&cur_time);
	ptm=localtime(&cur_time);
	char buf[64];
	strftime(buf,sizeof(buf),fmt.c_str(),ptm);
	return std::string(buf,buf+strlen(buf));
}

std::string saber::LogFormatter::pFileName(std::shared_ptr<LogEvent> &event){
	std::stringstream ss;
	ss<<event->getFile();
	return ss.str();
}

std::string saber::LogFormatter::pLine(std::shared_ptr<LogEvent> &event){
	std::stringstream ss;
	ss<<event->getLine();
	return ss.str();
}

std::string saber::LogFormatter::pTab(std::shared_ptr<LogEvent> &event){
	return "\t";
}

std::string saber::LogFormatter::pFiberId(std::shared_ptr<LogEvent> &event){
	std::stringstream ss;
	ss<<event->getFiberId();
	return ss.str();
}

std::string saber::LogFormatter::pThreadName(std::shared_ptr<LogEvent> &event){
	std::stringstream ss;
	ss<<event->getThreadName();
	return ss.str();
}

/**
 *@brief class LogAppender,StdOutAppender,FileAppender functions
 */

	
void saber::StdOutAppender::log(std::shared_ptr<Logger> &logger,LogLevel::Level level,LogEvent::ptr &event){
	if(level>=m_level){
			std::cout<<m_formatter->format(logger,event);
	}
}

saber::FileAppender::FileAppender(LogLevel::Level level,LogFormatter::ptr formatter,std::string file):LogAppender(level,formatter),m_file(file){
	int last_pos=0;
	for(int i=m_file.size()-1;i>=0;--i){
		if(m_file[i]=='/'){ 
			last_pos=i;
			break;
		}
	}
	std::string dir=m_file.substr(0,last_pos+1);
	std::string filename=m_file.substr(last_pos+1);
    saber::Mkdirs(dir);
    saber::Creat(m_file);

}


saber::FileAppender::FileAppender(std::string file):m_file(file){
	int last_pos=0;
	for(int i=m_file.size()-1;i>=0;--i){
		if(m_file[i]=='/'){ 
			last_pos=i;
			break;
		}
	}
	std::string dir=m_file.substr(0,last_pos+1);
	std::string filename=m_file.substr(last_pos+1);
    saber::Mkdirs(dir);
    saber::Creat(m_file);
}


void saber::FileAppender::log(std::shared_ptr<Logger> &logger,LogLevel::Level level, LogEvent::ptr &event){
	if(level>=m_level){
		if(m_os.is_open()){
			m_os.close();
			m_os.open(m_file,std::ios::app);
		}
		m_os.open(m_file,std::ios::app);
		if(!m_os){
			std::cout<<"<<error>> file open error";
			exit(0);
		}
		std::string tmp=m_formatter->format(logger,event);
		m_os<<tmp;
		m_os.close();
	}
}
/**
 *@brief class Logger functions
 */

void saber::Logger::delAppender(){
	if(!m_appenders.empty()){
		m_appenders.pop_back();
	}
}

void saber::Logger::clearAppender(){
	if(!m_appenders.empty()){
		m_appenders.clear();
	}
}

void saber::Logger::log(LogLevel::Level level,LogEvent::ptr &event){
	if(level>=m_level){			
		auto self=std::shared_ptr<Logger>(this); 
		for(auto item:m_appenders){
			item->log(self,level,event);
		}
	}
}

void saber::Logger::debug(LogEvent::ptr &event){
	if(LogLevel::DEBUG>=m_level){
			log(LogLevel::DEBUG,event);
	}
}

void saber::Logger::info(LogEvent::ptr &event){
	if(LogLevel::INFO>=m_level){
			log(LogLevel::INFO,event);
	}
}

void saber::Logger::warn(LogEvent::ptr &event){
	if(LogLevel::WARN>=m_level){
			log(LogLevel::WARN,event);
	}

}

void saber::Logger::error(LogEvent::ptr &event){
	if(LogLevel::ERROR>=m_level){
			log(LogLevel::ERROR,event);
	}
}

void saber::Logger::fatal(LogEvent::ptr &event){
	if(LogLevel::FATAL>=m_level){
			log(LogLevel::FATAL,event);
	}
}




