#include <iostream>
using std::cin;
using std::cout;

void read(short int *s)
{
	for(int i=0;i<81;i++)
		cin >> s[i];
}

void stampa(short int* s)
{
	for(int i=0;i<81;i++)
	{
		if(i%9 == 0)
			cout << '\n';
		if(s[i] == -1)
			cout << '-' << ' ';
		else
			cout << s[i] << ' ';
	}
	cout << '\n';
}

short int getVal(short int *s, int x, int y)
{
	return s[(y*9)+x];
}

int getX(int i)
{
	return i/9;
}
int getY(int i)
{
	return i%9;
}

bool completed(short int *s)
{
	for(int i=0;i<9*9;i++)
		if(s[i] == -1)
			return false;
	return true;
}

bool trycomplete(short int* s, int ind)
{
	//già risolto
	if (s[ind] != -1)
		return false;
	
	bool *iv = new bool [9]{false, false, false, false, false, false, false, false, false}; //i valori da 1 a 9, se invalidi
	int v;
	
	//scorro le colonne
	for(int i=0;i<9;i++)
	{
		v = getVal(s, getY(ind), i);
		if(v != -1)
			iv[v-1] = true;
	}
	//scorro le righe
	for(int i=0;i<9;i++)
	{
		v = getVal(s, i, getX(ind));
		if(v != -1)
			iv[v-1] = true;
	}
	//scorro le celle
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			v = getVal(s,i+((getY(ind)/3)*3), j+((getX(ind)/3)*3));
			if(v != -1)
				iv[v-1] = true;
		}
		
	//controlle se c'è un unico valore a true
	int cont = 0;
	int val = -1;
	for(int i=0;i<9;i++)
		if(iv[i] == false)
		{
			cont++;
			val = i+1;
		}
	//setto l'unico a true in s
	if(cont==1)
	{
		s[ind] = val;
		return true;
	}
	return false;
}
short int* clone(short int* s)
{
	short int* r = (short int*)new short int[9][9];
	for(int i=0;i<81;i++)
		r[i] = s[i];
	return r;
}

bool trycompleteRic(short int* s, int ind)
{
	if (ind == 81)
	{
		cout << "Completato:\n";
		stampa(s);
		return true;
	}
	if (s[ind] != -1)
	{
		return trycompleteRic(s, ind+1);
	}
	
	bool *iv = new bool [9]{false, false, false, false, false, false, false, false, false}; //i valori da 1 a 9, false = possibili
	int v;
	
	for(int i=0;i<9;i++)
	{
		v = getVal(s, getY(ind), i);
		if(v != -1)
			iv[v-1] = true;
	}
	for(int i=0;i<9;i++)
	{
		v = getVal(s, i, getX(ind));
		if(v != -1)
			iv[v-1] = true;
	}
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			v = getVal(s,i+((getY(ind)/3)*3), j+((getX(ind)/3)*3));
			if(v != -1)
				iv[v-1] = true;
		}
		
	int cont = 0;
	for(int i=0;i<9;i++)
		if(iv[i] == false)
			cont++;
	if(cont == 0)
		return false;
	
	for(int i=0;i<9;i++)
		if(iv[i] == false)
		{
			short int * sc = clone(s);
			sc[ind] = i+1;
			
			//cout << "ricorsione da indice " << ind << '\n';
			//stampa(sc);
			
			if(trycompleteRic(sc, ind+1))
			{
				delete[] sc;
				return true;
			}
			delete[] sc;
		}
	return false;
}

bool resolve(short int *s)
{
	bool rit = false;
	bool ris;
	for(int i=0;i<9*9;i++)
		if(s[i] == -1)
		{
			ris = trycomplete(s, i);
			if(ris && !rit)
				rit = true;
		}
	return rit;
}

bool resolveRic(short int *s)
{
	bool inizio = false;
	for(int i=0;!inizio && i<9*9;i++)
		if(s[i] == -1)
			inizio = trycompleteRic(s, i);
	return inizio;
}

int main()
{
	short int *s = (short int*)new short int[9][9];
	//read the sudoku, -1 = no value
	read(s);
	stampa(s);
	cout << "inizio primo metodo...\n";
	bool firstTry = true;
	while(firstTry && !completed(s))
	{
		firstTry = resolve(s);
	}
	cout << "primo metodo terminato:\n";
	stampa(s);
	if(!completed(s))
	{
		cout << "Primo metodo non sufficente, inizio secondo metodo...\n";
		if(!resolveRic(s))
			cout << "ERRORE! Sudoku non possibile!\n";
	}
	
	return 0;
}