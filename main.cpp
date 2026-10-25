#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();
void for_each_goat(const set<Goat>& trip);
void any_of_goat(const set<Goat>& trip);
void all_of_goat(const set<Goat>& trip);
void accumulate_goat(const set<Goat>& trip);
void copy_goat(const set<Goat>& trip);
void transform_goat(const set<Goat>& trip);
void lower_bound_goat(const set<Goat>& trip);
void upper_bound_goat(const set<Goat>& trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Create set of goats
    set<Goat> trip;

    // Main menu loop
    do {
        int choice = main_menu();

        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            delete_goat(trip);
        }
        else if (choice == 3) {
            cout << endl;
            display_trip(trip);
        }
        else if (choice == 4) {
            cout << endl;
            for_each_goat(trip);
        }
        else if (choice == 5) {
            any_of_goat(trip);
        }
        else if (choice == 6) {
            all_of_goat(trip);
        }
        else if (choice == 7) {
            accumulate_goat(trip);
        }
        else if (choice == 8) {
            copy_goat(trip);
        }
        else if (choice == 9) {
            transform_goat(trip);
        }
        else if (choice == 10) {
            lower_bound_goat(trip);
        }
        else if (choice == 11) {
            upper_bound_goat(trip);
        }
        cout << endl;
        

        again = (choice != 12);
    }
    while (again);




    return 0;
}

// ***** FUNCTION DEFINITIONS *****

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Display goat names (for_each)\n";
    cout << "[5] Check for goats older than specific age (any_of)\n";
    cout << "[6] Check all goats are younger than specific age (all_of)\n";
    cout << "[7] Average age of goats (accumulate)\n";
    cout << "[8] Copy goats into a vector (copy)\n";
    cout << "[9] Create a list of goat names (transform)\n";
    cout << "[10] Find the first goat at or after a name (lower_bound)\n";
    cout << "[11] Find the first goat after a name (upper_bound)\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > 12) {
        cout << endl;
        cout << "Invalid choice. Try again: ";
        cin >> choice;
    }
    return choice;
}

void add_goat(set<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    int age = rand() % (MAX_AGE + 1);
    string color = colors[rand() % SZ_COLORS];

    Goat newGoat(name, age, color);

    trip.insert(newGoat);
    cout << endl;
    cout << "Added goat successfully" << endl;
}

void display_trip(set<Goat> trip) {
    if (trip.empty()) {
        cout << "There are no goats in the trip.\n";
        return;
    }
    int count = 1;

    for (const Goat& goat : trip) {
        cout << "[" << count << "] " << goat.get_name()
             << " (" << goat.get_age() << ", "
             << goat.get_color() << ")" << endl;

        count++;
    }
}

int select_goat(set<Goat> trip) {
    cout << endl;
    display_trip(trip);

    int choice;
    cout << "Select a goat --> ";
    cin >> choice;

    while (choice < 1 || choice > trip.size()) {
        cout << "Invalid choice. Try again ";
        cin >> choice;
    }

    return choice;
}

void delete_goat(set<Goat>& trip) {
    if(trip.empty()) {
        cout << endl;
        cout << "There are no goats to delete.\n";
        return;
    }

    int choice = select_goat(trip);

    auto it = trip.begin();

    for (int i = 1; i < choice; i++) {
        ++it;
    }

    trip.erase(it);
    cout << endl;
    cout << "Deleted goat successfully" << endl;
}

void for_each_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "There are no goats in the trip." << endl;
        return;
    }
    for_each(trip.begin(), trip.end(), [](const Goat& goat) {
        cout << "Goat name: " << goat.get_name() << endl;
    });
}

void any_of_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    int age;
    cout << "Enter age: ";
    cin >> age;

    bool found = any_of(trip.begin(), trip.end(), [age](const Goat& goat) {
        return goat.get_age() > age;
    });

    if (found) {
        cout << "\nAt least one goat is older than " << age << "." << endl;
    } else {
        cout << "\nNo goats are older than " << age << "." << endl;
    }
}

void all_of_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    int age;
    cout << "Enter age: ";
    cin >> age;

    bool found = all_of(trip.begin(), trip.end(), [age](const Goat& goat) {
        return goat.get_age() < age;
    });

    if (found) {
        cout << "\nAll goats are younger than " << age << "." << endl;
    } else {
        cout << "\nNot all goats are younger than " << age << "." << endl;
    }
}

void accumulate_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    int total = accumulate(trip.begin(), trip.end(), 0, [](int total, const Goat& goat) {
        return total + goat.get_age();
    });

    // get average
    double average = static_cast<double>(total) / trip.size();
    // display average
    cout << "\nAverage goat age is " << fixed << setprecision(2) 
         << average << " years" << endl;
}

void copy_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    // create empty vector
    vector<Goat> copiedGoats;

    // copy goats from set into the vector
    copy(trip.begin(), trip.end(), back_inserter(copiedGoats));

    // display copied goats
    cout << "\nCopied goats: " << endl;

    for (const Goat& goat : copiedGoats) {
        cout << goat.get_name() << " ("
             << goat.get_age() << ", "
             << goat.get_color() << ")" << endl;
    }
}

void transform_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    // create vector to store goat names
    vector<string> goatNames;

    // extract names using transform
    transform(trip.begin(), trip.end(), back_inserter(goatNames), [](const Goat& goat) {
        return goat.get_name();
    });

    // display the transformed names
    cout << "\nGoat names (transform):" << endl;

    for (const string& name : goatNames) {
        cout << name << endl;
    }

}

void lower_bound_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    string name;
    cout << "Enter a goat name: ";
    cin >> name;

    // find the first goat whose name is >= the entered name
    auto it = lower_bound(trip.begin(), trip.end(), Goat(name));

    if (it != trip.end()) {
        cout << "\nFirst goat at or after " << name << ": "
             << it->get_name() << " ("
             << it->get_age() << ", "
             << it->get_color() << ")" << endl;
    } else {
        cout << "\nNo goat found at or after " << name << "." << endl;
    }
}

void upper_bound_goat(const set<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip." << endl;
        return;
    }

    string name;
    cout << "Enter a goat name: ";
    cin >> name;

    // find the first goat alphabetically after the entered name
    auto it = upper_bound(trip.begin(), trip.end(), Goat(name));

    if (it != trip.end()) {
        cout << "\nFirst goat after " << name << ": "
             << it->get_name() << " ("
             << it->get_age() << ", "
             << it->get_color() << ")" << endl;
    } else {
        cout << "\nNo goat found after " << name << "." << endl;
    }
}