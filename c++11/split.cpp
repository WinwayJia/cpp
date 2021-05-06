#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split_array(const string& str, char sep, vector<string>& vec) {
    size_t liPos = 0;
    size_t liPrePos = 0;
    vec.clear();
    do {
        liPos = str.find_first_of(sep, liPrePos);
        vec.push_back(str.substr(liPrePos, liPos - liPrePos));
        liPrePos = liPos + 1;
    } while (string::npos != liPos);
}

int main() {
    string str = "123";
    vector<string> vec;
    split_array(str, ',', vec);

    for (vector<string>::iterator iter = vec.begin(); iter != vec.end();
         iter++) {
        cout << *iter << endl;
    }
}
