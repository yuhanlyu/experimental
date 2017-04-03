# Josephus problem
[Josephus problem](https://en.wikipedia.org/wiki/Josephus_problem) is a
classic puzzle.

This module contains six methods of solving Josephus problem.
1. D. Woodhouse  
   [Programming the Josephus Problem](https://doi.org/10.1145/988906.988919)
2. Method from [Concrete Mathematics](https://en.wikipedia.org/wiki/Concrete_Mathematics) 3.3.
3. Method from [The Art of Computer Programming](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming) 1.3.3 Exercise 31.
4. Method from [The Art Of Computer Programming](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming).
5. Fatih Gelgi  
   [Time Improvement on Josephus Problem](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.5.177)
6. My space-efficient version of Gelgi's method.
   
## Benchmark
<pre>
----------------------------------------------------------------
Benchmark                         Time           CPU Iterations
----------------------------------------------------------------
BM_Woodhousea/2            15704256 ns   15638163 ns        448
BM_Woodhousea/3            15665934 ns   15636556 ns        447
BM_Woodhousea/9            15653078 ns   15636153 ns        448
BM_Woodhousea/27           15671668 ns   15635171 ns        448
BM_Woodhousea/81           15710185 ns   15638114 ns        448
BM_Woodhousea/243          15701817 ns   15638834 ns        447
BM_Woodhousea/729          15702990 ns   15638608 ns        448
BM_Woodhousea/2187         15677920 ns   15637234 ns        448
BM_Woodhousea/6561         15672952 ns   15631866 ns        448
BM_Woodhousea/19683        15634707 ns   15634419 ns        448
BM_Woodhousea/59049        15638739 ns   15638162 ns        448
BM_Woodhousea/177147       15635059 ns   15634729 ns        448
BM_Woodhousea/531441       15638216 ns   15637625 ns        447
BM_Woodhousea/1594323      15635885 ns   15635555 ns        448
BM_Woodhousea/2097152      15637111 ns   15636518 ns        448
BM_ConcreteMath/2               263 ns        263 ns   26622715
BM_ConcreteMath/3               448 ns        448 ns   15634585
BM_ConcreteMath/9              1588 ns       1588 ns    4410165
BM_ConcreteMath/27             4938 ns       4938 ns    1418015
BM_ConcreteMath/81            14997 ns      14997 ns     466595
BM_ConcreteMath/243           45178 ns      45177 ns     154921
BM_ConcreteMath/729          135773 ns     135768 ns      51565
BM_ConcreteMath/2187         407423 ns     407414 ns      17179
BM_ConcreteMath/6561        1222817 ns    1222770 ns       5726
BM_ConcreteMath/19683       3667424 ns    3667357 ns       1909
BM_ConcreteMath/59049      11003580 ns   11003257 ns        636
BM_ConcreteMath/177147     33002437 ns   33002167 ns        212
BM_ConcreteMath/531441     99023566 ns   99022833 ns         71
BM_ConcreteMath/1594323   297066064 ns  297063404 ns         24
BM_ConcreteMath/2097152   390787982 ns  390784788 ns         18
BM_TAOCP/2                      256 ns        256 ns   27301066
BM_TAOCP/3                      442 ns        442 ns   16017959
BM_TAOCP/9                     1567 ns       1567 ns    4408693
BM_TAOCP/27                    4824 ns       4824 ns    1450985
BM_TAOCP/81                   14652 ns      14652 ns     477809
BM_TAOCP/243                  44147 ns      44146 ns     158602
BM_TAOCP/729                 132633 ns     132632 ns      52768
BM_TAOCP/2187                398079 ns     398076 ns      17584
BM_TAOCP/6561               1194365 ns    1194356 ns       5862
BM_TAOCP/19683              3582781 ns    3582751 ns       1954
BM_TAOCP/59049             10748885 ns   10748808 ns        651
BM_TAOCP/177147            32248238 ns   32247935 ns        217
BM_TAOCP/531441            96773431 ns   96772704 ns         72
BM_TAOCP/1594323          290257216 ns  290255380 ns         24
BM_TAOCP/2097152          381906820 ns  381904020 ns         18
BM_TAOCPK/2                     257 ns        257 ns   27206639
BM_TAOCPK/3                     437 ns        437 ns   16024032
BM_TAOCPK/9                    1547 ns       1547 ns    4519575
BM_TAOCPK/27                   4818 ns       4818 ns    1452421
BM_TAOCPK/81                  14652 ns      14652 ns     477950
BM_TAOCPK/243                 44134 ns      44133 ns     158587
BM_TAOCPK/729                132669 ns     132664 ns      52797
BM_TAOCPK/2187               398008 ns     398003 ns      17592
BM_TAOCPK/6561              1194197 ns    1194158 ns       5860
BM_TAOCPK/19683             3582210 ns    3582158 ns       1954
BM_TAOCPK/59049            10748396 ns   10748061 ns        651
BM_TAOCPK/177147           32238433 ns   32237868 ns        217
BM_TAOCPK/531441           96738887 ns   96735478 ns         72
BM_TAOCPK/1594323         290156395 ns  290152829 ns         24
BM_TAOCPK/2097152         381738992 ns  381727344 ns         18
BM_Gelgi/2                      430 ns        430 ns   16275645
BM_Gelgi/3                      652 ns        652 ns   10737425
BM_Gelgi/9                     2018 ns       2018 ns    3467210
BM_Gelgi/27                    5849 ns       5849 ns    1198985
BM_Gelgi/81                   16057 ns      16057 ns     435808
BM_Gelgi/243                  42560 ns      42558 ns     164485
BM_Gelgi/729                 113253 ns     113250 ns      61800
BM_Gelgi/2187                315597 ns     315593 ns      22172
BM_Gelgi/6561                838665 ns     838640 ns       8348
BM_Gelgi/19683              2158674 ns    2158634 ns       3240
BM_Gelgi/59049              5263673 ns    5263505 ns       1328
BM_Gelgi/177147            11473293 ns   11472988 ns        609
BM_Gelgi/531441            22018347 ns   22017475 ns        318
BM_Gelgi/1594323           21585450 ns   21584993 ns        324
BM_Gelgi/2097152           15750328 ns   15749838 ns        444
BM_ImprovedGelgi/2              518 ns        518 ns   13472676
BM_ImprovedGelgi/3              753 ns        753 ns    9289662
BM_ImprovedGelgi/9             2201 ns       2201 ns    3179584
BM_ImprovedGelgi/27            6104 ns       6104 ns    1146714
BM_ImprovedGelgi/81           16788 ns      16787 ns     416981
BM_ImprovedGelgi/243          45615 ns      45614 ns     153461
BM_ImprovedGelgi/729         122663 ns     122661 ns      57049
BM_ImprovedGelgi/2187        326171 ns     326163 ns      21469
BM_ImprovedGelgi/6561        851813 ns     851794 ns       8217
BM_ImprovedGelgi/19683      2179307 ns    2179261 ns       3212
BM_ImprovedGelgi/59049      5389461 ns    5389330 ns       1299
BM_ImprovedGelgi/177147    12641128 ns   12640867 ns        554
BM_ImprovedGelgi/531441    16758561 ns   16758219 ns        418
BM_ImprovedGelgi/1594323   16764898 ns   16764532 ns        418
BM_ImprovedGelgi/2097152   16756726 ns   16756368 ns        418
</pre>

Note that the performance of Woodhousea method is very stable, 
and is faster than Gelgi's method when m is close to n.
