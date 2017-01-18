#include "parsemanager.h"
#include "codegenerator.h"
#include <unistd.h>
#include <QDebug>


const int ParseManager::_initVectorSize = 8;
const int ParseManager::_sha256Size = 32 ;

ParseManager::ParseManager( const QByteArray& bytes )
    :_bytes( bytes ), _threadPool(  sysconf( _SC_NPROCESSORS_CONF ) - 1 ), _found( false )
{
}

void ParseManager::parse()
{
    if( _bytes.size() == 0 )
        return;
    _dec.setEncryptData( _bytes.mid( _initVectorSize, _bytes.size() - ( _initVectorSize + _sha256Size )  ) );
    CodeGenerator gen;
    QString code;
    while( ( ( code = gen.nextCode() ) != QString::null ) )
    {
        _threadPool.addTask( &ParseManager::_decrypt, this, code );
        if( _found.load() == true )
            break;
    }
   while( ( _found.load() == false ) && ( _threadPool.tasksDone() != _threadPool.tasks() ) );
   _threadPool.stop();

}


void ParseManager::_decrypt( QString code )
{
            DecDecrypter::DecrypData dData = _dec.decrypt( _bytes.left( _initVectorSize ),  code );
            if( dData.getHash() == QString( _bytes.right( _sha256Size ).toHex() ) )
            {
               _found.store( true );
               qDebug()<<"Founded code="<<code;
               qDebug()<<"Text="<<dData.getData();
            }
}

