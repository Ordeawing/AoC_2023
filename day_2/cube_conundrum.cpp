#include <fstream>
#include <iostream>
#include <regex>
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

void checkValue(string set, int &game_id) {
    regex red("([0-9]+) red");
    regex green("([0-9]+) green");
    regex blue("([0-9]+) blue");
    smatch match;
    int red_max = 12;
    int green_max = 13;
    int blue_max = 14;

    if (regex_search(set, match, red)) {
        int red_count = stoi(match[1].str());
        if (red_count > red_max) {
            game_id = 0;
        }
    }
    if (regex_search(set, match, green)) {
        int green_count = stoi(match[1].str());
        if (green_count > green_max) {
            game_id = 0;
        }
    }
    if (regex_search(set, match, blue)) {
        int blue_count = stoi(match[1].str());
        if (blue_count > blue_max) {
            game_id = 0;
        }
    }
}

int main () {
    fstream file;
    file.open("file.txt", fstream::in);

    size_t s_games = 0;
    string *games;
    games = new string[s_games];
    int result = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line, ':')) {
            getline(file, line);
            if (line.find("Game") == string::npos) {
                add(&games, line, &s_games);
            }
        }

        for (int i = 0; i < s_games; i++) {
            size_t pos;
            string set;
            int game_id = i + 1;
            while ((pos = games[i].find(";")) != string::npos) {
                set = games[i].substr(0, pos);
                checkValue(set, game_id);
                games[i].erase(0, pos + 1);
            }
            checkValue(games[i], game_id);
            result += game_id;
        }
        file.close();
        cout << result << endl;
    }
}