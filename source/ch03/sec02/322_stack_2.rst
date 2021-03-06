栈的应用：表达式求值
++++++++++++++++++++

求表达式的值是最常见的数学运算之一，也是计算机软件最常见的任务之一。例如最简单的整数四则运算表达式，只允许使用加减乘除四则运算和括号（允许嵌套），所有运算数都是整数，但要注意其值不一定是整数。

对于人类来说，四则运算求值这个任务有可能计算过程会比较麻烦，但是对表达式的理解一定是很简单的，只要上过小学，四则运算和括号的使用规则就一定非常熟练，只要认真地去一步步计算即可。但是对于计算机来说，给定一个字符串形式的表达式，最大的挑战是要让软件看懂这个表达式，而计算却不是什么问题。

计算机要对表达式求值，首先要分析词法，即分解出运算符和运算数，对于运算数要将其从字符串形式转为整数。经过词法分析，一个字符串形式的表达式就会被拆解成一个记号（token）序列，这些记号有两种类型，一种是运算符，另一种是运算数。

完成词法分析之后，要对得到的记号序列进行语法分析，根据运算优先级（乘除优先级高于加减）和括号的位置确定计算顺序。语法分析结束之后即可按照分析结果逐步完成计算。

词法分析和语法分析还承担了判断表达式是否正确的任务，词法错误主要包括不正确的运算符、不符合规则的运算数等，语法错误主要包括运算符前后缺少运算数、括号不匹配等。在算法问题中往往题目会确保输入的表达式是正确的，这时候我们就可以忽略查错这个步骤。

所以计算机要完成一个表达式的求值，前后共要进行词法分析、语法分析和求值三个步骤。由于不同运算有不同优先级，通过加括号又可以调整计算顺序，所以数学表达式的计算过程可以非常灵活。但是计算机最不喜欢的就是灵活，计算机希望表达式能够没有括号、没有优先级、总是从左到右或者从右到左按固定的顺序运算。

为此人们发明了\ :strong:`前缀表达式`\ 和\ :strong:`后缀表达式`\ 两种新的表达式形式，同时把人类使用的通常的表达式称为\ :strong:`中缀表达式`\ 。

前缀、中缀和后缀表达式
^^^^^^^^^^^^^^^^^^^^^^

所谓的前缀、中缀、后缀表达式，是三种不同的表达式形式，是指运算符放在运算数的前面、中间还是后面而言的。比如通常的数学表达式 ``1 + 2``\ ，运算符加号是放在两个运算数中间的，所以叫做中缀表达式，如果写成前缀表达式就是 ``+ 1 2``\ ，写成后缀表达式就是 ``1 2 +``\ 。前缀表达式和后缀表达式是由波兰逻辑学家 Lukasewicz 发明的，因此前缀表达式也叫做\ :strong:`波兰表达式`\ ，后缀表达式叫做\ :strong:`逆波兰表达式`\ 。

前缀和后缀表达式是不允许也不需要使用括号的，所有运算也没有优先级之分。在把通常的中缀表达式转换为相应的前缀或后缀表达式时，就已经使所有运算按正确的顺序沿一个方向排列好了，前缀表达式从右向左，后缀表达式从左向右。于是这两种表达式形式特别适用于计算机求值。

**前缀表达式**

例如普通的表达式 ``1 - 2 * 3``\ ，写成前缀表达式时应该把运算符 ``-`` 和 ``*`` 都放在各自的运算数之前，按照优先级，乘法先算，所以先把 ``2 * 3`` 写成 ``* 2 3``\ ，而减法的两个运算数分别为 ``1`` 和 ``* 2 3``\ ，因此最终的前缀表达式为 ``- 1 * 2 3``\ 。

计算机求前缀表达式的值时，使用一个栈存放中间结果。计算过程从右向左扫描表达式，遇到运算数就将其压栈，遇到运算符就从栈中弹出两个数进行计算并把计算结果重新压入栈中。如此下去直到整个表达式扫描完毕，栈中留下的那个数就是表达式的值。例如示例中的这个表达式的运算过程如下：

