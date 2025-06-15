#pragma once
#ifndef _swj_include_
#define _swj_include_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <complex>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;
typedef complex<double> cd;
typedef complex<float> cf;
typedef complex<int> ci;
typedef complex<long> cl;

struct one_D { double x; };
struct two_D { double x, y; };
struct three_D { double x, y, z; };
struct ijk { int i, j, k; };
struct vector_d { double x, y, z; };
struct vector_f { float x, y, z; };

//#define _linux_intel_swj
//#define _win_intel_swj
//#define _pause_when_error_swj

#ifdef _linux_intel_swj
#define fprintf_s fprintf
#define fscanf_s fscanf
#define sprintf_s sprintf
#endif

void std_printf_swj(FILE* standard_output, char* output_swj)
{
#ifdef _win_intel_swj
    fprintf_s(standard_output, "%s", output_swj);
#endif
#ifdef _linux_intel_swj
    fprintf(standard_output, "%s", output_swj);
#endif
}

void pause_when_error()
{
#if (defined _pause_when_error_swj)&&(defined _win_intel_swj)
    getchar();
#endif
}

void copyright_swj_2021(FILE* standard_output)
{
    fprintf_s(standard_output, "+-------------------------------------------------------------------------------------------+\n");
    fprintf_s(standard_output, "|This code is written by Wujun Shi.                                                         |\n");
    //fprintf_s( standard_output, "|(former)Department of Physics, Tsinghua University, Beijing, China                         |\n" );
    //fprintf_s( standard_output, "|(former)Max Planck Institute for Chemical Physics of Solids, Dresden, Germany              |\n" );
    fprintf_s(standard_output, "|Center for Transformative Science, ShanghaiTech University, Shanghai, China                |\n");
    fprintf_s(standard_output, "|Any problems, please contact with wjshi.phys@gmail.com, or shiwujun2003@126.com.           |\n");
    fprintf_s(standard_output, "|Enjoy!                                                                                     |\n");
    fprintf_s(standard_output, "+-------------------------------------------------------------------------------------------+\n");
}
void copyright_swj_2017(FILE* standard_output)
{
    fprintf_s(standard_output, "+---------------------------------------------------------------------------------------+\n");
    fprintf_s(standard_output, "|This code is written by Wujun Shi.                                                     |\n");
    fprintf_s(standard_output, "|Center for Transformative Science, ShanghaiTech University, Shanghai, China            |\n");
    //fprintf_s(standard_output, "|Max Planck Institute for Chemical Physics of Solids, Dresden, Germany                  |\n");
    fprintf_s(standard_output, "|Any problems, please contact with wjshi.phys@gmail.com, or shiwujun2003@126.com.       |\n");
    fprintf_s(standard_output, "|Enjoy!                                                                                 |\n");
    fprintf_s(standard_output, "+---------------------------------------------------------------------------------------+\n");
}

void version_swj(FILE* standard_output, char* fucntion1, char* release_date1, char* release_version1)
{
    fprintf_s(standard_output, "+-------------------------------------------------------------------------------------------+\n");
    fprintf_s(standard_output, "| %-90s|\n", fucntion1);
    fprintf_s(standard_output, "| This version is released on  %-19s                                          |\n", release_date1);
    fprintf_s(standard_output, "| Current version is  %-19s                                                   |\n", release_version1);
    fprintf_s(standard_output, "| %-90s|\n", "Enjoy!");
    fprintf_s(standard_output, "+-------------------------------------------------------------------------------------------+\n");
}

