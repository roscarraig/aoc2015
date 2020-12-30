#include <string.h>
#include "aoc.h"

int find_place(char places[7][16], char *place)
{
  int i = 0;
  while(places[i][0] != 0 && strcmp(places[i], place))
    i++;
  strcpy(places[i], place);
  return(i);
}

typedef struct hop_s {
  int p1;
  int p2;
  int dist;
} hop;

int find_hop(int from, int to, hop *hops, int count)
{
  int i;

  for(i = 0; i < count; i++)
    if((hops[i].p1 == from && hops[i].p2 == to) || (hops[i].p2 == from && hops[i].p1 == to))
      return(hops[i].dist);

  printf("This should not happen\n");
  return(-1);
}

int route(unsigned int been, int current, int hopcount, int nodecount, int mind, hop *hops, int dist)
{
  int i, result;

  been |= 1 << current;

  if (been + 1 == (1 << nodecount))
    return(dist < mind ? dist : mind);

  if(dist > mind)
    return(mind);

  for(i = 0; i < nodecount; i++)
  {
    if(been & (1 << i))
      continue;
    result = route(been, i, hopcount, nodecount, mind, hops, find_hop(current, i, hops, hopcount) + dist);
    if(result < mind)
      mind = result;
  }
  return(mind);
}

int route2(unsigned int been, int current, int hopcount, int nodecount, int maxd, hop *hops, int dist)
{
  int i, result;

  been |= 1 << current;

  if (been + 1 == (1 << nodecount))
    return(dist > maxd ? dist : maxd);

  for(i = 0; i < nodecount; i++)
  {
    if(been & (1 << i))
      continue;
    result = route2(been, i, hopcount, nodecount, maxd, hops, find_hop(current, i, hops, hopcount) + dist);
    if(result > maxd)
      maxd = result;
  }
  return(maxd);
}

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[1024];
  char  places[16][16];
  hop   hops[30];
  int   i = 0;
  int   part1 = 0, part2, hopcount = 0, nodecount;

  memset(places, 0, 256);
  memset(hops, 0, 30 * sizeof(hop));

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    char place1[16], place2[16];
    int  dist;

    sscanf(buffer, "%s to %s = %d\n", place1, place2, &dist);
    hops[hopcount].p1 = find_place(places, place1);
    hops[hopcount].p2 = find_place(places, place2);
    hops[hopcount++].dist = dist;
  }
  for(i = 1; places[i][0] != 0; i++)
    part1 += find_hop(i - 1, i, hops, hopcount);

  nodecount = i;
  part2 = part1;

  for(i = 0; places[i][0] != 0; i++)
    part1 = route(0, i, hopcount, nodecount, part1, hops, 0);

  printf("Part 1: %d\n", part1);

  for(i = 0; places[i][0] != 0; i++)
    part2 = route2(0, i, hopcount, nodecount, part2, hops, 0);

  printf("Part 2: %d\n", part2);
}
