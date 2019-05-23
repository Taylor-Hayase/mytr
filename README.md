# mytr
C program that implements a simple version of tr

To complie run: make

Usage: ./mytr [-d] set1 [set2] [input] [output]

Translation:
  This option requires two sets, the first being what characters will be translated,
  and the second being what the characters will be translated to. Each character in one set corresponds to the character
  in the other set at the same position. Extra characters in the fisrt set will be ignored, and extra characters in the second 
  set will result in repeat translations.
  
Deletion:
  This option is triggered by the additon of the "-d" flag and will only take a single set. Any characters within that set 
  will be deleted from the given input.
  
Escaped Character:
  The following escaped characters are supported as set inputs for this implementation
  \\ - backslash
  \n - newline 
  \t - horizontal tab
 
If no input or output files are given then the program will take stdin and print to stdout.
