def generate_big_random_bin_file(filename,size):
    """
    generate big binary file with the specified size in bytes
    :param filename: the filename
    :param size: the size in bytes
    :return:void
    """
    import os 
    with open('%s'%filename, 'wb') as fout:
        fout.write(os.urandom(size)) #1

    print ('big random binary file with size %f generated ok'%size)
    pass 
def generate_big_random_letters(filename,length):
    
    import random
    import string
    letters = "1234567890-=!@#$%^&*()_+qwertyuiop[]\\QWERTYUIOP{}|asdfghjkl;\'ASDFGHJKL:\"zxcvbnm,./ZXCVBNM<>?"

    chars = ''.join([random.choice(letters) for i in range(length)]) #1


    with open(filename, 'w') as f:
        f.write(chars)
    pass

generate_big_random_letters("test.txt", 10000)
