#define TOT 200

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <thread>
#include <mutex>

using namespace std;
//g++ -std=c++11 -pthread -o index.exe index.cpp

ofstream sortie("match.txt", ios::out);
mutex mtxA;
mutex mtxB;

void foo ();
void bar ( int x );

int main(int argc, char const *argv[])
{
    mtxA.lock();
    mtxB.lock();
    std :: thread first ( foo ); // Cr ́eation du premier thread , qui ex ́ecute foo
    std :: thread second ( bar ,0); // Cr ́eation du deuxi`eme thread , qui ex ́ecute bar (0)

    std :: cout << " main , foo et bar s ’ executent en parallelle ...\n " ;

    // synchronize threads :
    first.join(); // main attend que le premier thread ( foo ) se termine
    second.join(); // main attend que le second thread ( bar ) se termine

    std :: cout << " foo et bar sont termines .\n " ;

    //sleep(3);
    sortie.close();

    return EXIT_SUCCESS;
}

void foo ()
{
    int i = 0;
    while(i<TOT)
    {    
        sortie << "A-";
        i++;
        sortie.flush();
        mtxB.unlock();
        mtxA.lock();
    }
    std :: cout << " fin foo\n " ;
}
void bar ( int x )
{
    int i = 0;
    while(i<TOT)
    {
        mtxB.lock();
        sortie << "B-";
        sortie.flush();
        i++;
        mtxA.unlock();
    }
    std :: cout << " fin bar\n " ;
}