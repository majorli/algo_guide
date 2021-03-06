递归与二分
--------------

递归法是算法设计中最为重要的技巧之一，无数的经典算法使用了递归法进行设计，无数的难解之题使用了递归法之后变得思路清晰简洁，无数的实际问题使用了递归法之后得到了更加高效更加完美的解法。事实上我们已经学过一个递归算法：快速幂。学习递归的时候请回过头去看看：:ref:`ref_216`\ ，体会一下它为什么实际上是一个递归算法。

递归是一个数学上的概念，递归法是利用递归方式来构造问题之解的算法设计方法，C++语言中一个函数自己调用自己称为递归调用，是程序实现递归算法的\ :strong:`一种`\ 方法。在这一部分我们将学习什么是数学上递归的概念，递归怎么应用在算法设计中成为递归法，以及怎样用C++语言实现递归算法。我们将会学习几个经典的递归算法例子，也会看到一些滥用或者误用递归法的坏例子。在后面的基础排序算法部分以及后续其他章节中，我们将不断看到递归法的应用，编写各种各样的递归程序。

学习了递归法之后，我们还会介绍一种很常用的递归算法：二分法。二分法利用递归的思路在有序的空间中快速寻找到问题的解，时间复杂度往往能够达到对数时间 :math:`O(\log n)`\ 。二分法非常实用，应用场景也非常多，是算法竞赛的必考考点。普及组阶段往往会考一些单纯的二分算法，比如二分搜索、牛顿迭代法解方程等。提高组及以上阶段的竞赛中，常会考到在复杂算法中应用二分法来提高效率的考题。我们将通过四个例题由浅入深地介绍二分法的应用。

本部分包括以下内容：

* 递归的基本概念
* 经典递归问题：Hanoi塔
* 递归与递推：Fibonacci数列
* 递归与递推：数的计算（洛谷P1028）
* 二分法的基本概念
* 二分迭代法解方程，立方根的计算
* 一元三次方程求解（洛谷P1024）
* 跳石头（洛谷P2678，NOIP2015）
* 切绳子（洛谷P1577）
* 中位数问题

.. toctree::
   :maxdepth: 2

   sec04/241_recursive
   sec04/242_hanoi
   sec04/243_fibo
   sec04/244_lg1028
   sec04/245_bin_search
   sec04/246_cubic_root
   sec04/247_p1024
   sec04/248_p2678
   sec04/249_p1577
   sec04/24A_median

