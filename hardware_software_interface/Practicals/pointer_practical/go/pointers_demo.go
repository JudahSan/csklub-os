package main

import "fmt"

func increment(num *int) {
	*num = *num + 1 // dereference and modify
}

func main() {
	a := 10
	ptr := &a

	fmt.Println("a =", a)
	fmt.Println("&a =", &a, "(address of a)")
	fmt.Println("ptr =", ptr, "(value of pointer)")
	fmt.Println("*ptr =", *ptr, "(value at address p)")

	*ptr = 20
	fmt.Println("\nAfter *p = 20;")
	fmt.Println("a =", a)
	fmt.Println("*ptr =", *ptr)

	increment(ptr)
	fmt.Println("\nAfter increment(p);")
    fmt.Println("a =", a)
}