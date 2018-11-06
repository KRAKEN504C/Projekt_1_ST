#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>



using namespace std;
//Rouxls Kaard was here.

class bledy {
public:
	int miejsce_w_G_viktorze;
	bitset<8> poprzednia_wartosc;

	void setter(int i, bitset<8> b)
	{
		miejsce_w_G_viktorze = i;
		poprzednia_wartosc = b;
	}
	bitset<8> get_value_bit() {
		return poprzednia_wartosc;
	}
	int get_value_int() {
		return miejsce_w_G_viktorze;
	}
};

//nie zapomnij zrobic z viktorow wskazniki!!!
//Dobra dobra. Ju� s�. Nie ma si� co tak o nie denerwowa�.
void GeneracjaBledow(bool powtorzenia, int opcja, vector<bitset<8>> * oryginal, vector<bledy> * robimy_bledy)
{
	srand(time(NULL));
	//powtorzenia	0-nie	1-tak
	int ile_tych_bledow;
	switch (opcja)
	{
	case 0:
		ile_tych_bledow = (0.01*(*oryginal).size())/100;
		cout << "\ntych bledow dla opcji nr.0 jest:" << ile_tych_bledow;
		break;
	case 1:
		ile_tych_bledow = (0.1*(*oryginal).size()) / 100;
		cout << "\ntych bledow dla opcji nr.1 jest:" << ile_tych_bledow;
		break;
	case 2:
		ile_tych_bledow = (1*(*oryginal).size()) / 100;
		cout << "\ntych bledow dla opcji nr.2 jest:" << ile_tych_bledow;
		break;
	case 3:
		ile_tych_bledow = (10*(*oryginal).size()) / 100;
		cout << "\ntych bledow dla opcji nr.3 jest:" << ile_tych_bledow;
		break;
	default:
		break;
	}

	bledy *test = new bledy;
	//test->setter(2, (*oryginal)[0]);
	bitset<8> tymczasosowka;
	int przelosowania = 0;
	for (int i = 0; i <= ile_tych_bledow; i++)
	{
		int GOD = rand() % (*oryginal).size(); 

		if ((*robimy_bledy).size() > 0 && powtorzenia == 0)
		{
			bool czy_juz_byla = 1;
			while (czy_juz_byla) {
				//cout <<"\n\n"<< GOD;
				for (int i = 0; i < (*robimy_bledy).size(); i++)
				{
					//cout <<"\t"<< (*robimy_bledy)[i].miejsce_w_G_viktorze;
					if (GOD != (*robimy_bledy)[i].miejsce_w_G_viktorze) { czy_juz_byla = 0; /*cout << "\tnie bylo";*/ }
					else { czy_juz_byla = 1; /*cout << GOD << "\tBYLA"; przelosowania++;*/ }
				}
				GOD = rand() % (*oryginal).size();
			}
		}

		//tymczasosowka = (*oryginal)[GOD];
		test->setter(GOD, (*oryginal)[GOD]);
		(*robimy_bledy).push_back(*test);
		//int od0do7 = rand() % 8;
		//cout << "\n" << (*oryginal)[GOD];
		(*oryginal)[GOD].flip(rand() % 8);
		//cout << "\t" << (*oryginal)[GOD];
	}

	//cout << "\n\n Ilosc ponownych losowan (sprawdzenie czy to dziala)" << przelosowania;

	//(*robimy_bledy).push_back(*test);
	//cout << "\n" << (*robimy_bledy)[0].poprzednia_wartosc << endl;
	//(*robimy_bledy)[0].setter(3, (*oryginal)[1]);
	//cout << "\n" << (*robimy_bledy)[0].poprzednia_wartosc << endl;
}

int Parzystosc(vector<bitset<8>> viktor)
{
	int sdoint=0;
	int suma = 0;
	for (auto i = viktor.begin(); i != viktor.end(); i++)
	{
		bitset <8> test = *i;
		sdoint = (int)(test.to_ulong());
		while (sdoint>0)
		{
			suma += sdoint % 10;
			sdoint /= 10;
		}
	}

	if (suma % 2 == 0) { return 0; }
	else { return 1; }

}

