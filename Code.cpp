#include <iostream>
#include <string>
#include <math.h>
using namespace std;


void populateBaseValues();
void populateCharArray();
void Settings();


string ConvertCode(string str);
string ConvertMessage (string str);


int Base2Decimal(string str);
string Decimal2Base (int num);
char NumToChar (int num);
int CharToNum(char car);

const int ARRAYMAX = 62;
const int ASCIIAValue = 65;
const int ASCIIaValue = 97;
const int ASCII0Value =48;
const int MAXBASE = ARRAYMAX+1;


char baseValues[ARRAYMAX];
int charArray[95];//For userdefined values of A-Z a-z space numbers and punctuation symbols (So we won't use ASCII values)
int base = 16;


int main()
{
	int attempts =0;
	string input ="";
	string userAction ="";
	string result ="";
	
	//populate Tables
	populateBaseValues();
	populateCharArray();
	
	
	while(userAction != "end")
	{
		cout << "What do you want to do?" << endl << "\tSettings (settings)\n\tConvert Code (code)\n\tConvert Message (message)\n\tEnd Program (end)"<<endl;
		
		cin >> userAction;
		
		if(userAction == "settings")
		{
			attempts = 0;//If the user starts using the program as intended I don't want to knock them down for any typos.
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

int CharToNum (char car)//Will return ASCII or custom values of the character.
{
	int num =0;
	
	//num = car;
	
	num = charArray[car-32];//the indexes of this array correspond to ASCII values starting at 32, so we must subtract 32 to get the proper array index. If the user has edited this table it will return the value the user wants
	
	return num;
}

char NumToChar (int num)
{
	/*char car = ' ';
	if (num < 32 || num > 126) //These numbers are chosen based on the ASCII value table. I do not want to mess with any complicated whitespace values nor do I want to work with values that aren't even in the ASCII table.
	{
		car = ' ';
	} else
	{
		car = num;
	}
	return car;*/
	char car;
	bool found = false;
	for (int i = 0; i< 95; i++)//This is to look through the userdefined values of characters for their code.
	{
		if (charArray[i] == num)//In order to ensure that the user does not forget a character from ASCII values 32-126, using only a one rowed array makes it so that users can only edit the corresponding values of an ASCII array and they will not change order. 
		{
			car = i+32;//We add 32 because this array represents ASCII chars 32-126 but we do not want to have empty values in our array in order to avoid confusion when a user goes to edit the values to create a unique code.
			found = true;
		}
	}
	if (!found)
	{
		cout << num << " doesn't correspond to any character value.";
		car = 254;
	}
	return car;
}

void Settings()//Change the base to work in (Might change this function if I think of more settings that can be changed) (We might be able to make it so that users can choose the value of characters instead of just sticking with the ASCII values [Advanced Users Only])
{
	string userAction = "";
	while (userAction != "end")
	{
		cout << "\t\tChange Base (base)\n\t\tChange Char Values (char)\n\t\tMore Information (info)\n\t\tCancel change Settings (end)"<<endl;
		cin >> userAction;
		if(userAction == "base")
		{
			int previous = base;
			int num = 0;
			while(num>MAXBASE||num<2)
			{
				cout << "The current base is " << base << ". What base would you like to work in?";
				cin >> num;
			}
			base =num;
			if(base == previous)
			{
				cout << "No change to base. "<< base << endl;
			}
			cout << "New base is " << base << "."<<endl;
		}else if(userAction == "char")
		{
			cout << "\t\tWARNING\nEditing the character array table may cause unexpected outcomes"<<endl <<"\tReset to default values (default)\n\tContinue Editing (edit)\n\tGo back (back)\n\tExit settings (end)"<<endl;
			cin >> userAction;
			if (userAction=="default")
			{
				populateCharArray();
				userAction = "end";
			}else if(userAction =="edit")
			{
				char car;
				int value=0;
				cout << "To edit the character shown enter a new value, to keep it's original value type -1, to end process type end."<<endl;
				for(int i = 0; i<95; i++)
				{
					car = i+32;
					cout << "'"<<car<<"'";
					cin >> userAction;
					if(userAction=="end")
					{
						i=95;
					}else if(stoi(userAction)<0)
					{
						//do nothing
					}else
					{
						value = stoi(userAction);
						charArray[i] = value;
					}
				}
				
			}//If userAction = back it will restart the settings menu, if it is end it will trigger the end event 
			
		}else if(userAction == "info")
		{
			cout << "Changing the base can affect how your message is encoded and how your code is decoded. Common bases are binary (2), octal (8), and hexadecimal (16). We commonly think in base 10 which is our normal counting system. You can choose any base up to 63." << endl <<endl <<"For more advanced users you can edit the character values. By default the character values follow the ASCII table, i.e space is 32 A is 65. I only allow up to ASCII character 126. But if you are so inclined you can change the character values and make any of the ASCII characters from 32 to 126 equal to any real positive integer. It is recommended to keep to values in sequential order and have no repeating numbers when you edit these values. You have been warned."<<endl;
		}else if(userAction=="end")
		{
			
		}else
		{
			cout << "Invalid Action, options are cAsEsEnSiTiVe"<<endl;
		}
	}
}

//Convert a single Base phrase to Decimal
int Base2Decimal(string str)
{
	int num=0;
	for(int i = 0; i< str.length();i++)
	{
		for(int j=0;j<base;j++)
		{
			if(str.at(i) == baseValues[j])
			num = num + j*pow(base,str.length()-1-i);
		}
	}
	return num;
}

//Convert a single Decimal number to Base 
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
			value = baseValues[remainder] + value;//baseValues[remainder] is using the value to find the char that represents that value.
			num = num/base;
		}
	}
	return value;
}

void populateCharArray()
{
	for(int i=0;i<95;i++)
	{
		charArray[i] = i+32; //This is for default ASCII values starting with the " ".
	}
}
void populateBaseValues()//Used for creating the code. In Hex F represents 15, in this array the array index is the value that is associated with the represented char in the array.
{
	for( int i=0;i<ARRAYMAX; i++)
	{
		
		if(i<10)//0-9 placed in the 0-9 slots of the array
		{
			baseValues[i]= ASCII0Value+ i;
		}
		else if(i>=10 && i < 10+26)//A-Z placed in the 10-36 slots of the array
		{
			baseValues[i] = ASCIIAValue+i-10;
		}else//a-z placed in the 37-62 slots of the array
			baseValues[i] = ASCIIaValue+i-10-26;
	}
}