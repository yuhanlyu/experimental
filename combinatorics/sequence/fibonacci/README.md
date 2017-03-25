In the unit test, some arithmetics may overflow and may trigger undefined behavior.

Doubling method is faster than Q-matrix method, 
and tumble method is faster than iterative method.

<pre>
----------------------------------------------------
Benchmark             Time           CPU Iterations
----------------------------------------------------
BM\_Iterative         39 ns         39 ns   17947895
BM\_Doubling          11 ns         11 ns   66489336
BM\_Tumble            25 ns         25 ns   27036572
BM\_QMatrix           15 ns         15 ns   47370188
</pre>
