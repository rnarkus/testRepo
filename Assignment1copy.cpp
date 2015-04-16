// Markus Hudobnik
// 1/23/2015
// Assignment 1
// Craigslist program 

// Recived suggestions from stackExchange and reddit.com

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct item
{
	string type;
	bool status; // false = for sale, true = wanted
	int price;
};

item createItem(string line) //this function inputs a line from the file into a struct
{
    item newitem;
    istringstream iss(line);
    string type, status, price;
    bool statusbool;
    getline(iss, type, ',');
    getline(iss, status, ',');
    getline(iss, price, ',');
    if (status == " wanted")
        statusbool = true; 
    else
        statusbool = false;
    newitem.status = statusbool;
    newitem.type = type;
    newitem.price = stoi(price);

    return newitem; // returns the fully formed struct
}

int compareItem (item itemcc, item itemArray[], int counter, int &operations) 
// checks to see if there is a match in the array
{
    for (int i=0; i < counter; i++)
    {
        operations++; // +1 for every time this loop runs, 
        // based on how many items are in the array
        // this loop is flexible because it will run a different amount everytime
        // the fucntion is called
        if ((itemcc.type == itemArray[i].type) 
            && (itemcc.status == false && itemArray[i].status == true)
            && (itemcc.price <= itemArray[i].price))
            return i;      
        else if ((itemcc.type == itemArray[i].type) 
            && (itemcc.status == true && itemArray[i].status == false)
            && (itemcc.price >= itemArray[i].price)) 
            return i;  
    }
    return -1;
}

void printRemaining (int counter, item itemArray[])
{
    for (int h=0; h<counter; h++)
    {
        if (itemArray[h].status == false)
            cout << itemArray[h].type << ", " << "for sale" << ", " << itemArray[h].price << endl;
        else
            cout << itemArray[h].type << ", " << "wanted" << ", " << itemArray[h].price << endl;
    }
}

void shiftLeft (item itemstruct, item itemArray[], int &counter, int &index, int &operations)
{
    if (itemstruct.status == 0) 
    {
        cout << itemstruct.type <<" "<<      itemstruct.price<<endl;
    }
    else 
    {
        cout << itemArray[index].type <<" "<<      itemArray[index].price<<endl;
    }
    
    for (int j = index; j < counter; j++)
    {
        itemArray[j] = itemArray[j+1]; // overwrites the previous item, 1 = 2, 2 = 3, etc
        operations++; // +1 for each loop, based on the counter
    }
    counter--; // decreases the counter for the removed item
}

int main(int argc, char* argv[])
{
	ifstream messageboard; // declares the file
    messageboard.open(argv[1]); // opens the file

    item itemArray[100];
    int index;
    int counter = 0;
    int operations = 0;
    string line;
    if(messageboard.is_open()) // checks to make sure the file is actually open
    {
        while (getline(messageboard, line)) // reads in the file until the very end
        {
            operations++; // +1 operation for each line in the code
            item itemstruct = createItem(line); //returned value goes into the main struct 
            index = compareItem(itemstruct, itemArray, counter, operations);
            // if there a match in the array, it removes the items by shifting to the left,
            // If not, it is added into the next availbale space in the array.
            // counter keeps track of how many items are currently in the array
            if (index == -1)
                itemArray[counter++] = itemstruct;
            else if (index > -1)
                shiftLeft(itemstruct, itemArray, counter, index, operations);   
        } 
    messageboard.close();
    }
    cout << "#" << endl;
    printRemaining(counter, itemArray);
    cout << "#" << endl;
    cout << "operations:" << operations <<endl;
}

