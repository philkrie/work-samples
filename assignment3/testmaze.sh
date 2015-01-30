#!/bin/bash
./maze maze_input.txt > maze_output.txt
diff maze_output.txt output.txt
