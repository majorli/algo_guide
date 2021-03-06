.. index:: 中位数算法

中位数问题
++++++++++++++++

:strong:`中位数`\ （median），又称\ :strong:`中值`\ ，是一个重要的统计指标。它是将一组数据按顺序排列后居于中间位置的数，可将数据划分为个数相等的两部分，其中一个部分中所有数都大于等于中位数，另一个部分中所有数都小于等于中位数。对于有限的数集，如果其中有奇数个数，那么把所有数排序后正中间的那一个数的值就是中位数；如果有偶数个数，排序后最中间两个数的平均值是中位数。

.. admonition:: 示例

   数列 [7,1,3,20,5] 的中位数是5。数列中比5小的数和比5大的数个数相等，都是2个。如果把这5个数排序后得到 [1,3,5,7,20]，可以发现5位于正中间的位置。

   数列 [1,3,10,2] 的中位数是2和3的平均数2.5。数列中比2.5小的数和比2.5大的数都是2个。如果把数列排序为 [1,2,3,10]，就可以直观地看出2和3是最中间的两个数，所以中位数取它们的平均数。

简而言之，一个数列的中位数就是将其排序后，位于最中间位置的数值。对于这个数列而言，其中比中位数小的数和比中位数大的数应当是数量相等的。所以说中位数可以将数列中的数据划分为个数相等的两个部分，一个部分中所有数都大于等于中位数，另一个部分中所有数都小于等于中位数。

关于中位数，有一点概念必须澄清：\ *它是一个单独的数，而不是数列中的一个元素！*

如果给出一组数值，求它的中位数是很简单的，只需要对数组进行排序，然后根据元素个数的奇偶性来进行计算即可。

C++提供了一个非常方便实用的快速排序函数 ``std::sort()``\ ，可以用来对数组中指定的一段元素进行排序。调用 ``sort()`` 函数，只需要提供数组中要排序的那一段元素的头尾指针即可。要使用这个函数，需引入 ``algorithm`` 库并使用命名空间 ``std``\ ，下面是用法示例：

.. code-block:: c++

   #include <algorithm>
   using namespace std;

   int a[100];
   for (int i = 0; i < 100; ++i) scanf("%d", &a[i]); // 读入100个元素

   sort(a, a + 10);      // 对 a[0] 到 a[9] 之间的10个元素进行排序，注意含头不含尾的范围表示原则
   sort(a + 20, a + 40); // 对 a[20] 到 a[39] 之间的20个元素进行排序
   sort(a, a + 100);     // 对 a[0] 到 a[99]，即整个数组进行排序

所以，假如有一个题目，要读入 :math:`n\le1000` 个整数并求其中位数，那么程序将非常简单：

.. code-block:: c++

   #include <cstdio>
   #include <algorithm>

   using namespace std;

   int main()
   {
           int n, a[1001];
           scanf("%d", &n);
           for (int i = 0; i < n; ++i) scanf("%d", &a[i]);  // 读数
           sort(a, a + n);  // 排序
           // 根据 n 的奇偶性来计算中位数并输出，保留2位小数
           printf("%.2lf\n", n % 2 ? (double) a[n/2] : (a[n/2] + a[n/2-1]) / 2.0);

   }

这个程序看懂了吗？看懂了我们就继续讨论一个更加复杂的问题。

现在有两个有序数组 :math:`A` 和 :math:`B`\ ，各有 :math:`m` 和 :math:`n` 个元素，两个数组都已经完成升序排序，即元素从小到大排列。现在要求快速求出这两个数组中所有元素的中位数，时间复杂度不高于 :math:`O\bigl(\log(m+n)\bigr)`\ 。其中 :math:`0\le m,n \le 10^6`\ ，保证两个数组不会同时为空。

.. _24A1-merge-ref:

归并法求两个有序数组的中位数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

