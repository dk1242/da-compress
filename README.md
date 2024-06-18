# dacompress
`dacompress` is a simple tool to compress and decompress the text files following the [**Huffman Coding Tree Algorithm**](https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/Huffman.html).
```
dacompress [--options] <filename>
```
## Installation
### Linux:
  Run `make` in the project folder.
### Other machines:
Run `g++ -o dacompress main.cpp` and use it using `./dacompress`.
## Usage
`dacompress` can be used in 3 direct ways:
```
1. Without specifying any option, it will self analyze the file and will compress or decompress it 

->      dacompress <filename> 

```
```
2. With compress option
->      dacompress --compress <filename> 

```
```
3. With decompress option
->      dacompress --decompress <filename> 

```

## Examples
```bash
➜  da-compress git:(main) ✗ dacompress --compress test.txt
Compressed file generated: compressed_test.txt
```
```bash
➜  da-compress git:(main) ✗ dacompress test.txt
Compressed file generated: compressed_test.txt
```
```
➜  da-compress git:(main) ✗ dacompress compressed_test.txt 
Decompressed file generated: decompressedcompressed_test.txt.txt
```

## References
1. For project idea: [Build Your Own Compression Tool](https://codingchallenges.fyi/challenges/challenge-huffman/)
2. [Huffman Coding Trees](https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/Huffman.html)