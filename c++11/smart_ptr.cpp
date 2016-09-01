#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <boost/scoped_ptr.hpp>

class Test {
	public:
		Test(int x, std::string name) : m_x(x), m_name(name) {
			std::cout << __FUNCTION__ << std::endl;
		}
		virtual ~Test() {
			std::cout << __FUNCTION__ << std::endl;
		}
	private:
		int m_x;
		std::string m_name;
};

std::ostream& operator << (std::ostream& out, const Test& t) {
	out << "output Test t";
	return out;
}

void test_scoped_ptr() {
	{
		boost::scoped_ptr<Test> t(new Test(1000, "oneooo"));
	}
	std::cout << "outof {} after" << std::endl;
}

void test_auto_ptr() {
}

void test_shared_ptr(std::vector<std::shared_ptr<Test>> &vec) {

	std::shared_ptr<Test> t(new Test(10, "101010")); // work ok
	//std::shared_ptr<Test> t = new Test(10, "101010"); // dont work
	vec.push_back(t);
}

int main() {
	std::cout << "/**********scoped_ptr***************/" << std:: endl;
	test_scoped_ptr();

	std::cout << "/***********auto_ptr****************/" << std:: endl;

	std::cout << "/**********shared_ptr***************/" << std:: endl;
	std::vector<std::shared_ptr<Test>> vec;
	test_shared_ptr(vec);

	for (auto t : vec) {
		std::cout << *t << std::endl;
	}

	return 0;
}
