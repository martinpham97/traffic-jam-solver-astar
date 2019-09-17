# traffic-jam-solver-astar

A [Rush hour](https://en.wikipedia.org/wiki/Rush_Hour_(puzzle)) like puzzle solver using A* algorithm.

The Objects are highly optimized for the performance of the algorithm (expect some readability issues, though I've tried to document everything).

## Example

The board is an NxN grid with interlocking blocks of cars.

Each car will be represented by its ID. By default, the main car's ID is 1.

Each car can only be moved either horizontally or vertically depending on its orientation.

The goal is to move the main car towards the exit (which to make it touch the edge of the board).

### Initial state

```
000333
004060
114060
554007
022207
000007
```

### Possible solved state

```
033360
004060
004011
554007
002227
000007
```

### Sample output from the program using A* algorithm

```
Solution found in: 3 ms
Moves: 19
000333
004060
114060
554007
022207
000007

000333
004060
114060
554007
022207
000007

003330
004060
114060
554007
022207
000007

033300
004060
114060
554007
022207
000007

033360
004060
114000
554007
022207
000007

033360
004060
114000
554007
002227
000007

033360
004060
114007
554007
002227
000000

033360
004067
114007
554007
002220
000000

033360
004067
114007
554007
000222
000000

033360
000067
114007
554007
004222
000000

033360
000067
110007
554007
004222
004000

033360
000067
011007
554007
004222
004000

033360
000067
001107
554007
004222
004000

033360
000067
000117
554007
004222
004000

033360
000067
004117
554007
004222
000000

033360
004067
004117
554007
000222
000000

033360
004067
004117
554007
002220
000000

033360
004060
004117
554007
002227
000000

033360
004060
004110
554007
002227
000007

033360
004060
004011
554007
002227
000007
```

## Performance

The program utilises multiple optimisation methods to improve performance:
- Using a linear 1D array instead of 2D to store the state of the board improves performance due to memory locality
- Using references to avoid copy constructing objects

## Testing

Unit testing for most functions are available under the TrafficJamLogicTest directory.