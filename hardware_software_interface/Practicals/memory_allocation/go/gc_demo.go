package main

import (
	"fmt"
	"runtime"
)

type node struct {
	name  string
	links []*node
}

func makeGraphs() *node {
	root := &node{name: "root"}
	left := &node{name: "left"}
	right := &node{name: "right"}
	root.links = []*node{left, right}
	left.links = []*node{root}

	// This cycle has no path from the returned root and is eligible for GC.
	unreachableA := &node{name: "unreachable A"}
	unreachableB := &node{name: "unreachable B"}
	unreachableA.links = []*node{unreachableB}
	unreachableB.links = []*node{unreachableA}

	return root
}

func main() {
	root := makeGraphs()
	fmt.Printf("Root %q keeps %q and %q reachable\n",
		root.name, root.links[0].name, root.links[1].name)
	fmt.Println("An unreferenced cycle is no longer reachable after makeGraphs returns.")

	var before runtime.MemStats
	runtime.ReadMemStats(&before)
	runtime.GC()
	runtime.KeepAlive(root)

	var after runtime.MemStats
	runtime.ReadMemStats(&after)
	fmt.Printf("Requested a garbage collection (NumGC: %d -> %d)\n",
		before.NumGC, after.NumGC)
	fmt.Printf("HeapAlloc after collection: %d bytes\n", after.HeapAlloc)
	fmt.Println("Heap statistics are runtime-wide; Go does not guarantee when an individual object is reclaimed.")
}
