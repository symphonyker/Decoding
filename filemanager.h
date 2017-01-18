#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <memory>
#include <QString>
#include <QFile>
#include <QByteArray>


class FileManager
{
private:
    QString _name{""};
    QFile _file;
    QByteArray _bytes;
    bool _readed{false};
public:
   FileManager(char* name);
   FileManager& operator=(const FileManager&) = delete;
   const QString& fileName() const;
   QFile& file();
   bool open();
   const QByteArray& bytes();


};

#endif // FILEMANAGER_H