int CheckSum(vector<bitset<8>> viktor)
{
	int check = 0;
	int sdoint;
	for (auto i = viktor.begin(); i != viktor.end(); i++)
	{
		bitset <8> test = *i;
		sdoint = (int)(test.to_ulong());
		while (sdoint>0)
		{
			check += sdoint % 10;
			sdoint /= 10;
		}
	}
	return check;
}

string CRC()
{
	return "Jeszcze nic";
}


int main()
{
	string nazwa = "";
	cout << "Prosz� poda� nazwe z roszerzeniem tego smutnego pliku ktory odbedzie ta niezwykle okrutna procedure.:";
	cin >> nazwa;


	//srand(time(NULL));
	//Stworzenie zmiennych fstream do zarz�dzania plikiem wej�ciowym i wyj�ciowym.
	ifstream input(/*"Pliczek"*/ nazwa, ios::binary);
	ofstream output(/*"Pliczek_po_przejsciach"*/"SPRAWDZONY_"+nazwa, ios::binary);
	ifstream czytanie_outputu(/*"Pliczek_po_przejsciach"*/"SPRAWDZONY_" + nazwa, ios::binary);
	ofstream bledny_output(/*"Bledny_Pliczek"*/"BLEDNY_" + nazwa, ios::binary);
	//ofstream 
	
	//skonwertowanie wszystkich znakow w pliku na binarne, i schowanie ich do vectora.
	//vector<bitset<8>> viktorBP(istreambuf_iterator<char>(input), {});
	//input.clear();
	//input.seekg(0, ios::beg);
	vector<bitset<8>> *viktortBP = new vector<bitset<8>>/*(istreambuf_iterator<char>(input), {})*/;

	//Szybsze wczytywanie wartosci od istreambuf.
	stringstream ss;
	ss << input.rdbuf();
	input.close();
	string elosz = ss.str();
	(*viktortBP).resize(elosz.size());
	for (int i = 0; i < elosz.size(); i++)  (*viktortBP)[i] = elosz[i];
	//tak sie to wczytuje!

	//*viktortBP(istreambuf_iterator<char>(input), {});

	//cout << "\n" << viktorBP.size();
	//cout << "\n" << (*viktortBP).size();


	//zrzucenie wszystkiego, co bylo w vectorze, z powrotem do pliku.
	for (int i = 0; i < (*viktortBP).size(); i++)
	{

		//unsigned char konwersja = (*viktortBP)[i].to_ulong();
		//output << konwersja;

	}

	//cout << "przerobiono " << viktorBP.size() << "ciagow 8 bitowych w pliku" << endl;
	////it's working IT'S WORKING 
	//cout << "\n\n\t" << viktorBP[1] << endl;
	//bitset<8> testowy = viktorBP[1];
	//cout << testowy << endl;
	//unsigned char jescze_bardziej_testowy = testowy.to_ulong();
	//cout << jescze_bardziej_testowy << endl;

	//Sprawdzenie, czy wszystkie chary zostaly poprawnie zapisane w vectorze. (w plikach innych niz czyste txt odradzam uzywania)
	/*cout << "\n\n\n wszystkie chary(bez zadnych dodatkow): \n";
	for (auto i=viktorBP.begin(); i!=viktorBP.end(); i++)
	{ 
		cout << *i <<endl;
	}*/

	output << endl << endl;
	//Generowanie bitu parzysto�ci
	int BitParzystosci = Parzystosc((*viktortBP));
	cout << "\n\nBit Parzystosci: " << BitParzystosci;
	//output << BitParzystosci;
	//output << endl;

	//Generowanie sumy kontrolnej
	int check = CheckSum((*viktortBP));
	cout << "\n\nSuma kontrolna: " << check;
	//output << check;
	//output << endl;

	//Generowanie CRC


	//zrzucenie wszystkiego z powrotem do pliku.
	for (int i = 0; i < (*viktortBP).size(); i++) {
		unsigned char konwersja = (*viktortBP)[i].to_ulong();
		output << konwersja;
	}

	//wybor srodka poprawnosci.
	int wybor = 0;
	cout << "jaki srodek sprawdzania poprawnosci dusza chciala?\n0 - Bit Parzystosci(zalosny)\n1 - Suma Kontrolna(mniej zalosny)\n2 - CRC(najmniej zalosny (aktualnie w produkcji))\n";
	cin >> wybor;
	switch (wybor)
	{
	case 0:
		cout << "Bit Parzystosci\n";
		output << BitParzystosci;
		output << endl;
		break;
	case 1:
		cout << "Suma Kontrolna\n";
		output << check;
		output << endl;
		break;
	case 2:
		cout << "CRC (Nic nie wpisano do pliku. Mowilem, ze jeszcze nie gotowe.)\n";
		break;
	default:
		cout << "nieprawidlowa opcja. Wybrano domyslnie Bit Parzystosci\n";
		output << BitParzystosci;
		output << endl;
		break;
	}

	(*viktortBP).clear();
	czytanie_outputu.clear();
	czytanie_outputu.seekg(0, ios::beg);
	//Ponowne zczytanie do vectora.
	ss << czytanie_outputu.rdbuf();
	czytanie_outputu.close();
	(*viktortBP).resize(elosz.size());
	for (int i = 0; i < elosz.size(); i++)  (*viktortBP)[i] = elosz[i];

	//Generowanie bledow

	//typedef vector<bledy> robimy_bledy;
	//robimy_bledy* wskaznik;
	//vector <bledy> robimy_bledy;

	vector<bledy> *robimy_bledy = new vector<bledy>();
	cout << "\n\ntest" << endl;
	cout << "\n" << (*viktortBP)[0] << "\n" << (*viktortBP)[1]<<"\n\n";


	wybor = 0;
	cout << "Ile procentow(zniszczenia danych) dusza chciala? \n0 = 0.01 Procenta\n1 = 0.1 Procenta\n2 = 1 Procent\n3 = 10 Procent\t";
	cin >> wybor;
	switch (wybor)
	{
	case 0:
		cout << "0.01 Procenta\n";
		wybor = 0;
		break;
	case 1:
		cout << "0.1 Procenta\n";
		wybor = 1;
		break;
	case 2:
		cout << "1 Procent\n";
		wybor = 2;
		break;
	case 3:
		cout << "10 Procent\n";
		wybor = 3;
		break;
	default:
		cout << "nieprawidlowa opcja. Wybrano domyslnie 0.01 Procenta\n";
		wybor = 0;
		break;
	}


	bool powtorzenia = 0;
	cout << "Czy dusza chce zeby bledy mogly sie nadpisywac?\n0 - nie\n1 - tak\n";
	cin >> powtorzenia;
	switch (powtorzenia)
	{
	case 0:
		cout << "Brak powtorzen.";
		powtorzenia = 0;
		break;
	case 1:
		cout << "Wybrano powtorzenia";
		powtorzenia = 1;
		break;
	default:
		cout << "\nnieprawidlowa opcja. Wybrano brak powtorzen\n";
		powtorzenia = 0;
		break;
	}

	GeneracjaBledow(powtorzenia,wybor, viktortBP, robimy_bledy);
	//cout << "\n\nfinal test: " << (*robimy_bledy)[0].poprzednia_wartosc;

	//zrzucenie wszystkiego razem z bledami do pliku.
	for (int i = 0; i < (*viktortBP).size(); i++){
		unsigned char konwersja = (*viktortBP)[i].to_ulong();
		bledny_output << konwersja;
	}

	cin.get();
	cin.get();
	//system("Pause");
}













/*

int i = 't';
cout << i << "\n";

string bitsetTest = bitset<8>(128).to_string();
cout << bitsetTest << "\n";

unsigned long decimal = bitset<8>('t').to_ulong();
cout << decimal << "\n";

*/



/*
char testowa = 0;

while (Pliczek >> testowa)
{
string binTest = DoBinarnych(testowa);
cout << binTest;
Binarne << binTest;

}*/



/*
//policzenie ilosci charow w pliku.
char c;
int ileCharow = 0;
while ((Pliczek.get(c), Pliczek.eof()) == false) { ileCharow++; }
cout << ileCharow << endl;

//Umieszczenie wskaznika na poczatek pliku.
Pliczek.clear();
Pliczek.seekg(0, ios::beg);
*/