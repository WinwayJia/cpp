#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class CStack {
    typedef T value_type;
    typedef size_t  size_type;
    public:
        explicit CStack(int size) {
            m_base = (T*)malloc(sizeof(T) * size);
            m_top = m_base;
            m_size = size;
            m_num = 0;
        }
        bool empty () const {
            return m_num == 0;
        }
        size_type size () const {
            return m_num;
        }
        value_type& top() {
            return *(m_top-1);
        }
        const value_type& top () const {
            return *(m_top-1);
        }
        void push (const T& x) {
            if (m_num == m_size) {
                T* tmp = (T*)realloc(m_base, sizeof(T)*2*m_size);
                m_base = tmp;
                m_top = m_base + m_size;
                m_size = 2 * m_size;
            }
            *m_top ++ = x;
            m_num ++;
        }
        void pop () {
            m_top --;
            m_num --;
        }
    private:
        T*          m_base;
        T*          m_top;
        int         m_size;
        int         m_num;
};

#ifdef DEBUG
int main(int argc, char** argv) {
    CStack<int> stack(4);

    for (int i=0; i<100; i++) { 
        stack.push(i);
    }

    while (!stack.empty()) {
        cout << stack.top() << endl;
        stack.pop();
    }

    return 0;
}
#endif
