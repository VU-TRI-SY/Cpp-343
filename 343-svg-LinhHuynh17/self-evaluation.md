# Self-Evaluation

## Name(s): 

Out of 20 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes/No

- If the program does not compile or gives a segmentation error when compiled, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: -1 for each compilation warning, min -3: 1

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 1

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 1

- Check under *4. clang-format does not find any formatting issues*

Q: Runs and produces correct output: 1

- N/A for this assignment, enter 0 if proper SVG file is produced

Q: -2 for any detected memory leak: ENTER_NUMBER

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: ENTER_NUMBER

- -1 for each large block of code not executed
- -2 for each function that is never called
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are there at least 2 new SVG subclasses: ENTER_NUMBER

- -10 if no other SVG subclass is implemented
- -5 if no only 1 other SVG subclass is implemented

Q: Are all functions in .h and .cpp file documents (min -3): ENTER_NUMBER

- -1 for each function not documented

Q: Is there an attempt to create an interesting abstract artwork: ENTER_NUMBER

- -1 No attempt at creativity
- +1 The output is worthy of displaying in a gallery and will not look out of place next to some from https://www.google.com/search?q=geometric+abstract+art&tbm=isch

Q: Additional abstract artwork as svg and png: ENTER_NUMBER

- +1 5 interesting output files named svg1.svg, svg2.svg, ... with corresponding png files

Q: Total points: ENTER_NUMBER