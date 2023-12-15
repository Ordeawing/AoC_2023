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

int main () {
    fstream file;
    file.open("file.txt", fstream::in);

    size_t s_buffer = 0;
    string *buffer;
    buffer = new string[s_buffer];

    int result = 0;

    if (file.is_open()) {
        
        string line;
        int index = 0;
        int r_index = 0;
        while (true) {
            getline(file, line);
            add(&buffer, line, &s_buffer);

            if (index == 0) {
                getline(file, line);
                add(&buffer, line, &s_buffer);
            } else {
                r_index = 1;
            }

            string sub = "*";
            for (size_t pos = buffer[r_index].find(sub); pos != string::npos; pos = buffer[r_index].find(sub, pos + sub.length())) {
                cout << pos << endl;
            }

            break;

            if (file.eof()) break;
            index++;
        }

        file.close();
    }
}