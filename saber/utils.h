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
	void Mkdir(std::string &file);

	void Mkdirs(std::string &file);
	
	void Creat(std::string &file);

	/**
	 *@brief thread related function
	 */
	
	pid_t GetPid();

	uint32_t GetElapse();

	uint32_t GetFiberId();

};
#endif
