#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <QString>
#include <array>

class CodeGenerator
{
private:
    struct __genIndexs
    {
        std::array<int, 3> arr;
    };
    __genIndexs _indexs;
    QString _symbolPool;
    void _init();
    void _initIndexes();
    void _correctIndexes();
    void _correctIndex(int );
    void _fillSymbolPool();
    bool _end{false};
    static const int _numCount;
    static const int _chCount;
public:
    CodeGenerator();
    QString nextCode();
};

#endif // CODEGENERATOR_H
