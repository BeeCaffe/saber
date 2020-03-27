#include"iomanager.h"
#include"macro.h"
#include<unistd.h>
#include<sys/epoll.h>
#include"log.h"
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include"thread.h"
namespace saber{
static saber::Logger::ptr g_logger=LOG_NEW("system");
IOManager::IOManager(size_t thread,bool use_caller,const std::string& name):Scheduler(thread,use_caller,name){
    m_epfd=epoll_create(5000);
    ASSERT2(m_epfd>0,"epoll wait error");
    
    int rt=pipe(m_tickleFds);
    ASSERT2(rt!=-1,"pipe creat error");

    epoll_event event;
    memset(&event,0,sizeof(epoll_event));
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = m_tickleFds[0];
    rt = fcntl(m_tickleFds[0],F_SETFL,O_NONBLOCK);
    ASSERT(rt!=-1);
    //add events to epoll
    rt = epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_tickleFds[0],&event);
    ASSERT(rt!=-1);

    contextResize(64);
    start();
}

IOManager::~IOManager(){
    stop();
    close(m_epfd);
    close(m_tickleFds[0]);
    close(m_tickleFds[1]);

    for(size_t i=0;i<m_fdContexts.size();++i){
        if(m_fdContexts[i]){
            delete m_fdContexts[i];
        }
    }
}

int IOManager::addEvent(int fd,Event event,std::function<void()> cb){
    FdContext* fd_ctx=nullptr;
    RWMutexType::ReadLock lock(m_mutex);
    if(m_fdContexts.size()>fd){
        fd_ctx=m_fdContexts[fd];
        lock.unlock();
    }else{
        lock.unlock();
        RWMutexType::WriteLock lock2(m_mutex);
        contextResize(m_fdContexts.size()*1.5);
        fd_ctx=m_fdContexts[fd];
    }
    FdContext::MutexType::Lock lock3(fd_ctx->mutex);
    if(fd_ctx->events & event){//if fd_ctx->events == event
        LOG_ERROR(g_logger)<<"addEvent assert fd="<<fd
            <<"event="<<event
            <<"fd_ctx.event="<<fd_ctx->events;
        ASSERT(!(fd_ctx->events&event));
    }
    int op=fd_ctx->events ? EPOLL_CTL_MOD:EPOLL_CTL_ADD;
    epoll_event epevent;
    epevent.events=EPOLLET| fd_ctx->events | event;
    epevent.data.ptr=fd_ctx;

    int rt=epoll_ctl(m_epfd,op,fd,&epevent);
    if(rt){
        LOG_ERROR(g_logger)<<"epoll_ctl("<<m_epfd<<", "
            <<op<<","<<fd<<","<<epevent.events<<"):"
            <<rt<<" ("<<errno<<")"<<strerror(errno)<<")";
        return -1;
    }
     m_pendingEventCount++;
    fd_ctx->events=(Event)(fd_ctx->events|event);
    FdContext::EventContext& event_ctx=fd_ctx->getContext(event);
    ASSERT(!event_ctx.scheduler);
    ASSERT(!event_ctx.fiber);
    ASSERT(!event_ctx.cb);
    
    event_ctx.scheduler=Scheduler::GetThis();
    if(cb){
        event_ctx.cb.swap(cb);
    }else{
        event_ctx.fiber=Fiber::GetThis();
        ASSERT(event_ctx.fiber->getState()==Fiber::EXEC);
    }
    return 0;

}

void IOManager::contextResize(size_t sz){
    m_fdContexts.resize(sz);
    for(size_t i=0;i<m_fdContexts.size();++i){
        if(!m_fdContexts[i]){
            m_fdContexts[i]=new FdContext;
            m_fdContexts[i]->fd=i;
        }
    }
}

bool IOManager::delEvent(int fd,Event event){
    RWMutexType::ReadLock lock(m_mutex);
    if(m_fdContexts.size()<=fd){
        return false;
    }
    FdContext* fd_ctx=m_fdContexts[fd];
    lock.unlock();

    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if(!(fd_ctx->events)&event){
        return false;
    }
    Event new_event=(Event)(fd_ctx->events & ~event);
    
    int op=new_event ? EPOLL_CTL_MOD:EPOLL_CTL_DEL; 
    epoll_event epevent;
    epevent.events = EPOLLET|new_event;
    epevent.data.ptr = fd_ctx;

    int rt=epoll_ctl(m_epfd,op,fd,&epevent);
    if(rt){
        LOG_ERROR(g_logger)<<"addEvent assert fd="<<fd
            <<"event="<<event
            <<"fd_ctx.event="<<fd_ctx->events;
        ASSERT(!(fd_ctx->events&event));
        return false;
    }
    --m_pendingEventCount;
    fd_ctx->events=new_event;
    FdContext::EventContext& event_ctx=fd_ctx->getContext(event);
    fd_ctx->resetContext(event_ctx);
    return true;
}


void IOManager::FdContext::triggerEvent(IOManager::Event event){
    ASSERT(events & event);
    events=(Event)(events & ~event);
    EventContext& ctx=getContext(event);
    if(ctx.cb){
        ctx.scheduler->schedule(&ctx.cb);
    }else{
        ctx.scheduler->schedule(&ctx.fiber);
    }
    ctx.scheduler=nullptr;
    return;
}


IOManager::FdContext::EventContext& IOManager::FdContext::getContext(IOManager::Event event){
   switch(event){
        case IOManager::READ:
            return read;
        case IOManager::WRITE:
            return write;
        default:
            ASSERT2(false,"getContext");
   }
}

void  IOManager::FdContext::resetContext(IOManager::FdContext::EventContext& ctx){
    ctx.scheduler = nullptr;
    ctx.fiber.reset();
    ctx.cb = nullptr;
}

