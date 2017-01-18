#include <iostream>
#include <QDebug>
#include "filemanager.h"
#include "parsemanager.h"


using namespace std;

int main( int argc, char* argv[] )
{
    if( argc != 2 )
        std::cerr<<"Wrong argument!!!"<<std::endl;
    FileManager fm( argv[1] );
    if( !fm.open())
        std::cerr<<"Cant open the file: "<< argv[1]<<std::endl;
    ParseManager pm( fm.bytes() );
    pm.parse();

    return 0;
}

