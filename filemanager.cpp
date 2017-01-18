#include "filemanager.h"
#include <QDataStream>

FileManager::FileManager(char * name )
    : _name( name )
{
}


const QString& FileManager::fileName() const
{
    return _name;
}

bool FileManager::open()
{

    _file.setFileName( _name );
    return _file.open( QIODevice::ReadOnly );

}

QFile& FileManager::file()
{
    return _file;
}

const QByteArray &FileManager::bytes()
{
    if( !_readed )
    {
        if( !_file.isOpen() )
            return _bytes;
        QDataStream stream( &_file );
        stream.setVersion( QDataStream::Qt_4_8 );
        int count { 4 };
        char* temp{nullptr};
        while( !stream.atEnd() )
        {
            temp = new char[ count ];
            stream.readRawData(  temp, count );
            _bytes.append( temp, count );
            delete [] temp;
        }
        return _bytes;
    }
    else
        return _bytes;



}
