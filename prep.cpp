#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

void addItem( const string& item_id, const string& item_name, const string& item_quantity,const string& item_registration_date ){
    ofstream file("inventory.csv", ios::app);
    if (file.is_open()){
        file << item_id << ',' << item_name << ',' << item_quantity << ',' << item_registration_date << '\n';
        file.close();
        cout<<"items added successfully\n";
    }
    else{
        cout<<"please try again";
    }
}
void listItems(){
    ifstream file("inventory.csv");
    if(file.is_open()){
        vector<string> items;
        string line;
        while(getline(file, line)){
            items. push_back(line);
        }
            sort(items.begin(), items.end());
            cout << "Items in stock (sorted alphabetically):\n";
        for (const string& item : items) {
            cout << item << '\n';
        }
        file.close();
    }
}
int main(){
    string command1;
    string itemDetails;
    string item_id;
    string item_name;
    string item_quantity;
    string item_registration_date;
    cout<<" please enter the command: ";
    cin>>command1;
    transform(command1.begin(), command1.end(), command1.begin(), ::tolower);
    if(command1 =="itemadd"){

        cout<<"enter the item_id, name, quantity and registeration date, add them at the same time separate them using space: ";
        cin>> item_id>>item_name>>item_quantity>>item_registration_date;
        addItem(item_id, item_name, item_quantity, item_registration_date);

        }
    else{
        cout<<"couldn't perform the action";
    }
    listItems();
    return 0;
}

