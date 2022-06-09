#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "memlayout.h"
 
int
main(int argc, char *argv[])
{

  int fd = 0;
  void* addr = 0;
  fd = open("test.txt", O_CREATE | O_RDWR);
  for (int i = 0; i <  5; i++) {
    printf(fd, "%d", i);
  }
  write(fd, "\n", 1);


  char* addr1 = 0;

    addr1 = mmap(addr, 5, PROT_READ, MAP_PRIVATE, fd, 0);
    for (int i = 0; i < 5; i++) {
      addr1[i] = addr1[i] +1;
    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap1: %c\n", addr1[i]);
    }

  int pid2 = fork();

  if(pid2 < 0)
      exit();
  else if(pid2 == 0)
  {
    for (int i = 0; i < 5; i++) {
      addr1[i] = addr1[i]+ 1;
    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap2: %c\n", addr1[i]);
    }
    exit();
  }
  else{
      wait();
    }
  int pid3 = fork();
  if(pid3 < 0)
      exit();
  else if(pid3 == 0)
  {
    for (int i = 0; i < 5; i++) {
      addr1[i] = addr1[i]+2;

    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap3: %c\n", addr1[i]);
    }
    exit();
  }
  else {
      wait();
    }

  for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap1: %c\n", addr1[i]);
  }
  close(fd);
  exit();
}