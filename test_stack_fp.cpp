#include <iostream>
#include <stack>
#include <string>

class MyClass
{
private:
	void hello();
	void bye();

public:
	MyClass();
};

void MyClass::hello() { std::cout << "hello" << std::endl; }

void MyClass::bye() { std::cout << "bye" << std::endl; }

MyClass::MyClass()
{
	typedef void (MyClass::*FuncPointer)(void);
	std::stack<FuncPointer> st;

	st.push(&MyClass::bye);
	st.push(&MyClass::hello);
	(this->*st.top())();
}

int main() { MyClass a; }