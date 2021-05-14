# huffman-compressor

data structures project

# todo

- [X] research huffman coding
  - [X] linked list priority queue
  - [X] binary tree data structure that serves as a base for the Huffman tree
  - [X] build a huffman tree using the binary tree
- [X] divide tasks
- [ ] if file is too small to be compressed print that and exit

## samir  

- [X] read user specified text
- [X] use a map or hash table
- [X] Implement a linked-list priority queue to dynamically sort the frequency table
- [X] Design the required binary tree data structure that serves as a base for the Huffman tree
  - [X] Only one binary tree is allowed
  - [X] The tree data field must be able to accommodate both the frequency and the value of any character

## peter

- [X] build the huffman tree
- [X] Generate the variable-length codes from the Huffman tree
- [X] serialize hash table into a file with .cod extension 
- [X] The generated codes must be displayed on the screen and saved with the same filename as the input+'.cod'
  
## youssef

- [ ] Compress the input file using the codes generated from the Huffman tree
  - [ ] The generated output must have the same filename as the input but with the extension '.com'
  - [ ] The output file cannot have a size larger than the input file

## 3sam

- [ ] Decompress any previously compressed file using the code file
  - [ ] The decompressed file must match the original uncompressed file.
  - [ ] You must use the code file generated in to retrieve the codes required for the decompression process.

# extra

- [ ] turn app to command line application
- [ ] exit if non ascii file entered

# optimisation

- [ ] read huge files in small chuncks to fit memory <https://stackoverflow.com/questions/34751873/how-to-read-huge-file-in-c>
- [ ] opt linked list by adding size instead of iterating all over it every time
