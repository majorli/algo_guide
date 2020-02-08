C++ string简介
++++++++++++++++++++++

C++ string是C++标准模板库(STL)提供的一个特殊的容器类，是一种封装好的定义完好的字符串类型，而不再是C-string那样借用字符型数组来实现的“半成品”样子。相比C-string，C++ string的功能更加强大和完善，更加安全可靠，也更加易用，是一种真正的类型，这是它的优点。它的缺点是处理速度慢于C-string，灵活度也略微欠缺。在一般的算法程序中，C++ string是更加推荐使用的字符串表示方式。只有极少数对运行速度有苛刻要求、处理的字符串规模极大的题目，使用C++ string可能会导致TLE，这时候就必须改用C-string了。

本节我们介绍C++ string的使用方法，在本节以后我们将一律采用C++ string来表示字符串。

C++ string的成员函数有很多，同一个函数也常会有多个重载版本，不可能在这里一一说明。我们仅对算法程序中常见的用法进行分类说明，掌握这些常见用法就可以基本掌握C++ string的用法，足以应付绝大多数算法编程问题。要想更深入地了解它，可阅读相关的书籍和资料，比如《C++ Primer Plus》。


常见用法
^^^^^^^^^^^^^^^^

**1. 定义、构造器和赋值**

要使用C++ string，首先要在程序开头引入string库，并使用命名空间std。然后在程序中可以用类型名 ``string`` 来定义具体的C++ string变量（以后我们就简称C++ string变量为string）。

.. hint::

   按照面向对象编程的术语来说，STL库提供的所有类型，包括string和其他各种容器（例如 ``vector`` 等），都是\ :strong:`类(class)`，类定义了一些复杂的数据类型，它们有自己的数据（成员变量）和功能（成员函数），类的具体变量叫做\ :strong:`对象(object)`。这些都是面向对象编程的核心概念，在学习算法编程的时候，我们可以暂且把类就当做是一些数据类型，把对象就称为变量。

.. code-block:: c++

   #include <string>

   using namespace std;

   string s;    // 定义了一个全局string，名为s，它的初始值是空字符串 ""

   int main()
   {
           string s1;   // 定义了一个属于main函数的局部string变量s1，它也有初始值，即空字符串 ""
           // ...

           return 0;
   }

.. note::

   在定义string时，和C-string不同的是，我们不需要指定长度，因为string的长度是自动可变长度，这是string的一大优势。

   另外，我们以前学过，局部变量在定义时如果没有被设置初值，那它的值就是不确定的，C++不会自动初始化局部变量。但是这里局部变量s1没有被初始化，可实际上它还是被初始化为空字符串 ``""`` 了！这是为什么呢？我们前面提高过，C++ string是一个类，不是普通的数据类型。而类有一种特殊的叫做\ :strong:`构造器`\ 的成员函数，在定义类的对象时无论如何会有一个构造器被执行，用来“构造”出一个实实在在的对象。所以 ``string s1;`` 这样一句看上去什么都没有指定的普通的局部变量定义，实际上也调用了C++ string类的默认构造器，它会把 ``s1`` 构造成一个空字符串 ``""``。

   请注意：C++语言允许我们对自定义的结构（struct）类型也定义构造器。

   BTW，构造器这种东西，大多数纯C++程序员更习惯叫它\ :strong:`构造函数`，而Java程序员更喜欢称其为构造器。

C++ string远不止构造一个空字符串这么一种简单的默认构造器，它还有很多种其他构造器，通过不同的参数表来区分。在定义string时可以在变量名后面像函数调用一样用一对括号传入一些特定的参数来调用与之对应的某一个构造器，这样就能根据需要灵活地构造新string。最常用的几种构造方式如下面的示例所示：

.. code-block:: c++

   string s2("ABC");  // 用一个字符串来构造，s2 = "ABC"
   string s3(4, 'A');   // 用指定个数的同一字符来构造，s3 = "AAAA"，即4个'A'，注意参数类型是char，用单引号
   string s4("ABCDE", 1, 3);    // 用一个字符串的子串来构造，s4 = "BCD"，即"ABCDE"从位置1开始，长度为3的子串

上面所说的字符串，可以是例子中使用的字符串字面量，也可以是C-string，也可以是另一个C++ string，所以构造方式是很多样很灵活的。比如下面这段程序，请想一想 ``s1`` 到 ``s6`` 分别会被构造成什么？然后自己运行一遍试试。

