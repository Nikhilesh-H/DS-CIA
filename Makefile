CXX = g++

build:
	mkdir -p build

test: build
	$(CXX) tests/test_treap.cpp -o build/test_treap -lgtest -lgtest_main -Itreap
	./build/test_treap

format:
	clang-format -i treap/*.cpp treap/*.h veb/*.cpp veb/*.h tests/*.cpp

treap: build
	$(CXX) treap/treap.cpp -o build/treap

veb: build
	$(CXX) veb/veb.cpp -o build/veb

clean:
	rm -rf build
