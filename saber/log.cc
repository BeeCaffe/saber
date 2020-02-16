#include"log.h"
/**
 *@brief class LogEvent
 */
////constructor
saber::LogEvent::LogEvent(LogLevel::Level level,
							 uint32_t line,
							 const char* file,
							 uint32_t thread_id,
							 uint32_t fiber_id,
							 uint64_t time,
							 uint32_t elapse,
							 std::shared_ptr<Logger> logger,
							 std::string thread_name):
							 m_level(level),
							 m_line(line),
							 m_file(file),
							 m_threadId(thread_id),
							 m_time(time),
							 m_elapse(elapse),
							 m_logger(logger),
						     m_threadName(thread_name){}
/**
 *@brief class LogAppender
 */
/// set formatter of log appender
void saber::LogAppender::setFormatter(std::shared_ptr<LogFormatter> format){m_formatter=format; }

////print log information to console
void saber::StdOutAppender::log(LogLevel::Level level,LogEvent::ptr event){
	if(level>=m_level){
		std::cout<<m_formatter->format(event);
	}
}
saber::FileAppender::FileAppender(LogLevel::Level level,std::string file):m_file(file),m_level(level){}
saber::FileAppender::FileAppender(std::string file):m_file(file){}
void saber::FileAppender::reopen(){
	if(m_os.is_open()){
		m_os.close();
		m_os.open(m_file,std::ios::app);
	}
}
void saber::FileAppender::makeDirs(){
	int last_pos=0;
	for(int i=m_file.size()-1;i>=0;--i){
		if(m_file[i]=='/'){ 
			last_pos=i;break;
		}
	}
	std::string dir=m_file.substr(0,last_pos+1);
	std::string filename=m_file.substr(last_pos+1);
	saber::Mkdirs(dir);
	saber::Creat(m_file);
}
void saber::FileAppender::log(LogLevel::Level level, LogEvent::ptr event) {
		if(m_os.is_open()) reopen();
		if(!m_os.is_open()){
			makeDirs();
			m_os.open(m_file,std::ios::app);
		}
		if(level>=m_level){
			m_os<<m_formatter->format(event);
		}
		m_os.close();
}


/**
 *@brief class LogFormatter
 */

std::string saber::LogFormatter::timeString(LogEvent::ptr event ,std::string pattern){
	std::stringstream ss;
	if(pattern.empty()) pattern="%y-%m-%d %H:%M:%S";
	struct tm* ptm;
	time_t time=event->getTime();
	ptm=localtime(&time);
	for(int i=0;i<pattern.size();++i){
		switch(pattern[i]){
			case 'y': ss<<(1900+ptm->tm_year);break;
			case 'Y': ss<<(1900+ptm->tm_year);break;
			case 'm': ss<<(1+ptm->tm_mon);break;
			case 'd': ss<<ptm->tm_mday;break;
			case 'H': ss<<ptm->tm_hour;break;
			case 'M': ss<<ptm->tm_min;break;
			case 'S': ss<<ptm->tm_sec;break;
			case 's': ss<<ptm->tm_sec;break;
			case '-': ss<<"-";break;
			case '\\': ss<<"\\";break;
			case ':': ss<<":";break;
			case ' ': ss<<" ";break;
			case '%': break;
			default: std::cout<<"<<error>> timeString()-time pattern error"<<"error char is :"<<pattern[i]<<std::endl;
		}
	}
	return ss.str();
}
////get event time
std::string saber::LogFormatter::msgString(LogEvent::ptr event){
	return event->getMsg().str();
}
////get event elapse
std::string saber::LogFormatter::elapseString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getElapse();
	return ss.str();
}
////get log name
std::string saber::LogFormatter::logNameString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getLogger()->getName();
	return ss.str();

}
////get thread id
std::string saber::LogFormatter::threadIdString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getThreadId();
	return ss.str();
}
////new line
std::string saber::LogFormatter::newLineString(LogEvent::ptr event){
	return "\n";
}
////file name
std::string saber::LogFormatter::fileNameString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getFile();
	return ss.str();

}
////line
std::string saber::LogFormatter::lineString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getLine();
	return ss.str();
}
//// tab
std::string saber::LogFormatter::tabString(LogEvent::ptr event){
	return "\t";
}
//// fiber id
std::string saber::LogFormatter::fiberIdString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getFiberId();
	return ss.str();
}
//// thread name
std::string saber::LogFormatter::threadNameString(LogEvent::ptr event){
	std::stringstream ss;
	ss<<event->getThreadName();
	return ss.str();
}
//// log level
std::string saber::LogFormatter::levelString(LogEvent::ptr event){
	std::stringstream ss;
	switch(event->getLevel()){
			case LogLevel::LogLevel::DEBUG : ss<<"DEBUG";break;
			case LogLevel::LogLevel::INFO : ss<<"INFO";break;
			case LogLevel::LogLevel::WARN : ss<<"WARN";break;
			case LogLevel::LogLevel::ERROR : ss<<"ERROR";break;
			case LogLevel::LogLevel::FATAL : ss<<"FATAL";break;
			case LogLevel::LogLevel::UNKNOWN : ss<<"UNKNOWN";break;
	}
	return ss.str();
}
std::string saber::LogFormatter::format(LogEvent::ptr event){
	return parsePattern(event,m_pattern);
}
std::string saber::LogFormatter::parsePattern(LogEvent::ptr event,std::string &pattern){
	std::stringstream ss;
	for(int i=0;i<pattern.size();++i){
		if(pattern[i]=='%'){
			char fmt=pattern[i+1];
			if(fmt=='%'){		   //// %%
				ss<<"%";i++;continue;
			}else if(fmt=='d'){	   //// %d
				int j=i+2;
				if(pattern[i+2]!='{'){
					std::cout<<"<<error>> pattern format error 1 ";exit(0);
				}
				while(j<pattern.size()&&pattern[j]!='}') ++j;
				ss<<timeString(event,pattern.substr(i+3,j-i-3));
				i=j;
			}else{
				switch(fmt){
				case 'm':ss<<msgString(event);break;
				case 'p':ss<<levelString(event);break;
				case 'r':ss<<elapseString(event);break;
				case 'c':ss<<logNameString(event);break;
				case 't':ss<<threadIdString(event);break;
				case 'n':ss<<newLineString(event);break;
				case 'f':ss<<fileNameString(event);break;
				case 'l':ss<<lineString(event);break;
				case 'T':ss<<tabString(event);break;
				case 'F':ss<<fiberIdString(event);break;
				case 'N':ss<<threadNameString(event);break;
				default : std::cout<<"<<error>> pattern format error 2"<<"char is :"<<fmt<<std::endl;exit(0);break;
				}
				i++;
			}
		}else if(pattern[i]=='['){ //// [
			ss<<"[";
			int j=i;
			while(j<pattern.size()&&pattern[j]!=']') ++j;
			if(j==pattern.size()){ 
				std::cout<<"<<error>> pattern format error 3";exit(0);
			}
			std::string tmp(pattern.substr(i+1,j-i-1));
			ss<<parsePattern(event,tmp);
			ss<<"]";
			i=j;
		}else{ 					   ////others
			ss<<pattern[i];
		}
	}
	return ss.str();
}
/**
 *@brief class Logger
 */
