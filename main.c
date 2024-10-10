#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
   MAX_CHAR = 100,  // Maximum characters we can read
   MAX_LINE = 1000  // Maximum strings we can read
};

void game_start(int index, char buffer[MAX_LINE][MAX_CHAR], int line, int track);

int main(int argc, char **argv) {
	if(argv[1] == NULL || strncmp(argv[1], "mactan", 6) != 0) {
	    printf("Please provide a valid argv[1]\n");
	    return 1;
	} else if(argv[2] == NULL) {
	    printf("Please provide a valid argv[2]\n");
	    return 1;
	}
	
	FILE *fileptr = fopen(argv[2], "r");
	if(fileptr == NULL) {
	    printf("Cannot open '%s' file location\n", argv[2]);
	    return 1;
	}
	
	char buffer[MAX_LINE][MAX_CHAR];
	
	for(int i = 0; i < MAX_LINE; i++) {
	    if(fgets(buffer[i], MAX_CHAR, fileptr) == NULL) {
	        break;
	    }
	}
	
	fclose(fileptr);
	
	int index = 0, line = 0, track = 0;
	while(strncmp(buffer[index], "<//>", 4) != 0) {
	        printf("%s", buffer[index]);
	        index++;
	}
	   
	getch();
	    
	system("clear");
	game_start(index, buffer, line, track);
	 
	return 0;
}

void game_start(int index, char buffer[MAX_LINE][MAX_CHAR], int line, int track) {
    char narr[MAX_LINE][MAX_CHAR] = {
       "<001-001>", "<001-ATT>", "<001-DEF>", "<001-DDG>",
       "<002-002>", "<002-ATT>", "<002-DEF>", "<002-DDG>",
       "<003-003>", "<003-ATT>", "<003-DEF>", "<003-DDG>",
       "<004-004>", "<004-ATT>", "<004-DEF>", "<004-DDG>",
       "<005-005>", "<005-ATT>", "<005-DEF>", "<005-DDG>",
       "<END-END>"
    };
    char list[3][5] = {"-att", "-def", "-ddg"};
    char input[5];
    int list_size = sizeof(list) / sizeof(list[0]);
    
    system("clear");
    for(; index < MAX_LINE; index++) {
        if(strncmp(buffer[index], narr[line], 9) == 0) {
            while(strncmp(buffer[index], "<//>", 4) != 0) {
                printf("%s", buffer[index]);
                index++;
            }
            
            break;
        }
    }
    
    scanf("%4s", input);
    int num = 0;
    while(strncmp(input, list[num], 4) != 0) {
        if(num > list_size) {
            printf("\n'%s' is not a valid input\n", input);
            return;
        } num++;
    }
    
    switch(num) {
        case 0: track = line + 1; break;
        case 1: track = line + 2; break;
        case 2: track = line + 3; break;
        default: break;
    }
    
    system("clear");
    for(; index < MAX_LINE; index++) {
        if(strncmp(buffer[index], narr[track], 9) == 0) {
            index++;
            while(strncmp(buffer[index++], "<//>", 4) != 0) {
                printf("%s", buffer[index]);
            }
            
            break;
        }
    }
    
    printf("\n");
    fflush(stdin);
    
    getch();
    
    if(track == 1 || track == 5 || track == 9 || track == 10 || track == 19) {
        printf("You've died from your previous decision\n");
        return;
    } else if(line == 20) {
        return;
    }
    
    line += 4;
    game_start(index, buffer, line, track);
    
}
