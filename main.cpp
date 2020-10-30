#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

struct matrix {
    int row;
    int column;
    float *elements;

    matrix(int a, int b) {
        row = a;
        column = b;
        elements = new float[a * b]{};
    }
};

void m_product(float *c, float *a, float *b,int row1, int column1, int row2, int column2) {
    for (int i = 0; i < row1 * column2; ++i) {
        for (int j = 0; j < column1; ++j) {
            c[i] += a[(i / column2) * column1 + j] * b[i % column2 + j * column2];
        }
    }
}

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
        for (int i = 0; i < row1 * column1; ++i) {
            cin >> a.elements[i];
            if (cin.fail()) {
                cout << "Wrong input! Please try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                goto here;
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
        for (int i = 0; i < row2 * column2; ++i) {
            cin >> b.elements[i];
            if (cin.fail()) {
                cout << "Wrong input! Please try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max());
                goto here;
            }
        }

//        row1 = 10000;
//        column1 = 10000;
//        row2 = 10000;
//        column2 = 10000;
//        matrix a(row1, column1);
//        a.elements[0] = 1;
//        matrix b(row2, column2);
//        b.elements[0] = 1;

        matrix c(row1, column2);

        // do the matrix calculation
        // begin time
        auto start1 = std::chrono::steady_clock::now();

        m_product(c.elements, a.elements, b.elements, row1, column1, row2, column2);

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

        cout << "Wanna continue?(YES to continue, NO to exit)" << endl;
        cin >> str;
        if (str == "NO") {
            return 0;
        }
    }
    return 0;
}

/**
 * brutal(float):over 300000 ms(5 min)
 * OpenBLAS:28055 ms
 */
