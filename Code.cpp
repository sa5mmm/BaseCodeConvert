#include <iostream>
#include <string>
#include <math.h>
using namespace std;


void populateCharValue();
void Settings();
string ConvertCode(string str);
int Base2Decimal(string str);
string Decimal2Base (int num);
char NumToChar (int num);
string ConvertMessage(string str);
int CharToNum(char car);

const int ARRAYMAX = 62;
const int ASCIIAValue = 65;
const int ASCIIaValue = 97;
const int ASCII0Value =48;
const int MAXBASE = ARRAYMAX+1;


char charArray[ARRAYMAX];
int base = 16;


int main()
{
	int attempts =0;
	string input ="";
	string userAction ="";
	string result ="";
	
	//populate the Value Table
	populateCharValue();
	
	
	
	while(userAction != "end")
	{
		cout << "What do you want to do?" << endl << "\tSettings (settings)\n\tConvert Code (code)\n\tConvert Message (message)\n\tEnd Program (end)"<<endl;
		
		cin >> userAction;
		
		if(userAction == "settings")
		{
			attempts = 0;//If the user starts using the program I don't want to knock them down for any typos.
			Settings();
		}else if(userAction == "code")
		{
			attempts = 0;
			cout << "You are going to convert a code in base "<< base << " into a message." << endl << "Please enter the code below: ";
			cin.ignore(1000, '\n');//Without this statement the user wasn't able to type their response
			getline (cin,input);
			
			result = ConvertCode(input);

			cout << endl << endl << result << endl << endl;//This used to be at the end but I think I might have it be posted into a text editor instead of to the console.
		}else if(userAction == "message")
		{
			attempts =0;
			cout << "You are going to convert a message into a code in base " << base << "." <<endl <<"Please enter the message below: "<<endl;
			cin.ignore(1000, '\n');
			getline (cin,input);
			result = ConvertMessage(input);
			
			cout << endl <<endl <<result << endl << endl;
			
		}else if(userAction == "end")
		{
			
		}else//User puts in some other option not mentioned (Only get 5 attempts before program ends)
		{
			if (attempts == 5)
			{
				userAction = "end";
			}else
			{
				cout << "Invalid action please try again (they are cAsEsEnSiTiVe do not include spaces or other characters)" << endl;
				attempts++;
			}
		}
	}
	
return 0;

}

string ConvertMessage(string str)
{
	string code = "";
	char working = ' ';
	string base = "";
	for (int i = 0; i < str.length(); i++)
	{
		working = str.at(i);
		base = Decimal2Base(CharToNum(working));
		code = code + base + " ";
	}
	return code;
}

string ConvertCode(string str)
{
	string message ="";
	string sub = "";
	int pos =0;
	int length = 0;
	//Locate phrases in the string (characters between spaces)
	//start at pos of string, find next space. take position of space minus start pos to get the length of the substring.
	while (pos + length <= str.length())//If the position of the space and the length of the substring are greater than the length of the initial string we have found all of the substrings
	{
		//Finds a Substring between the " "
		length = str.find(" ",pos) - pos;
		sub = str.substr(pos, length);
		//We must find the value of the substring Next and add that to the message
		message = message + NumToChar(Base2Decimal(sub));
		
		//Sets up the loop to find the next substring
		pos = str.find(" ",pos)+1;
		
	}
	return message;
}

int CharToNum (char car)//Right now this just returns the ASCII value for the char, but if I want to make it so that users can change what value a character is I need this function.
{
	int num =0;
	
	num = car;
	
	return num;
}

char NumToChar (int num)
{
	char car = ' ';
	if (num < 32 || num > 126) //These numbers are chosen based on the ASCII value table. I do not want to mess with any complicated whitespace values nor do I want to work with values that aren't even in the ASCII table.
	{
		car = ' ';
	} else
	{
		car = num;
	}
	return car;
}

void Settings()//Change the base to work in (Might change this function if I think of more settings that can be changed) (We might be able to make it so that users can choose the value of characters instead of just sticking with the ASCII values [Advanced Users Only])
{
	int num =0;
	while( num > MAXBASE || num < 2 )
	{
		cout << "What base would you like to work in?";
		cin >> num;
	}
	base = num;
	cout << "The base is set to " << base << "."<<endl;
}
//Convert from Base to Decimal
int Base2Decimal(string str)
{
	int num=0;
	for(int i = 0; i< str.length();i++)
	{
		for(int j=0;j<base;j++)
		{
			if(str.at(i) == charArray[j])
			num = num + j*pow(base,str.length()-1-i);
		}
	}
	return num;
}

//Convert from Decimal to Base
string Decimal2Base(int num)
{
	string value = "";
	int remainder =0;
	while (num != 0 || remainder >0)
	{
		remainder = num % base;
		if ( num ==0 && remainder == 0 )
		{
		}else 
		{
			value = charArray[remainder] + value;
			num = num/base;
		}
	}
	return value;
}


void populateCharValue()//This table is to figure out values of basenumbers I might make it so that users can choose what value of each character they want to use for their code (ex. in ASCII A is 65, but if users want they can make A = x where x is all real positive integers)
{
	for( int i=0;i<ARRAYMAX; i++)
	{
		
		if(i<10)//0-9 placed in the 0-9 slots of the array
		{
			charArray[i]= ASCII0Value+ i;
		}
		else if(i>=10 && i < 10+26)//A-Z placed in the 10-36 slots of the array
		{
			charArray[i] = ASCIIAValue+i-10;
		}else//a-z placed in the 37-62 slots of the array
			charArray[i] = ASCIIaValue+i-10-26;
	}
}