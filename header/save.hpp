#include <fstream>

using namespace std;

// Сохранения прогресса
void saveGame(int count, int clicker, int upgPrice) {
    ofstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile<<count<<endl;
        saveFile<<clicker<<endl;
        saveFile<<upgPrice<<endl;
        saveFile.close();
    }
}

// Загрузка прогресса
void loadGame(int &count, int &clicker, int &upgPrice) {
    ifstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile>>count;
        saveFile>>clicker;
        saveFile>>upgPrice;
        saveFile.close();
    }
}