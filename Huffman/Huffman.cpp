// Huffman.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop3_naloga3: Huffmanovo kodiranje */

/* Napišite program, ki za dani niz znakov, poišèe Huffmanovo kodiranje in ga izpiše na
   ekran. Vsak niz v vhodni datoteki bo v svoji vrstici, vhodna datoteka lahko vsebuje veè
   nizov. Za vsak niz najprej (po abecednem vrstnem redu) izpišite dobljeno kodiranje v
   obliki znak  binarna koda, kjer se kode za vsak znak zapišejo v svoji vrstici. Naslednja
   vrstica naj vsebuje binarno kodo podanega niza, kjer med posameznimi kodami ne sme biti
   nobenih presledkov. */


#include "stdafx.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class CKod
{
public:
	char znak;
	string koda;
	CKod(char aZ, string aKo);
	~CKod(void);
};

class CElement
{
public:
	CElement(char aZ, int aN);
	CElement(char aZ, int aN, CElement* aL, CElement* aD);
	~CElement(void);
	char znak;
	int n;
	CElement* levi;
	CElement* desni;
	void SLD(string aKo, CElement* aV);
	void SLD1(string aKo, CElement* aV);
	void SLDv(vector<CKod*> &aT, string aK, CElement* aV);

};

class CHuffman
{
public:
	CHuffman(void);
	~CHuffman(void);
	vector<CElement*> gozd;
	vector<CElement*> frekvence;
	void TvoriVektorGozd(string aB);
	int Prestej(string aB, char aZ);
	void TvoriVektorFrekvence1(string aB);
	void TvoriVektorFrekvence(string aB);
	void Koda(string aB);
	void Preuredi(CElement* aP, CElement* aD);
	void IzpisVektorjaGozd();
	void IzpisVektorjaFrekvence();
	bool ZeVpisan(vector<CElement*> aG, char aZ);
	void Koda1(vector<CKod*> &aRe, string aB);
	void IzpisKod(vector<CKod*> aL);
	void IzpisK(string aBeseda, vector<CKod*> aL);
	void Preuredi(vector<CKod*> &aK);
	CKod* Najdi(char aZ, vector<CKod*> aL);

};


CKod::CKod(char aZ, string aKo)
{
	znak = aZ;
	koda = aKo;
}

CKod::~CKod(void)
{
}

CElement::CElement(char aZ, int aN)
{
	levi = NULL;
	desni = NULL;
	znak = aZ; 
	n = aN;
}

CElement::~CElement(void)
{
}
CElement::CElement(char aZ, int aN, CElement* aL, CElement* aD)
{
	levi = aL;
	desni = aD;
	znak = aZ; 
	n = aN;
}
void CElement::SLD(string aKo, CElement* aV)
{
	if(aV->levi == NULL && aV->desni == NULL){
		// znak in aKo
		cout << aV->znak << "   " << aKo << endl;
	} else {
		SLD(aKo+"0", aV->levi);
		SLD(aKo+"1", aV->desni);
	}
}
void CElement::SLD1(string aKo, CElement* aV)
{
	if(aV->levi == NULL && aV->desni == NULL){
		cout << aKo;
	} else {
		SLD1(aKo+"0", aV->levi);
		SLD1(aKo+"1", aV->desni);
	}
}
void CElement:: SLDv(vector<CKod*> &aT, string aK, CElement* aV)
{
	if(aV->levi == NULL && aV->desni == NULL){
		CKod* aR = new CKod(aV->znak, aK);
		aT.push_back(aR);
	} else {
		SLDv(aT, aK+"0", aV->levi);
		SLDv(aT, aK+"1", aV->desni);
	}
}

CHuffman::CHuffman(void)
{
	vector<CElement*> gozd;
	vector<CElement*> frekvence;
}

CHuffman::~CHuffman(void)
{
}
void CHuffman:: TvoriVektorGozd(string aB)
{
	for(int i = 0; i< aB.size(); i++){
		if(!ZeVpisan(gozd, aB.at(i))){
			int aR = Prestej(aB, aB.at(i));
			CElement* aT = new CElement(aB.at(i), aR);
			gozd.push_back(aT);
		}
	}
}
void CHuffman:: TvoriVektorFrekvence(string aB)
{
	for(int i = 0; i< aB.size(); i++){
		if(!ZeVpisan(frekvence, aB.at(i))){
			int aR = Prestej(aB, aB.at(i));
			CElement* aT = new CElement(aB.at(i), aR);
			frekvence.push_back(aT);
		}
	}
}
void CHuffman:: TvoriVektorFrekvence1(string aB)
{
	TvoriVektorFrekvence(aB);
	cout << endl;
	int j = 0;
	while(j < frekvence.size()){
		int i = frekvence.size()-1;
		while(i>j){
			if(frekvence.at(i)->n > frekvence.at(i-1)->n){
				CElement* aK = frekvence.at(i);
				frekvence.at(i) = frekvence.at(i-1);
				frekvence.at(i-1) = aK;
			}
			i--;
		}
		j++;
	}
}

