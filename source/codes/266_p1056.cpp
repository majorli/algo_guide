#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
        int m, n, k, l, d;      // 遵守C++代码惯例，用小写字母命名变量
        scanf("%d %d %d %d %d", &m, &n, &k, &l, &d);

        // 所有可能的行、列通道，行通道用其下边一行的行号为编号，列通道用其左边一列的列号为编号
        // 行、列通道的编号最小的为1号，最大可能的为999号
        // 数组下标对应通道位置号，元素值为该位置的通道能隔开的交头接耳学生对数
        int split_rows[1000] = { 0 }, split_cols[1000] = { 0 };
        int x, y, p, q;
        for (int i = 0; i < d; i++) {
                scanf("%d %d %d %d", &x, &y, &p, &q);  // 这些学生对的坐标值不需要保存
                if (x == p) // 行坐标相等，表示一左一右两位同学，用"较小的列坐标"号通道可以隔开
                        split_cols[min(y, q)]++;
                else        // 否则即为列坐标相等，表示一前一后，用"较小的行坐标"号通道可以隔开
                        split_rows[min(x, p)]++;
        }
        // 通道能隔开学生的对数 * 1000 + 通道编号，再取负数，则进行排序时，相当于双关键字排序
        // 主关键字为"通道能隔开学生的对数"，副关键字为"通道编号"
        // 取负数是为了实现绝对值的逆序排序
        for (int i = 1; i < m; i++)
                split_rows[i] = - split_rows[i] * 1000 - i;
        for (int j = 1; j < n; j++)
                split_cols[j] = - split_cols[j] * 1000 - j;
        sort(split_rows + 1, split_rows + m);
        sort(split_cols + 1, split_cols + n);
        // 取前 k 个行通道和前 l 个列通道即得到最优解，接下来要对最优解按照通道位置编号再次排序
        // 故将元素值绝对值除1000取余，变为通道编号，再进行排序就符合了输出格式要求
        for (int i = 1; i <= k; i++)
                split_rows[i] = - split_rows[i] % 1000;
        for (int j = 1; j <= l; j++)
                split_cols[j] = - split_cols[j] % 1000;
        sort(split_rows + 1, split_rows + k + 1);
        sort(split_cols + 1, split_cols + l + 1);
        // 按照输出格式要求输出最优解，行末不能有空格
        printf("%d", split_rows[1]);
        for (int i = 2; i <= k; i++)
                printf(" %d", split_rows[i]);
        printf("\n");
        printf("%d", split_cols[1]);
        for (int j = 2; j <= l; j++)
                printf(" %d", split_cols[j]);
        printf("\n");
        
        return 0;
}
