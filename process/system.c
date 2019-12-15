#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  char filename[80];
  char str[512];
  char *ptr;
  int fd;
  FILE *fp;

  strcpy(filename, "../tmp_area/lsXXXXXX");
  if((fd = mkstemp(filename)) == -1){
    perror("mkstemp");
    return(-1);
  }
  fprintf(stderr, "*** temp filename = %s\n", filename);
  sprintf(str, "ls -1 > %s", filename);
  if(system(str) == -1){
    perror("system");
    close(fd);
    return(-1);
  }

  if((fp = fdopen(fd, "r")) == NULL){
    perror("fdopen");
    return(-1);
  }

  while(1){
    fgets(str, 512, fp);
    if(feof(fp)){
      break;
    }
    ptr = strchr(str, '\n');
    if(ptr != NULL){
      *ptr = '\0';
    }
    printf("%s\n", str);
  }
  fclose(fp);

  sprintf(str, "rm -f %s", filename);
  system(str);
  return(0);
}
