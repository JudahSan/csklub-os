// Concept:
// - In Go, we can view values as byte slices using the
// encoding/binary package and the math package for float bits.
// - Like C, this reveals endianness and biray encoding details
// $ make run-go

package main

import (
	"encoding/binary"
	"fmt"
	"math"
	"unsafe"
)

// showBytes prints the memory address and value of each byte
// in the provided byte slice

func showBytes(data []byte) {
	for i, b := range data {
		fmt.Printf("%p\t0x%.2x\n", unsafe.Pointer(&data[i]), b)
	}
	fmt.Println()
}

// showInt demonstrates byte-level representation of an int32 value
func showInt(x int32) {
	fmt.Printf("int a = %d;\n", x)

	// convert int to byte array (Little Endian)
	buf := make([]byte, 4)
	binary.LittleEndian.PutUint32(buf, uint32(x))

	showBytes(buf)
}

// showFloat demostrates byte-level representation of a float32 value
func showFloat(x float32) {
	fmt.Printf("float b = %.2f;\n", x)

	// convert float to IEEE 754 bit representation
	buf := make([]byte, 4)
	binary.LittleEndian.PutUint32(buf, math.Float32bits(x))

	showBytes(buf)
}

// showDouble demonstrates byte-level representation of a float64 value
func showDouble(x float64) {
	fmt.Printf("double c = %.2f;\n", x)

	buf := make([]byte, 8)
	binary.LittleEndian.PutUint64(buf, math.Float64bits(x))

	showBytes(buf)
}

func main() {
	showInt(12345)
	showFloat(12345.0)
	showDouble(12345.0)
}
