// stack_demo.go — Go: Stack Frames, Escape Analysis & Calling Conventions
//
// Go manages stacks automatically (goroutine stacks grow/shrink on demand),
// but the same concepts from the notes apply:
//
//   1. swap           — pointer args; Go passes by value, so we pass pointers
//   2. sfact          — recursive factorial with accumulated pointer (like notes)
//   3. Escape analysis— when a local "escapes" to the heap (Go's &val analogue)
//   4. Register ABI   — Go 1.17+ passes args in registers (like x86-64 notes)
//   5. Stack growth   — goroutines start with small stacks that grow dynamically

package main

import (
	"fmt"
	"runtime"
	"unsafe"
)

// -------------------------------------------------------------------
// 1. swap — pointer-based swap (mirrors the C/asm version in the notes)
//    In Go 1.17+ the compiler passes xp, yp in registers (rdi, rsi).
// -------------------------------------------------------------------
func swap(xp, yp *int) {
	t0 := *xp
	t1 := *yp
	*xp = t1
	*yp = t0
}

func callSwap() {
	zip1 := 15213
	zip2 := 98195
	fmt.Printf("  Before: zip1=%d  zip2=%d\n", zip1, zip2)
	swap(&zip1, &zip2) // Go takes address of locals freely
	fmt.Printf("  After : zip1=%d  zip2=%d\n", zip1, zip2)
}

// -------------------------------------------------------------------
// 2. sfact — mirrors the notes exactly:
//    val lives on sfact's stack frame; &val is passed to sHelper.
//    Go's escape analysis decides whether val stays on stack or heap.
// -------------------------------------------------------------------
func sHelper(x int, accum *int) {
	if x <= 1 {
		return
	}
	z := (*accum) * x // z is a local variable on sHelper's frame
	*accum = z
	sHelper(x-1, accum)
}

func sfact(x int) int {
	val := 1           // val may be stack-allocated if it doesn't escape
	sHelper(x, &val)   // pass pointer — forces val to be addressable
	return val
}

// -------------------------------------------------------------------
// 3. Escape analysis demo
//    When we return a pointer to a local, Go moves it to the heap.
//    This is the Go equivalent of why val needs stack space in the notes.
// -------------------------------------------------------------------

//go:noinline
func escapesToHeap() *int {
	x := 42    // x escapes: we return its address
	return &x  // compiler: "x moved to heap"
}

//go:noinline
func staysOnStack() int {
	x := 42 // x does NOT escape: we return the value
	return x
}

func escapeDemo() {
	hp := escapesToHeap()
	sv := staysOnStack()
	fmt.Printf("  escapesToHeap() -> *%p = %d  (heap allocated)\n", hp, *hp)
	fmt.Printf("  staysOnStack()  -> %d          (register/stack)\n", sv)
}

// -------------------------------------------------------------------
// 4. Closure capturing a local — the Go analogue of the notes'
//    "pointer to local variable" pattern.
//    The closed-over variable is heap-allocated automatically.
// -------------------------------------------------------------------
func makeAccumulator(start int) func(int) int {
	sum := start // captured by the closure → escapes to heap
	return func(delta int) int {
		sum += delta
		return sum
	}
}

func closureDemo() {
	acc := makeAccumulator(0)
	for _, v := range []int{10, 20, 30, 40} {
		fmt.Printf("  acc(%d) = %d\n", v, acc(v))
	}
}

// -------------------------------------------------------------------
// 5. Stack growth — Go goroutines start with 2–8 KB stacks and grow.
//    Deep recursion triggers stack copying, unlike fixed-size C stacks.
// -------------------------------------------------------------------
func deepRecurse(n int) int {
	if n == 0 {
		return 0
	}
	// Allocate a local array to force stack growth pressure
	var frame [64]byte
	frame[0] = byte(n)
	_ = frame
	return 1 + deepRecurse(n-1)
}

func stackGrowthDemo() {
	depth := 10_000
	result := deepRecurse(depth)
	fmt.Printf("  Recursed %d levels without stack overflow (Go grew the stack)\n", result)
}

// -------------------------------------------------------------------
// 6. Register ABI info (Go 1.17+)
//    Show that Go now passes up to 9 integer args in registers,
//    matching x86-64 conventions described in the notes.
// -------------------------------------------------------------------
func registerABIInfo() {
	fmt.Printf("  Go version : %s\n", runtime.Version())
	fmt.Printf("  GOARCH     : %s\n", runtime.GOARCH)
	fmt.Printf("  int size   : %d bytes (pointer-sized on this arch)\n", int(unsafe.Sizeof(int(0))))
	fmt.Println("  Since Go 1.17, integer args are passed in registers")
	fmt.Println("  (rax, rbx, rcx, rdi, rsi, r8, r9, r10, r11 on amd64)")
	fmt.Println("  — matching the x86-64 calling convention in the notes.")
}

// -------------------------------------------------------------------
// main
// -------------------------------------------------------------------
func main() {
	fmt.Println("\n=== 1. Pointer Swap ===")
	callSwap()

	fmt.Println("\n=== 2. Recursive sfact (pointer to local) ===")
	for n := 1; n <= 7; n++ {
		fmt.Printf("  sfact(%d) = %d\n", n, sfact(n))
	}

	fmt.Println("\n=== 3. Escape Analysis ===")
	escapeDemo()

	fmt.Println("\n=== 4. Closure Capturing a Local (heap escape) ===")
	closureDemo()

	fmt.Println("\n=== 5. Stack Growth via Deep Recursion ===")
	stackGrowthDemo()

	fmt.Println("\n=== 6. Register ABI Info ===")
	registerABIInfo()

	fmt.Println()
}
