#include<bits/stdc++.h>
using namespace std;
class key_value_pair
{
private:
    string key;
    int value;
public:
    key_value_pair()
    {
        key="";
        value=-1;
    }
    key_value_pair(string str,int val)
    {
        key=str;
        value=val;
    }
    void setkey(string str)
    {
        key=str;
    }
    void setvalue(int val)
    {
        value=val;
    }
    string getkey()
    {
        return key;
    }
    int getvalue()
    {
        return value;
    }
};
class hashTable
{
private:
    int tablesize;
    int separate_chain_collision;
    int double_hash_collision;
    int custom_probe_collision;
    int currEli_doublehash;
    int currEli_customhash;
    vector<key_value_pair>doublehash;
    vector<key_value_pair>customhash;
    vector<vector<key_value_pair>>separate_chain;
public:
    int C1=194,C2=170,terminating_point=1e7;
    hashTable()
    {
        tablesize=0;
        separate_chain.resize(0,vector<key_value_pair>());
        currEli_doublehash=0;
        currEli_customhash=0;
        separate_chain_collision=0;
        double_hash_collision=0;
        custom_probe_collision=0;
    }
    hashTable(int size)
    {
        tablesize=size;
        separate_chain.resize(tablesize,vector<key_value_pair>());
        separate_chain_collision=0;
        double_hash_collision=0;
        custom_probe_collision=0;
        currEli_doublehash=0;
        currEli_customhash=0;
    }
    void setTablesize(int size)
    {
        tablesize=size;
        separate_chain.resize(tablesize,vector<key_value_pair>());
        doublehash.resize(tablesize);
        customhash.resize(tablesize);
        currEli_doublehash=0;
        currEli_customhash=0;
    }
    int hashfunction(string key)
    {
        int temp = 1;
        int hashval = 0;

        for (int i = 0; i < key.length(); i++)
        {
            hashval = (hashval + (key[i] - 'a' + 1) * temp) % tablesize;
            temp = (temp* 32) % tablesize;
        }
        return (hashval % tablesize + tablesize) % tablesize;
    }

    int hashfunction2(string key)
    {
        int hashvalue=0,temp;
        for(int i=0; i<key.length(); i++)
        {
            temp=key[i]>60?key[i]+20:key[i]-40;
            hashvalue+=(hashvalue*10+temp)%tablesize;
        }
        return (hashvalue%tablesize+tablesize)%tablesize;
    }

    int auxHash_function(string key)
    {
        int hashval=0;
        for(int i=0; i<key.size(); i++)
        {
            hashval+=(key[i]*3)%tablesize;
        }
        return (13-(hashval%13))%tablesize;
    }
    void insertat_separatechain(key_value_pair key_val,int opt)
    {
        string key=key_val.getkey();
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        if(separate_chain[index].size()>0)
        {
            separate_chain_collision++;
        }
        separate_chain[index].push_back(key_val);
    }

    void insertat_doublehash(key_value_pair key_val,int opt)
    {
        string key=key_val.getkey();
        if(tablesize==currEli_doublehash)
        {
            //cout<<"Table is full"<<endl;
            return;
        }
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        if(doublehash[index].getvalue()!=-1)//an element is already there
        {
            int aux_index=abs(auxHash_function(key)%tablesize);
            int i=1;//i=number of probing
            while(true)
            {
                int modified_index=(index+i*aux_index)%tablesize;
                if(doublehash[modified_index].getvalue()==-1)
                {
                    doublehash[modified_index]=key_val;
                    break;
                }
                i++;
                if(i>=terminating_point)
                {
                    cout<<"Infinite Loop"<<endl;
                    exit(0);
                }
            }
            double_hash_collision+=i;
        }
        else
        {
            doublehash[index]=key_val;
        }
        currEli_doublehash++;
    }
    void insertat_customhash(key_value_pair key_val,int opt)
    {
        string key=key_val.getkey();
        if(tablesize==currEli_customhash)
        {
            //cout<<"Table is full"<<endl;
            return;
        }
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        if(customhash[index].getvalue()!=-1)//an element is already there
        {
            int aux_index=abs(auxHash_function(key)%tablesize);
            int i=1;//i=number of probing

            while(true)
            {
                int modified_index=(index+C1*i*aux_index+C2*i*i)%tablesize;
                if(customhash[modified_index].getvalue()==-1)
                {
                    customhash[modified_index]=key_val;
                    break;
                }
                i++;
                if(i>=terminating_point)
                {
                    cout<<"Infinite Loop"<<endl;
                    exit(0);
                }

            }
            custom_probe_collision+=i;
        }
        else
        {
            customhash[index]=key_val;
        }
        currEli_customhash++;
    }

