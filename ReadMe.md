<i>HBF - High Brain Fuck</i>
============================

![GitHub release (latest by date)](https://img.shields.io/github/v/release/640-XIII/High-Brain-Fuck?color=f&label=Version) ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/640-XIII/High-Brain-Fuck)

<b>HBF</b> is a side project created when I was bored during my first semester of university and as a way to understand pointers / file at a basic level. Now it became a <a href = "https://en.wikipedia.org/wiki/Esoteric_programming_language" target = "_blank">esoteric</a> programming language I actually use to kill some time.

<hr>

# Memory

<b>HBF</b> has two types of memory called <u><b>main memory</b></u> and <u><b>extended memory</b></u> respectively, the main difference between the two is that <u><b>main memory</b></u> has a value range from 0 to 255 while <u><b>extended memory</b></u> has a range from 0 to 65535.

<h6><i>*Note: Both memory types are dynamically allocated.</i></h6>

<br>

To traverse the <u><b>main memory</b></u> you can use following commands:

><h6>
><ul>
><li>NEX - Go to the next memory cell</li>
><li>PRE - Go to the previous memory cell</li>
><li>PF* - Go forward * memory cells</li>
><li>PB* - Go backwards * memory cells</li>
></ul>

You can modify the value in the current cell inside the <u><b>main memory</b></u> using the following commands:

><h6>
><ul>
><li>AD* - Add the value of * to the current memory cell</li>
><li>SU* - Subtract the current memory cell value by the value of *</li>
><li>ADP - Add the previous cell value to the current memory cell</li>
><li>ADN - Add the next cell value to the current memory cell</li>
><li>AP* - Add the value of the cell * cells ago</li>
><li>AN* - Add the value of the cell * cell forward</li>
><li>DEC - Decrease the value of the current memory cell by one</li>
><li>INC - Increase the value of the current memory cell by one</li>
><li>DV* - Divide the current memory cell value with the value of * and save the result</li>
><li>PW* - Raise the current memory cell value to the power of * and save the result</li>
><li>CPP - Copy the value of the previous memory cell and save the value to the current memory cell</li>
><li>CPN - Copy the value of the next memory cell and save the value to the current memory cell</li>
><li>RR* - Save the remainder to the current memory cell</li>
><li>SHR - Bitwise logical shift operation (right)</li>
><li>SHL - Bitwise logical shift operation (left)</li>
><li>MV* - Save the value of * to the current memory cell</li>
><li>ML* - Multiply the current value with the value of * and save the result</li>
><li>MM* - Save the value of * to all memory cells</li>
></ul>

<br>

To travarse the <u><b>extended memory</b></u> you can use the following commands:

><h6>
><ul>
><li>EMN - Go to the next memory cell</li>
><li>EMP - Go to the previous memory cell</li>
></ul>

<br>

To modify the values inside of <u><b>extended memory</b></u> you can use the following commands:

><h6>
><ul>
><li>EMI - Increase the current cell value by one</li>
><li>EMD - Decrease the current cell valye by one</li>
><li>EMN - Multiply the current cell value with the value of the next cell</li>
><li>EMP - Multiply the current cell value with the value of the previous cell</li>
><li>ESN - Decrease the current cell value by the value of the next cell</li>
><li>ESP - Decrease the current cell value by the value of the previous cell</li>
><li>EAN - Increase the current cell value by the value of the next cell</li>
><li>EAP - Increase the current cell value by the value of the previous cell</li>
><li>EP* - Raise the current value to the power of * and save the result</li>
><li>EM* - Multiply the current value with the number * and save the result</li>
><li>ES* - Subtract * from the current value</li>
><li>EA* - Add * to the current value</li>
></ul>

<hr>

# Input / Output

You can get input and save the results into <u><b>main memory</b></u> using the <b>GET</b> and <b>DIS</b> commands. 

To get input from the user and save it into extended memory or show the contents of extended memory you can use the <b>EMG</b> and <b>EMS</b> commands.

<hr>

# Functions

<b>HBF</b> supports functions with the following restrictions:

><ol>
><li>The function name must be unique</li>
><li>The function must end with a <b>RET</b> command</li>
><li>You cannot call a function inside a function</li>
></ol>

<hr>

# Labels

<b>HBF</b> also supports labels with the following restriction:

><ol>
><li>The label name must be unique</li>
></ol>

<hr>

# Conditional statements

Conditional statements use the <u><b>main memory</b></u> for decision making and there are two available commands, <b>CMT</b> and <b>CMF</b>.

<hr>

# END command

Unlike the previous versions the END command is not required but it can still be used to exit the program.

# Comments

Comments are allowed, everything after the <b>third character</b> won't be saved in memory so you can use that space for comments.