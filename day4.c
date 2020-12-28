#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

int check_hash(char *key, int n)
{
  unsigned char buffer[128], result[MD5_DIGEST_LENGTH];

  sprintf(buffer, "%s%d", key, n);
  MD5(buffer, strlen(buffer), result);

  if(result[0] || result[1] || result[2] > 15)
    return(0);
  if(result[2] == 0)
    return(2);
  return(1);
}

int main(int argc, char *argv[])
{
  int part1 = 0, part2;

  while(!check_hash(argv[1], part1))
    part1++;

  printf("Part 1: %d\n", part1);
  part2 = part1;

  while(check_hash(argv[1], part2) != 2)
    part2++;

  printf("Part 2: %d\n", part2);
}
