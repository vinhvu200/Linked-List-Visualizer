#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

#include "simulated_llist.cpp"

using namespace std;
using namespace cgicc;

//------------------------------------------------------
//	This section contains all function for my
//	own mini json parser
//-----------------------------------------------------

//	int to string
string intToString(int num)
{
        stringstream ss;
        ss << num;
        return ss.str();
}

//	bool to string
string boolToString(bool b)
{
	if (b == true)
		return "true";
	else
		return "false";
}

//	array to string
//	Example string: '17,14,08,-1,-1'
string arrayToString(int array[MAXNODES])
{
	string z = "";
	string temp;

	if (intToString(array[0]).length() == 1){
		z = z + "0" + intToString(array[0]);
	}
	else
		z = z + intToString(array[0]);

	for (int i=1; i<MAXNODES; i++){

	        if (intToString(array[i]).length() == 1)
        	        z = z + ',' + "0" + intToString(array[i]);
	        else
	                z = z + ',' + intToString(array[i]);
	}

	return z;
}

//	string to int
int stringToInt(string s)
{
	return atoi(s.c_str());
}

//	string to bool
bool stringToBool(string s)
{
        if (s == "true")
                return true;
        else
                return false;
}

//	string to Array
//	Example string: '17,14,08,-1,-1'
void stringToArray(string s, int (&array)[MAXNODES])
{
        string::iterator it = s.begin();
        string sNum, first, second;
        int num, count=0;
        first = *it;
        it++;
        second = *it;
        it++;
        sNum = first + second;
        array[count] = stringToInt(sNum);
        count++;

        for (it; it != s.end(); it++){
                string check;
                check = *it;
                if (check == ","){
                        it++;
                        first = *it;
                        it++;
                        second = *it;
                        sNum = first + second;
                        array[count] = stringToInt(sNum);
                        count++;
                }
        }
}

//	wraps the variable name and value into json format 
//	and pass back the string
string jsonWrap(string jsonVar, string varName="", string val="")
{
        if (jsonVar == ""){
                jsonVar = jsonVar + "{" + "\"" + varName + "\": \"" + val + "\"}";
                return jsonVar;
        }
        else{
                string temp = "";
                jsonVar.erase (jsonVar.end()-1);
                temp = temp + ",\n" + "\"" + varName + "\": \"" + val + "\"}";
                jsonVar.append(temp);
                return jsonVar;
        }
}

//-----------------------------------------------------------------

//	Convert all of cgi strings to proper variable 
//	and pass them on to be updated
void updateSetUp(string lc, string lsc, string len, string pa, string va,
		 string opa, string ova, string f, string r, string s, 
		 string pointP, string of, string os, string oR, 
		 string opointP, string sf, string ilf, string ff, 
		 string uef)
{
	// integers
	int _lc, _lsc, _len, _f, _r, _s, _pointP, _of, _os, _oR, _opointP;
	
	_lc = stringToInt(lc);
        _lsc = stringToInt(lsc);
        _len = stringToInt(len);
        _f = stringToInt(f);
        _r = stringToInt(r);
        _s = stringToInt(s);
        _pointP = stringToInt(pointP);
        _of = stringToInt(of);
        _os = stringToInt(os);
        _oR = stringToInt(oR);
        _opointP = stringToInt(opointP);

	// arrays
	int _pa[MAXNODES], _va[MAXNODES], _opa[MAXNODES], _ova[MAXNODES];
	stringToArray(pa, _pa);
	stringToArray(va, _va);
	stringToArray(opa, _opa);
	stringToArray(ova, _ova);

	// boolean
	bool _sf, _ilf, _ff, _uef;
	
	_sf = stringToBool(sf);
	_ilf = stringToBool(ilf);
        _ff = stringToBool(ff);
        _uef = stringToBool(uef);

	updateAll(_lc, _lsc, _len, _f, _r, _s, _pointP, 
		  _of, _os, _oR, _opointP, _pa, _va, _opa, 
		  _ova, _sf, _ilf, _ff, _uef);
}

