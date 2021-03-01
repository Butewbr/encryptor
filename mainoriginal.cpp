#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/*
USANDO PAIR:

pair <int, float > p2;
p1.first = 10;
p1.second = 3.55;

pair <string, char> p2;
p2.first = "asdklafklsdkl";
p2.second = 'a';

pair< pair <string, char>, float > p3;
p3.first.first = "askdakl";
p3.first.second = 'l';
p3.second = 10.3;
*/

bool mysorterfunction(const pair< size_t, size_t > &p1, const pair <size_t, size_t > &p2)
{
	return (p1.second > p2.second);
}

int main(int argc, char const *argv[])
{
    cout << "enter with an alphabet to read: ";
    string pathAlpha;
    cin >> pathAlpha;
    
    //reading an alphabet file
    ifstream frAlpha(pathAlpha);
    vector< char > alphabetList;
    if(!frAlpha.is_open())
    {
        cout << "Error, alphabet file not found" << endl;
        return 1;
    }
    else
    {
        string tmp;
        while(getline(frAlpha, tmp))
        {
            alphabetList.push_back(tmp.at(0));
        }
    }

    stringstream manuscriptStr;
	cout << "enter manuscript to encode: ";
	string pathManusc;
	cin >> pathManusc;

	ifstream frManusc(pathManusc);

	if (!frManusc.is_open())
	{
		cout << "error file not fond" << endl;

		return 2;
	}

	char ch;

	while(frManusc.get(ch))
	{
		manuscriptStr << ch;
	}

	cout << manuscriptStr.str() << endl;

	//frequencia de caracteres do manuscrito

    vector < pair< size_t, size_t > > frequencyList;
    for(size_t i=0; i<256; i++)
    {
        pair< size_t, size_t > p;
        p.first = i;
        p.second = 0;        
        frequencyList.push_back(p);
    }
    for(size_t i=0; i<manuscriptStr.str().size(); i++)
    {
        char ch = manuscriptStr.str().at(i);
        frequencyList.at(ch).second++;       
    }

    //sort c++ by element excluding elements with 0 appearences
	stable_sort(frequencyList.begin(), frequencyList.end(), mysorterfunction);
    
    for (size_t i = 0; i < frequencyList.size(); ++i)
    {
    	if (frequencyList.at(i).second == 0)
    	{
    		frequencyList.erase(frequencyList.begin()+i, frequencyList.end());
    	}
    }

    for(size_t i=0; i<frequencyList.size(); i++)
    {
        cout << (char) frequencyList.at(i).first << " -> " << frequencyList.at(i).second << endl;
    }

    if (alphabetList.size() < frequencyList.size())
    {
    	cout << "Error, alphabet blablalbabl" << endl;

    	return 3;
    }

    for(size_t i=0; i<frequencyList.size(); i++)
    {
    	frequencyList.at(i).second = alphabetList.at(i);
    }

	cout << "decoded thingy:" << endl;
    for(size_t i=0; i<frequencyList.size(); i++)
    {
        cout << (char) frequencyList.at(i).first << " -> " << (char) frequencyList.at(i).second << endl;
    }

    //conversion
    for(size_t i = 0; i < manuscriptStr.str().size(); i++)
    {
        char ch = manuscriptStr.str().at(i);

        for(size_t j = 0; j < frequencyList.size(); j++)
        {
            if(ch == frequencyList.at(j).first)
            {
                cout << (char) frequencyList.at(j).second;
                break;
            }
        }        
    }
    cout << endl;

	return 0;
}