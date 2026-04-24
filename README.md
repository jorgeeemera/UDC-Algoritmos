# Algoritmos - UDC Engineering
This repository contains implementations and empirical efficiency analyses of fundamental algorithms developed for the **Algoritmos** course at the University of A Coruña.

## 📊 Featured Project: Fibonacci Efficiency Study
A comprehensive empirical study analyzing three different algorithms to calculate the Fibonacci sequence, comparing execution times with theoretical complexities:
- **fib1**: Recursive approach ((\phi^n)$ complexity). Acceptable for small $ but inefficient for large scales.
- **fib2**: Iterative linear approach ((n)$ complexity).
- **fib3**: Optimized logarithmic approach ((\log n)$ complexity), identified as the best option for high-magnitude calculations.

## 📁 Repository Structure
- **/FIBONACCI**: Empirical analysis and C implementations.
- **/SORTING**: Classical sorting algorithm implementations.
- **/DISPERSION**: Hash tables and dispersion function analysis.
- **/HEAPSORT**: Implementation and theoretical analysis.

## 💻 Development Environment
- **Hardware**: MacBook Pro 14" (Apple Silicon M1, 16GB RAM).
- **OS**: macOS Sequoia 15.0.
- **Compiler**: Apple clang version 16.0.0.

## 📋 Methodology
- Execution time measured in microseconds (μs).
- Implementation of average-of-k-executions for small time measurements ( < 500\mu s$) to ensure accuracy.
- Use of underestimating and overestimating bounds for precise complexity validation.
