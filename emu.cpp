#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "reg.h"
#include <vector>
#include <exception>
#include <map>
//#include "hashtable.cpp"
using namespace std;

class emulator {
private:

	int memory[1024]; //=new int [4096];  multiples of 4
	int registers[16] ;
	int pc ;
	int ra ; // not to be used
	bool flag_EQ ;
	bool flag_BGT ;
	int sp ; // sp = ox FFC
	bool main_encountered ;
	std::map<string,int> hash;

public:

	vector<string> linestorage;		//stores line of files in the vector form
	emulator() {
		int registers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4092, 0 };
			int pc = 0;
			int ra = 0; // not to be used
			bool flag_EQ = false;
			bool flag_BGT = false;
			int sp = 4092; // sp = ox FFC
			bool main_encountered = false;
	}
	void realfile(char * filename)		//call it to read the file once
			{
		ifstream mystream;
		char* currentline = new char[256];
		mystream.open(filename);
		if (mystream.fail()) {
			puts("Loading failed");
			return;
		} else {
			int i = 0;
			while (!mystream.eof()) {
				i++;
				mystream.getline(currentline, 256);
				std::vector<std::string> test(7);
				test = scan_line_return_char_array(currentline);
				if( check_label(test[0]))
					{
							string s ="";
							for(int j=0;j<test[0].size()-1;j++)
								{
									s = s+ test[0][j] + "";
								}
							hash[s]=i-1;
					}

				linestorage.push_back(currentline);	//test[0]+test[1]+test[2]+test[3]+test[4]+test[5]);
			}
		}
	//	cout <<"yoyo pc"<<hash.find(".main")->second<<endl;
	}
	void execution(char * filename) {
		realfile(filename);
		pc =  hash[".main"];
		registers[14]=4092;
		//cout<<"pc is:"<<pc<<" "<<registers[14]<<endl;
		if (pc != -1) {
			while (pc < linestorage.size()) {
				compare21(scan_line_return_char_array(linestorage[pc]));
			}
		} else {
			cout << "Main not found";
		}
	}
	void compare21(std::vector<std::string> test)	//assuming capital letters
			{
		if (test[0] == "ADD" || test[0] == "add") {
			ADD(test);
		} else if (test[0] == "ADDU" || test[0] == "addu") {
			ADDU(test);
		} else if (test[0] == "ADDH" || test[0] == "addh") {
			ADDH(test);
		} else if (test[0] == "SUB" || test[0] == "sub") {
			SUB(test);
		} else if (test[0] == "SUBU" || test[0] == "subu") {
			SUBU(test);
		} else if (test[0] == "SUBH" || test[0] == "subh") {
			SUBH(test);
		} else if (test[0] == "MUL" || test[0] == "mul") {
			MUL(test);
		} else if (test[0] == "MULU" || test[0] == "mulu") {
			MULU(test);
		} else if (test[0] == "MULH" || test[0] == "mulh") {
			MULH(test);
		} else if (test[0] == "DIV" || test[0] == "div") {
			DIV(test);
		} else if (test[0] == "DIVU" || test[0] == "divu") {
			DIVU(test);
		} else if (test[0] == "DIVH" || test[0] == "divh") {
			DIVH(test);
		} else if (test[0] == "MOD" || test[0] == "mod") {
			MOD(test);
		} else if (test[0] == "MODU" || test[0] == "modu") {
			MODU(test);
		} else if (test[0] == "MODH" || test[0] == "modh") {
			MODH(test);
		} else if (test[0] == "CMP" || test[0] == "cmp") {
			CMP(test);
		} else if (test[0] == "CMPU" || test[0] == "cmpu") {
			CMPU(test);
		} else if (test[0] == "CMPH" || test[0] == "cmph") {
			CMPH(test);
		} else if (test[0] == "AND" || test[0] == "and") {
			AND(test);
		} else if (test[0] == "ANDU" || test[0] == "andu") {
			ANDU(test);
		} else if (test[0] == "ANDH" || test[0] == "andh") {
			ANDH(test);
		} else if (test[0] == "OR" || test[0] == "or") {
			OR(test);
		} else if (test[0] == "ORU" || test[0] == "oru") {
			ORU(test);
		} else if (test[0] == "ORH" || test[0] == "orh")		//24th ifelse
				{
			ORH(test);
		} else if (test[0] == "NOT" || test[0] == "not") {
			NOT(test);
		} else if (test[0] == "NOTU" || test[0] == "notu") {
			NOTU(test);
		} else if (test[0] == "NOTH" || test[0] == "noth") {
			NOTH(test);
		} else if (test[0] == "MOV" || test[0] == "mov") {
			MOV(test);
		} else if (test[0] == "MOVU" || test[0] == "movu") {
			MOVU(test);
		} else if (test[0] == "MOVH" || test[0] == "movh") {
			MOVH(test);
		} else if (test[0] == "LSL" || test[0] == "lsl") {
			LSL(test);
		} else if (test[0] == "LSR" || test[0] == "lsr") {
			LSR(test);
		} else if (test[0] == "ASR" || test[0] == "asr") {
			ASR(test);
		} else if (test[0] == "NOP" || test[0] == "nop") {
			;
		} else if (test[0] == "LD" || test[0] == "ld") {
			LDR(test);
		} else if (test[0] == "ST" || test[0] == "st" || test[0] == "STR"
				|| test[0] == "str") {
			STR(test);
		} else if (test[0] == "BEQ" || test[0] == "beq") {
			if(flag_EQ)
			{
				pc = hash[test[1]];//.find(test[1])->second;
				return;
			}
		}else if (test[0] == "BGT" || test[0] == "bgt") {
			if(flag_BGT)
			{
				pc = hash[test[1]];//.find(test[1])->second;
				return;
			}
		} else if (test[0] == "B" || test[0] == "b") {
			{
				pc = hash[test[1]];//.find(test[1])->second;
				return;
			}
		} else if (test[0] == "CALL" || test[0] == "call") {
			{
				registers[15] =  pc+1;
				pc = hash[test[1]];//.find(test[1])->second;
				return;
			}
		} else if (test[0] == "RET" || test[0] == "ret" || test[0] == ".ret"
				|| test[0] == ".RET") {
			{
				pc = registers[15];
				return;
			}
		} else if (test[0] == ".PRINT" || test[0] == ".print") {
				callprint(test);
		}
		else
			{
			if( check_label(test[0]))	// as the instruction can be in same line.
		{
			std::vector <std::string> tst(test.size()-1) ;
			for(int i= 0  ; i < test.size()-1;i++)
				{
					tst[i] = test[i+1];
				}
			compare21(tst);
			return;
		}
			else
				{
				}
			}

		pc++;
	}

	int returnnumber(int i) // i assumed to be correct ;
			{
		return registers[i];
	}

	int returnnumber(string s)		// not to be used by source register
			{
		char const *c = s.c_str();
		if (strcmp(c, "r0") == 0) {
			return registers[0];
		} else if (strcmp(c, "r1") == 0) {
			return registers[1];
		} else if (strcmp(c, "r2") == 0) {
			return registers[2];
		} else if (strcmp(c, "r3") == 0) {
			return registers[3];
		} else if (strcmp(c, "r4") == 0) {
			return registers[4];
		} else if (strcmp(c, "r5") == 0) {
			return registers[5];
		} else if (strcmp(c, "r6") == 0) {
			return registers[6];
		} else if (strcmp(c, "r7") == 0) {
			return registers[7];
		} else if (strcmp(c, "r8") == 0) {
			return registers[8];
		} else if (strcmp(c, "r9") == 0) {
			return registers[9];
		} else if (strcmp(c, "r10") == 0) {
			return registers[10];
		} else if (strcmp(c, "r11") == 0) {
			return registers[11];
		} else if (strcmp(c, "r12") == 0) {
			return registers[12];
		} else if (strcmp(c, "r13") == 0) {
			return registers[13];
		} else if (strcmp(c, "r14") == 0 || (strcmp(c, "sp") == 0)) {
			return registers[14];
		} else if (strcmp(c, "ra") == 0 || (strcmp(c, "r15") == 0)) {
			return registers[15];
		} else {
//			cout << "not of proper format";
			return -1;
		}
	}
	void tympas(void) {
		int i = 0;
		while (i < linestorage.size()) {
//			cout << linestorage[i] << endl;
			i++;
		}
	}
	std::vector<std::string> scan_line_return_char_array(string currentline)//returns segregated words
			{
		char e = currentline[0];
		int i = 0;
		int no = 0;
		bool word = false;
		std::vector<std::string> carray(7);
		string buff = "";
		for (i = 0; i < currentline.length() && no < 7; i++) {
			e = currentline[i];
			if (e == ' ' || e == ',' || e == ';' || e =='['||e ==']'||e == ':'||e=='\t') {	//
				if (word == true) {
					if(e == ':')
					{
						carray[no] = buff + e + "";
					}
					else
						{
						carray[no] = buff;
						}
					no++;
				}
				word = false;
				buff = "";
			} else {
				buff = buff + e + "";
				word = true;
			}
		}
		if (no <= 7) {
			if (word) {
				carray[no] = buff;
			}
		} else {
//			cout << "error too many ";
		}
		return carray;
	}

	int return_immiu(vector<string> test, int i) {
		int immi;
		istringstream convert(test[i]);
		if (isregister_or_isimmidiate(test[i]) == 2)	//it is register
				{
			immi = registers[registernumber(test[i])];
		} else if (isregister_or_isimmidiate(test[i]) == 1)	//it is ox .....
				{
			immi = convert_to_decimalu(test[i] + test[i + 1] + test[i + 2]);
		} else if (!(convert >> immi))		// it is not number
		{
			throw 20;
		} else	// it is number stored in immi
		{
			if (immi < 0)
				immi = -immi;
		}
		return immi;
	}
	int return_immih(vector<string> test, int i) {
		int immi;
		istringstream convert(test[i]);
		if (isregister_or_isimmidiate(test[i]) == 2)	//it is register
				{
			immi = registers[registernumber(test[i])];
		} else if (isregister_or_isimmidiate(test[i]) == 1)	//it is ox .....
				{
			immi = convert_to_decimalu(test[i] + test[i + 1] + test[i + 2])
					* pow(2, 16);
		} else if (!(convert >> immi))		// it is not number
		{
//			cout << "wrong format";
			throw 20;
		} else	// it is number stored in immi
		{
			immi = immi * pow(2, 16);
		}
		return immi;
	}
	int return_offset_for_load_store (vector <string>test)
	{
		istringstream convert(test[2]);
		int immi;
		if(isregister_or_isimmidiate(test[2]) == 2)		// it is register
			{
				immi = registers[registernumber(test[2])];
			}
		else if(isregister_or_isimmidiate(test[2]) == 1)	//it is ox
			{
				string asd = "";
				int sum = 0;
				string s = test[2]+test[3]+test[4]+test[5];
				for(int i =2;i<s.size() ;i++)
					{
						if(hex_to_int (s[i])>=0)
							{
								sum = sum * 16 + hex_to_int (s[i]);
							}
						else
							{
							asd =  asd +s[i] + "";
							}
					}
				immi = sum + registers[registernumber(asd)];
			}
		else if (!(convert >> immi))
			{
//				cout <<"wrong";
			}
		else	//test[2] is a number -> test[3] is r/sp
			{
				immi = immi + registers[registernumber(test[3])];
			}
		return immi;
	}

	int return_immi(vector<string> test, int i)	// returns only 3rd immidiate
			{
		int immi;
		istringstream convert(test[i]);
		if (isregister_or_isimmidiate(test[i]) == 2)	//it is register
				{
			immi = registers[registernumber(test[i])];
		} else if (isregister_or_isimmidiate(test[i]) == 1)	//it is ox .....
				{
			immi = convert_to_decimal(test[i] + test[i + 1] + test[i + 2]);
		} else if (!(convert >> immi))		// it is not number
		{
			throw 20;
		} else	// it is number stored in immi
		{
		}
		return immi;
	}

	void ADD(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] + return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg <<"add"<< endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void ADDU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] + return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void ADDH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] + return_immih(test, 3);
			} catch (int msg) {
//				cout << msg<<"msg"<<endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void MUL(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] * return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg <<"mul" << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void SUB(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] - return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg <<"sub"<< endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void DIV(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] / return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg <<" div"<< endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void MOD(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] % return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg<<"mod" << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void AND(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] & return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg<<"snd" << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void OR(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] | return_immi(test, 3);	//as add is 3 format
			} catch (int msg) {
//				cout << msg <<"or"<< endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void NOT(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				registers[i] = ~(return_immi(test, 2));		//as add is 3 format
			} catch (int msg) {
//				cout << msg<<"not" << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void LSR(vector<string> test) //adds 2^32 to a negative number
			{
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = unsigned(registers[j]) >> return_immi(test, 3); //as add is 3 format
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void ASR(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = signed(registers[j]) >> return_immi(test, 3); //as add is 3 format
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void LSL(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] << return_immi(test, 3); //as add is 3 format
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void MOV(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				registers[i] = return_immi(test, 2);	//as add is 3 format
			} catch (int msg) {
//				cout << msg<<"mov" << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
	void LDR(vector<string> test) {
			int i = registernumber(test[1]);
			int dest ;
			if (i != -1) {
				try {
					dest = return_offset_for_load_store (test)/4;//return_immiu(test, 2)/4;	//as add is 3 format
					if((dest>=0) && (dest<1024))
						{
							registers[i]=memory[dest];
						}
					else
						{
//						cout << "memory overflow";
						}
				} catch (int msg) {
					cout << msg << endl;
				}
			} else {
//				cout << "wrong input";
			}
		}

	void STR(vector<string> test) {	//also include offset
				int i = registernumber(test[1]);
				int dest ;
				if (i != -1) {
					try {
						dest = return_offset_for_load_store (test)/4; //return_immiu(test, 2)/4;	//as add is 3 format
						if(0<dest<1024)
							{
								memory[dest] = registers[i];
							}
					} catch (int msg) {
//						cout << msg <<"error"<< endl;
					}
				} else {
//					cout << "wrong input";
				}
			}
	void callprint (vector <string> test)
	{
		int i = registernumber(test[1]);
		cout <<registers[i]<<endl;
	}
	void CMP(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				if (registers[i] >= return_immi(test, 2)) {
					if (registers[i] == return_immi(test, 2))//as add is 3 format
							{
						flag_EQ = true;
						flag_BGT = false;
					} else {
						flag_EQ = false;
						flag_BGT = true;
					}
				} else {
					flag_EQ = false;
					flag_BGT = false;
				}
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}

	void MULU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] * return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void SUBU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] - return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void DIVU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] / return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void MODU(vector<string> test) {
//		cout << "modu" << endl;
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] % return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void ANDU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] & return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void ORU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] | return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void NOTU(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1)
			try {
				registers[i] = ~(return_immiu(test, 2));
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}

	void LSLU(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		istringstream convert(test[3]);
		if (i != -1 && j != -1)
			try {
				registers[i] = registers[j] | return_immiu(test, 3);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void MOVU(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1)
			try {
				registers[i] = return_immiu(test, 2);
			} catch (int msg) {
//				cout << msg << endl;
			}
		else {
//			cout << "wrong input";
		}
	}
	void CMPU(vector<string> test) {
//		cout << "CMPU" << endl;
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				if (registers[i] >= return_immiu(test, 2)) {
					if (registers[i] == return_immiu(test, 2))//as add is 3 format
							{
						flag_EQ = true;
						flag_BGT = false;
					} else {
						flag_EQ = false;
						flag_BGT = true;
					}
				} else {
					flag_EQ = false;
					flag_BGT = false;
				}
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}

	void MULH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] * return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void SUBH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] - return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void DIVH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] / return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void MODH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] % return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void ANDH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] & return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void ORH(vector<string> test) {
		int i = registernumber(test[1]);
		int j = registernumber(test[2]);
		if (i != -1 && j != -1) {
			try {
				registers[i] = registers[j] | return_immih(test, 3);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void NOTH(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				registers[i] = ~(return_immih(test, 3));
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void MOVH(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				registers[i] = return_immih(test, 2);
			} catch (int msg) {
//				cout << "msg";
			}
		} else {
//			cout << "wrong input";
		}
	}
	void CMPH(vector<string> test) {
		int i = registernumber(test[1]);
		if (i != -1) {
			try {
				if (registers[i] >= return_immih(test, 2)) {
					if (registers[i] == return_immih(test, 2))//as add is 3 format
							{
						flag_EQ = true;
						flag_BGT = false;
					} else {
						flag_EQ = false;
						flag_BGT = true;
					}
				} else {
					flag_EQ = false;
					flag_BGT = false;
				}
			} catch (int msg) {
//				cout << msg << endl;
			}
		} else {
//			cout << "wrong input";
		}
	}
};
