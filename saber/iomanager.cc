#include"iomanager.h"
#include"macro.h"
#include<unistd.h>
#include<sys/epoll.h>
#include"log.h"
#include<fcnth.h>
#include<errno.h>
#include<string.h>
namespace saber{
static saber::Logger::ptr g_logger=LOG_NEW("system");
IOManager::IOManager(size_t thread,bool use_caller,const std::string& name):Scheduler(threads,use_caller,name){
    m_epfd=epoll_wait(5000);
    ASSETR2(m_epfd>0,"epoll wait error");
    
    int rt=pipe(m_tickleFds);

    ASSETR2(rt,"pipe creat error");
    epoll_event event;
    memset(&event,0,sizeof(epoll_event));
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = m_tickleFds[0];
    rt = fcntl(m_tickleFds[0],F_SETFL,O_NONBLOCK);
    ASSETR(rt);
    //add events to epoll
    rt = epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_tickleFds[0],&event);
    ASSETR(fd);

    contextResize(64);
    start();
}

IOManager::~IOManager(){
    stop();
    colse(m_epfd);
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
    FdContext::Mutex::Lock lock3(fd_ctx->m_mutex);
    if(fd_ctx->events & event){//if fd_ctx->events == event
        LOG_ERROR(g_logger)<<"addEvent assert fd="<<fd
            <<"event="<<event
            <<"fd_ctx.event="<<fd_ctx->events;
        ASSETR(!(fd_ctx->m_events&event));
    }
    int op=fd_ctx->events ? EPOLL_CTL_MOD:EPOLL_CTL_ADD;
    epoll_event epevent;
    epevent.events=EPOLLET| fd_ctx->events | event;
    epevent.data.ptr=fd_ctx;

    int rt=epoll_ctl(m_epfd,op,fd,&ep_event);
    if(rt){
        LOG_ERROR(g_logger)<<"epoll_ctl("<<m_epfd<<", "
            <<op<<","<<fd<<","<<epevent.events<<"):"
            <<rt<<" ("<<errno<<")"<<strerror(errno)<<")";a
        return -1;
    }
     m_pendingEventCount++;
    fd_ctx->events=(Event)(fd_ctx->events|event);
    FdContext::EventContext& event_ctx=fd_ctx->getContext(event);
    ASSETR(!event_ctx.scheduler);
    ASSETR(!event_ctx.fiber);
    ASSETR(!event_ctx.cb);
    
    event_ctx.scheduler=Scheduler::GetThis();
    if(cb){
        context.cb.swap();

    }else{
        context.fiber=Fiber::GetThis();
        ASSETR(context->getState()==Fiber::EXEC);
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
    RWMutexType::Readlock lock(m_mutex);
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
        ASSETR(!(fd_ctx->m_events&event));
        return false;
    }
    --m_pendingEventCount;
    fd_ctx->events=new_event;
    FdContext::EventContext& event_ctx=fd_ctx->getContext(event);
    fd_ctx->resetContext(event_ctx);
    return true;
}


void IOManager::FdContext::triggerEvent(IOManager::Event event){
    ASSETR(events & event);
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
            ASSETR2(false,"getContext");
   }
}

void  IOManager::FdContext::resetContext(IOManager::FdContext::EventContext& ctx){
    ctx.scheduler = nullptr;
    ctx.fiber.reset();
    ctx.cb = nullptr;
}

bool IOManager::cancelEvent(int fd.Event event){
    RWMutexType::Readlock lock(m_mutex);
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
        ASSETR(!(fd_ctx->m_events&event));
        return false;
    }

    fd_ctx->triggerEvent(event);
    --m_pendingEventCount;
    return true;

}

bool IOManager::cancelAll(int fd){
    RWMutexType::Readlock lock(m_mutex);
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
            <<"event="<<event
            <<"fd_ctx.event="<<fd_ctx->events;
        ASSETR(!(fd_ctx->m_events&event));
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

    ASSETR(fd_ctx->events == 0);
    return true;
}

IOManager* IOManager::GetThis(){
    return dynamic_cast<IOManager*>(Scheduler::GetThis());
}
};