bool IOManager::cancelEvent(int fd,Event event){
    RWMutexType::ReadLock lock(m_mutex);
    if(m_fdContexts.size()<=fd){
        return false;
    }
    FdContext* fd_ctx=m_fdContexts[fd];
    lock.unlock();

    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if(!(fd_ctx->events)&event){
        return false;
    }
    Event new_event=(Event)(fd_ctx->events & ~event);
    
    int op=new_event ? EPOLL_CTL_MOD:EPOLL_CTL_DEL; 
    epoll_event epevent;
    epevent.events = EPOLLET|new_event;
    epevent.data.ptr = fd_ctx;

    int rt=epoll_ctl(m_epfd,op,fd,&epevent);
    if(rt){
        LOG_ERROR(g_logger)<<"addEvent assert fd="<<fd
            <<"event="<<event
            <<"fd_ctx.event="<<fd_ctx->events;
        ASSERT(!(fd_ctx->events&event));
        return false;
    }

    fd_ctx->triggerEvent(event);
    --m_pendingEventCount;
    return true;

}

bool IOManager::cancelAll(int fd){
    RWMutexType::ReadLock lock(m_mutex);
    if(m_fdContexts.size()<=fd){
        return false;
    }
    FdContext* fd_ctx=m_fdContexts[fd];
    lock.unlock();

    FdContext::MutexType::Lock lock2(fd_ctx->mutex);
    if(!(fd_ctx->events)){
        return false;
    }
    
    int op = EPOLL_CTL_DEL; 
    epoll_event epevent;
    epevent.events = 0;
    epevent.data.ptr = fd_ctx;

    int rt=epoll_ctl(m_epfd,op,fd,&epevent);
    if(rt){
        LOG_ERROR(g_logger)<<"addEvent assert fd="<<fd
            <<"fd_ctx.event="<<fd_ctx->events;
        //ASSERT(!(fd_ctx->events & ));
        return false;
    }

    if(fd_ctx->events & READ){
        fd_ctx->triggerEvent(READ);
         --m_pendingEventCount;
    }

    if(fd_ctx->events & WRITE){
         fd_ctx->triggerEvent(WRITE);
         --m_pendingEventCount;
    }

    ASSERT(fd_ctx->events == 0);
    return true;
}

IOManager* IOManager::GetThis(){
    return dynamic_cast<IOManager*>(Scheduler::GetThis());
}

void IOManager::tickle(){
    if(!hasIdelThreads()){
          
        return;
    }
    int rt=write(m_tickleFds[1],"T",1);
    ASSERT(rt==1);
}

bool IOManager::stopping(){
    return m_pendingEventCount==0
           && Scheduler::stopping();
}


void IOManager::onTimerInsertedAtFront(){
    tickle();
}

void IOManager::idle(){
    epoll_event* events=new epoll_event[64];
    std::shared_ptr<epoll_event> shared_event(events,[](epoll_event* ptr){
                    delete[] ptr;
                });
    while(true){
        uint64_t next_timeout=0;
        if(stopping()){
            next_timeout=getNextTimer();
            if(next_timeout == ~0ull){
                 LOG_INFO(g_logger)<<"name="<<"idle stopping exit";
             break;
            }
        }


        int rt=0;
        do{
            static const int MAX_TIMEOUT=1000;
            if(next_timeout != ~0ull){
                next_timeout = (int)next_timeout >MAX_TIMEOUT ?  MAX_TIMEOUT : next_timeout;
            }else{
                next_timeout = MAX_TIMEOUT;
            }
            rt=epoll_wait(m_epfd,events,64,(int)next_timeout);
            if(rt<0&&errno==EINTR){
            
            }else{
                break;
            }
        }while(true);

        std::vector<std::function<void()>> cbs;
        listExpiredTimer(cbs);
        if(!cbs.empty()){
            schedule(cbs.begin(),cbs.end());
        }

        for(int i=0;i<rt;++i){
            epoll_event& event=events[i];
            if(event.data.fd==m_tickleFds[0]){
                uint8_t dummy;
                while(read(m_tickleFds[0],&dummy,1)==1);
                continue; 
            }
            FdContext* fd_ctx= (FdContext*)event.data.ptr;
            FdContext::MutexType::Lock lock(fd_ctx->mutex);
            if(event.events&(EPOLLERR | EPOLLHUP)){
                event.events |= EPOLLIN&EPOLLOUT;
            }
            int real_event = NONE;
            if(event.events & EPOLLIN){
                real_event |= READ;
            }
            if(event.events & EPOLLOUT){
                real_event |=WRITE;
            }
            if((fd_ctx->events&real_event)==NONE){
                continue;
            }
            int left_events=(fd_ctx->events & ~real_event);
            int op=left_events ? EPOLL_CTL_MOD:EPOLL_CTL_DEL;
            event.events = EPOLLET|left_events;
            int rt2=epoll_ctl(m_epfd,op,fd_ctx->fd,&event);
            if(rt2){
                LOG_ERROR(g_logger)<<"epoll_ctl"<<m_epfd<<", "
                    <<op<<","<<fd_ctx->fd<<","<<event.events<<"):"
                    <<rt2<<" ("<<errno<<") ("<<strerror(errno)<<")";
                continue;
            }
            if(real_event&READ){
                fd_ctx->triggerEvent(READ);
                --m_pendingEventCount;
            }
            if(real_event & WRITE){
                fd_ctx->triggerEvent(WRITE);   
                --m_pendingEventCount;
            }
        }
    Fiber::ptr cur=Fiber::GetThis();
    auto raw_ptr = cur.get();
    cur.reset();
    raw_ptr->swapOut();
    }
}
};


