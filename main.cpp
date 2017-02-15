#include <iostream>
#include <dirent.h>
#include <list>
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
            startingPosition = (unsigned long long int) (i + 1);
        }
    }
    return str.substr(startingPosition, str.size());
}

void mainMenu(){
    printf(" ( 1 ) Conversao para Tons de Cinza\n");
    printf(" ( 2 ) Floyd-Steinberg Dithering\n");
    printf(" ( 3 ) Correcao de Gabaritos\n");
    printf(" ( 0 ) Sair\n");
}

void convertToGrayScale(){
    string path;

    DIR* directory;

    struct dirent *ep;

    list<string> gabaritos;

    cout << "Entre com o caminho com as imagens que se deseja converter: ";
    getline(cin, path);

    directory = opendir(path.c_str());

    if(directory == NULL){
        cerr << "Error(" << errno << ") opening " << directory << endl;
        return;
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
        teste.toGrayScale();
    }
}

void applyFloydSteinberg(){
    string path;

    DIR* directory;

    struct dirent *ep;

    list<string> gabaritos;

    cout << "Entre com o caminho com as imagens que se deseja aplicar o dithering: ";
    getline(cin, path);

    directory = opendir(path.c_str());

    if(directory == NULL){
        cerr << "Error(" << errno << ") opening " << directory << endl;
        return;
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
        teste.floydSteinberg();
    }
    return;
}

void gradeResponseCards(){
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
        return;
    }
    while((ep = readdir(directory))){

        auto filePath = path + "/" + ep->d_name;
        if(has_suffix(filePath, ".bmp")){
            cout << filePath << endl;
            gabaritos.push_back(filePath);
        }

    }
    cout << "-------------------------------------------------" << endl;
    cout << "        Gabarito: " << gabarito << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "        Diretorio: " << directory << endl;
    for(auto it = gabaritos.begin(); it != gabaritos.end(); it++){
        cout << "-------------------------------------------------" << endl;
        string aux="";
        aux+= *it;
        string aux2="";
        BitmapImage teste = BitmapImage(aux, find_file_name((*it)));
        cout << teste.fileName << endl;
        teste.toBlackAndWhite();
        teste.Erode(5);
        teste.Dilate(8);
        teste.findTopLeftRectangle();
        teste.findBotLeftRectangle();
        teste.findTopRightRectangle();
        teste.findAnswers(teste.topLeft);
        cout << "    Respostas: ";
        int sum = 0;
        int blank = 0;
        int multipleAnswers = 0;
        for (int i = 0; i < teste.answers.size(); i++) {
            if(gabarito[i] == teste.answers[i]) sum++;
            if(teste.answers[i] == 'O') blank++;
            if(teste.answers[i] == 'X') multipleAnswers ++;
            cout << teste.answers[i];
        }
        cout << endl;
        cout << "    Acertos: " << sum << endl;
        cout << "    Brancos: " << blank << endl;
        cout << "    Multiplas Respostas: " << multipleAnswers << endl;

    }
    cout << "-------------------------------------------------" << endl;
    return;
}

int main(int argc, char* argv[]) {
    int option;

    while(true){
        mainMenu();
        cin >> option;
        getchar();
        switch(option) {
            case 0:
                return EXIT_SUCCESS;
            case 1:
                convertToGrayScale();
                break;
            case 2:
                applyFloydSteinberg();
                break;
            case 3:
                gradeResponseCards();
                break;
            default:
                cout << "Opcao invalida, favor inserir novamente" << endl;
        }
    }
    return EXIT_SUCCESS;
}