# C++ Projects
--------------
This repository contains solutions to the programming labs of an introductory course in the C++ programming language.

Special importance has been laid on writing code that is well tested, is easy to read, can be refactored without major changes, and most importantly, has no memory leaks.

Compilation is based on c++23, testing is based on the Catch2 framework and memory check is based on the valgrind tool.

# Projects
-----------
# I/O operations
Starting out with C++ code and handling input/output operations as well as text manipulation.

# Time
```
        12
    11      1
 10            2
 
 9      \|     3
 
 8             4
    7       5
        6
```

Implements a library that can be used to create time objects and perform operations on them.

# Sorted Linked List
```
+---+    +---+    +---+    +---+
| 1 |--->| 2 |--->| 3 |--->| 4 |---> Ø
+---+    +---+    +---+    +---+
```

Implements a library that had a linked list data structure which is always sorted, regardless of operation.

# Circuit Simulator
```

	                --------
	          ----->|  R   |--------
	         |      --------        |
	         | 			|		---
	   ------ 			--------------> |C| ----
	| + |    |			|		---     |
	| B |	 |			|			|	
	  -	 |     --------		|			|
	  ^	 ----->|  R   |----------			|	
  	  |	       --------					|	
 	  -----------------------------------------------------


```
Implements a framework to build and simulate simple DC electric circuit networks. The supported components are Batteries, Resistors, Capacitors and connecting wires.

# Text Editor 
Implements a text editor program that can be used from the command line to perform various operations on a text file.
The program is mainly based on using the standard library algorithms and containers.

Printing the help command results in:
```
Description:
  This program can be used to edit text files through the command-line.

Usage:
  <a.out> <path/to/text_file> [--help] [--print] [--table] [--frequency] [--remove=<word>] [--substitute=<old>+<new>]

Required Arguments:
  <a.out>An executable file.
  <path/to/text_file>Path to a text file.

Optional Arguments:
  --helpPrint this message.
  --printPrint the content of the provided text file.
  --tablePrint the frequency of the words sorted by the words.
  --frequencyPrint the frequency of the words sorted by the frequencies.
  --remove=<word>Remove all occurrences of <word>.
  --substitute=<old>+<new>Substitutes all occurrences of <old> with <new>.
# --
Example Usages:
  ./a.out text_file.txt --print
  ./a.out text_file.txt --remove=word --table
  ./a.out text_file.txt --substitute=word+WORD --frequency
  ```
  
