
🏦 Mini Banking Simulation (C++)

A console-based banking system built in C++ that simulates real-world banking operations including user registration, login, transactions, and an admin panel. This project was developed to practice core Object-Oriented Programming (OOP) concepts.

📋 Features
User Features

Register a new account with name, email, password, and initial deposit
Login with email and password (3 attempts before lockout)
Deposit money into your account
Withdraw money with balance validation
Check balance and view account details
Transfer funds to another registered account
Cascade Demo — demonstrates method chaining and operator overloading

Admin Features

Secure admin login (separate credentials)
View all registered accounts
Delete any user account
Manually set any account's balance


🗂️ Project Structure
mini-banking/
│
├── main.cpp        # All source code (single-file project)
└── README.md       # Project documentation


```

---

## 🔐 Default Credentials

### User Accounts (created at startup)
| Name | Email | Password | Balance |
|---|---|---|---|
| Ali | ali@gmail.com | ali123 | Rs. 5000 |
| Sara | sara@gmail.com | sara123 | Rs. 3000 |

### Admin Account
| Email | Password |
|---|---|
| admin@bank.com | admin123 |

---

## 🖥️ Menu Overview
```
=== BANK MENU ===
 1. Register
 2. Login
 3. Admin
 4. Exit
```

After login:
```
-- Menu --
 1. Deposit
 2. Withdraw
 3. Balance
 4. Transfer
 5. Cascade Demo
 6. Logout

📌 Key Design Decisions

Fixed array of 10 accounts — kept simple intentionally; no STL containers used to stay beginner-friendly
Friend function showAccount() — demonstrates how non-member functions can access private data
Cascade / method chaining — deposit() and withdraw() both return *this, enabling acc.deposit(100).deposit(200)
Operator overloading — += wraps the deposit logic; == compares accounts by email
Admin via pointer — Admin* admin = new Admin(...) demonstrates heap allocation and delete


🛡️ Input Validation

Email must contain @
No duplicate emails allowed
Passwords must be at least 6 characters
Deposits and withdrawals must be positive
Overdraft is prevented — can't withdraw more than available balance
Login is locked after 3 failed attempts


📚 What I Learned

Designing classes with proper encapsulation
Using this pointer to enable method chaining
Difference between static and instance members
How friend functions interact with private class data
Operator overloading in practical scenarios
Managing dynamic memory with new and delete


👨‍💻 Author
M.Muzammil
BS Software Engenering | Semester 2


This project was developed as part of an Object-Oriented Programming course to practice C++ class design, constructors, operator overloading, and memory management.