/*
	When HTML passes back information, it will go here.
	This function will first get all the variables and
	then update the variables in simulated_llist.cpp to
	be used.

	simulated_llist.cpp will use the information to change
	characteristics of the linked list. Then, it will wrap
	all the information into a json format and pass it
	back to the front-end.
*/
int main()
{
	Cgicc receivedData;

	cout << "Content-Type:application/json\n\n";

	//Get all information passed back
	form_iterator leftChoice = receivedData.getElement("leftChoice");
        form_iterator rightChoice = receivedData.getElement("rightChoice");
        form_iterator lChoice = receivedData.getElement("lChoice");
        form_iterator rChoice = receivedData.getElement("rChoice");
	form_iterator en = receivedData.getElement("elementNum");
	form_iterator lc = receivedData.getElement("lastCommand");
        form_iterator lsc = receivedData.getElement("lastSubChoice");
        form_iterator len = receivedData.getElement("lastElementNum");
        form_iterator pa = receivedData.getElement("pointerArray");
        form_iterator va = receivedData.getElement("valueArray");
        form_iterator opa = receivedData.getElement("oldPointerArray");
        form_iterator ova = receivedData.getElement("oldValueArray");
        form_iterator f = receivedData.getElement("front");
        form_iterator r = receivedData.getElement("rear");
        form_iterator s = receivedData.getElement("second");
        form_iterator pointP = receivedData.getElement("P");
        form_iterator of = receivedData.getElement("oldFront");
        form_iterator os = receivedData.getElement("oldSecond");
        form_iterator oR = receivedData.getElement("oldRear");
        form_iterator opointP = receivedData.getElement("oldP");
        form_iterator sf = receivedData.getElement("segFlag");
        form_iterator ilf = receivedData.getElement("infLoopFlag");
        form_iterator ff = receivedData.getElement("fullFlag");
        form_iterator uef = receivedData.getElement("undoErrFlag");

	// Update all
	updateSetUp(**lc, **lsc, **len, **pa, **va, **opa, **ova, **f, **r, **s, **pointP,
		    **of, **os, **oR, **opointP, **sf, **ilf, **ff, **uef);

	// Json string to be passed back
        string z = "";

	//Change the linked list according to the user input
	handleEvent(stringToInt(**lChoice), stringToInt(**rChoice), stringToInt(**en));
	//topMenu(stringToInt(**lChoice), stringToInt(**rChoice), stringToInt(**en));

        //Create arrays
        int _pa[MAXNODES], _va[MAXNODES], _opa[MAXNODES], _ova[MAXNODES];
        stringToArray(**pa, _pa);
        stringToArray(**va, _va);
        stringToArray(**opa, _opa);
        stringToArray(**ova, _ova);

        string s_pa, s_va, s_opa, s_ova;

	// Convert current arrays to strings
	s_pa = arrayToString(pointerArray);
        s_va = arrayToString(valueArray);
        s_opa = arrayToString(oldPointerArray);
        s_ova = arrayToString(oldValueArray);

	//Json wrap all the information
	z = jsonWrap(z, "left", **leftChoice);
	z = jsonWrap(z, "right", **rightChoice);
	z = jsonWrap(z, "leftNum", **lChoice);
        z = jsonWrap(z, "rightNum", **rChoice);
	z = jsonWrap(z, "lc", intToString(lastCommand));
        z = jsonWrap(z, "lsc", intToString(lastSubChoice));
        z = jsonWrap(z, "len", intToString(lastElementNum));
        z = jsonWrap(z, "pa", s_pa);
        z = jsonWrap(z, "va", s_va);
        z = jsonWrap(z, "opa", s_opa);
        z = jsonWrap(z, "ova", s_ova);
        z = jsonWrap(z, "f", intToString(front));
        z = jsonWrap(z, "r", intToString(rear));
        z = jsonWrap(z, "s", intToString(second));
        z = jsonWrap(z, "pointP", intToString(P));
        z = jsonWrap(z, "of", intToString(oldFront));
        z = jsonWrap(z, "os", intToString(oldSecond));
        z = jsonWrap(z, "or", intToString(oldRear));
        z = jsonWrap(z, "opointP", intToString(oldP));
        z = jsonWrap(z, "sf", boolToString(segFlag));
        z = jsonWrap(z, "ilf", boolToString(infLoopFlag));
        z = jsonWrap(z, "ff", boolToString(fullFlag));
        z = jsonWrap(z, "uef", boolToString(undoErrFlag));
	z = jsonWrap(z, "cf", boolToString(circFlag));

	// Pass back to front-end
	cout << z;

}

