# HashTable
Implementing a hashtable that contains words and supports the following operations: add, remove, find, clear, print_bucket, print, resize double, resize halve.

Operations:
1) add <word>    
   - add word to hashtable
2) remove <word> 
   - remove word from hashtable
3) find <word> [out]
   - find word in hashtable, 
   - write True/False to a new line in the specified file or to the console if the parameter is missing
4) clear
   - empty table
5) print_bucket <index_bucket> [out]
   - write words from the bucket on a single line in the specified file or to the console if the parameter is missing
6) print [out]
   - print all buckets on separate lines in the specified file or to the console if the parameter is missing
7) resize double
   - doubles hash size
8) resize halve
   - halves hash size
  
Parameters:
- Initial legth of hashtable
- The following parameters are optional and represent a list of input files from which to read. If they are missing the           reading is done from the standard input (STDIN).
  
Example:
```
./tema1 256 hash1.in hash2.in
./tema1 100 < hash1.in
    
hash1.in:
add tema
add hash
print hash.out
find tema hash.out
remove tema
find tema hash.out
print hash.out
resize double
print
print_bucket 185 hash2.out
```
    
