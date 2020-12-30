#include <string.h>
#include "aoc.h"

typedef struct wire_s {
  char label[3], hv;
  int  op, a, b;
  unsigned short value;
} wire;

int find_wire(wire *wires, char *label)
{
  int i = 1;

  if(label[0] >= '0' && label[0] <= '9')
  {
    sscanf(label, "%d", &i);
    return(-i);
  }
  while(wires[i].label[0])
  {
    if(strcmp(wires[i].label, label) == 0)
      return(i);
    i++;
  }
  strcpy(wires[i].label, label);
  return(i);
}

short int lshift(unsigned short int value, int dist)
{
  return(value << dist);
}

short int rshift(unsigned short int value, int dist)
{
  return(value >> dist);
}

unsigned short int resolve(wire *wires, int t, int d)
{
  int a, b;

  if(t <= 0)
  {
    return(-t);
  }
  if(wires[t].hv)
    return(wires[t].value);
  a = wires[t].a;
  b = wires[t].b;

  switch(wires[t].op)
  {
    case 1:
      wires[t].value = ~resolve(wires, a, d + 1);
      break;
    case 2:
      wires[t].value = lshift(resolve(wires, a, d + 1), b);
      break;
    case 3:
      wires[t].value = resolve(wires, a, d + 1) | resolve(wires, b, d + 1);
      break;
    case 4:
      wires[t].value = resolve(wires, a, d + 1) & resolve(wires, b, d + 1);
      break;
    case 5:
      wires[t].value = resolve(wires, a, d + 1);
      break;
    case 6:
      wires[t].value = rshift(resolve(wires, a, d + 1), b);
      break;
    default:
      printf("This should not happen %d %d %s\n", wires[t].op, t, wires[t].label);
      return(0);
  }
  wires[t].hv = 1;
  return(wires[t].value);
}

int main(int argc, char *argv[])
{
  FILE     *fp = open_data(argc, argv);
  char      buffer[1024];
  wire     *wires = malset(400 * sizeof(wire));
  short     int value = 0;

  while(!feof(fp) && fgets(buffer, 1024, fp))
  {
    char *p;
    char  from[3], to[3];
    int   a, b, t;

    p = index(buffer, '\n');
    *p = 0;

    if(buffer[0] == 'N')
    {
      sscanf(buffer + 4, "%s -> %s", from, to);
      a = find_wire(wires, from);
      t = find_wire(wires, to);
      wires[t].op = 1;
      wires[t].a = a;
    }
    else if(strstr(buffer, "RSHIFT"))
    {
      sscanf(buffer, "%s RSHIFT %d -> %s", from, &b, to);
      a = find_wire(wires, from);
      t = find_wire(wires, to);
      wires[t].op = 6;
      wires[t].a = a;
      wires[t].b = b;
    }
    else if(strstr(buffer, "LSHIFT"))
    {
      sscanf(buffer, "%s LSHIFT %d -> %s", from, &b, to);
      a = find_wire(wires, from);
      t = find_wire(wires, to);
      wires[t].op = 2;
      wires[t].a = a;
      wires[t].b = b;
    }
    else if(strstr(buffer, "OR"))
    {
      char from2[3];

      sscanf(buffer, "%s OR %s -> %s", from, from2, to);
      a = find_wire(wires, from);
      b = find_wire(wires, from2);
      t = find_wire(wires, to);
      wires[t].op = 3;
      wires[t].a = a;
      wires[t].b = b;
    }
    else if(strstr(buffer, "AND"))
    {
      char from2[3];

      sscanf(buffer, "%s AND %s -> %s", from, from2, to);
      a = find_wire(wires, from);
      b = find_wire(wires, from2);
      t = find_wire(wires, to);
      wires[t].op = 4;
      wires[t].a = a;
      wires[t].b = b;
    }
    else if(buffer[0] >= 'a' && buffer[0] <= 'z')
    {
      sscanf(buffer, "%s -> %s", from, to);
      a = find_wire(wires, from);
      t = find_wire(wires, to);
      wires[t].op = 5;
      wires[t].a = a;
    }
    else
    {
      sscanf(buffer, "%d -> %s", &a, to);
      t = find_wire(wires, to);
      wires[t].op = 5;
      wires[t].value = a;
      wires[t].hv = 1;
    }
  }
  printf("Result: %d\n", resolve(wires, find_wire(wires, "a"), 0));
}
