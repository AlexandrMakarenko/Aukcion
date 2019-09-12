
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "windows.h"
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::getline;
using namespace std;


void cls()
{
	if (system("clear")) system("cls"); //очистка экрана
}


class Lot
{
public:
	string name;
	double startPrice = 0;
	Lot()
	{}
	~Lot()
	{}
};


class Aukcioner
{
private:
	string FI; // Фамилия, имя
public:
	int id = 0;
	Aukcioner() {}
	Aukcioner(string FI, int id)
	{
		this->FI = FI;
		this->id = id;
	}
	~Aukcioner() {}
	void setFI(string FI)
	{
		this->FI = FI;
	}
	string getFI()
	{
		return FI;
	}
};

class AukcionerPool
{
private:
	struct PoolRecord
	{
		Aukcioner* instance;
		bool    in_use;
	};

	std::vector<PoolRecord> m_pool;

public:
	Aukcioner* createNewObject()
	{
		for (size_t i = 0; i < m_pool.size(); ++i)
		{
			if (!m_pool[i].in_use)
			{
				// переводим объект в список используемых
				m_pool[i].in_use = true;
				return m_pool[i].instance;
			}
		}
		// если не нашли свободный объект, то расширяем пул
		PoolRecord record;
		record.instance = new Aukcioner;
		record.in_use = true;

		m_pool.push_back(record);

		return record.instance;
	}

	void deleteAukcioner(Aukcioner* aukcioner)
	{
		// в реальности не удаляем, а лишь помечаем, 
		// что объект свободен
		for (size_t i = 0; i < m_pool.size(); ++i)
		{
			if (m_pool[i].instance == aukcioner)
			{
				m_pool[i].in_use = false;
				break;
			}
		}
	}

	virtual ~AukcionerPool()
	{
		// теперь уже "по-настоящему" удаляем объекты
		for (size_t i = 0; i < m_pool.size(); ++i)
			delete m_pool[i].instance;
	}
};

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	int start = clock(); // засекаем время старта
	setlocale(LC_CTYPE, "rus");
	Lot my_lot;

	
		cout << "\nВведите наименование лота, который выставляете на продажу : ";
		getline(cin, my_lot.name);    //вводим имя лота
		cout << "\nВведите стартовую стоимость лота: ";
		cin >> my_lot.startPrice;
		ofstream lot("Лоты.txt", std::ios::app); // открытие файла Лоты для записи информации о лоте в конец файла
												 // функция проверки на открытие файла с Лотами и запись в него или выход из программы при ошибке.
		if (lot.is_open())
		{
			lot << "Наименование лота - " << my_lot.name << endl << "  стартовая цена составляет - " << my_lot.startPrice << endl;
			cout << "\nИдет сохранение данных о лоте.\n\n" << endl;
			Sleep(500);
			cout << "\nВсе данные о лоте сохранены." << endl;
		}
		else
		{
			cout << "\nДанные о лоте не были сохранены. Пожалуйста, попробуйте заново\n\n";
			return -1;        // код ошибки при не открытии файла с данными о лоте
		}
		Sleep(2000);
		cls();
		cout << "\nТеперь зарегистрируем участников аукциона.";
		cout << "\nВведите количество участников : ";
		int kol_y4;                //отвечает за количество участников аукциона
		cin >> kol_y4;
		Aukcioner* y4_ki = new Aukcioner[kol_y4];
		ofstream player("Участники.txt", std::ios::app); // открытие файла Участники для записи в него участников аукциона в конце файла
		player << "\n\n\nУчастники аукциона за - " << my_lot.name << endl; //отступ в файле для красивого оформления
		//Функция ввода участников аукциона с последующей записью в файл
		for (int i = 0; i < kol_y4; i++)
		{
			cout << "\nВведите Фамилию и Имя участника ";
			string fam = "";
			getline(cin, fam);
			if (fam == "")
				getline(cin, fam);
			cout << "Номер участника : " << i + 1;
			y4_ki[i].setFI(fam);
			y4_ki[i].id = i;
			player << "Участник №" << i + 1 << ".  Фамилия и Имя - " << fam << endl; //запись в файл каждого введенного участника
		}
		Sleep(2000);
		cls();
		int num;
		cout << "\nНапоминание - ставка поднимает стоимость на 5%"<< endl;
		cout << "Введите 1, чтобы начать аукцион.\t";
		cin >> num;
		cls();
		ofstream stavki("Ставки.txt", std::ios::trunc); //создаем файл, в котором будут храниться данные 
													 // о том, какой id сделал ставку

		bool check = true; //нужна для проверки

		while (num > 0)
		{


			if ((num > kol_y4) | (num < 0))
			{
				cout << "Введены не правильные данные об участнике.";
				cout << "Ошибочка";
				check = false;
				break;
			}


			{
				cout << "\nЛот:  " << my_lot.name << "\nцена:  " << my_lot.startPrice;
				cout << "\nВведите номер участника поднявшего ставку - ";
				cin >> num;
				my_lot.startPrice = (my_lot.startPrice / 100) * 105;
				cls();
				if (num == 0)
					int b;
				else if (num > 9)
					stavki << num << " ";
				else
				{
					stavki << num << "  ";
				}
			}

		}

		stavki.close();
		ifstream stavki2("Ставки.txt");
		stavki2.std::ios_base::in; // открываем файл для чтения

		if (check == true) {

			cout << "\nСпасибо за внимание. Лот был продан.";
			cout << "\nПобедитель аукциона участник с id - ";
			stavki2.seekg(-3, ios::end);
			string last;  //строка для записи последнего номера, поднявшего ставку
			stavki2 >> last;
			cout << last;
			lot << "Цена продажи составила - " << my_lot.startPrice << "\n\n\n\n" << endl; //запись финальной цены лота в файл лот

			int end = clock();
			int t = (end - start) / CLOCKS_PER_SEC;// команда CLOCKS_PER_SEC 
											   //нужна для перевода результата функции clock в секунды
			cout << "\n\n\n\n\nВремя работы: " << t << " секунд\n";
			system("pause");

		}
		else
		{
			cout << "\nВозникла ошибка. \nПриносим свои извинения. \nПопробуйте в другой раз" << endl;
			lot << "\nСлучилась беда и кажется всё сломалось." << endl;

			int end = clock();
			int t = (end - start) / CLOCKS_PER_SEC;// команда CLOCKS_PER_SEC 
											   //нужна для перевода результата функции clock в секунды
			cout << "\n\n\n\n\nВремя работы: " << t << " секунд\n";
			system("pause");

		}

		lot.close();     //закрытие файла Лот
	
	return 0;
}

