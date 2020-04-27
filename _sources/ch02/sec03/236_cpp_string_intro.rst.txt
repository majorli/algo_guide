C++ string简介
++++++++++++++++++++++

C++ string是C++标准模板库(STL)提供的一个特殊的容器类，是一种封装好的定义完好的字符串类型，而不再是C-string那样借用字符型数组来实现的“半成品”样子。相比C-string，C++ string的功能更加强大和完善，更加安全可靠，也更加易用，是一种真正的类型，这是它的优点。它的缺点是处理速度慢于C-string，灵活度也略微欠缺。在一般的算法程序中，C++ string是更加推荐使用的字符串表示方式。只有极少数对运行速度有苛刻要求、处理的字符串规模极大的题目，使用C++ string可能会导致TLE，这时候就必须改用C-string了。

本节我们介绍C++ string的使用方法，在本节以后我们将开始大量采用C++ string来表示字符串。

C++ string的成员函数有很多，同一个函数也常会有多个参数不同的版本（C++函数重载），不可能在这里一一说明。我们仅对算法程序中常见的用法进行分类说明，掌握这些常见用法就可以基本掌握C++ string，足以应付绝大多数算法编程问题。要想更深入地了解它，可阅读相关的书籍和资料，比如《C++ Primer Plus》。


常见用法
^^^^^^^^^^^^^^^^

**1. 定义、构造器和赋值**

要使用C++ string，首先要在程序开头引入 ``string`` 库，并使用命名空间 ``std``\ 。然后在程序中可以用类型名 ``string`` 来定义具体的C++ string变量，或者直接简称为string。

.. hint::

   按照面向对象编程的术语来说，STL库提供的所有类型，包括 ``string`` 和其他各种容器，例如 ``vector`` 等，都叫做\ :strong:`类(class)`\ ，类定义了一些复杂的数据类型，它们有自己的数据（成员变量）和功能（成员函数），类的具体变量叫做\ :strong:`对象(object)`\ 。这些都是面向对象编程的核心概念，在学习算法编程的时候，我们可以暂且把类就当做是一些数据类型，把对象就称为变量。

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

   另外，我们以前学过，局部变量在定义时如果没有被设置初值，那它的值就是不确定的，C++不会自动初始化局部变量。但是这里局部变量 ``s1`` 没有被初始化，可实际上它还是被初始化为空字符串 ``""`` 了！这是为什么呢？我们前面提到过，C++ string是一个类，不是普通的数据类型。而类有一种特殊的叫做\ :strong:`构造器`\ 的成员函数，在定义类的对象时无论如何会有一个构造器被执行，用来“构造”出一个实实在在的对象。所以 ``string s1;`` 这样一句看上去什么都没有指定的普通的局部变量定义，实际上也调用了C++ string类的默认构造器，它会把 ``s1`` 构造成一个空字符串 ``""``\ 。

   请注意：C++语言允许我们对自定义的结构（struct）类型也定义构造器。

   BTW，构造器这种东西，大多数纯C++程序员更习惯叫它\ :strong:`构造函数`\ ，而Java程序员更喜欢称其为构造器。

C++ string远不止构造一个空字符串这么一种简单的默认构造器，它还有很多种其他构造器，通过不同的参数表来区分。在定义string时可以在变量名后面像函数调用一样用一对括号传入一些特定的参数来调用与之对应的某一个构造器，这样就能根据需要灵活地构造新string。最常用的几种构造方式如下面的示例所示：

.. code-block:: c++

   string s2("ABC");  // 用一个字符串来构造，s2 = "ABC"
   string s3(4, 'A');   // 用指定个数的同一字符来构造，s3 = "AAAA"，即4个'A'，注意参数类型是char，用单引号
   string s4("ABCDE", 1, 3);    // 用一个字符串的子串来构造，s4 = "BCD"，即"ABCDE"从位置1开始，长度为3的子串

上面注释中所说的字符串，可以是字符串字面量，也可以是C-string，也可以是另一个C++ string，所以构造方式是很多样很灵活的。比如下面这段程序，请想一想 ``s1`` 到 ``s6`` 分别会被构造成什么？然后自己运行一遍试试。

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

C++ string就像其他常见的内置数据类型变量一样，可以直接用等号进行赋值。这相较于C-string又是一大进步。对string进行赋值时，等号右边可以是一个字符串字面量，可以是另一个string，可以是一个C-string，甚至可以是一个字符。例如：