    int number_of_sepchain_collision()
    {
        return separate_chain_collision;
    }
    int number_of_double_hash_collision()
    {
        return double_hash_collision;
    }
    int number_of_custom_hash_collision()
    {
        return custom_probe_collision;
    }

    void clearTable()
    {
        separate_chain.resize(0,vector<key_value_pair>());
        doublehash.resize(0);
        customhash.resize(0);
        separate_chain_collision=0;
        double_hash_collision=0;
        custom_probe_collision=0;
    }

    void sep_chain_tableInfo()
    {
        cout<<endl;
        cout<<"Separate Chaining Hash Table"<<endl;
        for(int i=0; i<separate_chain.size(); i++)
        {
            cout<<i;
            for(int j=0; j<separate_chain[i].size(); j++)
            {
                cout<<" "<<separate_chain[i][j].getkey()<<" ";
            }
            cout<<endl;
        }
    }
    void double_hash_tableinfo()
    {
        cout<<endl;
        cout<<"Double Hashing Hash Table"<<endl;
        for(int i=0; i<tablesize; i++)
        {
            cout<<i<<"-"<<doublehash[i].getkey()<<endl;
        }
        cout<<endl;
    }
    void customprobe_tableInfo()
    {
        cout<<endl;
        cout<<"Custom Probe Hash Table"<<endl;
        for(int i=0; i<tablesize; i++)
        {
            cout<<i<<"-"<<customhash[i].getkey()<<endl;
        }
        cout<<endl;
    }

    void display()
    {
        sep_chain_tableInfo();
        double_hash_tableinfo();
        customprobe_tableInfo();
    }

    int search_in_sep_chain(string key,int opt)
    {
        int count_probe=1;
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        for(int i=0; i<separate_chain[index].size(); i++)
        {
            if(separate_chain[index][i].getkey()==key)
            {
                // cout<<"From index "<<index<<"-"<<key<<" is found ";
                return count_probe;
            }
            count_probe++;
        }
        // cout<<key<<" is not found"<<endl;
        return count_probe;
    }
    int search_in_doubleHash(string key,int opt)
    {
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        int aux_index=abs(auxHash_function(key)%tablesize);
        int count_probe=0,flag=0;
        while(doublehash[(index+count_probe*aux_index)%tablesize].getkey() != key)
        {
            if (doublehash[(index+count_probe*aux_index)%tablesize].getvalue() == -1)
            {
                flag=1;
                //  cout<<key<<" is not found"<<endl;
                return count_probe+1;
            }
            if(count_probe>=tablesize)
            {
                cout<<"Infinite Loop"<<endl;
                exit(0);
            }
            count_probe++;
        }
        int currentPos=(index+count_probe*aux_index)%tablesize;
        // if(flag==0)
        //   cout<<"From index "<<currentPos<<"-"<<key<<" is found ";

        return count_probe+1;
    }

