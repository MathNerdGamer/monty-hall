# Monty Hall

A little C++ simulation for the Monty Hall problem.

Example usage:

```
./monty_hall 25000000
Result: 16666932 / 25000000
Using the optimal strategy, to swap after a goat is revealed, one wins 66.6677% of the time.
```

The true probability of winning the car is 2/3. This is because the probability of getting the car is the same as the probability of initially selecting a goat, as this means the other door must be a car after the goat reveal.