int CHuffman:: Prestej(string aB, char aZ)
{
	int st = 0;
	for(int j = 0; j< aB.size(); j++){
		if(aB.at(j) == aZ){
			st++;
		}
	}
	return st;
}
void CHuffman:: Koda(string aB)
{
	string aK;
	string aKo;
	TvoriVektorGozd(aB);
	TvoriVektorFrekvence1(aB);
	while(gozd.size() > 1){
		Preuredi(frekvence.at(frekvence.size()-1), frekvence.at(frekvence.size()-2));
	}
	gozd.at(0)->SLD(aK, gozd.at(0));
	gozd.at(0)->SLD1(aKo, gozd.at(0));
}
void CHuffman::Preuredi(CElement* aP, CElement* aD )
{
	CElement* aR = new CElement(' ', aP->n + aD->n, aP, aD);
	gozd.pop_back();
	frekvence.pop_back();
	gozd.pop_back();
	frekvence.pop_back();
	gozd.push_back(aR);
	frekvence.push_back(aR);
	int j = 0;
	while(j < frekvence.size()){
		int i = frekvence.size()-1;
		while(i>j){
			if(frekvence.at(i)->n > frekvence.at(i-1)->n){
				CElement* aK = frekvence.at(i);
				frekvence.at(i) = frekvence.at(i-1);
				frekvence.at(i-1) = aK;
			}
			i--;
		}
		j++;
	}
}
void CHuffman:: IzpisVektorjaGozd()
{
	for(int i = 0; i< gozd.size(); i++){
		cout << gozd.at(i)->znak;
		cout << gozd.at(i)->n;
		cout << endl;
	}
}
void CHuffman:: IzpisVektorjaFrekvence()
{
	for(int i = 0; i< frekvence.size(); i++){
		cout << frekvence.at(i)->znak;
		cout << frekvence.at(i)->n;
		cout << endl;
	}
}
bool CHuffman:: ZeVpisan(vector<CElement*> aG, char aZ)
{
	for(int i = 0; i < aG.size(); i++){
		if(aG.at(i)->znak == aZ){
			return true;
		}
	}
	return false;
}
void CHuffman:: Koda1(vector<CKod*> &aRe, string aB)
{
	string aK;
	string aKo;
	TvoriVektorGozd(aB);
	TvoriVektorFrekvence1(aB);
	while(gozd.size() > 1){
		Preuredi(frekvence.at(frekvence.size()-1), frekvence.at(frekvence.size()-2));
	}
	gozd.at(0)->SLDv(aRe, aK, gozd.at(0));
	cout<< endl;
	Preuredi(aRe);
	IzpisKod(aRe);
}
void CHuffman:: IzpisKod(vector<CKod*> aL)
{
	for(int i = 0; i < aL.size(); i++){
		cout << aL.at(i)->znak << " " << aL.at(i)->koda <<endl;
	}
}
CKod* CHuffman:: Najdi(char aZ, vector<CKod*> aL)
{
	for(int i = 0; i< aL.size(); i++){
		if(aL.at(i)->znak == aZ)
			return aL.at(i);
	}
	return NULL;
}
void CHuffman:: IzpisK(string aBeseda, vector<CKod*> aL)
{
	for(int i = 0; i < aBeseda.size(); i++){
		CKod* aK = Najdi(aBeseda.at(i), aL);
		if(aK == NULL){
			cout << "Napaka";
		}else{
			cout << aK->koda;
		}
	}
}
void CHuffman:: Preuredi(vector<CKod*> &aK)
{
	int j = 0;
	while(j < aK.size()){
		int i = aK.size()-1;
		while(i>j){
			if(aK.at(i)->znak < aK.at(i-1)->znak){
				CKod* aP = aK.at(i);
				aK.at(i) = aK.at(i-1);
				aK.at(i-1) = aP;
			}
			i--;
		}
		j++;
	}
}


void Izpis(char* ime){
 ifstream dat(ime);
 if (dat.is_open()){
	 string aNiz;
	while(!dat.eof()){
		dat>>aNiz;
		CHuffman* aKod = new CHuffman();
		vector<CKod*> aT;
		aKod->Koda1(aT,aNiz);
		cout << endl;
		cout << aNiz;
		cout << endl;
	}
		dat.close();
 }
 else	
	 cout<<"Napaka pri odpiranju datoteke!";
}
vector<string> Preberi(char* ime)
{
	vector<string> aB;
 ifstream dat(ime);
 if (dat.is_open()){
	 string aNiz;
	while(!dat.eof()){
		dat>>aNiz;
		if(dat.good()){
			aB.push_back(aNiz);
		}
	}
		dat.close();
		return aB;
 }
 else{	
	 cout<<"Napaka pri odpiranju datoteke!";
	 throw "Napaka!";
 }
}
void Uredi(vector<string> &aV)
{
	int j = 0;
	while(j < aV.size()){
		int i = aV.size()-1;
		while(i>j){
			if(aV.at(i).at(0) < aV.at(i-1).at(0)){
				string aK = aV.at(i);
				aV.at(i) = aV.at(i-1);
				aV.at(i-1) = aK;
			}
			i--;
		}
		j++;
	}
}
void Izpis1(vector<string> aV)
{
	Uredi(aV);
	for(int i = 0; i< aV.size(); i++){
		CHuffman* aKod = new CHuffman();
		vector<CKod*> aT;
		cout << endl;
		cout << aV.at(i);
		aKod->Koda1(aT, aV.at(i));
		aKod->IzpisK(aV.at(i), aT);
		cout << endl;
	}

}
int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> aST = Preberi("Huf.txt");
	Izpis1(aST);
	
	cin.ignore();
	cin.get();
	return 0;
}



