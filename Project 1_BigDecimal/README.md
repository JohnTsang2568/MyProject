Usage: Open testApp.sln.

Description: Implements arithmetic operations for arbitrarily long integers (including positive and negative) and arbitrary‑precision real numbers.

Input format: The input consists of 3n+1 lines. The first line is an integer n, representing the number of computation groups.

The next 3n lines are the group contents. Each group has 3 lines: the first line indicates whether to perform multiplication or division; the second and third lines are the two numbers. Each group is processed sequentially.

Output: The output contains n lines, each ending with a newline. If decimals are involved, trailing zeros after the decimal point should be omitted. If all digits after the decimal point are zero, the decimal point should also be omitted.

For decimal results, at most 10 decimal places are kept, rounded. If the absolute value of the divisor is less than 1e-6, output "ERROR".