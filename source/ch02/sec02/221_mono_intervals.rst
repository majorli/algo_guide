单调区间在线统计
++++++++++++++++++++++++

:strong:`单调性`\ 和\ :strong:`单调区间`\ 是数学上的重要概念，用于描述一元实数函数值和数列元素的增减性，以及具有相同增减性的一段范围。

**函数的单调性和单调区间**

对于一个一元实数函数 :math:`f(x)`\ ，如果在自变量 :math:`x` 的某一个取值范围内，对于任意两个不同的自变量 :math:`x_1\lt x_2`\ ，它们所对应的函数值大小关系是 :math:`f(x_1)\lt f(x_2)`\ ，那么称函数 :math:`f(x)` 在这个取值范围内\ :strong:`单调递增`\ ，称这个取值范围为函数 :math:`f(x)` 的一个\ :strong:`单调递增区间`\ ；反之，如果在某个取值范围内的任意两个不同自变量 :math:`x_1\lt x_2` 满足 :math:`f(x_1)\gt f(x_2)`\ ，那么称函数 :math:`f(x)` 在这个自变量取值范围内\ :strong:`单调递减`\ ，称这个取值范围为函数 :math:`f(x)` 的一个\ :strong:`单调递减区间`\ 。通俗地说，单调递增就是函数值随着自变量的增大而增大，单调递减就是函数值随着自变量的增大而减小。

例如正比例函数 :math:`f(x)=2x` 就是一个单调递增函数，它的单调区间是整个实数域 :math:`\Bbb{R}`\ ，任意两个不同的实数 :math:`x_1\lt x_2`\ ，必定满足 :math:`2x_1\lt 2x_2`\ 。

反比例函数 :math:`f(x)={2\over x}` 则有两个单调区间，:math:`(-\infty, 0)` 和\ :math:`(0,+\infty)`\ ，它们都是单调递减区间。任意两个不同的正数 :math:`0\lt x_1\lt x_2` 满足 :math:`{2\over x_1} \gt {2\over x_2}`\ ；对于任意两个不同的负数，情况同样如此。

平方数函数 :math:`f(x)=x^2` 也有两个单调区间，:math:`(-\infty, 0]` 和 :math:`[0,+\infty)`\ 。前者是单调递减区间，后者是单调递增区间，这是因为负数的平方等于负数的绝对值的平方，而负数越大，其绝对值越小。和反比例函数的情况不同的是，平方函数的两个单调区间里增减性不同，而且两个区间在零点处是连续而且平滑的。

.. image:: ../../images/221_mono_int.png

从上面三个函数的图像里，沿着自变量增大的方向去直观地看，在单调递增区间里，函数的图像是向上爬山的样子，在单调递减区间里，函数的图像是向下滑坡的样子。

.. admonition:: 补充

   事实上，还可以有函数值不变的区间，叫做常数区间。比如常数函数 :math:`f(x)=c`，整个实数域就是它的常数区间。

   如果把条件从严格的大于（小于）放松为大于等于（小于等于），单调增减性就放宽为普通的增减性，单调区间也就相应地放宽为普通的递增或递减区间。例如满足判断条件 :math:`x_1\lt x_2 \implies f(x_1)\le f(x_2)` 的区间就是普通的递增区间，而不是单调递增区间，称函数 :math:`f(x)` 在这个区间上递增，而不是单调递增。在普通的递增或递减区间里允许包含一些常数子区间，而单调的增减区间内是不能出现常数子区间的，这种情况在分段函数里经常出现。


**数列的单调性和单调区间**

函数的单调性是数学里特别特别特别重要的一个知识点，但是单调性并不只用于分析实数函数，它也经常用于分析数列，即分析数列元素的值相对于元素位置（或称为下标）的单调性。在算法领域里，与数列单调性相关的问题非常普遍。数列的单调性和函数单调性有类似的地方，也有不同的地方。

