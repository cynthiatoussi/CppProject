#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "Drive.h"
#include "Config.h"
#include "Bridge.h"
//-------------------------------
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

using namespace std;

Drive::Drive()
{

}

Drive::detect(){

}

Drive::~Drive()
{
    wait();
}
Drive dr;
Config c;
Bridge b;

    string allDrives;

    string folder;

//-------------------EXTENSION REMOVAL FROM PATH IN A STRING---------------------------


/*string Drive::clear_slash(string const& path_of_file, auto & d_slash = "/\\")
{
    size_t index_of_slash = path_of_file.find_last_of(d_slash);
    string file_name = path_of_file.substr(index_of_slash + 1);
    return file_name;
}

string Drive::extension_removal(string const& name_of_file)
{
    size_t index_of_period = name_of_file.find_last_of('.');
    string file_without_extension = name_of_file.substr(0, index_of_period);
    return file_without_extension;
}
*/
//------------------------REWRITE COMPARE FUNCTION--------------------------
//----------------------------RECREATE THE strcmp() FUNCTION-------------------------------


string Drive::CompareFile(string a, string b){
        bool flag(a.size() == b.size());
        int i(0);
        while (flag && i != min(a.size(), b.size())){
            flag = a[i] == b[i];
            i++;
        }
        return flag ? "Found":"Not Found";
}


char Drive::getUsb(){
    char usb = '0';
    char sizeLocalDrive[MAX_PATH];
    DWORD dResult = GetLogicalDriveStrings(MAX_PATH, sizeLocalDrive);
    string currentUsb = "";
    for(int i = 0; i < dResult; i++){
        if(sizeLocalDrive[i] > 64 && sizeLocalDrive[i] < 90){
            currentUsb.append(1, sizeLocalDrive[i]);
            if(allDrives.find(sizeLocalDrive[i]) > 100){
                usb = sizeLocalDrive[i];
            }
        }
    }
    allDrives = currentUsb;

    return usb;
}

void Drive::wait(){
    char usbLetter = getUsb();

    while(true){
        usbLetter = getUsb();
        if(usbLetter != '0'){
            printf("%c\n ", usbLetter);
            sync(usbLetter);
            Sleep(1000);
        }
    }
}

