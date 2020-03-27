#ifndef __SABER_UTILS_H
#define __SABER_UTILS_H
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<iostream>
#include<fcntl.h>
#include<vector>
#include<execinfo.h>
#include<sstream>
#include"fiber.h"
namespace saber{
	/**
	 *@brief file ralated functions
	 */
	void Mkdir(std::string &file);

	void Mkdirs(std::string &file);
	
	void Creat(std::string &file);

	/**
	 *@brief thread related function
	 */
	
	pid_t GetThreadId();

	uint32_t GetElapse();

	uint64_t GetFiberId();
 
	
	void BackTrace(std::vector<std::string>& bt,int size,int skip);
	std::string BackTraceToString(int size,int skip,const std::string& prefix="	");
    //time ms
    uint64_t GetCurrentMS();
    uint64_t GetCurrentUS();
};
#endif
