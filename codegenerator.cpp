#include "codegenerator.h"
#include <QDebug>

const int CodeGenerator::_numCount = 10;
const int CodeGenerator::_chCount = 26;

CodeGenerator::CodeGenerator()
{
    _init();
}


void CodeGenerator::_init()
{
    _initIndexes();
    _fillSymbolPool();
}

void CodeGenerator::_initIndexes()
{
    for( int i = 0; i < _indexs.arr.size(); ++i )
        _indexs.arr[i] = 0;
}

void CodeGenerator::_fillSymbolPool()
{
    for( int i = 0; i < _numCount; ++i)
            _symbolPool.append( ('0' + i ) );
    for( int i = 0; i < _chCount; ++i)
            _symbolPool.append( ('a' + i ) );
    for( int i = 0; i < _chCount; ++i)
            _symbolPool.append( ('A' + i ) );
}


QString CodeGenerator::nextCode()
{
    QString code;
    if( _end )
        return QString::null;
    for( int i  = 0; i < _indexs.arr.size(); ++i )
    {
        //qDebug()<<"i="<<i;
        code.append( _symbolPool[_indexs.arr[i]] );
    }
    _correctIndexes();
    return  code;
}


void CodeGenerator::_correctIndexes()
{
    _correctIndex( 0 );
}

void CodeGenerator::_correctIndex( int index )
{
    if( ( index > _indexs.arr.size() ) )
    {
        _end = true;
        return;
    }
    if( ( _indexs.arr[index] + 1 ) >= _symbolPool.size() )
    {
        _indexs.arr[index] = 0;
        _correctIndex( ++index );
    }
    else
        _indexs.arr[index] += 1;

}
