#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	int r,g,b;
} color;
int width = 0;
int height = 0;
void usage();
unsigned concatenate(unsigned x, unsigned y);
int main(int args, char* argv[]){
	printf("Terminal PPM Viewer - Electro_Corp\n");
	if(!argv[1]) usage();
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){printf("File %s not found!\n",argv[1]);exit(1);}
	fseek(fp, 0L, SEEK_END);
	char buffer[ftell(fp)];
	rewind(fp);
	fread(buffer,sizeof(buffer),1,fp);
	// load colors
	color Colors[2560];
	int g = 0, no = 0, i = 0;
	// get the width / height
	while(no < 3)
		if(buffer[i++] == '\n')
		no++; 
	for(i = i; i < sizeof(buffer)/sizeof(buffer[0]); i++){
		printf("%d, %d\n",g,i);
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
   			 		sscanf(c, "%d", buffer[i]);
					switch(s){
						case 0:
						n = 0;
						if(tmp.r != 0)
						n = concatenate(tmp.r, c);
						else
						n = c;
						tmp.r = n;
						break;
						case 1:
						n = 0;
						if(tmp.b != 0)
						n = concatenate(tmp.b, c);
						else
						n = c;
						tmp.b = n;
						break;
						case 2:
						n = 0;
						if(tmp.g != 0)
						n = concatenate(tmp.g, c);
						else
						n = c;
						tmp.g = n;
						break;
					}
				}
				s++;
				//if(buffer[i] == ' ') s++;
				
			}
			Colors[g++] = tmp;
		}
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

