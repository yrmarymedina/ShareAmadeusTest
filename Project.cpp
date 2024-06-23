#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>
#include </Users/Yrmary Medina Delgad/Documents/personal/test_amadeus/test_amadeus/lib/pugixml-1.14/src/pugixml.hpp>
#include </Users/Yrmary Medina Delgad/Documents/personal/test_amadeus/test_amadeus/lib/pugixml-1.14/src/pugiconfig.hpp>
#include <algorithm>

using namespace std;

class Employee
{
	public:
		string name;
		int id;
		string department;
		double salary;
		Employee(string _name, int _id, string _department, double _salary)
		{
			name = _name;
			id = _id;
			department = _department;
			salary = _salary;
		}

};

class Employeess 
{
	public:
		vector<Employee> Employees;

	public : double GetAverageSalary(const std::vector<Employee>& employees)
	{
		string result;
		double total = 0;

		for (auto it = employees.cbegin(); it != employees.cend(); it++) {
			total = it->salary + total;
		}
		double avarege = total / employees.size();
		
		return avarege;
	}

	public: double GetHighestSalary(const std::vector<Employee>& employees)
	{
		double salary = 0;

		for (auto it = employees.cbegin(); it != employees.cend(); it++) {
			salary = max(salary, it->salary);
		}

		return salary;
	}

	public: void GetSortList(const std::vector<Employee>& employees)
	{
		vector<Employee> emplo = employees;

		std::sort(emplo.begin(), emplo.end(),
			[](const Employee& e, const Employee& ee) 
			{ return e.id < ee.id; });

		std::cout << " ***Employees List*** " << endl;

		for (auto it = employees.cbegin(); it != employees.cend(); it++) 
		{
			std::cout << " Id: " << it->id << endl;
		}
	}
};

 class ConvertFiles 
{
	public:ConvertFiles() {};

	public : Employeess ConvertJson(const std::string& filename)
	{
		Json::Value jsonData;
		Json::Reader jsonReader;
		Employeess list;
		try
		{
			ifstream ifs(filename);

			if (ifs.is_open())
			{
				jsonReader.parse(ifs, jsonData);
				const Json::Value& objeto = jsonData["employees"];
				for (int i = 0; i < objeto.size(); i++)
				{
					Employee employee = Employee(
						objeto[i]["name"].toStyledString(),
						objeto[i]["id"].asInt(),
						objeto[i]["department"].toStyledString(),
						objeto[i]["salary"].asDouble());

					list.Employees.push_back(employee);
				}
			}
			else
			{
				std::cerr << "Error laod json file" << std::endl;
			}
		}
		catch (...) 
		{
			throw new exception("Format Error");
		}
		return list;
	}

	public:Employeess ConvertXml(const std::string& filename)
	{
		Employeess list;
		pugi::xml_document doc;
		try
		{
			if (doc.load_file("fileXml1.xml"))
			{
				for (pugi::xml_node employeeNode : doc.child("employees").children("employee"))
				{
					string name = employeeNode.child_value("name");
					int id = stoi(employeeNode.child_value("id"));
					string department = employeeNode.child_value("department");
					double salary = stod(employeeNode.child_value("salary"));

					Employee employee = Employee(
						name,
						id,
						department,
						salary);
					list.Employees.push_back(employee);
				}
			}
			else
			{
				std::cerr << "Error load xml file" << std::endl;
			}
		}
		catch (...) 
		{
			throw new exception("Format Error");
		}
		return list;
	}

};


int main()
{
	ConvertFiles json_file;
	Employeess list;
	string path;
	string error;
	try
	{

		std::getline(cin, path);

		if (path.empty())
		{
			std::cerr << "Please, You need put the file name" << std::endl;

			exit(EXIT_FAILURE);
		}

		if (path.find(".xml") == std::string::npos && path.find(".json") == std::string::npos)
		{
			error = "Format error";
			throw (error);
		}
			

		if (path.find(".xml") != std::string::npos)
		{
			list = json_file.ConvertXml(path);
		}

		if (path.find(".json") != std::string::npos)
		{
			list = json_file.ConvertJson(path);
		}

		if (!list.Employees.empty()) 
		{
			std::cout << " ***Average Calculated:" << list.GetAverageSalary(list.Employees) << endl;
			std::cout << " ***Highest Salary:" << list.GetHighestSalary(list.Employees) << endl;
			list.GetSortList(list.Employees);
		}
		else
		{
			error = "Empty File";
			throw (error);
		}

		system("pause");

	}catch (string error)
	{
		cout << "something is wrong:" << error;
	}
}

