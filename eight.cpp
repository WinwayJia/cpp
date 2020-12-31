#include <iostream>
#include <vector>


bool check(int x, int y, int N, std::vector<std::vector<int>>& matrix) {
    // left up
    int tx = x;
    int ty = y;
    while (tx >=0 && ty >= 0) {
        if (matrix[ty][tx]) {
            return false;
        }
        tx --;
        ty --;
    }
    // right up
    tx = x;
    ty = y;
    while (tx < N && ty >= 0) {
        if (matrix[ty][tx]) {
            return false;
        }
        tx ++;
        ty --;
    }
    // up
    ty = y;
    while (ty >= 0) {
        if (matrix[ty][x]) {
            return false;
        }
        ty --;
    }
    
    return true;
}

void backtrack(std::vector<std::vector<int>>& matrix, int N, int cur, 
    std::vector<std::vector<std::vector<int>>>& ans) {
    if (N == cur) {
        ans.push_back(matrix);
        return;
    }

    int i = cur;
    int y = i;
    for (int j=0; j<N; j++) {
        int x = j;
        if (!check(x, y, N, matrix)) {
            continue;
        }
        matrix[y][x] = 1;
        backtrack(matrix, N, y+1, ans);
        matrix[y][x] = 0;
    }
}


std::vector<std::vector<std::vector<int>>> GetFromConfig(int N) {
    std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 0));    
    std::vector<std::vector<std::vector<int>>> ans;
    backtrack(matrix, N, 0, ans);

    return ans;
}
int main() {
	auto ans = GetFromConfig(8);
    for (auto& solu : ans) {
        for (auto& row : solu) {
            for (auto x : row) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "xxxxxxxxxxxx" << std::endl;
    }
}
