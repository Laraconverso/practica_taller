all:
	mkdir -p bin/
	g++ -o bin/factorial factorial/main.cpp

tests: all
	byexample -l shell doctests/factorial.md
