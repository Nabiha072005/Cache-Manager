# Cache Manager

A cache management system developed in **C++**, integrating custom-built data structures with a **MySQL relational database** to manage and retrieve customer records.

The project combines a Binary Search Tree (BST), Hash Table, and Doubly Linked List to support key-based lookups, FIFO cache eviction, sorted traversal, and range queries.

## Technologies Used

- **Language:** C++
- **Database:** MySQL
- **Database Connectivity:** MySQL Connector/C++
- **Data Structures:** Binary Search Tree, Hash Table, Doubly Linked List
- **Data Format:** JSON
- **Libraries:** nlohmann/json

## Features

### 1. Custom Data Structures

Implemented three data structures from provided interface specifications:

**Hash Table**
- Uses modulo hashing to calculate bucket indices.
- Implements separate chaining with doubly linked nodes to resolve collisions.
- Supports insertion, deletion, and key-based lookup.
- Provides O(1) average-case lookup under a well-distributed hash function and bounded load factor, with O(n) worst-case lookup.

**Doubly Linked List**
- Maintains customer records in insertion order.
- Supports insertion at the head and removal of the oldest record from the tail.
- Enables First-In, First-Out (FIFO) cache management.

**Binary Search Tree**
- Maintains customer records organized by key.
- Supports insertion, deletion, and tree traversals.
- Provides ascending and descending sorted output.
- Supports range queries within specified key boundaries.

### 2. Cache Management

The `CacheManager` class coordinates all three data structures to maintain a bounded cache.

When a customer record is added:

1. The record is inserted into the doubly linked list.
2. A corresponding entry is added to the hash table for key-based retrieval.
3. The record is inserted into the binary search tree for ordered operations.
4. If the cache is full, the oldest entry is evicted using the FIFO policy.

Record deletion and cache clearing operations update all three structures.

### 3. MySQL Database Integration

Integrated MySQL Connector/C++ to retrieve customer membership information from a relational database.

The `customers` table contains the following fields:

| Column | Description |
|---|---|
| `key` | Customer identifier |
| `statusLevel` | Customer membership status |
| `fullName` | Customer name |
| `address` | Street address |
| `city` | City |
| `state` | State |
| `zip` | ZIP code |

The application uses parameterized SQL queries to retrieve a customer's membership status by key.

```sql
SELECT statusLevel
FROM customers
WHERE `key` = ?;
```

The retrieved status is incorporated into the customer record before insertion into the cache.

### 4. JSON-Based Configuration and Testing

The application reads JSON configuration files to determine:

- Input and output file paths
- Hash table bucket count
- Maximum FIFO cache capacity
- Database schema and customer table

It also processes provided JSON test cases to exercise cache operations, including insertion, deletion, lookup, tree traversal, sorting, and range queries.

Results are written to both the console and an output file.

## Architecture

The Cache Manager coordinates three complementary data structures:

```text
                 CacheManager
                      |
          +-----------+-----------+
          |           |           |
      Hash Table  Doubly Linked  Binary Search
                      List           Tree
          |           |           |
      Key-based   FIFO Cache     Sorting and
       Lookup      Eviction      Range Queries
```

MySQL supplies customer membership information, which is incorporated into records before they are inserted into the cache.

## Time Complexity

| Operation | Expected complexity |
|---|---|
| Hash table lookup | O(1) average, O(n) worst |
| Hash table insertion | O(1) for bucket-head insertion |
| Hash table deletion | O(1) average, O(n) worst |
| BST search | O(log n) average, O(n) worst |
| BST insertion | O(log n) average, O(n) worst |
| BST deletion | O(log n) average, O(n) worst |
| FIFO tail removal | O(1) for linked-list removal |
| BST sorted traversal | O(n) |

These complexities describe the individual data structure operations. Full cache operations may involve multiple structures, and the BST is not self-balancing.

## Running the Project

### Prerequisites

- C++ compiler compatible with the project
- MySQL Server
- MySQL Connector/C++
- nlohmann/json library

### Setup

1. Clone the repository.

```bash
git clone https://github.com/YOUR-USERNAME/Cache-Manager.git
cd Cache-Manager
```

2. Create the MySQL database and customer table using the project's SQL setup script.

3. Configure the application with the correct database connection settings. Do not commit database passwords or other credentials.

4. Update the JSON configuration file with the appropriate database schema, table name, file paths, and cache settings.

5. Build the project in a C++ development environment with MySQL Connector/C++ and the JSON library configured.

6. Run the executable to process the configured JSON test cases and generate the output log.

*Build commands may vary depending on the compiler, operating system, and installed connector version.*

## Project Background

Developed as part of a computer science coursework project focused on data structures, algorithms, and database integration.

The project interfaces and test cases were provided as part of the coursework. I independently implemented the Binary Search Tree, Hash Table, Doubly Linked List, Cache Manager coordination logic, and MySQL database integration.

## Author

**Nabiha Khalid Sheikh**
