#include <iostream>
#include <chrono>
#include "OpenMXM.h"

using namespace std;

int main() {
    int row1, column1, row2, column2;
    float f;
    string str;
    here:
    while (true) {
//        // initial the first the matrix struct
//        cout << "Please enter the size of the first matrix" << endl << "row: ";
//        cin >> f;
//        if (floor(f) == f) {
//            row1 = f;
//        } else {
//            cout << "Wrong input! Please try again!" << endl;
//            continue;
//        }
//        cout << "column: ";
//        cin >> f;
//        if (floor(f) == f) {
//            column1 = f;
//        } else {
//            cout << "Wrong input! Please try again!" << endl;
//            continue;
//        }
//        matrix a(row1, column1);
//        cout << "elements: " << endl;
//        for (int i = 0; i < row1 * column1; ++i) {
//            cin >> a.elements[i];
//            if (cin.fail()) {
//                cout << "Wrong input! Please try again!" << endl;
//                cin.clear();
//                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//                goto here;
//            }
//        }
//
//        // initial the second matrix struct
//        cout << "Please enter the size of the second matrix" << endl << "row: ";
//        cin >> f;
//        if (floor(f) == f) {
//            row2 = f;
//        } else {
//            cout << "Wrong input! Please try again!" << endl;
//            continue;
//        }
//        if (row2 != column1) {
//            cout << "matrix size mismatch! Please try again!" << endl;
//            continue;
//        }
//        cout << "column: ";
//        cin >> f;
//        if (floor(f) == f) {
//            column2 = f;
//        } else {
//            cout << "Wrong input! Please try again!" << endl;
//            continue;
//        }
//        matrix b(row2, column2);
//        cout << "elements: " << endl;
//        for (int i = 0; i < row2 * column2; ++i) {
//            cin >> b.elements[i];
//            if (cin.fail()) {
//                cout << "Wrong input! Please try again!" << endl;
//                cin.clear();
//                cin.ignore(numeric_limits<std::streamsize>::max());
//                goto here;
//            }
//        }

        row1 = 1000;
        column1 = 1000;
        row2 = 1000;
        column2 = 1000;
        matrix a(row1, column1);
        a.elements[0] = -3;
        a.elements[1] = 2;
        matrix b(row2, column2);
        b.elements[0] = -2;
        b.elements[1] = -3;

        matrix c(row1, column2);

        // do the matrix calculation
        // begin time
        auto start1 = std::chrono::steady_clock::now();

        m_product_column(c.elements, a.elements, b.elements, row1, column1, row2, column2);

        // end time
        auto end1 = std::chrono::steady_clock::now();

        cout << c.elements[0] << ' ' << c.elements[1] << endl;

//        for (int i = 0; i < row1 * column2; ++i) {
//            cout << c.elements[i] << ' ';
//            if ((i + 1) % column2 == 0) {
//                cout << endl;
//            }
//        }

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
 *
 */

/** 1M:
 * brutal: 1051 ms
 * continuous cache: 207 ms
 * OpenBLAS: 33 ms
 * transposition:
 */