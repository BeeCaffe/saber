#include"hook.h"
namespace saber{
static thread_local bool t_hook_enable = false;

#define  HOOK_FUN(XX) \
        XX(sleep) \
        XX(usleep)

void hook_init(){
    static bool is_inited = false;
    if(is_inited){
        return;
    }
#define XX(name) name ## _f = (name ## _fun)dlsym(RTLD_NEXT,#name);\
    HOOK_FUN(XX);
#undef 
}

struct _HookIniter{
    _HookIniter(){
        hook_init();
    }
};

static _HookIniter s_hook_init;


bool is_hook_enable(){
    return t_hook_enable;
}

void set_hook_enable(bool flag){
    t_hook_enable=flag;
}
   
};

extern "C"{
    #define XX(name) name ## _fun name ##_f =nullptr;
        HOOK_FUN(XX)
    #undef XX

unsigned int sleep(unsigned int seconds){
    if(!saber::t_hook_enable){
        return sleep_f(seconds);
    }
    saber::Fiber::ptr fiber = saber::Fiber::GetThis();
    saber::IOManager* iom = GetThis();
    iom->addTimer(seconds*1000,std::bind(&saber::IOManager::schedule,iom,fiber));
    saber::Fiber::YeildToHold();
}

int usleep_fun(useconds_t usec){
    if(!saber::t_hook_enable){
        return usleep_f(seconds);
    }
    saber::Fiber::ptr fiber = saber::Fiber::GetThis();
    saber::IOManager* iom = GetThis();
    iom->addTimer(usec / 1000,std::bind(&saber::IOManager::schedule,iom,fiber));
    saber::Fiber::YeildToHold();
}

}

