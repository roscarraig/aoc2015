#include <string.h>
#include "aoc.h"

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[1024], lights[1000][1000];
  unsigned int lights2[1000][1000], part2 = 0;
  int   i, j, part1 = 0;

  memset(lights, 0, 1000000);
  memset(lights2, 0, 1000000 * sizeof(int));

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    int x1, y1, x2, y2, a;

    if(strncmp(buffer, "turn on ", 8) == 0)
    {
      a = 8;
    }
    else if(strncmp(buffer, "turn off ", 9) == 0)
    {
      a = 9;
    }
    else if(strncmp(buffer, "toggle ", 7) == 0)
    {
      a = 7;
    }
    sscanf(buffer + a, "%d,%d through %d,%d", &x1, &y1, &x2, &y2);

    for(j = y1; j <= y2; j++)
      for(i = x1; i <= x2; i++)
        switch(a)
        {
          case 7:
            lights[i][j] = 1 - lights[i][j];
            lights2[i][j] += 2;
            break;

          case 8:
            lights[i][j] = 1;
            lights2[i][j]++;
            break;

          case 9:
            lights[i][j] = 0;
            if(lights2[i][j] > 0)
              lights2[i][j]--;
            break;
        }
  }
  for(j = 0; j < 1000; j++)
    for(i = 0; i < 1000; i++)
    {
      part1 += lights[i][j];
      part2 += lights2[i][j];
    }
  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}
