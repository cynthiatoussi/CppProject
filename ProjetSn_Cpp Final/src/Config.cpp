#include "Config.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <stdio.h>



Config::Config()
{
    //ctor
}



void Config::readFiles()
{
    vector <string> myFile;

    //----------------------------OPEN FILE IN LECTURE--------------------
	FILE* file = fopen("C:\\Users\\hp\\Desktop\\keyce_drive\\Info.csv", "r");

	if (!file)
	{
		printf("impossible d'ouvrir le ficier\n");


	}

	char content[1024];

	while (fgets(content, 1024, file))
	{
		char* v = strtok(content, ";");
		while (v)
		{
		    myFile.push_back(v);
			//printf("%s ", v);
			v = strtok(NULL, ";");
		}
		printf("\n");
	}

	fclose(file);


}
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

void Config::listefiles() {
    string path = "F:\\";
    cout << "le Keyce Drive drive il y a les fichiers ci dessous \n \n "<< endl;
    for (const auto & file : directory_iterator(path))

        cout << file.path() << endl;
    cout << "Branchez votre clee \n \n "<< endl;

}

Config::~Config()
{
    //dtor
}
