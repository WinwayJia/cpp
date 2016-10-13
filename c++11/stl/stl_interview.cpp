#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void print(int x) {
    cout << x << endl;
}

bool too_big(int x) {
    return x > 3;
}

void remove_elements() {
    // vector
    vector<int> vec = {5, 3, 2, 8, 1, 9};
    /*
    for (auto it = vec.begin(); it != vec.end(); ) {
        if (*it > 3) {
            cout << " vector remove " << *it << endl;
            it = vec.erase(it);
        } else {
            ++ it;
        }
    }
    */
    // 利用算法库 vector
    vec.erase(remove_if(vec.begin(), vec.end(), too_big), vec.end());
    for_each(vec.begin(), vec.end(), print);

    // list
    list<int> ll = {5, 3, 2, 8, 1, 9};
    for (auto it = ll.begin(); it != ll.end(); ) {
        if (*it > 3) {
            cout << " list remove " << *it << endl;
            it = ll.erase(it);
        } else {
            ++ it;
        }
    }

    // map
    map<int, string> mm;
    mm[8] = "8";
    mm[3] = "3";
    mm[2] = "2";
    mm[9] = "9";

    for (auto it = mm.begin(); it != mm.end(); ) {
        if (it->first > 5) {
            cout << " map remove " << it->first << " " << it->second << endl;
//            it = mm.erase(it);  // ok
            mm.erase(it++); // 在进入erase之前，传入it的拷贝副本，it自身++，所以此处OK
        } else {
            ++ it;
        }
    }
    remove(ll.begin(), ll.end(), 8);
//    remove(mm.begin(), mm.end(), 8);  // error

}

// iterator 在insert后失效测试
void iter_after_insert() {
    map<int, string> mm;
    mm[8] = "8";
    mm[3] = "3";
    mm[2] = "2";
    mm[9] = "9";
    
    auto it = mm.begin();
    mm[1] = "1";
    for ( ; it != mm.end(); ++it) {
        cout << "iter after insert " << it->first << " " << it->second << endl;
    }
}


// set, multiset, map[key] 不可修改
void const_value() {
    set<int> ss;
    ss.insert(8);
    ss.insert(3);
    ss.insert(2);
    ss.insert(9);

    set<int>::iterator it = ss.find(3);
//    *it = 20;  // error

    // map
    map<int, string> mm; 
    mm[8] = "8";
    mm[3] = "3";
    mm[2] = "2";
    mm[9] = "9";
    auto iter = mm.find(3);
    iter->second = "33";
//    iter->first = 4;
}

int main(int argc, char** argv) {
    remove_elements();
//    iter_after_insert();
}
