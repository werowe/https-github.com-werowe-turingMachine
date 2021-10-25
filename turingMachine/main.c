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
    
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int i = 0;
    
    struct Configuration config = {
      atoi("b"),
        "None",
        {"P0","R"},
        atoi("c")
    };
  

    configs[i++]=config;
    
    strcpy(config.mConfig,atoi("c"));
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    strcpy(config.finalMConfig,atoi("e"));
      
    configs[i++]=config;
    
    strcpy(config.mConfig,atoi("e"));
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"P1");
    strcpy(config.operations[1],"R");
    strcpy(config.finalMConfig,atoi("f"));
      
    configs[i++]=config;
    
    strcpy(config.mConfig,"f");
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    strcpy(config.finalMConfig,"b");
      
    configs[i++]=config;
    
   
    int times = 0;
    int stop = 20;
    int idx=0;
    
    int whichConfig=0;
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
        
        printf("mConfig %s finalMConfig %s \n",config.mConfig, config.finalMConfig);
    
        if (strcmp(config.symbol,"None") == 0 ) {
                
                if ( strcmp(tape[idx]," ") == 0) {
                    printf("is empty\n");
    
                for ( int j = 0; j < 3;j++) {
                    printf("%s\n",config.operations[j]);
                    
                    if ( strcmp(config.operations[j],"P0") == 0) {
                        strcpy(tape[idx],"0");
                       }
                    if ( strcmp(config.operations[j],"P1") == 0) {
                        strcpy(tape[idx],"1");
                       }
                    if ( strcmp(config.operations[j],"R") == 0) {
                        idx++;
                       }
                    printf("ptrTape in loop %s",ptrTape );
                    }
                }
        }
        
        config = configs[atoi(config.finalMConfig)];
        times++;
    }
    
    printf("ptrTape %s",ptrTape );
    printf("done\n");
    
    
}
