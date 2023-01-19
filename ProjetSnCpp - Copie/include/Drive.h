#include <windows.h>
#include <string>
#ifndef DRIVE_H
#define DRIVE_H

using namespace std;
class Drive
{
    public:
        Drive();
        detect();
        vector <string> sync(char usb);
        void kCopy(string file, string name);
        time_t  convert_to_timestamp(string dt);
        string getFileExtension(string filePath);
        string CompareFile(string a, string b);
        void wait();
        char getUsb();
        virtual ~Drive();

    protected:



};

#endif // DRIVE_H
