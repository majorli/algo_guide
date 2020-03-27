排列与组合：数学的概念
++++++++++++++++++++++++++++++

:math:`排列`\ （permutation）与\ :math:`组合`\ （combination）是两个重要的数学概念，是组合数学和概率论的基础，是离散数学、集合论的重要组成部分，在计算机算法上有非常多的应用。这一节我们先来简单介绍一下排列与组合的数学概念。


排列和排列数的计算
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

排列是指若干个互不相同物体按顺序排列。比如3个不同的小球，分别编号为1号球、2号球、3号球，那么 [1,2,3] 就是它们的一种排列，[2, 1, 3] 也是一种。参与排列的物体数量比较少的时候，很容易用罗列的方法列出所有可能的排列。比如1到3号三个小球的排列一共有6种，可以很快罗列完整，分别为：

.. code-block:: none

   [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]

有时候我们并不想把所有物体都拿出来进行排列，而是指定从中取出若干个进行排列。例如从1号到4号三个小球中取出3个进行排列，经过仔细的罗列，可以得到24种不同的排列：

.. code-block:: none

   [1,2,3], [1,2,4], [1,3,2], [1,3,4], [1,4,2], [1,4,3]
   [2,1,3], [2,1,4], [2,3,1], [2,3,4], [2,4,1], [2,4,3]
   [3,1,2], [3,1,4], [3,2,1], [3,2,4], [3,4,1], [3,4,2]
   [4,1,2], [4,1,3], [4,2,1], [4,2,3], [4,3,1], [4,3,2]

在数学里，:strong:`排列`\ 是指将相异对象或符号根据确定的顺序重排的操作，重排得到的每一个序列都称作一个排列。或者用集合的语言来形容，将一个集合中的元素重排成序列（我们知道，集合中的元素是各不相同且没有相互顺序的，而序列里的元素是有相互顺序关系的）。

从 :math:`n` 个相异对象中任意取 :math:`m` 个进行排列，其中 :math:`0\le m\le n` 且均为整数，可以得到的不同排列的数量，就叫做 :math:`m` 取 :math:`n` 的\ :strong:`排列数`，记作 :math:`P_n^m` 或 :math:`A_n^m`，有时候为了书写方便也简单地写成 :math:`P(n,m)` 或 :math:`A(n,m)`。现在中国的中学数学教材上一般采用 :math:`A_n^m` 这种写法，而计算机教材和大学数学教材上通常使用 :math:`P_n^m` 这种写法，我们使用后一种。如果 :math:`m=n`，即排列所有 :math:`n` 个相异对象的，称作\ :strong:`全排列`，:math:`P_n^n` 也称作 :math:`n` 的\ :strong:`全排列数`。

从前面两个简单的例子可以看出，随着 :math:`n,m` 这两个参数的增大，排列数会迅速增大，而且变得难以手工罗列。事实上，对于任意固定的 :math:`m\gt0`，排列数 :math:`P_n^m` 随着 :math:`n` 增长的阶是阶乘级的，比指数级还高。关于怎样遍历所有排列的算法将在后面介绍，这一节我们先介绍怎样计算排列数。

乍看起来有点奇怪的是，:math:`n` 和 :math:`m` 都是可以等于零的。实际上这也没什么奇怪的，虽然很多人觉得“取0个对象进行排列”，甚至“从0个对象中取出0个进行排列”这种操作很有点神操作的感觉，但在实际上和在数学上都是有意义的，而且毕竟要考虑到空集的情况。当然了，不管对象的总数 :math:`n` 是多少，从中一个对象都不取并进行排列显然只能有一种结果，那就是得到的结果也只能是一个空排列，而这个世界上只有一种空排列。因此我们可以得到排列数的第一条计算规则：

.. math::

   P_n^0\equiv1

.. note::

   数学符号 :math:`\equiv` 表示“恒等于“。

接下来我们看 :math:`m=1` 的情况，此时当然有 :math:`n\ge1`，也就是从 :math:`n` 个相异对象中取 :math:`1` 个的排列。很显然共有 :math:`n` 种不同取法，分别对应 :math:`n` 个对象。因此这种情况也很简单，我们马上可以得到第二条计算规则：

.. math::

   P_n^1=n

