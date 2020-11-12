//
// Created by 21548 on 2020/11/9.
//

#ifndef MATRIX_MULTIPLICATION_OPENMXM_H
#define MATRIX_MULTIPLICATION_OPENMXM_H

#include <iostream>

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

void m_product_column(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2);

void m_product_row(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2);

void m_product_block(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2);

#endif //MATRIX_MULTIPLICATION_OPENMXM_H
