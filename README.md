# Multithreading-MultiProcessing_FileEncryptor-Decryptor

## Overview
This project implements a high-performance file encryption and decryption system using **multithreading and multiprocessing**. It efficiently handles multiple encryption and decryption tasks concurrently, improving performance and resource utilization.

## Features
- **Multithreading**: Uses a thread pool to process encryption and decryption tasks concurrently.
- **Multiprocessing**: Utilizes shared memory and semaphores for inter-process communication.
- **Task Queue**: Implements a queue-based task management system with synchronization.
- **Secure Encryption**: Uses modern cryptographic techniques for file encryption and decryption.
- **Scalability**: Can handle large numbers of tasks efficiently.

## Installation
### Prerequisites
Ensure you have the following installed on your system:
- **GCC/G++** (for compiling C++ code)
- **CMake** (optional, for build management)
- **pthread** (for multithreading support)
- **sys/mman.h, semaphore.h** (for shared memory and semaphores)

### Build and Run
1. Clone the repository:
   ```sh
   git clone https://github.com/Askhat26/Multithreading-MultiProcessing_FileEncryptor-Decryptor.git
   cd Multithreading-MultiProcessing_FileEncryptor-Decryptor
   ```
2. Compile the project:
   ```sh
   g++ -o encryptor_decryptor main.cpp ProcessManagement.cpp -lpthread -lrt
   ```
3. Run the program:
   ```sh
   ./encryptor_decryptor
   ```

## Usage
1. **Submitting an Encryption Task**:
   - The system accepts file encryption tasks and adds them to the task queue.
   - Each task is processed by an available thread.
   
2. **Multithreading Execution**:
   - Worker threads fetch tasks from the queue and execute encryption/decryption in parallel.
   - Synchronization mechanisms prevent race conditions.

3. **Multiprocessing for Task Handling**:
   - Shared memory is used to store and manage tasks.
   - Semaphores ensure smooth synchronization between producer (task submission) and consumer (task execution) processes.

## Code Structure
```
Multithreading-MultiProcessing_FileEncryptor-Decryptor/
├── src/
│   ├── main.cpp                   # Entry point
│   ├── ProcessManagement.cpp       # Task management (threading & multiprocessing)
│   ├── Cryption.cpp                # Encryption & decryption logic
│   ├── ProcessManagement.hpp       # Header file
│   ├── Cryption.hpp                # Header file
├── README.md                       # Project documentation
```

## Contributing
Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to create a pull request or open an issue.

## License
This project is licensed under the **MIT License**. See the `LICENSE` file for details.

## Contact
For any questions or suggestions, reach out to [Askhat26](https://github.com/Askhat26).

