#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

class Bank {
private:
    // userId → balance
    // unordered_map gives O(1) average for all operations
    unordered_map<int, long long> accounts;

public:

    // CREATE X Y
    // If user X doesn't exist → create with balance Y → return true
    // If user X exists        → add Y to balance      → return false
    bool create(int userId, long long amount) {
        if (accounts.find(userId) == accounts.end()) {
            // New user — create account
            accounts[userId] = amount;
            return true;
        }
        // Existing user — just top up
        accounts[userId] += amount;
        return false;
    }

    // DEBIT X Y
    // Subtract Y from user X's balance
    // Fails if: user doesn't exist OR balance < Y
    bool debit(int userId, long long amount) {
        // User not found
        if (accounts.find(userId) == accounts.end()) return false;

        // Insufficient balance
        if (accounts[userId] < amount) return false;

        // All good — deduct
        accounts[userId] -= amount;
        return true;
    }

    // CREDIT X Y
    // Add Y to user X's balance
    // Fails if user doesn't exist
    bool credit(int userId, long long amount) {
        // User not found
        if (accounts.find(userId) == accounts.end()) return false;

        // Add money
        accounts[userId] += amount;
        return true;
    }

    // BALANCE X 
    // Return balance of user X
    // Return -1 if user doesn't exist
    long long balance(int userId) {
        if (accounts.find(userId) == accounts.end()) return -1;
        return accounts[userId];
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;
    cin.ignore();

    Bank bank;

    while (Q--) {
        string line;
        getline(cin, line);
        istringstream iss(line);

        string command;
        iss >> command;

        if (command == "CREATE") {
            int x; long long y;
            iss >> x >> y;
            cout << (bank.create(x, y) ? "true" : "false") << "\n";

        } else if (command == "DEBIT") {
            int x; long long y;
            iss >> x >> y;
            cout << (bank.debit(x, y) ? "true" : "false") << "\n";

        } else if (command == "CREDIT") {
            int x; long long y;
            iss >> x >> y;
            cout << (bank.credit(x, y) ? "true" : "false") << "\n";

        } else if (command == "BALANCE") {
            int x;
            iss >> x;
            cout << bank.balance(x) << "\n";
        }
    }

    return 0;
}