.. code-block:: c++

   string s1 = "ABC";   // 使用C-string字面量进行赋值，直接赋初始值
   string s2, s3, s4;
   s2 = 'x';            // s2被赋值为一个单字符的字符串，"x"，但是切记唯有这种赋值方式不能用于赋初始值！
   s3 = s1;             // 使用另一个C++ string进行赋值
   char s[] = "Hello World";
   s4 = s;              // 使用C-string变量进行赋值


**2. 长度、比较、拼接和交换**

使用成员函数 ``string::size()`` 可以获取一个string的长度：

.. code-block:: c++

   string s = "Hello World!";
   cout << s.size() << endl;    // 输出s的长度，12

C++ string支持直接用六个关系运算符 ``==, !=, <, >, <=, >=`` 进行字典序比较，这就非常的自然和谐了，相较于C-string又是一大进步。它们的用法和用于数值大小比较时完全一样，只是比较的规则是字符串的字典序，这里就不再举例说明了。

下面看一下C++ string的字符串拼接功能，即把多个字符串首尾相接起来形成一个新的字符串。例如连接 ``"Hel"`` 和 ``"lo"`` 就可以生成一个新字符串 ``Hello"``\ 。C++ string采用加法运算符 ``+`` 来实现拼接，非常自然，毫无违和感：

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

字符串拼接在复杂的文本处理类题目中经常会用到，传统的C-string要实现复杂拼接是很费力气的，\ ``cstring`` 库提供的 ``strcat()`` 函数并不是太好用，而且有数组越限风险。所以这也是C++ string的一个非常有用的改进。

C++ string还有一个很实用的小功能：交换内容。使用成员函数 ``string::swap()`` 可以实现两个string内容的互换：

.. code-block:: c++

   string s1("Math"), s2("Chines");
   s1.swap(s2);         // s1变成"Chines"， s2变成"Math"



**3. 子串操作**

*(1) 查找*

C++ string具有多种灵活易用的子串或字符查找功能，它们都是以string的成员函数的方式来提供的，它们的返回值都是子串或字符在这个string中的位置（即第一个字符出现的位置）。如果查不到，则会返回一个叫做 ``string::npos`` 的常量。``string: :npos`` 是一个定义好的静态常量，用这个名字就可以直接使用。这些函数如下：

``string::find()``\ ：从前往后查找子串或字符出现的位置。

``string::rfind()``\ ：从后往前查找子串或字符出现的位置。

``string::find_first_of()``\ ：从前往后查找何处出现另一个字符串中包含的字符。例如：

.. code-block:: c++

   s1.find_first_of("abc");  // 查找s1中第一次出现"abc"中任一字符('a'或'b'或'c')的位置

``string::find_last_of()``\ ：从后往前查找何处出现另一个字符串中包含的字符。

``string::find_first_not_of()``\ ：从前往后查找何处出现另一个字符串中没有包含的字符。

``string::find_last_not_of()``\ ：从后往前查找何处出现另一个字符串中没有包含的字符。

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

   这几个查找函数的用法是类似的，它们至少接收一个参数，即要查找的子串或字符或以字符串形式表示的字符集。这是最基本的用法，如果是从前向后的正向查找就从首字符开始，如果是反向查找则从尾字符开始找起。

   它们也都可以接收第二个可选参数，用来指示一个开始查找的位置，表示查找要从这个位置开始，而不是从默认的头或尾开始。

   当然它们还有其他的用法，但记住上面两种最常用的一般来说就足够了，如果有兴趣可以去查找相关的书籍资料自行了解。

C++ string除了在子串或字符查找功能上相较于C-string进行了增强以外，还提供了一系列C-string时代没有现成提供的新功能，而自己编程实现这些功能往往是比较麻烦，容易引起错误的。

*(2) 求取*

``string::substr()`` 可以用来求出一个子串，以一个新的C++ string的方式返回这个子串。

它接收两个参数：子串首字符位置和长度，其中第二个参数子串长度为可选参数。调用时，如果省略了子串长度参数或首位置加长度超过了字符串长度，则求出来的子串就是从首位置开始一直到字符串结尾的部分。例如：

.. code-block:: c++

   string s1 = "this is C++";
   string s2 = s1.substr(2, 5);    // s2 = "is is"
   s2 = s1.substr(2);              // s2 = "is is C++"

.. important::

   在C++ string的惯例里，总是用一个起始位置和一个长度来表示子串，例如子串(2,4)表示从位置2（第三个字符）开始，长度为4个字符的子串。这和其他容器中用左闭右开区间表示一段范围的惯例是不同的。

