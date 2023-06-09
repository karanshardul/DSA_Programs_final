#include <iostream>
#include <string>
using namespace std;

class HashTable{
    string name;
    int num;
    public:
        HashTable();
        void display();
        int Hash(string s);
        void insert_ht1();
        void insert_ht2();
}HT1[10],HT2[10];

HashTable::HashTable(){
    for(int i=0; i <10; i++){
        HT1[i].name = "Blank";
        HT1[i].num = 0;

        HT2[i].name = "Blank";
        HT2[i].num = 0;
    }
}

void HashTable::display(){
    for(int i=0; i<10; i++){
        cout << HT1[i].name <<"----" << HT1[i].num<< "      " << HT2[i].name <<"----" << HT2[i].num <<endl;
    }
    cout << endl;
}

int HashTable::Hash(string s){
    int k=0; 
    int n = s.size();

    for(int i=0; i<n; i++) k += s[i];

    return k%10;
}

void HashTable::insert_ht1(){
    int j;
    cout << "Enter the number of entries to make in Table 1: " ;
    cin >> j;
    cout << endl;

    for(int i=0; i<j; i++){

        string s; 
        int k;

        cout << "Enter the name of person" << i+1<<": ";
        cin >> s;
        cout <<endl;

        cout << "Enter the number of person" << i+1<<": ";
        cin >> k; 
        cout <<endl;

        int index = Hash(s);
        cout << index << endl;

        if (HT1[index].name == "Blank")
        {
            HT1[index].name = s;
            HT1[index].num = k;
            continue;
        }

        bool is_inserted = false;

        for(int j = index ; j < 10; j++){

            int curr = j%10;
            
            if(HT1[i].name == "Blank"){
                HT1[i].name = s;
                HT1[i].num = k;
                is_inserted = true;
                break;
            }
        }
        
        string ans = is_inserted ? "Data Set successfully" : "Overflow";
        cout << ans << endl;
        
    }

}

void HashTable::insert_ht2(){
    int j;
    cout << "Enter the number of entries to make in Table 2: " ;
    cin >> j;
    cout << endl;

    for(int i=0; i<j; i++){
        string s; 
        int k;
        int index=0;
        int prev_index=0;

        cout << "Enter the name of person" << i+1<<": ";
        cin >> s;cout;
        cout << "Enter the number of person" << i+1<<": ";
        cin >> k;
        
        cout <<endl;

        index = Hash(s);
        
        if (HT2[index].name == "Blank")
        {
            HT2[index].name = s;
            HT2[index].num = k;
            cout << "User saved at index " << index << endl;
            display();
            continue;
        }
        
        string m = HT2[index].name;
        prev_index = Hash(m);
            
        if(index == prev_index){
            bool is_inserted = false;
            for(int j = index+1 ; j<10; j++){

                int i = j%10;

                if(HT2[i].name == "Blank"){
                    HT2[i].name = s;
                    HT2[i].num = k;
                    is_inserted = true;
                    break;
                }
            }

            string ans = is_inserted ? "Data Inserted" : "Overflow";
            cout << ans << endl;
            
        }else{
            string prev_name = HT2[prev_index].name;
            int prev_num = HT2[prev_index].num;
            
            HT2[index].name = s;
            HT2[index].num = k;

            cout << "curr " << index;
            cout << " prev " << prev_index;
            cout << endl;

            bool is_inserted = false;
            for (int j = index+1; j < 10; j++)
            {

                int i = j % 10;

                if (HT2[i].name == "Blank")
                {
                    HT2[i].name = prev_name;
                    HT2[i].num = prev_num;
                    is_inserted = true;
                    break;
                }
            }

            string ans = is_inserted ? "Data Inserted" : "Overflow";
            cout << ans << endl;
        }

        display();  
    }

}


int main(){
    cout << endl;
    cout<< "            Welcome Mam!!!        "<< endl;
    HashTable h;
    // h.insert_ht1();
    h.insert_ht2();
    h.display();
}