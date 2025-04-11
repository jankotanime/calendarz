# Calendarz  
### Version: Beta 1.3

---

**Calendarz** is a C++ program designed for managing a calendar and events assigned to specific days. This is my first significant project in C++, and I am still working on it.

## Environment Setup:

### Requirements:
- Linux
- g++ 11.4+  
- wxWidgets 3.0.5+  
- Make (optional)

### Running (On linux):
1. Run Calendarz with `./bin/calendarz`.
2. Run notificationService with `./bin/notificationService`.
3. For auto-starting open `~/.profile` or `~/.bash_profile` add "./{Calendarz-location}/bin/notificationService" to the new last line.

### Building:
1. Modify the Makefile to include the wxWidgets folder.
2. Build Calendarz with `make run`.
3. Build NotificationService with `make notirun`.

## Features:
- Date management using `chrono`.
- Event management, with data stored in a CSV file.
- Adding and deleting events.
- Daily notifications about events.