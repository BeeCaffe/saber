#include"utils.h"
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

pid_t saber::GetPid(){
	pid_t pid=getpid();
	return pid;
}

uint32_t saber::GetElapse(){
	uint32_t ans=0;
	return ans;
}

uint32_t saber::GetFiberId(){
	uint32_t ans=0;
	return ans;
}

















