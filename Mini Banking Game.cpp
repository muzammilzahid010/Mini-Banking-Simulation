#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int TRIES = 3;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


class Bank {
private:
    string name, email, password;
    float  balance;
    static int total;        

public:

    //  Default constructor
    Bank() : name(""), email(""), password(""), balance(0) {}

    //  Parameterized constructor + initializer list
    Bank(string n, string em, string pw, float bal)
        : name(n), email(em), password(pw), balance(bal) {
        total++;
    }

    // W3: Copy constructor (required by syllabus)
    Bank(const Bank& o)
        : name(o.name), email(o.email),
        password(o.password), balance(o.balance) {
    }

    //  Destructor
    ~Bank() {
        // cleanup — count managed by constructor and remove()
    }

    // W4: Accessors
    string getName()  const { return name; }
    string getEmail() const { return email; }

    //  const method
    float getBalance() const { return balance; }

    // static method
    static int getTotal() { return total; }

    // W4: Login check
    bool login(const string& em, const string& pw) const {
        return (email != "" && em == email && pw == password);
    }

    //  deposit — returns *this for cascade
    Bank& deposit(float amt) {
        if (amt <= 0) { cout << "[Error] Invalid amount!\n"; return *this; }
        balance += amt;
        cout << "[OK] Rs." << amt << " deposited. Balance: Rs." << balance << "\n";
        return *this;   //  this pointer enables cascade
    }

    // withdraw — returns *this for cascade
    Bank& withdraw(float amt) {
        if (amt <= 0) { cout << "[Error] Invalid amount!\n";           return *this; }
        if (amt > balance) { cout << "[Error] Not enough balance!\n";       return *this; }
        balance -= amt;
        cout << "[OK] Rs." << amt << " withdrawn. Balance: Rs." << balance << "\n";
        return *this;   // this pointer enables cascade
    }

    //  += operator — cascade shortcut for deposit
    Bank& operator+=(float amt) { return deposit(amt); }

    //  == operator — compare two accounts
    bool operator==(const Bank& o) const { return email == o.email; }

  
    friend void showAccount(const Bank& b) {
        cout << "  Name   : " << b.name << "\n"
            << "  Email  : " << b.email << "\n"
            << "  Balance: Rs." << b.balance << "\n";
    }

   transfer — takes object as argument
    void transfer(Bank& to, float amt) {
        if (amt <= 0) { cout << "[Error] Invalid amount!\n";     return; }
        if (amt > balance) { cout << "[Error] Not enough balance!\n"; return; }
        balance -= amt;
        to.balance += amt;
        cout << "[OK] Rs." << amt << " sent to " << to.name << "\n";
    }

    // Admin: set balance
    void setBalance(float b) {
        if (b < 0) { cout << "[Error] Cannot be negative!\n"; return; }
        balance = b;
        cout << "[Admin] Balance set to Rs." << b << "\n";
    }

    // Admin: delete
    void remove() {
        total--;
        cout << "[Deleted] " << name << "\n";
        name = email = password = "";
        balance = 0;
    }

};

int Bank::total = 0;   


// ═══════════════════════════════════════
//  CLASS: Admin
// ═══════════════════════════════════════
class Admin {
private:
    string email, password;

public:
    
    Admin(string em, string pw) : email(em), password(pw) {}

    bool login(const string& em, const string& pw) const {
        return (em == email && pw == password);
    }

    void viewAll(Bank acc[], int n) const {
        cout << "\n=== ALL ACCOUNTS ===\n";
        for (int i = 0; i < n; i++) {
            if (acc[i].getEmail() == "") continue; 
            cout << "[" << i + 1 << "]\n";
            showAccount(acc[i]);  
        }
        cout << "Total: " << Bank::getTotal() << "\n";
        cout << "====================\n";
    }

    void deleteAcc(Bank acc[], int n) const {
        viewAll(acc, n);
        if (Bank::getTotal() == 0) return;
        int i; cout << "Slot (1-" << n << "): "; cin >> i; i--;
        if (i < 0 || i >= n || acc[i].getEmail() == "")
        {
            cout << "[Error] Invalid slot!\n"; return;
        }
        acc[i].remove();
    }

    void changeBalance(Bank acc[], int n) const {
        viewAll(acc, n);
        if (Bank::getTotal() == 0) return;
        int i; cout << "Slot (1-" << n << "): "; cin >> i; i--;
        if (i < 0 || i >= n || acc[i].getEmail() == "")
        {
            cout << "[Error] Invalid slot!\n"; return;
        }
        float b; cout << "New balance: Rs."; cin >> b;
        acc[i].setBalance(b);
    }
};



