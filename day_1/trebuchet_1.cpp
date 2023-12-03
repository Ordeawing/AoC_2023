#include <fstream>
#include <iostream>

using namespace std;

int main() {
    fstream file;
    file.open("file.txt", fstream::in);

    if (file.is_open()) {
        string line;
        int f_total = 0;
        while (getline(file, line)) {
            int d_first = -1;
            int d_last = 0;
        
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (isdigit(c) && d_first == -1) {
                    d_first = c - '0';
                    d_last = c - '0';
                } else if (isdigit(c)) {
                    d_last = c - '0';
                }
            }
            
            int l_total = (d_first * 10) + d_last;
            f_total += l_total;
            
            cout << l_total << '\n';
        }
        cout << f_total << '\n';
        file.close();
    }
}