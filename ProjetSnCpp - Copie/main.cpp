#include <iostream>
#include <filesystem>
#include <string>
#include "Drive.h"
#include "Bridge.h"
#include "Config.h"
//#include "notif.h"

#include <tchar.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <strsafe.h>

#define UNICODE
#include <windows.h>
#include <vector>


using namespace std;


int main()
{
    vector <string> myFinalFiles;
    Drive d;
    char letters ;
    letters = d.getUsb();
    while(1)
    {
        letters = d.getUsb();

        if (letters != '0')
        {
            myFinalFiles = d.sync(letters);

            for (int i = 0 ; i < myFinalFiles.size() ; i++ )
            {
                cout << myFinalFiles.at(i);
            }
        }
    }
    return 0;
}





