#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>


int main (void){
    
    //opens up the dictionary provided 
    FILE* file = fopen("/home/cs50/pset5/dictionaries/large", "r");
    if (!file) {
    perror("fopen");
        printf("yes it IS null1!!");
        return 0;
       
    }
    printf("successed");
    return 1;
}
