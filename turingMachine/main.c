//
//  main.c
//  turingMachine
//
//  Created by Walker Rowe on 10/19/21.
//

#include <stdio.h>
#include <strings.h>


char tape[50] = {"                                                "};

struct Configuration {
   char  mConfig[2];
   char  symbol[50];
   char  operations[5][3];
   char  finalMConfig[2];
} book;

int main(int argc, const char * argv[]) {
    
    struct Configuration configs[500];
    struct Configuration *ptrConfig = &configs[0];
    
    char *prtTape = &tape[0];
    
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
    
   
    
    while (i>0) {
        config = configs[i];
        
        printf("%s\n",config.mConfig);
        switch (strcmp(*prtTape,config.symbol)) {
        
                
            case 0:
    
                for ( int j = 0; j < strlen(config.operations);j++) {
                    printf("%s\n",config.operations[j]);
                }
        }
        
                  prtTape++;
        i--;
    }
    
    printf("done\n");
    
    
}
