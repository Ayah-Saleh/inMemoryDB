# inMemoryDB Class Implementation

**How to Run the Code**
1. Setup -- Make sure you have a C++ compatible compiler
2. Download -- Download the code files (inMemoryDB.cpp & inMemoryDB.h) into the same directory
3. Compile -- Navigate to the directory using terminal and run the code
4. Results -- You will see output that shows the results of transactional operations

**Future Modifications** 

In order to turn this assignment into an "official" future assignment, I would continue to clarify instruction because I had to do some 
additional research to figure things out like in order to return a nullptr in the get method I would need to use raw pointers. I also would give more
details on things like error handling/edge cases on the put, commit, and rollback methods. Building on that, I think a good idea would be to include a 
test file with a pre-defined main.cpp/test cases to verify that each of the student-written functions is correct and aligns with expectations. Another
thing is that I think it would be good to use the command line interface in this assignment or have a simple ui to make testing/grading easier.
