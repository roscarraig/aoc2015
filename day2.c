#include "aoc.h"

int main(int argc, char *argv[])
{
  FILE        *fp = open_data(argc, argv);
  char         buffer[10240];
  unsigned int part1 = 0, part2 = 0;

  while(!feof(fp) && fgets(buffer, 10240, fp))
  {
    int x, y, z, a, p, la, lp;

    sscanf(buffer, "%dx%dx%d\n", &x, &y, &z);

    a = x * y;
    p = x + y;
    la = a;
    lp = p;
    part1 += 2 * a;
    a = y * z;
    p = y + z;

    part1 += 2 * a;

    if(a < la)
      la = a;

    if(p < lp)
      lp = p;

    a = x * z;
    p = x + z;
    part1 += 2 * a;

    if(a < la)
      la = a;

    if(p < lp)
      lp = p;

    part1 += la;
    part2 += lp * 2 + x * y * z;
  }
  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}
