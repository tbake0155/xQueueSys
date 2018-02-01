Author: Timothy Baker
Date: Spring 2018
Class: CS471

Semester Project - xQueueSys

xQueueSys is a gtk windowed application that will allow the user to create a priority queue with other processes (built-in or user specified during run time).

To run GTK, navigate to xQueueSys/bin/ in a terminal and execute the command "./xqueuesys".  xqueuesys can be run from launching the application
directly (clicking the executable) but any child processes launched that require shell interaction will not have a visible shell launched.

(Ideally this would be changed, and could be by launching xterm and feeding xterm the path of the child process.)

If the processes/ and process_tracker/ sub-folders are not in the bin/ directory (parallel to the xqueuesys executable) the program will not work correctly.
xqueuesys requires the helper program process_tracker to function. xqueuesys will behave unexpectedly if the processes/ subfolder is not present.




