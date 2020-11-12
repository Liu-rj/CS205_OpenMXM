//
// Created by 21548 on 2020/11/9.
//

#include "OpenMXM.h"

void m_product_row(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2) {
    int apos = 0;
    int bpos;
    int cpos = 0;
    for (int i = 0; i < row1; ++i) {
        bpos = 0;
        for (int j = 0; j < column1; ++j) {
            for (int k = 0; k < column2; ++k) {
                c[cpos++] += a[apos] * b[bpos++];
            }
            apos++;
            cpos -= column2;
        }
        cpos += column2;
    }
}

void m_product_column(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2) {
    for (int i = 0; i < column2; ++i) {
        for (int j = 0; j < row1; ++j) {
            for (int k = 0; k < column1; ++k) {
                c[j * column1 + i] += a[j * column1 + k] * b[k * column2 + i];
            }
        }
    }
}

void m_product_block(float *c, const float *a, const float *b,int row1, int column1, int row2, int column2) {
    
}