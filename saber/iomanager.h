#ifndef __IOMANAGER_H
#define __IOMANAGER_H
#include"scheduler.h"
#include<memory>
namespace saber{
class IOManager:public Scheduler{
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;

    enum Event{
        NONE=0x0;
        READ=0x1;
        WRITE=0X2;
    };
private:

    struct FdContext{
        typedef Mutex MutexType;
        struct EventContext{
            Scheduler* scheduler=nullptr;   //The scheduler which is waitting for executing 
            Fiber::ptr fiber;       //The fiber of event
            std::function<void()> cb;   //The call back function of event
        };
        int fd=0;             //the handle of event connection
        EventContext& getContext(Event event);
        void resetContext(EventContext& ctx);
        void triggerEvent(Event event);
        EventContext read;  //read event
        EventContext write; //write event

        Event events = NONE;  //registed event 
        MutexType m_mutex;
    };

public:
    IOManager(size_t thread=1,bool use_caller=true,const std::string& name="");
    ~IOManager();
    //0 success, -1 error
    int addEvent(int fd,Event event,std::function<void()> cb=nullptr);
    bool delEvent(int fd,Event event);
    bool cancelEvent(int fd.Event event);

    bool cancelAll(int fd);
    static IOManager* GetThis();
    void contextResize(size_t sz);
protected:
    void tickle() override;
    bool stopping() override;
    void idle() override;
private:
    int m_epfd=0;
    int m_tickleFds[2];
    std::atomic<size_t> m_pendingEventCount={0};
    RWMutexType m_mutex;
    std::vector<FdContext*> m_fdContexts;

};
};
#endif
