#include "threadpool.h"
#include <QDebug>

ThreadPool::ThreadPool( const int threadNumber )
    :_queue( 0 ), _tasksDone( 0 ), _done( false )
{
    for( int i = 0; i < threadNumber; ++i )
        _pool.create_thread( boost::bind( &ThreadPool::_worker, this ) );
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::joinAll()
{
    while( !_queue.empty() );
    done();
    _pool.join_all();
}

void ThreadPool::stop()
{
    done();
    _pool.join_all();
}

void ThreadPool::_worker()
{
    while( !_done.load( boost::memory_order_relaxed ) )
    {
        wrapper *wr;
        if( _queue.pop( wr ) )
        {
           wr->call();
           delete wr;
            _tasksDone.fetch_add( 1, boost::memory_order_relaxed );
        }
        else
            boost::this_thread::yield();

    }
}

void ThreadPool::done()
{
    _done.store( true, boost::memory_order_relaxed );
}

int ThreadPool::tasksDone()
{
    return _tasksDone.load( boost::memory_order_acquire );
}

int ThreadPool::tasks()
{
    return _tasks.load( boost::memory_order_acquire );
}


void ThreadPool::resetCounter()
{
    _tasksDone.store( 0, boost::memory_order_release );
}




