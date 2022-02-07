#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;

class Student {
	string name, surname;
	int* homework;
	int exam;
	double final_grade;
	int size;
public:

	Student(int s)
	{
		name = "";
		surname = "";
		exam = 0;
		final_grade = 0;
		size = s;
		homework = new int[size];

	}

	Student(string a, string b, int s)
	{
		size = s;
		name = a;
		surname = b;
		if (size > 0)
		{
			homework = new int[size];
		}
		else
		{
			homework = NULL;
		}
		exam = 0;
		final_grade = 0;
	}

	Student(Student const& data)
	{
		if (data.homework != NULL)
		{
			this->size = data.size;
			if (this->size > 0)
			{
				this->homework = new int[this->size];
				for (int i = 0; i < this->size; i++)
				{
					this->homework[i] = data.homework[i];
				}
			}
			else
			{
				this->homework = NULL;
			}
		}
		this->name = data.name;
		this->surname = data.surname;
		this->exam = data.exam;

	}

	Student& operator=(Student const& data)
	{
		if (data.homework != NULL)
		{
			this->size = data.size;
			if (this->size > 0)
			{
				this->homework = new int[this->size];
				for (int i = 0; i < this->size; i++)
				{
					this->homework[i] = data.homework[i];
				}
			}
			else
			{
				this->homework = NULL;
			}
		}
		this->name = data.name;
		this->surname = data.surname;
		this->exam = data.exam;
		return *this;
	}

	~Student()
	{
		if (homework != NULL)
		{
			delete[] homework;
		}
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
	double getFinalGrade()
	{
		return final_grade;
	}

	int getExam()
	{
		return exam;
	}
	int* getHomework()
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
	void setFinalGrade(double e)
	{
		this->final_grade = e;
	}
	void setHomework(int* h)
	{
		if (h != NULL)
		{
			if (size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					this->homework[i] = h[i];
				}
			}
		}
		else
		{
			this->homework = NULL;
		}
	}


};
class student_array {
	vector<Student> stdarray;
	vector<double> finalGrade;
	vector<Student> lessThanFive;
	vector<Student> greaterThanFive;

	int totalStudent;

public:
	
	student_array(int entries)
	{
		this->totalStudent = entries;
	}

	int generateScore()
	{
		int random = rand() % 10;
		return random;
	}



	void getFileData()
	{
		ifstream fin;

		string fileName = to_string(totalStudent) + "//kursiokai_" + to_string(totalStudent) + ".txt";
		fin.open(fileName);



		if (fin.is_open()) {



			string temp1, temp2;

			int temp_homework[5];

			int exam;

			double avg = 0;

			double final_Grade = 0;


			Student obj(5);


			for (int j = 0; j < totalStudent; j++)
			{


				fin >> temp1;
				fin >> temp2;

				obj.setSurname(temp1);
				obj.setName(temp2);

				for (int i = 0; i < 5; i++)
				{
					fin >> temp_homework[i];
				}

				obj.setHomework(temp_homework);
				fin >> exam;
				obj.setExam(exam);
				avg = Average(&obj);
				final_Grade = (0.4 * avg) + (0.6 * obj.getExam());
				stdarray.push_back(obj);
				finalGrade.push_back(final_Grade);
			}

			for (int i = 0; i < totalStudent; i++) {
				stdarray.at(i).setFinalGrade(finalGrade.at(i));
			}

		}
		else {
			cout << "Fail To Open Input FIle.\n";
		}
		fin.close();
	}
	bool IsSurnameEqual(Student a, Student b)
	{
		return (a.getSurname().compare(b.getSurname()) == 0);
	}
	double findMedian(int* a, int n)
	{
		vector<int> values;

		for (int i = 0; i < n; i++) {
			values.push_back(a[i]);
		}
		sort(values.begin(), values.end());

		if (n % 2 != 0)
			return (double)a[n / 2];

		return ((double)a[(n - 1) / 2] + (double)a[n / 2]) / 2.0;
	}

