all: main

EXE = greet
CXX = clang++

greet.o: greet.cxx
	$(CXX) -c $< -stdlib=libstdc++

main.o: main.cxx
	$(CXX) -c $< -stdlib=libstdc++

main: main.o greet.o
	$(CXX) -o $(EXE) $^ -stdlib=libstdc++

clean:
	rm -f *.o $(EXE)
