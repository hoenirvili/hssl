#!/bin/bash

echo "Lorem Ipsum este pur şi simplu o machetă pentru text a industriei tipografice. Lorem Ipsum a fost macheta standard a industriei încă din secolul al XVI-lea, când un tipograf anonim a luat o planşetă de litere şi le-a amestecat pentru a crea o carte demonstrativă pentru literele respective. Nu doar că a supravieţuit timp de cinci secole, dar şi a facut saltul în tipografia electronică practic neschimbată. A fost popularizată în anii '60 odată cu ieşirea colilor Letraset care conţineau pasaje Lorem Ipsum, iar mai recent, prin programele de publicare pentru calculator, ca Aldus PageMaker care includeau versiuni de Lorem Ipsum" > file.txt
echo -e "====== FILE CONTENT ======"
echo -e
cat file.txt
echo -e
echo -e "=========================="
echo -e
echo -e "===== GEN HAS FUNC ======"
echo -e "openssl dgst -c -hex -sha256 file.txt > h1.txt"
echo -e "openssl dgst -c -hex -sha256 file.txt >> h1.txt"
openssl dgst -c -hex -sha256 file.txt > h1.txt
openssl dgst -c -hex -md5 file.txt >> h1.txt
echo -e "==========================="
echo -e
cat h1.txt
echo -e
echo "Lorem Ipsum este pur şi simplu o machetă ptntru text a industriei tipografice. Lorem Ipsum a fost macheta standard a industriei încă din secolul al XVI-lea, când un tipograf anonim a luat o planşetă de litere şi le-a amestecat pentru a crea o carte demonstrativă pentru literele respective. Nu doar că a supravieţuit timp de cinci secole, dar şi a facut saltul în tipografia electronică practic neschimbată. A fost popularizată în anii '60 odată cu ieşirea colilor Letraset care conţineau pasaje Lorem Ipsum, iar mai recent, prin programele de publicare pentru calculator, ca Aldus PageMaker care includeau versiuni de Lorem Ipsum" > file.txt
cat file.txt
echo -e 
echo -e "===== GEN HAS FUNC ======"
echo -e "openssl dgst -c -hex -sha256 file.txt > h2.txt"
echo -e "openssl dgst -c -hex -sha256 file.txt >> h2.txt"
openssl dgst -c -hex -sha256 file.txt > h2.txt
openssl dgst -c -hex -md5 file.txt >> h2.txt
echo -e "==========================="
cat h2.txt

