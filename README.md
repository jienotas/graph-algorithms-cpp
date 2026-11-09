# Scenic-area route system (adjacency-matrix graph, C++)

A console application built on a hand-written graph library: load a scenic area from
two text files, then query attractions, enumerate tour routes, compute shortest paths,
and design a minimum-cost cable layout.

Coursework from a data-structures course, kept because it is the cleanest example I
have of separating an interface (`*.h`) from an implementation (`*.cpp`) and building
an actual data structure rather than calling one from a library.

---

## What it does

Menu, five operations:

| # | Operation | Method |
|---|---|---|
| 1 | Load the map | `CreatGraph()` reads `Vex.txt` then `Edge.txt`, fills an adjacency matrix |
| 2 | Query an attraction | `GetSpotInfo()` — name, description, degree, adjacent attractions |
| 3 | Enumerate tour routes | `TravelPath()` — DFS over all simple paths from a start node, printed as route chains |
| 4 | Shortest path | `FindShortPath()` — exhaustive DFS over simple paths, keeps the minimum-weight one |
| 5 | Cable layout | `DesignPath()` — minimum spanning tree, reported edge by edge with total length |

## Input format

`Vex.txt` — node count, then one record per line, whitespace-separated:

```
7
0 北门 景区主入口，售票处
1 观景台 海拔 1200 米
...
```

`Edge.txt` — `u v w`, undirected, weight in metres:

```
0 2 700
0 4 1000
1 2 1000
```

## Build

**Visual Studio:** open `GraphPro.sln`, build, run. The project stores sources as
UTF-8, so add `/utf-8` to *C/C++ → Command Line → Additional Options* if the Chinese
string literals render as mojibake in the console (MSVC otherwise assumes the ANSI
code page).

**g++:**

```bash
g++ -std=c++17 -O2 -o graphpro main.cpp Graph.cpp Tour.cpp
./graphpro        # run from the directory containing Vex.txt and Edge.txt
```

## Design notes and known limits

- `AdjMatrix[20][20]` and `Vexs[20]` are fixed-size arrays inside `CGraph`. Correct and
  fast for the assignment's scale, wrong as a library: this is the first thing I would
  change today (dynamic allocation, or `std::vector<std::vector<int>>`).
- `Init()` fills the matrix with `0`, not infinity, and `InsertEdge` simply overwrites.
  So "no edge" and "zero-weight edge" are indistinguishable, which is fine for a
  positive-weight map and a landmine anywhere else. `INF` is defined but only used inside
  the shortest-path routine.
- Shortest path is exhaustive DFS, not Dijkstra. At ≤ 20 nodes it is acceptable and it
  has the side benefit of returning the actual path, but the worst case is factorial.
- No input validation beyond index bounds; a malformed `Edge.txt` will load silently.
- Chinese output uses `system("cls")` and console code pages, so it is Windows-centric.

## License

MIT — see `LICENSE`.
