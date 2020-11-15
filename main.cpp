#include <iostream>
#include <cmath>
#include <chrono>
#include "OpenMXM.h"

using namespace std;

int main() {
    int row1, column1, row2, column2;
    float f;
    string str;
    here:
    while (true) {
        // initial the first the matrix struct
        cout << "Please enter the size of the first matrix" << endl << "row: ";
        cin >> f;
        if (floor(f) == f) {
            row1 = f;
        } else {
            cout << "Wrong input! Please try again!" << endl;
            continue;
        }
        cout << "column: ";
        cin >> f;
        if (floor(f) == f) {
            column1 = f;
        } else {
            cout << "Wrong input! Please try again!" << endl;
            continue;
        }
        matrix a(row1, column1);
        cout << "elements: " << endl;
        for (int i = 0; i < row1; ++i) {
            for (int j = 0; j < column1; ++j) {
                cin >> a.elements[i][j];
                if (cin.fail()) {
                    cout << "Wrong input! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    goto here;
                }
            }
        }

        // initial the second matrix struct
        cout << "Please enter the size of the second matrix" << endl << "row: ";
        cin >> f;
        if (floor(f) == f) {
            row2 = f;
        } else {
            cout << "Wrong input! Please try again!" << endl;
            continue;
        }
        if (row2 != column1) {
            cout << "matrix size mismatch! Please try again!" << endl;
            continue;
        }
        cout << "column: ";
        cin >> f;
        if (floor(f) == f) {
            column2 = f;
        } else {
            cout << "Wrong input! Please try again!" << endl;
            continue;
        }
        matrix b(row2, column2);
        cout << "elements: " << endl;
        for (int i = 0; i < row2; ++i) {
            for (int j = 0; j < column2; ++j) {
                cin >> b.elements[i][j];
                if (cin.fail()) {
                    cout << "Wrong input! Please try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max());
                    goto here;
                }
            }
        }

        matrix c(row1, column2);

        // do the matrix calculation
        // begin time
        auto start1 = std::chrono::steady_clock::now();

        mxm_block(c.elements, a.elements, b.elements, row1, column1, row2, column2);

        // end time
        auto end1 = std::chrono::steady_clock::now();

        for (int i = 0; i < row1 * column2; ++i) {
            cout << c.elements[i] << ' ';
            if ((i + 1) % column2 == 0) {
                cout << endl;
            }
        }

        printf("%s%ld%s", "calculation takes ",
               std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count(), " ms\n");

        cout << "Wanna continue [YES/NO]?" << endl;
        cin >> str;
        if (str == "NO") {
            return 0;
        }
    }
}

/** 100M:
 * brutal: too long to wait
 * continuous cache: 249760 ms
 * OpenBLAS: 29195 ms
 * openmp: 163277 ms
 */

/** 1M:
 * brutal: 1051 ms
 * continuous cache: 207 ms
 * OpenBLAS: 33 ms
 * openmp: 22ms
 */