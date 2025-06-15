#pragma once
FILE *open_read( char *filename )
{
    FILE *fp;
#ifdef _win_intel_swj
    if ( (fopen_s( &fp, filename, "r" )) != 0 )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        pause_when_error();
        return NULL;
    }
#endif
#ifdef _linux_intel_swj
    if ( (fp = fopen( filename, "r" )) == NULL )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        return NULL;
    }
#endif
    return fp;
}
FILE *open_write( char *filename )
{
    FILE *fp;
#ifdef _win_intel_swj
    if ( (fopen_s( &fp, filename, "w" )) != 0 )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        pause_when_error();
        return NULL;
    }
#endif
#ifdef _linux_intel_swj
    if ( (fp = fopen( filename, "w" )) == NULL )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        return NULL;
    }
#endif
    return fp;
}

FILE *open_readb( char *filename )
{
    FILE *fp;
#ifdef _win_intel_swj
    if ( (fopen_s( &fp, filename, "rb" )) != 0 )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        pause_when_error();
        return NULL;
    }
#endif
#ifdef _linux_intel_swj
    if ( (fp = fopen( filename, "rb" )) == NULL )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        return NULL;
    }
#endif
    return fp;
}
FILE *open_writeb( char *filename )
{
    FILE *fp;
#ifdef _win_intel_swj
    if ( (fopen_s( &fp, filename, "wb" )) != 0 )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        pause_when_error();
        return NULL;
    }
#endif
#ifdef _linux_intel_swj
    if ( (fp = fopen( filename, "wb" )) == NULL )
    {
        fprintf_s( stdout, "Cannot open %s!\n", filename );
        return NULL;
    }
#endif
    return fp;
}
