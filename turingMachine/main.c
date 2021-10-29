//
//  main.c
//  turingMachine
//
//  Created by Walker Rowe on 10/19/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


struct Configuration {
   char mConfig[2];
   char  symbol[50];
   char  operations[5][3];
   char nextConfig[2];
};

int main(int argc, const char * argv[]) {
    

    struct Configuration configs[500];
  
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int i = 0;
 
    struct Configuration config = {"a", "a", {"a"}, "a"};
    
    char strConfig[4][50] =
    {
         "b|None|P0^R|c",
         "c|None|R|e",
          "e|None|P1^R|f",
          "f|None|R|b"
    };
    

    int g;
    
    for(int a=0; a < 4; a++ ) {
        char * workStr = strConfig[a];
        const char * ptrNextConfig = strrchr(strConfig[a], '|');
        strcpy(config.nextConfig,ptrNextConfig+1);
        const char s[2] = "|";
        const char c[2] = "^";
         char * token = strtok( workStr, s);
         int b=0;
         while( token != NULL ) {
              switch(b){
              case 0:
                    strcpy(config.mConfig,token);
                    break;
              case 1:
                      if (strcmp(token, "None") == 0) {
                            strcpy(config.symbol, " ");
                      } else {
                              strcpy(config.symbol,token);
                      }
                    break;
              case 2:
                      g=0;
                      char * tk = strtok(token, c);
                      while (tk != NULL) {
                          strcpy(config.operations[g],tk);
                          g++;
                          tk = strtok( NULL, c);
                      }
                    break;
              case 3:
                   // grabbed last one up top
                    break;
              }
              token = strtok( NULL, s);
              b++;
            
      }
        configs[i++]=config;
    }
    
    int times = 0; // control number of runs
    int stop = 400; // control number of runs
  
    
    int whichConfig=0;
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
        
        char symbol[]=" ";
        strncpy(symbol,ptrTape, 1);
        
        // if tape position is None
        if (strcmp(symbol, config.symbol) == 0) {
                
            // loop through array of operations
    
                for ( int j = 0; j < 3;j++) {
                  
                    
                    if ( strcmp(config.operations[j],"P0") == 0) {
                        *ptrTape='0';
                       }
                    if ( strcmp(config.operations[j],"P1") == 0) {
                        *ptrTape='1';
                       }
                    if ( strcmp(config.operations[j],"R") == 0) {
                        ptrTape++;
                       }
             
                        
                    }
            
           // printf("search for %c int %i \n", (char) config.nextConfig, config.nextConfig);
            
            for (int x=0; x < i; x++) {
              //  printf("searching config %c next config %c \n", configs[x].nextConfig, configs[x].mConfig);
                if (strcmp(configs[x].mConfig,config.nextConfig) == 0) {
                 //   printf("found config %c next config %c \n", configs[x].mConfig, configs[x].nextConfig);
                    config = configs[x];
                    break;
                }
            }
            
        }
        
        times++;
        printf("ptrTape %s\n",tape );
    }
    
   
    printf("done\n");
    
    int exp=-1;
    
   
  
    double rational=0;
    
    // calculate like this:
    //
    // .01010101=(2**-2)+(2**-4)+(2**-6)=0.333333
    
    for (int l = 0; l < strlen(tape); l++) {
        if (isdigit(tape[l])) {
            if ( (int) tape[l] == '1') {
                rational = rational + pow(2, exp);
            }
            exp--;
        }
    }
    
   printf("in decimal this is . %.15f\n", rational);
 
}
