#include <iostream>
#include <string>
using namespace std;

const int MAXNODES = 5;

int lastCommand, lastSubChoice, lastElementNum;

//Current and old pointer/value arrays
int pointerArray[MAXNODES], valueArray[MAXNODES]; 
int oldPointerArray[MAXNODES], oldValueArray[MAXNODES];

//Current/old pointers
int front, rear, second, P;
int oldFront, oldSecond, oldRear = rear, oldP;

//All error flags
bool segFlag, infLoopFlag, fullFlag, undoErrFlag;
bool circFlag = false;

//These two used to update all variables with info from front-end
void copyArray(int (&array1)[MAXNODES], int (&array2)[MAXNODES]);
void updateAll(int lc, int lsc, int len, int f, int r, int s,
                int pointP, int of, int os, int oR, int opointP,
                int pa[MAXNODES], int va[MAXNODES], int opa[MAXNODES], int ova[MAXNODES],
                bool sf, bool ilf, bool ff, bool uef);

// Utilities to use to handle events
void backupList();
bool undo(bool allowUndo);
int setPointerNext(int&, int);
bool setPointerElem(int, int);
void _delNode(int);
void delNode(int);
int setPointer(int&, int);
void checkCircular(int);

//Handles user input to change linked list
bool handleEvent(int, int, int);

//--------------------------------------------------------------------------

//Copies array1 to array2
void copyArray(int array1[MAXNODES], int (&array2)[MAXNODES])
{
	for (int i = 0; i < MAXNODES; i++){
		array2[i] = array1[i];
	}
}

//Update all global variables
void updateAll(int lc, int lsc, int len, int f, int r, int s,
                int pointP, int of, int os, int oR, int opointP,
                int pa[MAXNODES], int va[MAXNODES], int opa[MAXNODES], int ova[MAXNODES],
                bool sf, bool ilf, bool ff, bool uef)
{
	lastCommand = lc; lastSubChoice = lsc; lastElementNum = len;
	front = f; rear = r; second = s; P = pointP; 
	oldFront = of; oldSecond = os; oldRear = oR; oldP = opointP;
	segFlag = sf; infLoopFlag = ilf; fullFlag = ff; undoErrFlag = uef;
	
	copyArray(pa, pointerArray); copyArray(va, valueArray);
	copyArray(opa, oldPointerArray); copyArray(ova, oldValueArray);

}

//Stores current value/pointer arrays into old value/pointer array
//Stores current pointer into old pointer variables
void backupList() 
{

	oldFront = front;
	oldSecond = second;
	oldRear = rear;
	oldP = P;

	for(int i = 0; i < MAXNODES; i++){
		oldValueArray[i] = valueArray[i];
		oldPointerArray[i] = pointerArray[i];
	}
}

//Change current value/pointer array to old value/pointer array
//Change current pointer variable to old pointer variable
bool undo(bool allowUndo) 
{
	if(allowUndo == false)
		return true; 

	front = oldFront;
	second = oldSecond;
	rear = oldRear;
	P = oldP;

	for(int i = 0; i < MAXNODES; i++){
		valueArray[i] = oldValueArray[i];
		pointerArray[i] = oldPointerArray[i];
	}
	return false; 
}

/*
	This function will set the 'next'
	attribute of the pointer node to
	the subChoice. It will then return 
	an integer to indicate if an error 
	flag has been toggled.

	subChoices	
	1	newNode	
	2	Front
	3	Second
	4	Rear
	5	P
	6	Front->Next
	7	Second->Next
	8	Rear->Next
	9	P->Next
	10	NULL
*/
int setPointerNext(int& pointer, int subChoice)
{
	if (pointer == -1 || pointer == -2)
		return 1;

	int nodeSlot = 0;

	switch(subChoice){
	//newNode
	case 1:
		nodeSlot = 0;
		while(nodeSlot < MAXNODES && valueArray[nodeSlot] > -1)
			nodeSlot++;

		if(valueArray[nodeSlot] <= -1) {
			valueArray[nodeSlot] = 0;
			pointerArray[nodeSlot] = -2; 
			pointerArray[pointer] = nodeSlot;
			return 0;
		}
		else
			return 3;

		return 0;
		break;
	// front
	case 2:
		if (front == -2)
			return 1;
		pointerArray[pointer] = front;
		break;
	// second
	case 3: 
		if (second == -2)
			return 1;
		pointerArray[pointer] = second;
		return 0; 
		break;
	// rear
	case 4: 
		if (rear == -2)
			return 1;
		pointerArray[pointer] = rear;
		return 0; 
		break;
	// P
	case 5: 
		if (P == -2)
			return 1;
		pointerArray[pointer] = P;
		return 0; 
		break;
	// front->next
	case 6: 
		if(front <= -1 || pointerArray[front] == -2)
			return 1; 
		pointerArray[pointer] = pointerArray[front]; 
		return 0; 
		break;
	// second->next
	case 7: 
		if(second <= -1 || pointerArray[second] == -2)
			return 1; 
		pointerArray[pointer] = pointerArray[second];
		return 0;
		break;
	// rear->next
	case 8: 
		if (rear <= -1 || pointerArray[rear] == -2)
			return 1;
		pointerArray[pointer] = pointerArray[rear];
		return 0;
		break;
	// P->next
	case 9: 
		if(P <= -1 || pointerArray[P] == -2)
			return 1; 
		pointerArray[pointer] = pointerArray[P]; 
		return 0;
		break;
	// NULL
	case 10: 
		pointerArray[pointer] = -1;
		return 0; 
		break;

	default:
		return 0;
		break;
	}
}

