# Important Warning

The algorith itself has been correctly implemented but I'm missing the actual compression part: we dump to file the encoded binary string by treating every digit (either 1 or 0) as an unsigned 8 bit integer. This means that something like `101` is going to be dumped as `00000001 00000000 00000001`.

This defeats the purpose of compression and results in an outfile bigger than the input. What we would need is:

```
parse digits in groups of 8 (8 bits), store that in an uint8_t and dump that entirely 
padding will be necessary but since we know the length we can discard whatever comes after that

0111110110110100110110110
becomes
10001111|10110110|10011011|0110 (and add 0s to pad it)
and then dump each part as an integer (first e.g. is 143 decimal)
```

As of right now, I'm going to put on hold this problem, I might come back to it later in the future.