.. code-block:: none

   表达式：+ 1 * 2 3

   初始栈：[]
   
   第1步：读到运算数3，压栈，栈变成 [3]

   第2步：读到运算数2，压栈，栈变成 [3, 2]

   第3步：读到运算符*，从栈中先后弹出2和3，计算2 * 3 = 6，压栈，栈变成 [6]

   第4步：读到运算数1，压栈，栈变成 [6, 1]

   第5步：读到运算符-，从栈中先后弹出1和6，计算1 - 6 = -5，压栈，栈变成 [-5]

   表达式扫描完毕，栈中应该只剩下一个元素，即计算结果-5

带括号的中缀表达式的处理方法也是一样的，无非最内层的括号有最高的运算优先级而已。例如 ``(3 + 4) * 5 - 6``\ ，优先级最高的运算是 ``(3 + 4)``\ ，先将其变成 ``+ 3 4``\ ，然后将乘法部分变成 ``* + 3 4 5``\ ，最后再将减法部分也变成前缀形式，得到最终的前缀表达式 ``- * + 3 4 5 6``\ 。

.. admonition:: 练习

   1. 仿照前面所示的步骤，手工进行前缀表达式 ``- * + 3 4 5 6`` 的运算，检查计算结果。
   2. 手工将下列中缀表达式转换为前缀表达式并求值，检查计算结果：

      ``1 - 2 - 3``

      ``12 + 13 * 14 - 15 / 16``

      ``1 + ((2 + 3) * 4) - 5``


**后缀表达式**

实际上在计算机软件中使用前缀表达式的情况并不多，几乎都使用后缀表达式。具体的原因和表达式优化有关，现在不需要深究，知道即可。正因为如此，在算法问题中基本也只会出现后缀表达式有关的问题，我们需要熟练地掌握后缀表达式的生成和运算方法，能熟练地编写相关的程序。

.. warning::

   后缀表达式的生成和计算是目前为止遇到的最大难点，也是一大重点。

首先仍然用 ``1 - 2 * 3`` 为例来看看怎样手动生成后缀表达式。和生成前缀表达式一样，还是按照运算顺序来逐个部分的变为后缀式。首先将 ``2 * 3`` 变成 ``2 3 *``\ ，随后处理减法部分，前后两个操作数分别为 ``1`` 和 ``2 3 *``\ ，所以写成 ``1 2 3 * -`` 的形式，这就是最终的后缀表达式。

后缀表达式的计算方法和前缀表达式也是几乎一样的，有两个区别：一是从左向右扫描，二是每一步运算先弹出的数为右运算数、后弹出的数为左运算数。以计算 ``1 2 3 * -`` 为例：

.. code-block:: none

   表达式：1 2 3 * -

   初始栈：[]

   第1步：读到运算数1，压栈，栈变成 [1]

   第2步：读到运算数2，压栈，栈变成 [1, 2]

   第3步：读到运算数3，压栈，栈变成 [1, 2, 3]

   第4步：读到运算符*，从栈中先后弹出3和2，计算2 * 3 = 6，压栈，栈变成 [1, 6]

   第5步：读到运算符-，从栈中先后弹出6和1，计算1 - 6 = -5，压栈，栈变成 [-5]

   表达式扫描完毕，栈中应该只剩下一个元素，即计算结果-5

再如中缀表达式 ``(3 + 4) * 5 - 6``\ ，按照运算顺序，先把 ``(3 + 4)`` 变成 ``3 4 +``\ ，接下来将乘法部分改成 ``3 4 + 5 *``\ ，最后处理减法部分，得到最终的后缀表达式 ``3 4 + 5 * 6 -``\ 。

.. admonition:: 练习

   1. 仿照前面所示的步骤，手工进行后缀表达式 ``3 4 + 5 * 6 -`` 的运算，检查计算结果。
   2. 手工将下列中缀表达式转换为后缀表达式并求值，检查计算结果：

      ``1 - 2 - 3``

      ``12 + 13 * 14 - 15 / 16``

      ``1 + ((2 + 3) * 4) - 5``


