EXE = bench_mpi
SRC = bench_mpi.cxx
CXX = mpicxx

$(EXE): $(SRC)
	$(CXX) -o $@ $<

bench: $(EXE)
	bash bench.sh

clean:
	rm -f $(EXE)