.. code-block:: c++

   #include <iostream>
   #include <string>
   
   using namespace std;
   
   int main()
   {
           char s[] = "Hello World";
           string s1(s);
           string s2(s, 0, 5);
           string s3("Hello World");
           string s4("Hello World", 6, 5);
           string s5(s3);
           string s6(s5, 3, 5);
           cout << s1 << endl;
           cout << s2 << endl;
           cout << s3 << endl;
           cout << s4 << endl;
           cout << s5 << endl;
           cout << s6 << endl;
   
           return 0;
   }

至于赋值，C++ string就像其他常见的内置数据类型变量一样，可以直接用等号进行赋值。这相较于C-string又是一大进步。更加方便的是，对string进行赋值时，等号右边的表达式类型既可以是另一个string，也可以是一个C-string，甚至可以是一个char。例如：

.. code-block:: c++

   string s1 = "ABC";   // 使用C-string字面量进行赋值，直接赋初始值
   string s2, s3, s4;
   s2 = 'x';            // s2被赋值为一个单字符的字符串，"x"，但是切记唯有这种赋值方式不能用于赋初始值！
   s3 = s1;             // 使用另一个C++ string进行赋值
   char s[] = "Hello World";
   s4 = s;              // 使用C-string变量进行赋值


**2. 长度、比较、连接和交换**

使用成员函数 ``string::size()`` 可以获取一个string的长度：

.. code-block:: c++

   string s = "Hello World!";
   cout << s.size() << endl;    // 输出s的长度，12

C++ string支持直接用六个关系运算符（``==, !=, <, >, <=, >=``）进行字符串的字典序比较，这就非常的自然和谐了，相较于C-string又是一大进步。它们的用法和用于数值大小比较时完全一样，只是比较的规则是字符串的字典序，这里就不再举例说明了。

下面看一下C++ string的一个新功能：字符串连接，即把多个字符串首尾相接起来形成一个新的字符串。例如连接 ``"Hel"`` 和 ``"lo"`` 就可以生成一个新字符串 ``Hello"``。C++ string采用加法运算符 ``+`` 来实现这个操作，使得连接字符串的表达式显得非常的自然，毫无违和感：

.. code-block:: c++

   string s1 = "interest", s2 = "ing", s3 = "ed";

   cout << "He is " + s1 + s3 + " in C++ because C++ is " + s1 + s2 + "." << endl;

请试一试上面这段代码会输出什么。

甚至我们还可以像这样，现在的你们一看就懂：

.. code-block:: c++

   string s1 = "interest";
   string s2 = s1;
   s1 += "ing";         // s1变成 "interesting"
   s2 += "ed";          // s2变成 "interested"

字符串连接操作在复杂的字符串处理，特别是文字处理类的题目中经常会用到，传统的C-string要实现这一功能还是要很花费一些力气的，而且有很大的数组越限风险。所以这也是C++ string的一个非常有用的改进。

C++ string还有一个很实用的小功能：交换内容。使用成员函数 ``string::swap()`` 可以实现两个string内容的互换：

.. code-block:: c++

   string s1("Math"), s2("Chines");
   s1.swap(s2);         // s1变成"Chines"， s2变成"Math"



**3. 子串操作**

*(1) 查找*

C++ string具有多种灵活易用的子串或字符查找功能，它们都是以string的成员函数的方式来提供的，它们的返回值都是子串或字符在这个string中的位置（即第一个字符出现的位置）。如果查不到，则会返回一个叫做 ``string::npos`` 的常量。``string: :npos`` 是一个定义好的静态常量，用这个名字就可以直接使用。这些函数如下：

``string::find()``：从前往后查找子串或字符出现的位置。

``string::rfind()``：从后往前查找子串或字符出现的位置。

``string::find_first_of()``：从前往后查找何处出现另一个字符串中包含的字符。例如：

.. code-block:: c++

   s1.find_first_of("abc");  // 查找s1中第一次出现"abc"中任一字符('a'或'b'或'c')的位置

``string::find_last_of()``：从后往前查找何处出现另一个字符串中包含的字符。

``string::find_first_not_of()``：从前往后查找何处出现另一个字符串中没有包含的字符。

