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
#define OPLEN 15
#define SYMLEN 4
#define CFSIZE 500

struct Configuration {
   char mConfig[3];
   char  symbol[4];
    char  operations[OPLEN][3];
   char nextConfig[3];
};

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[CFSIZE];
    struct Configuration loopConfigs[CFSIZE];
    
    int i = 0;
 
    struct Configuration config = {"a", "a", {"a"}, "a"};
  
   // it's ok to have the same letter for the m_config more than once.  we want it to just jump to that first instruction
    // then loop through the others
    
   /* char strConfig[3][50] = {
        "a|None|P@^R^P@^R^P0^R^R^P0^L^L|d1",
        "d1|1|R^Px^L^L^L|d2",
        "d2|0|R^Px^L^L^L|a"
    };
    
    */
    
    char strConfig[12][50] = {
        "a|None|P@^R^P@^R^P0^R^R^P0^L^L|d",
        "d|1|R^Px^L^L^L|d",
        "d|0||q",
        "q|0|R^R|q",
        "q|1|R^R|q",
        "q|None|P1^L|p",
        "p|x|E^R|q",
        "p|@|R|f",
        "p|None|L^L|p",
        "f|0|R^R|f",
        "f|1|R^R|f",
        "f|None|P0^L^L|d",
    };
    
    
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
                    //  printf("mConfig %s ", config.mConfig);
                    break;
              case 1:
                      if (strcmp(token, "None") == 0) {
                            strcpy(config.symbol, " ");
                      } else {
                              strcpy(config.symbol,token);
                      }
                     // printf(" symbol %s", config.symbol);
                    break;
              case 2:
                      g=0;
                      char * tk = strtok(token, CARET);
                      // erase operations
                      
                      for(int o=0; o <  OPLEN; o++){
                           strcpy(config.operations[o],"");
                       }
                      while (tk != NULL) {
                          strcpy(config.operations[g],tk);
                       //   printf( " operation %s ", config.operations[g]);
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
        printf(" nextConfig %s\n", config.nextConfig);
        configs[i++]=config;
  
    }
    
 
  
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int times = 0; // control number of runs
    int stop = 40; // control number of runs
    
    // symbol at position on tape
    
    char symbol[]=" ";
  
    // point to first config
    config = configs[0];
    
    int toLoad = 1;
    
    loopConfigs[0]=configs[0];
    
    while (times<stop) {
    
        strncpy(symbol,ptrTape, 1);
        
        // loop through all mConfigs
        
    
        
        for (int k = 0; k < toLoad; k++) {
            config = loopConfigs[k];
        
     // load symbol that matches space on tape None, 1, 0
        if (strcmp(symbol, config.symbol) == 0) {
                
            // loop through array of operations
    
                for ( int j = 0; j < columns; j++) {
                    
                    // poor way of checking whether operation is empty, better way is variable size of array
                    
                    if (strcmp(config.operations[j],"")!=0) {
                     //   printf("operation %s", config.operations[j]);
                        ;
                    }else {
                        break;
                    }
                                        
                    if ( (int) config.operations[j][0]== 'P') {
                        *ptrTape=(int) config.operations[j][1];
                       }
                    
                    if ( (int) config.operations[j][0]== 'E') {
                      //  printf("erasing %s \n", config.operations[j]);
                        *ptrTape=' ';
                       }
            
                    if ( strcmp(config.operations[j],"R") == 0) {
                     //   printf("move right\n");
                        ptrTape++;
                       }
                    
                    if ( strcmp(config.operations[j],"L") == 0) {
                     //   printf("move left\n");
                        ptrTape--;
                       }
                        
                    }
                }
            
        }
            // erase loop configs for next run
        memset(&loopConfigs, 0, sizeof(loopConfigs));
        
           // i is how many config objects there are
        
            toLoad=0;
            
            for (int x=0; x < rows; x++) {
                if (strcmp(configs[x].mConfig,config.nextConfig) == 0) {
                    loopConfigs[toLoad] = configs[x];
                    toLoad++;
                }
            }
            
        printf("\n tape %s\n",tape );
        times++;
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
 
