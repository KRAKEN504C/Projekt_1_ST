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
//Dobra dobra. Ju¿ s¹. Nie ma siê co tak o nie denerwowaæ.
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
					else { czy_juz_byla = 1; break; /*cout << GOD << "\tBYLA"; przelosowania++;*/ }
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
	return check % 256;
}


void dzielonko(int &bitek) {
	if (bitek == 0)
		bitek = 1;
	else
		bitek = 0;
}

double crc8(const vector<bitset<8>> &viktor) {
	vector<int> v_bitsetow;
	vector<int> v_dzielony;
	/*const*/ bitset<8> dzielnik = 137;

	for (int i = 0; i < viktor.size(); i++) {
		for (int j = 7; j >= 0; j--) {
			v_bitsetow.push_back(viktor[i][j]);
		}
	}

	for (int i = dzielnik.size() - 1; i >= 0; i--) {
		v_dzielony.push_back(dzielnik[i]);
	}

	for (int i = 0; i < dzielnik.size() - 1; i++)
		v_bitsetow.push_back(0);

	//dla wszystkich 4 bitowych pakietów.
	for (int i = 0; i <= v_bitsetow.size() - v_dzielony.size(); i++) {
		//przemieszcz wska¿nik na pierwsz¹ jedynkê.
		if (v_bitsetow[i] == 1) {
			//i to wszystko podziel.
			for (int j = 0; j < v_dzielony.size(); j++) {
				if (v_dzielony[j] == 1)
					dzielonko(v_bitsetow[i + j]);
			}
		}
	}

	double suma = 0;
	for (int i = 0; i < v_dzielony.size() - 1; i++) {
		suma += v_bitsetow[v_bitsetow.size() - i - 1] * pow(2, i);
	}
	return suma;
}




