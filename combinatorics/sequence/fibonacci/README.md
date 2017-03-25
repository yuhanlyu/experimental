In the unit test, some arithmetics may overflow and may trigger undefined behavior.

Doubling method is faster than Q-matrix method, 
and tumble method is faster than iterative method.

<pre>
----------------------------------------------------
Benchmark             Time           CPU Iterations
----------------------------------------------------
BM_Iterative         39 ns         39 ns   17952331
BM_Doubling          11 ns         11 ns   66511465
BM_Tumble            24 ns         24 ns   29845878
BM_QMatrix           15 ns         15 ns   47363973
</pre>
