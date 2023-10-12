#include "src/md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errorMsg(char *msg){
    puts(msg);
    exit(1);
}

void asciiPrint(){
    puts("       _     _____      _   _____     _ ");
    puts("      | |   |  _  |    | | |____ |   | |");
    puts("  __ _| |__ | |/' | ___| |_    / / __| |");
    puts(" / _` | '_ \\|  /| |/ __| __|   \\ \\/ _` |");
    puts("| (_| | | | \\ |_/ /\\__ \\ |_.___/ / (_| |");
    puts(" \\__, |_| |_|\\___/ |___/\\__\\____/ \\__,_|");
    puts("  __/ |");
    puts(" |___/\n");
}

int main(int argc, char *argv[]){
    uint8_t tocrack[16], pass[16];
    char word[60];
    
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if(argc != 3){
        asciiPrint();
        puts("\nGh0st3d is an MD5 hash cracker made in C.\n");
        puts("Usage mode: ./ghosted <hash.txt> <wordlist.txt>");
        puts("@gul4rtt");
        exit(0);
    }

    if(file == NULL)
        errorMsg("[!] Error opening file.");

    for(int i = 0; i < 16; i++){
        uint8_t tmp;
        fscanf(file, "%02hhx", &tmp);
        tocrack[i] = tmp;
    }

    fclose(file);
    printf("[*] Hash found: ");
    printHash(tocrack);

    filename = argv[2];
    file = fopen(filename, "r");
    
    if(file == NULL)
        errorMsg("[!] The provided wordlist does not exist.");

    while(fgets(word, sizeof(word), file) != NULL){
        word[strcspn(word, "\n")] = '\0';
        md5String(word, pass);

        if(memcmp(tocrack, pass, sizeof(16)) == 0){
            printf("[*] Password found: %s\n", word);
            exit(0);
        }
    }

    puts("[!] Password not found =(");
    fclose(file);
    return 0;
}
