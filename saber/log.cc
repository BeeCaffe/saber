#include"log.h"
#include"config.h"
/*************************************************************************
 *@brief class LogLevel functions
 ************************************************************************/
std::string saber::LogLevel::toString(LogLevel::Level level){
	std::string str;
	switch(level){
		case LogLevel::LogLevel::DEBUG:
			str="DEBUG";
			break;
		case LogLevel::LogLevel::INFO:
			str="INFO";
			break;
		case LogLevel::LogLevel::WARN:
			str="WARN";
			break;
		case LogLevel::LogLevel::ERROR:
			str="ERROR";
			break;
		case LogLevel::LogLevel::FATAL:
			str="FATAL";
			break;
		default:
			str="UNKNOWN";
			break;
	}
	return str;
}

typename saber::LogLevel::Level saber::LogLevel::fromString(const std::string& str){
	if(str=="DEBUG"||str=="debug") return LogLevel::Level::DEBUG;
	if(str=="INFO"||str=="info") return LogLevel::Level::INFO;
	if(str=="ERROR"||str=="error") return LogLevel::Level::ERROR;
	if(str=="FATAL"||str=="fatal") return LogLevel::Level::FATAL;
	if(str=="WARN"||str=="warn") return LogLevel::Level::WARN;
	if(str=="UNKNOWN"||str=="unknown") return LogLevel::Level::UNKNOWN;
}
/************************************************************************* *@brief class LogEvent
 *************************************************************************/
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
                             m_fiberId(fiber_id),
							 m_elapse(elapse),
							 m_logger(logger),
						     m_threadName(thread_name){}
/*************************************************************************
 *@brief class LogAppender
 *************************************************************************/
////print log information to console
void saber::StdOutAppender::log(LogLevel::Level level,LogEvent::ptr event){
	if(level>=m_level){
		std::cout<<m_formatter->format(event);
	}
}

saber::FileAppender::FileAppender(LogLevel::Level level,std::string file):m_file(file),m_level(level){}

saber::FileAppender::FileAppender(std::string file):m_file(file){}

