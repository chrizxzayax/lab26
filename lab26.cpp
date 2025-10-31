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



int main() {

    for (int run = 0; run < NUM_RUNS; ++run) {// for each run set up data structures
        vector<string> data_vector;
        list<string> data_list;
        set<string> data_set;
    }

}