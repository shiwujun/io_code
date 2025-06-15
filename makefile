in_name=test_fwrite_mpi_v1.x
out_name=test_fwrite_mpi_v1.x
in_SUFFIXES=cpp
out_SUFFIXES=o
final_name=test_fwrite_mpi_v1.x.out

BLAS = ${MKLROOT}/lib/intel64/libmkl_scalapack_lp64.a -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_blacs_intelmpi_lp64.a -Wl,--end-group -lpthread -lm -ldl
LAPACK =
CPP=mpiicpc -static_mpi -qopenmp
FLAGS =
INCS = 
LIB = $(LAPACK) $(BLAS)

GF: $(out_name).$(out_SUFFIXES)
			$(CPP) -o $(final_name) $(out_name).$(out_SUFFIXES) $(INCS) $(LIB)

$(out_name).$(out_SUFFIXES) :  $(in_name).$(in_SUFFIXES)
			$(CPP) -c $(in_name).$(in_SUFFIXES)

clean:
		rm -f $(out_name).$(out_SUFFIXES)


