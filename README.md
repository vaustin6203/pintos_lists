# pintos_lists
A simple word counter using the Pintos Linked List data structure, a library also used in Linux. I optimized the word counter by adding multi-threads. The synchronization has been fine-grained so that different threads can open and read their respective files concurrently, serializing only their modifications to the shared data structure.