*(3) 替换*

``string::replace()`` 可以用来替换子串。请看示例：

.. code-block:: c++

   string s1("Henry Skywalker");
   s1.replace(1, 2, "smart", 2, 2); // 用"smart"的子串(2,2)，即"ar"，替换s1的子串(1,2)，即"en"
   cout << s1 << endl; // s1 = "Harry Skywalker"
   s1.replace(7, 6, 2, 't'); // 用2个't'替换s1的子串(7,6)，即"kywalk"
   cout << s1 << endl; // s1 = "Harry Stter"
   int n = s1.find('S'); // 查找字符'S'的位置，n = 6
   s1.replace(n, 1, "Po"); // 将子串(n,1)，即"S"，替换为"Po"
   cout << s1 << endl; // s1 = "Harry Potter"

*(4) 删除*

``string::erase()`` 用于从一个string中删除一个指定的子串，它也可以不指定子串长度。请看示例：

.. code-block:: c++

   string s1("Harry the Potter the Great");
   s1.erase(6, 4); // 删除子串(6, 4)，s1 = "Harry Potter the Great"
   s1.erase(12); // 省略子串长度，表示删除位置12及其后面的所有字符，s1 = "Harry Potter"

*(5) 插入*

``string::insert()`` 用于在一个string的指定位置处插入一个子串或若干个字符：

.. code-block:: c++

   string s1("H Potter"), s2("==***==");
   s1.insert(1, "arry"); // 在位置1处插入字符串"arry"，s1 = "Harry Potter"
   s1.insert(s1.size(), s2, 2, 3); // 在s1的最后插入s2的子串(2,3), s1 = "Harry Potter***"
   s1.insert(0, 3, '*'); //在位置0，即s1的开头插入3个字符'*'，s1 = "***Harry Potter***"

.. warning::

   使用 ``insert()`` 函数在string中插入子串或字符，指定的插入位置必须大于等于0，且不能超过原字符串的长度，否则会在运行时报错（out of range）并中止程序的运行。


``string::append()`` 用于在一个string的末尾添加子串或若干个字符。

这个成员函数除了不需要提供插入位置这个参数以外，其他用法和 ``string::insert()`` 完全一样。例如上面例子中的第3行就可以改写成：\ ``s1.append(s2, 2, 3);``\ ，这种写法和原先的写法在功能上是完全一样的，但是在运行速度上却要略微快一些，当然最重要的是写代码时也简单方便不少。

.. tip::

   当要在一个string的末尾添加另一个string时，一共有三种写法：

   1. 使用 ``string::insert()``\ ，位置参数为原字符串的长度。
   2. 使用 ``string::append()``\ 。
   3. 使用C++ string的连接（加法）运算：例如 ``s1 += s2``\ 。

   上面三种方法，最方便也最快速的是使用 ``string::append()``\ ，凡遇此类场景，请务必使用它。


``string::push_back()`` 用于在一个string的末尾添加单个字符。

调用方法非常简单，只要提供一个 ``char`` 型参数即可。它的运行速度非常之快，在某些场景下会非常有用。

比如当需要快速读取文本型数据的时候。我们知道C++ string只能通过C++的IO流进行读写，IO流配上C++ string的速度是比较慢的。这时可以配合速度最快的 ``getchar()`` 函数进行快速读取。例如下面这个小函数可以实现非常高速的按行读取C++ string。

.. literalinclude:: ../../codes/236_getline.cpp
   :language: c++

另外，当需要按照一定规律逐个字符生成字符串时这个函数也非常有用。


**4. 迭代器**

每一种C++ STL库提供的模板类型都有一对称为\ :strong:`迭代器（iterator）`\ 的东西，分别为首迭代器和尾迭代器，C++ string也不例外。

一般对于算法编程，迭代器用得并不多，可以说绝大多数情况下完全可以不使用迭代器。但是对于大型软件开发或极为复杂的算法程序编制，迭代器有时候就会变得很有用，而且能提高运行速度。那么什么是迭代器？可以说得很复杂，但也可以理解得很简单，目前我们简单地把它理解为一种“包装过的指针”就可以了。

对于C++ string，每一个具体的string都有一头一尾这一对迭代器，分别用成员函数 ``string::begin()`` 和 ``string::end()`` 来获取，它们的数据类型很长，叫做 ``string::iterator``\ 。其实所有的STL模板类型的迭代器都是类似格式的数据类型，例如int型向量 ``vector<int>`` 的迭代器类型名就叫做 ``vector<int>::iterator``\ 。

