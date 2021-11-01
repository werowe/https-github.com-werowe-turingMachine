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



#define PIPE "|"
#define CARET "^"

struct Configuration {
   char mConfig[2];
   char  symbol[50];
   char  operations[15][3];
   char nextConfig[2];
};

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[500];

    
    int i = 0;
 
    struct Configuration config = {"a", "a", {"a"}, "a"};
  
   // it's ok to have the same letter for the m_config more than once.  we want it to just jump to that first instruction
    // then loop through the others
    
    char strConfig[3][50] = {
        "a|None|P@^R^P@^R^P0^R^R^P0^L^L|d1",
        "d1|1|R^Px^L^L^L|d2",
        "d2|0|R^Px^L^L^L|a"
    };
    
    /*
    
    char strConfig[12][50] = {
        "a|None|P@^R^P@^R^P0^R^R^P0^L^L|d",
        "d1|1|R^Px^L^L^L|d2",
        "d2|0|R^Px^L^L^L|q",
        "q|0|R^R|q1",
        "q1|1|R^R|q2",
        "q2|None|P1^L|p",
        "p|x|E^R|q",
        "p|@|R|f",
        "p|None|L^L|p",
        "f|0|R^R|f",
        "f|1|R^R|f",
        "f|None|P0^L^L|d",
    };
    
     */
    
    
    /* 0.01010101001
    char strConfig[4][50] =
    {
         "b|None|P0^R|c",
         "c|None|R|e",
          "e|None|P1^R|f",
          "f|None|R|b"
    };
 

    
    char strConfig[3][50] =
      {
           "b|None|P0|b",
           "b|0|R^R^P1|b",
           "b|1|R^R^P0|b"
      };
     */
    

    int g;
    
      int total = sizeof(strConfig);
      int columns = sizeof(strConfig[0]);
      int rows = total / columns;
    
    for(int row=0; row < rows; row++ ) {
        char * workStr = strConfig[row];
        const char * ptrNextConfig = strrchr(strConfig[row], '|');
        strcpy(config.nextConfig,ptrNextConfig+1);
    
         char * token = strtok( workStr, PIPE);
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
                      char * tk = strtok(token, CARET);
                      while (tk != NULL) {
                          strcpy(config.operations[g],tk);
                          g++;
                          tk = strtok( NULL, CARET);
                      }
                    break;
              case 3:
                   // grabbed last one up top
                    break;
              }
              token = strtok( NULL, PIPE);
              b++;
            
      }
        configs[i++]=config;
    }
    
 
  
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int times = 0; // control number of runs
    int stop = 4; // control number of runs
    
    int whichConfig=0;
    
    // symbol at position on tape
    
    char symbol[]=" ";
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
        

        printf("using configuration mConfig %s symbol %s nextConfig %s\n", config.mConfig, config.symbol, config.nextConfig);
        
     // load symbol that matches space on tape None, 1, 0
        if (strcmp(symbol, config.symbol) == 0) {
                
            strncpy(symbol,ptrTape, 1);
            
            // loop through array of operations
    
                for ( int j = 0; j < columns;j++) {
                    printf("operation %s\n", config.operations[j]);
                    
                    if ( (int) config.operations[j][0]== 'P') {
                        *ptrTape=(int) config.operations[j][1];
                       }
                    
                    if ( (int) config.operations[j][0]== 'E') {
                        *ptrTape=' ';
                       }
            
                    if ( strcmp(config.operations[j],"R") == 0) {
                        ptrTape++;
                       }
                    
                    if ( strcmp(config.operations[j],"L") == 0) {
                        ptrTape--;
                       }
                    
                    printf("tape %s\n", tape);
                        
                    }
            
           // printf("search for %c int %i \n", (char) config.nextConfig, config.nextConfig);
            
           // i is how many config objects there are
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
