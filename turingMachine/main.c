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
   int mConfig;
   char  symbol[50];
   char  operations[5][3];
   int finalMConfig;
};

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[500];
    struct Configuration *ptrConfig = &configs[0];
    
    char tape[] = "                                                                                                                  " ;
    char *ptrTape=tape;
    
    int i = 0;
    
    struct Configuration config = {
      (int) 'b',
        "None",
        {"P0","R"},
        (int) 'c'
    };
  

    configs[i++]=config;
    
    config.mConfig=(int) 'c';
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    config.finalMConfig=(int)('e');
      
    configs[i++]=config;
    
    config.mConfig=(int) 'e';
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"P1");
    strcpy(config.operations[1],"R");
    config.finalMConfig=(int) 'f';
      
    configs[i++]=config;
    
    config.mConfig = (int) 'f';
    strcpy(config.symbol,"None");
    strcpy(config.operations[0],"R");
    config.finalMConfig = (int) 'b';
      
    configs[i++]=config;
    
   
    int times = 0; // control number of runs
    int stop = 20; // control number of runs
  
    
    int whichConfig=0;
    
    while (times<stop) {
        if (times==0) {
            config = configs[whichConfig];
        }
        
        printf("mConfig %c finalMConfig %c \n",(char) config.mConfig, (char) config.finalMConfig);
    
        /* if tape position is None */
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
                    
                    
                    // loop through and find the config to load.  it should be finalMConfig
                
                        
                    }
            
            printf("search for %c int %i \n", (char) config.finalMConfig, config.finalMConfig);
            
            for (int x=0; x < i; x++) {
                printf("searching config %c next config %c \n", configs[x].finalMConfig, configs[x].mConfig);
                if (configs[x].mConfig == config.finalMConfig) {
                    printf("found config %c next config %c \n", configs[x].mConfig, configs[x].finalMConfig);
                    config = configs[x];
                    break;
                }
            }
            
        }
        
        times++;
        printf("ptrTape %s",tape );
    }
    
   
    printf("done\n");
    
    
}
