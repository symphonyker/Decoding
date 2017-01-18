#include <QCryptographicHash>
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include "decdecrypter.h"


const int DecDecrypter::_keySize = 8;
const int DecDecrypter::_ivSize = 8;
const int DecDecrypter::_cryptBlockSize = 16;

DecDecrypter::DecDecrypter(const QByteArray & data )
    :_data( data )
{
}

DecDecrypter::DecDecrypter()
{}



//void DecDecrypter::setInitValue( const unsigned char value, const int index )
//{
//    if( index < 0 || index >7 )
//        return;
//    _initVector[index] = value ;
//}

DecDecrypter::DecrypData DecDecrypter::decrypt(const QByteArray &iv , const QString& key )
{
    unsigned char text[_cryptBlockSize];

    DES_cblock initVector  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    for( int i = 0; i < _ivSize; ++i )
        initVector[i] =(unsigned char) iv[i];

    QByteArray hash { QCryptographicHash::hash( key.toUtf8() ,QCryptographicHash::Md5)};
    DES_cblock key1  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    DES_cblock key2  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    DES_key_schedule schKey1;
    DES_key_schedule schKey2;

    _createKey( key1, hash.left( _keySize ) );
    _createKey( key2, hash.right( _keySize ) );
    _setKey( key1, schKey1 );
    _setKey( key2, schKey2 );
    int ptr = 0;
    QByteArray out;

    for( int i = 0; i < _data.size() / _cryptBlockSize; ++i )
    {
        memset( text,0, sizeof( text ) );

        DES_ede2_cbc_encrypt( (unsigned char*)_data.mid( ptr , _cryptBlockSize ) .data(), (unsigned char*)text, sizeof( text ), &schKey1, &schKey2, &initVector, DES_DECRYPT );
        out.append( ( char* ) text, _cryptBlockSize );
        ptr += _cryptBlockSize;
    }
    DecrypData d;
    d.setData( out );
    d.setHash( QString( QCryptographicHash::hash( out, QCryptographicHash::Sha256 ).toHex() ) );
    return d;

}

void DecDecrypter::_createKey( DES_cblock &key, const QByteArray &  data )
{
    for( int i = 0; i < _keySize; ++i )
        key[i] = (unsigned char) data[i];
}

bool DecDecrypter::_setKey( DES_cblock & key , DES_key_schedule & schKey )
{
    DES_set_odd_parity( &key );
    if (DES_set_key( &key, & schKey ) < 0)
    {
         std::cerr<<"DES SetKey Error"<<std::endl;
        return false;
    }
    else
        return true;

}
void DecDecrypter::setEncryptData(const QByteArray & data)
{
    _data = data;
}

DecDecrypter::DecrypData::DecrypData()
{

}

const QString& DecDecrypter::DecrypData::getHash() const
{
    return _hash;
}


const QByteArray& DecDecrypter::DecrypData::getData() const
{
    return _data;
}


void DecDecrypter::DecrypData::setData( const QByteArray &d )
{
    _data = d;
}

void DecDecrypter::DecrypData::setHash( const QString & h)
{
    _hash = h;
}

DecDecrypter::DecrypData& DecDecrypter::DecrypData::operator =( const DecrypData& d )
{
    this->_data = d._data;
    this->_hash = d._hash;

}

