//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
std::string word;
#include <stdlib.h>
#include <fstream>
#include "emu.h"
#include "reg.h"

using namespace std;
int main(int argc,char** argv) {
	emulator emu;
	emu.execution(argv[1]);
	return EXIT_SUCCESS;
}
