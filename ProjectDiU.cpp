#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<ios>      
#include<limits>
#include<direct.h>
#include <filesystem>
#define NOMINMAX
#include<windows.h>

using namespace std;
namespace fs = std::filesystem;

//functions
void registrar();
void login();
void custom();
void log_f(string name);
void read(string name);
//void entries(string name);
int menu();

//global vars
string trm_color = "color 0a";

//function: menu
int menu()
{
	
	int cp = 1252; //codepage "windows-1252" 
	int cpIn = GetConsoleCP(); //Console Input codepage
	int cpOut = GetConsoleOutputCP(); //Console Output codepage
	SetConsoleOutputCP(cp); 
	SetConsoleCP(cp); 
str:	
	system("cls");
	system(trm_color.c_str());
	std::cout << "Select Option:\n\n";
	std::cout << "Login [1]\nRegister [2]\nCustomization Settings [3]\nExit[0] \n\n";

	std::cout << "Option: ";
	int opt;
	std::cin >> opt;
	if(opt == 2)
	{
		registrar();
	}
	if(opt == 1)
	{
		login();
	}
	if(opt == 3)
	{
		custom();
	}
	if(opt == 0)
	{
		SetConsoleCP(cpIn); 
		SetConsoleOutputCP(cpOut); 
		exit(0);
	}
	else
	{
		system("cls");
		goto str;
	}
	
SetConsoleCP(cpIn); 
SetConsoleOutputCP(cpOut); 
return 1; //Error 1 <== Menu Error
}

void registrar()//function: register

{
	system("cls");
	_mkdir("C:\\ProjectDiU\\Users");		
	std::cout << "Username: ";
	string username;
	getline(cin, username);
	string filename;//
	string user_;//
	filename = "C:\\ProjectDiU\\Users\\";
	filename += username;
	user_ = filename;
	_mkdir(user_.c_str());
	filename += "\\";
	filename += username;
	filename += ".txt";
	ofstream myfile;//
	myfile.open(filename.c_str(), ios::app);
	myfile << username <<"\n";
	int n;//
	std::cout << "\nPassword: ";
	string placeholder;//
	string password;	//
	getline(cin, placeholder);
	for (n = 0; n < placeholder.length(); n++)
	{
		placeholder[n] += placeholder.length()*n;
		password[n] = placeholder[n];
		placeholder[n] = '\0';
		myfile << password[n];
	}
	std::cout << "\n\nUser registered!\n";	
	system("pause");
	myfile.close();
	menu();
}

void login()//function: login 
{
	system("cls");
	cin.ignore(numeric_limits<streamsize>::max(), '\n');//cleans buffer

	std::cout << "Username: ";
	string name;
	string path;
	getline(cin, name);
	path = "C:\\ProjectDiU\\Users\\";
	path += name;
	name += ".txt";
	path += "\\";
	path += name;
	fstream file;
	std::cout << "\nPassword: ";
	string psw;
	getline(cin, psw);
	int n;
	for (n = 0; n < psw.length(); n++)
	{
		psw[n] += psw.length()*n;
	}
	
	file.open(path.c_str());
	if(!file)
	{user_not_found:
		
		std::cout << "\n\nUser not found!\n";
		system("pause");
		menu();
	}	
	string line;
	for (int lineno = 1; getline(file,line) && lineno < 3; lineno++)
    {
		if (lineno == 2)
    	{
			if(line == psw)
			{
				file.close();
				account:
				
				system("cls");
				name = name.substr(0, name.find(".txt"));
				std::cout << "Welcome " << name << "\n\n";
				std::cout << "Write an Entry [1]\nRead an Entry [2]\nBack to Menu [0]\n";
				std::cout << "\nWhat would you like to do?: ";
				int n;
				std::cin >> n;
				switch (n)
				{
					case 1:
						log_f(name);
					case (2):
						cin.ignore(numeric_limits<streamsize>::max(), '\n');//cleans buffer
						read(name);
					case (0):
						menu();
					default:
						std::cout << "\nNot a valid answer";
						system("pause");
						goto account;
				}
				
				menu();
			}	
			else
			{
				goto user_not_found;
			}
		}
	}
}

