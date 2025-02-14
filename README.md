# COMP-1200: Intermediate C++ Programming

## Project Overview
This repository contains my **final assignment** for Intermediate C++ Programming (COMP 1200) at St. Lawrence College. The project is an **airline reservation system**, which demonstrates modular C++ programming, structured data storage, and validation techniques.

## Learning Objectives
This project applies:
- **Functions & Modular Programming**: Encapsulating logic into reusable functions.
- **File Handling in C++**: Reading and writing from data files.
- **Arrays & Parallel Data Structures**: Storing passenger reservations.
- **User Input Handling**: Ensuring error-free user interactions.
- **Boolean Logic & Validation**: Checking seat availability and preventing conflicts.

## Project Features
- **Passenger Management**: Stores names and seat assignments.
- **File-Based Persistence**: Reads existing reservations from `reservations.dat` and writes reports to `reservations.rpt`.
- **Seat Validation**: Ensures no duplicate seat assignments.
- **Search Functionality**: Allows searching for existing passengers.

## Repository Structure
```
COMP-1200-Intermediate-Cpp/
│── README.md                   # Project Overview
│── Assignment3.sln              # Visual Studio solution file
│── Assignment3.vcxproj          # C++ project file
│── Source.cpp                   # Core C++ program
│── reservations.dat             # Existing reservation data
│── reservations.rpt             # Output report file
│── LICENSE                      # Open-source license (optional)
```

## How to Compile & Run
1. Clone the repository:
   ```bash
   git clone https://github.com/tayjoleo/COMP-1200-Intermediate-Cpp.git
   ```
2. Open `Assignment3.sln` in **Visual Studio**.
3. Build and run the project from within **Visual Studio**.
4. Alternatively, compile manually using g++:
   ```bash
   g++ -o reservations Source.cpp
   ./reservations
   ```

## Future Improvements
- Implement **object-oriented programming (OOP)** to improve code organization.
- Expand **seat selection functionality** to allow modifications.
- Enhance **error handling** for better user experience.

## Author
Taylor Evans | Contact: **taylor.evans@student.sl.on.ca**
