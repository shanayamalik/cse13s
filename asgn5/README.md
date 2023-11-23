### README for Programming Assignment 5

#### Overview
This project includes the implementation of three Abstract Data Types (ADTs): Set, Hash Table, and Least Recently Used (LRU) Cache. Each part of the assignment builds upon the previous one, starting with a simple Set ADT, advancing to a more complex Hash Table, and culminating in the implementation of an LRU Cache. The ADTs are implemented in C, and testing files are provided to ensure correct functionality.

#### Part A: Set ADT
- **Files**: `set.c`, `set.h`
- **Description**: Implements a set of `(char*, void*)` pairs as a simplified linked list.
- **Compilation**: `gcc -Wall -Wextra set.c test_set.c -o test_set`
- **Testing**: Run `./test_set` to test the implementation.

#### Part B: Hash Table ADT
- **Files**: `hashtable.c`, `hashtable.h`, along with the files from Part A.
- **Description**: Implements a hash table using the Set ADT. The hash table manages `(char*, void*)` pairs and is more efficient for large collections.
- **Compilation**: `gcc -Wall -Wextra set.c hashtable.c test_hashtable.c -o test_hashtable`
- **Testing**: Run `./test_hashtable` to test the implementation.

#### Part C: LRU Cache
- **Files**: `lru.c`, `lru.h`, along with files from Parts A and B.
- **Description**: Implements an LRU Cache ADT with functions like `LRU_insert()`, `LRU_find()`, `LRU_print()`, and `LRU_iterate()`. This ADT uses a combination of the Set and Hash Table ADTs.
- **Compilation**: `gcc -Wall -Wextra lru.c hashtable.c set.c test_LRU.c -o test_lru`
- **Testing**: Run `./test_lru` to test the implementation.

#### Submission Guidelines
- Push all changes to GitLab repository. Exclude `.o` and `.txt` files from the submission.
- The final commit ID should be noted in the submission on Canvas.
