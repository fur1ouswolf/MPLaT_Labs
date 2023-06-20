package main

import (
	"fmt"
)

type Edge struct {
	first  int
	second int
	length int
}

type Graph struct {
	edges []Edge
}

func (g *Graph) addEdge(v Edge) {
	g.edges = append(g.edges, v)
}

func (g *Graph) printGraph() {
	fmt.Println(g.edges)
}

func (g *Graph) dijkstra(start int, end int) int {
	length := make([][]int, len(g.edges))
	for i := 0; i < len(g.edges); i++ {
		length[i] = make([]int, len(g.edges))
		for j := 0; j < len(g.edges); j++ {
			length[i][j] = -1
		}
	}
	length[start][start] = 0
	for i := 0; i < len(g.edges); i++ {
		length[g.edges[i].first][g.edges[i].second] = g.edges[i].length
	}

	for i := 0; i < len(g.edges); i++ {
		for j := 0; j < len(g.edges); j++ {
			if length[i][j] == -1 {
				continue
			}
			for k := 0; k < len(g.edges); k++ {
				if length[j][k] == -1 {
					continue
				}
				if length[i][k] == -1 || length[i][k] > length[i][j]+length[j][k] {
					length[i][k] = length[i][j] + length[j][k]
				}
			}
		}
	}

	return length[start][end]
}

func main() {
	var g Graph
	g.addEdge(Edge{0, 1, 6})
	g.addEdge(Edge{0, 2, 1})
	g.addEdge(Edge{0, 3, 1})
	g.addEdge(Edge{0, 5, 3})
	g.addEdge(Edge{1, 4, 1})
	g.addEdge(Edge{2, 3, 1})
	g.addEdge(Edge{3, 6, 10})
	g.addEdge(Edge{4, 6, 7})
	g.addEdge(Edge{5, 6, 1})
	g.printGraph()
	fmt.Println(g.dijkstra(0, 6))

}
