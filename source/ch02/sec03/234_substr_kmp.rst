子串搜索及KMP算法
++++++++++++++++++++++++++++

:strong:`子串搜索`\ ，也叫\ :strong:`子串匹配`\ ，是字符串处理领域非常重要和常用的一种操作。一般的子串搜索操作是指，给定两个字符串 :math:`S` 和 :math:`P`\ ，检查 :math:`P` 是不是 :math:`S` 的一个子串，如果是则返回 :math:`P` 的首字符在 :math:`S` 中出现位置，出现多次的话就返回第一次的位置；如果不是一般就返回-1。

例如：字符串 ``"abc"`` 就是 ``"1234abcd"`` 的一个子串，它第一次出现的位置是4，但它不是字符串 ``"1234ABCD"`` 的子串，因为ASCII字符是区分大小写的。

通常我们把字符串 :math:`S` 称为\ :strong:`文本串`\ ，把 :math:`P` 称为\ :strong:`模式串`\ 。最基本的子串搜索，模式串就是要搜索的子串，所做的是一字不差的精确匹配。高级的子串搜索，模式串中可能含有通配符，比如用 ``*`` 表示0个或任意多个任意字符，用 ``?`` 表示0个或1个任意字符。最灵活也最难实现的是\ :strong:`正则表达式`\ 匹配，此时模式串是一个正则表达式，它有自己的词法规则，可以非常灵活地表示各种各样的字符串样式，例如正则式 ``^-?[1-9]\d*$`` 表示任意的整数样式的字符串，而 ``^-?([1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0)$`` 能匹配小数样式的表达式。后两种高级的搜索也是我们常会把子串搜索称作子串匹配的原因，因为它们的功能已经超越了简单的搜索。

这一节我们讨论最基本的子串搜索算法，在文本串中一字不差地精确搜索模式串。

朴素的蛮力搜索算法
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

蛮力算法就是从文本串的头一个字符开始，作为起始位置与模式串进行比对，如果发现一致的子串，就返回起始位置，如果不一致就将起始位置移到文本串的下一个字符继续比对，直到找到子串或者找不到。

蛮力搜索的第一个起始位置是文本串的首字符 ``S[0]``\ 。假设文本串长度为 ``n``\ ，模式串长度为 ``M``\ ，那么蛮力搜索的最后一个起始位置就应该是 ``n-M``\ ，因为从这个位置到文本串的末尾还剩刚好 ``n-(n-M)=M`` 个字符，再往后移剩余字符数量就不如模式串多了，不可能再存在和模式串相同的子串。

利用 ``strncmp()`` 函数可以很简单地编写出这样一个函数：

.. code-block:: c++

   #include <cstdio>
   #include <cstring>
   
   int substr_search_bf(const char *s, const char *p);
   
   int main()
   {
           char s[81], p[11];
           scanf("%80s %10s", s, p);
           printf("%d\n", substr_search_bf(s, p));
   
           return 0;
   }
   
   int substr_search_bf(const char *s, const char *p)
   {
           int pos, n_s = strlen(s), n_p = strlen(p);
           for (pos = 0; pos <= n_s - n_p; ++pos)
                   if (strncmp(s+pos, p, n_p) == 0) break;
           return pos > n_s - n_p ? -1 : pos;
   }

这个蛮力算法非常简单易懂，但是它的时间复杂度是 :math:`O(nM)`\ ，属于比较高的二阶的时间复杂度。

精确子串搜索有一个非常经典的算法，由算法界的三位大神D.E.Knuth、J.H.Morris和V.R.Pratt同时发明的。这个算法是每一本算法教科书都必讲、每一个学习算法的人都必学的超经典算法，就以三位发明者的姓氏首字母命名为KMP算法。它是迄今为止精确子串搜索最经典的算法之一，也是算法史上最伟大的发明之一，它的时间复杂度是 :math:`O(n+M)`\ 。下面我们来讲解一下这个KMP算法。

.. index:: KMP算法

KMP算法
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

KMP算法是对蛮力算法的改进，所以要理解KMP算法必须先了解蛮力算法不好的地方在哪里。

假设文本串 :math:`S` 为 ``"ABCAABCB"``\ ，模式串 :math:`P` 为 ``"ABCB"``\ 。下面我们先看看蛮力搜索的过程：

.. code-block:: none

   第1步：比对位置 pos = 0
   S: ABCAABCB
   P: ABCB
   第1步比对结果：失败，pos后移一位。

   第2步：比对位置 pos = 1
   S: ABCAABCB
   P:  ABCB
   第2步比对结果：失败，pos后移一位。

   第3步：比对位置 pos = 2
   S: ABCAABCB
   P:   ABCB
   第3步比对结果：失败，pos后移一位。

   第4步：比对位置 pos = 3
   S: ABCAABCB
   P:    ABCB
   第4步比对结果：失败，pos后移一位。

   第5步：比对位置 pos = 4
   S: ABCAABCB
   P:     ABCB
   第5步比对结果：成功，返回子串首位置4。

从这个过程可以看出，其实第1步比对失败后，比对位置 ``pos`` 并不需要傻傻地一个一个往后挪，至少可以直接跳到第4步那个位置 ``pos = 3``\ ，因为第1次发生比对不符合的字符就是 ``S[3] = 'A'``\ 。

KMP算法的改进思路就是：:emphasis:`当一次比对失败时，利用已经匹配的那部分信息，将模式串尽可能多地移动到一个合适的位置，使得下一次比对可以从上一次匹配失败的那个位置开始继续进行`\ 。

例如在上面这个例子里，第1步比对中匹配正确的字符有 ``S[0],S[1],S[2]``\ ，直到 ``S[3]`` 发生错误。使用蛮力法，第2步又回过头去从 ``S[1]`` 开始比对，这就是蛮力算法时间复杂度为 :math:`O(nM)` 的原因。如果我们能让模式串在第1步比对失败后移动到一个合适的位置，使得第2步可以从 ``S[3]`` 直接继续，那么整个比对过程最多进行 ``n`` 次比对，因为在文本串上我们不走回头路。这就是KMP算法的基本思路。

有了思路，我们还要解决一个具体问题：所谓“合适的位置”到底在哪里？是不是简单地把模式串移动到上一次匹配失败的字符位置开始就可以了？当然不是，例如看下面这个例子：

文本串 :math:`S`\ ：\ ``"ABCABCABE"``\ ，模式串 :math:`P`\ ：\ ``"ABCABE"``\ ，用索引 ``i,j`` 分别表示在文本串和模式串上的比对位置。

.. code-block:: none

   第1次比对，从 i = j = 0 开始
      i: 0  1  2  3  4 [5] 6  7  8
      S: A  B  C  A  B  C  A  B  E
      P: A  B  C  A  B  E
      j: 0  1  2  3  4 [5]
   比对结果：在 i = 5 处匹配失败。

这时候，如果简单地把模式串移动到和 ``S[5]`` 对齐的位置，会发现文本串中剩余字符数量不够了，就会得出搜索失败的结论。然而这是错误的！

仔细观察模式串，可以发现上一次匹配成功的前5个字符 ``"ABCAB"`` 有相同的前缀和后缀 ``"AB"``\ 。所以我们应该把开头的那一段前缀 ``"AB"`` 移动到后面这一段后缀 ``"AB"`` 所在的位置，然后就可以从上一次匹配失败的位置 ``S[5]`` 开始继续比对了：

.. code-block:: none

   第2次比对，P移动到和 S[3] 对齐的位置，
   仍从上一次不匹配字符的位置 i = 5 处开始比对，对应的模式串位置为 j = 2
      i: 0  1  2  3  4 [5] 6  7  8
      S: A  B  C  A  B  C  A  B  E
      P:          A  B  C  A  B  E
      j:          0  1 [2] 3  4  5
   比对结果：匹配成功，返回子串首位置3。

现在我们可以找到一点头绪了。当某一次比对在某个字符处发生了不匹配，那么模式串要移动到的“合适位置”与已经匹配成功的那一部分里面有没有相同的前后缀有关。

设上一次比对时，第一对不匹配字符为 ``S[i] != P[j]``\ 。如果在已经匹配成功的部分模式串里面最长的相同前后缀长度为 ``next``\ ，那么下一次就应该把模式串首字符移动到对准文本串字符 ``S[i-next]`` 的位置，因为从这个位置到发生不匹配的字符 ``S[i]`` 之前恰有 ``next`` 个字符。模式串这样移过来之后刚好长度为 ``next`` 的前缀部分位于这一段区域里，最长的相同前后缀恰好充分利用起来。下一步就从字符 ``S[i]`` 开始继续比对，与之比对的模式串字符为 ``P[next]``\ ，这可以通过赋值 ``j = next`` 来完成。

.. hint::

   这里我们要明白一件事情，所谓将模式串移动到文本串位置 ``i-next``\ ，实际上就相当于将文本串位置 ``i`` 对准模式串位置 ``next``\ 。二者其实是完全一样的，只是视角不同，前者是看作模式串向后移动，后者是看作文本串向前移动。通过赋值 ``j = next`` 就完成了所谓的“移动模式串到合适的位置”。

   这个赋值的意义可以通俗地表示为：这一次文本串位置 ``i`` 上的字符和模式串位置 ``j`` 上的字符匹配失败了，:strong:`下一次`\ 请将其和模式串位置 ``next`` 上的字符进行匹配。这就是为什么KMP算法把“最长相同前后缀长度”的数组有点奇怪地取名为next数组的原因。


如果在上一次比对已经匹配成功的部分里没有相同前后缀，即相同前后缀的最大长度为0，那么下一次比对时整个已经匹配成功的部分都是无效的，模式串的开头将移动到当前比对失败位置。例如在 ``"ABCDEFG"`` 中搜索 ``"ABCA"``\ ：

.. code-block:: none

   第1次比对，从 i = j = 0 开始，到 i = 3 时匹配失败
      i: 0  1  2 [3] 4  5  6
      S: A  B  C  D  E  F  G
      P: A  B  C  A
      j: 0  1  2 [3]
   已经匹配的部分 "ABC" 中没有相同的前后缀，l = 0，所以 j = l = 0，相当于将模式串直接移动到 i 的位置

   第2次比对，i = 3， j = 0
      i: 0  1  2 [3] 4  5  6
      S: A  B  C  D  E  F  G
      P:          A  B  C  A
      j:         [0] 1  2  3
   第一个字符就匹配失败，已经匹配部分为空，整个模式串应该向后移动一个字符继续比对，但超长了，搜索失败


如果上一次比对时匹配部分长度为0，即第一个字符就不匹配，那么下一次比对时就只能后移一个字符，\ ``i = i + 1, j = 0``\ ，然后继续开始比对。

下面我们来理一理思路，把算法的框架搭出来。设模式串中每一个字符 ``P[j]`` 之前的部分，即子串 ``P[0:j]`` 中最长的相同前后缀长度为 ``next[j]``\ 。对于模式串的第2个字符 ``P[1]``\ ，它前面只有一个首字符，不存在前后缀，所以 ``next[1] = 0`` 是固定的。对于模式串的首字符 ``P[0]``\ ，我们规定 ``next[0] = -1``\ ，这是为了方便在算法中实现“如果第一个字符就不匹配”情况发生时的处理。下面是算法的伪代码：

.. admonition:: KMP算法

   :math:`\text{KMP_Search}(S,P):`

      :math:`i\leftarrow0,j\leftarrow0`

      :math:`\text{WHILE  }j\lt \text{Len}(P) \text{  AND  } \text{Len}(S)-i \ge \text{Len}(P)-j \text{  DO}`

         :math:`\text{IF  }j=-1\text{  OR  }S[i]=P[j] \text{   THEN}`

            :math:`i\leftarrow i+1,j\leftarrow j+1`

         :math:`\text{ELSE}`

            :math:`j\leftarrow next[j]`

      :math:`\text{IF  }j=\text{Len}(P)`

         :math:`\text{THEN RETURN  }i-j`

         :math:`\text{ELSE RETURN  }-1`


大多数教科书和网上关于KMP算法的讲解都把循环条件设置为比较简单的 :math:`j\lt \text{Len}(P) \text{  AND  } i \lt \text{Len}(S)`\ 。这当然是对的，而且比较好懂。但是如果当模式串事实上已经移出了文本串的范围时，或者模式串比文本串还要长时，循环仍然会继续比对下去，这其实是有点浪费的。我们算法里的循环条件虽然复杂一点，但是当模式串超出文本串尾部的时候，循环不会执行下去，此时一定满足 :math:`j\neq\text{Len}(P)`\ ，所以会返回-1表示搜索失败。

算法中最难理解的部分是循环内部的那条判断语句，这条语句一共判断了三种情况，一一分析如下：

1、:math:`j=-1` 的情况

什么时候 :math:`j` 才会等于-1呢？正常情况下，字符位置 :math:`j` 不会变成负数，唯一出现负数的地方就是 :math:`next[0]` 的值总是-1。所以发生这种情况唯一的可能就是上一次比对时模式串首字符就不匹配，此时 :math:`j=0` 而且 :math:`S[i]\neq P[j]`\ ，因此在上一轮循环中判断语句进入了 :math:`\text{ELSE}` 分支，执行了赋值语句 :math:`j\leftarrow next[j]` 使得它变成了-1。

那么在这种情况下，这一轮应该怎么处理呢？当然是模式串向后移动一个位置（或者视作文本串向前移动一个位置），然后仍然从模式串的首字符 :math:`P[0]` 开始继续比对，比对的文本串字符为 :math:`S[i+1]`\ 。条件分支里的语句 :math:`i\leftarrow i+1, j\leftarrow j+1` 恰好能完成这项工作。

2、:math:`S[i]=P[j]` 的情况

这种情况很好理解，就是本次比对的两个字符相同，比对成功。那么下一步当然应该是继续比对下一对字符了，也就是条件分支里的语句所做的工作。

3、:math:`\text{ELSE}` 分支表示的其余情况

剩下的其余情况无非就是本轮比对失败的情况了，这时就进入 :math:`\text{ELSE}` 分支，把模式串位置改成下一个“合适的位置”就可以进入下一轮循环了。


**next数组**

好了，现在看起来万事俱备只欠东风了。东风就是这个next数组，要怎样才能得到这个next数组呢？如果蛮力去计算的话整个算法就都没意义了，因为时间复杂度会达到 :math:`O(m^2)`\ 。我们有更好的方法，时间复杂度 :math:`O(m)`\ 。

再重复一遍（因为这很重要），next数组和模式串长度相等，第 :math:`j` 个元素 :math:`next[j]` 表示前 :math:`j` 个字符构成的子串 :math:`P[0:j]` 的最长相同前后缀长度。我们已经知道，对于任何一个模式串，\ :math:`next[0]=-1,next[1]=0`\ 。一看到这种“有初值”的数值序列，一定要第一时间想到“递推”这种重要的数学方法，快速计算next数组就是要用递推的方法。

递推，就是要解决这样的问题：如果已经知道从 :math:`next[0]` 到 :math:`next[j]` 的所有值，怎么求出下一个 :math:`next[j+1]` 的值？

令 :math:`k=next[j]`\ ，表示在子串 :math:`P[0:j]` 中，长度为 :math:`k` 的前缀 :math:`P[0:k]` 和后缀 :math:`P[j-k:j]` 相同，而且这是最长的情况。现在考虑下一个子串 :math:`P[0:j+1]`\ ，它只是在原来那个子串的尾部添加了一个字符 :math:`P[j]`\ ，可想而知 :math:`next[j+1]` 最多比 :math:`next[j]` 大1。下面我们就来讨论这些情况的产生条件以及怎样快速而正确地求 :math:`next[j+1]`\ 。

可以分三种情况来讨论：

情况1：\ :math:`P[k] = P[j]`\ ，这时候 :math:`next[j+1] = next[j] + 1 = k + 1`\ ，这是一种皆大欢喜的情况。为什么会这样？请看下面的图解：

.. image:: ../../images/234_kmp.001.png

图中的两段红色区域是子串 :math:`P[0:j]` 的最大相同前后缀，现在两个蓝色小块也相同。所以在子串 :math:`P[0:j+1]` 中，前后两块红加蓝区域一定也相同，而且是最长的。因此这种情况下就有 :math:`next[j+1] = next[j] + 1 = k + 1`\ 。可以看出这个结论在 :math:`k = 0` 时仍然是正确的。

情况2：\ :math:`P[k] \neq P[j],k = 0`\ ，这时候 :math:`next[j+1] = 0`\ ，请看下面的图解：

.. image:: ../../images/234_kmp.002_1.png

图中的蓝色和黄色两个小块不相同，显然这样的情况下 :math:`next[j+1]` 不可能为1。那么它有可能大于1吗？不妨先假设可以，设存在 :math:`next[j+1] \gt 1`\ ，则子串 :math:`P[0:j+1]` 中有一段长度大于1的相同前后缀。鉴于 :math:`P[0]` 既不同于 :math:`P[j]` 又不同于 :math:`P[j-1]`\ ，所以只能是下图所示这种情况，图中前后两块蓝加黄区域就是相同前后缀：

.. image:: ../../images/234_kmp.002_2.png

但如果真是这样的话，既然蓝加黄的长度要大于1，那不是说明在子串 :math:`P[0:j]` 内有长度大于0的相同前后缀了吗？显然这和前提条件 :math:`k = 0` 矛盾了，故存在 :math:`next[j+1] > 1` 这个假设不成立！这种情况下 :math:`next[j+1]` 只能等于0。


情况3：\ :math:`P[k] \neq P[j],k \gt 0`\ ，这时候需要让 :math:`k\leftarrow next[k]` 然后用这个新的 :math:`k` 值去递归地计算 :math:`next[j+1]`\ 。这是比较难理解的部分，请仔细看下面的图解：

.. image:: ../../images/234_kmp.003_1.png

这种情况下显然 :math:`next[j+1]` 有可能为0，那么它有可能大于0吗？有！

因为 :math:`k \gt 0`\ ，所以我们可以考虑子串 :math:`P[0:k]` 中的相同前后缀情况。设 :math:`L = next[k] > 0`\ ，即在子串 :math:`P[0:k]` 中有长度为 :math:`L` 的最大相同前后缀，那么问题就要归约为 :math:`P[L]` 是不是等于 :math:`P[j]` 了。如下图所示：

.. image:: ../../images/234_kmp.003_2.png

可见，只要遇到情况3，就可以这样把问题归约为 :math:`P[j]` 和 :math:`P[next[k]]` 之间的子问题，以相同的方法继续判断。这样不断归约下去，子问题的规模会越来越小，总有一次会遇到情况1或者情况2，从而结束这个递归的归约过程。所以遇到这种情况时我们只需要让 :math:`k\leftarrow next[k]` 然后继续下去就可以了。

理解了上面三种情况之后，就可以根据它们来归纳出从初值开始推算整个next数组的算法了。但如果直接依据三种情况来写程序，代码会比较复杂。越是复杂的代码越容易有bug，所以实际编程时还要再改进一下。复杂在什么地方呢？复杂在算法的两个递归终止条件，情况1和情况2，二者相差比较大，判断条件和终止方式都不相同，我们应该设法让它们统一起来。

这里我们还是利用 :math:`next[0] == -1`\ 。遇到情况2的时候不要直接去终止递归，而是视作为情况3，让 :math:`k \leftarrow next[0] = -1` 并继续递归下去。本来我们是要在这一层让 :math:`next[j+1]` 变成0并终止递归的，现在变成了让 :math:`k` 变成-1并进入下一层，不过-1加1不就是0吗？所以只要给情况1加一个条件：当 :math:`k = -1` 时也和正常的情况1一样处理，令 :math:`next[j+1] \leftarrow k + 1` 并终止递归。这样就能把我们故意“漏”下来的情况2视作情况1一样处理掉了。是不是感觉和KMP算法主框架的技巧非常相似？下面就是这种朴素的next算法：

.. admonition:: 朴素next算法

   :math:`\text{Naive_Next}(next, P):`

      :math:`next[0]\leftarrow-1`

      :math:`k\leftarrow-1`

      :math:`j\leftarrow0`

      :math:`\text{WHILE  }j\lt \text{Len}(P) \text{  DO}`

         :math:`\text{IF  }k=-1\text{  OR  }P[j]=P[k] \text{  THEN}`

            :math:`k\leftarrow k+1`

            :math:`j\leftarrow j+1`

            :math:`next[j]\leftarrow k`

         :math:`\text{ELSE}`

            :math:`k\leftarrow next[k]`

.. admonition:: 练习

   请自己用纸笔按照上面这个算法计算一下模式串 ``"ABAAXABABY"`` 对应的next数组。

   正确的答案应该是：``[ -1 , 0 , 0 , 1 , 1 , 0 , 1 , 2 , 3 , 2 ]``\ 。

但是这样就结束了吗？上面这个算法既然被叫做“朴素”的算法，说明肯定还有点什么可以进一步改进的地方。

请看这样一个模式串：\ ``"ABAB"``\ ，经过计算，它的next数组为 ``[-1,0,0,1]``\ 。下面我们来看它在文本串 ``"ABACABAD"`` 中的搜索过程：

.. code-block:: none

   第1次比对，从 i = j = 0 开始，到 i = 3 时匹配失败
      i: 0  1  2 [3] 4  5  6  7
      S: A  B  A  C  A  B  A  D
      P: A  B  A  B
      j: 0  1  2 [3]
   next:-1  0  0 [1]
   在S[3]='C', P[3]='B'处匹配失败，根据next[3]=1的指示，下一次应该从P[1]开始继续匹配

   第2次比对，i = 3， j = 1
      i: 0  1  2 [3] 4  5  6  7
      S: A  B  A  C  A  B  A  D
      P:       A  B  A  B
      j:       0 [1] 2  3
   next:      -1 [0] 0  1
   S[3]='C'和P[1]='B'的匹配再次失败

到这里我们就看出了问题，当第一次匹配失败时，按照 ``next[3]`` 的指示，改为从 ``P[next[3]] == P[1]`` 继续匹配，但 ``P[1]`` 是等于 ``P[3]`` 的，都是字符 ``'B'``\ ，所以下一次匹配注定仍将失败。换句话说，这次移动实质上是无效的！这个问题会在一定程度上影响搜索效率，应该设法改进，也就是不能出现 ``P[j] == P[next[j]]`` 的现象。

从next数组本身的意义来看，这个问题很好理解。next数组实质上是一个移动模式串的“导航表”，每一个元素 ``next[j]`` 都是一条导航指令，表示如果与模式串中的字符 ``P[j]`` 匹配失败，那么下一步请将 ``P[next[j]]`` 移动过来尝试匹配。这个过程是会一路连续下去的，如果下一步和 ``P[next[j]]`` 匹配仍然失败，那么再下一步请尝试和 ``P[next[next[j]]]`` 进行匹配，如此一直进行下去。

所以，如果我们事先就能确定一定以及肯定地知道 ``P[next[j]] == P[j]``\ ，那么这个 ``next[j]`` 就会把比对过程导航到一个坑里去。下一步必定仍然失败，然后必定会进一步被导航去 ``P[next[next[j]]``\ 。既然如此，我们为什么还要跳这个坑呢？我们何不在计算next数组的时候就查出这些坑来并且直接跨过去？

对！我们只要在每次计算 ``next[j]`` 之后检查是否 ``P[next[j]] == P[j]``\ ，如果是就直接将 ``next[j]`` 设置成 ``next[next[j]]``\ ，这样就可以在设计“导航表”的时候直接把这些坑都越过了。

用这种方法再计算一下 ``"ABAB"`` 的next数组，\ ``next[0]`` 和 ``next[1]`` 的值不会变，仍然为-1和0。当计算得到 ``next[2]`` 等于0的时候，我们发现 ``P[2] == P[0] == 'A'``\ ，所以应该把 ``next[2]`` 设置成 ``next[0]``\ ，即-1。然后计算 ``next[3]``\ ，按照计算规则，由于上一个 ``next[2]`` 等于-1，所以 ``next[3]`` 应该直接设置为 ``next[2] + 1``\ ，即0。这样得到的next数组为 ``[-1, 0, -1, 0]``\ 。然后再来看看它在 ``"ABACABAD"`` 中的搜索过程：

.. code-block:: none

   第1次比对，从 i = j = 0 开始，到 i = 3 时匹配失败
      i: 0  1  2 [3] 4  5  6  7
      S: A  B  A  C  A  B  A  D
      P: A  B  A  B
      j: 0  1  2 [3]
   next:-1  0 -1 [0]
   在S[3]='C', P[3]='B'处匹配失败，根据next[3]=0的指示，下一次应该从P[0]开始继续匹配

   第2次比对，i = 3， j = 0
      i: 0  1  2 [3] 4  5  6  7
      S: A  B  A  C  A  B  A  D
      P:          A  B  A  B
      j:         [0] 1  2  3
   next:        [-1] 0 -1  0
   S[3]='C'和P[0]='A'的匹配再次失败

   后续步骤省略...

可以看到，现在不会再跳那个坑了！下面是一个使用KMP算法进行子串搜索的示例程序，采用的是改进过的next数组算法。这个示例程序假定文本串和模式串的最大长度分别为1000和100个字符，允许包含空格。程序分两行按行输入文本串和模式串，然后输出搜索结果，即第2行的模式串在第1行的文本串中首次出现的首字符位置，如果搜索不到则输出-1。

.. literalinclude:: ../../codes/234_kmp.cpp
   :language: c++

.. important::

   这里似乎还有一个问题，我们在改进的next算法中只检查了下一步会不会是坑，即是不是 ``P[j] == P[next[j]]``\ ，并没有进一步去判断越过第一个坑后会不会掉进第二个坑。也就是说，我们只让 ``next[j] = next[next[j]]``\ ，但会不会 ``P[next[next[j]]]`` 也是等于 ``P[j]`` 的呢？
   
   当然是有可能的，比如 ``"ABABAB"`` 或类似这样子的模式串都会有“连续坑”。用朴素的next算法，会得到next数组 ``[-1,0,0,1,2,3]``\ 。如果在 ``P[5]`` 处匹配失败，下一步会跳到 ``P[next[5]]`` 即 ``P[3]``\ ，这个字符还是 ``'B'`` 所以匹配肯定失败。再下一步会找到 ``P[next[3]]`` 即 ``P[1]``\ ，仍然是坑 ``'B'``\ ！
   
   所以我们上面的算法对吗？我们不是只判断了一步吗？难道不是应该递归地判断下去直到没有坑为止吗？然而算法是正确的，连续坑确实会被全部填平！这是为什么？请务必想明白这个问题！



.. attention::

   这个KMP算法应该是到目前为止我们接触到的最为玄学的一个经典算法了，不光算法思路理解有点麻烦，而且代码也有点难读。但是千万记住，KMP是字符串处理的必学算法，哪怕你记不住算法，哪怕你离开课本就写不出这个算法的正确代码，但是必须读懂它，必须用纸笔模拟运行它，必须看懂每一行代码的用意！这个算法非常重要，彻底搞懂KMP算法，尝试着不看教材自己正确地写出来，能做到了，那么大多数的字符串处理问题对你来说都不是问题了。



小结
^^^^^^^^

KMP算法的时间复杂度是 :math:`O(n+M)`\ 。其中 :math:`n` 是文本串的长度，算法的子串搜索部分由于实现了文本串字符位置不走回头路，所以搜索需要花费的时间为 :math:`O(n)`\ 。:math:`M` 是模式串的长度，搜索之前要耗费 :math:`O(M)` 的时间来计算出整个next数组，这部分的时间复杂度分析相当复杂，就不详细讲解了。总之KMP算法的时间复杂度为 :math:`O(n+M)`\ ，这比起蛮力搜索的 :math:`O(nM)` 是数量级的改进。

KMP算法虽然是子串搜索的经典算法，但它现在已经不是最快最好的了。比如1977年发明的Boyer-Moore算法，简称BM算法，从模式串的尾部开始向前匹配，最坏情况下达到 :math:`O(n)` 的时间复杂度。在实践中，它比KMP算法的效率略高。1990年发明的Sunday算法，和BM算法一样从后向前进行匹配，它的实现比KMP算法和BM算法都简单，而且在实践中比BM算法的速度更快。

.. admonition:: 附加题

   搜索相关资料，学习Sunday算法，并自己编程练习。其实这个算法比KMP可简单得太多了，平均速度据说比KMP快3到5倍，真是一个优秀的算法。

   参考资料：\ `Sunday算法 by 刘毅 <https://www.subetter.com/algorithm/sunday-algorithm.html>`_\ ，\ `字符串匹配——Sunday算法 <https://blog.csdn.net/q547550831/article/details/51860017>`_\ 。


在实际的算法问题编程时，如果需要进行子串搜索，我们完全不推荐手写KMP算法来自己实现，就算你会Sunday算法，我们也完全不推荐自己手写Sunday算法来实现。这种情况下应该遵循“不重复造轮子”的原则，使用C++库函数来进行子串搜索。如果使用传统的C-string来处理字符串，那么请使用 ``cstring`` 库的 ``strstr(), strcasestr(), strnstr()`` 这三个函数。比较复杂一些的字符串处理问题，更建议使用C++ string，它有两个很好用速度也很快的成员函数 ``string::find()`` 和 ``string::rfind()``\ ，前者从前向后找模式串第一次出现的位置，后者从后向前找模式串最后一次出现的位置。

建议在实际编程时使用现成“轮子”还有一个原因是，这些现成的轮子都是经过优化的，一般自己手写的模板算法在运行效率上是比不过它们的。比如最简单的 ``strstr()`` 函数往往在实践中会比自己手写的KMP算法速度更快，C++ string的两个成员函数现在则多是用优化过的Sunday算法实现的，自己手写的模板Sunday算法是不如它们速度快的。

.. attention::

   学些KMP这些经典算法，目的是学习这些算法的设计思路和思考问题的一般方法，这些经典算法中凝聚的是算法设计最伟大的智慧和最精妙的思想，学好它们能够大大提升解决算法问题的能力。另外，还要学习从算法到代码的能力和技巧，有了思路还要有能力把思路变成实际的C++代码。这就是为什么我们在前面说过，必须做好理解算法、读懂代码、纸笔模拟，并且手写实现的学习步骤，一步都不能少，甚至可以在此基础上尝试做一做改进优化代码的练习。


