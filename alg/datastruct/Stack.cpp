#include <iostream>
#include <string.h>

using namespace std;

template <class T>
class Stack {
    public:
        Stack(size_t size=64):m_size(size), m_count(0) {
            m_base = new T[64];
            if (!m_base) {
            }
            m_top = m_base;

        }

        ~Stack() {
            if (m_base) {
                delete[] m_base;
            }
        }

        void Push(T &t) {
            if (m_count == m_size) {
                T* tmp = new T[m_size*3/2]; 
                if (!tmp) {
                    //throw ;
                    return ;
                }
                memcpy(tmp, m_base, sizeof(T)*m_count);
                m_base = tmp;
                m_top = m_base + sizeof(T)*m_count;
            }

            *m_top = t;
            m_top ++;
            m_count ++;
            m_size = m_size*3/2;
        }

        T Pop() {
            m_top --;
            return *m_top;
        }

    private:
        void init() {

        }

        T   *m_base;
        T   *m_top;
        size_t m_count;
        size_t m_size;
};

int main(int argc, char** argv) {

    Stack<int> testStack;

    for (int i=0; i<10; ++i) {
        testStack.Push(i);
    }
    
    for (int i=0; i<10; ++i) {
        cout << testStack.Pop() << endl;
    }

    return 0;
}