在数学里，数列 :math:`A=\{a_n\}` 就是一组n个用正整数连续编号的数：:math:`a_1,a_2,\dots,a_n`\ ，每一个具体的数称为数列的一个\ :strong:`项`\ ，编号表示项在数列中的位置，称作\ :strong:`下标`\ 。数学的习惯一般是从1开始编号，第一项为1号项，最后一项为n号项。有时候也可以把数列视作一类特殊的函数，即把下标值视作自变量，把项视作函数值，而自变量的取值范围即为整数区间 :math:`[1,n]`\ ，这时候往往把项 :math:`a_i` 写成 :math:`A(i)` 这样的形式。

在计算机编程语言里，数列一般是用数组或者顺序容器（比如C++的vector容器）来实现的，并且在概念上对数学里单纯的“数”列进行了一般化的推广，成为了一般性的元素序列。一个\ :strong:`序列`\ 由一系列顺序存放的同类型对象构成，这些对象称为序列的\ :strong:`元素`\ ，类似于数列的项，但是其类型不局限于普通的数，任何计算机能够表示和运算的对象，比如字符、字符串、结构等都可以是序列的元素类型。另外，元素的下标和绝大多数编程语言的设定一致，一般从0开始编号，长度为 :math:`n` 的序列中第一个元素是0号元素，最后一个元素是 :math:`n-1` 号元素。

自从C语言诞生以来，几乎所有的编程语言都采用了“方括号+下标”的序列元素访问语法，这已经成为了业界标准。所以在探讨算法编程的时候，习惯使用 :math:`A[i]` 这种方式表示序列的元素。另外，C语言还确立了另一个业界标准，即采用左闭右开的方式来表示序列中的一段范围，也就是通常所说的含头不含尾原则。所以通常用 :math:`[i,j)` 表示从 :math:`i` 到 :math:`j-1` 的一段下标范围。近几年随着Python语言的兴起，也开始用 :math:`A[i:j]` 这种方式来表示从 :math:`A[i]` 到 :math:`A[j-1]` 的子序列。可见，哪怕不是C-like语言的Python，也采用含头不含尾的规则来表示范围。

今后我们会视上下文的情形来使用下列符号。

* 用 :math:`A=\{a_n\}` 表示由 :math:`n` 个元素构成的数列 :math:`A`\ ，数列名使用大写字母，元素用 :math:`a_i` 表示，用 :math:`\{a_i,\dots,a_j\}` 表示数列中从第 :math:`i` 项到第 :math:`j` 项的一段，或者表示成区间 :math:`[i,j]`\ 。
* 用大写字母 :math:`A` 表示一个名为 :math:`A` 的序列，其中的元素用 :math:`A[i]` 表示，用 :math:`A[i:j]` 表示从 :math:`A[i]` 到 :math:`A[j-1]` 的子序列，或者表示成左闭右开区间 :math:`[i,j)`\ ；用 :math:`A[i..j]` 表示从 :math:`A[i]` 到 :math:`A[j]` 的子序列，或者表示成闭区间 :math:`[i,j]`\ ；上述几种表示法可以在一个下标方括号内出现多次，用逗号分隔，例如 :math:`A[0:2,5,7..9]` 表示0,1,5,7,8,9六个元素。采用此种表示方式时下标总是从0开始。

如果数列 :math:`A=\{a_n\}` 的一段 :math:`\{a_i,\dots,a_j\}` 中每一项都比它前面的项更大，即对于任意的 :math:`i\lt k \le j`\ ，都有 :math:`a_k \gt a_{k-1}` 成立，那么数学上就把这一段称为数列的一个单调递增区间，长度为 :math:`j-i+1`\ ；反之如果这一段里的所有项都比它前面的项更小，它就是数列的一个单调递减区间，长度当然也是 :math:`j-i+1`\ 。

.. admonition:: 补充

   和函数类似，数列也可以有常数区间、普通的递增区间和递减区间。

.. attention::

   由于数列的下标是整数这个特性，导致数列可以有只含有一个项的区间。这样的区间既可以认为是递增的，也可以认为是递减的，更可以认为是常数的。具体要怎样看待它需要根据题意来判断。

对于数列的某一个区间 :math:`[i,j]`\ ，用其中最大的项减去最小的项得到的差称为这个区间的\ :strong:`振幅`\ 或\ :strong:`幅度`\ 。如果这是一个递增或递减区间，那么无论单调与否，它的振幅一定是 :math:`\vert a_j-a_i\vert`\ 。递增区间的振幅叫\ :strong:`增幅`\ ，递减区间的振幅叫\ :strong:`降幅`\ 。