vector <string> Drive::sync(char usb){
    string filename(1, usb);
    vector <string> myExtensions;
    vector<string> r;
    filename += ":\\";
    cout << filename;
    vector <string> Allrecentfiles;
    vector <string> Extension;
    vector <string> finalFiles;
    string is_available;
    string myDate;
    Extension = c.readFiles();
//-----------------REWRTITE THE PATH WITH FOLDER IN CSV FILE----------------------
    filename += "\\";

    if( Extension[0] == "folder")
    {
        folder = Extension[1];
    }

    filename += folder;

    //filename += "\\";

    cout << "new file name path" << endl;
    cout << filename << endl;

 /*   for(int i = 0 ; i < Extension.size() ; i++)
    {
        cout << Extension.at(i) << endl ;
    } */
    //--------------------------------------LIST ALL FILES IN SPECIAL DIRECTORY-------------------------------------------
    if(filesystem::is_directory(filename))
    // si filesystem est un dossier, alors copy tous les fichiers à l'intérieur sur le bureau
    {
        for(int i = 0 ; i <= 13 ; i += 3)
            {
               /* if ( (Extension.at( i + 2 ) == "extensions" ) )
                {
                    cout << Extension.at(i+3);
                }*/
                //-------------------DETERMINER LES EXTENSIONS CONTENUES DANS LE FICHIER--------------------------
                if(Extension.at( i + 3 ) == "extensions")
                {
                    //cout << Extension.at(i + 4) << endl;
                    //--------myExtensions contient les extensions du fichier excel-------------------------
                    myExtensions.push_back(Extension.at( i + 4));
                }
                //-------------------DETERMINER LA DATE-----------------------------------------------------
                myDate = Extension.at(13);



           }
//----------------------------CONVERT DATE TO TIMESTAMP-----------------------------------------------------
time_t convertDate = dr.convert_to_timestamp(myDate);
//cout << convertDate << endl;
//----------------------------SEARCH ALL FILE AND COVERT IT IN THE VECTOR-----------------------------------
        for(const auto & entry : filesystem::directory_iterator(filename)){
            //cout << entry.path() << endl;
            //kCopy(entry.path().string(), entry.path().filename().string());

            //auto ft1 = filesystem::last_write_time(entry.path().string());
            //cout << "Last date modification" << " " << &ft1 << endl;
            struct stat result;
            if(stat(entry.path().string().c_str(), &result)==0)
                {
                    auto mod_time = result.st_mtime;
                    //cout << mod_time << endl;
                    if (mod_time > convertDate)
                    {
                        //cout << "fichiers plus recents" << endl;
                        Allrecentfiles.push_back(entry.path().string());
                    }
                    else
                    {
                        //cout << "fICHIERS NON RECENTS" << endl;
                        continue;
                    }

                }

}
//------------------------EXTENSION OF FILES------------------------
cout << "RECENT FILES SIZE" << endl;
cout << Allrecentfiles.size();
string extensionFile ;
//------------------------GETTING ALL EXTENSION TO FILES------------

for ( int i = 0 ; i < myExtensions.size(); i++)
{
    for (int j = 0 ; j < Allrecentfiles.size() ; j++)
    {
        //cout << "<<\n EXTENSIONS" << endl;
        //cout << myExtensions[i];


        extensionFile = dr.getFileExtension(Allrecentfiles.at(j));

        //cout << "<<\n EXTENSIONS FROM FILE" << endl;
        //cout << extensionFile;

        is_available = dr.CompareFile(extensionFile, myExtensions.at(i));

        if(is_available == "Found")
        {
            //cout << "True extention" << endl;
            finalFiles.push_back(Allrecentfiles.at(j));
        }
        else{
                //cout << "Wrong extensions" << endl;
            continue;
        }
        //cout << extensionFile << endl;

    }


}
//-------------------------SHOW ALL AVAILABE FILES------------------------
//cout << "------------------AVAILABLE FILES------------------" << endl;
string finalFileName;
for (int i = 0 ; i < finalFiles.size() ; i++)
{
//--------------------------COPY ALL FILE WHICH IS IN THIS VECTOR---------------------------
finalFileName = finalFiles.at(i);
// Remove directory if present.
// Do this before extension removal incase directory has a period character.
const size_t last_slash_idx = finalFiles.at(i).find_last_of("\\/");
if (string::npos != last_slash_idx)
{
    finalFiles.at(i).erase(0, last_slash_idx + 1);
}

    //cout << finalFileName<<endl;
    //cout << finalFiles.at(i) << endl;
    b.kCopy(finalFileName, finalFiles.at(i));

    //finalFileName = dr.extension_removal(dr.clear_slash(finalFiles.at(i)));
    //cout << filesystem::path(finalFiles.at(i)).filename() << endl ;
    //cout << finalFileName << endl;

    //b.kCopy(finalFiles.at(i), finalFiles.at(i).filename())

    //kCopy(entry.path().string(), entry.path().filename().string());
}
    }
    return finalFiles;
    }

time_t  Drive::convert_to_timestamp(string dt){

     tm t{};
     istringstream ss(dt);

    ss >> std::get_time(&t, "%d/%m/%Y");
    if (ss.fail()) {
        throw std::runtime_error{"failed to parse time string"};
    }
    return mktime(&t);
}

string Drive::getFileExtension(string filePath)
{
    // Create a Path object from given string
    filesystem::path pathObj(filePath);
    // Check if file name in the path object has extension
    if (pathObj.has_extension()) {
        // Fetch the extension from path object and return
        return pathObj.extension().string();
    }
    // In case of no extension return empty string
    return "";
}
//}
/*
void Drive::kCopy(string file, string name){
    cout << file;
    ofstream ofile ("C:\\Users\\user\\Desktop\\keyce_drive\\"+ name);
    ifstream sfile (file, ios::binary);
    char buffer[1024];
    while(sfile.read(buffer, sizeof(buffer))){
        ofile.write(buffer, sfile.gcount());
    }
//    ofile.write(buffer, sfile.gcount());

    ofile.close();
    sfile.close();
}
*/
