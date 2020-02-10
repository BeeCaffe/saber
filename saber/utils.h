#ifndef __SABER_UTILS_H
#define __SABER_UTILS_H
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<iostream>
#include<fcntl.h>
namespace saber{
	/**
	 *@brief file ralated functions
	 */
	void s_mkdir(std::string &file);

	void s_mkdirs(std::string &file);
	
	void s_creat(std::string &file);

	/**
	 *@brief thread related function
	 */
	
	pid_t s_getPid();

	uint32_t s_getElapse();

	uint32_t s_getFiberId();

};
#endif
