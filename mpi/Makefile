EXE = bench_mpi
SRC = bench_mpi.cxx
CXX = mpicxx

$(EXE): $(SRC)
	$(CXX) -o $@ -O3 $<

bench: $(EXE)
	bash bench.sh

clean:
	rm -f $(EXE)
