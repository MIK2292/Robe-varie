#include <string>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;


int n_parole = 0;
int SIZE = 10;

//TOOLS

string toupper(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] <= 'Z' and str[i] >= 'A')
			continue;
		else if (str[i] <= 'z' and str[i] >= 'a')
			str[i] -= 'a' - 'A';
	}
	return str;
}

char tolower(char str)
{
	if (str <= 'Z' and str >= 'A')
		str += 'a' - 'A';
	return str;
}

char toupper(char str)
{
	if (str <= 'z' and str >= 'a')
		str -= 'a' - 'A';
	return str;
}


//PARTE FACILE

string* Word_input()
{
	cout << "****************************************\n"
		 << "***      CRUCIPUZZLE GENERATOR       ***\n"
		 << "***  Inserisci le parole da cercare  ***\n"
		 << "***  quando hai finito inserisci '0' ***\n"
		 << "****************************************\n"
		 << endl;
		 
	int counter = 1;
	string word;
	vector<string> Words;
	
	while(1)
	{
		cout << "Inserisci la parola n." << counter++ << "\n\t\t\t";
		cin >> word;
		word = toupper(word); //scrive word solo con lettere maiuscole
//		cout << tolower(word[0]);
		if (word[0] > 'Z' || word[0] < 'A')
			break;
		
		Words.push_back(word);
	}
	
	string* Parole = new string[Words.size()];
	n_parole = Words.size();
	copy(Words.begin(), Words.end(), Parole);
	return Parole;
}

void ordina_per_lunghezza(string* Parole)
{
	string temp;
	
	for (int i = 0; i < n_parole-1; i++)
	{
		for (int j = 0; j < n_parole-1; j++)
		{
			if (Parole[j].size() < Parole[j+1].size())
			{
				temp = Parole[j];
				Parole[j] = Parole[j+1];
				Parole[j+1] = temp;
			}
		}
	}
}


char rand_letter()
{
	char alfabeto[21] = "abcdefghilmnoprstuvz";
	return alfabeto[rand() % 20];
}

char** randCP_generator() //CP= crucipuzzle
{
	char** Matrix = new char*[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		Matrix[i] = new char[SIZE];
		for (int j = 0; j < SIZE; j++)
			Matrix[i][j] = rand_letter();
	}
	
	return Matrix;
} 

void CP_print(char** Matrix)
{
	cout << endl << endl;
	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
//			cout << Matrix[i][j] << "   ";
			cout << toupper(Matrix[i][j]) << " ";
		}
		cout << "\n";
	}
}

//void array_print()


// PARTE DIFFICILE: sistemare le parole nel CP

int best_size(string* Parole)
{
	int size = Parole[0].size();
	
	if (Parole[0].size() <= 10)
		size = 10;
	
//	int tot_lenght = 0;
//	
//	for (int i = 0; i < n_parole; i++)
//	{
//		tot_lenght += Parole[i].size();
//	}
	
	return size;	
}

void scrivi_parola(char** M, string str, int PosX, int PosY, int v)
{
	switch (v){
		case 0: //ORIZZONTALE
			for (char CH : str)
				M[PosY][PosX++] = CH;
			break;
			
		case 1: //VERTICALE
			for (char CH : str)
				M[PosY++][PosX] = CH;
			break;
			
		case 2: //OBLIQUO
			for (char CH : str)
				M[PosY++][PosX++] = CH;
			break;
			
		default : cout << "Erroree";
	}
}

bool check_compatibility(char** M, string str, int PosX, int PosY, int v)
{
	switch (v){
		case 0: //ORIZZONTALE
			for (char CH : str)
			{
				if (M[PosY][PosX] <= 'a' && M[PosY][PosX] != CH)
					return false;
				PosX++;
			}
			break;
		case 1: //VERTICALE
			for (char CH : str)
			{
				if (M[PosY][PosX] <= 'a' && M[PosY][PosX] != CH)
					return false;
				PosY++;
			}
			break;
		case 2: //OBLIQUO
			for (char CH : str)
			{
				if (M[PosY][PosX] <= 'a' && M[PosY][PosX] != CH)
					return false;
				PosX++; PosY++;
			}
			break;
		default : cout << "Erroree";
	}
	
	return true;
}

void insert_a_cazzo(char** M, string str)
{
	int verso = rand()%3;
	int PosX, PosY;
	int counter = 0;
	
	while(counter < 300)
	{
		switch (verso){
			case 0: //ORIZZONTALE
				PosX = rand()%(SIZE+1 - str.size());
				PosY = rand()%SIZE;
				break;
			case 1: //VERTICALE
				PosX = rand()%SIZE;
				PosY = rand()%(SIZE+1 - str.size());
				break;
			case 2: //OBLIQUO
				PosX = rand()%(SIZE+1 - str.size());
				PosY = rand()%(SIZE+1 - str.size());
				break;
			default : cout << "Erroreeee";
		}
		
//		cout << "\n\n" << PosX << "\n" << PosY;
		
		if (check_compatibility(M, str, PosX, PosY, verso))
		{
			scrivi_parola(M, str, PosX, PosY, verso);
			return;	
		}
		counter++;
	} //end while
	
	cout << endl << str << " non inserito :(";
}

//void insert_e_combina(char** M, string str)
//{
//	
//}

void insert_all(char** Matrix, string* Parole)
{
	cout << "\n\n";
	for (int i = 0; i < n_parole; i++)
	{
//		cout << ".";
		insert_a_cazzo(Matrix, Parole[i]);
	}
}


//MAIN

int main()
{
	srand(time(NULL));
	string* Parole = Word_input();
	ordina_per_lunghezza(Parole);
	SIZE = best_size(Parole);
//	SIZE = 11;
	char** CruciPuzzle = randCP_generator();
//	CP_print(CruciPuzzle);
	insert_all(CruciPuzzle, Parole);
	CP_print(CruciPuzzle);
}






