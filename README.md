# The-Traveling-Salesman-Problem

## Description
The problem of finding a cycle in a graph that contains all vertices (each exactly once) and has the lowest possible cost.

## Design

The program is primarily responsible for sorting the cities in such a way as to get the shortest route between them. At its input, it downloads data in the format ("A B C"), where:
- A stands for the identifier of a given city
- B is the latitude coordinate
- C magnitude coordinate

After the operations are performed, the program correctly writes out the converted data in the data collection to the output.

## Dependiencies

```cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>
#include <bits/stdc++.h>
```

## Results

Sample route calculated between 9 cities (Warsaw, Amsterdam, Berlin, Helsinki, London, Minsk, Paris, Stockholm, Zagreb)

![route example](https://github.com/Adam1904/The-Traveling-Salesman-Problem/blob/main/route%20example.png)
[link to the source](https://www.google.com/maps/)