首迭代器始终指向string的头部，即位置0；尾迭代器始终指向string的尾部后面一个位置（类似于C-string中末尾的结束符 ``'\0'`` 所在的位置）。程序中可以定义自己的迭代器变量，使用首迭代器或尾迭代器来初始化它，之后就可以像指针一样使用它了。看一个简单的例子就会很清楚迭代器的用法了，下面这个示例程序逐个字符的依正向和反向两个方向输出一个字符串：

.. code-block:: c++

   #include <iostream>
   #include <string>
   
   using namespace std;
   
   int main()
   {
           string s = "Hello";
           string::iterator it;
           for (it = s.begin(); it != s.end(); ++it) // 可以像指针一样做++运算和比较运算
                   cout << *it; // 可以和指针一样用 * 运算来获取它指向的值
           cout << endl;
           // 上一个循环结束时，迭代器it等于s.end()，这是一个虚拟的位置，位于s最后一个字符之后
           while (--it >= s.begin()) // 先--，然后判断是否小于首迭代器
                   cout << *it;
           cout << endl;
   
           return 0;
   }

运行后会输出下面的结果：

.. code-block:: none

   Hello
   olleH

.. tip::

   指针的大部分用法，都可以依样画葫芦地照搬照抄用于迭代器。（但千万记住，迭代器不是指针，而是一种“包装过的指针”，至于怎么包装的，目前不需要深究。）


输入输出
^^^^^^^^^^^^^^^^

使用C++ string来表示字符串时，只能用C++的IO流来进行输入输出。

.. hint::

   C++的IO流同样也可以实现传统的C-string的输入输出，例如：

   .. code-block:: c++

      char s[101];
      cin >> s;
      cout << s << endl;
   
   这样的程序是完全正确的，但是无法保证输入的字符串会不会超长。所以一般还是建议C++ string使用IO流，而C-string则使用C标准IO。

**输出**

输出C++ string特别简单，只要使用 ``cout <<`` 运算即可。例如：

.. code-block:: c++

   string s("Harry Potter");
   cout << s << " is great!" << endl;

**输入**

C++ string的输入和C-string的情况一样，分为按单词输入和按行输入两种。

使用 ``cin >>`` 运算可以方便地实现按单词输入C++ string。例如：

.. code-block:: c++

   string s1, s2, s3;
   cin >> s1; // 输入一个单词形式的字符串到s1中
   cin >> s2 >> s3; // 先后输入两个单词形式的字符串到s2和s3中，中间以至少一个空白符(空格、tab、换行)分隔

使用 ``getline()`` 函数按行输入字符串。C++的这个函数非常好用，它会正确地读取到一行的末尾（第一次遇到换行符），行尾的换行符 ``'\n'`` 会从输入流中被读走并抛弃，不会像 ``cstdio`` 库的 ``fgets()`` 函数那样把换行符保留在字符串里，毕竟大多数情况下我们都不需要这个换行符。

``getline()`` 的使用方法也很简单，例如：

.. code-block:: c++

   string s;
   getline(cin, s); // 从标准输入流cin中读取一行字符串放入s中

.. warning::

   千万要记住，我们这里说的是函数 ``getline()``\ ，它用于按行读取C++ string。
   
   容易混淆的是，输入流 ``cin`` 也有一个成员函数名字叫 ``getline()``\ ，它是用于按行读取C-string的，是 ``cstdio`` 库 ``fgets()`` 函数的IO流版本，除了它会把行尾的换行符抛弃掉以外，它的用法和 ``fgets()`` 完全一样。
   
   二者绝对不要搞混淆，我们在使用C++ string时，要用 ``getline()`` 函数，而不是输入流的成员函数 ``cin.getline()``\ 。


这里顺便介绍一下C++的文件IO流。我们都知道，\ ``cstdio`` 库除了标准IO函数，例如 ``printf()/scanf()`` 等以外，还有一套用法和标准IO完全一致的文件IO函数，例如 ``fprintf()/fscanf()``\ ，用来从磁盘上的文本文件中读取数据和将输出数据写入到磁盘文本文件里去。C++的IO流当然也会有这么一套对应的流，称为\ :strong:`文件IO流`\ ，或简称\ :strong:`文件流`\ 。

要使用C++文件流，要同时引入 ``iostream`` 和 ``fstream`` 两个库，然后和传统的方法类似，在程序中要分四步走：

