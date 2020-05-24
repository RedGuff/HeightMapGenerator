#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cassert>
using namespace std;
// https://lodev.org/cgtutor/randomnoise.html
int XMax = 256;
int YMax = 256;
const int MAXPGM = 65536; // Format PGM : https://fr.wikipedia.org/wiki/Portable_pixmap
int white = 256;
//assert( (white < MAXPGM) && ("Lessive trop forte : blanc trop blanc ! ")); // ???

int writeVector2DFilePGM(vector < vector < int > >& Matrix, string file = "") { // Ok.
    ofstream fichier(file.c_str(), ios::out);
    if(!fichier) {
        cerr << "ERROR: Impossible to write in " << file << endl;
    return -1; // Error.
        }
    else {
        fichier << "P2\n" << XMax << " " << YMax << "\n" << white << endl;
        for(int vt = 0; vt < Matrix[0].size(); vt++) {
            for(int hz = 0; hz < Matrix.size(); hz++) {
                fichier << Matrix[hz][vt] << " ";
                }
            fichier  << endl;
            }
        fichier.close();

    return 0; // Ok.
    }
    };

void changeMatrix(vector < vector < int > >& Matrix) {
        for(int vt = 0; vt < Matrix[0].size(); vt++) {
            for(int hz = 0; hz < Matrix.size(); hz++) {
                 Matrix[hz][vt] = rand() % white;
                }
        }
}



int main() {
    srand(time(NULL));       // No need for better init.
    cout << "HeightMapGenerator makes a pseudorandom grey heightmap. Not tileable!" << endl;
    vector < vector < int > > Matrix(XMax, vector< int >(YMax, 0));
    string file = "output.pgm";
changeMatrix(Matrix);
    if (writeVector2DFilePGM(Matrix, file)==0)
    {
        cout << "Ok!" << endl;
    }

    return 0;
    }
