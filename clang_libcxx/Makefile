all: main

EXE = greet
CXX = clang++

greet.o: greet.cxx
	$(CXX) -c $< -stdlib=libc++

main.o: main.cxx
	$(CXX) -c $< -stdlib=libc++

main: main.o greet.o
	$(CXX) -o $(EXE) $^ -stdlib=libc++

clean:
	rm -f *.o $(EXE)