	void printOutputToFile()
	{
		ofstream fout;
		string fileName = to_string(totalStudent) + "//" + to_string(totalStudent) + "_vargsiukaiStudents.txt";
		fout.open(fileName);
		ofstream fout1;
		string fileName1 = to_string(totalStudent) + "//" + to_string(totalStudent) + "_kietiStudents.txt";
		fout1.open(fileName1);


		if (fout.is_open() && fout1.is_open()) {


			fout << "Pavarde\t\t\t Vardas\t\t\tGalutinis (Vid.)\tGalutinis (Med.)\n";
			fout << "---------------------------------------------------------------------------------\n";
			fout1 << "Pavarde\t\t\t Vardas\t\t\tGalutinis (Vid.)\tGalutinis (Med.)\n";
			fout1 << "--------------------------------------------------------------------------------\n";

			const char separator = ' ';
			const int nameWidth = 25;
			const int numWidth = 25;
			string name = "";
			string innerName = "";
			int position1 = 0, position2 = 0;
			double value = 0;

			for (auto it = stdarray.begin(); it != stdarray.end(); it++)
			{
				name = it->getSurname();
				for (auto itt = lessThanFive.begin(); itt != lessThanFive.end(); itt++) {
					innerName = itt->getSurname();
					position1 = innerName[innerName.size() - 1];
					position2 = name[name.size() - 1];

					if (position1 <= position2) {
						if (name.compare(innerName) == 0) {
							double median = 0;
							median = findMedian(itt->getHomework(), itt->getSize());
							median = (0.4 * median) + (0.6 * itt->getExam());
							value = it->getFinalGrade();
							fout << left << setw(nameWidth) << setfill(separator) << innerName;
							fout << left << setw(nameWidth) << setfill(separator) << itt->getName();
							fout << left << setw(numWidth) << setfill(separator) << value;
							fout << left << setw(numWidth) << setfill(separator) << median;
							fout << "\n";
							break;
						}
					}
					else {
						break;
					}
				}



			}

			for (auto it = stdarray.begin(); it != stdarray.end(); it++)
			{
				name = it->getSurname();
				for (auto itt = greaterThanFive.begin(); itt != greaterThanFive.end(); itt++) {
					innerName = itt->getSurname();
					position1 = innerName[innerName.size() - 1];
					position2 = name[name.size() - 1];

					if (position1 <= position2) {
						if (name.compare(innerName) == 0) {
							double median = 0;
							median = findMedian(itt->getHomework(), itt->getSize());
							median = (0.4 * median) + (0.6 * itt->getExam());
							value = it->getFinalGrade();
							fout1 << left << setw(nameWidth) << setfill(separator) << innerName;
							fout1 << left << setw(nameWidth) << setfill(separator) << itt->getName();
							fout1 << left << setw(numWidth) << setfill(separator) << value;
							fout1 << left << setw(numWidth) << setfill(separator) << median;
							fout1 << "\n";
							break;
						}
					}
					else {
						break;
					}
				}
				value = 0;


			}

		}

		fout.close();
		fout1.close();
	}

