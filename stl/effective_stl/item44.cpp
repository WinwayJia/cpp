// 尽量用成员函数代替同名的算法
/*
这样做有两个理由。
首先，成员函数更快。
其次，比起算法来，它们与容器结合得更好（尤其是关联容器）。那是因为同名的算法和成员函数通常并不是是一样的。
*/
#include <iostream>
#include <set>
#include <algorithm>
#include <sys/time.h>

int duration(struct timeval *tp) {
    struct timeval now;
    gettimeofday(&now, NULL);
    if (now.tv_usec < tp->tv_usec) {
        now.tv_usec += 1000000;
    }
    printf("%d.%06d\n", now.tv_sec - tp->tv_sec, now.tv_usec - tp->tv_usec);

}

// 
void test_find() {
    std::set<int>  s;
    for (int i=0; i<1000000; ++i) {
        s.insert(i);
    }
    struct timeval start;

    gettimeofday(&start, NULL);
    auto it = s.find(74560);
    duration(&start);
    std::cout << *it << std::endl;

    gettimeofday(&start, NULL);
    it = find(s.begin(), s.end(), 74560);
    duration(&start);
    std::cout << *it << std::endl;
}

int main(int argc, char** argv) {

    test_find();

    return 0;
}
