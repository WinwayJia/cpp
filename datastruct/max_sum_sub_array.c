/*
eg4.1：给你一个长度为N的整数数组，请找出最大的子数组和。 -- 《编程之美》

这一题其实可以用动态规划解决。定义两个辅助数组Start [N] 和 All [N]，
Start [i] 表示从元素i开始，包含元素i的最大的一段连续数组和。
All[i] 表示从元素i开始，最大的一段连续数组和。
All[0] = max { A[0], A[0]+Start[1], All[1] }  可以很方便的用动态规划解决。
如果要求返回最大子数组的位置，可以在循环中记录一下。算法还是能保持O(N)的时间复杂度的。
*/

int MaxSum(int *A, int n) {

    All[n-1]=Start [n-1]=A[n-1];

    for(int i=n-2;i>=0;i--){

        Start[i]= max( A[i], A[i]+Start[i+1] );  

        All[i]=max( Start[i], All[i+1] );   

    }

    return All[0];

}



