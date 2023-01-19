#ifndef BRIDGE_H
#define BRIDGE_H
#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

class Bridge
{
    public:
        Bridge();
        void kCopy(string file, string name);
        virtual ~Bridge();

    protected:

    private:
};

#endif // BRIDGE_H
