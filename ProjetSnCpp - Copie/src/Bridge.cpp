/*
*  BRIDGE RECUPERE LE VECTEUR STOCKE DANS DRIVE ET PUIS CA COPIE TOUS LES FICHIERS
* QUI Y SONT CONTENUS SUR MON BUREAU
*/
#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "Bridge.h"


Bridge::Bridge()
{
    //ctor
}
//---------------------------DECLARING ALL VARIABLES-----------------------------

//-----------------------------DEFINE THE COPY METHOD----------------------------------
void Bridge::kCopy(string file, string name){
    cout << file;
    ofstream ofile ("C:\\Users\\Admin\\Desktop\\keyce_drive\\"+ name,std::ios_base::binary);
    ifstream sfile (file,std::ios_base::binary);
    char buffer[1024];
    while(!sfile.eof()){
        sfile.read(buffer, sizeof(buffer));
        ofile.write(buffer, sfile.gcount());
    }
//    ofile.write(buffer, sfile.gcount());

    ofile.close();
    sfile.close();
}

Bridge::~Bridge()
{
    //dtor
}
