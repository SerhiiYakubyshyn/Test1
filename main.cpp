#include<iostream>
#include<Windows.h>
#include<time.h>
#include<iomanip>
#include<string.h>
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
void DoArr();
int* InitializationArray(int** Field, int Row, int Col);
void PrintLine(int** Field, int Row, int Col, int v, char Vertical, bool CanSee);
void PrintField(int** FieldPlayer, int** FieldComputer, int Row, int Col);
bool CharIntAudit(char* Write, int& PlaseV, int& PlaseH);
void CharIntTransformation(char* Write, int& PlaseV, int& PlaseH);
int* TankPlase(int** FieldPlayer, int** FieldComputer, int Row, int Col);
int* TankPlaseRandom(int** Field, int Row, int Col);
int* TankPlaseMoreRandom(int** Field, int PlaseV, int PlaseH);
bool AuditRandPlase(int** Field, int PlaseV, int PlaseH, int Audit);
void TankBattle(int** FieldPlayer, int** FieldComputer, int Row, int Col);
bool ChangeMark(int** Field, int PlaseV, int PlaseH);
int* AuditMarkShoot(int** FieldComputer, int PlaseV, int PlaseH);
int* HitPlayer(int** FieldPlayer, int** FieldComputer, int Row, int Col, int& ComputerTanks);
char* FeelStoris(char** StorisComp);
void DeleteStoris(char** StorisComp);
void ComputerDid(int** FieldPlayer, int PlaseV, int PlaseH, char** StorisComp, int& NumberStoris);
int* HitComputer(int** FieldComputer, int** FieldPlayer, int Row, int Col, int& CompShootMemoryV, int& CompShootMemoryH, bool& CompMemory, int& PlayerTanks, char** StorisComp);
void DeleteArray(int** Field, int Size);
int main()
{
	srand(time(NULL));
	DoArr();
	SetConsoleTextAttribute(hStdOut, (WORD)(15));
	cout << endl << endl;
	system("pause");
	return 0;
}
void DoArr()
{
	srand(time(NULL));
	int Doin = 2;
	SetConsoleTextAttribute(hStdOut, (WORD)(2));
	cout << "\n\tGame Tanks\n";
	while (Doin != 0) {
		int Row = 12;
		int Col = 22;
		int** FieldPlayer = new int* [Row];
		int** FieldComputer = new int* [Row];
		*FieldPlayer = InitializationArray(FieldPlayer, Row, Col);
		*FieldComputer = InitializationArray(FieldComputer, Row, Col);
		for (;;) {
			SetConsoleTextAttribute(hStdOut, (WORD)(2));
			cout << "\n\tStart Game(1), Exit(0)-> ";
			cin >> Doin;
			if (Doin == 0) {
				break;
			}
			else if (Doin == 1) {
				Sleep(500);
				system("CLS");
				bool IsRandom = true;
				char Write[10] = " ";
				PrintField(FieldPlayer, FieldComputer, Row, Col);
				cout << "\n\tDo you want to place the tanks yourself(0), or random(1)? ";
				cin >> Write;
				if (Write[0] == '0')////////////////////
					IsRandom = false;//////////////////
				else if (Write[0] == '1')/////////////
					IsRandom = true;///////////////// «роблено дл€ уникненн€ багу введенн€ при вибор≥ методу заповненн€.
				else////////////////////////////////
					break;/////////////////////////
				if (IsRandom)
					TankPlaseRandom(FieldPlayer, Row, Col);
				else
					TankPlase(FieldPlayer, FieldComputer, Row, Col);
				TankPlaseRandom(FieldComputer, Row, Col);
				Sleep(500);
				system("CLS");
				PrintField(FieldPlayer, FieldComputer, Row, Col);
				TankBattle(FieldPlayer, FieldComputer, Row, Col);
				break;
			}
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError!\n";
			}
		}
		DeleteArray(FieldPlayer, Row);
		DeleteArray(FieldComputer, Row);
	}
}
int* InitializationArray(int** Field, int Row, int Col)
{
	for (int v = 0; v < Row; v++) {
		Field[v] = new int[Col];
		for (int h = 0; h < Col; h++) {
			if (((v == 0) && (h == 0)) || ((v == Row - 1) && (h == Col - 1)) || ((v == 0) && (h == Col - 1)) || ((v == Row - 1) && (h == 0)))
				Field[v][h] = -2;
			else if ((v == 0) || (h == 0) || (v == Row - 1) || (h == Col - 1))
				Field[v][h] = -1;
			else
				Field[v][h] = 0;
		}
	}
	return *Field;
}
void PrintLine(int** Field, int Row, int Col, int v, char Vertical, bool CanSee)
{
	char Free = 79;
	char Corner = 32;
	char Tank = 254;
	char PaddedTank = 64;
	char Past = 88;
	char Horizontal = 65;
	for (int h = 0; h < Col; h++) {
		if (((Field[v][h] == -1) && (h > 0)) && ((v == 0) || (v == Row - 1))) {
			SetConsoleTextAttribute(hStdOut, (WORD)(11));
			cout << setw(2) << Horizontal << setw(2);
			Horizontal++;
		}
		else if (((Field[v][h] == -1) && (v > 0)) && ((h == 0) || (h == Col - 1))) {
			SetConsoleTextAttribute(hStdOut, (WORD)(11));
			cout << setw(2) << Vertical << setw(2);
		}
		else if (Field[v][h] == -2) {
			cout << setw(2) << Corner << setw(2);
		}
		else if ((Field[v][h] == 1) && (CanSee)) {
			SetConsoleTextAttribute(hStdOut, (WORD)(2));
			cout << setw(2) << Tank << setw(2);
		}
		else if ((Field[v][h] == 1) && (!CanSee)) {
			SetConsoleTextAttribute(hStdOut, (WORD)(15));////////////////////«м≥на кольру з 15 на 2, даЇ можлив≥сть п≥дсв≥тити танки комп'ютера.
			cout << setw(2) << Free << setw(2);
		}
		else if (Field[v][h] == 2) {
			SetConsoleTextAttribute(hStdOut, (WORD)(4));
			cout << setw(2) << PaddedTank << setw(2);
		}
		else if (Field[v][h] == 3) {
			SetConsoleTextAttribute(hStdOut, (WORD)(6));
			cout << setw(2) << Past << setw(2);
		}
		else {
			SetConsoleTextAttribute(hStdOut, (WORD)(15));
			cout << setw(2) << Free << setw(2);
		}
	}
}
void PrintField(int** FieldPlayer, int** FieldComputer, int Row, int Col)
{
	SetConsoleTextAttribute(hStdOut, (WORD)(6));
	bool CanSee = true;
	char Vertical = 48;
	cout << endl;
	for (int v = 0; v < Row; v++) {
		CanSee = true;
		PrintLine(FieldPlayer, Row, Col, v, Vertical, CanSee);
		cout << "\t";
		CanSee = false;
		PrintLine(FieldComputer, Row, Col, v, Vertical, CanSee);
		if (v > 0)
			Vertical++;
		cout << endl;
	}
	cout << endl;
}
bool CharIntAudit(char* Write, int& PlaseV, int& PlaseH)
{
	if (strlen(Write) != 2)
		return false;
	if ((Write[0] < 65) || ((Write[0] > 84) && (Write[0] < 97)) || (Write[0] > 116))
		return false;
	if ((Write[1] < 48) || (Write[1] > 57))
		return false;
	return true;
}
void CharIntTransformation(char* Write, int& PlaseV, int& PlaseH)
{
	PlaseV = (Write[1] - 48) + 1;
	if ((Write[0] >= 97) && (Write[0] <= 116))
		Write[0] -= 32;
	PlaseH = Write[0] - 64;
}
int* TankPlase(int** FieldPlayer, int** FieldComputer, int Row, int Col)
{
	int Tank = 0;
	while (Tank < 10) {
		bool CanStay = false;
		bool CanStayMore = false;
		int Audit = 1, PlaseV = 0, PlaseH = 0, PlaseVNear = 0, PlaseHNear = 0;
		char* Write = new char[10];
		while (!CanStay) {
			SetConsoleTextAttribute(hStdOut, (WORD)(2));
			cout << "\n\tPlace the tanks-> ";
			cin >> Write;
			if (CharIntAudit(Write, PlaseV, PlaseH))
				CharIntTransformation(Write, PlaseV, PlaseH);
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError! Should be (A-T) and (0-9)!\n";
			}
			if (AuditRandPlase(FieldPlayer, PlaseV, PlaseH, Audit)) {
				FieldPlayer[PlaseV][PlaseH] = 1;
				CanStay = true;
			}
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError!\n";
			}
		}
		Sleep(500);
		system("CLS");
		PrintField(FieldPlayer, FieldComputer, Row, Col);
		while ((!CanStayMore) && (CanStay)) {
			SetConsoleTextAttribute(hStdOut, (WORD)(2));
			cout << "\n\tPosition near-> ";
			cin >> Write;
			if (CharIntAudit(Write, PlaseVNear, PlaseHNear))
				CharIntTransformation(Write, PlaseVNear, PlaseHNear);
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError! Should be (A-T) and (0-9)!\n";
			}
			Audit = 0;
			if (AuditRandPlase(FieldPlayer, PlaseVNear, PlaseHNear, Audit)) {
				FieldPlayer[PlaseVNear][PlaseHNear] = 1;
				Tank++;
				CanStayMore = true;
			}
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError!\n";
			}
		}
		delete[]Write;
		Write = nullptr;
		Sleep(500);
		system("CLS");
		PrintField(FieldPlayer, FieldComputer, Row, Col);
	}
	return *FieldPlayer;
}
int* TankPlaseRandom(int** Field, int Row, int Col)
{
	int Audit = 1;
	int Tank = 0;
	while (Tank < 10) {
		int PlaseV = 0, PlaseH = 0;
		PlaseV = 1 + rand() % (Row - 2);
		PlaseH = 1 + rand() % (Col - 2);
		if (AuditRandPlase(Field, PlaseV, PlaseH, Audit)) {
			Field[PlaseV][PlaseH] = 1;
			*Field = TankPlaseMoreRandom(Field, PlaseV, PlaseH);
			Tank++;
		}
	}
	return *Field;
}
int* TankPlaseMoreRandom(int** Field, int PlaseV, int PlaseH)
{
	int Audit = 0;
	bool CanMore = false;
	while (!CanMore) {
		int MoreV = 0, MoreH = 0;
		int SideMove = 1 + rand() % 4;
		if (SideMove == 1)
			MoreV++;
		else if (SideMove == 2)
			MoreV--;
		else if (SideMove == 3)
			MoreH++;
		else if (SideMove == 4)
			MoreH--;
		if (AuditRandPlase(Field, PlaseV + MoreV, PlaseH + MoreH, Audit)) {
			Field[PlaseV + MoreV][PlaseH + MoreH] = 1;
			CanMore = true;
		}
	}
	return *Field;
}
bool AuditRandPlase(int** Field, int PlaseV, int PlaseH, int Audit)
{
	if (Field[PlaseV][PlaseH] != 0)
		return false;
	if (Field[PlaseV][PlaseH] == 1)
		return false;
	if (Field[PlaseV + 1][PlaseH] == 1)
		Audit++;
	if (Field[PlaseV - 1][PlaseH] == 1)
		Audit++;
	if (Field[PlaseV][PlaseH + 1] == 1)
		Audit++;
	if (Field[PlaseV][PlaseH - 1] == 1)
		Audit++;
	if (Field[PlaseV - 1][PlaseH - 1] == 1)
		Audit++;
	if (Field[PlaseV - 1][PlaseH + 1] == 1)
		Audit++;
	if (Field[PlaseV + 1][PlaseH - 1] == 1)
		Audit++;
	if (Field[PlaseV + 1][PlaseH + 1] == 1)
		Audit++;
	if (Audit == 1)
		return true;
	else
		return false;
}
void TankBattle(int** FieldPlayer, int** FieldComputer, int Row, int Col)
{
	int CompShootMemoryV = 0, CompShootMemoryH = 0;
	int PlayerTanks = 20, ComputerTanks = 20;
	bool CompMemory = false;
	char** StorisComp = new char* [10];
	FeelStoris(StorisComp);
	for (;;) {
		HitPlayer(FieldPlayer, FieldComputer, Row, Col, ComputerTanks);
		if (ComputerTanks == 0) {
			SetConsoleTextAttribute(hStdOut, (WORD)(2));
			cout << "\n\tYou winner!\n";
			break;
		}
		HitComputer(FieldComputer, FieldPlayer, Row, Col, CompShootMemoryV, CompShootMemoryH, CompMemory, PlayerTanks, StorisComp);
		if (PlayerTanks == 0) {
			SetConsoleTextAttribute(hStdOut, (WORD)(4));
			cout << "\n\tComputer winner!\n";
			break;
		}
	}
	DeleteStoris(StorisComp);
}
bool ChangeMark(int** Field, int PlaseV, int PlaseH)
{
	if ((Field[PlaseV][PlaseH] == 2) && (Field[PlaseV + 1][PlaseH] == 2))
		return true;
	else if ((Field[PlaseV][PlaseH] == 2) && (Field[PlaseV - 1][PlaseH] == 2))
		return true;
	else if ((Field[PlaseV][PlaseH] == 2) && (Field[PlaseV][PlaseH + 1] == 2))
		return true;
	else if ((Field[PlaseV][PlaseH] == 2) && (Field[PlaseV][PlaseH - 1] == 2))
		return true;
	else
		return false;
}
int* AuditMarkShoot(int** Field, int PlaseV, int PlaseH)
{
	if ((Field[PlaseV][PlaseH] != 2))
		return *Field;
	if (Field[PlaseV + 1][PlaseH] == 2) {
		for (int v = -1; v < 3; v++) {
			for (int h = -1; h < 2; h++) {
				if (Field[PlaseV + v][PlaseH + h] == 0)
					Field[PlaseV + v][PlaseH + h] = 3;
			}
		}
	}
	else if (Field[PlaseV - 1][PlaseH] == 2) {
		for (int v = -2; v < 2; v++) {
			for (int h = -1; h < 2; h++) {
				if (Field[PlaseV + v][PlaseH + h] == 0)
					Field[PlaseV + v][PlaseH + h] = 3;
			}
		}
	}
	else if (Field[PlaseV][PlaseH + 1] == 2) {
		for (int v = -1; v < 2; v++) {
			for (int h = -1; h < 3; h++) {
				if (Field[PlaseV + v][PlaseH + h] == 0)
					Field[PlaseV + v][PlaseH + h] = 3;
			}
		}
	}
	else if (Field[PlaseV][PlaseH - 1] == 2) {
		for (int v = -1; v < 2; v++) {
			for (int h = -2; h < 2; h++) {
				if (Field[PlaseV + v][PlaseH + h] == 0)
					Field[PlaseV + v][PlaseH + h] = 3;
			}
		}
	}
	return *Field;
}
int* HitPlayer(int** FieldPlayer, int** FieldComputer, int Row, int Col, int& ComputerTanks)
{
	bool CanHitPlayer = true;
	while (CanHitPlayer) {
		bool CanShoot = false;
		char* Write = new char[10];
		int PlaseV = 0, PlaseH = 0;
		while (!CanShoot) {
			SetConsoleTextAttribute(hStdOut, (WORD)(6));
			cout << "\n\tWhere to shoot? -> ";
			cin >> Write;
			if (CharIntAudit(Write, PlaseV, PlaseH)) {
				CharIntTransformation(Write, PlaseV, PlaseH);
				if ((FieldComputer[PlaseV][PlaseH] == 1) || (FieldComputer[PlaseV][PlaseH] == 0))
					CanShoot = true;
			}
			else {
				SetConsoleTextAttribute(hStdOut, (WORD)(4));
				cout << "\n\tError!\n";
			}
		}
		if (FieldComputer[PlaseV][PlaseH] == 1) {
			FieldComputer[PlaseV][PlaseH] = 2;
			CanHitPlayer = true;
			ComputerTanks--;
		}
		else if (FieldComputer[PlaseV][PlaseH] == 0) {
			FieldComputer[PlaseV][PlaseH] = 3;
			CanHitPlayer = false;
		}
		delete[]Write;
		Write = nullptr;
		if (ChangeMark(FieldComputer, PlaseV, PlaseH)) {
			AuditMarkShoot(FieldComputer, PlaseV, PlaseH);
			if (ComputerTanks == 0) {
				Sleep(500);
				system("CLS");
				PrintField(FieldPlayer, FieldComputer, Row, Col);
				break;
			}
		}
		if ((FieldComputer[PlaseV][PlaseH] == 2) || (FieldComputer[PlaseV][PlaseH] == 3)) {
			Sleep(500);
			system("CLS");
			PrintField(FieldPlayer, FieldComputer, Row, Col);
		}
	}
	return *FieldComputer;
}
char* FeelStoris(char** StorisComp)
{
	for (int i = 0; i < 10; i++) {
		StorisComp[i] = new char[100];
	}
	return *StorisComp;
}
void DeleteStoris(char** StorisComp)
{
	for (int i = 0; i < 10; i++) {
		delete[]StorisComp[i];
	}
	delete[]StorisComp;
	StorisComp = nullptr;
}
void ComputerDid(int** FieldPlayer, int PlaseV, int PlaseH, char** StorisComp, int& NumberStoris)
{
	char Vertical[2] = {};
	char Horizontal[5] = {};
	_itoa_s(PlaseV - 1, Vertical, 10);
	Horizontal[0] = PlaseH + 64;
	strcat_s(Horizontal, Vertical);
	SetConsoleTextAttribute(hStdOut, (WORD)(6));
	char Bufer1[100] = " Computer shot ";
	char Bufer2[6] = " and ";
	char Bufer3[20] = "got into the tank.";
	char Bufer4[20] = "missed.";
	strcat_s(Bufer1, Horizontal);
	strcat_s(Bufer1, Bufer2);
	if (FieldPlayer[PlaseV][PlaseH] == 2)
		strcat_s(Bufer1, Bufer3);
	else if (FieldPlayer[PlaseV][PlaseH] == 3)
		strcat_s(Bufer1, Bufer4);
	for (int j = 0; j < strlen(Bufer1) + 1; j++) {
		StorisComp[NumberStoris][j] = Bufer1[j];
	}
	NumberStoris++;
	int Size = NumberStoris;
	for (int i = 0; i < NumberStoris; i++) {
		cout << StorisComp[i] << endl;
	}
}
int* HitComputer(int** FieldComputer, int** FieldPlayer, int Row, int Col, int& CompShootMemoryV, int& CompShootMemoryH, bool& CompMemory, int& PlayerTanks, char** StorisComp)
{
	bool CanHitComputer = true;
	bool CanPrint = true;
	int NumberStoris = 0;
	while (CanHitComputer) {
		int PlaseV = 0, PlaseH = 0;
		if (!CompMemory) {
			PlaseV = 1 + rand() % (Row - 2);
			PlaseH = 1 + rand() % (Col - 2);
		}
		else if (CompMemory) {
			PlaseV = CompShootMemoryV;
			PlaseH = CompShootMemoryH;
			int SideMove = 1 + rand() % 4;
			if (SideMove == 1)
				PlaseV++;
			else if (SideMove == 2)
				PlaseV--;
			else if (SideMove == 3)
				PlaseH++;
			else if (SideMove == 4)
				PlaseH--;
		}
		if ((FieldPlayer[PlaseV][PlaseH] == 1) || (FieldPlayer[PlaseV][PlaseH] == 0))
			CanPrint = true;
		else
			CanPrint = false;
		if (FieldPlayer[PlaseV][PlaseH] == 1) {
			FieldPlayer[PlaseV][PlaseH] = 2;
			CanHitComputer = true;
			CompMemory = true;
			CompShootMemoryV = PlaseV;
			CompShootMemoryH = PlaseH;
			PlayerTanks--;
		}
		else if (FieldPlayer[PlaseV][PlaseH] == 0) {
			FieldPlayer[PlaseV][PlaseH] = 3;
			CanHitComputer = false;
		}
		if (ChangeMark(FieldPlayer, PlaseV, PlaseH)) {
			CompMemory = false;
			AuditMarkShoot(FieldPlayer, PlaseV, PlaseH);
			if (PlayerTanks == 0) {
				Sleep(1000);
				system("CLS");
				PrintField(FieldPlayer, FieldComputer, Row, Col);
				break;
			}
		}
		if (CanPrint) {
			Sleep(1000);
			system("CLS");
			PrintField(FieldPlayer, FieldComputer, Row, Col);
			ComputerDid(FieldPlayer, PlaseV, PlaseH, StorisComp, NumberStoris);
		}
	}
	return *FieldPlayer;
}
void DeleteArray(int** Field, int Size)
{
	for (int i = 0; i < Size; i++) {
		delete[]Field[i];
	}
	delete[]Field;
	Field = nullptr;
}