void saber::FileAppender::reopen(){
	
	MutexType::Lock lock(m_mutex);	
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
	
		MutexType::Lock lock(m_mutex);	
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

std::string saber::FileAppender::toYamlString(){
		MutexType::Lock lock(m_mutex);
		YAML::Node node;
		node["type"]="FileAppender";
		node["file"] = m_file;
		node["level"]=LogLevel::toString(m_level);
		if(m_hasFormatter&&m_formatter){
			node["formatter"]=m_formatter->getPattern();
		}
		std::stringstream ss;
		ss<<node;
		return ss.str();
}

std::string saber::StdOutAppender::toYamlString(){
		MutexType::Lock lock(m_mutex);
		YAML::Node node;
		node["type"] = "StdOutAppender";
		node["level"] = LogLevel::toString(m_level);
		if(m_hasFormatter&&m_formatter){
			node["formatter"]=m_formatter->getPattern();
		}
		std::stringstream ss;
		ss<<node;
		return ss.str();
}

/*************************************************************************
 *@brief class LogFormatter
 ************************************************************************/

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

void saber::LogAppender::setFormatter(const std::string& pattern){
	MutexType::Lock lock(m_mutex);
	m_formatter.reset(new LogFormatter(pattern));
	if(m_formatter){
		m_hasFormatter=true;
	}else{
		m_hasFormatter=false;
	}
}

void saber::LogAppender::setFormatter(const std::shared_ptr<LogFormatter>& fmt){
	MutexType::Lock lock(m_mutex);
	m_formatter=fmt;
	if(m_formatter){
		m_hasFormatter=true;
	}else{
		m_hasFormatter=false;
	}
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

/*************************************************************************
 *@brief class Logger
 ************************************************************************/
void saber::Logger::log(LogEvent::ptr event,LogLevel::Level level){
	if(level>=m_level){
		if(this==nullptr) std::cout<<"<<fatal>> logger shouoth not be nullptr"<<std::endl;

		MutexType::Lock lock(m_mutex);	
		for(int i=0;i<m_appenders.size();++i){
			m_appenders[i]->setFormatter(m_formatter);
			m_appenders[i]->log(level,event);
		}
	}
}

void saber::Logger::addAppender(LogAppender::ptr appender){
	MutexType::Lock lock(m_mutex);
	if(!appender->getFormatter()){
		MutexType::Lock ll(appender->m_mutex);
		appender->m_formatter=m_formatter;
	}
	m_appenders.push_back(appender);
}

void saber::Logger::delAppender(LogAppender::ptr appender){
	MutexType::Lock lock(m_mutex);	
	for(auto it=m_appenders.begin();
			 it!=m_appenders.end();
			 ++it){
		if(*it==appender){
			m_appenders.erase(it);
			break;
		}
	}
}

std::string saber::Logger::toYamlString(){
	MutexType::Lock lock(m_mutex);	
	YAML::Node node;
	node["name"]=m_logName;
	node["level"]=LogLevel::toString(m_level);
	if(m_formatter){
		node["formatter"]=m_formatter->getPattern();
	}
	for(auto& i:m_appenders){
		node["appenders"].push_back(YAML::Load(i->toYamlString()));
	}
	std::stringstream ss;
	ss<<node;
	return ss.str();
}

void saber::Logger::clearAppenders(){
	
	MutexType::Lock lock(m_mutex);	
	m_appenders.clear();
}

void saber::Logger::setFormatter(LogFormatter::ptr formatter){
	
	MutexType::Lock lock(m_mutex);	
	m_formatter=formatter;
	for(auto& i:m_appenders){
		MutexType::Lock ll(i->m_mutex);	
		if(!i->m_hasFormatter){
			i->m_formatter=formatter;
			i->m_hasFormatter=true;
		}
	}
}

void saber::Logger::setFormatter(const std::string& fmt){
	LogFormatter::ptr new_fmt(new saber::LogFormatter(fmt));
	setFormatter(new_fmt);
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

/*************************************************************************
 *brief class LogManager
 ************************************************************************/
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
	m_loggers["root"]=root_logger;
	return root_logger;
}

saber::Logger::ptr saber::LogManager::getLogger(const std::string& log_name){
	
	MutexType::Lock lock(m_mutex);	
	if(m_loggers.find(log_name)!=m_loggers.end()) return m_loggers[log_name];
	else {
		addLogger(log_name);
		return m_loggers[log_name];
	} 
}

std::string saber::LogManager::toYamlString(){
	
	MutexType::Lock lock(m_mutex);	
	YAML::Node	node;
	for(auto &i:m_loggers){
		node.push_back(YAML::Load(i.second->toYamlString()));
	}
	std::stringstream ss;
	ss<<node;
	return ss.str();
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

struct LogAppenderDefine{
	int type=0;//1:file 2:stdout
	saber::LogLevel::Level level=saber::LogLevel::Level::UNKNOWN;
	std::string formatter;
	std::string file;

	bool operator==(const LogAppenderDefine& oth) const {
		return  type==oth.type
				&&level==oth.level 
				&& formatter==oth.formatter 
				&& file==oth.file;
	}
};

struct LogDefine{
		saber::LogLevel::Level level=saber::LogLevel::Level::UNKNOWN;
		std::vector<LogAppenderDefine> appenders;
		std::string formatter;
		std::string name="";

		bool operator==(const LogDefine& oth)const{
			return level==oth.level 
					&& appenders==oth.appenders 
					&& formatter==oth.formatter 
					&& name==oth.name;
		}

		bool operator<(const LogDefine& oth) const{
			return name<oth.name;
		}
};

template<>
class saber::LexicalCast<std::string,std::set<LogDefine>>{
public:
	std::set<LogDefine> operator()(const std::string& v){
			YAML::Node node=YAML::Load(v);
			std::set<LogDefine> S;
			std::stringstream ss;
			for(size_t i=0;i<node.size();++i){
				const auto n=node[i];
				if(!n["name"].IsDefined()){
					std::cout<<"log configure error: name is null, "<<n<<std::endl;
					continue;
				}
				LogDefine ld;
				ld.name = n["name"].as<std::string>();
				ld.level = saber::LogLevel::fromString(n["level"].IsDefined() ? n["level"].as<std::string>():"");
				if(n["formatter"].IsDefined()){
					ld.formatter = n["formatter"].as<std::string>();
				}
				if(n["appenders"].IsDefined()){
					for(size_t j=0;j<n["appenders"].size();++j){
						auto a=n["appenders"][j];
						if(!a["type"].IsDefined()){
							std::cout<<"log configure error: appender type is null, "<<a<<std::endl;
							continue;
						}
						std::string type=a["type"].as<std::string>();
						LogAppenderDefine lad;
						if(type=="FileAppender"){
							lad.type=1;
							if(!a["file"].IsDefined()){
								std::cout<<"log configure error: file is null, "<<a<<std::endl;	
								continue;

							}
							lad.file=a["file"].as<std::string>();
							if(a["formatter"].IsDefined()){
								lad.formatter = a["formatter"].as<std::string>();
							}
						}else if(type=="StdOutAppender"){
							lad.type=2;
						}else{
							std::cout<<"log configure error: appender type is invalid, "<<a<<std::endl;
							continue;
						}
						ld.appenders.push_back(lad);
					}
				}
				S.insert(ld);
			}
			return S;
}
};

template<>
class saber::LexicalCast<std::set<LogDefine>,std::string>{
public:
		std::string operator()(const std::set<LogDefine>& s){
			YAML::Node node;
			std::stringstream ss;
			for(auto& i:s){
				YAML::Node n;
				n["name"]=i.name;
				n["level"]=LogLevel::toString(i.level);
				if(i.formatter.empty()){
					n["level"]=i.formatter;
				}
				for(auto& a: i.appenders){
					YAML::Node na;
					if(a.type==1){
						na["type"]="FileAppender";
						na["file"]=a.file;
					}else if(a.type==2){
						na["type"]="StdOutAppender";
					}
					na["level"]=saber::LogLevel::toString(a.level);
					if(a.formatter.empty()){
						na["formatter"]=a.formatter;
					}
					na["appenders"].push_back(na);
				}
				node.push_back(n);
			}
			ss<<node;
			return ss.str();
		}
};

saber::ConfigVar<std::set<LogDefine>>::ptr g_log_defines=
	saber::Config::lookUp("logs",std::set<LogDefine>(),"logs config");

struct LogIniter{
	LogIniter(){

			std::cout<<"LogIniter executed"<<std::endl;

		g_log_defines->addListener(
						[](const std::set<LogDefine>& old_value, 
						   const std::set<LogDefine>& new_value){
			std::cout<<"on_logger_conf_changed"<<std::endl;
			saber::Logger::ptr logger;
			for(auto& i:new_value){

				auto it=old_value.find(i);
				if(it == old_value.end()){
					//add new logger
					logger=LOG_NEW(i.name);
				}else{
					if(i==*it){
						//modify logger
						logger=LOG_NEW(i.name);
					}else{	
						continue;	
					}
				}
				logger->setLevel(i.level);
				if(!i.formatter.empty()){
					logger->setFormatter(i.formatter);
				}

				logger->clearAppenders();
				for(auto & a:i.appenders){
					saber::LogAppender::ptr ap;
					if(a.type==1){
						ap.reset(new saber::FileAppender(a.file));
					}else if(a.type==2){
						ap.reset(new saber::StdOutAppender());
					}
				
				ap->setLevel(a.level);
				if(!a.formatter.empty()){
						saber::LogFormatter::ptr fmt(new saber::LogFormatter(a.formatter));
						ap->setFormatter(fmt);
					}
				logger->addAppender(ap);
				}

				LOG_INFO(LOG_ROOT)<<"b2";
			}

			LOG_INFO(LOG_ROOT)<<"b3";
			//delete logger
			for(auto& i:old_value){
				auto it=new_value.find(i);
				if(it==new_value.end()){
					auto logger=LOG_NEW(i.name);
					logger->setLevel(saber::LogLevel::Level(100));
					logger->clearAppenders();
				}
			}
			LOG_INFO(LOG_ROOT)<<"b4";
		});
	} 
};

static LogIniter __log_init;

void saber::LogManager::init(){
	
}


