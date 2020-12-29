#include <string.h>
#include "aoc.h"

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[1024];
  int   part1 = 0, part2 = 0;

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    char *p = buffer + 1;

    while(*p && *p != '\n')
    {
      if(*p == '\\')
      {
        p++;
        if(*p == 'x')
          p += 2;
      }
      else if (*p == '"')
        part1++;
      p++;
      part1--;
    }
    part1 += (int) (p - buffer);
  }
  printf("Part 1: %d\n", part1);
  rewind(fp);

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    char *p = buffer;

    while(*p && *p != '\n')
    {
      if(*p == '\\')
        part2++;
      else if (*p == '"')
        part2++;
      p++;
    }
    part2 += 2;
  }
  printf("Part 2: %d\n", part2);
}
