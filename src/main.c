#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef struct {
	int r,g,b;
} color;
void usage();
unsigned concatenate(unsigned x, unsigned y);
int main(int args, char* argv[]){
  int height = 0;
  int width = 0;
	printf("Terminal PPM Viewer - Electro_Corp\n");
	if(!argv[1]) usage();
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){printf("File %s not found!\n",argv[1]);exit(1);}
	fseek(fp, 0L, SEEK_END);
	char buffer[ftell(fp)];
	rewind(fp);
	fread(buffer,sizeof(buffer),1,fp);
	// load colors
	color Colors[(sizeof(buffer)/sizeof(buffer[0]) - 6) / 6];
	int g = 0, no = 0, i = 13;
	// get the width / height
	while(no < 3)
		if(buffer[i++] == '\n')
		no++; 
  char* m = (char*)malloc((sizeof(char) *  (sizeof(buffer)/sizeof(buffer[0]))));
  strcpy(m,buffer);
  char* p = strtok(m," ");
  char* j = strtok(p, "\n");
  j = strtok(NULL, "\n");
  width = atoi(j);
  char* out;
  out = strtok(buffer," ");
  //printf("init = %s\n",out);
  int count = 0;
  color tmp = {0,0,0};
  int k = -1;
  while (out != NULL)
  {  
    if(count < 3){
        int c = 0;
        sscanf(out, "%d", &c);
        switch(count){
          case 0:
          tmp.r = c;
          break;
          case 1:
          tmp.g = c;
          break;
          case 2:
          tmp.b = c;
          break;
          default:
          printf("guh?\n");
          exit(1);
          break;
        }
    }else{
      count = 0;
      Colors[g++] = tmp;
    }
    count++;
    
    out = strtok(NULL, " ");
  }
  int c = 0;
	for(int i = 0; i < g; i++){
    //printf("%d,%d,%d \n",Colors[i].r,Colors[i].g, Colors[i].b);
    //getchar();
    printf("\033[48;2;%d;%d;%dm ",Colors[c].r,Colors[c].g, Colors[c].b);
    if(i % 1 == 0)c++;
    if(i % (width) == 0)printf("\n");
  }
}
void usage(){
	printf("./tppm [filename]\n");
	exit(0);
}


unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

