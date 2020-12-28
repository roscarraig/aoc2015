#include <string.h>
#include "aoc.h"

int vowel_count(char *input)
{
  char *p = input;
  int   count = 0;

  while(*p && *p != '\n')
  {
    switch(*p)
    {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        count++;
        break;
    }
    p++;
  }
  return(count);
}

int double_letter(char *input)
{
  char *p = input;

  while(*p && *p != '\n')
  {
    if(*p == p[1])
      return(1);
    p++;
  }
  return(0);
}

int double_pair(char *input)
{
  char *p = input;
  char  sub[3];

  sub[2] = 0;

  while(*p && *p != '\n')
  {
    sub[0] = p[0];
    sub[1] = p[1];
    if(strstr(p + 2, sub))
      return(1);
    p++;
  }
  return(0);
}

int trio(char *input)
{
  char *p = input;

  while(*p && *p != '\n')
  {
    if(p[0] == p[2])
      return(1);
    p++;
  }
  return(0);
}

int allowed(char *input)
{
  if(strstr(input, "ab") || strstr(input, "cd") || strstr(input, "pq") || strstr(input, "xy"))
    return(0);
  return(1);
}

int main(int argc, char *argv[])
{
  FILE  *fp = open_data(argc, argv);
  char   buffer[1024];
  int    part1 = 0, part2 = 0;

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    if(vowel_count(buffer) >= 3 && double_letter(buffer) && allowed(buffer))
      part1++;
    if(double_pair(buffer) && trio(buffer))
      part2++;
  }
  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}
