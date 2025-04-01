# Mutex-RR [0 marks]

Due: 15 March 2025

Just for fun:\
If you want to further explore yesterday's experiment:
I have added a 'hook' in round robin scheduler that can log different values.

In `main`, I have added `count1` and `count2`, individual counters for the two functions.

You can play with the following aspects:

- Try different values of `N` (max count)
- Add multiple threads
- Estimate the time taken in a loop by looking at the number of times the counter increments in one time slot
- Look at the assembly code (`-S` option) to see how `count++` is actually implemented
- See the effect of `volatile` both for shared variable count, and individual `count1` and `count2`.

If you are theoretically inclined, you could explore a mini-project on this line: analysing and optimizing scheduling for certain applications.
