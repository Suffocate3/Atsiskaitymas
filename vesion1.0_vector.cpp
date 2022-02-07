#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

class student_grade {
	string name, surname;
	vector<int> homework;
	int exam;
	double final_grade_med,final_grade_avg;
	int size;
public:
	student_grade()
	{

	}
	student_grade(string a, string b, int s)
	{
		size = s;
		name = a;
		surname = b;
		exam = 0;
	}

	int getSize()
	{
		return size;
	}
	string getName()
	{
		return name;
	}
	string getSurname()
	{
		return surname;
	}
	double getFinalgrade_avg()
	{
		return final_grade_avg;
	}
	double getFinalgrade_med()
	{
		return final_grade_med;
	}
	void setFinalgrade(double e,double a)
	{
		final_grade_med = e;
		final_grade_avg = a;
	}
	int getExam()
	{
		return exam;
	}
	vector<int> getHomework()
	{
		return homework;
	}
	void setName(string a)
	{
		name = a;
	}
	void setSurname(string b)
	{
		surname = b;
	}
	void setExam(int a)
	{
		exam = a;
	}
	void setHomework(vector<int> h)
	{
		for (int i = 0; i < h.size(); i++)
			homework.push_back(h[i]);
	}

};
class student_array {
	student_grade* stdarray;
	int choice;
	int total_row;
	int total_homework;
	int func;
public:
	student_array()
	{

	}
	student_array(int n, int f, int n_homework = 0, int nresults = 0)
	{
		choice = n;
		func = f;
		if (choice == 0)	
		{
			int count = getNoOfStd();
			if (count != 0)
			{
				stdarray = new student_grade[count];
				total_row = count;
				getFileData();
			}
			else
			{
				cout << "\nPlease input some data in kursiokai.txt\n";
			}


		}
		else if (choice == 1)
		{
			total_homework = n_homework;
			stdarray = new student_grade[nresults];
			total_row = nresults;
			for (int i = 0; i < nresults; i++)
			{
				string a, b;
				vector<int> temp_homework;
				cout << "\nEnter name: ";
				cin >> a;
				cout << "Enter Surname: ";
				cin >> b;
				stdarray[i] = student_grade(a, b, n_homework);
				srand(time(0));
				for (int j = 0; j < n_homework; j++)
				{
					temp_homework.push_back(generateScore());
				}
				stdarray[i].setHomework(temp_homework);
				stdarray[i].setExam(generateScore());

				double avg,avg1;
				//if (func == 0)
				{
					avg = Average(stdarray[i]);
				
					avg1 = findMedian(stdarray[i].getHomework(), stdarray[i].getSize());
				}
				double final_result = (0.4 * avg) + (0.6 * stdarray[i].getExam());
				double final_result1 = (0.4 * avg1) + (0.6 * stdarray[i].getExam());
				stdarray[i].setFinalgrade(final_result,final_result1);
			}

		}

	}
	int generateScore()
	{
		int random = rand() % 10;
		return random;
	}
	int tokenizer(string str)
	{
		stringstream ss(str);
		string word;
		int count = 0;
		while (ss >> word)
		{
			count++;
		}
		count -= 3;
		total_homework = count;
		return count;
	}
	void getFileData()
	{
		ifstream fin;
		string str;
		int count = 0;
		fin.open("kursiokai.txt");

		if (fin.is_open()) 
		{
			getline(fin, str);
			if (str.length() != 0)
			{
				count = tokenizer(str);
				total_homework = count;
			}

		}
		fin.close();
		fin.open("kursiokai.txt");

		if (fin.is_open())
		{   
			for (int j = 0; j < total_row; j++)
			{
				string temp1, temp2;
				int temp;
				vector<int> temp_homework;
				int exam;
				fin >> temp1;
				fin >> temp2;
				stdarray[j] = student_grade(temp1, temp2, count);
				for (int i = 0; i < total_homework; i++)
				{
					fin >> temp;
					temp_homework.push_back(temp);
				}
				stdarray[j].setHomework(temp_homework);
				fin >> exam;
				stdarray[j].setExam(exam);
				double avg,avg1;
				//if (func == 0)
				{
					avg = Average(stdarray[j]);
				}
				
				{
					avg1 = findMedian(stdarray[j].getHomework(), stdarray[j].getSize());
				}
				double final_result = (0.4 * avg) + (0.6 * stdarray[j].getExam());
				double final_result1 = (0.4 * avg1) + (0.6 * stdarray[j].getExam());
				stdarray[j].setFinalgrade(final_result,final_result1);
			}
		}
		fin.close();
	}
	void sort(vector<int> a, int n)
	{
		int i, j, min, temp;
		for (i = 0; i < n - 1; i++)
		{
			min = i;
			for (j = i + 1; j < n; j++)
				if (a[j] < a[min])
					min = j;
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
	double findMedian(vector<int> a, int n)
	{
		
		sort(a, n);

		if (n % 2 != 0)
			return (double)a[n / 2];

		return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
	}

	void bubbleSortSurname(student_grade arr[], int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++)
		{

		
			for (j = 0; j < n - i - 1; j++)
				if (arr[j].getSurname().compare(arr[j + 1].getSurname()) > 0) {
					student_grade temp(arr[j]);
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
		}
	}
	void bubbleSortName(student_grade arr[], int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++)
		{

			for (j = 0; j < n - i - 1; j++)
				if (arr[j].getName().compare(arr[j + 1].getName()) > 0) {

					student_grade temp(arr[j]);
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
		}
	}

	void print()
	{
			cout << "Pavarde\t\tVardas\t\tGalutinis(Ved.)\t\tGalutinis(Med.) \n";
		for (int i = 0; i < total_row; i++)
		{
			bubbleSortSurname(stdarray, total_row);
			bubbleSortName(stdarray, total_row);
			cout << stdarray[i].getName() << "\t\t" << stdarray[i].getSurname() << "\t\t";
			cout << stdarray[i].getFinalgrade_avg() <<"\t\t" ;
			cout << stdarray[i].getFinalgrade_med() << "\n";
		}
	}
	int getNoOfStd()
	{
		ifstream fin;
		string str;
		int count = 0;
		fin.open("kursiokai.txt");
		if (fin.is_open())
		{   
			string str;
			while (getline(fin, str))
			{
				count++;
			}
		}
		fin.close();

		return count;

	}
	double Average(student_grade obj)
	{
		double avg;
		vector<int> temp = obj.getHomework();
		double sum=0;
		for (int i = 0; i < obj.getSize(); i++)
		{
			sum += temp[i];
		}
		avg = (1.0 * sum) / obj.getSize();
		return avg;
	}

};
int main()
{
	int choice=0, func=0, nstd=0, nhomework=0;
	cout << "Enter Your Choice:\n1.Fetch data from file\n2.Generate data randomly\nYour Choice: ";
	cin >> choice;

	if (choice == 2)
	{
		cout << "\nNumber of Students? ";
		cin >> nstd;
		cout << "Number of Homeworks? ";
		cin >> nhomework;
		cout << "\n\n";
	}
	student_array obj(choice - 1, func - 1, nhomework, nstd);
	obj.print();
}