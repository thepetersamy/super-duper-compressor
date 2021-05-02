import filecmp
  
f1 = "/home/peter/stuff/huffman-compressor/Huffman-compressor/Huffman-compressor/file1.txt"
f2 = "/home/peter/stuff/huffman-compressor/Huffman-compressor/Huffman-compressor/file2.txt"
  

result = filecmp.cmp(f1, f2, shallow=False)
print(result)