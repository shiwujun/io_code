// test-fwrite-complex.cpp : Defines the entry point for the console application.
//
#define _linux_intel_swj
//#define _win_intel_swj
#define _pause_when_error_swj
#define _swj_debug

#include <mpi.h>
#include <mkl.h>
#include "swj_v1.0.h"
#include "file_v1.0.h"
#include "malloc_v2.0.h"


//below to define the site number of one file
#define __lie 1
//above to define the site number of one file

//below to define the number of file
#define file_num_set 10
//above to define the number of file

//output block size in MB
//change this
#define _output_block 4

//if define _buffer_define, set the size of buffer in MB
//#define _buffer_size_set 16

static int get_system_output(char* cmd, char* output, int size)
{
    FILE* fp = NULL;
    int offset = 0;
    fp = popen(cmd, "r");
    if (fp)
    {
        while (fgets(output + offset, size, fp) != NULL)
        {
            int len = strlen(output + offset);
            offset += len;
        }
    }
    pclose(fp);
    return 0;
}

int main(int argc, char* argv[])
{
    // constant
    int B2kB = 1024;
    int kB2MB = 1024;
    int MB2GB = 1024;
    int GB2TB = 1024;

    //mpi part
    int process_id, tot_process, host_name_len;
    char host_name[MPI_MAX_PROCESSOR_NAME];
    int loop_pid;
    int root_pid = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &tot_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Get_processor_name(host_name, &host_name_len);

    //on each process
    long _1line = B2kB * kB2MB * MB2GB;//1G sits in one direction
    long _lie = __lie; //another direction
    __int64 total_site_num = (__int64)_1line * _lie;
    double* data_1d;
    Tx_1D(&data_1d, total_site_num);
    double total_size = (1.0 * total_site_num) / (1.0 * B2kB * kB2MB * MB2GB) * sizeof(double); //size in memory (GB)

    //for output
    int one_output = _output_block * B2kB * kB2MB;
    int num_output = total_site_num * sizeof(data_1d[0]) / one_output;

    //record the system time
    char command_time[1000] = { " " };
    char command_line[] = { "date" };

    if (process_id == root_pid)
    {
        fprintf_s(stdout, "sizeof(int) = %ld, sizeof(long) = %ld, sizeof(long long) = %ld, sizeof(MKL_INT) = %ld, sizeof(__int64) = %ld\n", sizeof(int), sizeof(long), sizeof(long long), sizeof(MKL_INT), sizeof(__int64));
        fprintf_s(stdout, "%-20.6lf GB size of file will be allocated at each process.\n", total_size);
        fprintf_s(stdout, "size of one_output       = %d\n", one_output);
        fprintf_s(stdout, "size of num_output       = %d\n", num_output);
        fprintf_s(stdout, "size of total_num in num = %lld\n", total_site_num);
        fprintf_s(stdout, "size of total_num in vol = %lld\n", total_site_num * 8);
    }

    //write log files in each process
    FILE* write_log;
    char filename_log[1000] = { " " };
    sprintf_s(filename_log, "output_log_%d.txt", process_id);
    write_log = open_write(filename_log);
    if (write_log == NULL)
    {
        fprintf_s(stderr, "cannot create %s..\n", filename_log);
        pause_when_error();
        return 2;
    }
    fprintf_s(stdout, "pid %d of %d is on %s\n", process_id, tot_process - 1, host_name);
    fprintf_s(write_log, "pid %d of %d is on %s\n", process_id, tot_process - 1, host_name);

    MPI_Barrier(MPI_COMM_WORLD); //waiting for every process

    //begin write the system time
    fprintf_s(stdout, "===============================================\tat pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "===============================================\tat pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(stdout, "begin  initial the 1D vector at pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "begin  initial the 1D vector at pid: %d of %d... \t|\t", process_id, tot_process - 1);
#ifdef _win_intel_swj
    system("echo %date% %time%");
#else
    get_system_output(command_line, command_time, 1000);
    fprintf_s(write_log, "%s", command_time);
#endif
    fflush(write_log);
    //end write the system time

    //initial the memory
    //srand((unsigned)time(NULL));
    //for (__int64 loop_x=0; loop_x< total_site_num; loop_x++)
    //{
    //    x_1d_each_process[loop_x] = rand();
    //}

    for (__int64 loop_x = 0; loop_x < total_site_num; loop_x++)
    {
        data_1d[loop_x] = 0.0;
    }

    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_SFMT19937, process_id);
    vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD_ACCURATE, stream, total_site_num, data_1d, 0.0, 10000.0);
    vslDeleteStream(&stream);

    //begin write the system time
    fprintf_s(stdout, "finish initial the 1D vector at pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "finish initial the 1D vector at pid: %d of %d... \t|\t", process_id, tot_process - 1);
#ifdef _win_intel_swj
    system("echo %date% %time%");
#else
    get_system_output(command_line, command_time, 1000);
    fprintf_s(write_log, "%s", command_time);
#endif
    fprintf_s(stdout, "===============================================\tat pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "===============================================\tat pid: %d of %d...\n", process_id, tot_process - 1);
    //end write the system time

    MPI_Barrier(MPI_COMM_WORLD);
    fprintf_s(stdout, "\n");
    fprintf_s(write_log, "\n");
    fflush(write_log);

    FILE* write_dat;
    char filename_dat[1000] = { " " };
    unsigned int seed; 
    for (int loop_file = 0; loop_file < file_num_set; loop_file++)
    {
        fprintf_s(stdout, "begin  initial the 1D vector at pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fprintf_s(write_log, "begin  initial the 1D vector at pid: %d of %d in loop %d ...           \t|\t", process_id, tot_process - 1, loop_file);
#ifdef _win_intel_swj
        system("echo %date% %time%");
#else
        get_system_output(command_line, command_time, 1000);
        fprintf_s(write_log, "%s", command_time);
#endif
        fflush(write_log);

        seed = process_id + loop_file;
        VSLStreamStatePtr stream;
        vslNewStream(&stream, VSL_BRNG_SFMT19937, seed);
        vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD_ACCURATE, stream, total_site_num, data_1d, 0.0, 10000.0);
        vslDeleteStream(&stream);

        fprintf_s(stdout, "finish initial the 1D vector at pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fprintf_s(write_log, "finish initial the 1D vector at pid: %d of %d in loop %d ...           \t|\t", process_id, tot_process - 1, loop_file);
#ifdef _win_intel_swj
        system("echo %date% %time%");
#else
        get_system_output(command_line, command_time, 1000);
        fprintf_s(write_log, "%s", command_time);
#endif
        fflush(write_log);

        sprintf_s(filename_dat, "output_pid-%d_file-%d.bin", process_id, loop_file);
        write_dat = open_writeb(filename_dat);
        if (write_dat == NULL)
        {
            fprintf_s(stderr, "cannot create %s..\n", filename_dat);
            pause_when_error();
            return 2;
        }

        //writing data to files
        fprintf_s(stdout, "begin  writing               at pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fprintf_s(write_log, "begin  writing               at pid: %d of %d in loop %d ...           \t|\t", process_id, tot_process - 1, loop_file);
#ifdef _win_intel_swj
        system("echo %date% %time%");
#else
        get_system_output(command_line, command_time, 1000);
        fprintf_s(write_log, "%s", command_time);
#endif
        fflush(write_log);

        fwrite(data_1d, one_output, num_output, write_dat);

        fflush(write_dat);
        fprintf_s(stdout, "finish writing               at pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fprintf_s(write_log, "finish writing               at pid: %d of %d in loop %d ...           \t|\t", process_id, tot_process - 1, loop_file);
#ifdef _win_intel_swj
        system("echo %date% %time%");
#else
        get_system_output(command_line, command_time, 1000);
        fprintf_s(write_log, "%s", command_time);
#endif
        fprintf_s(stdout, "===============================================\tat pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fprintf_s(write_log, "===============================================\tat pid: %d of %d in loop %d...\n", process_id, tot_process - 1, loop_file);
        fflush(write_log);
        fclose(write_dat);
    }


    //deleting allocated memory
    fprintf_s(stdout, "begin  deleting the 1D vector at pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "begin  deleting the 1D vector at pid: %d of %d... \t|\t", process_id, tot_process - 1);
#ifdef _win_intel_swj
    system("echo %date% %time%");
#else
    get_system_output(command_line, command_time, 1000);
    fprintf_s(write_log, "%s", command_time);
#endif
    fflush(write_log);

    delete_Tx_1D(data_1d, total_site_num);//deleting mem

    fprintf_s(stdout, "finish deleting the 1D vector at pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "finish deleting the 1D vector at pid: %d of %d... \t|\t", process_id, tot_process - 1);
#ifdef _win_intel_swj
    system("echo %date% %time%");
#else
    get_system_output(command_line, command_time, 1000);
    fprintf_s(write_log, "%s", command_time);
#endif
    fflush(write_log);

    if (process_id==root_pid)
    {
        fprintf_s(stdout, "finished\n");
        fflush(stdout);
    }

    fprintf_s(stdout, "finished at pid: %d of %d...\n", process_id, tot_process - 1);
    fprintf_s(write_log, "finished at pid: %d of %d... \t|\t", process_id, tot_process - 1);
#ifdef _win_intel_swj
    system("echo %date% %time%");
#else
    get_system_output(command_line, command_time, 1000);
    fprintf_s(write_log, "%s", command_time);
#endif

    fclose(write_log);

    MPI_Finalize();
    return 0;
}

