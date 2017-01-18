#ifndef DECDECRYPTER_H
#define DECDECRYPTER_H
#include <QByteArray>
#include <QString>
#include <openssl/des.h>


class DecDecrypter
{
private:
    QByteArray _data;
    static const int _keySize;
    static const int _ivSize;
    static const int _cryptBlockSize;
    void _createKey( DES_cblock &,  const QByteArray& );
    bool _setKey( DES_cblock &, DES_key_schedule& );
public:
    class DecrypData
    {
        public:
            DecrypData();
            void setData( const QByteArray& );
            const QByteArray& getData() const;
            const QString& getHash() const;
            void setHash( const QString& );
            DecrypData& operator=( const DecrypData& );
        private:
            QByteArray _data;
            QString _hash;

    };
    DecDecrypter( const QByteArray& );
    DecDecrypter();
    void setInitValue( const unsigned char, const int );
    void setEncryptData( const QByteArray& );
    DecrypData decrypt( const QByteArray & iniVector,const QString& key );
};

#endif // DECDECRYPTER_H
