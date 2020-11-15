//
// Created by 21548 on 2020/11/9.
//

#ifndef MATRIX_MULTIPLICATION_OPENMXM_H
#define MATRIX_MULTIPLICATION_OPENMXM_H

#include <iostream>

struct matrix {
    int row;
    int column;
    float **elements;

    matrix(int a, int b) {
        row = a;
        column = b;
        elements = new float*[row];
        for (int i = 0; i < row; ++i) {
            elements[i] = new float[column]{};
        }
    }
};

void mxm_column(float **c, float **a, float **b,int row1, int column1, int row2, int column2);

void mxm_row(float **c, float **a, float **b,int row1, int column1, int row2, int column2);

void mxm_block(float **c, float **a, float **b,int row1, int column1, int row2, int column2);

void mxm_sse(float **c, float **a, float **b,int row1, int column1, int row2, int column2);

void product1(float **c, float **a, float **b, int row1, int column1, int row2, int column2);

#endif //MATRIX_MULTIPLICATION_OPENMXM_H
