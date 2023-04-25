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
  char* out;
  out = strtok(buffer," ");
	/*for(i = i; i < sizeof(buffer)/sizeof(buffer[0]); i++){
		//printf("%d, %d\n",g,i);
		// parse
		int s = 0;
		color tmp = {0,0,0};
		if(buffer[i] == '\n')
		s++;
		else if(buffer[i] != ' '){
			while(s < 3){
				while(buffer[i++] != ' '){
					int c= 0;
					int n = 0;
   			 	sscanf(&buffer[i], "%d", &c);
          printf("%c\n",buffer[i]);
          getchar();
          if(c >= 10)i++;
          if(c >= 100) i+=2;
					switch(s){
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
				}

				s++;
				//if(buffer[i] == ' ') s++;
				
			}
			Colors[g++] = tmp;
      //printf("%d,%d,%d \n",Colors[g-1].r,Colors[g-1].g, Colors[g-1].b);
      //getchar();
		}
	}*/
  int count = 0;
  color tmp = {0,0,0};
  int k = 0;
  while (out != NULL)
  {  
    if(k == 1){
        printf("%s\n",out);
        sscanf(out, "%d", &width);
        printf("%d\n",width);
    }
    else if(count < 3){
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
    k++;
    out = strtok(NULL, " ");
  }
  int c = 0;
	for(int i = 0; i < g; i++){
    //printf("%d,%d,%d \n",Colors[i].r,Colors[i].g, Colors[i].b);
    //getchar();
    printf("\033[48;2;%d;%d;%dm ",Colors[c].r,Colors[c].g, Colors[c].b);
    if(i % 1 == 0)c++;
    if(i % (width+3) == 0)printf("\n");
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