1、建立具体的文件流对象，或者你可以理解为 ``std::fstream`` 型的变量。

   类似于C标准IO的定义文件句柄变量：\ ``FILE *fin, *fout``\ 。

2、为文件流对象打开一个具体的文件。

   类似于C标准IO的为文件句柄打开具体文件：\ ``fin = fopen("file1", "w");``\ 。

3、像使用 ``cin/cout`` 一样使用已经打开的文件流对象，用 ``<<`` 或 ``>>`` 运算进行输入输出。

   类似于C标准IO的 ``fprintf()/fscanf()`` 等函数的使用。

4、读写完毕后关闭文件流对象。

   类似于C标准IO的关闭文件句柄：\ ``fclose(fin)``\ 。

例如从文件 ``a.in`` 中读取2个整数，计算其乘积并将结果写入文件 ``a.out`` 中的程序如下：

.. code-block:: c++
   
   #include <iostream>
   #include <fstream>
   
   using namespace std;
   
   int main()
   {
           fstream fin, fout;           // 建立文件流对象
           fin.open("a.in", fstream::in);       // 打开文件用于输入
           fout.open("a.out", fstream::out);    // 打开文件用于输出
   
           int a, b;
           fin >> a >> b;               // 还是那个配方
           fout << a * b << endl;       // 还是那个味道
   
           fin.close();                 // 关闭输入文件流
           fout.close();                // 关闭输出文件流

           return 0;
   }


下面再看一个复杂一点的例子。前面我们演示过用 ``getline()`` 函数从标准IO流按行读取一个字符串，那时候函数的第一个参数用的是 ``cin``\ 。实际上它可以是任何一个输入流，包括输入文件流。下面这个例子，使用C++文件流和 ``getline()`` 函数逐行读取文本文件 ``test.in`` 并输出到文件 ``test.out`` 中：

.. code-block:: c++

   #include <iostream>
   #include <fstream>
   
   using namespace std;
   
   int main()
   {
           fstream fin, fout;
           fin.open("test.in", fstream::in);
           fout.open("test.out", fstream::out);
   
           string s;
           while (getline(fin, s)) // 一旦文件读取完毕或出错，getline()的返回可以被判断为false
                   fout << s << endl; // 注意getline()会丢弃换行符，所以输出时要自己加上换行
   
           fin.close();
           fout.close();
   
           return 0;
   }


自己编一个测试用的文本文件 ``test.in``\ ，里面要放一些空行。运行上面的程序看看是不是一模一样地复制成为了 ``test.out``\ 。由此测试可以看出，\ ``getline()`` 在按行读取时遇到空行也会毫不犹豫地准确读取进来。读一个空行会得到一个空字符串 ``""``\ 。


最后再介绍一下快速读取单个字符的方法。\ ``cstdio`` 库有一个号称速度最快的单个字符读取函数 ``getchar()``\ ，与之对应，C++的IO流也有一个这样的函数：成员函数 ``get()``\ 。用法也和 ``getchar()`` 函数几乎一样：

.. code-block:: c++

   int ch;          // 用int来存放char，还记得为什么吗？
   ch = cin.get();  // 从标准输入流读取一个字符放到ch中，如果读到流结束则范围-1（这就是用int的原因）

还记得以前学过的 ``cstdio`` 版的鹦鹉学舌程序吗？现在来看看C++输入输出流的新版：

.. code-block:: c++

   #include <iostream>
   
   using namespace std;
   
   int main()
   {
           int ch;
           while ((ch = cin.get()) != -1)  // cstdio版：while ((ch = getchar()) != EOF)
                   cout << (char)ch;  // 注意要强转数据类型为char，否则输出的会是一个数字
   
           return 0;
   }

作为编程练习，请写一个文件流版本的鹦鹉学舌。

.. warning::

   事实上 ``cin.get()`` 函数还有好几种别的用法，甚至可以用来按行读取C-string形式的字符串。但是要记得，C-string归 ``cstdio`` 库管，无论是 ``cin.get()`` 还是前面提到过的 ``cin.getline()`` 都不如直接用 ``cstdio`` 库的 ``fgets()`` 更好。C++在其输入流对象中实现对应C-string的功能，只是为了其自身的功能完善性，事实上它们在使用时都或多或少的有一些问题，不太好用。

   所以切记，我们只推荐用 ``int ch = cin.get()`` 这一种快速读取单个字符的用法，不要去深究和尝试它的其他用法。



字符串流
^^^^^^^^^^^^^^^^

