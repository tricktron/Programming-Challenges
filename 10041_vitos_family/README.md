# README
The problem is described here: [Problem](10041_problem.pdf)

<details>
<summary> Solution </summary>
<p>
We need to find the sum of each elements absolute distance to the
median as this is the *central* house.
This comes down to finding the median of an array and it is thus a
partial sorting problem.
Approach | Runtime
--- | ---
Sort the array and pick the median. | nlogn
Use the randomized selection algorithm described in selection.tex | n on average
Use the selection algorithm described in median_selection.tex | n worst case

Surprisingly the randomized approach performs better because finding
the median of medians generates more overhead on average.
</p>
</details>

