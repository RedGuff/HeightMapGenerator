#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
// #include <cassert>
using namespace std;
// https://lodev.org/cgtutor/randomnoise.html for inspirations and motivations.
int XMax = 256;
int YMax = 256;
const int MAXPGM = 65536; // Format PGM : https://fr.wikipedia.org/wiki/Portable_pixmap
int white = 256;
//assert( (white =< MAXPGM) && ("Lessive trop forte : blanc trop blanc ! ")); // Not working! Why???

void coutVector2D(vector < vector < int > >& Matrix) { // Ok.
    for(int vt = 0; vt < Matrix[0].size(); vt++) {
        for(int hz = 0; hz < Matrix.size(); hz++) {
            cout << Matrix[hz][vt] << " ";
            }
        cout  << endl;
        }
    };

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

void MatrixAddRand(vector < vector < int > >& Matrix, int ampl = white) { // Ok.
    for(int vt = 0; vt < Matrix[0].size(); vt++) {
        for(int hz = 0; hz < Matrix.size(); hz++) {
            Matrix[hz][vt] = Matrix[hz][vt] + rand() % ampl;
            }
        }
    }

void MatrixLissageRect(vector < vector < int > >& Matrix, int lissageX = 42, int lissageY = 42) { // Ok.
    for(int vt = 0; vt < Matrix[0].size(); vt++) {
        for(int hz = 0; hz < Matrix.size(); hz++) {
            int sumXY = 0;
            for(int yvt = 0; yvt < lissageY ; yvt++) {
                for(int xhz = 0; xhz < lissageX; xhz++) {
                    sumXY = sumXY + Matrix[(hz + xhz) % Matrix[0].size()][(vt + yvt) % Matrix.size()]; // % is for tilage and compatibility.
                    }
                }
            Matrix[hz][vt] = sumXY / (lissageX * lissageY); // I respect logarithmic calculations, but I don't need them here.
            }
        }
    }


void saturation(vector < vector < int > >& Matrix) { // Ok.
    for(int vt = 0; vt < Matrix[0].size(); vt++) {
        for(int hz = 0; hz < Matrix.size(); hz++) {
            Matrix[hz][vt] = max(Matrix[hz][vt], 0);
            Matrix[hz][vt] = min(Matrix[hz][vt], white);
            }
        }
    };

int main() {
    srand(time(NULL));       // No need for better init.
    cout << "HeightMapGenerator makes a pseudorandom grey tileable heightmap!" << endl;
    vector < vector < int > > Matrix(XMax, vector< int >(YMax, 0));
    string file = "R:\output.pgm";
    MatrixAddRand(Matrix, white);
    // coutVector2D(Matrix);
    MatrixLissageRect(Matrix, 42, 5);
    cout << "\n" << endl;
    // coutVector2D(Matrix);
    saturation(Matrix);
    if(writeVector2DFilePGM(Matrix, file) == 0) {
        cout << file << ": Ok!" << endl;
        }
    return 0;
    }
