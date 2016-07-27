#include <iostream>
#include <dirent.h>
#include <list>
#include <libltdl/lt_system.h>
#include "BitmapImage.h"

using namespace std;

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char* argv[]) {

    string gabarito;
    string path;


    DIR* directory;
    struct dirent *ep;

    list<string> gabaritos;

    cout << "Entre com o gabarito oficial: ";
    getline(cin, gabarito);
    cout << "Entre com o caminho com os gabaritos à serem corrigidos: ";
    getline(cin, path);


    directory = opendir(path.c_str());

    if(directory == NULL){
        cerr << "Error(" << errno << ") opening " << directory << endl;
        return errno;
    }
    while((ep = readdir(directory))){

        auto filepath = path + "/" + ep->d_name;

        if(has_suffix(filepath, ".bmp")){
            cout << filepath << endl;
            gabaritos.push_back(filepath);
        }

    }
    for(auto it = gabaritos.begin(); it != gabaritos.end(); it++){
        auto image = fopen((*it).c_str(), "rb+");
        if(image == NULL){
            cerr << "Error(" << errno << ") opening " << (*it) << endl;
        }
        string aux="";
        aux+= *it;
        BitmapImage teste = BitmapImage(aux);

    }
    return EXIT_SUCCESS;
}