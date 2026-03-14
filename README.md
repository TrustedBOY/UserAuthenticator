# UserAuth — C++ Console Authentication System

A lightweight console-based authentication system written in C++.
Supports user registration, login, and persistent encrypted storage.

## Features

- Sign Up with username, email, and password
- Login via username or email
- Password length validation (8–16 characters)
- Password confirmation on sign up
- Caesar-cipher encryption on all stored data
- Binary file storage
- Auto-creates data directory and file if missing
- Input validation with re-prompt on invalid entries

## Project Structure
```
project/
├── data/
│   └── loginData.dat       # auto-generated, stores encrypted user records
├── src/
│   └── main.cpp
└── README.md
```
## How Data is Stored

Each user record is stored as one line in the binary file:
```
[encrypted: username*email*password]
```

The entire record is encrypted using a character shift cipher (+44 on each byte)
before being written to disk, and decrypted on read.

## Requirements

- C++17 or later
- A C++ compiler (GCC, Clang, MSVC)

## Compilation
```bash
g++ -std=c++17 -o userauth src/main.cpp
```

## Usage
```
1- Login
2- Sign-Up
4- Exit
Enter Your Choice ::
```

## Planned Features

- [ ] Forgot password / reset
- [ ] Delete account
- [ ] Stronger encryption

## Notes

> This project is for learning purposes.
> The encryption method (character shift) is not secure for production use.
> Do not use this to store real sensitive data.

2025-03-14
