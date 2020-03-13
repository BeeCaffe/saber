#ifndef __MARCO_H
#define __MARCO_H
#include<string.h>
#include<assert.h>
#include"utils.h"

#define ASSERT(x) \
		if(!(x)){ \
			LOG_ERROR(LOG_ROOT)<<" ASSERTION: "#x \
							   <<"\nbacktrace:\n" \
							   <<saber::BackTraceToString(100,2,"    "); \
			assert(x); \
		}

#define ASSERT2(x,w)\
	if(!(x)){ \
			LOG_ERROR(LOG_ROOT)<<" ASSERTION: "#x \
							   <<"\n"<<w \
							   <<"\nbacktrace:\n" \
							   <<saber::BackTraceToString(100,2,"    "); \
			assert(x); \
	}



#endif
