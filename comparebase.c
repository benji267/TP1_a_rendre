#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h> 
#include <stdint.h>
#define CHK(op) do { if ((op) == -1) raler (1, #op); } while (0)

noreturn void raler (int syserr, const char *msg, ...)
{
    va_list ap;

    va_start (ap, msg);
    vfprintf (stderr, msg, ap);
    fprintf (stderr, "\n");
    va_end (ap);

    if (syserr == 1)
        perror ("");

    exit (EXIT_FAILURE);
}


int main(int argc, char* argv[]){
    if(argc!=3){
        perror("erreur sur le nombre d'argument");
        exit(1);
    }
    else{
        int k;
        int d;
        int i;
        int premier_fichier;
        CHK(premier_fichier=open(argv[1], O_RDONLY, 0666));
        int deuxieme_fichier;
        CHK(deuxieme_fichier=open(argv[2], O_RDONLY, 0666));
        struct stat fichier_1;
        CHK(fstat(premier_fichier, &fichier_1));
        int taille_premier_fichier=fichier_1.st_size;
        struct stat fichier_2;
        CHK(fstat(deuxieme_fichier, &fichier_2));
        int taille_deuxieme_fichier=fichier_2.st_size;
        char* buffer_premier_fichier[taille_premier_fichier];
        char* buffer_deuxieme_fichier[taille_deuxieme_fichier];
        while((k=read(premier_fichier, buffer_premier_fichier, taille_premier_fichier ) > 0)){
            if((d=read(deuxieme_fichier,buffer_deuxieme_fichier, 1000) > 0)){
                if(k==-1){
                    perror("erreur sur le read");
                }
                else if(d==-1){
                    perror("erreur sur le read");
                }
                else{
                    if(argv[1]==NULL){
                        perror(" EOF on fichier1 which is empty ");
                        exit(1);
                    }
                    else if(argv[2]==NULL){
                        perror(" EOF on fichier2 which is empty ");
                        exit(1);                        
                    }
                    for(i=0; i<1000; i++){
                        if((buffer_premier_fichier[i]=='\n') && (buffer_deuxieme_fichier[i]=='\n')){
                            ligne+=1;
                        }
                        else if(buffer_premier_fichier[i]==buffer_deuxieme_fichier[i]){
                            bytes+=1;
                        }
                        else if(buffer_premier_fichier[i]==EOF && buffer_deuxieme_fichier[i]!=EOF){
                            perror(" EOF on fichier1 after byte bytes, line ligne ");
                            exit(1)
                        }
                        else if(buffer_premier_fichier[i]!=EOF && buffer_deuxieme_fichier[i]==EOF){
                            perror(" EOF on fichier2 after byte bytes, line ligne ");
                            exit(1)
                        }
                        else if(buffer_premier_fichier[i]!=buffer_deuxieme_fichier[i]){
                            perror(" fichier1 fichier2 differ: byte bytes, line ligne ");
                        }
                    }
                    exit(0);
                }                  
        }
    }
}