# Memory Allocation and Garbage Collection

These examples demonstrate the garbage-collection concepts in the memory
allocation notes.

## Run the examples

From this directory:

```sh
make run
```

Build or run one language at a time with `make build-c`, `make run-c`,
`make build-go`, or `make run-go`. Use `make clean` to remove generated
binaries.

## C: explicit mark-and-sweep

`c/mark_sweep.c` implements a small collector for a linked list of heap
objects. The program supplies its roots explicitly. Marking follows object
references from those roots and uses a mark bit to avoid revisiting nodes,
including nodes in cycles. Sweeping frees unmarked objects and clears the mark
bits on live objects.

The collector recognizes only exact pointers to its own allocated objects.
This is a teaching example, not a conservative collector for arbitrary C
programs.

## Go: automatic garbage collection

`go/gc_demo.go` creates a reachable object graph and an unreachable cycle, then
requests a garbage collection with `runtime.GC`. Go's runtime traces pointers
from roots and can reclaim unreachable cycles automatically; programs do not
call `free`. The runtime does not expose deterministic, per-object reclamation,
so the example reports runtime heap statistics rather than claiming that a
particular object was freed at a specific time.
