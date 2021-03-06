C++模板的妙用
-------------

C++语言提供了一种叫做\ :strong:`模板`\ （template）的技术，用来支持所谓的\ :strong:`泛型`\ （generic types）编程。那么什么叫做泛型呢？简单地说就是使某些特定变量可以支持多种数据类型，比如函数参数、返回值、结构体成员变量等。C++实现泛型编程的具体方式就是使用模板技术。

虽然模板技术更多地被应用在面向对象的工程编程领域，但是它在算法编程中也有自己的用武之地。尤其在数据结构这个部分，模板技术是实现所谓抽象数据类型（ADT）的关键技术。在这里我们先了解一下模板技术的一些典型用法。

**模板函数：让一个函数适用多种数据类型**

通常调用函数时参数的数据类型必须和函数参数表里的定义一致或相兼容。例如下面这个两个整数取大者的函数，我们已经很熟悉了。

.. code-block:: c++
   
   int max(int a, int b)
   {
           return a > b ? a : b;
   }

调用这个函数，两个参数必须是 ``int`` 型或者可以隐式转换为 ``int`` 型的数据类型，比如 ``short`` 和 ``char``\ 。如果是 ``long long`` 或者 ``double``\ ，虽然也可以强制转换为 ``int``\ ，但是不安全，有可能造成错误。如果为每一种数据类型都写一个这样的函数，分别叫做 ``max_int()``、``max_long_long()``、``max_double()`` 等等等等，是不是很傻？用模板技术就可以轻松解决这个问题，先看代码。

.. literalinclude:: ../codes/140_template_1.cpp
   :language: c++
   :emphasize-lines: 3,4

.. note::

   * ``template<...>`` 是一条C++模板指令，写在函数头的前面，这个函数就变成了模板函数。
   * 尖括号里的 ``typename`` 是模板指令的关键字，用来指定这里要使用一个泛型数据类型。
   * 使用 ``template<typename T>`` 指令之后就把紧跟在它后面的那个函数变成了模板函数，这个函数的形参和返回值可以用 ``T`` 来指代数据类型，而不需要确定真实的数据类型。

于是通过这种方式，模板函数 ``max()`` 就实现了适应各种数据类型。如果函数写成声明与定义分离的形式，那么在函数声明和函数定义两处都应该加上相同的模板指令。

.. warning::

   值得注意的是，C++模板技术并没有想象中严格，模板函数能否正确运行完全取决于程序员是否传递了不会引起错误的参数值。例如我们的 ``max()`` 函数，能够正确运行的参数类型应该是数值类型。但如果我们传入了两个C-string：
   
   ``printf("%s is bigger\n", max("abc", "def"));``
   
   程序编译仍会通过，而运行结果八成会告诉我们 ``abc is bigger``\ 。这就不对了，按照字符串比较的规则，明明应该是 ``def`` 更大啊。这是因为C-string不支持小于运算，所以 ``max()`` 函数不适用于比较C-string。但是C++模板并不会对传入的参数类型是否合适进行检验，于是它就一本正经地胡说八道。


C++模板并不限制一个模板函数里的泛型数量，也允许泛型和指定类型混用，所以一个模板函数可以有多个泛型，也可以同时存在指定类型。接下来我们让刚才的 ``max()`` 函数华丽变身为一个更加强大灵活的比较大小函数，它能接收两个不同数据类型的数值，把后一个参数强制转换为前一个参数的类型然后进行比较，返回值也采用前一个参数的数据类型。另外它还接收一个可选的逻辑型参数来指定是用来找较大的值还是较小的值。

.. literalinclude:: ../codes/140_template_2.cpp
   :language: c++
   :emphasize-lines: 3,4

.. note::

   在这个比较函数的参数表中，最后一个逻辑参数 ``bool max = true`` 这样的写法叫做\ :strong:`默认值参数`\ 。对于这样的函数，在调用时可以不提供这个参数，让函数自动使用参数表里指定的默认值。所以我们调用这个函数时可以只提供前两个参数，此时函数就默认选较大的值。
   
   C++允许函数有一个或多个默认值参数，但是它们必须放在参数表的最后面。在任何一个默认值参数之后不能出现普通参数。

上面这段程序的运行结果如下：

.. code-block:: none

   3.141593 is bigger
   -3 is smaller


**模板结构：让成员变量可以适应多种数据类型**

模板结构是实现所谓抽象数据类型的关键技术，在数据结构的领域里会广泛使用到，C++的STL模板库就大量采用了这种技术。