//	Update the value of the pointer node
bool setPointerElem(int pointer, int value)
{
	if(pointer <= -1)
		return true;

	valueArray[pointer] = value;
	return false;
}

//	If points to the deleted pointer position, 
//	then set that pointer to junk also.
void _delNode(int temp)
{
	for (int i=0; i<MAXNODES; i++){
		if (pointerArray[i] == temp)
			pointerArray[i] = -2;
	}

	if (front == temp)
		front = -2;
        if (second == temp)
                second = -2;
        if (rear == temp)
                rear = -2;
        if (P == temp)
                P = -2;

}

/*
	Deletes the pointer that is passed in.
	Then sets the pointer to junk. All 
	pointers pointing to junk will be updated.

	CHOICES:
	2	front
	3	second
	4	rear
	5	P
	6	front->next
	7	second->next
	8	rear->next
	9	P->next
*/
void delNode(int choice)
{

	int temp;
	switch(choice){

	// front
	case 2:
		temp = front;
		valueArray[front] = -1;
		pointerArray[front] = -1;
		front = -2;
		_delNode(temp);
		break;
	// second
	case 3:
		temp = second;
		valueArray[second] = -1;
		pointerArray[second] = -1;
		second = -2;
		_delNode(temp);
		break;
	// rear
	case 4:
		temp = rear;
		valueArray[rear] = -1;
		pointerArray[rear] = -1;
		rear = -2;
		_delNode(temp);
		break;
	// P
	case 5:
		temp = P;
		valueArray[P] = -1;
		pointerArray[P] = -1;
		P = -2;
		_delNode(temp);
		break;
	// front->next
	case 6:
		if (valueArray[pointerArray[front]] != -1 && 
		valueArray[pointerArray[front]] != -2){

			temp = pointerArray[front];
			valueArray[pointerArray[front]] = -1;
			pointerArray[pointerArray[front]] = -1;
			_delNode(temp);
		}
		break;
	// second->next
	case 7:
		if (valueArray[pointerArray[second]] != -1 &&
		valueArray[pointerArray[second]] != -2){

			temp = pointerArray[second];
			valueArray[pointerArray[second]] = -1;
			pointerArray[pointerArray[second]] = -1;
			_delNode(temp);
		}
		break;
	// rear->next
	case 8:
		if (valueArray[pointerArray[rear]] != -1 &&
		valueArray[pointerArray[rear]] != -2){

			temp = pointerArray[rear];
			valueArray[pointerArray[rear]] = -1;
			pointerArray[pointerArray[rear]] = -1;
			_delNode(temp);
		}
		break;
	// P->next
	case 9:
		if (valueArray[pointerArray[P]] != -1 &&
		valueArray[pointerArray[P]] != -2){

			temp = pointerArray[P];
			valueArray[pointerArray[P]] = -1;
			pointerArray[pointerArray[P]] = -1;
			_delNode(temp);
		}
		break;

		default:
		break;
	}
}

/*
	Given the pointer, check if there is
	a circular linked list, starting at
	that pointer.
*/
void checkCircular(int pointer)
{
	if (circFlag == true)
		return;

	int temp1, temp2;
	temp1 = pointer; temp2 = pointer;

	while(temp2 != -1 && temp2 != -2){
		temp2 = pointerArray[temp2];
		if (temp2 == -1 || temp2 == -2)
			break;
		temp2 = pointerArray[temp2];
		if (temp2 == -1 || temp2 == -2)
                        break;

		temp1 = pointerArray[temp1];
		if (temp2 == temp1){
			circFlag = true;
			break;
		}
	}

}

