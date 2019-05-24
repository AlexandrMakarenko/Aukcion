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
	if (system("clear")) system("cls"); //������� ������
}


class Lot
{
public:
	string name;
	double startPrice;
	Lot()
	{}
	~Lot()
	{}
};


class Aukcioner
{
private:
	string FI; // �������, ���
public:
	int id;
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
                if (! m_pool[i].in_use)
                {
                    // ��������� ������ � ������ ������������
                    m_pool[i].in_use = true;
                    return m_pool[i].instance;
                }
                        }
            // ���� �� ����� ��������� ������, �� ��������� ���
            PoolRecord record;
            record.instance = new Aukcioner;
            record.in_use   = true;
 
            m_pool.push_back(record);
 
            return record.instance;
        }
 
        void deleteAukcioner(Aukcioner* aukcioner)
        {
            // � ���������� �� �������, � ���� ��������, 
            // ��� ������ ��������
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
            // ������ ��� "��-����������" ������� �������
            for (size_t i = 0; i < m_pool.size(); ++i)
                delete m_pool[i].instance;
        }
};

int main()
{
	int start = clock(); // �������� ����� ������
	setlocale(LC_CTYPE, "rus");
	Lot my_lot;
	cout << "\n������� ������������ ����, ������� ����������� �� ������� : ";
	getline(cin, my_lot.name);    //������ ��� ����
	cout << "\n������� ��������� ��������� ����: ";
	cin >> my_lot.startPrice;
	ofstream lot("����.txt", std::ios::app); // �������� ����� ���� ��� ������ ���������� � ���� � ����� �����
	// ������� �������� �� �������� ����� � ������ � ������ � ���� ��� ����� �� ��������� ��� ������.
	if (lot.is_open())
	{
		lot << "������������ ���� - " << my_lot.name << endl << "  ��������� ���� ���������� - " << my_lot.startPrice << endl;
		cout << "\n���� ���������� ������ � ����.\n\n" << endl;
		lot.close();     //�������� ����� ���
		Sleep(500);
		cout<<"\n��� ������ � ���� ���������."<<endl;
	}
	else
	{
		cout << "\n������ � ���� �� ���� ���������. ����������, ���������� ������\n\n";
		return -1;        // ��� ������ ��� �� �������� ����� � ������� � ����
	}
	cls();
	cout << "\n������ �������������� ���������� ��������.";
	cout << "\n������� ���������� ���������� : ";
	int kol_y4;                //�������� �� ���������� ���������� ��������
	cin >> kol_y4;
	Aukcioner *y4_ki = new Aukcioner[kol_y4];
	ofstream player("���������.txt", std::ios::app); // �������� ����� ��������� ��� ������ � ���� ���������� �������� � ����� �����
	player << "\n\n\n��������� ��������:" << endl; //������ � ����� ��� ��������� ����������
	//������� ����� ���������� �������� � ����������� ������� � ����
	for (int i = 0; i < kol_y4; i++)
	{
		cout << "\n������� ������� � ��� ��������� ";
		string fam = "";
		getline(cin, fam);
		if (fam == "")
		getline(cin, fam);
		cout << "����� ��������� : " << i + 1;
		y4_ki[i].setFI(fam);
		y4_ki[i].id = i;
		player << "�������� �" << i + 1 << ".  ������� � ��� - " << fam << endl; //������ � ���� ������� ���������� ���������
	}
	cls();
	int num;
	cout << "������� 1, ����� ������ �������.\t";
	cin >> num;
	cls();
	ofstream stavki("������.txt", std::ios::trunc); //������� ����, � ������� ����� ��������� ������ 
												 // � ���, ����� id ������ ������
	while (num > 0)
	{
		if (num = 0)
		{
			return 0;
		}
		else
		{
			cout << "\n���:  " << my_lot.name << "\n����:  " << my_lot.startPrice;
			cout << "\n������� ����� ��������� ���������� ������ - ";
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
	ifstream stavki2("������.txt");
	stavki2.std::ios_base::in; // ��������� ���� ��� ������ 
	cout << "\n������� �� ��������. ��� ��� ������.";
	cout << "\n���������� �������� �������� � id - ";
    stavki2.seekg(-3, ios::end);
    string last;  //������ ��� ������ ���������� ������, ���������� ������
    stavki2>>last;
    cout<<last;
    int end = clock();
    int t = (end-start)/CLOCKS_PER_SEC;// ������� CLOCKS_PER_SEC 
	                                   //����� ��� �������� ���������� ������� clock � �������
    cout<<"\n\n\n\n\n����� ������: "<<t<<" ������\n";
	system("pause");
	return 0;
}
