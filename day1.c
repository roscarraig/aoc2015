#include <string.h>
#include "aoc.h"


int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[10240];
  int   part1 = 0, part2 = 0;

  while(!feof(fp) && fgets(buffer, 10240, fp))
  {
    char *p = buffer;

    printf("Line\n");
    while(*p && *p != '\n')
    {
      if(*p == '(')
        part1++;
      else if(*p == ')')
        part1--;
      if(part1 == -1 && part2 == 0)
        part2 = 1 + (int) (p - buffer);
      p++;
    }
  }
  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}
