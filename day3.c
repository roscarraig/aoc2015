#include <string.h>
#include "aoc.h"

typedef struct house_s {
  int boxes;
  int x;
  int y;
} house;

int find_house(house *houses, int x, int y)
{
  int i = 0;

  while(houses[i].boxes > 0)
  {
    if(houses[i].x == x && houses[i].y == y)
    {
      houses[i].boxes++;
      return(i);
    }
    i++;
  }
  houses[i].x = x;
  houses[i].y = y;
  houses[i].boxes = 1;
  return(i);
}

int main(int argc, char *argv[])
{
  FILE  *fp = open_data(argc, argv);
  char   buffer[10240], *p = buffer;
  house *houses = malset(10000 * sizeof(house));
  int    i, t = 0, part1 = 0, part2 = 0, x = 0, y = 0, x2[2], y2[2];

  find_house(houses, 0, 0);
  fgets(buffer, 10240, fp);
  while(*p && *p != '\n')
  {
    switch(*p)
    {
      case('>'):
        x++;
        break;
      case('<'):
        x--;
        break;
      case('^'):
        y++;
        break;
      case('v'):
        y--;
        break;
    }
    p++;
    i = find_house(houses, x, y);
    if(i > part1)
      part1 = i;
  }
  part1++;
  printf("Part 1: %d\n", part1);

  p = buffer;
  memset(houses, 0, 10000 * sizeof(house));
  memset(x2, 0, 2 * sizeof(int));
  memset(y2, 0, 2 * sizeof(int));

  while(*p && *p != '\n')
  {
    switch(*p)
    {
      case('>'):
        x2[t]++;
        break;
      case('<'):
        x2[t]--;
        break;
      case('^'):
        y2[t]++;
        break;
      case('v'):
        y2[t]--;
        break;
    }
    p++;
    i = find_house(houses, x2[t], y2[t]);
    if(i > part2)
      part2 = i;
    t = 1 - t;
  }
  part2++;
  printf("Part 2: %d\n", part2);
}
