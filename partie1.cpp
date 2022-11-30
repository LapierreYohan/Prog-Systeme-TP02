#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;
//g++ -o index.exe index.cpp

int main(int argc, char const *argv[])
{
    int tube[2];
    char c;
    pid_t pid;

    if ((pipe(tube) == -1) || (pid = fork())==-1)
    {
        perror ("Erreur création tube ou processus");
        exit(errno);
    }

    if (pid > 0) 
    {
        close (tube[0]);
        write(tube[1], "qrpuvssentr qr prggr cuenfr ra ebg13 !", 38); // Non bloquant
        close(tube[1]);
        wait(NULL);
    } 
    else 
    {

        close (tube [1]);
        while (read(tube [0],&c,1)) // Bloquant : Attend une ecriture : Synchronisé 
        {
            if (( c <= 'z' )&&( c >= 'a' ))
            {
                char temp = (c - 'a' +13)%26+ 'a';
                std :: cout << temp ;
            }
            else
                std :: cout << c ;
        }
        close (tube[0]);
        std :: cout << std :: endl ;
    }
    std :: cout << " fin du processus " << getpid () << std :: endl ;

    return EXIT_SUCCESS;
}