#include <string.h>
#include "aoc.h"

int seats(int matrix[9][9], unsigned int seen, int seat, int hap, int maxh, int count)
{
  int i;

  seen |= 1 << seat;

  if(seen + 1 == 1 << count)
  {
    hap += matrix[0][seat] + matrix[seat][0];
    if(hap > maxh)
      return(hap);
    return(maxh);
  }
  for(i = 1; i < count; i++)
    if(seen & (1 << i))
      continue;
    else
    {
      int val = seats(matrix, seen, i, hap + matrix[seat][i] + matrix[i][seat], maxh, count);

      if(val > maxh)
        maxh = val;
    }
  return(maxh);
}

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[102400], *p = buffer;
  int   count = 0;
  int   matrix[9][9], maxh = 0, i;

  memset(matrix, 0, 81 * sizeof(int));

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    char a = buffer[0], b, *p = index(buffer, ' ') + 7;
    int  sign = (*p == 'g' ? 1 : -1), delta;

    if(a == 'M')
      a = 'H';
    a -= 'A';
    p += 5;
    sscanf(p, "%d ", &delta);
    p = index(p, ' ') + 36;
    b = *p;
    if(b == 'M')
      b = 'H';
    b -= 'A';
    matrix[a][b] = sign * delta;
    count++;
  }
  for(i = 0; i < 8; i++)
    maxh += matrix[i][(i + 1) % 8] + matrix[(i + 1) % 8][i];

  for(i = 1; i < 8; i++)
  {
    int hap = seats(matrix, 1, i, matrix[0][i] + matrix[i][0], maxh, 8);

    if(hap > maxh)
      maxh = hap;
  }
  printf("Part 1: %d\n", maxh);
  maxh = 0;
  for(i = 0; i < 9; i++)
    maxh += matrix[i][(i + 1) % 9] + matrix[(i + 1) % 9][i];
  for(i = 1; i < 9; i++)
  {
    int hap = seats(matrix, 1, i, matrix[0][i] + matrix[i][0], maxh, 9);

    if(hap > maxh)
      maxh = hap;
  }
  printf("Part 2: %d\n", maxh);
}
