# Hash functions

Textul dat ca exemplu:

```text
Lorem Ipsum este pur şi simplu o machetă pentru text a industriei tipografice. Lorem Ipsum a fost macheta standard a industriei încă din secolul al XVI-lea, când un tipograf anonim a luat o planşetă de litere şi le-a amestecat pentru a crea o carte demonstrativă pentru literele respective. Nu doar că a supravieţuit timp de cinci secole, dar şi a facut saltul în tipografia electronică practic neschimbată. A fost popularizată în anii '60 odată cu ieşirea colilor Letraset care conţineau pasaje Lorem Ipsum, iar mai recent, prin programele de publicare pentru calculator, ca Aldus PageMaker care includeau versiuni de Lorem Ipsum
```
Rezultatele functiilor **hash** a textului
```
SHA256(file.txt)= c2:c7:66:37:26:ad:24:59:c1:65:75:d5:86:ce:65:a9:97:88:bd:06:cd:80:8c:3e:14:47:24:f0:cc:72:3d:19
MD5(file.txt)= c5:79:c5:1d:dc:f3:9f:5d:5a:68:d6:3d:8a:af:ac:24
```

Dupa modificarea unei litere din cuvantul `pentru` in `ptntru` obtine noi functii hash

```
SHA256(file.txt)= 50:43:67:08:53:ad:92:04:1a:6f:07:e0:f5:f1:d0:e3:a1:0d:3a:0c:90:ff:3c:b8:6c:5c:59:d8:6e:1c:96:b8
MD5(file.txt)= 01:b5:07:aa:25:50:f5:34:7b:55:64:8e:47:b3:0e:45
```

# Observatie
Chiar daca s-a modificat un caracter functiile hash rezultante nu sunt deloc identice.
Daca scriem un cod pentru testarea fiecarui bit in parte din chei gasim doar un byte identic.

Un cod exemplu de comparararea rezultatelor functiilor hash in GoLang ar fi asa.

```go
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
```

# Stdout
```
INDEX BYTE=  5 5
a   a
d   d
EQUAL BYTE COUNT:  1
```

> Doar byte-ul de pe pozitia a 5-a (**0xad**) din sha256 a ramas identic.