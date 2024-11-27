#include "inMemoryDB.h"
#include <iostream>

void Database::begin_transaction() {
    if (currTransaction) {
        throw std::runtime_error("Transaction already in progress.");
    }
    currTransaction = true;
    transaction.clear();
}

void Database::put(const std::string& key, int value) {
    if (!currTransaction) {
        throw std::runtime_error("Cannot perform 'put' without an active transaction.");
    }
    transaction[key] = value;
}

int* Database::get(const std::string& key) const {
    if (currTransaction && transaction.count(key)) {
        return new int(transaction.at(key));
    }
    if (main_state.count(key)) {
        return new int(main_state.at(key));
    }
    return nullptr; 
}

void Database::commit() {
    if (!currTransaction) {
        throw std::runtime_error("No active transaction to commit.");
    }
    for (const auto& [key, value] : transaction) {
        main_state[key] = value;
    }
    currTransaction = false;
    transaction.clear();
}

void Database::rollback() {
    if (!currTransaction) {
        throw std::runtime_error("No active transaction to rollback.");
    }
    currTransaction = false;
    transaction.clear();
}

int main() {
    Database db;

    try {
        db.begin_transaction();
        db.put("key1", 10);
        db.put("key2", 20);

        // Handle `get` safely with pointers
        int* value1 = db.get("key1");
        if (value1) {
            std::cout << "Within transaction: key1 = " << *value1 << std::endl;
            delete value1; // Free the allocated memory
        } else {
            std::cout << "Within transaction: key1 not found" << std::endl;
        }

        db.commit();

        value1 = db.get("key1");
        if (value1) {
            std::cout << "After commit: key1 = " << *value1 << std::endl;
            delete value1; // Free the allocated memory
        } else {
            std::cout << "After commit: key1 not found" << std::endl;
        }

        db.begin_transaction();
        db.put("key1", 30);
        value1 = db.get("key1");
        if (value1) {
            std::cout << "Within new transaction: key1 = " << *value1 << std::endl;
            delete value1; // Free the allocated memory
        } else {
            std::cout << "Within new transaction: key1 not found" << std::endl;
        }

        db.rollback();

        value1 = db.get("key1");
        if (value1) {
            std::cout << "After rollback: key1 = " << *value1 << std::endl;
            delete value1; // Free the allocated memory
        } else {
            std::cout << "After rollback: key1 not found" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}