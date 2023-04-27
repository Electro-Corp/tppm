#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int r, g, b;
} color;
void usage();
int main(int args, char *argv[]) {
  int height = 0;
  int width = 0;
  printf("Terminal PPM Viewer - Electro_Corp\n");
  if (!argv[1])
    usage();
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("File %s not found!\n", argv[1]);
    exit(1);
  }
  fseek(fp, 0L, SEEK_END);
  char buffer[ftell(fp)];
  rewind(fp);
  fread(buffer, sizeof(buffer), 1, fp);
  // load colors
  color Colors[(sizeof(buffer) / sizeof(buffer[0]) - 6) / 6];
  int g = 0;
  // get the width / height
  char *m =
      (char *)malloc((sizeof(char) * (sizeof(buffer) / sizeof(buffer[0]))));
  strcpy(m, buffer);
  char *p = strtok(m, " ");
  char *j = strtok(p, "\n");
  j = strtok(NULL, "\n");
  width = atoi(j);
  //
  char *out = strtok(buffer, " \n");
  color tmp = {0, 0, 0};
  int k = 0, c = 0, count = 0;
  while (out != NULL){
    if(k == 2) height = atoi(out);
    if(count <= 2 && k > 3){
       // printf("USING * %s\n",out);
        sscanf(out, "%d", &c);
        switch(count){
            case 0: tmp.r = c; break;
            case 1: tmp.g = c; break;
            case 2: tmp.b = c; break;
        }
        count++;
    }else if(k > 3){
        Colors[g++] = tmp;
        count = 0;
        //printf("[%d %d %d]\n",Colors[g-1].r, Colors[g-1].g, Colors[g-1].b);
        //getchar();
        out = strtok(NULL, " \n");
        out = strtok(NULL, " \n");
    }else{
      //printf("NOT USING * %s\n",out);
    }
    k++;
    out = strtok(NULL, " \n");
}
  for (int i = 0, c = 0; i < g *2; i++) {
    printf("\033[48;2;%d;%d;%dm.", Colors[c].r, Colors[c].g, Colors[c].b);
    if (i % 2 == 0)
      c++;
    if (i % (width) == 0)
      printf("\n");
  }
  printf("\nInfo, %d pixels found, expected %d, diff of %d\n", g,
         width * height, width * height - g);
}
void usage() {
  printf("./tppm [filename]\n");
  exit(0);
}
