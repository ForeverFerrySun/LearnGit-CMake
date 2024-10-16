/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-1\main.cpp
 * @Date         : 2024-09-29 16:03:04
 * @author       : foreverferrysun
 * @LastEditTime : 2024-10-16 11:14:38
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */

#include "./include/8queenF.h"
#include <iostream>
// 测试8皇后问题的解法
void test_8queenF() {
    // 打印测试标题
    std::cout << "测试 8queenF:\n";
    // 打印期望的解的数量
    std::cout << "Expected: 92\n";
    
    // 创建一个8皇后问题的实例
    alg::Queen8 q;
    // 解决8皇后问题并打印结果
    q.solve();
}

// 程序入口点
int main() {
    // 调用测试函数，验证8皇后问题的解决方案
    test_8queenF();
    // 程序执行完毕，返回0表示正常结束
    return 0;
}