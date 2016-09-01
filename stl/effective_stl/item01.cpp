// Item 1: Choose your containers with care.

● 标准STL序列容器：vector、string、deque和list。
● 标准STL关联容器：set、multiset、map和multimap。
● 非标准序列容器slist和rope。slist是一个单向链表，rope本质上是一个重型字符串。（“绳子（rope）”是重型的“线（string）”。明白了吗？）你可以找到一个关于这些非标准（但常见的）容 器的概览在条款50。
● 非标准关联容器hash_set、hash_multiset、hash_map和hash_multimap。我在条款25检验了这些可以广泛获得的基于散列表的容器和标准关联容器的不同点。
● vector<char>可以作为string的替代品。条款13描述了这个替代品可能会有意义的情况。
● vector作为标准关联容器的替代品。就像条款23所说的，有时候vector可以在时间和空间上都表现得比标准关联容器好。
● 几种标准非STL容器，包括数组、bitset、valarray、stack、queue和priority_queue。因为它们是非STL容器，所以在本书中关于它们我说得很少，虽然条款16提到了数组比STL容器更有优势的一种情况，而条款18揭示了为什么bitset可能比vector<bool>要好。值得注意的是，数组可以和STL算法配合，因为指针可以当作数组的迭代器使用。
