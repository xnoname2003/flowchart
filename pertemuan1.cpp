#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	
	//contoh1
	cout << "" << endl;
	cout << " Selamat Datang " << endl;
	cout << " Pada Praktikum Algoritma dan Pemrograman " << endl;
	
	cout << "" << endl;
	cout << "" << endl;
	
	//contoh2
	char huruf;
	
	cout << " Masukan sebuah Huruf: "; cin >> huruf;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Huruf yang anda masukan adalah: " << huruf << endl;
	
	cout << "" << endl;
	cout << "" << endl;
	
	//contoh3
	int A, B;
	
	cout << " Menampilkan nilai A dan B " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Masukan nilai A: "; cin >> A;
	cout << " Masukan nilai B: "; cin >> B;
	
	A = A + 2;
	B = B - 4;
	
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Nilai A adalah " << A << " dan B adalah " << B << endl;
	
	cout << "" << endl;
	cout << "" << endl;
	
	//contoh4
	int C;
	float D;
	cout << " Menampilkan nilai C dan D " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Masukan nilai C: "; cin >> C;
	C = C + 22;
	D = sqrt(C);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Nilai C adalah " << C << " dan D adalah " << D << endl;
	
	
	cin.get();
	return 0;
}