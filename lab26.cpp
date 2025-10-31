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

        {//read into the set structure
            ifstream fin("codes.txt");
            if (!fin) {
                cerr << "Error opening file." << endl;
                return 1;
            }
            string cd;
            auto start = chrono::high_resolution_clock::now();     
            while (fin >> cd) {
                data_set.insert(cd);
            }
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][0][2] = duration.count();
            fin.close();
        }
//this is the sort phase firstly we sort the vector, then the list
        {//sort the vector
            auto start = chrono::high_resolution_clock::now();
            sort(data_vector.begin(), data_vector.end());
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][1][0] = duration.count();

        }
        {
            auto start = chrono::high_resolution_clock::now();
            data_list.sort();
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][1][1] = duration.count();

        }
        {//set is always sorted, so no timing needed
            results[run][1][2] = -1;
        }
            //insertion phase "TESTCODE" into the middle of each structure
            
        {
            size_t ind_v = data_vector.size() / 2;
            auto start = chrono::high_resolution_clock::now();
            data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][2][0] = duration.count();
        }
        // list inserted in the middle
        {
            size_t ind_l = data_list.size() / 2;
            auto it = data_list.begin();
            advance(it, ind_l);
            auto start = chrono::high_resolution_clock::now();
            data_list.insert(it, "TESTCODE");
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][2][1] = duration.count();
        }
        // set insertion
        {
            auto start = chrono::high_resolution_clock::now();
            data_set.insert("TESTCODE");
            auto end = chrono::high_resolution_clock::now();// end timing
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][2][2] = duration.count();
        }

        // delete the phase in a middle element from each structure
        size_t nvec = data_vector.size();
        size_t nlist = data_list.size();
        size_t nset = data_set.size();
        if( nvec == 0 || nlist == 0 || nset == 0 ){
            results[run][3][0] = results[run][3][1] = results[run][3][2] = -1;
        }else {

            size_t ind = nvec / 2;
            {
                string target_v = data_vector[ind];
                auto start = chrono::high_resolution_clock::now();
                // remove shifts elements and returns new end; erase actually removes them
                data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v), data_vector.end());
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[run][3][0] = duration.count();
            }
            
            {
                auto it = data_list.begin();
                advance(it, ind);
                string target_l = *it;
                auto start = chrono::high_resolution_clock::now();
                data_list.remove(target_l);// removes all occurrences
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[run][3][1] = duration.count();
            }
            {
                auto it = data_set.begin();
                advance(it, ind < nset ? ind : (nset - 1)); // safe-guard if sizes differ
                string target_s = *it;
                auto start = chrono::high_resolution_clock::now();
                data_set.erase(target_s);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[run][3][2] = duration.count();
            }
        }
        for (int op = 0; op < ROWS; ++op)
            for (int st = 0; st < COLS; ++st)
                if (results[run][op][st] >= 0) //If this operation is inapplicable (e.g., sort on set stored as -1),
                // skip adding that to the accumulator and i won't include it when averaging.
                    accum[op][st] += results[run][op][st];

    }

    double averages[ROWS][COLS];
    for (int op = 0; op < ROWS; ++op) {
        for (int st = 0; st < COLS; ++st) {
            if (op == 1 && st == 2) { // sort on set marked as -1
                averages[op][st] = -1.0;
            } else {
                // For simplicity we divide by NUM_RUNS even if some runs had -1 (not timed)
                averages[op][st] = static_cast<double>(accum[op][st]) / static_cast<double>(NUM_RUNS);
            }
        }
    }

    // Nicely print results
    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << endl;
    cout << "Number of simulations: " << NUM_RUNS << endl << endl;
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List" << setw(W1) << "Set" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << setw(W1) << labels[i];
        for (int j = 0; j < COLS; j++) {// print each average
            if (averages[i][j] < 0)
                cout << setw(W1) << -1;
            else
                cout << setw(W1) << static_cast<long long>(averages[i][j] + 0.5); // rounded microseconds 
        }
        cout << endl;
    }

    cout << endl << "Done. Averages above are in microseconds." << endl;
    return 0;
    
    // Print averaged results
    
}