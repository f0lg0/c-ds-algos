# Graphs

Graph is a pair (V, E) where V is a finite set of vertices and E is a finite set of edges.

Examples of graphs:

![graphs](../assets/graphs.png)

An edge with an orientation is a directed edge, while an edge with no orientation is an undirected edge.
If all the edges in a graph are undirected then the graph is an undirected graph.

## Representation of Graphs

There are two ways of representing graphs with code:

-   Adjacency matrix
-   Adjecency list

### Matrix

![matrix](../assets/matrix.png)

1 if there is an edge from Vi to Vj

0 otherwise

In case of a weighted graph then the entries are the weight of the edges.

### List

In this representation, the n rows of the adjacency matrix are represented as n linked lists. An array Adj[1, 2, . . . . . n] of pointers where for 1 < v < n, Adj[v] points to a linked list containing the vertices which are adjacent to v (i.e. the vertices that can be reached from v by a single edge). If the edges have weights then these weights may also be stored in the linked list elements.

![list](../assets/list.png)
