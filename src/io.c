// #include "include/io.h"
// #include <stdio.h>
// #include <stdlib.h>

// char* get_file_contents(const char *filepath){
//     char* buffer = 0;
//     long length;

//     FILE *f = fopen(filepath, "rb");

//     if (f){

//         fseek(f, 0, SEEK_END);
//         length = ftell(f);
//         fseek(f, 0, SEEK_SET);


//         buffer = calloc(length ,length);


//         if (buffer)
//             fread(buffer, 1, length, f);
        
//         fclose(f);

//         return buffer;

//     }
//     printf("Could not open file: %s\n", filepath);
//     exit(2);
// }


#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>

char* get_file_contents(const char *filepath)
{
    char* buffer = 0;
    long length;

    FILE *f = fopen(filepath, "rb");

    if (!f)
    {
        printf("Could not open file: %s\n", filepath);
        exit(2);
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    rewind(f);

    buffer = calloc(length + 1, sizeof(char));

    if (!buffer)
    {
        printf("Memory allocation failed\n");
        fclose(f);
        exit(3);
    }

    fread(buffer, 1, length, f);
    buffer[length] = '\0';

    fclose(f);

    return buffer;
}