+++
date = '2026-05-11T03:36:13+03:00'
draft = false
title = 'Memory Allocation'
toc = true
weight = 40
+++

# Memory Allocation

- Dynamic memory allocation
  - Size/ number of data stuctures may only be known at run time
  - Need to allocate space on the heap
  - Need to de-allocate (free) unused memory so it can be re-allocated
- Implementation
  - Implicit free lists
  - Explicit free lists
  - Sefregated free lists
- Garbage collection
- Commobly memory-related bugs in C programs


### Implicit Memory Allocation: Garbage Collection

**Garbage collection**

- Automatic reclamation of heap-allocated storage- application never has to free

```c
void foo()
{
    int *p = (int *)malloc(128);
    return; /*p block is now garbage */
}
```

- Common in functional languages, scripting languages, and modern object oriented languages:
    - Lisp, ML, Java, Perl, Mathematica

- Variants ("conservative" garbage collectors) exist for C and C++
    - However, cannot necessarilly collect all garbage

- How does the memory allocator know when memory can be freed?
    - In general, we cannot know what is going to be used in the future since it depends on conditions
    - But, we can tell that certain blocks cannot be used if there are no pointers to them

- So the memory allocator needs to know what is a pointer and what is not - how can it do this?

- We'll make some assumptions about pointers:
    - Memory allocator can distinguish pointers from non-pointers
    - All pointers point to the start of a block in the heap
    - Application cannot hide pointers (e.g., by coercing them to an int, and then back again)

**Classical GC Algorithms**

- Mark-and-sweep collection (McCarthy, 1960)
	- Does not move blocks (unless you also "compact")
- Refenrece counting (Collins, 1960)
	- Does not move blocks (not discussed)
- Copying collection (Minsky, 1963)
	- Moves blocks (not discussed)
- Generational Collectors (Lieberman and Hewitt, 1083)
	- Collection based on lifetimes
		- Most allocatotions become garbage very soon
		- So focus reclamation work on zones of memory recently allocated
- Resources: Jone and Lin, "Garbage Collection: Algorithms for Automatic Dynamic Memory", John Wiley & Sons, 1996

**Memory as a Graph**

- We view memory as a directed graph
	- Each allocated heap block is a node in the graph
	- Each pointer is an edge in the graph
	- Locations not in the heap that contain pointers into the heap are called root nodes (e.g. registers, locations on the stack, global variables)

![Memory as a Graph](/images/memory-graph.png)

- A node (block) is reachable if there is a path from any root to that node
- Non-reachable nodes are garbage (cannot be needed by the application)

**Mark and Sweep Collection**

- Can build on top of malloc/ free package
	- Allocate using malloc until you "run out of space"

- When out of space:
	- Use extra mark bit in the head of each block
	- Mark: Start at roots and set mark bit on each reachable block
	- Sweep: Scan all blocks and free blocks that are not marked

**Assumptions For a Simple Implementation**

- Application can use functions such as:

	- `new(n)`: returns pointer to new block with all locations cleared
	- `read(b,i)`: read locations i of block b into register
		- `b[i]`
	- `write(b, i, v)`: write v into location i of block b
		- `b[i] = v`

- Each block will have a header word
	- `b[-1]`

- Functions used by the garbage collector:
	- `is_ptr(p)`: determines whether p is a pointer to a block.
	- `length(p)`: returns length of block pointed to by p, not including header
	- `get_roots()`: returns all the roots

- Mark using depth-first traversal of the memory graph

```c
prt mark(ptr p)
{		
	if (!is_ptr(p)) return;				// p: some word in a heap block
	if (markBitSet(p)) return;		// do nothing if not pointer
	setMarkBit(p);								// check if already marked
	for (i=0; i < length(p) i++)	// set the mark bit
		mark(p[i]);									// recursively call mark on
	return;												//  all words in the block
}
```

- Sweep using lengths to find next block

```c
prt sweep(ptr p, ptr end)				// prts to start & end of heap
{																// while not at end of heap
	while (p < end) {							
		if markBitSet(p)						// check if block is marked 
			clearMarkBit();						// if so, reset mark bit
		else if (allocateBitSet(p))	// if not marked, but allocated
			free(p)										// free the block
		p += length(p);							// adjust pointer to next block
	}
}
```

**Conservative Mark & Sweep in C**

- Would mark & sweep work in C?
	- `is_ptr()` determins if a word is a pointer by checking if it points to an allocated block of memory
	- But in C, pointers can point into the middle of allocated blocks (not so in Java)
		- Makes it tricky to find all allocated blocks in makr phase
	- There are ways to solve/ avoid this problen in C, but the resulting garbage collector is `conservative`:
		- Every reachable node correctly identified as reachable, but some unreadchable nodes might be incorrectly marked as reachable

**Common memory-related bugs in C programs**

**Memory-Related Perils and Pitfalls**

- Dereferencing bad pointers
- Reading unintialized memory
- Overwriting memory
- Referencing nonexistent variables
- Freeing blocks multiple times
- Referencing freed blocks
- Failing to free blocks

**Derefencing Bad Pointers**

- The classic scanf bug

```c
int val;

...

scanf("%d", val);
```

- Will cause scanf to interpret contents of val as an address!
	- Best case: program terminates immediately due to segmentation fault
	- Worst case: contents of val correspond to some valid read/ write area of virtual memory, causing scanf to overwrite that memory, with disastrous and baffling cosequences much later in program execution.