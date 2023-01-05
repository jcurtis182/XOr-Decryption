#include <stdio.h>
#include <stdlib.h>

//this is the complicated version of the XOr decryption shown in catXOr

int main(int argc, char** argv){
    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL){
        printf("Error opening file '%s\n'", argv[1]);                   //error case
        exit;
    }
    
    FILE *output = fopen("Q4Output.txt", "w+");                         //create file for output so it can be turned in
    fseek(file, 0L, SEEK_END);
    long int size = ftell(file);                                        //get file size
    rewind(file);                                                       //^^^ moves to end of file, so we have to go back to the start
    
    char buffer[64];                                                    //create both buffers
    char buffer2[64];
    
    for(int i = 0; i < size - 1;){                                      //go thru every line of file
        int length = fread(buffer, 1, 64, file);                        //adding each time to find length
        i+= length;
        for(int j = 0; j < length; j++){                                
            char prev = buffer[j];                                      //store prev char into second buffer so we can use it as the XOr key for next one
            
            if(i > 64) buffer[j] = buffer[j] ^ buffer2[j];              //if <64, XOr Key is the last char that we just saved
            else buffer[j] = buffer[j] ^ ((char)157);                   //if >64, XOr Key is 157
            
            buffer2[j] = prev;
            printf("%c", buffer[j]);                                    
            
            char* temp = &buffer[j];
            fwrite(temp, 1, 1, output);                                 //Print decrypted char to output file
            buffer[j] = '\0';
        }
    }
    printf("\n\nSuccess. Output printed to Q4Output.txt");              //it works peepoHappy Clap
    printf("\n%s size: %d\n", argv[1], size);
    fclose(file);
    fclose(output);
}