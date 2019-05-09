# `STDIN` String Sorter (Vector Implementation)
**Course:** COP4530  
**Instructor:** Duan  
**Project:** Project 1  

# Description
This program uses data entered through the default input to sort/locate the top 10 most used numbers, characters, and words for the given input. If two of these occur the same ammount of times, the one which occurs first will be given priority. Words are defined as (not case sensitive) alphabetical characters seperated by numbers or other non-alphabetical characters. Numbers are treated as strings, meaning 2004 is not equal to 0002004, for example. When two characters happen in the same number of times, the character with a smaller ASCII value should be considered as being used more frequently

# Future Improvements
This program depends on the use of vectors, which are inefficient. To decrease and improve runtime, vectors may be replaced with stl::map instead.

# Included Files
- makefile
- proj1.cpp
- proj1.h
- driver.cpp
- proj1_provided.tar
  - Files provided by the instructor to test the implementation. 

# Usage
## Build
To build the implementation, run `make` within the directory. This build will require the `gpp` compiler. 
## Run
To run the implementation after building, use the executable and a test file. For example `test1 < test0`.

# Academic Honesty & Appropriate Use
This repository branch is available on the personal github of Julian Sweatt for academic and professional purposes. The repository is purposefully obfuscated from search engine indexing/crawling to comply with the [Florida State University Academic Honor Policy](https://fda.fsu.edu/sites/g/files/imported/storage/original/application/0ab8e9de6a98c1377d68de9717988bda.pdf). The content of this repository may be used as a reference of the technical abilities of the developer. The content of this repository may not be used by another student to complete an academic assignment in any way.