#include "plant.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;

size_t k = 0;
vector <size_t> M;
size_t H = 0;
vector <double> Y;
size_t P = 0;
double Ynom = 0;
size_t N = 0;
vector <double> A;
double C = 0;
double U = 0;
double C1 = 0;
vector <double> X;

void Vvod() 
{
	bool fl = true;
	//ввод числа датчиков опрашиваемых на объекте 
	while (fl) 
	{
		cout << "Введите число датчиков ";
		cin >> k;
		if (k > 0 && k < 79) 
		{
			fl = false;
		}
		else
		{
			cout << "Ошибка: введите корректное число больше 0 но меньше 79";
		}
	}
	M.resize(k);
	A.resize(k);
	X.resize(k);
	//Y.resize(k);
	//Ввод использующихся каналов
	for (size_t i = 0; i < k; i++)
	{
		fl = true;
		while (fl)
		{
			cout << "Введите номер датчика M[" << i << "] для опроса (1-6 или 11-90) ";
			cin >> M[i];
			if (M[i] < 91 && M[i] > 10)
			{
				fl = false;
			}
			if (M[i] > 0 && M[i] < 7 ) 
			{
				fl = false;
			}
			if(M[i] < 0)
			{
				cout << "Ошибка: неправильный диапазон" << "\n";
			}
			if (M[i] < 11 && M[i] > 6) 
			{
				cout << "Ошибка: неправильный диапазон" << "\n";
			}
			if (M[i] > 90) 
			{
				cout << "Ошибка: неправильный диапазон" << "\n";
			}
		}
	}
	fl = true;
	//Ввод номера датчика для особо важного измерения
	cout << "Номер датчика для особо важного измерения (11-90) ";
	while (fl)
	{
		cin >> H;
		if (H > 10 && H < 91)
		{
			fl = false;
		}
		else
		{
			cout << "Ошибка: требуется натуральное число" << "\n";
		}
	}

	fl = true;
	//Ввод номера датчика по которому на объект будет подаваться управляющее воздействие
	cout << "Номер канала по которому на объект будет подаваться управляющее воздействие(7-10) ";
	while (fl)
	{
		cin >> P;
		if (P > 6 && 11 > P)
		{
			fl = false;
		}
		else
		{
			cout << "Ошибка: неправильный диапазон" << "\n";
		}
	}

	fl = true;
	//Ввод Yном
	cout << "Введите номинальное значение отклика ";
	while (fl)
	{
		cin >> Ynom;
		if (Ynom > 0)
		{
			fl = false;
		}
		else
		{
			cout << "Ошибка: неправильный диапазон" << "\n";
		}
	}
	fl = true;
	//Ввод числа повторений измерений
	cout << "Введите длительность работы программы (раз) ";
	while (fl)
	{
		cin >> N;
		if (N > 0)
		{
			fl = false;
		}
		else
		{
			cout << "Ошибка: введите натуральное число" << "\n";
		}
	}
	Y.resize(N);
	//Ввод коэффициентов
	for (size_t i = 0; i < k; i++)
	{
		fl = true;
		while (fl)
		{
			cout << "Введите " << i << " - й коэффициент, определяющий закон управления ";
			cin >> A[i];
			if (A[i] != 0)
			{
				fl = false;
			}
			else
			{
				cout << "Ошибка: неправильный диапазон" << "\n";
			}
		}
	}

}



int main() 
{
	setlocale(LC_ALL, "Russian");
	//инициализация оу
	Plant plant;
	plant_init(plant);
	Vvod();
	//опрос каналов и запись их в X[i]
	cout << endl;
	cout << "Внимание!В случае если величина управляющего значения будет выходить за рамки допустимых, она будет приведена к верхней(нижней) грани допустимых значений"<<endl<<endl;
	cout << " №       ";

	for (size_t i = 0; i < k; i++)
	{
		cout << " X" << i +1 << "      ";
	}

	cout << "  U        " << "   Y        " << "   C        ";

	cout << endl;

	for (size_t j = 0; j < N; j++)
	{
		if (j < 9) 
		{
			cout << " " <<j + 1 << "   ";
		}
		else 
		{
			cout << j + 1 << "   ";
		}

		for (size_t i = 0; i < k; i++)
		{
			X[i] = plant_measure(M[i], plant);
			if (X[i]>0) 
			{
				cout << " ";
			}
			cout << X[i] << "    ";
		}
		U = A[0];
		for (size_t i = 1; i < k; i++)
		{
			U = U + (A[i] * X[i]);
		}

		cout << U << "      ";
		
		switch (P)
		{
		case 7:
			if (U > 70)
			{
				U = 70;
			}
			if (U < -70) 
			{
				U = -70;
			}
			if (U <= 70 && U >= -70)
			{
				U = U;
			}
			//cout << "новое значение U=" << U<<endl;
			break;
		case 8:
			if (U>3)
			{
				U = 3;
			}
			if (U<-3)
			{
				U = -3;
			}
			if (U <= 3 && U >= -3)
			{
				U = U;
			}
			//cout << "новое значение U=" << U<<endl;
			break;
		case 9:
			if (U > 5)
			{
				U = 5;
			}
			if (U < -5)
			{
				U = -5;
			}
			if (U <= 5 && U >= -5)
			{ 
				U = U; 
			}
			//cout << "новое значение U=" << U<<endl;
			break;
		case 10:
			if (U > 2.5)
			{
				U = 2.5;
			}
			if (U < -2.5)
			{
				U = -2.5;
			}
			if (U <= 2.5 && U >=-2.5)
			{
				U = U;
			}
			//cout << "новое значение U=" << U<<endl;
			break;
		default:
			break;
		}

		plant_control(P, U, plant);
		Y[j] = plant_measure(H, plant);
		cout <<Y[j] << "      ";
		C += pow( (Y[j] - Ynom), 2 );
		cout << C << endl;
	}





	cout << endl;
	C1 = C / N;
	cout << "C1=" << C1 << endl;
}