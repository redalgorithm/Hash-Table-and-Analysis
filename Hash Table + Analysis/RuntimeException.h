// RuntimeException.h
//
// Created by Shaanan Curtis on 5/27/18.
// Copyright © 2018 SEC. All rights reserved.
//

#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include<iostream>
#include<string>
using namespace std;

//------------------------------------------------
// RuntimeException (class)
//
//  Class strictly defined for exception handling
//  if a runtime error is thrown
//
// Private members: yes
// Protected members: no
// Public members: yes
// Constructors: Yes
//------------------------------------------------
class RuntimeException {			                // generic runtime exception
private:
	string errorMsg;
public:
	RuntimeException (const string& err) {errorMsg = err; }
	string getMessage() const { return errorMsg; }
};

inline ostream& operator << (ostream& out, const RuntimeException& e)
{ return out << e.getMessage(); }

#endif
