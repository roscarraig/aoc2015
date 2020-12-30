#include <string.h>
#include "aoc.h"

char *parse(char *blob, int *rval)
{
  char *p = blob;
  int   notred = 1, tv = 0, sign = 1;

  while(*p && *p != '\n')
  {
    if(*p == '{')
    {
      int subv = 0;

      p = parse(p + 1, &subv);
      *rval += subv * notred;
    }
    else if(strncmp(p, ":\"red\"", 6) == 0)
    {
      notred = 0;
      *rval = 0;
      p += 6;
    }
    else if(*p == '}')
    {
      if(tv > 0)
        *rval += sign * tv * notred;
      return(p + 1);
    }
    else if(*p >= '0' && *p <= '9')
    {
      if(tv == 0 && *(p - 1) == '-')
        sign = -1;
      tv = 10 * tv + (*p - '0');
      p++;
    }
    else if(tv > 0)
    {
      *rval += sign * tv * notred;
      sign = 1;
      tv = 0;
      p++;
    }
    else
      p++;
  }
  return(0);
}

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[102400], *p = buffer;
  int   part1 = 0, part2 = 0, tv = 0, sign = 1;

  fgets(buffer, 102400, fp);
  while(*p && *p != '\n')
  {
    if(*p >= '0' && *p <= '9')
    {
      if(tv == 0 && *(p - 1) == '-')
        sign = -1;
      tv = 10 * tv + (*p - '0');
    }
    else if(tv > 0)
    {
      part1 += sign * tv;
      sign = 1;
      tv = 0;
    }
    p++;
  }
  parse(buffer, &part2);
  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}
