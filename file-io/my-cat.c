#include <stdio.h>



int main(int argc, char *argv[])
{

    unsigned char c;
    if (argc < 2){
        
        while ((c = getchar()) != EOF){
            putchar(c);
        }
        return 0;
    }

    FILE *file = fopen(argv[1], "rb");

    while (fread(&c, sizeof c, 1, file) == 1)
    {
        putchar(c);
    }

    fclose(file);

    return 0;
}
