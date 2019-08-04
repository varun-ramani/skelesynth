CC := clang++

bin/skelesynth: initbuild build/wave.o build/main.o
	${CC} build/wave.o build/main.o -o bin/skelesynth -Wall

build/wave.o: src/wave.h src/wave.cc
	${CC} -c src/wave.cc -o build/wave.o -Wall

build/main.o: src/main.cc
	${CC} -c src/main.cc -o build/main.o -Wall

initbuild:
	mkdir -p build
	mkdir -p bin

clean:
	rm -rf build bin

run: bin/skelesynth
	./bin/skelesynth
