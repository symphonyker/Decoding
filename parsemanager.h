#ifndef PARSEMANAGER_H
#define PARSEMANAGER_H
#include <QByteArray>
#include "threadpool.h"
#include "decdecrypter.h"
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>


class ParseManager
{
private:
    DecDecrypter _dec;
    QByteArray _bytes;
    static const int _initVectorSize;
    static const int _sha256Size;
    ThreadPool _threadPool;
    void _decrypt( QString );
    boost::atomic<bool> _found;
public:
    ParseManager(  const QByteArray& );
    ParseManager();
    void parse();
    void setParseData( const QByteArray& );
};

#endif // PARSEMANAGER_H