如果 :math:`m=2`，我们可以这样考虑，每一种排列都可以分两步完成：第1步，先从所有的 :math:`n` 个对象中任取一个，一共有 :math:`n` 中取法；第2步，从剩下的 :math:`n-1` 个对象中再任取一个放在刚才已经取出的那个对象后面，一共有 :math:`n-1` 种取法。上述两步做完就完成了一次 :math:`n` 取 :math:`2` 的排列，根据乘法原理，这样的由先后两步合起来的操作总共有 :math:`n(n-1)` 种，因此就有了第三条计算规则：

.. math::

   P_n^2=n(n-1)

依此类推，不难得到对于任意的 :math:`m\gt2`，我们不过是不断重复“任取一个，再从剩下的对象里任取一个”这样的操作，把陆续取出的对象依次排在一起，直到取满 :math:`m` 次为止。简单推算一下就知道，最后一次取的时候可供选择的对象还剩 :math:`n-m+1` 个，所以：

.. math::

   P_n^m=\underbrace{n\cdot(n-1)\cdot\cdots\cdot(n-m+1)}_\text{m个连续递减整数连乘}\tag{1}

当 :math:`m=n` 时，这个连乘会一直延续到1位置，这也和最后一次只剩一个对象可取的实际情况相符。所以全排列数为：

.. math::

   P_n^n=n\cdot(n-1)\cdot\cdots\cdot1=n!

再仔细观察 :math:`m\ge1` 的几个计算规则，我们可以发现，其实它们本质上都是一样的，都是从 :math:`n` 开始的连续 :math:`m` 个逐个递减的正整数连乘起来，即都可以统一为公式 :math:`(1)`。再考虑到 :math:`n-m+1` 的下一个整数是 :math:`n-m`，以及 :math:`0!=1`，这个公式又可以改写为：

.. math::

   P_n^m=\frac{n!}{(n-m)!}\tag{2}

而且我们可以发现，公式 :math:`(2)` 也可以包容 :math:`m=0` 的情形。这个公式是数学上计算排列数的标准公式。



.. admonition:: 练习：重复排列（Permutations with repetition）

   另外还有一种特殊的排列称为\ :strong:`重复排列`。普通的排列，每一个对象最多只能取一次，而重复排列则允许一个对象被多次取出。有点类似于一个对象被取出之后还可以复制一份放回去以便下次再取，所以有些书上也称之为“可放回的排列”。

   :math:`n` 取 :math:`m` 的重复排列数记作 :math:`U_n^m`。请大家思考一下它的计算公式，以及应该用什么算法来编程实现计算。



组合和组合数的计算
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In mathematics, a combination is a selection of items from a collection, such that (unlike permutations) the order of selection does not matter. For example, given three fruits, say an apple, an orange and a pear, there are three combinations of two that can be drawn from this set: an apple and a pear; an apple and an orange; or a pear and an orange. More formally, a k-combination of a set S is a subset of k distinct elements of S. If the set has n elements, the number of k-combinations is equal to the binomial coefficient

{\displaystyle {\binom {n}{k}}={\frac {n(n-1)\dotsb (n-k+1)}{k(k-1)\dotsb 1}},}{\binom {n}{k}}={\frac {n(n-1)\dotsb (n-k+1)}{k(k-1)\dotsb 1}},
which can be written using factorials as {\displaystyle \textstyle {\frac {n!}{k!(n-k)!}}}\textstyle {\frac {n!}{k!(n-k)!}} whenever {\displaystyle k\leq n}k\leq n, and which is zero when {\displaystyle k>n}k>n. The set of all k-combinations of a set S is often denoted by {\displaystyle \textstyle {\binom {S}{k}}}{\displaystyle \textstyle {\binom {S}{k}}}.

Combinations refer to the combination of n things taken k at a time without repetition. To refer to combinations in which repetition is allowed, the terms k-selection,[1] k-multiset,[2] or k-combination with repetition are often used.[3] If, in the above example, it were possible to have two of any one kind of fruit there would be 3 more 2-selections: one with two apples, one with two oranges, and one with two pears.

Although the set of three fruits was small enough to write a complete list of combinations, with large sets this becomes impractical. For example, a poker hand can be described as a 5-combination (k = 5) of cards from a 52 card deck (n = 52). The 5 cards of the hand are all distinct, and the order of cards in the hand does not matter. There are 2,598,960 such combinations, and the chance of drawing any one hand at random is 1 / 2,598,960.