/*
	This function will set the given pointer
	to the subChoice given. It will then return
	a integer to indicate whether an error
	flag has been toggled.

        subChoices
        1       newNode
        2       Front
        3       Second
        4       Rear
        5       P
        6       Front->Next
        7       Second->Next
        8       Rear->Next
        9       P->Next
        10      NULL
*/
int setPointer(int& pointer, int subChoice)
{
	int nodeSlot = 0;

	switch(subChoice)
	{
		case 1:
			nodeSlot = 0;
			while(nodeSlot < MAXNODES && valueArray[nodeSlot] > -1){
				nodeSlot++;
			}
			if (nodeSlot >= MAXNODES){
				fullFlag = true;
				return 0;
			}
			if(valueArray[nodeSlot] <= -1){
				valueArray[nodeSlot] = 0;
				pointerArray[nodeSlot] = -2;
				pointer = nodeSlot; 
				return 0;
			}
			else
				fullFlag = true;
			
			return 0;
			break;

		case 2: 
			if (front == -2)
				return 1;
			pointer = front;
			return 0;
			break;

		case 3:

			if (second == -2)
				return 1;
			else{
				pointer = second;
				return 0;
			}
			break;

		case 4:
			if (rear == -2)
				return 1;
			pointer = rear;
			return 0;
			break;

		case 5:
			if (P == -2)
				return 1;
			pointer = P;
			return 0; 
			break;

		case 6: 
			if(front <= -1){
				pointer = -1;
				return 1;
			}
			else if (pointerArray[front] == -2)
				return 1;
			else{
				pointer = pointerArray[front];
				return 0;
			}
			break;

		case 7:
			if(second <= -1){
				pointer = -1;
				return 1;
			}
			else if (pointerArray[second] == -2)
				return 1;
			else {
				pointer = pointerArray[second];
				return 0; 
			}
			break;

		case 8: 
			if(rear <= -1){
				pointer = -1;
				return 1;
			}
			else if (pointerArray[rear] == -2)
				return 1;
			else{
				pointer = pointerArray[rear];
				return 0;
			}
			break;

		case 9: 
			if(P <= -1){
				pointer = -1;
				return 1;
			}
			else if (pointerArray[P] == -2){
				return 1;
			}
			else {
				pointer = pointerArray[P];
				return 0; 
			}
			break;

		case 10: 
			pointer = -1;
			return 0;
			break;

		default:
			return 0; 
			break;
	}
}

/*
	Given the user input from the front-end, this 
	function will decide which function to handle
	the situation.
*/
bool handleEvent(int choice, int subChoice, int elementNum)
{

	int storeResult = 0;
	bool allowUndo = false;
	bool repeat = true;

	if(lastCommand != 13) 
		allowUndo = true;

	if(choice != 13) 
		backupList();

	switch(choice){
		case -1:
			return false;
			break;

			case 1:
			lastSubChoice = subChoice;
			storeResult = setPointer(front, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 2:
			lastSubChoice = subChoice;
			storeResult = setPointer(second, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 3:
			lastSubChoice = subChoice;
			storeResult = setPointer(rear, subChoice);
			if(storeResult == 1)
			segFlag = true;
			break;

		case 4:
			lastSubChoice = subChoice;
			storeResult = setPointer(P, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 5:
			lastSubChoice = subChoice;
			storeResult = setPointerNext(P, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 6:
			lastSubChoice = subChoice;
			storeResult = setPointerNext(front, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 7:
			lastSubChoice = subChoice;
			storeResult = setPointerNext(second, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 8:
			lastSubChoice = subChoice;
			storeResult = setPointerNext(rear, subChoice);
			if(storeResult == 1)
			segFlag = true;
			if(storeResult == 3)
			fullFlag = true;
			break;

		case 9:
			lastElementNum = elementNum;
			segFlag = setPointerElem(front, elementNum);
			break;

		case 10:
			lastElementNum = elementNum;
			segFlag = setPointerElem(second, elementNum);
			break;

		case 11:
			lastElementNum = elementNum;
			segFlag = setPointerElem(rear, elementNum);
			break;

		case 12:
			lastSubChoice = subChoice;
			delNode(subChoice);
			break;

		case 13:
			undoErrFlag = undo(allowUndo);
			break;

		case 14:
			lastElementNum = elementNum;
			segFlag = setPointerElem(P, elementNum);
			break;

	}

	checkCircular(front);
	checkCircular(rear);
	checkCircular(second);
	checkCircular(P);

	return true;

}