template <typename T>
void matrix_plus(T** a, T** b, T** c, int n, int pm)
//a+b=c
{
    int i, j;
    T ppmm;
    if (std::is_same<decltype(ppmm), cd>::value)
    {
        ppmm = cd(1.0 * pm, 0.0);
    }
    else
    {
        ppmm = 1.0 * pm;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + (ppmm * b[i][j]);
        }
    }
}
template <typename T>
void matrix_product(T** a, T** b, T** c, int n)
//a*b = c
{
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            c[i][j] = 0.0;
            for (k = 0; k < n; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}
template <typename T>
void matrix_plus3(T** a, int pm_ab, T** b, int pm_bc, T** c, T** d, int n)
//a(+-)b(+-)c=d
{
    int i, j;
    T ppmm1, ppmm2;
    if (std::is_same<decltype(ppmm1), cd>::value)
    {
        ppmm1 = cd(1.0 * pm_ab, 0.0);
    }
    else
    {
        ppmm1 = 1.0 * pm_ab;
    }

    if (std::is_same<decltype(ppmm2), cd>::value)
    {
        ppmm2 = cd(1.0 * pm_bc, 0.0);
    }
    else
    {
        ppmm2 = 1.0 * pm_bc;
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            d[i][j] = a[i][j] + (ppmm1 * b[i][j]) + (ppmm2 * c[i][j]);
        }
    }
}

vector_d cross_product(vector_d a, vector_d b)
{
    vector_d c;
    c.x = a.y * b.z - a.z * b.y;  //xyz
    c.y = a.z * b.x - a.x * b.z;  //yzx
    c.z = a.x * b.y - a.y * b.x;  //zxy
    return c;
}
void vector_mag(vector_d* r, double* r_mag)
{
    r_mag[0] = sqrt(r[0].x * r[0].x + r[0].y * r[0].y + r[0].z * r[0].z);
    r_mag[1] = sqrt(r[1].x * r[1].x + r[1].y * r[1].y + r[1].z * r[1].z);
    r_mag[2] = sqrt(r[2].x * r[2].x + r[2].y * r[2].y + r[2].z * r[2].z);
}
double cal_volume(vector_d a1, vector_d a2, vector_d a3)
{
    vector_d temp_a;
    double temp_volume;
    temp_a.x = 0.0; temp_a.y = 0.0; temp_a.z = 0.0;
    temp_a = cross_product(a1, a2);
    temp_volume = temp_a.x * a3.x + temp_a.y * a3.y + temp_a.z * a3.z;
    return temp_volume;
}
void cal_Reciprocal(vector_d* a, vector_d* b)
{
    double volume;
    int i;
    double pi;
    pi = 4.0 * atan(1.0);
    volume = cal_volume(a[0], a[1], a[2]);
    b[0] = cross_product(a[1], a[2]);
    b[1] = cross_product(a[2], a[0]);
    b[2] = cross_product(a[0], a[1]);
    for (i = 0; i < 3; i++)
    {
        b[i].x = b[i].x * (2.0 * pi) / volume;
        b[i].y = b[i].y * (2.0 * pi) / volume;
        b[i].z = b[i].z * (2.0 * pi) / volume;
    }
}
double vector_len(vector_d head, vector_d tail)
{
    double length;
    length = sqrt((tail.x - head.x) * (tail.x - head.x) + (tail.y - head.y) * (tail.y - head.y) + (tail.z - head.z) * (tail.z - head.z));
    return length;
}

template <typename T>
void copy_matrix(T** a, T** b, int n)
//a->b
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}

int cd_matrix_conj(cd** a, cd** b, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            b[i][j] = conj(a[j][i]);
        }
    }
    return 0;
}


template <typename T>
void matrix_transposition(T** a, T** b, int n)
//b = A^T
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            b[i][j] = a[j][i];
        }
    }

}

//template <typename T>
//void direct_product( T alpha, T **a, int ra, int ca, T **b, int rb, int cb, T **c )
////alpha * a xO b = c; put b in the should of a
////	[a11 a12 a13]
////a=[a21 a22 a23]
////	[a31 a32 a33]
////	[b11 b12 b13]
////b=[b21 b22 b23]
////	[b31 b32 b33]
////a xO b = c
////	[a11*b a12*b a13*b]
////c=[a21*b a22*b a23*b]
////	[a31*b a32*b a33*b]
//{
//    int ia, ja, ib, jb;
//
//    for ( ia = 1; ia <= ra; ia++ )
//    {
//        for ( ja = 1; ja <= ca; ja++ )
//        {
//            for ( ib = 1; ib <= rb; ib++ )
//            {
//                for ( jb = 1; jb <= cb; jb++ )
//                {
//                    c[rb*(ia - 1) + ib][cb*(ja - 1) + jb] = alpha * a[ia][ja] * b[ib][jb]; //https://en.wikipedia.org/wiki/Kronecker_product
//                }
//            }
//        }
//    }
//}

