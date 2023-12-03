#include <fstream>
#include <iostream>

using namespace std;

void add(string **array, string value, int *arr_size) {
    string *temp = new string[*arr_size + 1];
    copy(*array, *array + *arr_size, temp);
    temp[*arr_size] = value;

    *arr_size += 1;
    delete[] *array;
    *array = temp;
}

void remove(string **array, string to_delete, int *arr_size) {
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

void removeAt(string **array, int to_delete, int *arr_size) {
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

int countSub(string r_str, string sub) {
    int count = 0;
    for (size_t offset = r_str.find(sub); offset != string::npos; offset = r_str.find(sub, offset + sub.length())) {
        ++count;
    }
    return count;
}

int main() {
    
    fstream file;
    file.open("file.txt", fstream::in);
    int digits_size = 9;
    string s_digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char c_digits[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    if (file.is_open()) {
        string line;
        int f_total = 0;
        while (getline(file, line)) {
            for (int i = 0; i < digits_size; i++) {
                //todo
            }
        }
        cout << f_total << '\n';
        file.close();
    }

}