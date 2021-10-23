//
//  main.c
//  turingMachine
//
//  Created by Walker Rowe on 10/19/21.
//

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


 

struct Configuration {
   char  mConfig[2];
   char  symbol[50];
   char  operations[5][3];
   char  finalMConfig[2];
};

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[500];
    struct Configuration *ptrConfig = &configs[0];
    
    char tape[500] = " " ;
    char *ptrTape=tape;
    
    int i = 0;
    
    struct Configuration config = {
      "b",
        "None",
        {"P0","R"},
        "c"
    };
  

    configs[i++]=config;
    
    strcpy(config.mConfig,"c");
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    strcpy(config.finalMConfig,"e");
      
    configs[i++]=config;
    
    strcpy(config.mConfig,"e");
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"P1");
    strcpy(config.operations[1],"R");
    strcpy(config.finalMConfig,"f");
      
    configs[i++]=config;
    
    strcpy(config.mConfig,"f");
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    strcpy(config.finalMConfig,"b");
      
    configs[i++]=config;
    
   
    int k = 0;
    
    
    while (k<i) {
        config = configs[k];
        
        printf("%s\n",config.mConfig);
        

      
                
        if (strcmp(config.symbol,"None") == 0 ) {
                
                if ( strcmp(ptrTape," ") == 0) {
                    
                    printf("is empty\n");
    
                for ( int j = 0; j < 3;j++) {
                    printf("%s\n",config.operations[j]);
                    }
                }
        }
        
                  ptrTape++;
        k++;
    }
    
    printf("done\n");
    
    
}