template <typename T>
void direct_product(T alpha, T** a, int ra, int ca, T** b, int rb, int cb, T** c)
//alpha * a xO b = c; put b in the shoulder of a
//
//	[a11 a12 a13]
//a=[a21 a22 a23]
//	[a31 a32 a33]
//
//	[b11 b12 b13]
//b=[b21 b22 b23]
//	[b31 b32 b33]
//
//a xO b = c
//
//	[a11*b a12*b a13*b]
//c=[a21*b a22*b a23*b]
//	[a31*b a32*b a33*b]
{
    int ia, ja, ib, jb;

    for (ia = 0; ia < ra; ia++)
    {
        for (ja = 0; ja < ca; ja++)
        {
            for (ib = 0; ib < rb; ib++)
            {
                for (jb = 0; jb < cb; jb++)
                {
                    c[rb * (ia - 1) + ib][cb * (ja - 1) + jb] = alpha * a[ia][ja] * b[ib][jb]; //https://en.wikipedia.org/wiki/Kronecker_product
                }
            }
        }
    }
}

int RoundOff_double2int(double x)
{
    int y;


    if (fabs(x) < 1e-10)
    {
        return 0;
    }

    if (x > 0.0)
    {
        if (((int(1.5)) == 1) && (int(1.4) == 1))
        {
            y = int(x + 0.5);
            return y;
        }
        else if ((int(1.5) == 2) && (int(1.4) == 1))
        {
            y = int(x);
            return y;
        }
        else if (((int(1.5)) == 2) && ((int(1.4)) == 2))
        {
            y = int(x - 0.5);
            return y;
        }
        else
        {
            fprintf_s(stdout, "error in ``RoundOff_double2int'', I cannot determine what happen!\n");
            fprintf_s(stdout, "which value do you want 1.5 ~= ? and 1.4 ~= ?\n");
            exit(2);
        }
    }
    else if (x < 0.0)
    {
        if (((int(-1.5)) == -1) && (int(-1.4) == -1))
        {
            //y = int(fabs(x)/x * (fabs(x) + 0.5));
            y = int(x - 0.5);
            return y;
        }
        else if ((int(-1.5) == -2) && (int(-1.4) == -1))
        {
            y = int(x);
            return y;
        }
        else if (((int(-1.5)) == -2) && ((int(-1.4)) == -2))
        {
            y = int(x + 0.5);
            return y;
        }
        else
        {
            fprintf_s(stdout, "error in ``RoundOff_double2int'', I cannot determine what happen!\n");
            fprintf_s(stdout, "which value do you want 1.5 ~= ? and 1.4 ~= ?\n");
            exit(2);
        }
    }
    return NULL;
}

void vector_2_tensor(int i, int fatest, int normals, int* out_fatest, int* out_middle, int* out_lowest)
{
    //begin from 1
    int j;
    (*out_lowest) = (i - 1) / (normals * fatest) + 1;
    j = (i - 1) % (normals * fatest) + 1;
    (*out_middle) = (j - 1) / fatest + 1;
    (*out_fatest) = (j - 1) % fatest + 1;
}

void vector_2_matrix(int i, int fatest, int normals, int* out_fatest, int* out_middle, int* out_lowest)
{
    //begin from 0
    int j;
    (*out_lowest) = i / (normals * fatest);
    j = i % (normals * fatest);
    (*out_middle) = (j - 1) / fatest + 1;
    (*out_fatest) = (j - 1) % fatest + 1;
}

#endif
