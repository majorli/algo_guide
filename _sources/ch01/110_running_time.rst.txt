测定程序运行时间
----------------

算法编程极其重视速度，学习和测试算法经常需要精确测定程序的运行时间。使用 ``ctime`` 标准库中的时钟函数 ``clock()`` 可以方便地完成这一任务。

.. code-block:: c++

   clock_t clock();

``clock_t`` 是 ``ctime`` 库中定义的一个用来表示计算机时钟数的数据类型，实际上是一个 ``long int``\ 。

每次调用 ``clock()`` 函数，它就返回从程序开始运行到现在所经过的计算机时钟数，所以只要在某段程序的前后分别调用这个函数，得到的前后两个时钟数之差就是运行这段程序所耗费的时钟数。而计算机时钟是一个非常精准的微秒甚至纳秒级的计时器。为了将计算机时钟数转换为日常使用的时间单位，需要用到 ``ctime`` 库中的一个预定义常量 ``CLOCKS_PER_SEC``\ ，它等于这台计算机上每秒钟的时钟数。 

将时钟数除以 ``CLOCKS_PER_SEC`` 就能得到以秒为单位的运行时间。当然秒这个单位对于算法程序来说太大了，一般至少要以毫秒为单位。将时钟数除以 ``CLOCKS_PER_SEC / 1000`` 就能得到毫秒级的运行时间。


下面的示例程序使用一个单循环计算从1到100,000这十万个正整数的平方，结果存入一个数组。为了测试运行速度，我们加入了测定运行时间的功能。

.. literalinclude:: ../codes/110_running_time.cpp
   :language: c++
   :emphasize-lines: 6,7,11,16-17

运行这个小程序得到结果可能是这样的（具体数值因不同的运行环境而异）：

.. code-block:: none

   100000 times of i^i computed using a for loop.
   Start at 1944 clocks, end at 3960 clocks.
   Time elapsed = 2016 clocks.
   CLOCKS_PER_SEC = 1000000
   In ms, time elapsed = 2 ms.

