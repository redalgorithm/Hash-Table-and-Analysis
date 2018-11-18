// HashTableTest.cpp
//
// Created by Shaanan Curtis on 5/27/18.
// Copyright © 2018 SEC. All rights reserved.
//
/*
   This program demonstrates a Hash Table data structure using
   open addressing for collision resolution
 
   Particularly, the Linear Probe resolution scheme
*/

/*//-------------->>DELETE THIS LINE (cannot run more than one main program at a time: comment one) <<----------------
//                              comment out HashTableTest.cpp or QPHashTableTest.cpp
 
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include "LinearProbeHashTable.h"
using namespace std;

//-----------------------------------------------------------
// intKey (class)
//
//  Represents h(k)
//  Comparison class for integer keys
//
// Private members: no
// Protected members: no
// Public members: yes
// Constructors: no
//-----------------------------------------------------------
class intKey
{
    public:
        int hashValue(const int& key) const{
            return key;
        }
        bool isEqualTo(const int& key1, const int& key2) const{
            return (key1==key2);
        }
};
*///-------------->>DELETE THIS LINE <<----------------
//=========================================//

// MAIN PROGRAM //

//*****************************************//
/*//-------------->>DELETE THIS LINE <<----------------
int main()
{
    int count = 0;
    int ave = 0;
    char y;
do{
    
    {
        srand((unsigned int)time(NULL));        // seed the pseudo random number generator

        string filename;
        ofstream outFile;
        int numVals;
        const int numDigits = 6;

        cout << "This program generates random numbers and writes them to a file.\n\n";
        filename = "randNum.txt";
 
*///-------------->>DELETE THIS LINE <<----------------

////////////////////////////optional//////////////////////////////////
/*
cout << "Enter output filename <randNum.txt> with no spaces in the filename: ";
cin >> filename;
if (filename[0] == '\0')
{
    filename = "randNum.txt";
}
*/
/////////////////////////////////////////////////////////////////////

/*//-------------->>DELETE THIS LINE <<----------------
 
        outFile.open(filename);
        if (outFile.fail())
        {
            cout << "Unable to open '" << filename << "' for writing ...    exiting ...\n";
            exit(23);
        } else
        {
            cout << "Successful open of '" << filename << "' for writing\n\n";
        }

        cout << "Enter number of values to generate (> 0): ";
        cin >> numVals;

*///-------------->>DELETE THIS LINE <<----------------

///////////////////////////optional//////////////////////////////////
/*
cout << "Enter max number of digits per value (1 .. 9): ";
cin >> numDigits;
*/
////////////////////////////////////////////////////////////////////

/*//-------------->>DELETE THIS LINE <<----------------
 
        int maxVal = pow(10,numDigits);

        for (int i = 0; i < numVals; i++)
        {
            outFile << rand()%maxVal << endl;
        }
        outFile.close();

        cout << "Finished\n\n";
    //((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    //))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
        cout << "\n\nLINEAR PROBE HASH TABLE DEMO\n\n";
    
        const int N = 997;
        LinearProbeHashTable <int,int,intKey> hTable(N);          // table size is N
    
        typedef LinearProbeHashTable<int,int,intKey>::Position HashPos;
    
        ifstream inFile;
        inFile.open(filename);
        if (inFile.fail())
        {
            cout << "Unable to open '" << filename << "' for reading ... exiting ...\n";
            exit(23);
        } else
        {
            cout << "Successful open of '" << filename << "' for reading\n\n";
        }
    
        int k[numVals];
        int i=0;
        while(!inFile.eof())
        {
            inFile >> k[i];
            try
            {
                hTable.insertItem(k[i],k[i]);                    // using equal (key,value) pair for feasability
            } catch (RuntimeException str)
            {
                cout << str.getMessage();
            }
        
            i++;
        }
        cout << endl;
        cout << "Total Collisions: " << hTable.getCollisions() << endl;
        ave+=hTable.getCollisions();
        count++;
        if(count==3)
        {
            cout << "Average Collisions (out of 3) = " << ave/3 << endl;
            count = 0;
            ave = 0;
        }
        inFile.clear();
        inFile.close();
    }
 
*///-------------->>DELETE THIS LINE <<----------------

    //=====================================================================
    //=====================================================================
    //=====================================================================
    // make sure to comment out the prior demonstration before uncommenting this one
    // to avoid confusion for now
    /*
    {
        cout << "\n\nLINEAR PROBE HASH TABLE FULL DEMO\n\n";
        
        const int N = 37;
        LinearProbeHashTable <int,int,intKey> hTable(N); // table size is N
        
        typedef LinearProbeHashTable<int,int,intKey>::Position HashPos;
        HashPos pos;
        
        int k = 5;
        hTable.insertItem(k,k);
        pos = hTable.find(k);
        cout << "after searching for key " << k << ", found key = "
        << pos.key() << endl;
    
        // insert a collision key
        hTable.insertItem(k+N,k+N);
        // check that original 5 is still findable
        pos = hTable.find(k);
        cout << "<checking if original " << k << " is still findable>\n";
        cout << "after searching for key " << k << ", found key = "
        << pos.key() << endl;
        
        // check that collision key is findable
        pos = hTable.find(k+N);
        cout << "after searching for key " << k << "+N, found key = "
        << pos.key() << endl;
    
        // remove original key
        hTable.removeElement(k);
    
        // check that removed key is gone
        pos = hTable.find(k);
        if (pos.isNull())
        {
            cout << "successful removal of " << k << " from hash table\n";
        } else
        {
            cout << "Error! should not be able to find " << k << " after removal\n";
        }
    
        // check that collision key is still findable
        pos = hTable.find(k+N);
        cout << "after removal of " << k << ", searching for key " << k << "+N, found key = "
        << pos.key() << endl;
    }
    */

/*//-------------->>DELETE THIS LINE <<----------------
 
    cout << "continue? (y/n): ";
    cin >> y;
}while(toupper(y)=='Y');
    return 0;
}
 
*///-------------->>DELETE THIS LINE <<----------------