void saber::Logger::log(LogEvent::ptr event,LogLevel::Level level){
	if(level>=m_level){
		if(this==nullptr) std::cout<<"<<fatal>> logger should not be nullptr"<<std::endl;
		for(int i=0;i<m_appenders.size();++i){
			m_appenders[i]->setFormatter(m_formatter);
			m_appenders[i]->log(level,event);
		}
	}
}
void saber::Logger::addAppender(LogAppender::ptr appender){
	m_appenders.push_back(appender);
}
void saber::Logger::setFormatter(LogFormatter::ptr formatter){
	m_formatter=formatter;
}
void saber::Logger::debug(saber::LogEvent::ptr event){
	log(event,saber::LogLevel::Level::DEBUG);
}
void saber::Logger::info(LogEvent::ptr event){
	log(event,saber::LogLevel::Level::INFO);
}
void saber::Logger::warn(LogEvent::ptr event){
	log(event,saber::LogLevel::Level::WARN);
}
void saber::Logger::error(LogEvent::ptr event){
	log(event,saber::LogLevel::Level::ERROR);
}
void saber::Logger::fatal(LogEvent::ptr event){
	log(event,saber::LogLevel::Level::FATAL);
}
/**
 *brief class LogManager
 */
void saber::LogManager::initRoot(){
	root_logger.reset(new Logger("root"));
	LogFormatter::ptr fmt(new LogFormatter());
	StdOutAppender::ptr std_app(new StdOutAppender());
	FileAppender::ptr file_app(new FileAppender("../log/root.txt"));
	root_logger->setFormatter(fmt);
	root_logger->addAppender(std_app);
	root_logger->addAppender(file_app);
}

saber::Logger::ptr saber::LogManager::getRoot(){
	if(root_logger==nullptr) initRoot();
	return root_logger;
}

saber::Logger::ptr saber::LogManager::getLogger(std::string log_name){
	if(m_loggers.find(log_name)!=m_loggers.end()) return m_loggers[log_name];
	else {
		LOG_INFO(LOG_ROOT)<<log_name<<" is not exist, but a new log is built";
		addLogger(log_name);
		return m_loggers[log_name];
	} 
}

void saber::LogManager::addLogger(std::string log_name){
	Logger::ptr log(new Logger(log_name));
	LogFormatter::ptr fmt(new LogFormatter());
	StdOutAppender::ptr std_app(new StdOutAppender());
	std::string log_path="../log/"+log_name+".txt";
	FileAppender::ptr file_app(new FileAppender(log_path));
	log->setFormatter(fmt);
	log->addAppender(std_app);
	log->addAppender(file_app);
	m_loggers[log_name]=log;
}

