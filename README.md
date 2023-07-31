# XV6_InterprocessCommunication

**Xv6 Process Communication Enhancement**

Xv6 has been modified to support communication between processes using shared memory, where only one parent-child relationship is allowed. Three processes have been created: primestart as the parent process, and primecom and primecalc as child processes. The primestart process sets up shared memory structures and reports them to the operating system. Primecom receives commands from the user and pushes the command ID into shared memory, while primecalc computes prime numbers and writes them to shared memory. Primecalc also reads and executes commands sent by primecom.

To enable memory sharing, a new structure named "shared" was created to contain metadata about the shared memory regions. Additionally, two attributes were added to the "proc" structure: a pointer to the parent page directory and an array of shared structures.

**System Changes for Process Communication Functionality:**

1. **fork() Modification:** When the fork system call is invoked, the new child process inherits all common structures from its parent, including shared memory. However, the child cannot yet communicate with its parent at this point.

2. **exec() Modification:** Regular process size is limited to a maximum of 1 GB. From 1 GB up to 2 GB, physical addresses of the shared memory inherited from the parent are allocated. This enables communication between the child and parent, as the physical addresses of the parent's shared memory are mapped into the child's virtual memory from 1 GB up to 2 GB.

**Additional Changes to the xv6 OS:**

1. **System Call: share_mem(char *name, void *addr, int size):** This system call is used by the parent process to report memory that needs to be shared. The name parameter represents a unique name for the shared memory, addr is the address of the shared memory, and size indicates the size of the shared memory. The function returns a value indicating the success of the sharing process or any errors encountered.

2. **System Call: get_shared(char *name, void **addr):** This system call is used by child processes to access a common structure. The name parameter specifies the name of the shared structure the child process wants to access. The addr parameter is a pointer (passed by reference) that points to the shared memory after the system call is executed. The function returns a value indicating the success of the access or any errors encountered.

**Three User Programs:**

1. **primestart:** This program prepares structures to be passed on to its children, including an empty array of 400000 bytes (of type int), a counter for the position in the array (of type int), and a command indicator (of type int).

2. **primecom:** This program receives commands from the user, which include printing the nth prime number, printing the latest calculated prime number, pausing and resuming the calculation of prime numbers, and ending the process.

3. **primecalc:** This program calculates prime numbers. When a prime number is found, it writes the number to the common array and increments the position counter of the array. It also checks if any commands have been sent by the program primecom.

To start the program, follow these steps:

1. Open the terminal in the project's directory.
2. Run 'make clean' to clean the project.
3. Run 'make qemu' to start the xv6 operating system, which should be displayed in the QEMU window. 

Note: The communication between processes is now enabled using shared memory in xv6, allowing parent-child relationships and facilitating process communication.
