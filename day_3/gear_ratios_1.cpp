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

void add(char **array, char value, size_t *arr_size) {
    char *temp = new char[*arr_size + 1];
    copy(*array, *array + *arr_size, temp);
    temp[*arr_size] = value;

    *arr_size += 1;
    delete[] *array;
    *array = temp;
}

void remove(char **array, char to_delete, size_t *arr_size) {
    char *temp = new char[*arr_size - 1];
    int index = 0;
    for (int i = 0; i < *arr_size; i++) {
        if ((*(*array + i)) == to_delete) {
            temp[index] = *(*array + i);
            index++;
        }
    }

    *arr_size -= 1;
    delete[] *array;
    *array = temp;
}

void removeAt(char **array, int to_delete, size_t *arr_size) {
    char *temp = new char[*arr_size - 1];
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

    size_t s_filebuf = 0;
    string *filebuf;
    filebuf = new string[s_filebuf];

    int result = 0;

    if (file.is_open()) {
        
        int index = 0;
        int number_lines = 0;
        int buf_index = 0;
        string line;
        while (true) {
            if (index == 0) {
                getline(file, line);
                add(&filebuf, line, &s_filebuf);
                getline(file, line);
                add(&filebuf, line, &s_filebuf);
                number_lines = 2;
            } else {
                getline(file, line);
                if (strcmp(line.c_str(), filebuf[s_filebuf - 1].c_str()) != 0) {
                    add(&filebuf, line, &s_filebuf);
                    number_lines++;
                    buf_index = 1;
                }
            }
            
            size_t s_buf = 0;
            char *buf;
            buf = new char[s_buf];

            int first_pos = 0;
            int last_pos = 0;

            for (int i = 0; i < filebuf[buf_index].length(); i++) {
                char c = filebuf[buf_index][i];
                if (isdigit(c) && s_buf == 0) {
                    add(&buf, c, &s_buf);
                    first_pos = i;
                } else if (isdigit(c) && s_buf > 0) {
                    add(&buf, c, &s_buf);
                }
                
                if ((!isdigit(c) && s_buf > 0) || (i == filebuf[buf_index].length() - 1 && isdigit(c))) {
                    last_pos = i - 1;

                    int *check_lines;
                    check_lines = new int[number_lines];
                    if (buf_index == 0) {
                        check_lines[0] = 0;
                        check_lines[1] = 1;
                    } else if (buf_index == 1 && number_lines == 2) {
                        check_lines[0] = 0;
                        check_lines[1] = 1;
                    } else {
                        check_lines[0] = 0;
                        check_lines[1] = 1;
                        check_lines[2] = 2;
                    }
                    int boundaries[2] = {first_pos ? first_pos - 1 : first_pos, last_pos == filebuf[index].length() - 1 ? last_pos : last_pos + 1};

                    for (int j = check_lines[0]; j <= check_lines[number_lines - 1]; j++) {
                        for (int k = boundaries[0]; k <= boundaries[1]; k++) {
                            char c1 = filebuf[j][k];
                            if (c1 != '.' && !isdigit(c1)) {
                                int tmp_result = 0;
                                for (int l = 0; l < s_buf; l++) {
                                    tmp_result *= 10;
                                    tmp_result += buf[l] - '0';
                                }
                                result += tmp_result;
                            }
                        }
                    }

                    s_buf = 0;
                    delete[] buf;
                    buf = new char[s_buf];
                }
            }
            if (number_lines == 2 && index > 0) {
                cout << result << endl;
                break;
            }
            if (index > 0) {
                removeAt(&filebuf, 0, &s_filebuf);
                number_lines--;
            }
            index++;
        }

        file.close();
    }
}