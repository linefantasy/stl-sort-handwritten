// 第二次作业3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
using namespace std;

// 定义栈帧结构
// 这代表了一个"任务"或者说一次"函数调用"的状态
struct Frame {
    int n;          // 当前需要移动的盘子数量
    char from;      // 起始柱子
    char via;       // 辅助柱子
    char to;        // 目标柱子
    // int state;   // 此处未启用状态机，因为通过入栈顺序即可控制流程
};

// 统计栈的最大深度
// 使用 static 变量来记录历史上达到过的最大值 m
int MaxDepth(int m) {
    static int maxDepth = 0; // 静态变量，在函数调用间保持其值
    if (m > maxDepth) {
        maxDepth = m;
    }
    return maxDepth;
}

// 核心汉诺塔函数（非递归版）
int hanoi(int n, char from, char via, char to) {
    int max;             // 用于记录返回的最大深度
    stack<Frame> S;      // 定义一个栈，用于模拟系统的函数调用栈
    Frame P, T;          // P用于存放当前从栈顶取出的任务，T用于构建新任务入栈
    int currentDepth = 0; // 当前栈的模拟深度（注：原代码变量名为 maxDepth，为避免歧义，注释中理解为 currentDepth）

    // --- 初始化 ---
    // 构建初始任务：把 n 个盘子从 from 移到 to
    P.n = n; P.from = from; P.via = via; P.to = to;
    S.push(P);
    currentDepth = 1; // 此时栈里有1个元素

    while (1) {
        // 1. 取出当前要处理的任务（出栈）
        P = S.top();//每次从栈顶取出一个操作P
        S.pop();
        currentDepth -= 1; // 维护深度计数

        // 2. 基准情况（Base Case）：如果只需要移动 1 个盘子
        // 或者是把大问题拆解后的"移动最大盘子"那一步
        if (P.n == 1) {
            // 直接执行移动，不需要再拆分
            if (S.empty()) {
                // 如果栈空了，说明这是最后一个任务，打印并退出
                printf("Move disk from %c to %c\n", P.from, P.to);
                break;
            }
            else {
                // 否则只是完成了其中一步，打印移动动作，继续循环处理栈中剩余任务
                printf("Move disk from %c to %c\n", P.from, P.to);
            }
        }

        // 3. 递归步骤（Recursive Step）：如果 n > 1
        // 需要将问题 H(n, A, B, C) 拆解为三步。
        // 由于栈是【后进先出】，入栈顺序必须与执行顺序【相反】。
        // 期望执行顺序：
        //   Step 1: 把 n-1 个盘子从 From 移到 Via (借助 To)
        //   Step 2: 把第 n 个盘子从 From 移到 To
        //   Step 3: 把 n-1 个盘子从 Via 移到 To (借助 From)
        else {
            // --- 入栈 Step 3 (最后执行，所以最先入栈) ---
            // 逻辑：将 n-1 个盘子从 当前辅助柱(via) 移到 目标柱(to)
            T.n = P.n - 1;
            T.from = P.via;  // 起点是刚才的辅助柱
            T.via = P.from;  // 新的辅助柱是刚才的起点
            T.to = P.to;     // 终点不变
            S.push(T);
            currentDepth += 1;

            // --- 入栈 Step 2 (中间执行) ---
            // 逻辑：将剩下的那 1 个最大的盘子，从 起点 移到 终点
            // 注意：这里将 n 设为 1，下次循环拿出来时就会进入 if(P.n == 1) 分支直接打印
            T.n = 1;
            T.from = P.from;
            T.to = P.to;
            T.via = P.via; // 这个其实不重要了，因为直接移动不需要辅助
            S.push(T);
            currentDepth += 1;

            // --- 入栈 Step 1 (最先执行，所以最后入栈) ---
            // 逻辑：将 n-1 个盘子从 起点(from) 移到 辅助柱(via)
            T.n = P.n - 1;
            T.from = P.from; // 起点不变
            T.to = P.via;    // 目标变成了辅助柱
            T.via = P.to;    // 原来的目标柱变成辅助柱
            S.push(T);
            currentDepth += 1;

            // 更新历史最大深度
            // 此时我们在原来的基础上pop了1个，push了3个，净增2个
            max = MaxDepth(currentDepth);
        }
    }
    return max;
}

int main() {
    int n;
    char from, via, to;
    from = 'A'; via = 'B'; to = 'C';

    // 输入盘子数量
    if (scanf("%d", &n) != 1) return 0; // 简单的输入检查

    // 调用非递归汉诺塔函数并打印最大栈深
    printf("Max Stack Depth: %d\n", hanoi(n, from, via, to));

    return 0;
}
