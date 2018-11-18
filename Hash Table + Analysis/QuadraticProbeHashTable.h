// QuadraticProbeHashTable.h
//
// Created by Shaanan Curtis on 5/27/18.
// Copyright © 2018 SEC. All rights reserved.
//

#ifndef QuadraticProbeHashTable_h
#define QuadraticProbeHashTable_h
#include "RuntimeException.h"


//-----------------------------------------------------------
// Item (class)
//
//  Supports operations to set and get a (key,element) pair
//  Stores up to a single pair
//
// Private members: yes
// Protected members: no
// Public members: yes
// Default Constructors: Yes
// Constructors: Yes
//-----------------------------------------------------------
template <typename Key, typename Element>
class Item {                    // a (key, element) pair
private:
    Key        _key;                // key value
    Element   _elem;                // element
public:
    Item(const Key& k = Key(), const Element& e = Element())
    : _key(k), _elem(e) { }            // constructor
    const Key& key() const             // gets the key (read only)
    { return _key; }
    Element& element()                // gets the element
    { return _elem; }
    const Element& element() const         // gets the element (read only)
    { return _elem; }
    void setKey(const Key& k)            // sets the key value
    { _key = k; }
    void setElement(const Element& e)        // sets the element
    { _elem = e; }
};

// HASHTABLE EXCEPTIONS //

//------------------------------------------------
// HashTableFullException (class)
//
//  Class strictly defined for exception handling
//  if HashTableFull is thrown
//
// Private members: no
// Protected members: no
// Public members: yes
// Constructors: Yes
//------------------------------------------------
class HashTableFullException: public RuntimeException {
public:
    HashTableFullException(const string& err)
    : RuntimeException(err) { }
};

//------------------------------------------------
// NonexistentElementException (class)
//
//  Class strictly defined for exception handling
//  if NonexistentElement is thrown
//
// Private members: no
// Protected members: no
// Public members: yes
// Constructors: Yes
//------------------------------------------------
class NonexistentElementException: public RuntimeException {
public:
    NonexistentElementException(const string& err)
    : RuntimeException(err) { }
};

enum Status { EMPTY, USED, FREE };            // table entry status


//------------------------------------------------
// QuadraticProbeHashTable (class)
//
//  Demonstration of more advanced OOP to
//  achieve a functional Quadratic Probe Hash Table
//  i = h(key)
//  if occupied, i = ( h(key) + j*j ) MOD N
//               for j = 0, 1, 2, 3 , ...
//
// Private members: yes
// Protected members: yes
// Public members: yes
// Constructors: Yes
//------------------------------------------------
template <typename Key, typename Element, typename HashCmp>
class QuadraticProbeHashTable {
    
protected:                                                  // local types
    
    struct HashEntry : public Item<Key, Element> {          // a hash table entry
        Status status;                                      // entry status
        HashEntry(const Key& k = Key(),                     // constructor
                  const Element& e = Element(),
                  Status st = EMPTY)
        : Item<Key,Element>(k, e), status(st) { }
    };
    
    typedef HashEntry* EntryPtr;
    
public:                                                     // public types
    
    class Position {                                        // a hash table position
    private:
        EntryPtr node;                                      // pointer to entry
    public:
        Position(EntryPtr n = NULL)                         // constructor
        { node = n; }
        Element& element()                                  // get element
        { return node->element(); }
        const Key& key() const                              // get key
        { return node->key(); }
        bool isNull() const                                 // a null position?
        { return node == NULL; }
        friend class QuadraticProbeHashTable;               // give hash table access
    };
    
private:                                                    // member data
    int             n, N;                                   // size and capacity
    int             collisions;                             // total number of collisions per load factor
    EntryPtr        A;                                      // array of entries
    HashCmp        hash;                                    // the hash comparator
protected:                                                  // local utilities
    EntryPtr finder(const Key& key) const;                  // search utility
    EntryPtr inserter(const Key& key, const Element& e);    // insert utility
public:
    QuadraticProbeHashTable(int capacity = 100)             // constructor
    : n(0), N(capacity), collisions(0), hash() { A = new HashEntry[N]; }
    int size() const         { return n; }                  // size of dictionary
    bool isEmpty() const         { return (n == 0); }       // empty dictionary?
    
    int getCollisions() const {return collisions;}
    
    Position find(const Key& key) const                     // find a key
    {
        EntryPtr e = finder(key);
        if(e==NULL)
            throw NonexistentElementException("Key not found");
        
        return e;
        
    }
    
    void insertItem(const Key& key, const Element& element)
    throw(HashTableFullException)
    {
        EntryPtr e = inserter(key, element);                // attempt to insert
        if (e == NULL)                                      // failure
            throw HashTableFullException("Insertion into full hash table");
            }
    
    void removeElement(const Key& key)                      // remove using key
    throw(NonexistentElementException) {
        EntryPtr e = finder(key);                           // look up key
        if (e == NULL)                                      // not found?
            throw NonexistentElementException("Key not found");
        e->status = FREE;                                   // mark entry as free
        n--;                                                // decrease size
    }
    
    // ... (some functions omitted) ... //
    
};

// PROTECTED UTILITIES //

//------------------------------------------------
// finder (utility function)
//
// • Uses Quadratic Probing to search for an entry
//    with key k
//
// Params: passes an entry's key by reference
// I/O: none
// Returns: EntryPtr
//------------------------------------------------
template <typename Key, typename Element, typename HashCmp>
typename QuadraticProbeHashTable<Key, Element, HashCmp>::EntryPtr
QuadraticProbeHashTable<Key, Element, HashCmp>::
finder(const Key& key) const {                                      // search utility
    int j = 0;
    int i = hash.hashValue(key) % N;                                // get hash index
    int start = i;                                                  // starting point
    do
    {
        if (A[i].status == EMPTY) return NULL;                      // item is not found
        if (A[i].status == USED &&
            hash.isEqualTo(A[i].key(), key))                        // found it
            return &A[i];                                           // return with success
        i = (start + j*j) % N;                                      // try next slot
        j++;
    } while (i != start);                                           // until back to start
    return NULL;                                                    // return with failure
}

//------------------------------------------------
// inserter (utility function)
//
// • Uses Quadratic Probing to insert a (key,element)
//   pair
//
// Params: passes a full entry pair by reference
// I/O: outputs index of where entry was stored
//      and number of probes it took
//      to get there
// Returns: EntryPtr
//------------------------------------------------
template <typename Key, typename Element, typename HashCmp>
typename QuadraticProbeHashTable<Key, Element, HashCmp>::EntryPtr
QuadraticProbeHashTable<Key, Element, HashCmp>::
inserter(const Key& key, const Element& element)                    // insert utility
{
    int j = 0;
    int i = hash.hashValue(key) % N;                                // get hash index
    int start = i;                                                  // starting point
    do
    {
        if (A[i].status != USED)                                    // slot is available?
        {
            A[i] = HashEntry(key, element, USED);                   // store it here
            n++;                                                    // increase size
            cout << "Stored at Index = " << i << endl;
            cout << "Probes = " << j << endl;
            collisions+=j;
            return &A[i];                                           // return with success
        }
        i = (start + j*j) % N;                                     // try next slot
        j++;
    } while (i != start || j!=N);                                  // until back to start
    collisions+=j;
    return NULL;                                                   // return with failure
}


#endif /* QuadraticProbeHashTable_h */
