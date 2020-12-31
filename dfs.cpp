#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <stack>

struct Node {
    Node(char val, std::vector<char> links) : val_(val), links_(links){}
    char val_;
    std::vector<char> links_;
};

bool dfs(std::map<char, Node>& maps, char begin, char end, std::set<char>& visited, std::deque<char>& path) {
    path.push_back(begin);
    if (begin == end) {
        return true;
    }

    if (visited.find(begin) != visited.end()) {
        return false;
    }
    visited.insert(begin);

    auto iter = maps.find(begin);
    if (iter == maps.end()) {
        return false;
    }

    for (auto& x : iter->second.links_) {
        auto iter = visited.find(x);
        if (iter == visited.end()) {
            if (dfs(maps, x, end, visited, path)) {
                return true;
            }
        }
    }
    path.pop_back();

    return false;
}

bool dfs(std::map<char, Node>& maps, char begin, char end, std::deque<char>& path) {
    if (begin == end) {
        return true;
    }

    auto iter = maps.find(begin);
    if (iter == maps.end()) {
        return false;
    }

    std::set<char> visited;
    std::stack<std::map<char, Node>::const_iterator> st;
    st.push(iter);
    visited.insert(begin);

    while (!st.empty()) {
        auto node = st.top();
        st.pop();
        for (auto x : node->second.links_) {
            if (x == end) {
                return true;
            }
            auto it = maps.find(x);
            if (it == maps.end()) {
                continue;
            }

            auto res = visited.insert(x);
            if (res.second) {
                st.push(it);
            }
        }
    }

    return false;
}

int main() {
    std::map<char, Node> maps = {
        {'a', Node('a', {'b', 'd', 'e'})},
        {'b', Node('b', {'c', 'f'})},
        {'c', Node('c', {})},
        {'d', Node('d', {'c', 'e'})},
        {'e', Node('e', {'f', 'g'})},
        {'f', Node('f', {'a'})},
        {'g', Node('g', {})},
    };

    std::set<char> visited;
    std::deque<char> path;
    bool ans = dfs(maps, 'a', 'g', visited, path);
    std::cout << std::boolalpha << ans << std::endl;

    if (!ans) {
        return 0;
    }

    const char* sep = "";
    for (auto x : path) {
        std::cout << sep << x ;
        sep = " => ";
    }
    std::cout << std::endl;

    std::cout << "with stack: " << std::endl;
    ans = dfs(maps, 'a', 'h', path);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