中缀表达式的分析算法
^^^^^^^^^^^^^^^^^^^^

读入中缀表达式字符串后，首先要进行词法分析，将其识别为记号序列。整数四则运算有两种记号：一种是\ :strong:`运算符`\ （operator），包括 ``+-*/()``\ ；另一种是\ :strong:`运算数`\ （operand），即所有整数，简单起见，我们限定操作数都在 ``int`` 的取值范围内。

所以我们先定义一个表示记号的结构，可以用来存放两种类型的记号：

.. literalinclude:: ../../codes/322_expr.cpp
   :language: c++
   :lines: 7-11

当 ``is_op == true`` 时，表示这个记号是一个运算符，此时 ``op`` 就存放这个具体的运算符，即 ``+-*/()`` 这六个字符中的任一个；当 ``is_op == false`` 时则表示这个记号是一个运算数，其值存放在 ``num`` 中。

表达式分析的第一步，词法分析要做的工作就是把一个字符串形式的中缀表达式中每一个不同的元素识别分解出来，变成一个从左向右存放的记号序列。现在我们还不需要考虑计算，只需单纯地分解和识别记号。假设读入的字符串只包含 ``+-*/()0123456789`` 这些字符和空白符（空格、换行、Tab），而空白符我们认为是可有可无的，一旦读到空白符直接舍弃即可。

