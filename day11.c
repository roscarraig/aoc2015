#include <stdio.h>
#include <string.h>

int threeup(char *input)
{
  char *p = input + 2;

  while(*p)
  {
    if (*p == *(p - 1) + 1 && *p == *(p - 2) + 2)
      return(1);
    p++;
  }
  return(0);
}

int iol(char *input)
{
  if(index(input, 'i') || index(input, 'o') || index(input, 'l'))
    return(0);
  return(1);
}

int twopair(char *input)
{
  char *p = input + 1, c = 0;

  while(*p)
  {
    if(*p == *(p - 1))
    {
      if(c && *p != c)
        return(1);
      c = *p;
      p++;
    }
    p++;
  }
  return(0);
}

void increment(char *password)
{
  int i = 7;

  while(i >= 0)
  {
    password[i]++;
    if(password[i] == '{')
    {
      password[i] = 'a';
      i--;
    }
    else if(threeup(password) && iol(password) && twopair(password))
      return;
    else
      i = 7;
  }
}

int main(int argc, char *argv[])
{
  char part1[10];

  strcpy(part1, argv[1]);
  increment(part1);
  printf("Part1: %s\n", part1);
}