例如数列 [1,5,17,8,6,6,5,3,3,4,5,6,7,8] 中，单调递增区间有 [1,5,17]、[3,4,5,6,7,8] 两个，长度分别为3和6，增幅分别为16和5；单调递减区间有 [17,8,6]、[6,5,3]，长度均为3，降幅分别为11和3。另外，中间的一整段 [17,8,6,6,5,3,3] 共7项是一个普通的递减区间，它中间包含了两个常数区间 [5,5] 和 [3,3]，所以它不具有单调性。

数列单调区间的统计问题通常是求单调区间的长度或振幅的问题，一般会要求统计出一些最值，比如最长单调递增区间的长度、降幅最大递减区间的幅度等，这些都能用在线统计算法解决，时间复杂度 :math:`O(n)`\ ，空间复杂度 :math:`O(1)`\ ，是效率极高的经典算法。

.. index:: 最长单调区间长度

最长单调区间问题（洛谷P1567）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

最长单调区间问题是指在一个序列中找出长度最长的某类单调区间，可能是要找最长单调递增区间，也可能是单调递减区间。找到并给出它的长度或前后端点，要求采用在线算法。

以求最长单调递增区间的长度为例，在线算法的目标是要在读取元素的循环中一边读一边做判断，读完之后就给出答案。在整个输入序列中，可能有多个单调递增区间，只要能够在读的过程中有办法计算出每一个单调递增区间的长度，那么就可以像找最大值一样找出最长的那个区间长度了。用变量 ``max_len`` 表示已经找到的最长单调递增区间长度，初始值为0。在读取的过程中，用变量 ``cur_len`` 记录当前新找到的单调递增区间的长度。读取过程中每找到一个新的单调递增区间，就比较一下其长度是不是比已经找到过的最长单调递增区间还长，如果是的话就更新 ``max_len`` 的值为 ``cur_len`` 的值。

因此算法的重点是怎样随着读取找出每一个单调递增区间。

根据定义可知：每一个单调递增区间 :math:`[i,j)` 一定开始于这样一个元素，它不大于前面的那个元素，即 :math:`A[i]\le A[i-1]`\ 。因此在读取过程中一旦遇到这样一个元素，就说明从它开始将有一个新的单调递增区间了，这时候就应该把 ``cur_len`` 的值设为1。请注意：哪怕这个单调递增区间只有这一个元素，它也是一个长度为1的单调递增区间，所以这一步操作不会有任何问题。

根据定义又可知：在一个单调递增区间之内，任何一个元素必大于其前一个元素，因此在读取过程中，如果当前读到的元素 :math:`A[k]` 满足 :math:`A[k]\gt A[k-1]`\ ，那么说明当前这个单调递增区间还没有结束，新读到的元素只是延长了它的长度，所以这时候应该让 ``cur_len`` 增加1。

最后还是根据定义可知：每一个单调递增区间 :math:`[i,j)` 一定结束于这样一个元素，它的后一个元素不比它大，即 :math:`A[j]\le A[j-1]`\ 。所以每当读到这样一个元素 :math:`A[j]` 时，同时说明两件事情：首先，当前的单调递增区间结束了，这个区间的长度就是 ``cur_len``\ ；第二，\ :strong:`一个单调递增区间结束了`\ 的判断依据和\ :strong:`一个新的单调递增区间开始了`\ 的判断依据是一样的，即一个单调递增区间的结束必定伴随着一个新的单调递增区间的开始。因此这种情况下要做两件事情，先根据 ``cur_len`` 的值更新 ``max_len``\ ，然后让 ``cur_len`` 的值变成1。

在整个读取过程中，每一次都只需要将当前读到的元素和它的上一个元素做比较，因此并不需要把所有读到的元素都保存下来，我们只需要用一个临时变量 ``last`` 保存好每一次读入的元素，当下一次读入的时候和它做比较就可以了。

现在可以把上面的分析结论整理成算法的框架如下：