如果两个数组都是乱序的，为了求出它们所有元素的中位数，我们可以把两个数组的元素都合到一个大数组里，然后对大数组进行排序来求出中位数。但排序算法最快的时间复杂度为 :math:`O\bigl((n+m)\log(n+m)\bigr)`\ ，远大于问题所要求的上限 :math:`O\bigl(\log(n+m)\bigr)`\ 。这个方法的主要问题出在没有利用两个原始数组都已经有序这个条件。

那么即然两个数组都已经排好序了，我们可以用一种叫做\ :strong:`归并`\ 的操作把两个数组中的元素保持有序地合到另一个大数组里去，时间复杂度为线性的 :math:`O(n+m)`\ 。归并操作非常重要，在大量的算法问题中会用到，基本排序算法中最重要的\ :strong:`归并排序`\ 也是基于归并来完成的，一定要熟练掌握。

归并的思路来源于整队。比如有两列队伍，都是按照身高从矮到高排列好的，现在要把两列队伍合并为一列，并且保持身高从矮到高排列。这个整队过程非常简单，从两列队伍各自排在队头的人开始，每次挑出两个队头中比较矮的那个人出列，排进新的队伍的尾部，如果队头两个人身高一样就任选其中一人即可。不断循环这一过程，直到某个队伍的人全部挑完，把另一个队伍中剩余的人按原顺序排到新队伍的后面就完成了。下面举个简单的例子来说明这个过程：

.. code-block:: none

   初始状态：

   队伍一: [1, 3]

   队伍二: [2, 6, 7]

   新队伍: []

   第1步：队伍一的队头1较小，挑出来放到新队伍尾部

   队伍一: 1, [3]

   队伍二: [2, 6, 7]

   新队伍: [1]

   第2步：队伍二的队头2较小，挑出来放到新队伍尾部

   队伍一: 1, [3]

   队伍二: 2, [6, 7]

   新队伍: [1, 2]

   第3步：队伍一的队头3较小，挑出来放到新队伍尾部

   队伍一: 1, 3, []

   队伍二: 2, [6, 7]

   新队伍: [1, 2, 3]

   第4步：队伍一已空，把队伍二剩下的部分按原顺序放到新队伍尾部

   队伍一: 1, 3, []

   队伍二: 2, 6, 7, []

   新队伍: [1, 2, 3, 6, 7]

按照这个方法，我们把两个数组读进来之后，可以归并到一个新的数组里去，然后在新数组里计算中位数即可。

.. literalinclude:: ../../codes/24A_lc04_merge.cpp
   :language: c++

这个算法思路很简单，程序很简洁，运行速度其实也挺快的，通常情况下这种方法就很好，推荐使用。但是归并算法有一个很大的问题是大量占用内存，因为它要把所有原数据都复制一份，所以空间复杂度高达 :math:`O(m+n)`\ 。

归并的时间复杂度很显然是 :math:`O(m+n)`\ ，所以这个基于归并的算法还远达不到不超过 :math:`O\bigl(\log(m+n)\bigr)` 的时间复杂度要求。

我们需要一个更加快的算法，因为问题要求的时间复杂度为对数型，看到对数型的时间要求一定会想到二分法。这个世界上绝大多数达到对数时间的算法都是二分法。下面我们就要重点讲一讲怎么用二分法求两个有序数组的中位数。


二分法求两个有序数组的中位数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

根据中位数的定义，假设把 :math:`A,B` 两个数组有序归并成数组 :math:`C`\ ，取 :math:`half=\left\lfloor\frac{m + n}{2}\right\rfloor`\ ，将 :math:`C` 分为前后两半 :math:`C_l` 和 :math:`C_r`\ 。前半部分 :math:`C_l` 有 :math:`half` 个数，后半部分 :math:`C_r` 有 :math:`m+n-half` 个数。那么实际上我们已经找到中位数了：

   如果 :math:`m+n` 为奇数，中位数等于后半部分最小值 :math:`C_r[0]`\ ；

   如果 :math:`m+n` 为偶数，则中位数为前半部分最大值和后半部分最小值的平均值 :math:`\frac{1}{2}\bigl(C_l[half-1]+C_r[0]\bigr)`\ 。

