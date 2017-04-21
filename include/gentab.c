#include <stdio.h>
#include <string.h>

int main(){
    FILE* header = NULL;
    FILE* out = NULL;
    char line[500];
    header = fopen("space_test.h", "r");
    out = fopen("out.txt", "w");
    while (fgets(line, 500, header)){
        line[strlen(line)-1] = 0;
        if(!strncmp(line, " * @test", 8)){
            fprintf(out,"%s \t", line+8);
        }else if(!strncmp(line, " * @pre", 7)){
            fprintf(out,"%s \t", line+7);
        }else if(!strncmp(line, " * @post", 8)){
            fprintf(out,"%s \t", line+8);
        }else if(!strncmp(line, "void", 4)){
            fprintf(out, "%s\t\n",line+4);
        }
    }
}