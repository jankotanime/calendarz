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

## Preview
![Zrzut ekranu 2025-06-10 213225](https://github.com/user-attachments/assets/1dc4c197-acc9-4db2-899f-bce03a91275c)
![Zrzut ekranu 2025-06-10 213516](https://github.com/user-attachments/assets/aa961f28-7bea-4b70-903a-db37beb10deb)
![Zrzut ekranu 2025-06-10 213417](https://github.com/user-attachments/assets/3add2bdf-7328-4bce-a0e1-033c36517b0e)
