//
//  main.c
//  turingMachine
//
//  Created by Walker Rowe on 10/19/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
         "b|None|P0|R|c",
         "c|None|R|e",
          "e|None|P1^R|f",
          "f|None|R|b"
    };
    

    int g;
    
    for(int a=0; a < 4; a++ ) {
        char * workStr = strConfig[a];
         char * token = strtok( workStr, "|");
         int b=0;
         while( token != NULL ) {
              switch(b){
              case 0:
                    strcpy(config.mConfig,token);
                    break;
              case 1:
                    strcpy(config.symbol,token);
                    break;
              case 2:
                      g=0;
                      char * tk = strtok(token, "^");
                      while (tk != NULL) {
                          strcpy(config.operations[g],tk);
                          g++;
                          tk = strtok( NULL, "^");
                      }
                    break;
              case 3:
                    strcpy(config.nextConfig,token);
                    break;
              }
              token = strtok( NULL, "|");
              b++;
            
      }
        configs[i++]=config;
    }

  
    
    int times = 0; // control number of runs
    int stop = 20; // control number of runs
  
    
    int whichConfig=0;
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
        
        printf("mConfig %s nextConfig %s \n",  config.mConfig,  config.nextConfig);
    
        // if tape position is None
        if (strcmp(config.symbol,"None") == 0 ) {
                
        
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
    
 
}
