import filecmp
  
f1 = "TestingFiles/tmp.bin"
f2 = "TestingFiles/tmp2.bin"
  

result = filecmp.cmp(f1, f2, shallow=False)
print(result)