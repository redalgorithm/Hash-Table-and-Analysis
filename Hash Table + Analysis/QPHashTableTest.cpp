// QPHashTableTest.cpp
//
// Created by Shaanan Curtis on 5/27/18.
// Copyright © 2018 SEC. All rights reserved.
//
/*
 This program demonstrates a Hash Table data structure using
 open addressing for collision resolution
 
 Particularly, the Quadratic Probe resolution scheme
 */

#include <ctime>
#include <cmath>
#include <cctype>
#include <iostream>
#include <fstream>
#include "QuadraticProbeHashTable.h"
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
class intKey    //comparison class for integer keys
{
public:
    int hashValue(const int& key) const{
        return key;
    }
    bool isEqualTo(const int& key1, const int& key2) const{
        return (key1==key2);
    }
};

//=========================================//

// MAIN PROGRAM //

//*****************************************//

int main()
{
    char y;
    int count=0;
    long int ave = 0;
    
do{
    
    {
        srand((unsigned int)time(NULL));        // seed the pseudo random number generator
    
        string filename;
        ofstream outFile;
        int numVals;
        const int numDigits = 6;
    
        cout << "This program generates random numbers and writes them to a file.\n\n";
        filename = "randNum.txt";
        
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
        
    
        outFile.open(filename);
        if (outFile.fail())
        {
            cout << "Unable to open '" << filename << "' for writing ... exiting ...\n";
            exit(23);
        } else
        {
            cout << "Successful open of '" << filename << "' for writing\n\n";
        }
    
        cout << "Enter number of values to generate (> 0): ";
        cin >> numVals;
        
///////////////////////////optional//////////////////////////////////
/*
    cout << "Enter max number of digits per value (1 .. 9): ";
    cin >> numDigits;
*/
////////////////////////////////////////////////////////////////////
        
    
        int maxVal = pow(10,numDigits);
    
        for (int i = 0; i < numVals; i++)
        {
            outFile << rand()%maxVal << endl;
        }
        outFile.close();
    
        cout << "Finished\n\n";
    //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
        cout << "\n\nQUADRATIC PROBE HASH TABLE DEMO\n\n";
    
        const int N = 997;
        QuadraticProbeHashTable <int,int,intKey> hTable(N);                // table size is N
    
        typedef QuadraticProbeHashTable<int,int,intKey>::Position HashPos;
    
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
                hTable.insertItem(k[i],k[i]);                           // using equal (key,value) pair for feasability
            } catch (RuntimeException str)
            {
                cout << str.getMessage();
            }
        
            i++;
        }
        cout << endl;
        cout << "Total Collisions: " << hTable.getCollisions() << endl;
        count++;
        ave+=hTable.getCollisions();
        if(count==3)
        {
            cout << "Average Collisions (out of 3) = " << ave/3 << endl;
            count = 0;
            ave = 0;
        }
        
        inFile.clear();
        inFile.close();
    }
    
    //=========================================================================
    //=========================================================================
    //=========================================================================
    // make sure to comment out the prior demonstration before uncommenting this one
    // to avoid confusion for now
    /*
     {
         cout << "\n\nLINEAR PROBE HASH TABLE FULL DEMO\n\n";
     
         const int N = 37;
         QuadraticProbeHashTable <int,int,intKey> hTable(N); // table size is N
     
         typedef QuadraticProbeHashTable<int,int,intKey>::Position HashPos;
         HashPos pos;
     
         int k = 5;
         hTable.insertItem(k,k);
         try
         {
             pos = hTable.find(k);
             cout << "after searching for key " << k << ", found key = " << pos.key() << endl;
             
         } catch (RuntimeException str)
         {
             cout << str.getMessage();
         }
     
         // insert a collision key
         hTable.insertItem(k+N,k+N);
         // check that original 5 is still findable
         try
         {
             pos = hTable.find(k);
             cout << "<checking if original " << k << " is still findable>\n";
             cout << "after searching for key " << k << ", found key = " << pos.key() << endl;
             pos = hTable.find(k+N);
             cout << "after searching for key " << k << "+N, found key = " << pos.key() << endl;
             
         } catch (RuntimeException str)
         {
             cout << str.getMessage();
         }
     
         // check that collision key is findable
         
     
         // remove original key
         try
         {
             hTable.removeElement(k);
             pos = hTable.find(k);
             
         } catch (RuntimeException str)
         {
             cout << str.getMessage();
         }
         
     
         // check that removed key is gone
         
         if (pos.isNull())
         {
             cout << "successful removal of " << k << " from hash table\n";
         } else
         {
             cout << "Error! should not be able to find " << k << " after removal\n";
         }
     
         // check that collision key is still findable
         try
         {
             pos = hTable.find(k+N);
             cout << "after removal of " << k << ", searching for key " << k << "+N, found key = " << pos.key() << endl;
             
         } catch (RuntimeException str)
         {
             cout << str.getMessage();
         }
         
        }
    */
        cout << "continue? (y/n): ";
        cin >> y;
}while(toupper(y)=='Y');
    return 0;
}


