//
// Created by 21548 on 2020/11/9.
//

#include "OpenMXM.h"
#include <xmmintrin.h>
#include <immintrin.h>
#include <omp.h>

void mxm_row(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column1; ++j) {
            for (int k = 0; k < column2; ++k) {
                c[i][k] += a[i][j] * b[j][k];
            }
        }
    }
}

void mxm_column(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column2; ++j) {
            for (int k = 0; k < column1; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mxm_block(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
    int i, j ,k;
#pragma omp parallel for private(i, j, k)
    for (i = 0; i < row1; i ++) {
        for (j = 0; j < column1; j += 4) {
            register float reg1 = a[i][j], reg2 = a[i][j + 1], reg3 = a[i][j + 2], reg4 = a[i][j + 3];
            for (k = 0; k < column2; k += 4) {
                c[i][k] += reg1 * b[j][k] + reg2 * b[j + 1][k] + reg3 * b[j + 2][k] + reg4 * b[j + 3][k];
                c[i][k + 1] += reg1 * b[j][k + 1] + reg2 * b[j + 1][k + 1] + reg3 * b[j + 2][k + 1] + reg4 * b[j + 3][k + 1];
                c[i][k + 2] += reg1 * b[j][k + 2] + reg2 * b[j + 1][k + 2] + reg3 * b[j + 2][k + 2] + reg4 * b[j + 3][k + 2];
                c[i][k + 3] += reg1 * b[j][k + 3] + reg2 * b[j + 1][k + 3] + reg3 * b[j + 2][k + 3] + reg4 * b[j + 3][k + 3];
            }
        }
    }
}

void mxm_sse(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
    __m128 ma, mb, mc;
    mc = _mm_setzero_ps();
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column1; j ++) {
            for (int k = 0; k < column2; k += 4) {
                ma = _mm_load_ps(a[i]);
                mb = _mm_load_ps(b[j] + k);
                mc = _mm_add_ps(mc, _mm_mul_ps(ma, mb));
                _mm_store_ps(c[i] + k, mc);
            }
        }
    }
}

//void product1(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
//    register float creg1, creg2, creg3, creg4, areg;
//    for (int j = 0; j < column2; j += 4) {
//        for (int i = 0; i < row1; ++i) {
//            creg1 = 0;
//            creg2 = 0;
//            creg3 = 0;
//            creg4 = 0;
//
//            for (int k = 0; k < column1; ++k) {
//                areg = a[i][k];
//                creg1 += areg * b[k][j];
//                creg2 += areg * b[k][j + 1];
//                creg3 += areg * b[k][j + 2];
//                creg4 += areg * b[k][j + 3];
//            }
//
//            c[i][j] = creg1;
//            c[i][j + 1] = creg2;
//            c[i][j + 2] = creg3;
//            c[i][j + 3] = creg4;
//        }
//    }
//} // 900ms 486ms

void addDot(float **c, float **a, float **b, int column1, int i, int j) {
    register float creg1, creg2, creg3, creg4, creg5, creg6, creg7, creg8, creg9, creg10, creg11, creg12, creg13, creg14, creg15, creg16;
    register float areg1, areg2, areg3, areg4;
    creg1 = 0;
    creg2 = 0;
    creg3 = 0;
    creg4 = 0;

    __m128 ma, mb, mc0, mc1, mc2, mc3;

    for (int k = 0; k < column1; k++) {
        areg1 = a[i][k];
        areg2 = a[i + 1][k];
        areg3 = a[i + 2][k];
        areg4 = a[i + 3][k];

        creg1 += areg1 * b[k][j];
        creg2 += areg1 * b[k][j + 1];
        creg3 += areg1 * b[k][j + 2];
        creg4 += areg1 * b[k][j + 3];

        creg5 += areg2 * b[k][j];
        creg6 += areg2 * b[k][j + 1];
        creg7 += areg2 * b[k][j + 2];
        creg8 += areg2 * b[k][j + 3];

        creg9 += areg3 * b[k][j];
        creg10 += areg3 * b[k][j + 1];
        creg11 += areg3 * b[k][j + 2];
        creg12 += areg3 * b[k][j + 3];

        creg13 += areg4 * b[k][j];
        creg14 += areg4 * b[k][j + 1];
        creg15 += areg4 * b[k][j + 2];
        creg16 += areg4 * b[k][j + 3];
    }

    c[i][j] = creg1;
    c[i][j + 1] = creg2;
    c[i][j + 2] = creg3;
    c[i][j + 3] = creg4;

    c[i + 1][j] = creg1;
    c[i + 1][j + 1] = creg2;
    c[i + 1][j + 2] = creg3;
    c[i + 1][j + 3] = creg4;

    c[i + 2][j] = creg1;
    c[i + 2][j + 1] = creg2;
    c[i + 2][j + 2] = creg3;
    c[i + 2][j + 3] = creg4;

    c[i + 3][j] = creg1;
    c[i + 3][j + 1] = creg2;
    c[i + 3][j + 2] = creg3;
    c[i + 3][j + 3] = creg4;
}

void product1(float **c, float **a, float **b, int row1, int column1, int row2, int column2) {
//#pragma omp parallel for
    for (int j = 0; j < column2; j += 4) {
        for (int i = 0; i < row1; i += 4) {

            addDot(c, a, b, column1, i, j);
        }
    }
} // 900ms 486ms 460ms 125ms

void mxm_block(float *c, const float *a, const float *b, int row1, int column1, int row2, int column2) {
    int apos = 0;
    int bpos;
    int cpos = 0;
    for (int i = 0; i < row1; ++i) {
        bpos = 0;
        for (int j = 0; j < column1; j++) {
            register float common = a[apos];
            for (int k = 0; k < column2; k ++) {
                c[cpos++] += common * b[bpos++];
                c[cpos++] += common * b[bpos++];
                c[cpos++] += common * b[bpos++];
                c[cpos++] += common * b[bpos++];
            }
            apos++;
            cpos -= column2;
        }
        cpos += column2;
    }
}
