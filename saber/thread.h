#ifndef __SABER_THREAD_H
#define __SABER_THREAD_H
//pthread_xxx(before c++11)
//std::thread -> pthread
#include<thread>
#include<memory>
#include<functional>
#include<string>
#include<pthread.h>
#include<stdint.h>
#include<semaphore.h>
#include<exception>
namespace saber{
	/*********************************************************************
	 *Class Thread
	 ********************************************************************/
	class Semaphore{
	public:
		Semaphore(uint32_t count=0);
		~Semaphore();

		void wait();
		void notify();
	private:
		/**
	 	 *@brief copy constructor
	 	 */
		Semaphore& operator=(const Semaphore& s)=delete;

		Semaphore(const Semaphore&)=delete;

		Semaphore(const Semaphore&&)=delete;
	private:

		sem_t m_semaphore;

	};

	/********************************************************************
	 *Class ScopedLockImpl
	 ********************************************************************/
	template<class T>
	class ScopedLockImpl{
	public:
		ScopedLockImpl(T& mutex):m_mutex(mutex){
			m_mutex.lock();
			m_locked=true;
		}
		
		~ScopedLockImpl(){
			unlock();
		}
		
		void lock(){
			if(!m_locked){
				m_mutex.lock();
				m_locked=true;
			}
		}

		void unlock(){
			if(m_locked){
				m_mutex.unlock();
				m_locked=false;
			}
		}
	private:
		T& m_mutex;
		bool m_locked;
	};


	template<class T>
	class ReadScopedLockImpl{
	public:
		ReadScopedLockImpl(T& mutex):m_mutex(mutex){
			m_mutex.rdlock();
			m_locked=true;
		}
		
		~ReadScopedLockImpl(){
			unlock();
		}
		
		void lock(){
			if(!m_locked){
				m_mutex.rdlock();
				m_locked=true;
			}
		}

		void unlock(){
			if(m_locked){
				m_mutex.unlock();
				m_locked=false;
			}
		}
	private:
		T& m_mutex;
		bool m_locked;
	};

	template<class T>
	class WriteScopedLockImpl{
	public:
		WriteScopedLockImpl(T& mutex):m_mutex(mutex){
			m_mutex.wrlock();
			m_locked=true;
		}
		
		~WriteScopedLockImpl(){
			unlock();
		}
		
		void lock(){
			if(!m_locked){
				m_mutex.wrlock();
				m_locked=true;
			}
		}

		void unlock(){
			if(m_locked){
				m_mutex.unlock();
				m_locked=false;
			}
		}
	private:
		T& m_mutex;
		bool m_locked;
	};

	/********************************************************************
	 *Class Mutex and RWMutex
	 ******************************************************************/

	class Mutex{
	public:
		typedef ScopedLockImpl<Mutex> Lock;
		Mutex(){
			pthread_mutex_init(&m_mutex,nullptr);
		}

		~Mutex(){
			pthread_mutex_destroy(&m_mutex);
		}

		void lock(){
			pthread_mutex_lock(&m_mutex);
		}

		void unlock(){
			pthread_mutex_unlock(&m_mutex);
		}
	private:
		pthread_mutex_t m_mutex;
	};

	class RWMutex{
	public:
		typedef ReadScopedLockImpl<RWMutex> ReadLock;
		typedef WriteScopedLockImpl<RWMutex> WriteLock;
		RWMutex(){
			pthread_rwlock_init(&m_rwlock,nullptr);
		}

		~RWMutex(){
			pthread_rwlock_destroy(&m_rwlock);
		}

		void rdlock(){
			pthread_rwlock_rdlock(&m_rwlock);
		}

		void wrlock(){
			pthread_rwlock_wrlock(&m_rwlock);
		}

		void unlock(){
			pthread_rwlock_unlock(&m_rwlock);
		}

	private:
		pthread_rwlock_t m_rwlock;
	};

	class NullMutex{
	public:
		typedef ScopedLockImpl<NullMutex> Lock;

		NullMutex(){
		
		}

		~NullMutex(){
		
		}

		void lock(){
		
		}

		void unlock(){
		
		}
	};

	class NullRWMutex{
	public:
		typedef ReadScopedLockImpl<NullRWMutex> ReadLock;
		typedef WriteScopedLockImpl<NullRWMutex> WriteLock;
		NullRWMutex(){
		}

		~NullRWMutex(){
		}

		void rdlock(){
		}

		void wrlock(){
		}

		void unlock(){
		}
	};

	/*********************************************************************
	 *Class Thread
	 ********************************************************************/
	class Thread{
		public:
			typedef std::shared_ptr<Thread> ptr;

			/**
			 *@brief constructor, create thread
			 */
			Thread(std::function<void()> c,const std::string& name);

			/**
			 *@brief destructor
			 */
			~Thread();

			/**
			 *@brief set thread name
			 */
			const std::string& getName() const {return m_name;}

			/**
			 *@brief get thread id
			 */
			const pid_t getId()const {return m_id;}

			/**
			 *@brief get current thread name
			 */
			static const std::string& GetName();

			/**
			 *@brief set current thread name
			 */
			static void SetName(const std::string& name);

			/**
			 *@brief waits for current finish
			 */
			void join();

			/**
			 *@brief get current thread pointer
			 */
			static Thread* GetThis();

		private:
			/**
			 *@brief delete copy assign
			 */
			Thread& operator=(const Thread& t)=delete;

			/*
			 *@brief delete copy constructor
			 */
			Thread(const Thread& t)=delete;
			Thread(const Thread&& t)=delete;
		private:
			pid_t m_id=-1;	//process ID
			pthread_t m_thread=0;	//thread ID
			std::function<void()> m_cb;	//call back function of thread
			std::string m_name;	//thread name
			static void *run(void* arg);	//run thread call back function
			Semaphore m_semaphore;	//semaphore
	};
};
#endif
