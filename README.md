# uniformityChecker

<h3> Project Description </h3>
Uniformity Checker for boolean formulas. Uniformity is defined as: 
   A boolean formula is uniform if and only if the output values of 0 and 1 occur evenly that is the output
   has 2^n/2 0s and 2^n/2 1s.

The project has two parts:

   <b>scriptParser:</b>
        Script parser is used to parse SyGus scripts and their outputs and extract the logical formulas embeded inside the script
        and its corresponding output. The program when run will write the resulting formula to an outpu file of "formula1.txt".
    
   <b>uniformityChecker:</b>
        UniformityChecker is used to check if the resulting formula is uniform in terms of its output. The program parses the given 
        formula, turns it into a synthax-tree and checks for uniformity while printing all possible outputs. 
        
 <h3> Requirements </h3>
 //TO BE DONE LATER 
 
 <h3> Understanding the Output </h3>
 <b>scriptParser:</b>
   The scriptParser will simply output the extracted formula. For example, for a simple input of:
   
       (define-fun Tree ((i0 Bool) (i1 Bool) (i2 Bool) (i3 Bool)) Bool
         (xor (or (not i1) (xor i3 i2)) (xor (not i0) (and i3 i0))))
         
   The parser will output: 
   
        (xor (or (not i1) (xor i3 i2)) (xor (not i0) (and i3 i0)))
        
   
 <b>uniformityChecker:</b>
 
   uniformityChecker will first printing the synthax tree as it creates it. The printing will be done in the same order as you see 
   in the formula. For the output given above, you can expect the following result:
   
        Creating Tree
        Value is xor
        Value is or
        Value is not
        Value is i1
        Value is xor
        Value is i3
        Value is i2
        Value is xor
        Value is not
        Value is i0
        Value is and
        Value is i3
        Value is i0
        
 Second, the program will try all possible combinations of values for the given input variables and calculate the result and 
 print each possible input combination with its corresponding output. Thus, the output of
    
         For Input: 1010
         Result is: 1
 implies that for input values of i0 = 1, i1= 0, i2= 1, i3= 0, the given formula evaluates to 1.
   
   
<b> printTree() function: </b>
  The implemented tree class also includes a printTree() class function, that basically prints out the tree, starting from the ROOT,
  to STDOUT. This function uses a depth first approach and pre-order traversal meaning that it will follow the order of
  ROOT-> Left Child -> Right Child and thus everything to the right will be printed before everything on the right. Given the same 
  example, we can expect the output of:
  
        xor
        PRINT LEFT
        or
        PRINT LEFT
        not
        PRINT LEFT
        i1
        PRINT RIGHT
        xor
        PRINT LEFT
        i3
        PRINT RIGHT
        i2
        PRINT RIGHT
        xor
        PRINT LEFT
        not
        PRINT LEFT
        i0
        PRINT RIGHT
        and
        PRINT LEFT
        i3
        PRINT RIGHT
        i0
   
   <h3> How to Compile </h3>
   In order to compile the programs simply execute
   
      make
      
   <h3> How to Run </h3>
   
   <b>scriptParser:</b>
   You can run the script parser using
       ./make <file>
   The program requires an input of file path. This file should either be the SyGus script or should contain the output of the
   SyGus script
      
   <b>uniformityChecker:</b>
   You can run the uniformityChecker using
   
      ./tree <file>
    
 The file represents the file containing an extracted formula. Please see limitations for further information on input file. If not 
 provided, the input will default to formula1.txt which will be outputted by scriptParser
    
    <b> Putting it All Together </b>
 If you would like to run them all, you can just execute
    
        ./run
        
 this bash script will compile both programs and run them in order for you and then execute 
    
      make clean
      
 to clear all binary files generated.
      
   <h3> How to Run Tests </h3>
   //Coming Soon
   <h3> How to Read </h3>
   
 No specific order is any important than another for reading purposes
   
   <h3> Limitations </h3>
   
   The formula that will be inputted to the uniformity checker has to follow to following rules:
   
   <ul>
    <li> The input variables have to be represented by a lower case letter followed by a digit to distinguish the variable. 
    As in the form of [a-z][0-9]. The variables does not necessary need to be zero indexed or consequtive. For example:
    
        i0
  </li>
    
  <li>
    The input formula should not include letters followed by multiple digits or in other words numbers less than 0 or greater than 9
    [0<= x <=9]. If you need to have more than 9 variables, please distinguish them using different letter names such as:
      
          i0, r0, r1, i2, r2
       
 will all evaluate to different variables. 
 </li>
   
<h3> File Legend </h3>

MakeFile: makefile to compile programs and clear binary files

run: Bashscript to automately compile and run everything in order

scriptparser.cpp: Scriptparser implementation

tree.cpp: Functionality of the tree class, including the uniformityChecker

tree.h: Header File for the tree class

formula1.txt: Test formula, output file for scriptParser

formula2.txt: Test formula

AND2_TI.sl: Test SygusScript (Provided by Pei Luo)

exampleinput: Test SygusScriptOutput 

lexical: NFA based implementation for Tree class (Provided by Pei Luo)
