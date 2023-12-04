#include <fstream>
#include <iostream>

using namespace std;

void computeValue(int *f_pos, int *f_value, int *l_pos, int *l_value, int offset, int value) {
    if (*f_pos == -1) {
        *f_pos = offset;
        *l_pos = offset;
        *f_value = value;
        *l_value = value;
    } else if (offset < *f_pos) {
        *f_pos = offset;
        *f_value = value;
    } else if (offset > *l_pos) {
        *l_pos = offset;
        *l_value = value;
    }
}

int main() {
    
    fstream file;
    file.open("file.txt", fstream::in);
    int digits_size = 9;
    string s_digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char c_digits[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (file.is_open()) {
        string line;
        int f_total = 0;
        while (getline(file, line)) {
            int f_value;
            int f_pos = -1;
            int l_value;
            int l_pos;

            for (int i = 0; i < digits_size; i++) {
                string sub = s_digits[i];
                for (size_t offset = line.find(sub); offset != string::npos; offset = line.find(sub, offset + sub.length())) {
                    computeValue(&f_pos, &f_value, &l_pos, &l_value, offset, digits[i]);
                }

                sub = c_digits[i];
                for (size_t offset = line.find(sub); offset != string::npos; offset = line.find(sub, offset + sub.length())) {
                    computeValue(&f_pos, &f_value, &l_pos, &l_value, offset, digits[i]);
                }
            }

            f_total += (f_value * 10) + l_value;
        }
        cout << f_total << '\n';
        file.close();
    }

}