int main()
{
	string nazwa = "";
	cout << "Proszê podaæ nazwe z roszerzeniem tego smutnego pliku ktory odbedzie ta niezwykle okrutna procedure.:";
	cin >> nazwa;


	//srand(time(NULL));
	//Stworzenie zmiennych fstream do zarz¹dzania plikiem wejœciowym i wyjœciowym.
	ifstream input(/*"Pliczek"*/ nazwa, ios::binary);
	ofstream output(/*"Pliczek_po_przejsciach"*/"SPRAWDZONY_"+nazwa, ios::binary);
	ifstream czytanie_outputu(/*"Pliczek_po_przejsciach"*/"SPRAWDZONY_"+nazwa, ios::binary);
	ofstream bledny_output(/*"Bledny_Pliczek"*/"BLEDNY_"+nazwa, ios::binary);
	//ifstream czytanie_b_outputu(/*"Pliczek_po_przejsciach"*/"BLEDNY_" + nazwa);
	//ofstream 
	
	//skonwertowanie wszystkich znakow w pliku na binarne, i schowanie ich do vectora.
	//vector<bitset<8>> viktorBP(istreambuf_iterator<char>(input), {});
	//input.clear();
	//input.seekg(0, ios::beg);
	vector<bitset<8>> *viktortBP = new vector<bitset<8>>/*(istreambuf_iterator<char>(input), {})*/;

	//Szybsze wczytywanie wartosci od istreambuf.
	stringstream cudenko;
	cudenko << input.rdbuf();
	input.close();
	string dzialaj_plis = cudenko.str();
	(*viktortBP).resize(dzialaj_plis.size());
	for (int i = 0; i < dzialaj_plis.size(); i++)  (*viktortBP)[i] = dzialaj_plis[i];
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

	//output << endl << endl;

	//Generowanie bitu parzystoœci
	int BitParzystosci = Parzystosc((*viktortBP));
	cout << "\n\nBit Parzystosci: " << BitParzystosci;
	cout << "\nas bitset: " << bitset<8>(BitParzystosci);
	//output << BitParzystosci;
	//output << endl;

	//Generowanie sumy kontrolnej
	int check = CheckSum((*viktortBP));
	cout << "\n\nSuma kontrolna: " << check;
	cout << "\nas bitset: " << bitset<8>(check);
	//output << check;
	//output << endl;

	//Generowanie CRC
	double crc = crc8((*viktortBP));
	cout << "\n\nCRC: " << crc;
	cout << "\nas bitset: " << bitset<8>(crc);


	


	//wybor srodka poprawnosci.
	double wynikDobry = 0;
	int wybor = 0;
	cout << "\n\njaki srodek sprawdzania poprawnosci dusza chciala?\n0 - Bit Parzystosci(zalosny)\n1 - Suma Kontrolna(mniej zalosny)\n2 - CRC(najmniej zalosny (chyba gotowy))\n";
	cin >> wybor;
	switch (wybor)
	{
	case 0:
		cout << "Bit Parzystosci\n";
		//wynikDobry = 0;
		(*viktortBP).push_back('\n');
		(*viktortBP).push_back(BitParzystosci);
		//output << endl;
		//output << BitParzystosci;
		break;
	case 1:
		cout << "Suma Kontrolna\n";
		//wynikDobry = 1;
		(*viktortBP).push_back('\n');
		(*viktortBP).push_back(check);
		//output << endl;
		//output << check;
		break;
	case 2:
		cout << "CRC (chyba gotowe)\n";
		//wynikDobry = 2;
		(*viktortBP).push_back('\n');
		(*viktortBP).push_back(crc);
		//output << endl;
		//output << crc;
		break;
	default:
		cout << "nieprawidlowa opcja. Wybrano domyslnie Bit Parzystosci\n";
		//wynikDobry = 0;
		(*viktortBP).push_back('\n');
		(*viktortBP).push_back(BitParzystosci);
		//output << endl;
		//output << BitParzystosci;
		break;
	}

	int jaki_wynik = wybor;


	//zrzucenie wszystkiego z powrotem do pliku.
	for (int i = 0; i < (*viktortBP).size(); i++) {
		unsigned char konwersja = (*viktortBP)[i].to_ulong();
		output << konwersja;
	}
	input.close();
	output.close();

	cout << "\nprzed oproznieniem " << (*viktortBP).size() << "\n\n\n";

	(*viktortBP).clear();
	cout << "\npo oproznieniu " << (*viktortBP).size() << "\n\n\n";
	//czytanie_outputu.clear();
	//czytanie_outputu.seekg(0, ios::beg);
	//Ponowne zczytanie do vectora.
	stringstream cudenkov2;
	cudenkov2 << czytanie_outputu.rdbuf();
	czytanie_outputu.close();
	string chybaOK = cudenkov2.str();
	(*viktortBP).resize(chybaOK.size());
	for (int i = 0; i < chybaOK.size(); i++)  (*viktortBP)[i] = chybaOK[i];





	cout << "\npo napelnieniu " << (*viktortBP).size() << "\n\n\n";//juz ok. trzeba pamietac o zamykaniu pliku, po skorzystaniu z niego.
	//cout << "\ninny po napelnieniu " << (*viktorttBP).size() << "\n\n\n";

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

	bitset<8> wynikZly = (*viktortBP)[(*viktortBP).size()-1];

	//Wyliczenie jeszcze raz wyniku.
	switch (jaki_wynik)
	{
	case 0:
		//Generowanie bitu parzystoœci
		wynikDobry = Parzystosc((*viktortBP));
		break;
	case 1:
		//Generowanie sumy kontrolnej
		wynikDobry = CheckSum((*viktortBP));
		break;
	case 2:
		//Generowanie CRC
		wynikDobry = crc8((*viktortBP));
		break;
	default:
		break;
	}

	cout << "\n\ile powinno byc: " << bitset<8>(wynikDobry) << "\tile jest: " << wynikZly;
	if (bitset<8>(wynikDobry) == wynikZly) { cout << "\nWyniki w teorii sie zgadzaja, co nie oznacza, ze jest dobrze!"; }
	else { cout << "\nNo kto by sie spodziewal, ze w programi ktory ma za zadanie generowac w plikach bledy, powstaly bledy!"; }

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