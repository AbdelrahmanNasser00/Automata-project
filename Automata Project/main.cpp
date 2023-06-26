#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int maxSize = 500;
//Transition table to store rules of moving.
vector<vector<int>>transitionTable;

vector<bool>acceptedStates;// To mark final states as accepted.

string inputAlphapet, finalStates;
int numberOfStates, startState;

int takeInteger(int start, int end)
//To insure that the taken number is a valid one and in specific range
{
	int number;
	while (true)
	{
		string input; bool validNumber = true;

		cin >> input;
		int size = input.size();
		for (int i = 0; i < size; i++) {
			if (!isdigit(input[i])) {
				cout << "Invalid number ,please try again \n";
				validNumber = false;
				break;
			}
		}

		if (validNumber) {
			number = stoi(input);
			if (!(number >= start && number <= end)) {
				cout << "Invalid number ,please try again \n";
				continue;
			}
			else return number;;
		}
		else
			continue;
	}
	return number;
}
void takeTransitionTable()
// Takes rules of moving and stores every move for each state
{
	char letter; int nextMove;
	cout << "Rules of moving :\nPlease enter the right state of each move :\n";
	for (int i = 1; i <= numberOfStates; i++) {
		for (int j = 0; j < inputAlphapet.size(); j++) {
			letter = inputAlphapet[j];
			cout << "When state number '" << i << "' reads a '"
				<< letter << "' moves to state number :\n";
			nextMove = takeInteger(1, numberOfStates);
			//cin >> nextMove;
			transitionTable[i][letter - '0'] = nextMove;
		}
	}

}

void extractAlphapit()
//Remove extra characters and spaces from the alphapit string
{
	string temp = "";//To temporary store the alphapet
	int size = inputAlphapet.size();
	for (int i = 0; i < size; i++) {
		char letter = inputAlphapet[i];

		if (isalpha(letter) || isdigit(letter))
			temp.push_back(letter);
	}
	inputAlphapet = temp;
}
void exractFinalStates()
//Extract final states numbers and mark tehm as accepted states
{
	int size = finalStates.size();
	for (int i = 0; i < size; i++) {
		char letter = finalStates[i];
		if (isdigit(letter))
			acceptedStates[letter - '0'] = true;
	}
}
void testString()
//Takes a string and determines it will be accepted or rejected
// due to the defined DFA machnine
{
	string stringForTesting;
	cout << "Enter a string for testing :\n";
	cin >> stringForTesting;
	int currentState = startState;
	int size = stringForTesting.size();
	for (int i = 0; i < size; i++) {
		char letter = stringForTesting[i];
		currentState = transitionTable[currentState][letter - '0'];
		//checl if the letter in the input alphapet.
		if (currentState == -1) {
			cout << "Rejected\n\n";
			return;
		}
	}
	if (acceptedStates[currentState])
		cout << "Accepted\n\n";
	else
		cout << "Rejected\n\n";
}
void defineDFA()
//Take the 5-tuples of DFA
//[states,input alphapet,rules of moving,start state and final states].
{
	//Return the transition table to it's primary state with initial values equal to -1
	transitionTable = vector<vector<int>>(maxSize, vector<int>(maxSize, -1));
	//Return the acceptedStates  array to it's primary state with initial values equal to fasle
	acceptedStates = vector<bool>(maxSize, false);

	cout << "Enter the number of states : \n";
	numberOfStates = takeInteger(1, maxSize);
	//cin >> numberOfStates;
	cin.ignore();

	cout << "Enter the input alphapet in this foramt {X,X,X,...}: \n";
	getline(cin, inputAlphapet);
	extractAlphapit();

	takeTransitionTable();

	cout << "Enter the start state number :\n";
	cin >> startState;
	cin.ignore();

	cout << "Enter final states numbres in this format (only numbers) {X,X,X,...} :\n";
	getline(cin, finalStates);
	exractFinalStates();

}
void menu()
//Provides options to the user to choose between progaram features
{
	while (true)
	{
		string choise;
		cout << "Enter your choise :\n";
		cout << "1) To define a new DFA\n"
			<< "2)To exit\n";

		cin >> choise;
		if (choise == "1") {
			defineDFA();
			while (true)
			{
				string choise;
				cout << "Enter your choise :\n";
				cout << "1) To test a string\n"
					<<
					"2)To return to the main menu\n";
				cin >> choise;
				if (choise == "1")
					testString();
				else if (choise == "2")
					break;
				else
					cout << "Invalid choise ,please try again\n";
			}
		}
		else if (choise == "2")
			break;
		else
			cout << "Invalid choise ,please try again\n";
	}

	cout << "\n***********THANK YOU***********\n";

}
int main() {
	menu();
}
