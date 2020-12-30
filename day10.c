#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  size_t  l = 4 * strlen(argv[1]);
  char   *input = malloc(l), *output = malloc(l);
  int     i;

  strncpy(input, argv[1], l);
  
  for(i = 0; i < 50; i++)
  {
    char *pi = input, *po = output, c = *input, tmp[8];
    int   cc = 1;

    while(*pi != 0)
    {
      pi++;
      if(cc > 0 && c != *pi)
      {
        sprintf(po, "%d%c", cc, c);
        po += strlen(po);
        cc = 0;
      }
      if(c != *pi)
        c = *pi;
      cc++;
    }
    pi = input;
    input = output;
    output = pi;

    if(2 * strlen(input) > l)
    {
      l = strlen(input) * 4;
      input = realloc(input, l);
      output = realloc(output, l);
    }
  }
  printf("Part 1: %d\n", strlen(input));
}
