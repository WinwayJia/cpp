#include <iostream>
using namespace std;

class ParseNumberH3 {
    public:
        ParseNumberH3() {
        }
        ParseNumberH3(string strNumberH3) : m_strNumberH3(strNumberH3) {
            m_iNumberH3Size = m_strNumberH3.size(); 
        }
        void setNumberH3(string strNumberH3) {
            m_strNumberH3 = strNumberH3;
            m_iNumberH3Size = m_strNumberH3.size(); 
        }

        string getNetNo() const {
            return m_strNumberH3.substr(0, m_iNumberH3Size-4);
        }

        char getH0() const {
            return m_strNumberH3.at(m_iNumberH3Size-4);
        }
        char getH1() const {
            return m_strNumberH3.at(m_iNumberH3Size-3);
        }
        char getH2() const {
            return m_strNumberH3.at(m_iNumberH3Size-2);
        }
        char getH3() const {
            return m_strNumberH3.at(m_iNumberH3Size-1);
        }
        string getH0H1H2H3() const {
            return m_strNumberH3.substr(m_iNumberH3Size-4, 4);
        }

        string getStringByIndex(int start, int length) const {
            return m_strNumberH3.substr(start, length);
        }

    private:
        string m_strNumberH3;
        size_t m_iNumberH3Size;
};

int main(int argc, char** argv) {
    ParseNumberH3 pn;
    for (int i=1; i<argc; i++) {
        pn.setNumberH3(argv[i]);
        cout << pn.getNetNo() << endl;
        cout << pn.getH0() << endl;
        cout << pn.getH1() << endl;
        cout << pn.getH2() << endl;
        cout << pn.getH3() << endl;
        cout << pn.getH0H1H2H3() << endl << endl;;
    }
    
    return 0;
}
