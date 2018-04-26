# Laundry Management System

Laundry management system is a C++ application that built with Qt Creator. The database in this project is SQLite database browser. 

In order to run the project, 

1. Clone or download the project.

2. Download Qt Creator from it official website https://www.qt.io/, and SQLite from it official websit http://sqlitebrowser.org/.

3. Open the database file (sqlite/laundry.db) in SQLite database browser.

3. Open the project (main/Laundry_Management_System.pro) in Qt Creator. Then, open the main.cpp under sources folder, and change the line     12 to the directory path of your database file. 
                    >>>>dbLaundry.setDatabaseName("YOUR-FILE-PATH");
                    
4. Build and run the project.
