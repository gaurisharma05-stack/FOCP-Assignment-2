#include <iostream>      // cin, cout
#include <sstream>       // istringstream
#include <string>        // string, getline
#include <unordered_map> // unordered_map
#include <unordered_set> // unordered_set
using namespace std;

class MovieTicket {
private:
    // Using unordered_map for O(1) average access
    // Using unordered_set for O(1) average insert/delete/lookup
    unordered_map<int, unordered_set<int>> bookings;
    const int MAX_SLOTS = 100;

public:
    // ─── BOOK X Y ───────────────────────────────────────────────
    // Try to book a ticket for customer X for movie Y
    // Returns false if:
    //   1. Customer already booked this movie
    //   2. Movie is sold out (100 tickets gone)
    // Otherwise adds customer to the movie's booking set → true
    bool book(int customerId, int movieId) {
        // If movieId not seen before, this auto-creates an empty set for it
        unordered_set<int>& bookedSet = bookings[movieId];

        // Condition 1: duplicate booking
        if (bookedSet.count(customerId)) return false;

        // Condition 2: sold out
        if ((int)bookedSet.size() >= MAX_SLOTS) return false;

        // All clear — book the ticket
        bookedSet.insert(customerId);
        return true;
    }

    // ─── CANCEL X Y ─────────────────────────────────────────────
    // Try to cancel customer X's ticket for movie Y
    // Returns false if customer never booked this movie
    // Otherwise removes them from the set → true
    bool cancel(int customerId, int movieId) {
        // If movieId has no entry at all, customer definitely hasn't booked
        if (bookings.find(movieId) == bookings.end()) return false;

        unordered_set<int>& bookedSet = bookings[movieId];

        // erase() returns number of elements removed (0 or 1 for a set)
        // So it naturally returns true/false for us
        return bookedSet.erase(customerId) > 0;
    }

    // ─── IS_BOOKED X Y ──────────────────────────────────────────
    // Check if customer X has an active booking for movie Y
    bool isBooked(int customerId, int movieId) {
        if (bookings.find(movieId) == bookings.end()) return false;
        return bookings[movieId].count(customerId) > 0;
    }

    // ─── AVAILABLE_TICKETS Y ────────────────────────────────────
    // Return how many seats are still open for movie Y
    // If movie has never been queried/booked, all 100 are available
    int availableTickets(int movieId) {
        if (bookings.find(movieId) == bookings.end()) return MAX_SLOTS;
        return MAX_SLOTS - (int)bookings[movieId].size();
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;
    cin.ignore(); // consume the newline after the integer

    MovieTicket mt;

    while (Q--) {
        string line;
        getline(cin, line);
        istringstream iss(line);

        string command;
        iss >> command;

        if (command == "BOOK") {
            int x, y;
            iss >> x >> y;
            cout << (mt.book(x, y) ? "true" : "false") << "\n";

        } else if (command == "CANCEL") {
            int x, y;
            iss >> x >> y;
            cout << (mt.cancel(x, y) ? "true" : "false") << "\n";

        } else if (command == "IS_BOOKED") {
            int x, y;
            iss >> x >> y;
            cout << (mt.isBooked(x, y) ? "true" : "false") << "\n";

        } else if (command == "AVAILABLE_TICKETS") {
            int y;
            iss >> y;
            cout << mt.availableTickets(y) << "\n";
        }
    }

    return 0;
}
