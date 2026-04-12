# 🏦 Simple Bank Management System (C++)

A robust console-based application built with **C++** using a functional programming approach. This system manages banking operations, customer data, and administrative user controls with a sophisticated permission system.

---

## 🚀 Key Features

### 👥 Customer Management
* **Full CRUD Operations:** Add, Find, Edit, and Delete customers.
* **View Records:** Display a comprehensive list of all customer data.

### 💰 Transactions Management
* **Deposit & Withdraw:** Securely manage account balances.
* **Total Balances:** View a summary of all customer account balances.

### 🔐 User & Security Management
* **Login System:** Secure access requiring a Username and Password.
* **User Administration:** Complete management of system users (Add, Edit, Delete, Find).
* **Advanced Permissions:** A granular access control system using **Bitwise Operators** to grant or deny specific functionalities to users.

---

### 🔹 Data Persistence (Flat-File DB)
* **Text-Based Storage:** All data (Customers & Users) is stored in `.txt` files.
* **Custom Separators:** Data is parsed using a specific separator (e.g., `(//)`) to distinguish between record fields.
* **Record Handling:** Efficient reading and writing logic to sync local data structures with the text files.

---

### 💻 Tech Stack
* **Language:** C++
* **Paradigm:** Functional / Procedural Programming
* **Environment:** Console Application (CLI)

---

### 📂 Project Structure
* `Clients.txt`: Stores customer records.
* `Users.txt`: Stores system user records and their permission masks.

---

### 🚀 How to Run
1. **Clone the repository.**
2. **Setup Data Files:** Ensure the `.txt` files are in the same directory.
3. **Run:** Execute the application.

---

### 🔐 Default Credentials
To access the system and explore all features, use the following administrator account:

| Field | Value |
| :--- | :--- |
| **Username** | `admin` |
| **Password** | `1234` |

> **Note:** This user is granted **Full Permissions** (`pAll`), allowing you to test every module in the system (Clients, Transactions, and User Management).

---

## ⚠️ Important Execution Note

For the application to function correctly, the database files (**`Clients.txt`** and **`Users.txt`**) must be located in the same directory as the code (**`.cpp`**) file. 

The program uses relative paths to read and write data. If these files are missing from the project folder, the system will not be able to load or save any records.

---


## 🛠️ Technical Highlights

### 🔹 Permissions System (Bitwise Logic)
The system utilizes **Enums** and **Bitwise AND &** operations to manage user permissions efficiently. Each permission is represented by a binary power (1, 2, 4, 8, etc.), allowing multiple permissions to be stored in a single integer.


```cpp
enum enPermissions {
    pAll = -1, pListClients = 1, pAddNewClient = 2, 
    pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, 
    pTranactions = 32, pManageUsers = 64
};
```

## 👤 About the Author

**Ebrahim Hasan**
A passionate Software Developer with a solid foundation in Computer Science. My journey started with learning the basics of the C++ language (Functional programming), then mastering **Algorithms, Object Oriented Programming and Data Structures** in C++, then learning C#, .NET and SQL Server Database, which paved the way for building complex systems using **C# and .NET**.

* **Expertise:** Desktop Applications (WinForms), SQL Server Database Design, and Logic Automation.
* **Key Projects:** Driver License Management System, Code Generator Tool.
* **Current Goal:** Transitioning into Web Full-stack Development (C#/.NET Backend).

---
📫 **Connect with me:**
* 📧 **Email:** [ebrahim-hasan-dev@gmail.com](mailto:ebrahim-hasan-dev@gmail.com)
* 💼 **LinkedIn:** [Your Profile Name](https://linkedin.com/in/ebrahim-hasan)
