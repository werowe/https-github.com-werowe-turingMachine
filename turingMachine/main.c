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

struct Configuration {
   char mConfig[3];
   char  symbol[50];
    char  operations[OPLEN][3];
   char nextConfig[3];
};

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[500];

    
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
        "a|None|P@^R^P@^R^P0^R^R^P0^L^L|d1",
        "d1|1|R^Px^L^L^L|d2",
        "d2|0||q1",
        "q1|0|R^R|q2",
        "q2|1|R^R|q3",
        "q3|None|P1^L|p1",
        "p1|x|E^R|q1",
        "p2|@|R|f1",
        "p3|None|L^L|p1",
        "f1|0|R^R|f2",
        "f2|1|R^R|f3",
        "f3|None|P0^L^L|d1",
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
    
  
    printf("\n==============consuming rules =====================\n");
    

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
                    //  printf("next mConfig %s\n", ptrNextConfig);
                    break;
              }
              token = strtok( NULL, PIPE);
              b++;
            
      }
        printf(" nextConfig %s\n", config.nextConfig);
        configs[i++]=config;
        
     //   printf("\n===================end of that mConfig=================\n");
    
    }
    
 
  
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int times = 0; // control number of runs
    int stop = 40; // control number of runs
    
    int whichConfig=0;
    
    // symbol at position on tape
    
    char symbol[]=" ";
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
    
    //    printf("using configuration mConfig %s symbol %s nextConfig %s\n", config.mConfig, config.symbol, config.nextConfig);
        
        strncpy(symbol,ptrTape, 1);
        
       printf("mConfig %s ", config.mConfig);
        
     // load symbol that matches space on tape None, 1, 0
        if (strcmp(symbol, config.symbol) == 0) {
                
            printf(" symbol %s ", symbol);
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
                      //  printf("printing %s \n", config.operations[j]);
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
                    
             //       printf("tape %sEND\n", tape);
                        
                    }
                }
            
         //  printf("looking for next mConfig %s \n", config.nextConfig);
        
       
        
           // i is how many config objects there are
            for (int x=0; x < i; x++) {
             //   printf("searching config %s next config %s \n", configs[x].nextConfig, configs[x].mConfig);
                if (strcmp(configs[x].mConfig,config.nextConfig) == 0) {
             //       printf("found config %s next config %s \n", configs[x].mConfig, configs[x].nextConfig);
                    config = configs[x];
                    break;
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
 
