#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <functional>

struct ThreadPool
{

    struct wrapper
    {
       virtual void call()=0;
       virtual ~wrapper(){}
    };

    struct wrapperImpl : public wrapper
    {

        std::function<void()> fun;


        void call()
        {
            fun();
        }
    };

public:

    ThreadPool( const int c );


    ~ThreadPool();
    void done();

    int tasksDone();
    int tasks();

    void resetCounter();

    template <class CL,class ...ARG >
    void addTask( void (CL::*f)( ARG... ), CL* obj ,ARG... arg )
    {
        ThreadPool::wrapper* wr = new ThreadPool::wrapperImpl;
        ( (  ThreadPool::wrapperImpl *)wr )->fun = std::bind( f, obj, arg... );
        _tasks.fetch_add( 1, boost::memory_order_relaxed );
        _queue.push( wr );
    }

    template<class CL>
    void addTask( void (CL::*f)( ), CL*obj  )
    {
        ThreadPool::wrapper* wr = new ThreadPool::wrapperImpl;
        ( (  ThreadPool::wrapperImpl *)wr )->fun = std::bind( f, obj );
        _tasks.fetch_add( 1, boost::memory_order_relaxed );
        _queue.push( wr );
    }
    void joinAll();
    void stop();

private:

    boost::lockfree::queue< wrapper* > _queue;
    boost::atomic<bool> _done;
    boost::atomic<int> _tasksDone;
    boost::atomic<int> _tasks;
    boost::thread_group _pool;
    void _worker();
};

#endif // THREADPOOL_H
