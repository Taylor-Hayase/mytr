#include <stdio.h>
#include <string.h>

int arr_trans[255];

int special_map(char x, char y)
{
   if (x == '\\')
   /*Check if given a backslash*/
   {
      /*backslash*/
      if (y == '\\')
      {
         return (int)'\\';
      }
      /*newline*/
      else if (y == 'n')
      {
         return (int)'\n';
      }
      /*tab*/
      else if (y == 't')
      {
         return (int)'\t';
      }
      /*othersie just map to character*/
      else
      {
         return (int)y;
      }
   }
   /*Otherwise given a normal character*/
   return (int)x;
}

void map_translations(char indexes[], char values[], int len_i, int len_v)
{
   /*The index is the character to be replaced,
 *      Value is the replacing character*/
   int i = 0;
   int j = 0;
   int x, y;

   while (i < len_i)
   {
      /*x = index of character to be replaced
 *        i = index of first set*/
      /*Check if a backlash is given with special_map*/ 
      x = special_map(indexes[i], indexes[i + 1]);
      /*is shorter set2*/
      if (j >= len_v - 1)
      {
         /*is backslashed character?*/
         if ((values[len_v - 3] != '\\') && (values[len_v - 2] == '\\'))
         {
            y = special_map(values[len_v - 2], values[len_v - 1]);
         }
         /*or is set2 just shorter?*/
         else
         {
            y = (int)values[len_v - 1];
            /*len_v - 1i or j*/
         }
      }
      /*else set2 and set1 are same*/
      else
      {
         y  = special_map(values[j], values[j + 1]);
      }
      arr_trans[x] = y;
      /*if backslash was given, skip to next since counts as 2 character*/
      if ((x == (int)'\\') || (x == (int)'\n') || (x == '\t'))
      {   
         ++i;
      }

      if ((y == (int)'\\') || (y == (int)'\n') || (y == '\t'))
      {   
         ++j;
      }
      /*continue to next character*/
      ++i;
      ++j;
   }
}

void read_replace()
{
   /*read in the standard input value and replace accordingly*/
   char c;
   int i;    

   while ((c = fgetc(stdin)) != EOF)
   {
      i = (int)c;
      if (arr_trans[i] != 0)
      {
         c = arr_trans[i];
      }
      putchar(c);
   } 
}

void read_delete()
{
   /*read in the standard input value and delete accordingly*/
   char c;
   int i;
   int d = 0;

   while ((c = fgetc(stdin)) != EOF)
   {
      i = (int)c;
      /*see if needs to be deleted*/
      if (arr_trans[i] == 'd')
      {
         d = 1;
      }
      /*if not deleted*/
      if (d == 0)
      {
         putchar(c);
      }
      /*if deleted, don't put it in*/
      else
      {
         d = 0;
      }
   } 
}


int main(int argc, char *argv[])
{
   /*check if minimum input is met*/
   if (argc < 3)
   {
      fprintf(stderr, "Error: Not enough arguments\n");
   }
   /*make sure don't have too many arguments*/ 
   else if (argc > 3)
   {
      fprintf(stderr, "Error: Too many arguments\n");
   } 
   /*chech if is delete command*/
   else if ((argv[1][0] == '-') && (argv[1][1] == 'd'))
   {
      if (argc >= 4)
      {
         fprintf(stderr, "Error: Cannot delete with two sets\n");
      }
      map_translations(argv[2], "d", strlen(argv[2]), 1);
      read_delete();
   }
   /*or if given an invalie dash command*/
   else if ((argv[1][0] == '-') && (argv[1][1] != 'd'))
   {
      fprintf(stderr, "Error: Invalid argument given\n");
   }
   /*otherwise is just a translation*/
   else if (argc == 3)
   {
      /*given right amount of arguments for normal translation*/
      map_translations(argv[1], argv[2], strlen(argv[1]), strlen(argv[2]));
      read_replace();
   } 
   return 0;
}

