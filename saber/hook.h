#ifndef __HOOK_H
#define __HOOK_H
#include<unistd.h>
#include"fiber.h"
#include"iomanager.h"
#include<dlfcn.h>
#include<time.h>
namespace saber{
    bool is_hook_enable();
    void set_hook_enable(bool flag);
};
extern "C"{

    typedef unsigned int (*sleep_fun)(unsigned int seconds);
    extern sleep_fun sleep_f;

    typedef int (*usleep_fun)(useconds_t usec);
    extern usleep_fun usleep_f;

    int nanosleep();

}
#endif