    int search_in_customHash(string key,int opt)
    {
        int index;
        if(opt==1)
        {
            int ind1=abs(hashfunction(key)%tablesize);
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=abs(hashfunction2(key)%tablesize);
            index=ind2;
        }
        int aux_index=abs(auxHash_function(key)%tablesize);
        int count_probe=0,flag=0;
        while(customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].getkey() != key)
        {
            if (customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].getvalue() == -1)
            {
                flag=1;
                //cout<<key<<" is not found"<<endl;
                return count_probe+1;
            }
            if(count_probe>=tablesize)
            {
                cout<<"Infinite Loop"<<endl;
                exit(0);
            }
            count_probe++;

        }
        int currentPos=(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize;
        // if(flag==0)
        //   cout<<"From index "<<currentPos<<"-"<<key<<" is found ";
        return count_probe+1;
    }
    bool finding_duplicate(string key,int opt)
    {
        int index;
        if(opt==1)
        {
            int ind1=hashfunction(key)%tablesize;
            index=ind1;
        }
        else if(opt==2)
        {
            int ind2=hashfunction2(key)%tablesize;
            index=ind2;
        }
        //index=hashfunction2(key)%tablesize;
        for(int i=0; i<separate_chain[index].size(); i++)
        {
            if(separate_chain[index][i].getkey()==key)
            {
                return true;
            }
        }
        return false;
    }

    void delete_from_sep_chain(string key)
    {
        int index=hashfunction2(key)%tablesize;
        int flag=0;
        /*for(int i=0; i<separate_chain[index].size(); i++)
         {
             if(separate_chain[index][i].getkey()==key)
             {
                 separate_chain[index].erase(separate_chain[index].begin()+i);
                 flag=1;
                 break;
             }
         }*/
        for(auto it=separate_chain[index].begin(); it!=separate_chain[index].end(); it++)
        {
            if(it!=separate_chain[index].end())
            {
                if((*it).getkey()==key)
                {
                    separate_chain[index].erase(it);
                    flag=1;
                    break;
                }
            }
        }
        if(flag==1)
            cout<<"From index "<<index<<"-"<<key<<" is deleted"<<endl;
        else cout<<key<<" not found"<<endl;
    }

    void delete_from_double_hash(string key)
    {
        int index=abs(hashfunction2(key)%tablesize);
        int aux_index=abs(auxHash_function(key)%tablesize);
        int count_prob=0;
        while(doublehash[(index+count_prob*aux_index)%tablesize].getkey()!=key)
        {
            if(doublehash[(index+count_prob*aux_index)%tablesize].getvalue()==-1)
            {
                cout<<key<<" not found"<<endl;
                return;
            }
            count_prob++;
        }
        doublehash[(index+count_prob*aux_index)%tablesize].setkey("");
        doublehash[(index+count_prob*aux_index)%tablesize].setvalue(-1);
        int currentpos=(index+count_prob*aux_index)%tablesize;
        cout<<"From index "<<currentpos<<"-"<<key<<" is deleted"<<endl;
    }


    void delete_from_custom_hash(string key)
    {
        int index=abs(hashfunction2(key)%tablesize);
        int aux_index=abs(auxHash_function(key)%tablesize);
        int count_probe=0;
        while(customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].getkey()!=key)
        {
            if(customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].getvalue()==-1)
            {
                cout<<key<<" not found"<<endl;
                return;
            }
            count_probe++;
        }
        customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].setkey("");
        customhash[(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize].setvalue(-1);
        int currentpos=(index+C1*count_probe*aux_index+C2*count_probe*count_probe)%tablesize;
        cout<<"From index "<<currentpos<<"-"<<key<<" is deleted"<<endl;
    }

};
bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    if (num <= 3)
    {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int findNextPrime(int input)
{
    if (input <= 1)
    {
        return 2;
    }
    int next = input + 1;
    while (!isPrime(next))
    {
        next++;
    }
    return next;
}

string generateRandomWord()
{
    int word_len = 5 + rand() % 6; // Generates a random length between 5 and 10
    char valid[] = "abcdefghijklmnopqrstuvwxyz";
    string word;

    for (int i = 0; i < word_len; ++i)
    {
        char randomChar = valid[rand() % 26];
        word += randomChar;
    }

    return word;
}

int main()
{
    cout<<"Give an input number :";
    int n;
    cin>>n;
    int next_prime=findNextPrime(n);
    cout<<"Hash Table size is :"<<next_prime<<endl;
    hashTable hashtable1;
    hashTable hashtable2;
    hashtable1.clearTable();
    hashtable2.clearTable();
    hashtable1.setTablesize(next_prime);
    hashtable2.setTablesize(next_prime);

    string str_array[n];

    //for hashfunction1
    for(int k=0; k<n; k++)
    {
        string str=generateRandomWord();

        str_array[k]=str;
        key_value_pair kvl_pair(str,k);
        if( hashtable1.finding_duplicate(str,2))
        {
            k--;
            continue;
        }
       // else
        {
            hashtable1.insertat_separatechain(kvl_pair,1);
            hashtable1.insertat_doublehash(kvl_pair,1);
            hashtable1.insertat_customhash(kvl_pair,1);
            hashtable2.insertat_separatechain(kvl_pair,2);
            hashtable2.insertat_doublehash(kvl_pair,2);
            hashtable2.insertat_customhash(kvl_pair,2);
        }

    }
    //hashtable1.display();
    int sepCol=hashtable1.number_of_sepchain_collision();
    int doubCol=hashtable1.number_of_double_hash_collision();
    int custCol=hashtable1.number_of_custom_hash_collision();
    cout<<"For Hash-Function : 1->"<<endl;
    cout<<"Number of Collision in Separate Chaining :"<<sepCol<<endl;
    cout<<"Number of Collision in Double Hashing :"<<doubCol<<endl;
    cout<<"Number of Collision in Custom Probing :"<<custCol<<endl;

    double probe_no_of_sepChain=0;
    double probe_no_of_doubleHash=0;
    double probe_no_of_customProbe=0;
    double probe_no_of_sepChain2=0;
    double probe_no_of_doubleHash2=0;
    double probe_no_of_customProbe2=0;
    int selected_number=1000;
    for(int i=1; i<=1000; i++)
    {
        string inputstr=str_array[rand()%n];
        probe_no_of_sepChain+=hashtable1.search_in_sep_chain(inputstr,1);
        probe_no_of_doubleHash+=hashtable1.search_in_doubleHash(inputstr,1);
        probe_no_of_customProbe+=hashtable1.search_in_customHash(inputstr,1);
        probe_no_of_sepChain2+=hashtable2.search_in_sep_chain(inputstr,2);
        probe_no_of_doubleHash2+=hashtable2.search_in_doubleHash(inputstr,2);
        probe_no_of_customProbe2+=hashtable2.search_in_customHash(inputstr,2);
    }
    double avg_col_of_sepChain=probe_no_of_sepChain/selected_number;
    double avg_col_of_doubleHash=probe_no_of_doubleHash/selected_number;
    double avg_col_of_customProbing=probe_no_of_customProbe/selected_number;
    cout<<"Average Number of Collisions in Seaparate Chaining :"<<avg_col_of_sepChain<<endl;
    cout<<"Average Number of Collisions in Double Hashing :"<<avg_col_of_doubleHash<<endl;
    cout<<"Average Number of Collisions in Custom Probing :"<<avg_col_of_customProbing<<endl;
    cout<<endl;

    int sepCol2=hashtable2.number_of_sepchain_collision();
    int doubCol2=hashtable2.number_of_double_hash_collision();
    int custCol2=hashtable2.number_of_custom_hash_collision();
    cout<<"For Hash-Function : 2->"<<endl;
    cout<<"Hash Table size is :"<<next_prime<<endl;
    cout<<"Number of Collision in Separate Chaining :"<<sepCol2<<endl;
    cout<<"Number of Collision in Double Hashing :"<<doubCol2<<endl;
    cout<<"Number of Collision in Custom Probing :"<<custCol2<<endl;

    double avg_col_of_sepChain2=probe_no_of_sepChain2/selected_number;
    double avg_col_of_doubleHash2=probe_no_of_doubleHash2/selected_number;
    double avg_col_of_customProbing2=probe_no_of_customProbe2/selected_number;
    cout<<"Average Number of Collisions in Seaparate Chaining :"<<avg_col_of_sepChain2<<endl;
    cout<<"Average Number of Collisions in Double Hashing :"<<avg_col_of_doubleHash2<<endl;
    cout<<"Average Number of Collisions in Custom Probing :"<<avg_col_of_customProbing2<<endl;

}


