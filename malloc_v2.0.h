#pragma once
#ifndef _MALLOC_swj
#define _MALLOC_swj

int type_int_swj;
long type_long_swj;
float type_float_swj;
double type_double_swj;
cd type_cd_swj;

//a[i][j][k][l]
//a[slowest][normal][fast][fastest]

template <typename T>
T *T_1D ( T *swj_type, __int64 row )
{
    T *a;
    a = new T[row];
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T[row];'' in ``T *T_1D ( T *, __int64 row )''" );
        pause_when_error();
        exit ( 2 );
    }
    return a;
}
template <typename T>
void delete_T_1D( T *a, __int64 row )
{
    delete[] a;
    a = NULL;
}

template <typename T>
T **T_2D( T *swj_type, __int64 row, __int64 column )
{
    T **a;
    int i;
    a = new T *[row];
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T *[row];'' in ``T **T_2D( T**, __int64 row, __int64 column )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < row; i++ )
    {
        a[i] = new T[column];
        if ( !a[i] )
        {
            fprintf_s( stderr, "error of ``a[%5d] = new T[column];'' in ``T **T_2D( T**, __int64 row, __int64 column )''\n", i );
            pause_when_error();
            exit ( 2 );
        }
    }
    return a;
}
template <typename T>
void delete_T_2D( T **a, __int64 row, __int64 column )
{
    int i;
    for ( i = 0; i < row; i++ )
    {
        delete[] a[i];
        a[i] = NULL;
    }
    delete[] a;
    a = NULL;
}

template <typename T>
T ***T_3D( T *swj_type, __int64 row, __int64 column, __int64 height )
{
    T ***a;
    int i, j;

    a = new T **[height]; //point to every layer
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T **[height];'' in ``T ***T_3D( T*** __int64 row, __int64 column, __int64 height )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < height; i++ )
    {
        a[i] = new T *[row]; //point to every row
        if ( !a[i] )
        {
            fprintf_s( stderr, "error of ``a[%5d] = new T *[row];'' in ``T ***T_3D( T*** __int64 row, __int64 column, __int64 height )''\n", i );
            pause_when_error();
            exit ( 2 );
        }
        for ( j = 0; j < row; j++ )
        {
            a[i][j] = new T[column];
            if ( !a[i][j] )
            {
                fprintf_s( stderr, "error of ``a[%5d][%5d] = new T[column];'' in ``T ***T_3D( T*** __int64 row, __int64 column, __int64 height )''\n", i, j );
                pause_when_error();
                exit ( 2 );
            }
        }
    }
    return a;
}
template <typename T>
void delete_T_3D( T ***a, __int64 row, __int64 column, __int64 height )
{
    int i, j;
    for ( i = 0; i < height; i++ )
    {
        for ( j = 0; j < row; j++ )
        {
            delete[] a[i][j];
            a[i][j] = NULL;
        }
        delete[] a[i];
        a[i] = NULL;
    }
    delete[] a;
    a = NULL;
}

template <typename T>
void Tx_1D ( T **a, __int64 row )
{
    (*a) = new T[row];
    if ( !(*a) )
    {
        fprintf_s( stderr, "error of ``(*a) = new T[row];'' in ``void *Tx_1D ( T **a __int64 row )''" );
        pause_when_error();
        exit ( 2 );
    }
}
template <typename T>
void delete_Tx_1D( T *a, __int64 row )
{
    delete[] a;
    a = NULL;
}

