// tema_poo3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>

using namespace std;

class Plata {
	int id;
	string date;

public:

	Plata(int i=0,string d="")
	{
		id = i;
		date.assign(d);
	}

	~Plata()
	{

	}

	int g_id() const
	{
		return id;
	}

	string g_date() const
	{
		return date;
	}


};

template <class t>
class bd {
private:
	string nume[10];
	float suma[10];
	string data[10];
	int nr_el = 0;
public:
	~bd()
	{

	}



	void afisare()
	{
		for (int i = 0; i < nr_el; i++)
		{
			cout <<i<< ": nume:" << nume[i] << " suma:" << suma[i] << " data:" << data[i]<<endl;
		}
	}

	static void afisare_descriere()
	{
		cout << "Un obiect de acest tip stocheaza tranzactile facute cu cash";
	}

	void parsare_pachet(string s)
	{
		string pachet = s;
		//	pachet.replace() // replace ':' by ' '

		
		for (int i = 0; i < pachet.length(); i++)
		{
			if (pachet[i] == '$') pachet[i] =' ';
		}


		
		std::stringstream ss;
		ss << pachet;
		string str;
		char c;
		try {
			ss >> c;
			ss >> suma[nr_el];
			ss >> nume[nr_el];
			ss >> data[nr_el];
			ss >> str;
			if (str != "s") throw - 1;
		}
		catch (int a)
		{
			cout << "pachet:" << pachet << " corupt " << endl;
			return;
		}
		nr_el++;
		
	}

};

template <>
class bd<float> {
private:
	string nume[10];
	double suma[10];
	string data[10];
	int nr_card[10];
	int nr_el = 0;
public:
	
	~bd() {

	}

	void afisare()
	{
		for (int i = 0; i < nr_el; i++)
		{
			cout << i << ": nume:" << nume[i] << " suma:" << suma[i] << " data:" << data[i] <<" nr_card:"<<nr_card[i]<< endl;
		}
	}

	static void afisare_descriere()
	{
		cout << "Un obiect de acest tip stocheaza tranzactile facute cu card";
	}



	void parsare_pachet(string s)
	{
		string pachet = s;
		//	pachet.replace() // replace ':' by ' '


		for (int i = 0; i < pachet.length(); i++)
		{
			if (pachet[i] == '$') pachet[i] = ' ';
		}



		std::stringstream ss;
		ss << pachet;
		char c;
		string str;
		try {
			ss >> c;
			ss >> suma[nr_el];
			ss >> nume[nr_el];
			ss >> data[nr_el];
			ss >> nr_card[nr_el];
			ss >> str;
			if (str != "s") throw - 1;
		}
		catch(int a)
		{
			cout << "pachet:"<<pachet<<"corupt"<<endl;
			return;
		}
		nr_el++;

	}

};




class Gestiune {
private:
	int nr_plati=0;
	unordered_map<int,Plata> m;
	bd<float> card;
	bd<int> cash;
public:
	~Gestiune()
	{

	}


	void operator +=(string plata)
	{
		
		pair<int, Plata> p = make_pair(nr_plati, *new Plata(nr_plati, plata));
		nr_plati++;
		m.insert(p);
		procesare_element(nr_plati - 1);
	}

	Gestiune& operator =(Gestiune& g)
	{
		
		memcpy(this, new Gestiune(g), sizeof(Gestiune));
		return *this;
	}


	friend istream &operator >> (istream &in,Gestiune &g)
	{
		int n;
		in >> n;
		string s;
		while (n)
		{
			in >> s;
			g += s;
			n--;
		}
		return in;
	}

	friend ostream& operator << (ostream& out, Gestiune& g)
	{
		
		for (auto it = g.m.begin(); it != g.m.end(); ++it)
		{
			out << it->second.g_id() << " " << it->second.g_date() << endl;

		}
		return out;
	}


	//tip afisare 0 pentru pachete de date,1 pt cash ,2 pt card
	void afisare_plati(int tip=0)
	{

		if(tip==0)
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			cout<<it->second.g_id()<<" "<<it->second.g_date()<<endl;
			
		}

		if (tip == 1) cash.afisare();

		if (tip == 2) card.afisare();

	}

	void testRTTI()
	{
		cout <<"card:"<< typeid(card).name()<<" cash:"<<typeid(cash).name()<<endl;
	}


	string afisare_plata(int i)
	{
		auto it = m.begin();
		while (i!=0)
		{
			it++;
			if (it == m.end()) return "";
			i--;
		}
	return it->second.g_date();
	}
	
	//card c , n numerar(cash)
	void procesare_element(int i)
	{
		string str = afisare_plata(i);
		if (str[0] == 'c')
			card.parsare_pachet(str);
		else if (str[0] == 'n')
			cash.parsare_pachet(str);
		else cout << "Pachet de date corupt" << endl;

	}
};


void citire_afisare_n_elemente()
{
	Gestiune* g;
	int n;
	cin >> n;
	g = new Gestiune[n];
	for (int i = 0; i < n; i++)
		cin >> g[i];
	for (int i = 0; i < n; i++)
		cout << g[i];
}





//format pachet tip$suma$nume-prenume$Data$nr_card$caracter_de_siguranta

int main()
{
	Gestiune p;
	Gestiune b;
	//	citire_afisare_n_elemente();

	p +="c$100$ion$5-Aprilie-2019$99832$s";
	p += "c$300.2$virgil$3-Aprilie-2019$99832$s";
	p += "n$300.32$Marinica$2-Aprilie-2019$s";
	b = p;
	p += "c$400.3$Janel$1-Aprilie-2019$219832$s";
	cout << b;
	p.testRTTI();
	cout << "pachete:" << endl;

	p.afisare_plati();
	cout << endl;
	cout << "plati card:" << endl;
	p.afisare_plati(2);
	cout << endl;
	cout << "plati cash:"<<endl;
	p.afisare_plati(1);

}