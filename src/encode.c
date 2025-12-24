#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BMP_HEADER_SIZE 54
#define LENGTH_BITS 32

/* Get file size */
long get_file_size(FILE *fp)
{
    long size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    return size;
}

/* Embed one bit into LSB of image byte */
unsigned char embed_bit(unsigned char image_byte, unsigned char bit)
{
    image_byte = image_byte & 0xFE;   // clear LSB
    image_byte = image_byte | bit;    // set new bit
    return image_byte;
}

int main(int argc, char *argv[])
{
    FILE *src_image = NULL;
    FILE *secret_file = NULL;
    FILE *out_image = NULL;

    unsigned char header[BMP_HEADER_SIZE];
    unsigned char image_byte;
    unsigned char secret_byte;

    long secret_size;
    long image_size;
    long required_bytes;

    /* Argument check */
    if (argc != 4)
    {
        printf("Usage: %s <input.bmp> <secret.txt> <output.bmp>\n", argv[0]);
        return 1;
    }

    /* Open files */
    src_image = fopen(argv[1], "rb");
    secret_file = fopen(argv[2], "rb");
    out_image = fopen(argv[3], "wb");

    if (!src_image || !secret_file || !out_image)
    {
        printf("Error opening files\n");
        return 1;
    }

    /* Copy BMP header */
    fread(header, 1, BMP_HEADER_SIZE, src_image);
    fwrite(header, 1, BMP_HEADER_SIZE, out_image);

    /* Capacity check */
    secret_size = get_file_size(secret_file);
    image_size = get_file_size(src_image) - BMP_HEADER_SIZE;
    required_bytes = LENGTH_BITS + (secret_size * 8);

    if (image_size < required_bytes)
    {
        printf("Error: Image too small to hold secret\n");
        return 1;
    }

    /* Encode secret length (32 bits, MSB first) */
    for (int i = 31; i >= 0; i--)
    {
        unsigned char bit = (secret_size >> i) & 0x01;

        fread(&image_byte, 1, 1, src_image);
        image_byte = embed_bit(image_byte, bit);
        fwrite(&image_byte, 1, 1, out_image);
    }

    /* Encode secret data */
    while (fread(&secret_byte, 1, 1, secret_file))
    {
        for (int i = 7; i >= 0; i--)
        {
            unsigned char bit = (secret_byte >> i) & 0x01;

            fread(&image_byte, 1, 1, src_image);
            image_byte = embed_bit(image_byte, bit);
            fwrite(&image_byte, 1, 1, out_image);
        }
    }

    /* Copy remaining image bytes */
    while (fread(&image_byte, 1, 1, src_image))
    {
        fwrite(&image_byte, 1, 1, out_image);
    }

    fclose(src_image);
    fclose(secret_file);
    fclose(out_image);

    printf("Encoding completed successfully.\n");
    return 0;
}
