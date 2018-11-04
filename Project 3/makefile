in2post.x: in2post.cpp stack.hpp stack.x
	g++ in2post.cpp -o in2post.x -std=c++11

stack.x: stack.h test_stack1.cpp
	g++ -o stack.x stack.h test_stack1.cpp -std=gnu++11

clean:
	rm -f *.x stack
