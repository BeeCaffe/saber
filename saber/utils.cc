#include"utils.h"
#include"log.h"
#include<sys/time.h>

saber::Logger::ptr g_logger=FIND_LOG("system");
/**
 *@brief file related functions
 */
void saber::Mkdir(std::string &file){
	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char* tmp = file.c_str();

	if(access(tmp,F_OK)!=0){
		mkdir(tmp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	if(access(tmp,F_OK)!=0) saber::Mkdirs(file);
}

void saber::Mkdirs(std::string &file){
	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char*  tmp=file.c_str();
	if(access(tmp,F_OK)!=0){
		mkdir(tmp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}	
}

void saber::Creat(std::string &file){

	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char* tmp=file.c_str();
	if(access(tmp,F_OK)!=0){
		creat(tmp,0755);
	}
}

/**
 *@brief thread related functions
 */

pid_t saber::GetThreadId(){
	pid_t pid=getpid();
	return pid;
}

uint32_t saber::GetElapse(){
	uint32_t ans=0;
	return ans;
}

uint64_t saber::GetFiberId(){
	return saber::Fiber::GetFiberId();
}

void saber::BackTrace(std::vector<std::string>& bt,int size,int skip=2){
	void** array=(void**)malloc((sizeof(void)*size));
	size_t s=::backtrace(array,size);

	char** strings=backtrace_symbols(array,s);
	if(strings==NULL){
		LOG_ERROR(g_logger)<<"backtrace_symbols error";	
		return;
	}
	for(size_t i=skip;i<s;++i){
		bt.push_back(strings[i]);
	}
	free(strings);
	free(array);
}

std::string saber::BackTraceToString(int size,int skip=2,const std::string& prefix){
	std::vector<std::string> bt;
	BackTrace(bt,size,skip);
	std::stringstream ss;
	for(size_t i=0;i<bt.size();++i){
		ss<<prefix<<bt[i]<<std::endl;
	}
	return ss.str();
}

uint64_t saber::GetCurrentMS(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000ul+tv.tv_usec/1000;
}

uint64_t saber::GetCurrentUS(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000*1000ul+tv.tv_usec;

}














