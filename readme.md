# Banker's Algorithm.


## Usage
Compile on a Linux/UNIX machine using g++:
- ``g++ banker.cpp -o banker``

Run the program using ``./banker``

Ensure the ``input.txt`` file exists in the current directory the program is being ran from.

## Explanation of Banker's Algorithm and Implementation
Banker's algorithm is used to determine the best route of action for running processes to ensure there are enough resources to satisfy each process. This ensures the system is in a safe state, and deadlock can not occur.

## Expected ouptut
Expected output given the default ``input.txt`` file provided in the repo:
![alt text](image.png)

Expected output given an ``input.txt`` file that represents a table of a system not in a safe state:
![alt text](image-1.png)

