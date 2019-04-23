#include <iostream>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

enum support_lan { NOT_SUPT, c, cpp, java } lan;

static int fcheck();
static void outname_change();
static bool extention();
static void runapp();
static void tip();

bool runstat = true;
char cmdrn[50], ccmd[] = "gcc -o ", cpcmd[] = "g++ -o ", jcmd[] = "javac ", flname[30], outname[30], postfx[10] = ".cpp";
char colr[] = "color c", colw[] = "color 7", coly[] = "color 6",
colg[] = "color a";

int main(int argc, char const* argv[]) {
	tip();

	FileName:
	system(colw);
	static int count = 0;
	cout << "\t\t**Auto compile and Execution**\t\t-San\nFile Name With "
	"Extention: ";
	cin >> flname;

	if (fcheck()) {
		system(colr);
		cout << "\n\n";
		sleep(1);
		goto FileName;
	}
	cout << "\nPress ESP for Settings\nPress 'F5' to Auto Compile. . .\n\n: ";

	back:
	if (GetAsyncKeyState(VK_F5)) {
		system("cls");
		cout << "**Auto compile and Execution**  (" << ++count
		<< ")\nPress 'F5' to Auto Compile...\n\n: ";
		cout << cmdrn << endl;
		if (system(cmdrn) != 1) {
			system(colg);
			if (runstat)
				runapp();
		} else
		system(colr);
	}
	if (GetAsyncKeyState(VK_ESCAPE)) {
		system(coly);
		cout << "\n\n Press:\t(Use NUMPAD)\n1. Change File Name\n2. Change Output "
		"Name (Only: C & C++)\n3. Toggle Auto Execution  ";
		if (runstat)
			cout << "(AE: ON)";
		else
			cout << "(AE: OFF)";
		cout << "\nPress ESP to exit. . .\n";
		system("pause");
		if (GetAsyncKeyState(VK_ESCAPE))
			exit(0);
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			system("cls");
			goto FileName;
		}
		if (GetAsyncKeyState(VK_NUMPAD2)) {
			outname_change();
		}
		if (GetAsyncKeyState(VK_NUMPAD3)) {
			cout << " #AE Set#\n";
			runstat = !runstat;
		}
	}
	cout << ".";
	sleep(1);
	system(colw);
	goto back;
	return 0;
}

static void outname_change(){
	if(lan==c ||lan==cpp){
		cout << "\n #(Only Provide '.EXE' EXTENSION '.' exists below)\nNew Output Name: ";
		cin>>outname;
		switch (lan) {
			case c:
			strcpy(cmdrn, ccmd);
			strcat(cmdrn, outname);
			strcat(cmdrn, " ");
			strcat(cmdrn, flname);
			break;
			case cpp:
			strcpy(cmdrn, cpcmd);
			strcat(cmdrn, outname);
			strcat(cmdrn, " ");
			strcat(cmdrn, flname);
		}
	}
		else
			cout<<"\n #Operation Not Supported for this File\n";
		return;
	}


	static int fcheck() {
		DWORD fileAtt = GetFileAttributesA(flname);
		if (fileAtt == INVALID_FILE_ATTRIBUTES) {
			cout << "\n #File Not Presnt. . .";
			return 1;
		}
		int j, i, len = strlen(flname);
		i = len - 1;
		while (flname[i] != '.')
			i--;
		strcpy(outname, flname);
		outname[i] = '\0';
		j = 0;
		while (flname[i] != '\0')
			postfx[j++] = tolower(flname[i++]);
		postfx[j] = '\0';
		if (extention()) {
			system(colr);
			cout << "\n #Sorry, Type Not Supported . . .\n Wish to add custom command "
			"line?.. (Y/N)- ";
			sleep(1);
			system(colw);
			char cuscmd = getch();
			if (cuscmd == 'y' || cuscmd == 'Y') {
				cout << "\n\nEnter Command Line:\n- ";
				cin >> cmdrn;
				return 0;
			}
			return 1;
		}
		return 0;
	}

	static bool extention() {
		if (!strcmp(postfx, ".c"))
			lan = c;
		else if (!strcmp(postfx, ".cpp"))
			lan = cpp;
		else if (!strcmp(postfx, ".java"))
			lan = java;
		else
			return 1;
		switch (lan) {
			case c:
			strcpy(cmdrn, ccmd);
			strcat(cmdrn, outname);
			strcat(cmdrn, " ");
			strcat(cmdrn, flname);
			break;
			case cpp:
			strcpy(cmdrn, cpcmd);
			strcat(cmdrn, outname);
			strcat(cmdrn, " ");
			strcat(cmdrn, flname);
			break;
			case java:
			strcpy(cmdrn, jcmd);
			strcat(cmdrn, flname);
		}
		return 0;
	}

	static void runapp() {
		char run[20] = "start ";
		if(lan==java)
			strcat(run, "java ");
		strcat(run, outname);
		system(colg);
		cout << "\n #Running App. . .\n";
		system(run);
		return;
	}

	static void tip() {
		cout << "\t\t**Auto compile and Execution**\t\t-San\n";
		cout << " #How TO:#\nThis program automates the process of Compiling and "
		"Execution in one click.\n..(When using Editors like 'SUBLIME' "
		"etc)\n..Place this file, where the code is present.\n..Enter File Name with Extension.\n..In case of Extension "
		"mismatch, you are offered to add custom command line.\n..You can "
		"minimize this app or let it run in background.\n..Auto App LAUNCH "
		"can be toggled.\n..Press 'F5' to initiate.\n\n";
	}