EXE = bench_mpi bench_barrier
CXX = mpicxx

all: $(EXE)

%: %.cxx
	$(CXX) -o $@ -O3 $<

clean:
	rm -f $(EXE)