但是现在我们不能真的去归并出数组 :math:`C` 来，怎么办？我们当然还是要设法把所有的数划分成两半，并且在没有归并、没有排序的情况下判断是不是前一半中的最大值恰好小于等于后一半中的最小值，即 :math:`\max\{C_l\}\le \min\{C_r\}`\ 。请注意，现在 :math:`C_l` 中的最大值不是 :math:`C_l[half-1]` 了，:math:`C_r` 中的最小值也不是 :math:`C_r[0]` 了。如果找到了满足这个条件的一种划分，那么实际上中位数也就找到了：

   如果 :math:`m+n` 为奇数，中位数等于后半部分最小值 :math:`\min\{C_r\}`\ ；

   如果 :math:`m+n` 为偶数，则中位数为前半部分最大值和后半部分最小值的平均值 :math:`\frac{1}{2}\bigl(\max\{C_l\}+\min\{C_r\}\bigr)`\ 。

要找到这样一种划分，首先要有办法遍历所有可能的划分方法。

不失一般性，假设 :math:`m \le n`\ ，即数组 :math:`A` 的元素个数不多于数组 :math:`B` 的元素个数。如果读入的数据情况相反，我们可以在编程的时候用一个小技巧把两个数组互换过来，这个技巧到后面再讲，现在先在这个假设下进行分析。

如前所述，:math:`C_l` 中一定有一些数来自 :math:`A`\ ，另一些来自 :math:`B`\ ，:math:`C_r` 也是如此。:math:`A` 和 :math:`B` 都为 :math:`C` 的前后两半贡献了一些数。不难想象，:math:`A` 贡献给 :math:`C_l` 的数一定都不大于它贡献给 :math:`C_r` 的数，即 :math:`A` 对 :math:`C` 前后两半的贡献其实也是它自己的一个前后划分。数组 :math:`B` 当然也一样。所以，是 :math:`A` 和 :math:`B` 各自的一个前后划分，组合成了 :math:`C` 的前后两半。

于是我们可以先任意划分数组 :math:`A`\ ，将 :math:`A[0:k]` 贡献给 :math:`C_l`\ ，:math:`A[k:m]` 贡献给 :math:`C_r`\ ，其中 :math:`0\le k\le m`\ 。当 :math:`k=0` 时，:math:`A` 中所有元素都贡献给了 :math:`C_r`\ ；当 :math:`k=m` 时则全部贡献给了 :math:`C_l`\ 。

:math:`A` 划分完毕后，实际上 :math:`B` 的划分也就依此而确定了。这是因为 :math:`C_l` 规定了是要有 :math:`half` 个元素，所以既然 :math:`A` 已经提供了 :math:`k` 个，那么 :math:`B` 就一定是提供 :math:`half-k` 个。所以 :math:`B[0:half-k]` 贡献给 :math:`C_l`\ ，剩余的 :math:`B[half-k:n]` 全部贡献给 :math:`C_r`\ 。因为我们已经限定了 :math:`m \le n`\ ，所以确保了 :math:`B` 的划分一定不会出界，即一定能确保 :math:`0\le half-k\le n`\ 。这是一个简单的不等式推导，请自行验证。

数组 :math:`A` 一共有 :math:`m+1` 种划分，其中必有一种是满足中位数划分的条件的，即 :math:`\max\{C_l\}\le \min\{C_r\}`\ ，我们的任务于是就变成了找出这种划分。如果蛮力枚举，也已经把时间复杂度降到了 :math:`O\bigl(\min\{m,n\}\bigr)`\ 。如果对于任意一种划分 :math:`k`\ ，我们有办法确定它是大了还是小了，即数组 :math:`A` 给 :math:`C_l` 贡献其前 :math:`k` 个元素是给多了还是给少了，那么我们就可以愉快地用二分法来查找正确的划分数 :math:`k` 了，时间复杂度 :math:`O\bigl(\log\min\{m,n\}\bigr)`\ ，问题完美解决。

要判断一个划分 :math:`k` 是大了还是小了还是正好，一共有三种情况：

