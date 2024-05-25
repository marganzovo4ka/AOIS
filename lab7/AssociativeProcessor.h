#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
class AssociativeProccessor {
private:
    int table[16][16] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    string Sum(string a, string b) {
        int buf = 0;
        string res = "00000";
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] == '1')
                buf++;
            if (b[i] == '1')
                buf++;
            if (buf % 2 != 0)
                res[i + 1] = '1';
            if (buf >= 2)
                buf = 1;
            else
                buf = 0;
        }
        if (buf == 1)
            res[0] = '1';
        return res;
    }

    string IntToBinary(int value) {
        string res_x[16];
        string res;
        for (int i = 15; i >= 0; i--) {
            if (value / 2 != 0) {
                res_x[i] = to_string(value % 2);
                value /= 2;
            }
            else {
                res_x[i] = to_string(value);
                value = 0;
            }
        }
        for (int i = 0; i <= 15; i++) {
            res += res_x[i];
        }
        return res;
    }

    string RebildFound(int index) {
        string v;
        string a;
        string b;
        int count = 0;
        for (int i = index; i < 16 + index - 5; i++) {
            if (i < 16) {
                if (count < 3)
                    v += to_string(table[i][index]);
                if (count >= 3 && count < 7)
                    a += to_string(table[i][index]);
                if (count >= 7 && count < 11)
                    b += to_string(table[i][index]);
                count++;
            }
            else {
                if (count < 3)
                    v += to_string(table[i - 16][index]);
                if (count >= 3 && count < 7)
                    a += to_string(table[i - 16][index]);
                if (count >= 7 && count < 11)
                    b += to_string(table[i - 16][index]);
                count++;
            }
        }
        string res;
        res += v;
        res += a;
        res += b;
        res += Sum(a, b);
        return res;
    }

public:

    int BinaryToInt(string buf) {
        int res = 0;
        for (int i = buf.size() - 1; i >= 0; i--)
            res += ((buf[i] - 48) * pow(2, buf.size() - 1 - i));
        return res;
    }

    void ShowTable() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                cout << table[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    void Sort() {
        vector<int> vector_to_sort;
        string buf;
        for (int i = 0; i < 16; i++) {
            buf = GetWord(i);
            vector_to_sort.push_back(BinaryToInt(buf));
        }
        sort(vector_to_sort.begin(), vector_to_sort.end());
        for (int i = 0; i < 16; i++) {
            AddWord(i, IntToBinary(vector_to_sort[i]));
        }
    }

    void FindStarting(string start) {
        for (int i = 0; i < 16; i++) {
            int count = 0;
            for (int j = i; j < 3 + i; j++){
                if (table[j][i] == start[j - i] - 48) {
                    count++;
                }
                if (j == 2 + i && count == 3) {
                    AddWord(i, RebildFound(i));
                }
            }
        }
    }

    string GetWord(int index) {
        string res;
        for (int i = index; i < 16 + index; i++) {
            if (i >= 16){
                res += to_string(table[i-16][index]);
            }
            else {
                res += to_string(table[i][index]);
            }
        }
        return res;
    }

    void AddWord(int index, string word) {
        for (int i = index; i < 16 + index; i++) {
            if (i >= 16) {
                table[i - 16][index] = word[i - index] - 48;
            }
            else {
                table[i][index] = word[i - index] - 48;
            }
        }
    }

    string AddressColumn(int index) {
        string res;
        for (int i = 0; i < 16; i++) {
            if (i + index >= 16) {
                res += to_string(table[i + index - 16][i]);
            }
            else {
                res += to_string(table[i + index][i]);
            }
        }
        return res;
    }

    void Disparity(string frst_word, string sec_word, int recording_place) {
        string res;
        for (int i = 0; i < 16; i++) {
            if (frst_word[i] != sec_word[i])
                res += to_string(0);
            else
                res += to_string(1);
        }
        AddWord(recording_place, res);
    }

    void Equivalence(string frst_word, string sec_word, int recording_place) {
        string res;
        for (int i = 0; i < 16; i++) {
            if (frst_word[i] == sec_word[i])
                res += to_string(0);
            else
                res += to_string(1);
        }
        AddWord(recording_place, res);
    }

    void ProhibSecEl(string frst_word, string sec_word, int recording_place) {
        string res;
        for (int i = 0; i < 16; i++) {
            if (frst_word[i] == '0' && sec_word[i] == '1')
                res += to_string(0);
            else
                res += to_string(1);
        }
        AddWord(recording_place, res);
    }

    void ImplFromSecToFirst(string frst_word, string sec_word, int recording_place) {
        string res;
        for (int i = 0; i < 16; i++) {
            if (!(frst_word[i] == '0' && sec_word[i] == '1'))
                res += to_string(0);
            else
                res += to_string(1);
        }
        AddWord(recording_place, res);
    }
};