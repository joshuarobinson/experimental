package main

import (
	"fmt"
	"math"
	"os"
	"io/ioutil" )

func getByteEntropy(filename string) (float64, error) {
	bs, err := ioutil.ReadFile(filename)
	if err != nil {
		return 0.0, err
	}

	byte_counters := make(map[byte]int)
	for _, i := range bs {
		byte_counters[i] += 1
	}

	var entropy float64
	for _, count := range byte_counters {
		p_i := float64(count) / float64(len(bs))
		entropy -= p_i * math.Log2(p_i)
	}

	return entropy, nil
}

func main() {
	for _, element := range os.Args[1:] {
		entropy, err := getByteEntropy(element)
		if err == nil {
			fmt.Printf("%s\t%f\n", element, entropy)
		}
	}
}
