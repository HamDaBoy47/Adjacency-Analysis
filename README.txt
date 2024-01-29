Please ensure all necessary compilers and extensions are installed:
- g++
- pandas
- matplotlib

Before compiling:
1. Generate complexity graph only(multiple input rectangle arrays appraoch)
	- run.sh (LINE 23):
		LINESWEEP:
		Argument 1: NEEDS TO BE "-m"
		Arguemnt 2: NEEDS TO BE "-b", "-a" or "-w" for best, average or worst case respectively
    	Argument 3: NEEDS TO BE "-n" 
		Argument 4: NEEDS TO BE the MAX NUMBER of rectangles to be generated [1000-300000]
		Argument 5: NEEDS TO BE "-lineSweep"
		- Example: ./main.exe -m -a -n 100000 -lineSweep

		- Uncomment "python3 timePlotter.py 1 averageCase.csv Time_Complexity"
		- CHANGE "averageCase.csv" to the generated csv file name
		- CHANGE "Time_Complexity" to the desired graph title

		BRUTEFORCE:
		Argument 1: NEEDS TO BE "-m"
		Arguemnt 2: NEEDS TO BE "-r"
    	Argument 3: NEEDS TO BE "-n" 
		Argument 4: NEEDS TO BE the MAX NUMBER of rectangles to be generated [1000-300000]
		Argument 5: NEEDS TO BE "-bruteForce"
		- Example: ./main.exe -m -r -n 100000 -bruteForce

		- Uncomment "python3 timePlotter.py 1 averageCase.csv Time_Complexity"
		- CHANGE "averageCase.csv" to "bruteForce.csv"
		- CHANGE "Time_Complexity" to the desired graph title

	- Open terminal in folder directory
	- run command "./run.sh" - cleans existing files and generates new ones

2. Generate single size array of rectangles, with text output and visualisation of rectangles:
	- run.sh (LINE 23):
		Argument 1: NEEDS TO BE "-s"
		Arguemnt 2: NEEDS TO BE "-b", "-a" or "-w" for best, average or worst case respectively or "-r" when using brute force
    	Argument 3: NEEDS TO BE "-p" 
		Argument 4: NEEDS TO BE the MAX NUMBER of rectangles to be generated [50-1000] Recommended
		Argument 5: NEEDS TO BE "-lineSweep" or "-bruteForce" ENSURE CORRECT ARGUMENT 2
		- Example: ./main.exe -s -a -p 50 -lineSweep

		- Uncomment "python3 plot.py"

3. LineSweep validation:
	- run.sh (LINE 23):
		Argument 1: NEEDS TO BE "-c"
		Arguemnt 2: NEEDS TO BE "-b", "-a" or "-w" for best, average or worst case respectively
    	Argument 3: NEEDS TO BE "-n" for no Rectangle.csv or "-p" for Rectangle.csv generation(To visualise rectangles)
		Argument 4: NEEDS TO BE the MAX NUMBER of rectangles to be generated [50-1000] Recommended
		- Example: ./main.exe -c -a -n 50

		- Uncomment "python3 plot.py" if "-p" is used for ARGUMENT 3

