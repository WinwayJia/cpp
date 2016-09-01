/*
   容器容纳了对象，但不是你给它们的那个对象。此外，当你从容器中获取一个对象时，你所得到的对象不是容器里的那个对象。
   取而代之的是，当你向容器中添加一个对象（比如通过insert或push_back等），进入容器的是你指定的对象的拷贝。拷进去，拷出来。这就是STL的方式。
 */
/* 
   一个使拷贝更高效、正确而且对分割问题免疫的简单的方式是建立指针的容器而不是对象的容器. 指针的容器有它们自己STL相关的头疼问题, 
   如果你想避免这些头疼并且仍要避开效率、正确性和分割问题，你可能会发现智能指针的容器是一个吸引人的选择
 */
#include <iostream>
#include <list>
#include <string.h>
#include <vector>

class SampleClass {
    public:
        SampleClass(int len) {
            std::cout << "constructor" << std::endl;
            m_len = len;
            m_content = new char[m_len];
        }
        ~SampleClass() {
            std::cout << "destructor" << std::endl;
            if (m_content) {
                delete[] m_content;
                m_content = NULL;
            }
        }
        /*
           SampleClass& operator=(const SampleClass &sc) {
           m_len = sc.m_len;
           if (m_content) {
           delete[] m_content;
           m_content = NULL;
           }
           m_content = new char[m_len];
           memcpy(m_content, sc.m_content, m_len);
           }
         */
        SampleClass(const SampleClass &sc) {
            std::cout << "copy constructor" << std::endl;
            m_len = sc.m_len;
            m_content = new char[m_len];
            memcpy(m_content, sc.m_content, m_len);
        }
    private:
    public:
        int         m_len;
        char*       m_content;
};

typedef std::list<SampleClass> SCContainer;
typedef std::list<SampleClass>::iterator SCIterator;
typedef std::list<SampleClass>::const_iterator SCConstIterator;

void test_list(SCContainer& scc) {
    SampleClass sc(10);

    scc.push_back(sc);
}

int main(int argc, char** argv) {
    {
    SCContainer sc;
    test_list(sc);

    for (auto x : sc) {
        std::cout << x.m_len << " " << x.m_content << std::endl;
    }
    }

    std::cout << " test array " << std::endl;
    {
        SampleClass arrSc[10](10);
        std::vector<SampleClass> vecSc;
        vecSc.reserve(10);
    }

}
