#!/bin/bash

# Delete the previous files
make clean
rm RectDetails.csv
# rm *.pdf

# Compile the program
make

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed"
    exit 1
fi

# Run the program and display a progress bar
# -s : Single set of rectangles | -m : Multiple sets of rectangles (to get graph)
# -b : best case | -w : worst case | -a : average case
# -p : make visualisation of rectangles | -n : no visualisation
# -bruteForce : use brute force algorithm | -lineSweep : use sweep line algorithm

./main.exe -c -a -n 50

# Plot the results
# python3 timePlotter.py 1 averageCase.csv Time_Complexity
# python3 plot.py
