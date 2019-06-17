#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
mutex m;
class accaunt {
public:
	accaunt() :anun("\0"), azganun("\0"), gumar(0) {}
	accaunt(const string& anun1, const  string& azganun1, const int gumar1)
		:anun(anun1)
		, azganun(azganun1)
		, gumar(gumar1)
	{}
	accaunt(const accaunt& other)
	{
		anun = other.anun;
		azganun = other.azganun;
		gumar = other.gumar;
	}
	friend void transfer(int gumar, accaunt&, accaunt&);
	friend void mnacordi_harcum(accaunt&);
private:
	friend istream& operator<<(istream, const accaunt&);
	string anun;
	string azganun;
	int gumar;
};


void mnacordi_harcum(accaunt& myAccaount)
{
	m.lock();
	for (int i = 0; i < myAccaount.anun.size(); ++i)
	{
		cout << myAccaount.anun[i];
	}
	cout << " ";
	for (int i = 0; i < myAccaount.azganun.size(); ++i)
	{
		cout << myAccaount.azganun[i];
	}
	cout << "on accaunt have " << myAccaount.gumar << " dram" << endl;
	m.unlock();
}


void transfer(int gumar11, accaunt& other, accaunt& other1)
{
	int k = other1.gumar + gumar11;
	m.lock();
	other.gumar = other.gumar - gumar11;
	other1.gumar = other1.gumar + gumar11;
	if (other1.gumar == k) { cout << "transaction ok ,hdm petqa? \n"; }
	else if (other1.gumar != k)
	{
		cout << "transaction failed: \n";
	}
	m.unlock();
}
int main()
{
	int gumar = 40000;
	accaunt obj("Gevorg", "Ayvazyan", 100000);
	accaunt obj1("Davit", "Tevanyan", 300000);
	thread th(transfer, gumar, ref(obj), ref(obj1));
	thread th1(mnacordi_harcum, ref(obj));
	th.join();
	th1.join();
	system("pause");
}