	double Average(Student* obj)
	{
		double avg = 0;
		int* temp = obj->getHomework();
		double sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += temp[i];
		}
		avg = sum / 5.0;
		return avg;
	}




	void thousand_template_creation() {


		if (_mkdir("1000") != -1)
		{


			ofstream fout;
			fout.open("1000//kursiokai_1000.txt", ofstream::trunc);
			string surName = "Vardas";
			string name = "Pavarde";
			if (fout.is_open()) {

				for (int i = 1; i <= 1000; i++) {
					fout << surName << i << " " << name << i << " ";
					for (int j = 0; j < 6; j++) {
						fout << generateScore() << " ";
					}
					fout << "\n";
				}

			}
			else {
				cout << "There was a problem creating \"kursiokai_1000.txt\".\n";
			}
			fout.close();

		}
		else {
			cout << "Error in creating directory 1000";
		}

	}
	void ten_thousand_template_creation() {



		if (_mkdir("10000") != -1)
		{

			ofstream fout;
			fout.open("10000//kursiokai_10000.txt", ofstream::trunc);
			string surName = "Vardas";
			string name = "Pavarde";
			if (fout.is_open()) {

				for (int i = 1; i <= 10000; i++) {
					fout << surName << i << " " << name << i << " ";
					for (int j = 0; j < 6; j++) {
						fout << generateScore() << " ";
					}
					fout << "\n";
				}

			}
			else {
				cout << "There was a problem creating \"kursiokai_10000.txt\".\n";
			}
			fout.close();
		}
		else {
			cout << "Error while making directory 10000\n";
		}


	}

	void hundred_thousand_template_creation() {

		if (_mkdir("100000") != -1)
		{
			ofstream fout;

			fout.open("100000//kursiokai_100000.txt", ofstream::trunc);
			string surName = "Vardas";
			string name = "Pavarde";
			if (fout.is_open()) {

				for (int i = 1; i <= 100000; i++) {
					fout << surName << i << " " << name << i << " ";
					for (int j = 0; j < 6; j++) {
						fout << generateScore() << " ";
					}
					fout << "\n";
				}

			}
			else {
				cout << "There was a problem creating \"kursiokai_100000.txt\".\n";
			}
			fout.close();

		}
		else {

			cout << "Error while making directory 10000\n";
		}

	}
	void one_hundred_thousand_template_creation() {

		if (_mkdir("1000000") != -1)
		{
			ofstream fout;
			fout.open("1000000//kursiokai_1000000.txt", ofstream::trunc);
			string surName = "Vardas";
			string name = "Pavarde";
			if (fout.is_open()) {

				for (int i = 1; i <= 1000000; i++) {
					fout << surName << i << " " << name << i << " ";
					for (int j = 0; j < 6; j++) {
						fout << generateScore() << " ";
					}
					fout << "\n";
				}

			}
			else {
				cout << "There was a problem creating \"kursiokai_1000000.txt\".\n";
			}
			fout.close();
		}

		else {

			cout << "Error while making directory 100000\n";
		}

	}
	void ten_hundred_thousand_template_creation() {

		if (_mkdir("10000000") != -1)
		{
			ofstream fout;
			fout.open("10000000//kursiokai_10000000.txt", ofstream::trunc);
			string surName = "Vardas";
			string name = "Pavarde";
			if (fout.is_open()) {

				for (int i = 1; i <= 10000000; i++) {
					fout << surName << i << " " << name << i << " ";
					for (int j = 0; j < 6; j++) {
						fout << generateScore() << " ";
					}
					fout << "\n";
				}

			}
			else {
				cout << "There was a problem creating \"kursiokai_10000000.txt\".\n";
			}
			fout.close();
		}
		else {

			cout << "Error while making directory 10000000\n";
		}


	}

	void sortIntoCategories() {


		for (auto it = stdarray.begin(); it != stdarray.end(); it++) {
			auto value = it->getFinalGrade();
			if (value < 5.0) {
				lessThanFive.push_back(*it);

			}
			else {
				greaterThanFive.push_back(*it);
			}
		}

	}





};
int main()
{
	student_array obj(1000);

	cout << "---------------------------------------------\n";
	cout << "      TIME SPAN's FOR 1000 STUDENT ENTRIES  |\n";
	cout << "---------------------------------------------\n\n";


	clock_t tStart = clock();
	obj.thousand_template_creation();
	printf("For File Creation: %.2fs\n\n", (clock() - (double)tStart) / CLOCKS_PER_SEC);

	tStart = clock();
	obj.getFileData();
	printf("For Retrieving Data From File: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);

	tStart = clock();
	obj.sortIntoCategories();
	printf("For Sorting Into Categories: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);

	tStart = clock();
	obj.printOutputToFile();
	printf("For Printing Output To FIle: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);


		student_array obj1(10000);
	
		cout << "---------------------------------------------\n";
		cout << "    TIME SPAN's FOR 10,000 STUDENT ENTRIES  |\n";
		cout << "---------------------------------------------\n\n";
		
		tStart = clock();
		obj1.ten_thousand_template_creation();
		printf("For File Creation: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj1.getFileData();
		printf("For Retrieving Data From File: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj1.sortIntoCategories();
		printf("For Sorting Into Categories: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj1.printOutputToFile();
		printf("For Printing Output To FIle: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		student_array obj2(100000);
	
		cout << "---------------------------------------------\n";
		cout << "   TIME SPAN's FOR 100,000 STUDENT ENTRIES  |\n";
		cout << "---------------------------------------------\n\n";
	
	
		tStart = clock();
		obj2.hundred_thousand_template_creation();
		printf("For File Creation: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj2.getFileData();
		printf("For Retrieving Data From File: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj2.sortIntoCategories();
		printf("For Sorting Into Categories: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj2.printOutputToFile();
		printf("For Printing Output To FIle: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		student_array obj3(1000000);
	
		cout << "---------------------------------------------\n";
		cout << " TIME SPAN's FOR 1,000,000 STUDENT ENTRIES  |\n";
		cout << "---------------------------------------------\n\n";
	
	
		tStart = clock();
		obj3.one_hundred_thousand_template_creation();
		printf("For File Creation: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj3.getFileData();
		printf("For Retrieving Data From File: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj3.sortIntoCategories();
		printf("For Sorting Into Categories: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj3.printOutputToFile();
		printf("For Printing Output To FIle: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		student_array obj4(10000000);
	
		cout << "---------------------------------------------\n";
		cout << "TIME SPAN's FOR 10,000,000 STUDENT ENTRIES  |\n";
		cout << "---------------------------------------------\n\n";
	
	
		tStart = clock();
		obj4.ten_hundred_thousand_template_creation();
		printf("For File Creation: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj4.getFileData();
		printf("For Retrieving Data From File: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj4.sortIntoCategories();
		printf("For Sorting Into Categories: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	
		tStart = clock();
		obj4.printOutputToFile();
		printf("For Printing Output To FIle: %.2fs\n\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);

}