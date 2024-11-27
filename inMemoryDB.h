#ifndef INMEMORYDB_H
#define INMEMORYDB_H

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <optional>

using namespace std;

class Database{
public:
    void begin_transaction(); // start new transaction
    void put(const string& key, int val); // add or update key-val pair (only allowed during transaction)
    int* get(const string& key) const; // get val for given key
    void commit(); // commit curr transaction
    void rollback(); // abort all changes made within the transaction

private:
    unordered_map<string, int> main_state;
    unordered_map<string, int> transaction;
    bool currTransaction = false;
};

#endif 