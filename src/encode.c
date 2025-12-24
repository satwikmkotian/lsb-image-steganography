#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *src_image = NULL;
    FILE *secret_file = NULL;
    FILE *out_image = NULL;

    /* Check command-line arguments */
    if (argc != 4)
    {
        printf("Usage: %s <input.bmp> <secret.txt> <output.bmp>\n", argv[0]);
        return 1;
    }

    /* Open files */
    src_image = fopen(argv[1], "rb");
    secret_file = fopen(argv[2], "rb");
    out_image = fopen(argv[3], "wb");

    if (src_image == NULL || secret_file == NULL || out_image == NULL)
    {
        printf("Error: Unable to open one or more files\
            
/* Copy BMP header (first 54 bytes) */
unsigned char header[54];

fread(header, 1, 54, src_image);
fwrite(header, 1, 54, out_image);
