#include <fstream>
#include <iostream>
using namespace std;

void add(string **array, string value, size_t *arr_size) {
    string *temp = new string[*arr_size + 1];
    copy(*array, *array + *arr_size, temp);
    temp[*arr_size] = value;

    *arr_size += 1;
    delete[] *array;
    *array = temp;
}

void remove(string **array, string to_delete, size_t *arr_size) {
    string *temp = new string[*arr_size - 1];
    int index = 0;
    for (int i = 0; i < *arr_size; i++) {
        if (strcmp((*(*array + i)).c_str(), to_delete.c_str())) {
            temp[index] = *(*array + i);
            index++;
        }
    }

    *arr_size -= 1;
    delete[] *array;
    *array = temp;
}

void removeAt(string **array, int to_delete, size_t *arr_size) {
    string *temp = new string[*arr_size - 1];
    int index = 0;
    for (int i = 0; i < *arr_size; i++) {
        if (!(i == to_delete)) {
            temp[index] = *(*array + i);
            index++;
        }
    }
    
    *arr_size -= 1;
    delete[] *array;
    *array = temp;
}


int main () {
    fstream file;
    file.open("file.txt", fstream::in);

    size_t s_games = 0;
    string *games;
    games = new string[s_games];

    if (file.is_open()) {
        string line;
        while (getline(file, line, ':')) {
            getline(file, line);
            if (line.find("Game") == string::npos) {
                add(&games, line, &s_games);
            }
        }

        for (int i = 0; i < s_games; i++) {
            cout << games[i] << '\n';
        }

        file.close();
    }
}