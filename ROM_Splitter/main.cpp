#include <stdio.h>
#include <stdlib.h>

#define FILE_SIZE 131072 // 128KB
#define HALF_SIZE 65536  // 64KB

void splitBinaryFile(const char* inputFile, const char* outputFile1, const char* outputFile2) {
    FILE *inFile = fopen(inputFile, "rb");
    
    
    if (!inFile) {
        perror("Error opening input file");
        return;
    }

    FILE *outFile1 = fopen(outputFile1, "wb");
    FILE *outFile2 = fopen(outputFile2, "wb");


    if (!outFile1 || !outFile2) {
        perror("Error opening output files");
        fclose(inFile);
        return;
    }

    unsigned char buffer[FILE_SIZE];
    size_t bytesRead = fread(buffer, 1, FILE_SIZE, inFile);
    if (bytesRead != FILE_SIZE) {
        fprintf(stderr, "Error: Input file size is not 128KB!\n");
        fclose(inFile);
        fclose(outFile1);
        fclose(outFile2);
        return;
    }

    for (size_t i = 0; i < FILE_SIZE; i += 2) {
        fputc(buffer[i], outFile1);     // Even bytes (MSB)
        fputc(buffer[i + 1], outFile2); // Odd bytes (LSB)
    }

    fclose(inFile);
    fclose(outFile1);
    fclose(outFile2);

    printf("File split successfully.\n");
}

int main(int argc, char* argv[]) {

    // Correct Argument split.exe <input_file>
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile1 = "rom_msb.bin";
    const char* outputFile2 = "rom_lsb.bin";

    splitBinaryFile(inputFile, outputFile1, outputFile2);

    return 0;
}
