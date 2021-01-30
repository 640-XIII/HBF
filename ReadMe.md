<img src = "/misc/Icon.png" alt = "HBF">
<h1><i>HBF - High BrainFuck</i></h1>
<hr>

<h2><b>Contents</b></h2>

> [Short Summary](#short-summary)<br>
> [Input Output](#input-output)<br>
> [HBF Functions](#hbf-functions)<br>
> [HBF Labels](#hbf-labels)<br>
> [Conditional Statements](#conditional-statements)<br>
> [All Available Commands](#all-available-commands)<br>
> [Limitations and other info](#limitations)<br>
> [Contribute](https://github.com/640-XIII/HBF___High_Brain_Fuck/blob/main/CONTRIBUTING.md)<br>
<hr>

## Short Summary

<h4> How memory works in High BrainFuck </h4>

Memory in <b>HBF</b> works in cells, you have 256 cells of memory ( bytes ) which you can change in the #definein the <b><u>start</u></b> of the HBF.c file.

<h4>Change memory cells with the following commands</h4>

><h6>
><ul>
><li>NEX</li>
><li>PRE</li>
><li>PF*</li>
><li>PB*</li>
></ul>
></h6>

You can <b><u>manipulate</u></b> the cell values with varius commands which are the following:

><ul>
><li>AD*</li>
><li>ADP</li>
><li>ADN</li>
><li>AP*</li>
><li>AN*</li>
><li>DEC</li>
><li>INC</li>
><li>DV*</li>
><li>PW*</li>
><li>GET</li>
><li>CPP</li>
><li>CPN</li>
><li>RR*</li>
><li>SU*</li>
><li>MV*</li>
><li>ML*</li>
><li>RFM</li>
><li>MM*</li>
></ul>
[more details here](#all-available-commands)

## Input Output

To get <b><u>input</u></b> from the user the use of the <b>GET</b> command is needed, it will get a <b>single</b> character and saves the value in <b><u>integer</u></b> form ( 0 - 255 ) in the <b>current</b> memory cell.

To <b><u>display</u></b> anything on the screen the <b>DIS</b> is used, it will display the ASCII character <b>depending</b> on the value the memory cell <b>currently</b> holds.
<hr>

## HBF Functions
<b>HBF</b> also support a form of <b><u>functions</u></b>, rules to declare and call using the a function succesfuly:

><ol>
><li>Declare the function previously</li>
><li>End the function with a RET command</li>
><li>You cannot call a function inside a function</li>
><li>Two or more functions cannot share the same name</li>
</ol>

## HBF Labels
<b>HBF</b> also supports <b>labels</b> and to use them the following rules must be applied:

><ol>
><li>Declare the label before you call it</li>
><li>Two or more labels cannot share the same name</li>
</ol>

## Conditional statements
There are two types of conditional statements and are the following:

><ul>
><li>CMT</li>
><li>CMF</li>
</ul>

<b>CMT:</b> Compare True, if the <b><u>current</u></b> memory cell has a value of 1 or more it will <b>NOT</b> skip the next line.

<b>CMF:</b> Compare False, if the <b><u>current</u></b> memory cell has a value of 0 it will <b>NOT</b> skip the next line.

<hr>

## All available commands

><b>AD*</b> - Adds the * to the value of the current memory cell ( value = value + * )<br>
<b>AP*</b> - Adds the memory cell value of current_memory_cell_position - \*<br>
<b>AN*</b> - Adds the memory cell value of current_memory_cell_position + \*<br>
<b>ADP</b> - Adds the previous cell's value to the current cell's value ( value = value + previous_value)<br>
<b>ADN</b> - Adds the next cell's value to the current cell's value ( value = value + next_value)<br>
<b>DIS</b> - Display the value of the current memory cell to ASCII ( 65 value = A )<br>
<b>SS*</b> - Display * amount of characters in memory from the current cell to cell + * value without changing the pointer position<br>
<b>NWL</b> - Outputs a '\n' character<br>
<b>GET</b> - Get user input and save it to the current memory cell as an integer from 0 to 255 ( A = 65 value )<br>
<b>INC</b> - Increases the current cell's value by one ( value = value + 1 )<br>
<b>DEC</b> - Decreases the current cell's value by one ( value = value - 1 )<br>
<b>DV*</b> - Divides the current cell's value by * ( value = value / * )<br>
<b>PW*</b> - Increases the value of the current cell value by * ( value = value ^ * )<br>
<b>NEX</b> - Goes to the next memory cell<br>
<b>PRE</b> - Goes to the previous memory cell<br>
<b>PF*</b> - Goes to current memory cell location + * memory cell location<br>
<b>PB*</b> - Goes to current memory cell location - * memory cell location<br>
<b>LB*</b> - Create a label with the name \*<br>
<b>GO\*</b> - Go to the label with the name \*<br>
<b>CMT</b> - If the value of the cell is 1 or more it will not skip the next line, if the value is 0 it will skip the next line<br>
<b>CMF</b> - If the value of the cell is 0 it will not skip the next line, if the value is 1 or more it will skip the next line<br>
<b>CPP</b> - Copy the value of the previous cell to the current cell ( value = previous_value )<br>
<b>CPN</b> - Copy the value of the next cell to the current cell ( value = next_value )<br>
<b>FN*</b> - Create a function with the name \*<br>
<b>RET</b> - Indicated the end of a function<br>
<b>CL*</b> - Call a function with the name \*<br>
<b>MV*</b> - Move the * ASCII value to the current memory cell ( value = (int)A ) <br>
<b>ML*</b> - Multiplies the current value in memory by the number * given by the user<br>
<b>MM*</b> - Changes all memory cell's values to the value of \*<br>
<b>RFM</b> - Changed all memory cell's values to 0<br>
<b>SU*</b> - Subtracts * from the current value ( value = value - * )<br>
<b>RR*</b> - Saves the current value to the remainder of the division with * ( value = value % *)<br>
<b>END</b> - It indicates the end of the program, it is <b>always</b> needed<br>

<hr>

<h4>How to compile and run HBF scripts from console</h4>
<smaller>> linux</smaller>

```
$ gcc HBF.c -o out
$ ./out input.hbf
```
- [HBF scripts](https://github.com/640-XIII/HBF/tree/main/scripts)

<small>*Note: You can input all file types</small>

<hr>

<h2>Error Codes</h2>
<h6>
<ol>
<li>No input file</li>
<li>Error opening file</li>
<li>Runtime error</li>
<li>Uknown label</li>
<li>Label already exists</li>
<li>Function already exists</li>
<li>Function does not exist</li>
<li>Large command</li>
<li>Error closing input file</li>
</ol>
</h6>
<hr>

## Limitations

<h6>
<ul>
<li>Every command needs to be 3 characters long</li>
<li>Maximum labels possible are 64</li>
<li>Maximum functions possible are 64</li>
<li>Total memory available is 256 bytes</li>
<li>No unicode characters</li>
</ul>
</h6>
<small><i>*You can modify these values from the HBF.c and from headers.h file from version 1.3</i></small>
<br>

<hr>

**<u>WARNINGS</u>**
<br>

<i>*Calling a function or label and **not** having a exit condition will make a never ending while loop</i>

<i>*Overflow or Undeflow is **not** protected and the values any cell can hold range from 0 to 255.</i>