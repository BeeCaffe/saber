#ifndef __FIBER_H
#define __FIBER_H
#include<functional>
#include<ucontext.h>
#include<memory>
#include"thread.h"
namespace saber{
class Fiber;
class Scheduler;
/*************************************************************************
 *Class Fiber
 *************************************************************************/
class Fiber:public std::enable_shared_from_this<Fiber>{
    friend class Scheduler;
    public:

        typedef std::shared_ptr<Fiber> ptr;
        enum State{
            INIT=0,
            HOLD=1,
            EXEC=2,
            TERM=3,
            READY=4,
            EXCEPT=5
        };
        static Fiber::ptr GetThis();
        static void SetThis(Fiber* ptr);
        static void YeildToReady();
        static void YeildToHold();
        static uint64_t TotalFibers();
        static void MainFunc();
        static void CallerMainFunc();
        static uint64_t GetFiberId();
    public:
        Fiber(std::function<void()> cb,size_t stack_size=0,bool use_caller=false);
        ~Fiber();
        void reset(std::function<void()> cb);
        void swapIn();
        void swapOut();
        void call();
        void back();
        uint64_t getId() const {
            return m_id;
        }
        const State getState() const {return m_state;}
    private:
        Fiber();
    private:
        ucontext_t m_ctx;
        void *m_stack=nullptr;
        uint64_t m_stacksize=0;
        std::function<void()> m_cb;
        uint64_t m_id=0;
        State m_state=INIT;
};
};
 
#endif
