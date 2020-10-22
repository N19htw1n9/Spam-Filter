//Project 1
//
// Sarim Qureshi
// University of Illinois at Chicago
// CS 251: Spring 2020
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Passes a reference parameter of 'list' and 'filename' so that the data from a file may be loaded onto a vector
void load(vector<string> &list, string fileName)
{
	list = vector<string>();
	ifstream file(fileName);

	if (!file.is_open())
    {
        cout << "**Error, unable to open '" << fileName << "'" << endl;
        return;
    }

	cout << "Loading '" << fileName << "'" << endl;
	string elem;
	file >> elem;

	while(!file.eof())
	{
		if (file.fail())
            break;
        
        list.push_back(elem);
        file >> elem;
	}
	
	file.close();
	cout << "# of spam entries: " << list.size() << endl;
}

//Passes a reference parameter of 'list' and 'query' so that the sorted data from list may be efficiently searched for keyword query
bool binarySearch(vector<string> &list, string query)
{
	int low = 0;
	int high = list.size() - 1;
	int mid = 0;
	string elem;

	while(low <= high)
	{
		mid = (low + high) / 2;
		elem = list[mid];

		if(query == elem)
			return true;

		else if(query < elem)
			high = mid - 1;
		
		else
			low = mid + 1;
	}

	return false;
}

//Helper Function for isEmailSpam
//Removes emails that don't contain '*', and replaces those that do contain '*' with the username
void removeAndReplace(vector<string> &list, vector<string> &starList, string username)
{
	string domain;
	int colonIndex;

	for(string elem : list)
			if(elem.find('*') != std::string::npos)
				starList.push_back(elem);
	
	for(string &starElem : starList)
	{
		colonIndex = starElem.find(':');
		domain = starElem.substr(0, colonIndex + 1);

		if (starElem.substr(colonIndex + 1) == "*")
            starElem = domain + username;
	}
}

//Helper Function for Check and Filter
//Returns true if Email is spam or false if it is not spam
bool isEmailSpam(vector<string> &list, string elem)
{
	int seperatorIndex = elem.find('@');
	string username = elem.substr(0, seperatorIndex);
	string domain = elem.substr(seperatorIndex + 1);
	string format = domain + ":" + username;

	if(binarySearch(list, format) == true)
		return true;

	else
	{
		vector<string> starList;
		removeAndReplace(list, starList, username);
		return binarySearch(starList, format);
	}
}

//Validates the results of isEmailSpam
//Prints true if Email is spam or false if it is not spam
void check(vector<string> &list, string elem)
{
	if(isEmailSpam(list, elem) == true)
		cout << elem << " is spam" << endl;
	
	else	
		cout << elem << " is not spam" << endl;
}

//Filters through an email file given a loaded spam file to check which emails are spam
//Prints the number of emails processed and the number of emails that are spam
void filter(vector<string> list, string action)
{
	int indent = action.find(" ");
	string rawFileName = action.substr(0, indent);
	string outFileName = action.substr(indent + 1);
	
	ifstream rawFile(rawFileName);
	ofstream outFile(outFileName);

	if (!rawFile.is_open())
    {
        cout << "**Error, unable to open '" << rawFileName << "'" << endl;
        return;
    }

	if (!outFile.is_open())
    {
        cout << "**Error, unable to open '" << outFileName << "'" << endl;
        return;
	}

	string msgID;
	string emailAddress;
	string subject;

	int total = 0;
	int clean = 0;

	rawFile >> msgID;
	rawFile >> emailAddress;
	getline(rawFile, subject);

	while(!rawFile.eof())
	{
		if(rawFile.fail() || outFile.fail())
			break;
			
		if(isEmailSpam(list, emailAddress) == false)
		{
			outFile << msgID << " " << emailAddress << " " << subject << endl;
			clean++;
		}

		rawFile >> msgID;
		rawFile >> emailAddress;
		getline(rawFile, subject);

		total++;
	}

	rawFile.close();
	outFile.close();

	cout << "# emails processed: " << total << endl;
    cout << "# non-spam emails: " << clean << endl;
}

//Prints the contents of the vector that has loaded the data of the spam file
void display(vector<string> &list)
{
	for(string email : list)
		cout << email << endl;
}

int main()
{
	cout << "** Welcome to spam filtering app **" << endl;

	vector<string> list;

	int indent;
	string input;
	string command;
	string argument;

	while(input != "#")
	{
		cout << "\nEnter command or # to exit> ";
        getline(cin, input);

		indent = input.find(" ");
		command = input.substr(0, indent);
		argument = input.substr(indent + 1);

		if (command == "load")
            load(list, argument);

        else if (command == "display")
            display(list);

        else if (command == "check")
            check(list, argument);

        else if (command == "filter")
            filter(list, argument);

        else if (command == "#")
            break;

        else
            cout << "**invalid command" <<endl;

	}
	
	return 0;
}
