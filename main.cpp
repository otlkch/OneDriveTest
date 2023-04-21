#include <string>
#include <iostream>
#include "Test.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        cout << "Incorrect number of utility call arguments\n";
        return 0;
    };

    string login = argv[1];
    string password = argv[2];
    string command = argv[3];
    string src_path = argv[4];
    string dst_path = argv[5];

    /*parser(command, dst_path, src_path);
    }*/

    OneDriveWorker worker(login, password);
    return 0;
}