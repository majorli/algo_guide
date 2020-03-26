#include <cstdio>

void print(int d[], int n)
{
        printf("%d", d[0]);
        for (int i = 1; i < n; ++i) printf(" %d", d[i]);
        printf("\n");
}

int main()
{
        int n;
        scanf("%d", &n);
        int *data = new int[n];
        int *cnt = new int[10000]();    // 计数数组，动态申请数组时加上()会自动初始化为全0
        for (int i = 0; i < n; ++i) {
                scanf("%d", &data[i]);
                ++cnt[data[i]];         // 一边输入数据一边计数
        }
        for (int i = 1; i < 10000; ++i) // 计数值前缀和，使计数变成累积计数
                cnt[i] += cnt[i-1];
        int *index = new int[n];        // 分配索引表数组
        for (int i = n - 1; i >= 0; --i)// 将排序改成记录排序后的位置，即完成索引表的建立
                index[i] = --cnt[data[i]];
        delete [] cnt;

        print(data, n);
        print(index, n);

        delete [] data;
        delete [] index;

        return 0;
}
