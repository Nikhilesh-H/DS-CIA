test:
	g++ tests/test_treap.cpp -o test_treap -lgtest -lgtest_main -Itreap
	./test_treap
