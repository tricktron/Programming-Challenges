# Solution
We need to find the sum of each elements absolute distance to the
median as this is the *central* house.
This comes down to finding the median of an array and it is thus a
partial sorting problem.

Approach | Runtime
--- | ---
Sort the array and pick the median. | nlogn
Randomized selection see [test](test)  | n on average
Median selection see  | n worst case


Approach | Code | Result
--- | --- | ---
Randomized selection | [vito_random](vito_random.c) | ![uva result](vito_median_runtime.png)


Surprisingly the randomized approach performs better because finding
the median of medians generates more overhead on average.