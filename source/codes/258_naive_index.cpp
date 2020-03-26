#include <cstdio>
#include <algorithm>

// 用来组合原数据及其原数组中位置下标的结构类型，重载小于运算以便排序
struct Combo {
        int data;  // 数据
        int index; // 下标
        bool operator<(const Combo &c) const { return data < c.data; } 
};

// 工具函数
void print(int d[], int n)
{
        printf("%d", d[0]);
        for (int i = 1; i < n; ++i) printf(" %d", d[i]);
        printf("\n");
}

int main()
{
        int n;  // 数据量
        scanf("%d", &n);
        int *data = new int[n];         // 数据原数组
        Combo *tmp = new Combo[n];      // 带下标的结构变量数组，临时排序用
        for (int i = 0; i < n; ++i) {
                scanf("%d", &data[i]);
                tmp[i].data = data[i];  // 读入数据的同时生成临时结构数组
                tmp[i].index = i;
        }
        std::sort(tmp, tmp + n);        // 排序，根据需要也可用稳定排序 stable_sort()
        int *ind = new int[n];          // 生成空索引表
        // 遍历排好序的临时结构体，建立索引表
        // tmp[i].index 是这个数在原数组里的下标
        // i 是这个数排完序后的下标位置，也就是索引值
        for (int i = 0; i < n; ++i) ind[tmp[i].index] = i;
        delete [] tmp;          // 删除临时数组，释放空间
        print(data, n);         // 输出结果：原数组
        print(ind, n);          // 输出结果：索引表

        delete [] ind;
        delete [] data;

        return 0;
}
