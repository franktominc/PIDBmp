#include <iostream>
#include <dirent.h>
#include <list>
#include <libltdl/lt_system.h>
#include "BitmapImage.h"

using namespace std;

bool has_suffix(const std::string &str, const std::string &suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

string find_file_name(const std::string str){
    unsigned long long startingPosition = 0;
    for (auto i = 0; i < str.size(); i++) {
        if(str[i] == '/' || str[i] == '\\'){
            startingPosition = i+1;
        }
    }
    return str.substr(startingPosition, str.size());
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

        auto filePath = path + "/" + ep->d_name;
        if(has_suffix(filePath, ".bmp")){
            cout << filePath << endl;
            gabaritos.push_back(filePath);
        }

    }
    for(auto it = gabaritos.begin(); it != gabaritos.end(); it++){
        string aux="";
        aux+= *it;
        string aux2="";
        BitmapImage teste = BitmapImage(aux, find_file_name((*it)));
        cout << teste.fileName << endl;
        teste.Erode(5);

    }
    return EXIT_SUCCESS;
}