词法分析本身并不难，但要注意 ``+-`` 这两个符号，它们有时候是加法和减法的运算符，需要单独分析成对应的运算符token，有时候是运算数的正负号，要和它后面的正整数组合起来形成正确的运算数token。例如表达式 ``-3-(-4*(-5))``\ ，这里面的第1、第3和第4个 ``-`` 是负号，而第2个 ``-`` 则是减法运算符。根据数学上对表达式格式的规定可以知道，整个表达式的第一个 ``+-`` 字符和跟在左括号 ``(`` 之后的 ``+-`` 字符是运算数的正负号（左括号之后的那个字符其实是括号内的子表达式的第一个字符），其他的是加减运算符。

这样就可以整理出词法分析的算法思路了，我们使用一个辅助变量 ``sgn`` 来表示下一个运算数的正负号，如果下一个运算数是正数就令其等于1，负数则等于-1。

1. 初始化状态：令 ``sgn`` 为1；
2. 从头到尾逐个字符扫描中缀表达式：

   * 如果是 ``+-`` 且是整个表达式的首字符或紧跟在 ``(`` 之后的字符，那么设置好相应的 ``sgn`` 值；否则记录一个运算符token并令 ``sgn`` 等于1；
   * 如果是 ``*/()`` 则记录一个运算符token并令 ``sgn`` 等于1；
   * 如果是数码字符，那么使用字符串转整数的atoi算法得到运算数的绝对值，乘以 ``sgn`` 后记录一个运算数token；
   * 如果是别的字符则直接舍弃。

这个算法看起来简单，但是实际编程还是很有挑战的。由于算法竞赛很少遇到需要自己做词法分析的题目，所以我们直接给出函数代码，但还是建议自己先动手尝试一下，然后对照看懂这里给出的代码。

.. literalinclude:: ../../codes/322_expr.cpp
   :language: c++
   :lines: 2, 21-26, 50-93

在实际应用中，词法分析结束后要进行语法分析。算法编程时如果题目确保输入的中缀表达式正确，那么就不需要了。不过语法分析中的括号匹配检查可以作为一个很好的编程练习。

.. admonition:: 练习

   设计一种简单的算法，利用一个栈来检查中缀表达式中的括号是否左右匹配。输入为一个中缀表达式字符串，如果其中左右括号是匹配的，就输出 ``"OK"``\ ，否则就输出 ``"Wrong"``\ 。编程实现并测试。

   提示：纯粹做括号匹配检查不需要先做词法分析，可以直接基于中缀表达式的字符串来进行检查。

   思考：能不能不使用栈，也不使用任何其他复杂的数据结构，仅使用基础数据类型来完成这一检查？如果能，请编程实现并测试。

   附加：现在进一步要求在检查到表达式中左右括号不匹配时，能模仿C++编译器那样给出错误信息，指出错误发生的位置，例如输出像以下这样的错误信息：

   .. code-block:: none
   
      Wrong:
      2*(3+4))
             ^

   或者

   .. code-block:: none

      Wrong:
      2*((3+4)
        ^

后缀表达式的生成算法
^^^^^^^^^^^^^^^^^^^^

根据中缀式生成后缀式是一个经典算法问题，它有一个看上去不难，要理解和记住却挺难，要在考场上一次性快速写对非常难的经典算法。这个后缀式生成算法使用两个token栈，一个是运算符栈 ``s1``\ ，另一个是中间结果栈 ``s2``\ 。算法结束时，\ ``s2`` 中存放的就是对应的后缀表达式。算法的具体过程如下：

1. 初始化两个栈：运算符栈 ``s1`` 和中间结果栈 ``s2``\ 。
2. 从左到右的扫描中缀表达式的每一个记号 ``token``\ ，按下述逻辑完成处理：

   1. 若 ``token`` 是运算数，压入 ``s2``\ ；
   2. 若 ``token`` 是加减乘除四种运算符：

      * 如果 ``s1`` 为空或 ``s1`` 栈顶元素为左括号或 ``token`` 的优先级高于 ``s1`` 栈顶元素，则直接将 ``token`` 压入 ``s1``\ ；
      * 否则将 ``s1`` 栈顶元素弹出并压入 ``s2`` 然后继续与下一个栈顶元素比较直至满足上述压栈条件后将 ``token`` 压入 ``s1``\ 。

   3. 若 ``token`` 是左括号则直接压入 ``s1``\ ；
   4. 若 ``token`` 是右括号则依次弹出 ``s1`` 的栈顶元素并压入 ``s2`` 直到遇到第一个左括号，最后把这个左括号弹出 ``s1`` 并抛弃。

3. 重复上述步骤直到中缀表达式的所有记号处理完毕。
4. 将 ``s1`` 中剩余的所有元素依次弹出并压入 ``s2``\ 。
5. ``s2`` 中的元素按照 :emphasis:`从栈底到栈顶` 的顺序构成所要求的后缀表达式。

.. note::

   根据前面关于三种表达式形式的描述我们不难发现，三种形式的运算数顺序是一样的，所以算法的关键是遇到运算符时如何摆放。

   当遇到加减乘除四种真正的运算符时，有两种情况直接压入 ``s1``\ ：

   1. 如果 ``s1`` 为空或者栈顶元素为左括号 ``(``\ ，这种情况表示当前这个运算符是整个式子或其中某一个由一对括号括起来的子式子的第一个运算，这种情况直接将运算符压栈即可；
   2. 如果当前这个运算符的优先级高于栈顶元素的优先级，说明当前这个运算符将会先运算，而根据弹栈压栈规则，在 ``s1`` 越靠后的运算符在进入 ``s2`` 中去的时候越靠前，所以这时候应该暂时先将其压入到 ``s1`` 中，这样它在 ``s1`` 中的位置就靠在后面。

   此外还剩一种情况就是当前运算符的优先级不高于 ``s1`` 的栈顶元素，那么现在这个栈顶元素的运算应该在前，所以先将其弹出压入到 ``s2`` 去，不断重复这个操作直到满足当前运算符的压栈条件。

   最后就是遇到括号的处理了，其实无非是遇到右括号之后就把它对应的那一对括号中的子式子全部变成结果，放到 ``s2`` 中去而已。

接下来就是实际编程时的技巧了。假设我们要处理的中缀表达式最多可以有100个记号，这些记号已经用前面所述的 ``parse()`` 函数完成了分析，形成了一个长度为 ``len`` 的记号数组 ``tokens``\ ，现在我们要编写一个函数 ``postfix()`` 来对这个中缀表达式记号数组进行处理，变成后缀表达式记号数组。

这个函数中要用到两个元素类型为 ``Token`` 的栈，当然可以用STL容器 ``stack`` 来实现，但是事实上这并不是最佳方法，最佳的方法甚至不是自己实现一个栈，而是根本就用单纯的数组来模拟所需要的栈。请看下面的代码：

.. literalinclude:: ../../codes/322_expr.cpp
   :language: c++
   :lines: 3-6, 13-21, 28-34, 95-127

我们在这里简单地用两个数组 ``s1, s2`` 和两个栈长度变量 ``len1, len2`` 来模拟了栈，这种简单处理带来了许多编程上的方便。

如果将表示栈中元素数量的栈长度变量用做数组下标，那么它总是指向栈顶元素的后一个元素，所以 ``s2[len2++] = ...`` 这样的简单赋值语句即可实现压栈，也可以用 ``... = s1[--len1]`` 这样的方式实现弹栈并返回栈顶元素。二者结合起来就可以做到用一条赋值语句来实现从 ``s1`` 中弹出并压入 ``s2`` 中的操作：\ ``s2[len2++] = s1[--len1]``\ 。如果是单纯地弹栈那就更简单了，我们根本不需要真的去删除栈顶元素，只要把栈长度变量减一即可：\ ``--len1`` 就相当于弹掉了 ``s1`` 的栈顶元素。

另外，由于最终的结果是按从栈底到栈顶的顺序存放在栈 ``s2`` 中的，所以如果我们用了一个规范的栈，例如 ``stack`` 容器，那么反而会让结果的获取变得麻烦。因为我们只能通过弹栈来逐个获取记号，所以得到的记号序列和真正后缀表达式的记号序列是反向的。这里我们用普通的数组来模拟栈，事情就变得简单了，我们直接用 ``memcpy()`` 函数把这个假装自己是个栈的数组中的元素复制一份到原记号数组中去就可以了。

.. hint::

   当程序需要使用栈，而且栈的最大长度可以预期的情况下，经常使用这种数组加长度（也就是栈顶后下标）的方式来模拟栈。这种方式往往编程更简单、功能更灵活。

.. admonition:: 练习

   1. 根据上述算法，手动将下列中缀表达式转为后缀表达式：

      ``1 - 2 - 3``

      ``12 + 13 * 14 - 15 / 16``

      ``1 + ((2 + 3) * 4) - 5``

   2. 理解上述算法和程序，在此基础上总结根据中缀表达式生成前缀表达式的算法并编程实现。

后缀表达式的计算算法
^^^^^^^^^^^^^^^^^^^^

后缀表达式的计算算法就非常简单了，和前面所述的手工计算方法完全一致。

我们需要使用一个栈来存放计算的中间结果，请想一想这个栈的元素数据类型是什么？然后程序就从左到右地读取后缀表达式中每一个token，如果读到的是运算数就压入栈中，如果是运算符就从栈中连续弹出两个运算数然后进行计算，计算的结果压回栈中即可。这里要特别注意减法和除法是不满足交换律的，两个运算数有先后顺序。

事实上如果我们还是用数组加长度的方式来模拟栈，那么每一次运算都会变得非常简单。设中间结果栈的数组名为 ``v``\ ，长度变量为 ``len``\ ，那么当遇到运算的时候，假设是要做一次减法运算，只需要这样就可以了：

.. code-block:: c++

   v[len-2] -= v[len-1];
   --len;

如果表达式是格式正确的，那么最终的运算结果，即表达式的值，在每一个token都处理完之后就是最终留在栈里的栈顶元素，而且此时栈里有且只有这一个元素。

如果每一个token都处理完了之后，栈里的元素数量不是一个，或者在运算过程中出现了弹空栈的情况，那么表达式一定是格式不正确。

.. admonition:: 思考

   虽然算法问题一般不需要考虑表达式格式不正确的情况，但是我们还是有必要知道什么情况下运算结束后栈中元素数量大于一，什么情况下运算过程中会出现弹空栈，分别对应中缀表达式的哪些格式错误，请认真思考这个问题。

.. admonition:: 练习

   编写计算中缀表达式的函数，输入参数为一个中缀表达式token序列，数组加长度的形式，输出表达式的值，函数原型如下：

   .. code-block:: c++

      double eval(Token tokens[], int len);

