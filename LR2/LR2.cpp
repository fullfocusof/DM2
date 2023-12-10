#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

vector<vector<bool>> adjacencyM;
vector<int> variety;
int vars;

void Read_g()
{
	ifstream ifs("data.txt");
	if (ifs.is_open())
	{
		ifs >> vars;

		adjacencyM.resize(vars, vector<bool>(vars));

		variety.resize(vars);
		for (int i = 0; i < variety.size(); i++)
		{
			variety[i] = i + 1;
		}

		while (!ifs.eof())
		{		
			int v, u;
			ifs >> v;
			ifs >> u;

			int uID, vID;
			vector<int>::iterator uIT = find(variety.begin(), variety.end(), u);
			vector<int>::iterator vIT = find(variety.begin(), variety.end(), v);
			if (uIT == variety.end() || vIT == variety.end())
			{
				cerr << "Неверные данные";
			}

			uID = std::distance(variety.begin(), uIT);
			vID = std::distance(variety.begin(), vIT);
			adjacencyM[vID][uID] = true;

			/*if ()
			{
				cerr << "Неверные данные";
			}*/


		}
		cout << "Данные успешно считаны";	
	}
	else
	{
		cerr << "Ошибка открытия файла";
	}
	ifs.close();
}

int getZeroCol()
{
	for (int i = 0; i < adjacencyM.size(); i++)
	{
		bool allZero = true;
		for (int j = 0; j < adjacencyM.size(); j++)
		{
			if (adjacencyM[j][i])
			{
				allZero = false;
				break;
			}
		}
		if (allZero)
		{
			return i;
		}
	}

	return -1;
}

void TopologicSort(vector<int>& result)
{
	while (!adjacencyM.empty())
	{
		int colID = getZeroCol();
		if (colID != -1)
		{
			result.push_back(variety[colID]);
			variety.erase(variety.begin() + colID);
			adjacencyM.erase(adjacencyM.begin() + colID);
			for (auto& row : adjacencyM)
			{
				row.erase(row.begin() + colID);
			}
		}
		else
		{
			cerr << "Неверные данные(матрица не пуста и нет столбца из нулей)";
			return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	vector<int> result;

	Read_g(); cout << endl;
	system("pause");

	TopologicSort(result);

	system("cls");
	cout << "Линейно упорядоченное множество: ";
	for (auto& el : result)
	{
		cout << el << " ";
	}
	cout << endl;
	system("pause");
}