1. :math:`1\le k \le m-1`\ ，这时候 :math:`A[0:k]` 贡献给了 :math:`C_l`\ ，:math:`A[k:m]` 在 :math:`C_r` 中。相应的，数组 :math:`B` 的划分点为 :math:`j=half-k`\ ，满足 :math:`1\le j\le n-1`\ ，所以 :math:`B[0:j]` 贡献给了 :math:`C_l`\ ，:math:`C_r` 中则是 :math:`B[j:n]`\ 。两个数组对前后两半都有贡献，如下所示：

   .. code-block:: none

                      C的前半部分     |     C的后半部分

      来自数组A：  A[0], ..., A[k-1]  |  A[k], ..., A[m-1]

      来自数组B：  B[0], ..., B[j-1]  |  B[j], ..., B[n-1]

   我们要比较前半部分的最大值和后半部分的最小值，前半部分的最大值是 :math:`A[k-1]` 和 :math:`B[j-1]` 二者中的大者，后半部分的最小值是 :math:`A[k]` 和 :math:`B[j]` 二者的小者。四者要相互比较大小，但是由于两个原数组本身是有序的，所以 :math:`A[k-1]\le A[k]` 和 :math:`B[j-1]\le B[j]` 天生成立，它们不需要比较，我们只需要交叉对比即可：

   1. 当 :math:`A[k-1]\gt B[j]` 时，说明数组 :math:`A` 贡献给 :math:`C_l` 的数太多了，有过大的数混进前半部分去了，所以这时候我们应该减小 :math:`k` 的值；
   2. 当 :math:`B[j-1]\gt A[k]` 时，说明数组 :math:`A` 贡献给 :math:`C_l` 的数太少了，有过小的数混进后半部分去了，所以这时候我们应该增大 :math:`k` 的值；
   3. 其余情况，说明 :math:`A[k-1]\le B[j]` 且 :math:`B[j-1]\le A[k]`\ ，这就是说 :math:`A[k-1]` 和 :math:`B[j-1]` 二者中的大者小于等于 :math:`A[k]` 和 :math:`B[j]` 二者的小者，即 :math:`C` 前半部分的数都不大于后半部分的数，Bingo！我们找到了中位数。

2. :math:`k=0` 时，数组 :math:`A` 中所有数都分在了 :math:`C_r`\ ，:math:`C_l` 全部由 :math:`B[0:j]` 构成。此时 :math:`j=half`\ ，当 :math:`m=n` 时 :math:`j=n`\ ，会出现整个数组 :math:`B` 都在 :math:`C_l` 前半部分的情况，但是这没有关系，如下所示：

   .. code-block:: none

                      C的前半部分     |     C的后半部分

      来自数组A：                     |  A[0], ..., A[m-1]

      来自数组B：  B[0], ..., B[j-1]  |  B[j], ..., B[n-1]  (当 m == n 时，j == n，后半部分无 B 的元素)

   现在，数组 :math:`A` 对 :math:`C_l` 没有贡献任何数，所以前半部分的最大值就是 :math:`B[j-1]`\ ，而且 :math:`A` 的划分数 :math:`k` 也已经不能再减小了。因此只能有两种情况，要么 :math:`k` 小了，要么这个划分正好。而 :math:`B` 有没有对 :math:`C` 的后半部分贡献元素是无关紧要的，因为要减小 :math:`k` 的情况不存在，而且反正也没有数需要和它比大小：

   1. 当 :math:`B[j-1]\gt A[k]` 时，说明数组 :math:`A` 贡献给 :math:`C_l` 的数太少了，有过小的数混进后半部分去了，所以这时候我们应该增大 :math:`k` 的值；
   2. 其余情况，说明这就是中位数的正确划分。

