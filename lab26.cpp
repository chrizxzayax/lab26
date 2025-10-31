// comsc 210 | lab26 | Christian Molina

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_RUNS = 15;// number of runs for averaging
const int STRUCTURES = 3;// vector, list, set
const int ROWS = 4;// for data sizes
const int COLS = STRUCTURES;// for vector, list, set
const int W1 = 12;// width for printing



int main() {

    long long results[NUM_RUNS][ROWS][COLS];// to store timing results

    long long accum[ROWS][COLS];// to accumulate totals for averaging
    for (int run = 0; run < ROWS; ++run)// for each run set up data structures
        for (int c = 0; c < COLS; ++c)
            accum[run][c] = 0;

    for (int run = 0; run < NUM_RUNS; ++run) {
        vector<string> data_vector;
        list<string> data_list;
        set<string> data_set;

        {
            ifstream fin("codes.txt");
            if (!fin) {
                cerr << "Error opening file." << endl;
                return 1;
            }
            string cd;
            auto start = chrono::high_resolution_clock::now();     
            while (fin >> cd) {
                data_vector.push_back(cd);
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][0][0] = duration.count();
            fin.close();
        }

        {//read into the list structure
            ifstream fin("codes.txt");
            if (!fin) {
                cerr << "Error opening file." << endl;
                return 1;
            }
            string cd;
            auto start = chrono::high_resolution_clock::now();     
            while (fin >> cd) {
                data_list.push_back(cd);
            }
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][0][1] = duration.count();
            fin.close();
        }


    }

    
    // Print averaged results
    
}