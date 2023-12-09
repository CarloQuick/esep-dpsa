#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class InMemoryDB
{
public:
    // Create a map of strings to integers
    unordered_map<string, int> map;
    unordered_map<string, int> tempMap;
    bool active = false;
    bool commit = false;
    int get(string key)
    {
        unordered_map<string, int>::iterator it = map.find(key);
        if (it == map.end())
        {
            cout << "Element Not Present\n";
            return 0; // Null
        }
        else
        {
            cout << it->first << ": " << it->second << endl;
            return it->second;
        }
    };
    void put(string key, int val)
    {
        if (active)
        {
            tempMap[key] = val;
        }
        else
        {
            throw std::out_of_range("sdf");
        }
    }
    void begin_transaction()
    {
        active = !active;
    };
    void commitT()
    {
        commit = !commit;
        begin_transaction();
        unordered_map<string, int>::iterator it;
        for (it = tempMap.begin(); it != tempMap.end(); it++)
        {
            map[it->first] = it->second;
        }
        tempMap.clear();
    };
    void rollback()
    {
        tempMap.clear();
    };
};

int main()
{
    InMemoryDB inmemoryDB;
    // should return null, because A doesn’t exist in the DB yet
    // inmemoryDB.get("A");

    // should throw an error because a transaction is not in progress
    // inmemoryDB.put("A", 3);

    // // starts a new transaction
    inmemoryDB.begin_transaction();
    inmemoryDB.put("A", 3);

    // set’s value of A to 5, but its not committed yet
    inmemoryDB.put("A", 5);

    // should return null, because updates to A are not committed yet
    // inmemoryDB.get("A");

    // update A’s value to 6 within the transaction
    inmemoryDB.put("A", 6);

    // commits the open transaction
    inmemoryDB.commitT();
    inmemoryDB.get("A");

    return 0;
};