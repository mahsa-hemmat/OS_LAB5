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
  fd = open("temp.txt", O_CREATE | O_RDWR);
  for (int i = 0; i <  5; i++) {
    printf(fd, "%d", i+1);
  }
  write(fd, "\n", 1);


  char* addr1 = 0;
  char* addr2 = 0;
  char* addr3 = 0;

  int pid1 = fork();
  if(pid1 < 0)
      exit();
  else if(pid1 == 0)
  {
    addr1 = mmap(addr, 5, PROT_READ, MAP_PRIVATE, fd, 0);
    for (int i = 0; i < 5; i++) {
      addr1[i] = addr1[i];
    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap1: %c\n", addr1[i]);
    }
    exit();
  }
  else
    wait();

  int pid2 = fork();
  if(pid2 < 0)
      exit();
  else if(pid2 == 0)
  {
    addr2 = mmap(addr, 5, PROT_READ, MAP_PRIVATE, fd, 0);
    for (int i = 0; i < 5; i++) {
      addr2[i] = addr2[i]+ 1;
    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap2: %c\n", addr2[i]);
    }
    exit();
  }
  else
      wait();

  int pid3 = fork();
  if(pid3 < 0)
      exit();
  else if(pid3 == 0)
  {
    addr3 = mmap(addr, 5, PROT_READ, MAP_PRIVATE, fd, 0);
    for (int i = 0; i < 5; i++) {
      addr3[i] = addr3[i]+2;

    }
    for (int i = 0; i < 5; i++) {
      printf(0, "read from mmap3: %c\n", addr3[i]);
    }
    exit();
  }
  else {
      wait();
    }

  close(fd);
  exit();
}