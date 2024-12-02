# CS321 - Algorithms Analysis and Design  
### Assignment #2: Hashing, Red-Black Trees, and Skip Lists  

This repository contains the implementation of various hashing techniques, collision resolution methods, and data structures such as Red-Black Trees and Skip Lists. Additionally, the assignment includes solving practical problems using these implementations.

---

## Task 1: Hashing and Collision Resolution Techniques  

Implement the following functions for each of the specified hashing and collision resolution techniques:

### 1. Hashing Techniques  
- **Division Method**  
- **Multiplication Method**  
- **Mid Square Method**  
- **Folding Method**  

### 2. Collision Resolution Techniques  
- **Chaining Method**  
- **Open Addressing Method**  
- **Double Hashing**  

---

## Task 2: Red-Black Tree  

Implement the insertion and deletion operations of a Red-Black Tree using C++. The implementation should maintain the tree's properties according to Red-Black Tree rules.

### Functionalities  
1. Insert nodes while ensuring tree balance and color properties are maintained.  
2. Delete nodes with appropriate restructuring to uphold Red-Black Tree properties.  

---

## Task 3: Skip List  

### a. Skip List Implementation  
Implement a Skip List data structure in C++ that supports the following functionalities:  
1. Insertion of elements while maintaining probabilistic balancing criteria.  
2. Deletion of elements.  
3. Searching for elements efficiently.  

### b. Skip List Problem: Multiplayer Game Score Management  
Use the Skip List implementation to solve the following problem:  

#### Problem Description  
In a multiplayer game, players’ scores need to be tracked dynamically. Players can join and leave the game at any time, and their scores can change frequently. Use the Skip List to manage scores efficiently and implement the following functionalities:  

1. **Dynamic Score Updates**  
   - Update player scores dynamically based on performance.  

2. **Leaderboard Retrieval**  
   - Retrieve the top N players efficiently upon request.  

3. **Player Management**  
   - Add players when they join the game.  
   - Remove players when they leave.  
   - Allow players to view their current score at any time.  
