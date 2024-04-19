LEVENSHTEIN DISTANCE:
Levenshtein Distance, also called as Edit Distance is a problem used to convert one string into other string with minimum no.of of operations.
The operations include three:
  1.Replace
  2.Insert
  3.Delete
These problem can be solved in different ways 
  1.Recursive approach
  2.Iterative approach
  3.Dynamic programming approach
However, using Dynamic Programming will be more efficient than other two approaches.
In Dynamic Programming it can be solved using either Top-down approach or Bottom-up approach.Often Bottom-up approach is prefered for it's simplicity.
This problem uses a table to store solutions of subproblems multiple times.So if same sub problems are repeated then we simply retrieve the solutions from the table itself.
BEST CASE SCENARIO:
  Occurs when the two input strings are identical.
  In this case no operations are needed to transform from one string into other string so distance is "0".
  But the time complexity remains O(m*n)
WORST CASE SCENARIO:
  Occurs when none of the characters in the two input strings match.
  Then distance would be maximum length of two strings as it would require completely changing one string into other string.
  Remains same time complexity O(m*n)