// ═══════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════
int main() {

    Bank acc[10];
    int  n = 0;

    // Two accounts created by default at startup
    acc[n++] = Bank("Ali", "ali@gmail.com", "ali123", 5000);
    acc[n++] = Bank("Sara", "sara@gmail.com", "sara123", 3000);
    cout << "[System] 2 default accounts created.\n";

    
    Admin* admin = new Admin("admin@bank.com", "admin123");

    int ch = 0;
    do {
        cout << "\n=== BANK MENU ===\n"
            << " 1. Register\n"
            << " 2. Login\n"
            << " 3. Admin\n"
            << " 4. Exit\n"
            << " Choice: ";
        if (!(cin >> ch)) { clearCin(); continue; }

        // ── REGISTER ────────────────────
        if (ch == 1) {
            if (n >= 10) { cout << "[Error] Limit reached!\n"; continue; }

            string nm, em, pw; float bal;
            cout << "\n-- Register --\n";

            cout << "Name    : "; cin >> nm;

            cout << "Email   : "; cin >> em;
            if (em.find('@') == string::npos)
            {
                cout << "[Error] Invalid email!\n"; continue;
            }

            // duplicate check
            bool dup = false;
            for (int i = 0; i < n; i++)
                if (acc[i].getEmail() == em) { dup = true; break; }
            if (dup) { cout << "[Error] Email exists!\n"; continue; }

            cout << "Password: "; cin >> pw;
            if ((int)pw.size() < 6)
            {
                cout << "[Error] Password min 6 chars!\n"; continue;
            }

            cout << "Deposit : Rs.";
            if (!(cin >> bal) || bal < 0)
            {
                clearCin(); cout << "[Error] Invalid amount!\n"; continue;
            }

            acc[n++] = Bank(nm, em, pw, bal);
            cout << "[OK] Account created!\n";
        }

        // ── USER LOGIN ───────────────────
        else if (ch == 2) {
            int found = -1, tries = 0;
            cout << "\n-- Login --\n";

            while (tries < TRIES && found == -1) {
                string em, pw;
                cout << "Email   : "; cin >> em;
                cout << "Password: "; cin >> pw;
                for (int i = 0; i < n; i++)
                    if (acc[i].login(em, pw)) { found = i; break; }
                if (found == -1) {
                    tries++;
                    cout << "[Error] Wrong! " << TRIES - tries << " try(s) left.\n";
                }
            }
            if (found == -1) { cout << "[Locked] Too many attempts!\n"; continue; }
            cout << "[Welcome] " << acc[found].getName() << "!\n";

            int uc = 0;
            do {
                cout << "\n-- Menu --\n"
                    << " 1. Deposit\n 2. Withdraw\n 3. Balance\n"
                    << " 4. Transfer\n 5. Cascade Demo\n 6. Logout\n"
                    << " Choice: ";
                if (!(cin >> uc)) { clearCin(); continue; }

                float amt;
                switch (uc) {

                case 1:
                    cout << "Amount: Rs."; cin >> amt;
                    acc[found].deposit(amt);
                    break;

                case 2:
                    cout << "Amount: Rs."; cin >> amt;
                    acc[found].withdraw(amt);
                    break;

                case 3:
                    showAccount(acc[found]);   
                    break;

                case 4:
                    if (Bank::getTotal() < 2)
                    {
                        cout << "[Error] No other accounts!\n"; break;
                    }
                    cout << "Available:\n";
                    for (int i = 0; i < n; i++)
                        if (acc[i].getEmail() != "" && i != found)
                            cout << "  " << i + 1 << ". " << acc[i].getName() << "\n";
                    {
                        int t; cout << "Slot: "; cin >> t; t--;
                        if (t < 0 || t >= n || acc[t].getEmail() == "" || t == found)
                        {
                            cout << "[Error] Invalid slot!\n"; break;
                        }
                        cout << "Amount: Rs."; cin >> amt;
                        acc[found].transfer(acc[t], amt); 
                    }
                    break;

                case 5: {
                   
                    float a, b;
                    cout << "\n-- Cascade Demo --\n";
                    cout << "Deposit 1: Rs."; cin >> a;
                    cout << "Deposit 2: Rs."; cin >> b;

                    // Method cascade — each call returns *this
                    acc[found].deposit(a).deposit(b);

                    cout << "\nOperator += : Rs."; cin >> a;
                    (acc[found] += a);

                    
                    cout << "[==] Ali == Sara? "
                        << (acc[0] == acc[1] ? "Yes" : "No") << "\n";
                    cout << "[==] Ali == Ali? "
                        << (acc[0] == acc[0] ? "Yes" : "No") << "\n";

                    cout << "\n[Final]\n";
                    showAccount(acc[found]);   
                    break;
                }

                case 6: cout << "[Logout]\n"; break;
                default: cout << "[Error] Enter 1-6.\n";
                }
            } while (uc != 6);
        }

        // ── ADMIN LOGIN ──────────────────
        else if (ch == 3) {
            bool ok = false; int tries = 0;
            cout << "\n-- Admin Login --\n";
            while (tries < TRIES) {
                string em, pw;
                cout << "Email   : "; cin >> em;
                cout << "Password: "; cin >> pw;
                if (admin->login(em, pw)) { ok = true; break; }  
                tries++;
                cout << "[Error] Wrong! " << TRIES - tries << " try(s) left.\n";
            }
            if (!ok) { cout << "[Locked] Access denied!\n"; continue; }
            cout << "[Admin] Access granted!\n";

            int ac = 0;
            do {
                cout << "\n-- Admin Panel --\n"
                    << " 1. View All\n 2. Delete\n"
                    << " 3. Change Balance\n 4. Logout\n"
                    << " Choice: ";
                if (!(cin >> ac)) { clearCin(); continue; }
                switch (ac) {
                case 1: admin->viewAll(acc, n);                          break;
                case 2: admin->deleteAcc(acc, n);    break;
                case 3: admin->changeBalance(acc, n);  break;
                case 4: cout << "[Admin] Logged out.\n";                 break;
                default: cout << "[Error] Enter 1-4.\n";
                }
            } while (ac != 4);
        }

        else if (ch == 4) {
            cout << "[Exit] Goodbye!\n";
        }
        else { cout << "[Error] Enter 1-4.\n"; }

    } while (ch != 4);

    delete admin;   
    return 0;
}