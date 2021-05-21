import filecmp
  
f1 = "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\TestingFiles\\1.txt"
f2 = "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\TestingFiles\\2_d.txt"
  

result = filecmp.cmp(f1, f2, shallow=False)
print(result)