其实它的用法和模板函数没什么太大的区别，并不复杂。例如用结构来定义一份数据表，最多可存放100项数据，可用来存放多种不同数据类型的表格，比如有的表格存放的是整数，有的表格存放的是浮点数等等。普通的方法需要为每一种数据类型的表格定义各自的结构，使用模板结构就可以一种定义、多种用途了。看代码：

.. literalinclude:: ../codes/140_template_3.cpp
   :language: c++
   :emphasize-lines: 6,8,14,22

运行结果：

.. code-block:: none

   sqr(0) = 0
   sqr(1) = 1
   sqr(2) = 4
   sqr(3) = 9
   sqr(4) = 16
   sqr(5) = 25
   sqr(6) = 36
   sqr(7) = 49
   sqr(8) = 64
   sqr(9) = 81
   area of radius 0 circle =   0.00000000
   area of radius 1 circle =   3.14159265
   area of radius 2 circle =  12.56637061
   area of radius 3 circle =  28.27433388
   area of radius 4 circle =  50.26548246
   area of radius 5 circle =  78.53981634
   area of radius 6 circle = 113.09733553
   area of radius 7 circle = 153.93804003
   area of radius 8 circle = 201.06192983
   area of radius 9 circle = 254.46900494

上面这个程序计算了从0到9十个整数的平方以及它们对应半径的圆的面积，分别放在两张表里面，但是表的结构定义只有一个。这就是模板结构的威力。

模板结构的定义方式和模板函数并无二致。声明模板结构变量时，在结构名后面要紧跟一对尖括号，在里面给出和泛型对应的实际数据类型。如果模板结构使用了多个泛型，那么声明变量的时候尖括号里也要按顺序依次给出对应的具体类型，例如：

.. code-block:: c++
   
   template<typename T, typename V>
   struct S {
           T a;
           V b;
   };
   
   S<int, double> s1 = { 10, 3.14159 };

.. _ref_140_template_array:

**模板参数：搞定数组作为函数参数时的种种不爽**

我们知道，数组用作函数参数是一件很恶心的事情，总是有许多不愉快的地方。在传统的C语言里数组作为函数参数时这个参数实际上是一个指针类型的参数，把数组名作为实参传递给函数，形参得到的实际上是指向这个数组头一个元素的指针 ``&a[0]``\ 。因此函数内部的代码并不知道这个数组的长度是多少，我们还需要增加一个额外的参数来告诉函数数组的长度。所以我们的函数参数表会是这样的：

.. code-block:: c++
   
   int sqr_sum(int a[], int size);
   double cube_sum(double data[][], int rows, int cols);
   // 也可以写成指针的方式，下面的两个声明和上面的是等价的
   int sqr_sum(int *a, int size);
   double cube_sum(double **data, int rows, int cols);

即使在函数参数表的数组参数中写上长度值（例如 ``int a[10]``\ ）也是没有用的，写着只是给程序员看看而已，C++语言并不买这个帐，函数内部代码根本不需要管这个数字。

这就造成了数组作为函数参数时的几大问题：

1. 函数参数表变得冗长，尤其是当参数中有多个数组，或者有多维数组的时候。
2. 函数代码容易发生超限错误。
3. 多维数组用指针的指针的...指针表示，非常烧脑，有安全隐患，是任何一个程序员都要避之不及的用法。

用C++模板技术（配合上一点点C++引用）就可以完美地解决数组作为函数参数的种种问题。先来看一个简单的例子，对一个整型一维数组里的所有元素求平方和。

.. literalinclude:: ../codes/140_template_4.cpp
   :language: c++
   :lines: 1-11,22-24,26,27,29-31
   :emphasize-lines: 3,4,7

在这个示例里，我们用C++的模板参数技术解决了传递数组长度的问题，数组的长度作为一个模板参数 ``N`` 被定义在模板中。当调用该函数时，C++会自动把实参数组的真实长度填到这个模板参数里面去，于是函数就简单、安全地获取到了关于数组的一切信息。

这样定义了模板参数的函数也是一种模板函数，数组参数采用C++的\ :strong:`传引用`\ 方式进行传递。传引用的参数和传统的传指针一样，函数代码是可以修改实参的，若想不允许函数修改实参，可以在形参前面加上 ``const`` 修饰。

在一个模板函数里，可以同时存在泛型和模板参数。模板参数也可以有多个，所以完全不用担心参数表里有多个数组或者多维数组的问题。下面是一个较为复杂的例子，计算一个泛型二维数组里各个元素的立方和，并且确保函数不修改原数组里的数值。

.. literalinclude:: ../codes/140_template_4.cpp
   :language: c++
   :lines: 1,2,12-23,25,26,28-31
   :emphasize-lines: 3,4,7,8


怎么样？是不是很完美？害怕指针的我们以后再也不用担心给函数传递数组了。

