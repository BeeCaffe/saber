#include"utils.h"
/**
 *@brief file related functions
 */
void saber::s_mkdir(std::string &file){
	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char* tmp = file.c_str();
	if(access(tmp,F_OK)!=0){
		mkdir(tmp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	if(access(tmp,F_OK)!=0) saber::s_mkdirs(file);
}

void saber::s_mkdirs(std::string &file){
	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char*  tmp=file.c_str();
	if(access(tmp,F_OK)!=0){
		mkdir(tmp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}	
}

void saber::s_creat(std::string &file){

	if(file.empty()) std::cout<<"<<file error>> file can not be null";
	const char* tmp=file.c_str();
	if(access(tmp,F_OK)!=0){
		creat(tmp,0755);
	}
}

/**
 *@brief thread related functions
 */

pid_t saber::s_getPid(){
	pid_t pid=getpid();
	return pid;
}

uint32_t saber::s_getElapse(){
	uint32_t ans=0;
	return ans;
}

uint32_t saber::s_getFiberId(){
	uint32_t ans=0;
	return ans;
}

















