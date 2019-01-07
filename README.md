# File-System
Complete a simple file system like the one in all Operating Systems
There are 6 classes.

FSObject: File system object. The base class of all file system entities. It is an ABC (abstract base class).
File: Inherits from FSObject. It can store some string content.
Directory: Inherits from FSObject. It can contain other files or directories. It is also an ABC.
SADirectory: Inherits from Directory. It is an implementation of Directory that uses a static array.
LLDirectory: Inherits from Directory. It is an implementation of Directory that uses a linked list.
System: It is the file system class. It is on its own and it is a template class. The template type T is either SADirectory or LLDirectory for this assignment. In other words, it can be either a file system of SADirectory or a file system of LLDirectory depending on what template type you provide to it when you create the system.
Your solution to this assignment must be based on the given skeleton code provided in the Download section.

Your task is to complete the following:

FSObject implementation in FSObject.cpp
SADirectory implementation in SADirectory.cpp
LLDirectory implementation in LLDirectory.cpp
System implementation in System.tpp
