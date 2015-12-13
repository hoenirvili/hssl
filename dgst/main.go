package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func main() {
	hashOne, err := ioutil.ReadFile("h1.txt")
	if err != nil {
		fmt.Println("Can't read from file")
		os.Exit(1)
	}
	hashTwo, err := ioutil.ReadFile("h2.txt")
	if err != nil {
		fmt.Println("Ca't read from file")
		os.Exit(1)
	}
	// remove extra chars
	sanitHashOne := strings.Replace(string(hashOne), "SHA256(file.txt)= ", "", -1)
	sanitHashOne = strings.Replace(sanitHashOne, "MD5(file.txt)= ", "", -1)
	sanitHashOne = strings.Replace(sanitHashOne, ":", "", -1)

	sanitHashTwo := strings.Replace(string(hashTwo), "SHA256(file.txt)= ", "", -1)
	sanitHashTwo = strings.Replace(sanitHashTwo, "MD5(file.txt)= ", "", -1)
	sanitHashTwo = strings.Replace(sanitHashTwo, ":", "", -1)

	var count = 0

	for i, j := 0, 0; i < 63 && j < 63; i, j = i+2, j+2 {
		if sanitHashOne[i] == sanitHashTwo[j] && sanitHashOne[i+1] == sanitHashTwo[i+1] {
			fmt.Println("INDEX BYTE= ", i/2, j/2)
			fmt.Println(string(sanitHashOne[i]), " ", string(sanitHashTwo[j]))
			fmt.Println(string(sanitHashOne[i+1]), " ", string(sanitHashTwo[j+1]))
			count = count + 1
		}
	}
	for i, j := 64, 64; i < len(sanitHashOne)-1 && j < len(sanitHashTwo)-1; i, j = i+2, j+2 {
		if sanitHashOne[i] == sanitHashTwo[j] && sanitHashOne[i+1] == sanitHashTwo[j+1] {
			fmt.Println("INDEX BYTE= ", i/2, j/2)
			fmt.Println(string(sanitHashOne[i]), " ", string(sanitHashTwo[j]))
			fmt.Println(string(sanitHashOne[i+1]), " ", string(sanitHashTwo[j+1]))
			count = count + 1
		}
	}

	fmt.Println("EQUAL BYTE COUNT: ", count)
}
