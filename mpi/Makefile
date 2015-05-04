EXE = bench_mpi bench_barrier
CXX = mpicxx

%: %.cxx
	$(CXX) -o $@ -O3 $<

bench: $(EXE)
	bash bench.sh

clean:
	rm -f $(EXE)