``string::find_last_not_of()``：从后往前查找何处出现另一个字符串中没有包含的字符。

下面是一个C++ string子串、字符查找的示例程序：

.. code-block:: c++

   #include <iostream>
   #include <string>

   using namespace std;
   
   int main()
   {
           string s("I like programming");
           int n;
           if ((n = s.find('i')) != string::npos) // 查找字符'i'出现的位置
                   cout << "'i' is found at " << n << endl;
           if ((n = s.find("like", 3)) == string::npos) // 从位置3，即字符'i'开始查找"like"
                   cout << "\"like\" is not found" << endl;
           if ((n = s.find("program")) != string::npos) // 查找子串"program"
                   cout << "\"program\" is found at " << n << endl;
           if ((n = s.find_first_of("cp")) != string::npos) // 查找第一次出现'c'或'p'的位置
                   cout << "'c' or 'p' is first found at " << n << endl;
           if ((n = s.find_last_of('m')) != string::npos) // 查找最后一个'm'的位置
                   cout << "'m' is last found at " << n << endl;

           // 从位置1开始查找第一个'c'和'p'以外的字符
           if ((n = s.find_first_not_of("cp", 1)) != string::npos)
                   cout << "not 'c' and 'p' is first found at " << n << endl;
   
           return 0;
   }

.. note::

   这几个查找函数的用法是类似的，它们至少接收一个参数，即要查找的子串或字符或以字符串形式表示的字符集。这是最基本的用法，如果是从前向后的正向查找就从第一个字符（位置0）开始，如果是反向查找则从最后一个字符开始找起。

   它们也都可以接收第二个可选参数，用来指示一个开始查找的位置，表示查找要从这个位置开始，而不是默认的从头部（或从尾部）开始。

   当然它们还有其他的用法，但记住上面两种最常用的一般来说就足够了，如果有兴趣可以去查找相关的书籍资料自行了解。

C++ string除了在子串或字符查找功能上相较于C-string进行了增强以外，还提供了一系列C-string时代没有现成提供，需要自己编程实现的新功能（而这些功能在使用C-string时往往是比较麻烦，很容易引起错误的）。

*(2) 求取*

``string::substr()`` 可以用来求出一个子串，以一个新的C++ string的方式返回这个子串。

它接收两个参数：子串首字符位置和长度，其中第二个参数子串长度为可选参数。调用时，如果省略了子串长度参数或首位置加长度超过了字符串本身的长度，则求出来的子串就是从首位置开始一直到字符串结束的部分。例如：

.. code-block:: c++

   string s1 = "this is C++";
   string s2 = s1.substr(2, 5);    // s2 = "is is"
   s2 = s1.substr(2);              // s2 = "is is C++"

.. admonition:: 惯例

   在C++ string的惯例里，总是用一个起始位置和一个长度来表示子串，例如子串(2,4)表示从位置2（第三个字符）开始，长度为4个字符的子串。

*(3) 替换*

``string::replace()`` 可以用来替换子串。请看示例：

.. code-block:: c++

   string s1("Henry Skywalker");
   s1.replace(1, 2, "smart", 2, 2); // 用"smart"的子串(2,2)，即"ar"，替换s1的子串(1,2)，即"en"
   cout << s1 << endl; // Harry Skywalker
   s1.replace(7, 6, 2, 't'); // 用2个't'替换s1的子串(7,6)，即"kywalk"
   cout << s1 << endl; // Harry Stter
   int n = s1.find('S'); // 查找字符'S'的位置，n=6
   s1.replace(n, 1, "Po"); // 将子串(n,1)，即"S"，替换为"Po"
   cout << s1 << endl; // Harry Potter

*(4) 删除*

``string::erase()`` 用于从一个string中删除一个指定的子串，它也可以不指定子串长度。请看示例：

.. code-block:: c++

   string s1("Harry the Potter the Great");
   s1.erase(6, 4); // 删除子串(6, 4)，此后s1变成 "Harry Potter the Great"
   s1.erase(12); // 省略子串长度，表示删除位置12及其后面的所有字符，此后s1变成 "Harry Potter"

*(5) 插入*

``string::insert()``

``string::push_back()``

``string::append()``




**4. 迭代器**




输入输出
^^^^^^^^^^^^^^^^




字符串流
^^^^^^^^^^^^^^^^




（待续）