3. :math:`k=m` 时，数组 :math:`A` 中所有数都被分在了 :math:`C_l`\ ，:math:`C_r` 全部由 :math:`B[j:n]` 构成。此时 :math:`j=half-m`\ ，当 :math:`m=n` 时 :math:`j=0`\ ，会出现整个数组 :math:`B` 都在 :math:`C_r` 的情况，但是和情况2类似，这也没有关系，如下所示：

   .. code-block:: none

                      C的前半部分     |     C的后半部分

      来自数组A：  A[0], ..., A[m-1]  |

      来自数组B：  B[0], ..., B[j-1]  |  B[j], ..., B[n-1]  (当 m == n 时，j == 0，前半部分无 B 的元素)

   现在，数组 :math:`A` 对 :math:`C_r` 没有贡献任何数，所以后半部分的最小值就是 :math:`B[j]`\ ，而且 :math:`A` 的划分数 :math:`k` 也已经不能再增大了。因此只能有两种情况，要么 :math:`k` 大了，要么这个划分正好。而 :math:`B` 有没有对 :math:`C` 的前半部分贡献元素是无关紧要的，因为要增大 :math:`k` 的情况不存在，而且反正也没有数需要和它比大小：

   1. 当 :math:`A[k-1]\gt B[j]` 时，说明数组 :math:`A` 贡献给 :math:`C_l` 的数太多了，有过大的数混进前半部分去了，所以这时候我们应该减小 :math:`k` 的值；
   2. 其余情况，说明这就是中位数的正确划分。

上面一共分析了三种情况，每种情况里又有2到3种小情况，显得比较复杂。但是我们发现所有七种小情况其实一共只有减小 :math:`k`\ 、增大 :math:`k`\ 、解是 :math:`k` 这么三类，所以我们可以综合以上三种情况，整合成比较清晰的符合二分查找特征的三个分支：

1. 当 :math:`1\le k\le m` 时，即当 :math:`k\gt0` 时，如果 :math:`A[k-1]\gt B[j]`\ ，那么减小 :math:`k`\ ；
2. 当 :math:`0\le k\le m-1` 时，即当 :math:`k\lt m` 时，如果 :math:`B[j-1]\gt A[k]`\ ，那么增大 :math:`k`\ ；
3. 其余情况，查找成功。

上面就是整个二分查找数组 :math:`A` 的合适划分数 :math:`k` 的过程。

这个二分算法，比我们前面学过的几个都要复杂，而且有以下几个不同之处：

1. 问题必有解，所以二分查找的循环甚至可以用死循环，然后在判断找对答案的时候 ``break`` 循环。
2. 找对答案的情况比没找对的情况要复杂，所以我们在编程的时候应该先对没找对答案的情况进行判断，最后剩余的就是找对了答案的情况。
3. 由于必有解，所以在查找的边界处可能会有特殊情况需要照顾，在分析时要引起注意。

最后介绍一下怎样确保两个原数组一定是 :math:`m\le n`\ 。当然不是读完之后判断二者大小然后交换数组元素，那太笨了。我们可以定义一个二维数组用来保存两个原数组：

.. code-block:: c++

   int d[2][1000010];

然后照常读入两个原数组的长度 ``m`` 和 ``n``\ ，将数组 :math:`A` 读入到 ``d[0]`` 中，将数组 :math:`B` 读入到 ``d[1]`` 中。再定义两个整型变量：

.. code-block:: c++

   int a = 0, b = 1;

接下来就是见证奇迹的时刻。我们比较两个原数组的长度，如果 ``m <= n`` 就什么都不做，如果 ``m > n`` 就交换 ``m`` 和 ``n`` 的值，并且让 ``a = 1, b = 0``\ 。于是 ``d[a]`` 就是比较短的那个数组，长度为 ``m``\ ；``d[b]`` 就是比较短的那个数组，长度为 ``n``\ 。搞定！这叫做“名实分离”，我说你是 :math:`A` 你就是 :math:`A`\ ，说你是 :math:`B` 你就是 :math:`B`\ ，不管你原本是谁。这个技巧在很多场景下有用，很实用。

下面是完整的程序：

.. literalinclude:: ../../codes/24A_lc04_bin.cpp
   :language: c++


最后留一个思考问题：为什么不需要在开始查找之前对“有一个数组为空”的情况进行特判？