template <typename T>
void Tx_2D( T ***a, __int64 row, __int64 column )
{
    int i;
    (**a) = new T *[row];
    if ( !(**a) )
    {
        fprintf_s( stderr, "error of ``(**a) = new T *[row];'' in ``void Tx_2D( T ***a __int64 row, __int64 column )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < row; i++ )
    {
        (*a[i]) = new T[column];
        if ( !(*a[i]) )
        {
            fprintf_s( stderr, "error of ``(*a[i]) = new T[column];'' in ``void Tx_2D( T ***a __int64 row, __int64 column )''\n" );
            pause_when_error();
            exit ( 2 );
        }
    }
}
template <typename T>
void delete_Tx_2D( T **a, __int64 row, __int64 column )
{
    int i;
    for ( i = 0; i < row; i++ )
    {
        delete[] a[i];
        a[i] = NULL;
    }
    delete[] a;
    a = NULL;
}

template <typename T>
void Tx_3D( T ****a, __int64 row, __int64 column, __int64 height )
{
    int i, j;

    (***a) = new T **[height]; //point to every layer
    if ( !(***a) )
    {
        fprintf_s( stderr, "error of ``(***a) = new T **[height];'' in ``void Tx_3D( T ****a, __int64 row, __int64 column, __int64 height )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < height; i++ )
    {
        (**a[i]) = new T *[row]; //point to every row
        if ( !(**a[i]) )
        {
            fprintf_s( stderr, "error of ``(**a[i]) = new T *[row];'' in ``void Tx_3D( T ****a, __int64 row, __int64 column, __int64 height )''\n" );
            pause_when_error();
            exit ( 2 );
        }
        for ( j = 0; j < row; j++ )
        {
            (*a[i][j]) = new T[column];
            if ( !(*a[i][j]) )
            {
                fprintf_s( stderr, "error of ``(*a[i][j]) = new T[column];'' in ``void Tx_3D( T ****a, __int64 row, __int64 column, __int64 height )''\n" );
                pause_when_error();
                exit ( 2 );
            }
        }
    }
    return a;
}
template <typename T>
void delete_Tx_3D( T ***a, __int64 row, __int64 column, __int64 height )
{
    int i, j;
    for ( i = 0; i < height; i++ )
    {
        for ( j = 0; j < row; j++ )
        {
            delete[] a[i][j];
            a[i][j] = NULL;
        }
        delete[] a[i];
        a[i] = NULL;
    }
    delete[] a;
    a = NULL;
}

template <typename T>
T *convert_T1D( T *x, __int64 size)
{
    T *a;
    int i;
    &a[0] = &x[0];
    return a;
}
template <typename T>
void delete_convert_1D( T **a, __int64 size )
{
    delete[] a;
    a = NULL;
}

template <typename T>
T **convert_T2D( T *x, __int64 normal, __int64 fast )
{
    T **a;
    int i;
    a = new T *[normal];
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T *[row];'' in ``T **convert_T2D( T *x, __int64 row, __int64 column )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < normal; i++ )
    {
        a[i] = x + i*fast;
    }
    return a;
}
template <typename T>
void delete_convert_2D( T **a, __int64 normal, __int64 fast )
{
    delete[] a;
    a = NULL;
}

template <typename T>
T ***convert_T3D( T *x, __int64 slow, __int64 normal, __int64 fast )
{
    T ***a;
    int i, j;

    a = new T **[slow]; //point to every layer
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T **[height];'' in ``T ***convert_T3D( T *x, __int64 row, __int64 column, __int64 height )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < slow; i++ )
    {
        a[i] = new T *[normal]; //point to every row
        if ( !a[i] )
        {
            fprintf_s( stderr, "error of ``a[%5d] = new T *[row];'' in ``T ***convert_T3D( T *x, __int64 row, __int64 column, __int64 height )''\n", i );
            pause_when_error();
            exit ( 2 );
        }
       for ( j = 0; j < normal; j++ )
        {
            a[i][j] = x + i*normal*fast + j*fast;
        }
    }
    return a;
}
template <typename T>
void delete_convert_3D( T ***a, __int64 slow, __int64 normal, __int64 fast )
{
    delete[] a;
    a = NULL;
}


template <typename T>
T ****convert_T4D( T *x, __int64 slowest, __int64 slow, __int64 normal, __int64 fast )
{
    T ****a;
    int i, j, k;

    a = new T ***[slowest]; //point to every stack, i.e., slowest
    if ( !a )
    {
        fprintf_s( stderr, "error of ``a = new T ***[slowest];'' in ``T ****convert_T4D( T *x, __int64 fast, __int64 normal, __int64 slow, __int64 slowest )''\n" );
        pause_when_error();
        exit ( 2 );
    }
    for ( i = 0; i < slowest; i++ )
    {
        a[i] = new T **[slow]; //point to every layer
        if ( !a[i] )
        {
            fprintf_s( stderr, "error of ``a = new T **[slow];'' in ``T ****convert_T4D( T *x, __int64 fast, __int64 normal, __int64 slow, __int64 slowest )''\n" );
            pause_when_error();
            exit ( 2 );
        }
        for ( j = 0; j < slow; j++ )
        {
            a[i][j] = new T *[normal]; //point to every row
            if (!a[i][j])
            {
                fprintf_s( stderr, "error of ``a[i][j] = new T *[normal];'' in ``T ****convert_T4D( T *x, __int64 fast, __int64 normal, __int64 slow, __int64 slowest )''\n" );
            }
            for ( k = 0; k < normal; k++ )
            {
                a[i][j][k] = x + i*slow*normal*fast + j*normal*fast + k*fast;
            }
        }
    }
    return a;
}
template <typename T>
void delete_convert_4D( T ****a, __int64 slowest, __int64 slow, __int64 normal, __int64 fast )
{
    delete[] a;
    a = NULL;
}
#endif
