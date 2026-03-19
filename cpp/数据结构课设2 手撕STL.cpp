#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;

void swapdata(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}
//堆元素下沉
void ShiftDown(int R[], int n, int i) {
    //堆元素R[i]下沉, 数组R[ ]存储堆, n为堆包含的元素个数
    while (i <= n / 2) { //i最多下行至最后一个非叶结点
        int maxchd = 2 * i; // 假定最大孩子为左孩子
        if (maxchd + 1 <= n && R[maxchd] < R[maxchd + 1])
            maxchd++; //i的右孩子是最大孩子
        if (R[i] >= R[maxchd]) return;
        swap(R[maxchd], R[i]); // R[i]的最大孩子比R[i]大
        i = maxchd; // 结点i继续下沉
    }
}

//建立堆
void BuildHeap(int R[], int n) {
    for (int i = n / 2; i >= 1; i--)
        ShiftDown(R, n, i); //建立以i为根的堆，即下沉i
}

//堆排序
void HeapSort(int R[], int n) { //堆排序R[1]…R[n]
    BuildHeap(R, n); //将R建为堆
    for (int i = n; i > 1; i--) { //i为当前堆的堆尾
        swap(R[1], R[i]); //前i个元素的最大者R[1]与R[i]交换
        ShiftDown(R, i - 1, 1); //下沉R[1]使R[1]...R[i-1]重建为堆
    }
}

void continue_heap(int temp[], int size) {
    // 继续提取排序（完成子数组排序）
    for (int i = size; i > 1; i--) {
        swap(temp[1], temp[i]); 
        ShiftDown(temp, i - 1, 1);
    }
}
void Heap(int R[], int low, int high) {
    int size = high - low + 1;
    int temp[50005];
    for (int i = 1; i <= size; i++) temp[i] = R[low + i - 1];

    BuildHeap(temp, size);  // 先建堆
    for (int i = 1; i <= size; i++) printf("%d ", temp[i]);
    printf("Heap:");
    printf("\n");
    continue_heap(temp, size);
    
    for (int i = 1; i <= size; i++) R[low + i - 1] = temp[i];
}

//划分
int Partition(int R[], int m, int n) { //对子数组Rm…Rn分划
    int K = R[m], L = m + 1, G = n; //Rm为基准元素
    while (L <= G) {
        while (L <= n && R[L] <= K) L++; //从左向右找第一个>K的元素
        while (R[G] > K) G--; //从右向左找第一个K的元素
        if (L < G) { swap(R[L], R[G]); L++; G--; }
    }
    swap(R[m], R[G]);
    return G;
}

//直接插入排序
void InsertionSort(int R[], int n) { //对R[1]...R[n]排序
    for (int i = 2; i <= n; i++) { //R[1]..... R[i-1]  R[i]
        int K = R[i], j = i - 1;
        while (j >= 1 && R[j] > K) {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = K;
    }
}
//主要：快速排序
int depth=0;
void QuickSort(int R[], int m, int n,int depth,int two_log2n_N) {
    //depth++;
    
    if (n - m + 1 > threshold) {//如果子数组长度在阈值以上，则进入
        if (depth >= two_log2n_N) {//深度太深则进入堆排序
            Heap(R, m, n);

            //depth--;
            return;
        }
        int j = Partition(R, m, n);
        QuickSort(R, m, j - 1,depth+1, two_log2n_N);
        QuickSort(R, j + 1, n,depth+1, two_log2n_N);

    }
    //depth--;
    return;
}

//主排序函数

void sort(int* a, int n) {
    double log2n = log(n) / log(2);
    int two_log2n_N = (int)(2.0*log2n);
    //printf("%f=%d",2*log2n,2*log2n_N);
    printf("depth_limit:%d\n", two_log2n_N);

    QuickSort(a, 1, n,0, two_log2n_N);
    //数组 起始下标 末尾下标 递归深度 堆排序阈值
    printf("Intermediate:");
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    InsertionSort(a, n);
}

int main()
{
    int n, i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    sort(a, n);

    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}