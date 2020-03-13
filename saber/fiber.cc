#include"fiber.h"
#include<atomic>
#include"config.h"
#include"marco.h"
#include"scheduler.h"
#include"log.h"
namespace saber{
static Logger::ptr g_logger=LOG_NEW("system");
static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};
static thread_local Fiber* t_fiber=nullptr;
//main fiber
static thread_local Fiber::ptr t_threadFiber=nullptr;
static ConfigVar<uint32_t>::ptr g_fiber_stack_size=Config::lookUp<uint32_t>("fiber.statck_size",1024*1024,"fiber stack size");
class MallocStackAllocator{
    public:
        static void* Alloc(size_t size){
            return malloc(size);
        }

        static void Dealloc(void* ptr,size_t size){
            free(ptr);
        }
    private:
};
typedef MallocStackAllocator StackAlloc ;
/*************************************************************************
 *Class Fiber
 ************************************************************************/
Fiber::Fiber(){
    m_state=EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)){
        ASSERT2(false,"getcontext");
    }
    ++s_fiber_count;
    LOG_DEBUG(g_logger)<<"Fiber::Fiber() id="<<this->getId();
}

Fiber::ptr Fiber::GetThis(){
    if(t_fiber){
        return t_fiber->shared_from_this();
    }
    Fiber::ptr main_fiber(new Fiber());
    ASSERT(t_fiber==main_fiber.get());
    t_threadFiber=main_fiber;
    return t_fiber->shared_from_this();
}

void Fiber::SetThis(Fiber* ptr){
    t_fiber=ptr;
}

void Fiber::YeildToReady(){
    Fiber::ptr cur=GetThis();
    cur->m_state=READY;
    cur->swapOut();
}

void Fiber::YeildToHold(){
    Fiber::ptr cur=GetThis();
    cur->m_state=HOLD;
    cur->swapOut();
}

uint64_t Fiber::TotalFibers(){
    return s_fiber_count;
}

void Fiber::MainFunc(){
    Fiber::ptr cur=GetThis();
    ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb=nullptr;
        cur->m_state=TERM;
    }catch(std::exception &e){
        cur->m_state=EXCEPT;
        LOG_ERROR(g_logger)<<"Fiber Except: "<<e.what();
    }catch(...){
         cur->m_state=EXCEPT;
        LOG_ERROR(g_logger)<<"Fiber Except: ";
    }
    auto raw_ptr=cur.get();
    cur.reset();
    raw_ptr->swapOut();
    ASSERT2(false,"never reach");
}

void Fiber::CallerMainFunc(){
    Fiber::ptr cur=GetThis();
    ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb=nullptr;
        cur->m_state=TERM;
    }catch(std::exception &e){
        cur->m_state=EXCEPT;
        LOG_ERROR(g_logger)<<"Fiber Except: "<<e.what();
    }catch(...){
         cur->m_state=EXCEPT;
        LOG_ERROR(g_logger)<<"Fiber Except: ";
    }
    auto raw_ptr=cur.get();
    cur.reset();
    raw_ptr->back();
    ASSERT2(false,"never reach");

}

uint64_t Fiber::GetFiberId(){
    if(t_fiber){
        return t_fiber->getId();
    }
    return 0;
}

Fiber::Fiber(std::function<void()> cb,size_t stack_size,bool use_caller):
    m_id(++s_fiber_id),
    m_cb(cb){
    
    ++s_fiber_count;
    m_stacksize = stack_size ? stack_size:g_fiber_stack_size->getValue();
    m_stack=StackAlloc::Alloc(m_stacksize);
    if(getcontext(&m_ctx)){
        ASSERT2(false,"getcontext error");
    }
    m_ctx.uc_link=nullptr;
    m_ctx.uc_stack.ss_sp=m_stack;
    m_ctx.uc_stack.ss_size=m_stacksize;
    m_ctx.uc_stack.ss_flags=0;
    if(!use_caller){
        makecontext(&m_ctx,&Fiber::MainFunc,0);
    }else{
        makecontext(&m_ctx,&Fiber::CallerMainFunc,0);
    }
    LOG_DEBUG(g_logger)<<"Fiber::Fiber() id="<<this->getId();
}

Fiber::~Fiber(){
    --s_fiber_count;
    if(m_stack){
        ASSERT(m_state==TERM||
                m_state==INIT||m_state==EXCEPT);
       StackAlloc::Dealloc(m_stack,m_stacksize);
    }else{
        //main fiber
        ASSERT(!m_cb);
        ASSERT(m_state==EXEC);
        Fiber* cur=t_fiber;
        if(cur==this){
            SetThis(nullptr);
        }
    }
    LOG_DEBUG(g_logger)<<"Fiber::~Fiber() id="<<m_id;
}

void Fiber::reset(std::function<void()> cb){
    ASSERT(m_stack);
    ASSERT(m_state==TERM||m_state==INIT||m_state==EXCEPT);
    m_cb=cb;
    if(getcontext(&m_ctx)){
        ASSERT2(false,"getcontext error");
    }
    m_ctx.uc_link=nullptr;
    m_ctx.uc_stack.ss_sp=m_stack;
    m_ctx.uc_stack.ss_size=m_stacksize;
    m_ctx.uc_stack.ss_flags=0;
    makecontext(&m_ctx,&Fiber::MainFunc,0);
    m_state=INIT;
}

void Fiber::call(){
    SetThis(this);
    m_state=EXEC;
   if(swapcontext(&t_threadFiber->m_ctx,&m_ctx)){
        ASSERT2(false,"swapcontext");
   }
}

void Fiber::back(){
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx,&t_threadFiber->m_ctx)){
        ASSERT2(false,"swapcontext error");
    }
}

void Fiber::swapIn(){
    SetThis(this);
    ASSERT(m_state!=EXEC);
    m_state=EXEC;
    if(swapcontext(&Scheduler::GetMainFiber()->m_ctx,&m_ctx)){
        ASSERT2(false,"swapcontext error");
    }
}

void Fiber::swapOut(){
    SetThis(Scheduler::GetMainFiber());
    if(swapcontext(&m_ctx,&Scheduler::GetMainFiber()->m_ctx)){
        ASSERT2(false,"swapcontext error");
    }
}

};