void custom()//terminal customization
{
	system("cls");
	char inputb;
	char inputf;
	
	std::cout << "Welcome to Customization Settings!\n\n";
	std::cout << "Here you can customize the appearance of the\nterminal you are using(colors of the background and font)";
	std::cout << "\n\nBackground Color                 Font Color\n\n";
	std::cout << "0 = Black                     a = Light Green\n";
	std::cout << "1 = Blue                      b = Light Aqua\n";
	std::cout << "2 = Green                     c = Light Red\n";
	std::cout << "3 = Aqua                      d = Light Purple\n";
	std::cout << "4 = Red                       e = Light Yellow\n";
	std::cout << "5 = Purple                    f = Bright White\n";
	std::cout << "6 = Yellow\n";
	std::cout << "7 = White\n";
	std::cout << "8 = Gray\n";
	std::cout << "9 = Light Blue\n\n";

	std::cout << "Please type the number of the corresponding background color\nthen type the letter for the font color\n\n";
	std::cout << "Example: type '0a' for 'Black' background and 'Light Green' font\n\n";
	
	gt_inputb:
	std::cout << "Background Color(0 - 9): ";
	std::cin >> inputb;//background color
	if(inputb > '9' || inputb < '0')
	{
		std::cout << "Not a valid number!\n";
		goto gt_inputb;
	}
	
	gt_inputf:
	std::cout << "Font Color(a - f): ";
	std::cin >> inputf;//font color
	if(inputf > 'f' || inputf < 'a')
	{
		std::cout << "Not a valid letter!\n";
		goto gt_inputf;
	}
	trm_color = "color ";
	trm_color += inputb;
	trm_color += inputf;

	menu();
}

void log_f(string name)//log file writting
{	
    time_t lol;//time struct 
	struct tm *sys_dt;
    time(&lol);
	sys_dt = localtime(&lol);	

	system("cls");
	std::cout << "Welcome, " << name << ".\n\n";
	std::cout << "It is now " << asctime(sys_dt);
	std::cout << "\nPlease type the name for your entry (type '.exit' to return to LOGIN menu): ";
	string filename;//
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 	
	getline(cin, filename);
	string path; //
	path = "C:\\ProjectDiU\\Users\\";
	path += name;
	path += "\\logs";
	_mkdir(path.c_str());
	if(filename == ".exit")
	{
		menu();
	}
	else
	{
		ofstream log;//file: log to be written
		filename += ".txt";
		path += "\\";
		path += filename;
		log.open(path.c_str(), ios::app);
		log << asctime(sys_dt) <<"\n";		
		system("cls");
		std::cout << "It is now " << asctime(sys_dt);
		std::cout << "\n\nKey 'Enter' to stop writting\n\n";
		string text;//
		getline(cin, text);// log content
		int n;//
		for (n = 0; n <= text.length(); n++)
		{
			if(n % 120 == 0)
			{
				log << "\n";
			}
			text[n] += n*n;// encrypting (temporary method)
			log << text[n];
		}
		log << "\n\n" << name;
		system("cls");
		std::cout << "It is now " << asctime(sys_dt);

		log.close(); //File check
		if(log.fail())
		{
			std::cout <<"\n\nFailed to write file, please try again or check source code";
		}
		else
		{
			log.close();			
			std::cout <<"\n\n" << filename << " successfully written and saved\n";
		}
		system("pause");
		menu();
	}
}

void read(string name)//log reading
{
	Entries:
	system("cls");
	std::cout << "Your entries: \n\n";

	string user = name;
	string path = "C:\\ProjectDiU\\Users\\";
	path += user;
	path += "\\logs";
	for (const auto& entry : fs::directory_iterator(path))//iterate through user's "logs" folder
	{
		std::cout << entry.path().filename() << std::endl;
	}
	std::cout << "\nWhich entry would you like to read? (type '.exit' to return to the menu): ";
	string arquivo;
	getline(cin, arquivo);
	if (arquivo == ".exit")
	{
		menu();
	}

	path += "\\";
	path += arquivo;
	fstream file;
	file.open(path.c_str());
	string line;
	int lineno = 0;

	if (file.is_open())
	{
		while (!file.eof())
		{
			lineno++;
			getline(file, line);
			if (lineno < 4 || strcmp(user.c_str(), line.c_str() ) == 0)
			{
				if (strcmp(user.c_str(), line.c_str()) == 0)
				{
					std::cout << "\n\n" << line;
				}
				else
				{
					std::cout << line << endl;
				}

			}
			else
			{
				for (int n = 0; n < line.size(); n++)
				{
					line[n] -= n * n;
					std::cout << line[n];
				}
			}
		}
	}
	else
	{
		std::cout << "Entry not found! Please check your folder again.\n";
		system("pause");
		goto Entries;
	}
	file.close();
	Entries_final_question:
	std::cout << "\nWould you like to read another entry? [Y/N]: ";
	char ans;
	std::cin >> ans;
	switch (ans)
	{
	case 'N':
		menu();
	case ('n'):
		menu();
	case ('Y'):
		goto Entries;
	case ('y'):
		goto Entries;
	default:
		std::cout << "Not a valid answer!\n";
		goto Entries_final_question;
	}
}



int main()//main: starts menu
{
	_mkdir("C:\\ProjectDiU");	
	menu();
}
