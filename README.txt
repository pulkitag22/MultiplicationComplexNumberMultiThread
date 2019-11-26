REQUIRED FILES INFORMATION:
	main.c - This is the main file, which consist of all the logic and whis is the file which gets build to object file.
	defiantions.h - this is the header file for main.c. This consist of all the header files required for main.c and all the function declarations and struct complexNumbers defination.
	Makefile - for building the final object file of main.c. This consist of all the dependencies. Type the following commands in the terminal for:
		building - make all
		removing the build files - make clean
	In order to run the program, first type "make all", then, "main" file is created which can be run through "./main"
	input.txt - Consist of one sample valeu. The main.c file is looking for inputs from a file named "input.txt", load your samples in this before executing the program.
		sample format: <Number of inputs> 
			       <real part of 1st input>
			       <imaginary part of 1st input>
			       <real part of 2nd input>
			       <imaginary part of 2nd input>
				...so on...
	
HOW TO COMPILE:
	Type "make all" in the directory where the above 3 files are there. The flow takes care of the dependencies.

HOW TO EXECUTE:
	Type "./main" to execute.

DESCRIPTION OF PROGRAM:
	The written program computes the complex multiplication of 'n' number. The result is computed using parallel execution of multiple threads. For detailed description refer the problem statment in the folder. (Question.pdf)
