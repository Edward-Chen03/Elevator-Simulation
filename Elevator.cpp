#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
int floorNum;
string currentFloor;
vector<string> sequence;
bool up = false;

void convertList(string input)
{
    stringstream ss(input);
    vector<string> tempList;

    string number;
    while (ss >> number)
    {
        tempList.push_back(number);
    }

    sequence = tempList;
}

void printList(vector<string> input)
{
    for (string const &floor : input)
    {
        cout << floor << " ";
    }
}
void updateList()
{

    if (sequence.begin() == sequence.end())
    {
        currentFloor = "";
    }
    else
    {
        if (up)
        {
            auto index = find(sequence.begin(), sequence.end(), currentFloor);
            rotate(sequence.begin(), index, sequence.end());

            
            if(sequence.size() != 1){
                if(sequence[1] < currentFloor){
                    up = false;
                    currentFloor = sequence.back();

                }
                else{
                    currentFloor = sequence[1];
                }
                sequence.erase(sequence.begin());
            }
            else{
                currentFloor = "";
                sequence.clear();
            }
        }
        else
        {
            auto index = find(sequence.begin(), sequence.end(), currentFloor);

            reverse(sequence.begin(), index);

            if(sequence.size() != 1){

                if(sequence[1] < currentFloor){
                    currentFloor = sequence[1];

                }
                else{
                    up = true;
                    currentFloor = sequence[1];
                }

                sequence.erase(sequence.begin());

            }
            else{
                currentFloor = "";
                sequence.clear();
            }
        }

    
        
    }
}

void sortList(vector<string> input){
    bool sort = true;

    while (sort)
    {
        sort = false;
        for (int i = 0; i < input.size() - 1; i++)
        {
            int var1;
            int var2;
            if (input[i] == "G")
            {
                var1 = 0;
            }
            else if (input[i] == "B")
            {
                var1 = -1;
            }
            else
            {
                var1 = stoi(input[i]);
            }
            if (input[i + 1] == "G")
            {
                var2 = 0;
            }
            else if (input[i + 1] == "B")
            {
                var2 = -1;
            }
            else
            {
                var2 = stoi(input[i + 1]);
            }

            if (var1 > var2)
            {
                string temp = input[i];
                input[i] = input[i + 1];
                input[i + 1] = temp;
                sort = true;
            }
        }
    }

    sequence = input;

    auto search = lower_bound(sequence.begin(), sequence.end(), currentFloor);
    int index = distance(sequence.begin(), search);
    
    // need to handle when current floor isnt avaliable in list
    
    if(up){
        if(sequence.size() == index){
            up = false;
        }
    }
    else{
        if(index == 0){
            up = true;
        }
    }
    updateList();
}


int main()
{

    cout << "Please enter the number of floors:";
    cin >> floorNum;
    cout << floorNum;

    cout << '\n'
         << "Please enter your starting floor:";
    cin >> currentFloor;
    cout << currentFloor;

    while (stoi(currentFloor) > floorNum)
    {
        cout << '\n'
             << "Please enter a valid floor: ";
        cin >> currentFloor;
        cout << currentFloor;
    }
    
    

    cout << '\n' << "Now enter an elevator sequence or enter the next floor (with spaces in between each floor):";
    string input;
    getline(cin >> ws, input);
    convertList(input);
    if(sequence[0] > currentFloor){
        up = true;
    }
    else{
        up = false;
    }
    sequence.push_back(currentFloor);
    printList(sequence);



    while (true)
    {
        
        cout << '\n'
             << "Please enter the next floor: ";

        getline(cin >> ws, input); // fix getline to handle empty input

        switch (input[0])
        {
        case 'Q':
        case 'q':
        case 'quit':
        case 'Quit':
            cout << "Thanks!";
            return 0;
        case 'g':
        case 'G':
            sequence.push_back("G");
            sortList(sequence);
            printList(sequence);
            cout << currentFloor;
            break;
        case 'b':
        case 'B':
            sequence.push_back("B");
            sortList(sequence);
            printList(sequence);
            cout << currentFloor;
            break;

        default:
            if (input == "")
            {

            }
            else
            {
                sequence.push_back(input);
            }
            sortList(sequence);
            printList(sequence);
            cout << "\n Current Floor:" + currentFloor;
            break;
        }
    }

    return 0;
}
