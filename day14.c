#include <string.h>
#include "aoc.h"

typedef struct deer_s {
  char name[16];
  int  speed;
  int  runtime;
  int  restime;
  char state;
  int  points;
  int  turn;
  int  dist;
} deer;

int main(int argc, char *argv[])
{
  FILE *fp = open_data(argc, argv);
  char  buffer[1024];
  deer  team[10];
  int   i, j, count = 0, part1 = 0, part2 = 0, front = 0;

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    int cycle, t, distance, remainder;

    sscanf(
      buffer,
      "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
      team[count].name,
      &(team[count].speed),
      &(team[count].runtime),
      &(team[count].restime)
    );
    team[count].state = 1;
    team[count].points = 0;
    team[count].dist = 0;
    team[count].turn = 0;

    cycle = team[count].runtime + team[count].restime;
    t = 2503 / cycle;
    remainder = 2503 % cycle;
    distance = t * team[count].runtime + ((remainder < team[count].runtime) ? remainder : team[count].runtime);
    distance *= team[count].speed;

    if(distance > part1)
      part1 = distance;

    count++;
  }
  printf("Part1: %d\n", part1);

  for(i = 0; i < 2503; i++)
  {
    for(j = 0; j < count; j++)
    {
      team[j].turn++;

      if(team[j].state == 1)
      {
        team[j].dist += team[j].speed;

        if(team[j].dist > front)
          front = team[j].dist;

        
        if(team[j].turn == team[j].runtime)
        {
          team[j].state = 2;
          team[j].turn = 0;
        }
      } else if(team[j].turn == team[j].restime) {
        team[j].state = 1;
        team[j].turn = 0;
      }
    }
    for(j = 0; j < count; j++)
      if(team[j].dist == front)
        team[j].points++;
  }
  for(j = 0; j < count; j++)
    if(team[j].points > part2)
      part2 = team[j].points;

  printf("Part 2: %d\n", part2);
}