.. admonition:: 最长单调递增区间算法

   :math:`\text{MaxIncrementalRange}(A, n):`

      :math:`cur\_len\leftarrow0,max\_len\leftarrow0`

      :math:`\text{FOR  } i \leftarrow 0 \text{  TO  } n-1 \text{  DO}`

         :math:`\text{IF  } A[i] \gt last \text{  THEN}`

            :math:`cur\_len\leftarrow cur\_len+1`

         :math:`\text{ELSE}`

            :math:`max\_len\leftarrow\max\{max\_len, cur\_len\}`

            :math:`cur\_len\leftarrow1`

         :math:`last\leftarrow A[i]`

      :math:`\text{RETURN  } \max\{max\_len, cur\_len\}`

这个算法有三个地方值得一题：

1. 在整个算法最初的时候只给 ``max_len`` 和 ``cur_len`` 设置了初始值0，并没有给 ``last`` 变量赋初始值。所以我们不能假设在读取序列第一个元素 :math:`A[0]` 的时候 ``last`` 会有一个什么样的值，而且仔细想想这个变量确实设置什么初始值都不合适。这样不会有问题吗？

   其实由于 ``cur_len`` 和 ``max_len`` 的初始值都为0，所以 ``last`` 的初始值就不重要了。仔细观察算法，每读取一个元素之后紧接着就进行 ``IF`` 判断，一共有两个分支。当读完 :math:`A[0]` 之后，这条判断语句无论进入哪一个分支，其结果都是让 ``cur_len`` 变成1。如果进入的是 ``ELSE`` 分支，由于此时 ``max_len`` 和 ``cur_len`` 都为0，所以 ``max_len`` 的值也不会发生变化，仍然保持为0。这样的结果是正确的，无论 ``last`` 当时的值是多少，都会开始一个以 :math:`A[0]` 为起点的新的单调递增区间，并且已知的最长单调递增区间长度仍然为0。

2. 根据前面的描述我们知道，如果有一个元素终结了前一个单调递增区间，那么它一定同时开启了一个新的单调递增区间，这就是算法中 ``IF`` 语句的 ``ELSE`` 分支处理的情况。唯独整个序列的第一个元素 :math:`A[0]` 是特殊情况，它总是开启一个新单调递增区间，但它永远不会是前一个单调递增区间的终结，因为在它之前没有元素。

   但是如前所述，我们通过将 ``cur_len`` 的初始值设为0的方法，成功解决了第一个元素的特殊情况。可以这样理解，现在它不光开启了一个新的单调递增区间，而且终结了前一个“长度为0的虚拟的”单调递增区间。所以算法中并不需要对 :math:`A[0]` 做任何特殊处理，和其他元素做完全一样的处理就可以了，算法因此变得简洁。

3. 在读取完所有元素之后，算法应该已经知道了最长的单调递增区间的长度了，但这个长度并不是 ``max_len``\ ，而是 ``cur_len`` 和 ``max_len`` 二者中的大者，这是这个算法最大的坑点。

   请别忘了，最长的单调递增区间有可能位于整个序列的尾部，即以最后一个元素 :math:`A[n-1]` 结尾。这种情况下，循环没有机会读到它的下一个元素，也就没有机会运行下一次 ``IF`` 判断，也就没有机会进入到 ``ELSE`` 分支里面更新 ``max_len`` 的值。这最后一次更新需要留到循环结束之后去做！


.. index:: 【统计天数】, 〖洛谷P1567〗

下面我们通过一个实际的例题（洛谷P1567，统计天数）来看看最长单调递增区间统计问题的代码和应用。

**题目描述**

炎热的夏日，KC 非常的不爽。他宁可忍受北极的寒冷，也不愿忍受厦门的夏天。最近，他开始研究天气的变化。他希望用研究的结果预测未来的天气。经历千辛万苦，他收集了连续 :math:`N(1 \le N \le 10^6)` 的最高气温数据。现在，他想知道最高气温一直上升的最长连续天数。

**输入格式**

第 1 行：一个整数 :math:`N`。:math:`1 \le N \le 10^6`\ 。

第 2 行：:math:`N` 个空格隔开的整数，表示连续 :math:`N` 天的最高气温。:math:`0 \le 最高气温 \le 10^9`\ 。

**输出格式**

1 行：一个整数，表示最高气温一直上升的最长连续天数。

