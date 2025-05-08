#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

class Student {
	
	string FIO;
	string group;
	int book_number;
	vector<int> score;
	float mean = 0;
public:
	
	Student(string& f, string& g, int& n, vector<int>& s) {
		this->FIO = f;
		this->book_number = n;
		this->group = g;
		this->score = s;
		this->mean = mean1();
	}
	Student(const Student&) = default;
	Student& operator=(const Student&) = default;
	Student(Student&&) = default;
	Student& operator=(Student&&) = default;


	bool operator<( const Student& other) const {
		return mean < other.mean;
	}

	bool operator==(const Student& other) const{
		if (this->book_number == other.book_number &&
			this->FIO == other.FIO &&
			this->group == other.group &&
			this->score == other.score) {
			return true;
		}
		return false;
	}

	float mean1() {
		int sum = 0;
		for (vector<int>::iterator iter = score.begin(); iter < score.end(); iter++) {
			sum += *iter;
		}
		return sum / score.size();
	}
	void print(ostream& out) {
		out << FIO << " " << group << " " << book_number <<endl;
		for (auto i : score) {
			out << i << " ";
		}
	}
	struct Hash {
		size_t operator()(const Student& s) const {
			return hash<string>()(s.FIO) ^
				hash<string>()(s.group) ^
				hash<int>()(s.book_number);
		}
	};
};

ofstream& operator<<(ofstream& out, Student& s) {
	s.print(out);
	return out;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output1.txt");

	list<Student> lstud;
	string line;
	string F, I, O, group, scores;
	int number;
	

	while (getline(in, line) && getline(in, scores))
	{
		istringstream stream(line);
		stream >> F >> I >> O >> group >> number;
		string FIO = F + ' ' + I + ' ' + O;
		vector<int> s;
		for (auto i : scores) {
			if (i != ' ') {
				char n[1];
				n[0] = i;
				s.push_back(stoi(string(n)));
			}
		}
		lstud.push_back(Student(FIO, group, number, s));
	}
	vector<Student> vstud;
	copy(lstud.begin(), lstud.end(), back_inserter(vstud));
	set<Student> sset(vstud.begin(), vstud.end());
	unordered_set<Student, Student::Hash> unset(vstud.begin(), vstud.end());
	out << "set" << endl;
	for (auto i : sset) {
		out << i << endl;
	}
	out << "unordered_set" << endl;
	for (auto i : unset) {
		out << i << endl;
	}
	in.close();
	out.close();
	return 0;
}
