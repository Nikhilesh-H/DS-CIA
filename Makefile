CXX = g++

build:
	mkdir -p build

treap: build
	$(CXX) treap/treap.cpp -o build/treap

veb: build
	$(CXX) veb/veb.cpp -o build/veb

format:
	clang-format -i treap/*.cpp treap/*.h veb/*.cpp veb/*.h tests/*.cpp

test: build
	$(CXX) tests/test_treap.cpp -o build/test_treap -lgtest -lgtest_main -Itreap
	./build/test_treap
	$(CXX) tests/test_veb.cpp -o build/test_veb -lgtest -lgtest_main -Iveb
	./build/test_veb

clean:
	rm -rf build
