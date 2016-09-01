#include <utility>
#include <iostream>
#include <iostream>
#include <memory>

using namespace std;

class A
{
	public:
		A() { id = ++count; cout << "create A" << id  <<  "\n"; }
		~A() { cout << "destroy A" << id << "\n"; }
	private:
		static int count;
		int id;
};

int A::count = 0;

/*调用该函数会丢失掉所有权*/
void sink(auto_ptr<A> a)
{
	cout << "Enter sink()\n";
}

/*调用该函数会创建对象，并获取所有权*/
auto_ptr<A> create()
{
	cout << "Enter create()\n";
	auto_ptr<A> a(new A());
	return a;
}


auto_ptr<A> test()
{
	auto_ptr<A> a(NULL);
	return a;
}

int main(int argc, char *argv[])
{
	auto_ptr<A> a1 = create();
	auto_ptr<A> a2 = a1; /*转移所有权，此时a1无效了*/
	auto_ptr<A> a3(new A());
	cout << "Exit create()\n";
	sink(a2);/*丢失所有权，会发现a2的释放在sink函数中进行*/
	cout << "Exit sink()\n";



	auto_ptr<A> t = test();
	cout << "get()=" << t.get() << endl;

	A a[10];
	return 0;
}