**输入输出样例**

输入：

.. code-block:: none

   10
   1 2 3 2 4 5 6 8 5 9

输出：

.. code-block:: none

   5

这就是一个彻头彻尾的求最长单调递增区间长度的题，难度系数入门级。用上面的算法编写出C++代码，然后提交，AC：

.. literalinclude:: ../../codes/221_p1567.cpp
   :language: c++


提交后判题结果：

.. image:: ../../images/221_p1567.png


此题应该没有多少难度，但是有几个问题值得思考和尝试一下：

.. admonition:: 思考

   1. 如果要求的是最长单调递减区间，算法要怎样改动？
   2. 如果要求的是最短单调区间，算法需要做怎样的改动？
   3. 如果要求的不是区间长度，而是区间的两个端点，算法要如何改动？
   4. 如果是要统计普通的增减区间，不一定非要单调，算法又该如何改动？


.. index:: 最大单调区间振幅

最大单调区间振幅
^^^^^^^^^^^^^^^^^^^^^^^^

上面的算法经过简单的改动就可以适用于解决最大单调区间振幅问题，也就是找出振幅最大的某类单调区间，给出它的振幅。可以是单调递增区间，也可以是单调递减区间。

仍然以求最大的单调递增区间增幅为例。假设在要统计的数列 :math:`A=\{a_n\}` 中，某一连续段 :math:`\{a_i,\dots,a_j\}` 是一个单调递增数列，它的增幅是 :math:`Amp(i,j)=a_j-a_i`\ 。那么实际上这个增幅可以表示为：

.. math::

   \begin{align}
   Amp(i,j)
   =&Amp(i,j-1)+(a_j-a_{j-1})\\
   =&Amp(i,j-2)+(a_{j-1}-a_{j-2})+(a_j-a_{j-1})\\
   =&\cdots\\
   =&(a_{i+1}-a_i)+(a_{i+2}-a_{i+1})+\cdots+(a_{j-1}-a_{j-2})+(a_j-a_{j-1})=a_j-a_i
   \end{align}


这就意味着我们可以随着元素的读入，逐步地累积计算出一整个单调递增区间的增幅。我们可以继续沿用前面求最长单调递增区间长度的算法思路，用两个变量 ``max_amp`` 和 ``cur_amp`` 分别表示已经读到过的最大单调递增区间增幅和当前新读到的单调递增区间增幅。每读入一个元素，先判断它是否处于一个单调递增区间里，如果是那么相应增加当前单调递增区间的增幅；若不是则说明上一个单调递增区间结束了，那就根据 ``cur_amp`` 的大小修正 ``max_amp``\ ，再把 ``cur_amp`` 重置为0，表示一个新的单调递增区间即将开始。注意，现在 ``cur_amp`` 是重置为0而不是1。

另外，在求最大振幅的时候，用于保存上一个元素的变量 ``last`` 是必须要正确初始化的。事实上，正确初始化这个变量并不简单。如果是统计单调递增区间的，那么这个变量的初始值必须确保一定大于等于序列的第一个元素；如果要统计的是单调递减区间，那么它的初始值必须确保小于等于序列的第一个元素。这是为什么？这个规则的原理请一定要想明白。

但真正的麻烦是这个规则有时候难以实现，因为并不是任何时候我们都能实现知道序列中元素的取值范围，怎么办？办法很简单，这个变量的初始值的作用无非是虚拟一个 :math:`A[0]` 之前的元素出来，供真正的第一个元素 :math:`A[0]` 进行增减性判断，那么我们何不直接把这个变量直接初始化为 :math:`A[0]`\ ，然后从 :math:`A[1]` 开始读取元素呢？

下面是求最大单调递增区间增幅的代码，请对照算法说明读懂代码，并和前面的最长单调递增区间长度算法做一对比。

.. literalinclude:: ../../codes/221_largest_amp.cpp
   :language: c++

.. admonition:: 思考

   1. 怎样求最大单调递减区间降幅？
   2. 怎样求最小单调区间振幅？
   3. 怎样改为适用于统计普通递增或递减区间的振幅问题？

.. admonition:: 练习

   完成前面的思考问题，编写相应的程序并测试。

