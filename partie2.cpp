#define TOT 100

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/wait.h>


using namespace std;
//g++ -o index.exe index.cpp

int main(int argc, char const *argv[])
{
    int tubePere[2];
    int tubeFils[2];

    ofstream sortie("match.txt", ios::out);

    pid_t pid;
    int i = 0;
    char c;

    if ((pipe(tubePere) == -1) || (pipe(tubeFils) == -1) || (pid = fork())==-1)
    {
        perror ("Erreur création tube ou processus");
        exit(errno);
    }

    if (pid > 0) //Pere
    {
        close(tubeFils[1]); // Ferme l'ecriture dans la Com Fils
        close(tubePere[0]); // Ferme la lecture dans le proc pere

        while (i < TOT) {
            if(read(tubeFils[0],&c,1)) {
                i++;
                sortie<<"Ping-";
                sortie.flush();
                write(tubePere[1], "a", 1);
            }
       }
       close(tubeFils[0]);
       close(tubePere[1]);
       wait(NULL);
    } 
    else // Fils
    {
        close(tubeFils[0]);
        close(tubePere[1]);

        write(tubeFils[1], "a", 1);

        while (i < TOT) {
            if(read(tubePere[0],&c,1)) {
                i++;
                sortie<<"Pong\n";
                sortie.flush();
                write(tubeFils[1], "a", 1);
            }
       }
       close(tubePere[0]);
       close(tubeFils[1]);
    }
    sortie.close();
    std :: cout << " fin du processus " << getpid () << std :: endl ;

    return EXIT_SUCCESS;
}