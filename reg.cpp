
#include "reg.h"
using namespace std;

void halo (void)
	{
		//puts("Hello World");
	}
int convert_to_decimalu (string s)	//for the cases : 0x AB CD or oxAB CD or ox ABCD
		{
			int i = 2 ;
			int sum = 0;
			for(;i<s.size();i++)
			{
				sum = sum*16 + (hex_to_int(s[i]));
			}
//			cout << "returning sum:" <<sum <<endl;
			return sum;
		}
int convert_to_decimal (string s)	//for the cases : 0x AB CD or oxAB CD or ox ABCD
		{
//	cout<<"calling ox - decimal"<<s[3]<<endl;
			int i = 2 ;
			int sum = 0;
			for(;i<s.size();i++)
			{
			//	cout <<sum<<"s[i]:"<<s[i]<<endl;
				sum = sum*16 + (hex_to_int(s[i]));
			}
			if(s[2]=='8'||s[2]=='9'||s[2]=='a'||s[2]=='A'||s[2]=='b'||s[2]=='B'||s[2]=='c'||s[2]=='C'||s[2]=='d'||s[2]=='D'||s[2]=='e'||s[2]=='E'||s[2]=='f'||s[2]=='F')
				{
			//	cout<<endl<<sum<<"sum decrement"<<endl;
				sum = sum - pow(2,16);
				}
//				cout << "returning sum:" <<sum <<endl;
			return sum;
		}


int hex_to_int (char a)
		{
			if (a =='0')
				{
					return 0;
				}
			else if (a == '1')
				{
					return 1;
				}
			else if (a == '2')
				{
					return 2;
				}

			else if (a == '3')
				{
				return 3;
				}
			else if (a == '4')
				{
				return 4;
				}
			else if (a == '5')
				{
				return 5;
				}
			else if (a == '6')
				{
				return 6;
				}
			else if (a == '7')
				{
				return 7;
				}
			else if (a == '8')
				{
				return 8;
				}

			else if (a == '9')
				{
				return 9;
				}
			else if (a == 'a'||a=='A')
				{
				return 10;
				}
			else if (a == 'b'||a=='B')
				{
				return 11;
				}
			else if (a == 'c'||a=='C')
				{
				return 12;
				}
			else if (a == 'd'||a=='D')
				{
				return 13;
				}
			else if (a == 'e'||a=='E')
				{
				return 14;
				}
			else if (a == 'f'||a=='F')
				{
				return 15;
				}
			else
				{
//				cout <<a<<"not of proper format #hextoint"<<a<<endl;
				return -1;
				}
		}
//bool checklabel (vector<string>test)
//	{
//		int j = test[0].size();
//		string s =test[0];
//		if(s[j]==':')
//			{
//			return true ;
//			}
//		else
//			return false;
//	}
bool check_label (string s)
	{
		//cout<<"ssssss";
		int j   = s.size();
		if(s[j-1]==':')
			{
				return true;
			}
		return false;
	}
int registernumber (string s)
		{
			char const *c = s.c_str() ;		//REMEMBER
				//c=s;
			if (strcmp(c,"r0")==0)
				{
					return 0;
				}
			else if (strcmp(c,"r1")==0)
				{
					return 1;
				}
			else if (strcmp(c,"r2")==0)
				{
					return 2;
				}
			else if (strcmp(c,"r3")==0)
				{
					return 3;
				}
			else if (strcmp(c,"r4")==0)
				{
					return 4;
				}
			else if (strcmp(c,"r5")==0)
				{
					return 5;
				}
			else if (strcmp(c,"r6")==0)
				{
					return 6;
				}
			else if (strcmp(c,"r7")==0)
				{
					return 7;
				}
			else if (strcmp(c,"r8")==0)
				{
					return 8;
				}
			else if (strcmp(c,"r9")==0)
				{
					return 9;
				}
			else if (strcmp(c,"r10")==0)
				{
					return 10;
				}
			else if (strcmp(c,"r11")==0)
				{
					return 11;
				}
			else if (strcmp(c,"r12")==0)
				{
					return 12;
				}
			else if (strcmp(c,"r13")==0)
				{
					return 13;
				}
			else if (strcmp(c,"r14")==0|| (strcmp(c,"sp")==0))
				{
					return 14;
				}
			else if (strcmp(c,"ra")==0 || (strcmp(c,"r15")==0))
				{
					return 15;
				}
			else
				{
//					cout <<"not of proper format"<<c<<endl;
					return -1;
				}
		}
int isregister_or_isimmidiate (string s)//what for number
		{
			//char *c = s;
			//cout << "received " <<s <<endl;
			if((s[0] == 'o'||s[0]=='0')&&s[1]=='x')		//ox or 0x
				{
					return 1;
				}
			else if (s[0] == 'r'||(s[0]=='s'&&s[1]=='p'))
				{
					return 2;
				}
			else
				{
					return -1;
				}
		}

//int add (std::vector<std::string>test)
//{
//		int i = registernumber(test[1]);
//		int j = registernumber(test[2]);
//		int immi ;
//		istringstream convert(test[3]);
//		if(i!=-1&&j!=-1)
//			{
//				if(isregister_or_isimmidiate(test[3]) == 2)	//it is register
//				{
//					immi = ;//registers[registernumber(test[3])];
//				}
//				else if(isregister_or_isimmidiate(test[3]) ==1)	//it is ox .....
//				{
//					cout<<i<<" "<<j<<"sum is:"<<convert_to_decimal(test[3]+test[4]+test[5]);
//				}
//				else	if(!(convert >> immi))		// it is not number
//					{
//					cout << "wrong format";
//					}
//				else	// it is number stored in immi
//					{
//						cout <<immi<<"asdiamsdimdmdams";
//					}
//			}
//}