如果对C语言标准IO了解得比较深入的话就会知道，有这样一对把字符串当做输入输出设备的函数 ``sscanf()/sprintf()``\ 。它们的基本用法和普通的 ``scanf()/printf()`` 是一模一样的，但调用时还需提供一个C-string参数。\ ``sscanf()`` 函数就从这个字符串中去提取数据，而不是从键盘或者磁盘文件；\ ``sprintf()`` 则会把输出的信息写入到这个字符串里，而不是显示在屏幕上或者写到磁盘文件里去。

C++也提供了这样的功能，称为\ :strong:`字符串流`\ 。当然了，这个C++的字符串流要使用C++ string，不能用C-string。字符串流在算法编程中的实用价值不高，而且速度相当慢。有时候即便用字符串流会比较方便，有经验的人也会避而不用，宁可另寻他法。但是也有一些情况用上它确实会非常方便。我们先通过一个简单的示例来看看字符串流的基本用法，然后再看一种比较典型的用例。

要使用字符串流，需要引入 ``sstream`` 库。在 ``sstream`` 库中定义有表示字符串输入流的类型 ``istringstream`` 和表示字符串输出流的类型 ``ostringstream``\ 。用法不难，且一般只需要掌握最基本的用法即可，可以通过下面这个示例程序来学习。

假设在一个字符串中保存了若干个学生的姓名、学号和平均分GPA。字符串开头为学生人数，后面每位学生三个数据段，依次为姓名、学号和GPA分数。现在我们从这个字符串中提取所有这些信息，然后对用一种比较整齐的表格形式输出。

.. literalinclude:: ../../codes/236_ss.cpp
   :language: c++

运行的结果如下：

.. code-block:: none

   No.     Name    GPA
   1       Alice   5
   2       Bob     4.7
   3       Carol   3.5

在实际应用中，尤其是在一些实用工具的编写中，常会需要把数值在“数”和“文本”两种方式之间相互转换。在C语言标准库 ``cstdlib`` 中有一些用于将C-string转换为数值类型的库函数，例如 ``atoi()`` 函数，可以把一个内容为整数的C-string（例如 ``"123"``\ ）转换为 ``int`` 型数值，\ ``atof()`` 函数则把内容为小数的C-string（例如 ``"3.14"``\ ）转换为 ``double`` 型浮点数。数值类型转为C-string则可以通过 ``sprintf()`` 函数来实现。

在C++11（2011年标准）以前，并没有提供把C++ string转换为数值类型的函数。不幸的是NOI和大多数算法竞赛所用的C++版本都是C++98（1998年标准）。那要怎么进行“数”和“文本”的互换呢？方法有很多，但是在数据量不大的情况下，我们可以利用字符串流来方便的实现。

.. code-block:: c++

   string s1("123"), s2("3.14");
   int a;
   double pi;
   istringstream strin; // 建立一个新的字符串输入流，并没有连接到任何string上
   strin.str(s1);       // 连接到string s1上去
   strin >> a;          // 从s1读取一个整数，a = 123
   strin.clear();       // 若要重复使用字符串输入流，在连接新的字符串之前必须清空流的所有状态
   strin.str(s2);       // 改为连接到string s2上
   strin >> pi;         // 从s2读取一个双精度浮点数，pi = 3.14
   cout << a << " + " << pi << " = ";
   ostringstream strout;// 创建一个字符串输出流
   strout << a + pi;    // 输出 123 + 3.14 的和
   cout << strout.str() << endl;        // strout.str()返回strout中的内容，类型为string
   // 完整的输出结果为 123 + 3.14 = 126.14

上面这个代码片段，就利用了字符串输入流实现了把C++ string ``s1`` 的内容转换为整数 ``int a``\ ，\ ``s2`` 的内容转换为 ``double pi``\ ，而表达式 ``a + pi`` 的值，\ ``double`` 型的126.14则利用字符串输出流转换为了一个C++ string，即 ``strout.str()`` 的返回值。

另外，字符串流还可以用来方便地实现一些原本比较麻烦的操作，比如字符串的分割与合并等。但是这些操作在算法编程中遇到的确实不多，而且C++字符串流的速度也确实太慢了一点。所以我们就不细说了，有兴趣的可以自己查阅相关资料。

.. admonition:: 练习

   这一节的内容比较多，不通过多次编程实践也很难一下子记住那么多string的用法。所以关键还是要动手练习。

   请把前两节介绍的KMP算法和中心扩展算法，正确地编写一遍C++ string版本。这个练习一定要做！

