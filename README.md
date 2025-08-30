# Bank Management System 🏦

A comprehensive console-based banking management system built with C++ that provides secure client and user management with role-based access control.

## ✨ Features

### 🔐 Authentication & Security

- **Secure Login System** with username/password authentication
- **Role-Based Access Control** (RBAC) with granular permissions
- **Admin protection** (Admin user cannot be deleted)

### 👥 Client Management

- ✅ Add new clients with unique account numbers
- ✅ View all clients with formatted display
- ✅ Update client information
- ✅ Delete clients (with confirmation)
- ✅ Find clients by account number
- ✅ Client data validation and duplication prevention

### 💰 Transaction Management

- 💵 Deposit funds to client accounts
- 💸 Withdraw funds (with balance validation)
- 📊 View total balances across all accounts
- 🏦 Complete transaction history management

### 👨‍💼 User Management

- 👥 Add new system users with customizable permissions
- 👀 View all users
- ✏️ Update user credentials and permissions
- 🗑️ Delete users (except Admin)
- 🔍 Find users by username

### 🛡️ Permission System

- **7 granular permissions**:
  - List clients
  - Add new clients
  - Delete clients
  - Update clients
  - Find clients
  - Transactions management
  - Users management
- **Full access** option for administrators
- **Access denied** protection for unauthorized actions

## 🚀 Installation & Compilation

### Prerequisites

- C++ compiler (g++, clang++, or MSVC)
- C++11 or higher standard

### Compilation Command

```bash
g++ bank-system.cpp -o bank-system -std=c++11
```

Run the Application

```bash
./bank-system
```

## 📁 File Structure

```text
bank-management-system/
│
├── bank-system.cpp          # Main source code
├── Clients.txt              # Client data storage
├── Users.txt                # User credentials and permissions
└── README.md               # Documentation
```

## 🎮 Usage

### First-Time Setup

1. Create a Users.txt file with initial admin user:

```text
Admin#//#123#//#-1
```

2. Compile and run the application
3. Login with:
   - Username: Admin
   - Password: 123

### Default Login Credentials

- Admin Account: Username: Admin, Password: 123
- Permissions: Full access (-1)

### Navigation

1. <strong>Login</strong> with your credentials
2. <strong>Main Menu</strong> offers 8 options:

- Show client list
- Add new client
- Delete client
- Update client info
- Find client
- Transactions menu
- Manage users
- Logout

3. <strong>Transactions Menu</strong> provides:

- Deposit funds
- Withdraw funds
- View total balances
- Return to main menu

4. <strong>User Management Menu</strong> allows:

- List users
- Add new user
- Delete user
- Update user
- Find user
- Return to main menu

## 🔧 Technical Details

### Data Storage Format

- Clients: AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
- Users: Username#//#Password#//#Permissions

### Cross-Platform Support

- ✅ Windows (uses cls and pause)
- ✅ Linux/macOS (uses clear and custom pause)
- Automatic system detection and command adaptation

### Error Handling

- ✅ Input validation for numbers and strings
- ✅ File operation error checking
- ✅ Duplicate account number prevention
- ✅ Balance validation for withdrawals
- ✅ Permission checking for all operations

## 🛡️ Security Features

<strong>Password protection</strong> for all user accounts
<strong>Permission-based access control</strong>
<strong>Admin account protection</strong> (cannot be deleted)
<strong>Data validation</strong> on all inputs
<strong>Secure file operations</strong> with error checking

## 📊 Data Management

### Client Information Stored:

- Account Number (unique identifier)
- PIN Code
- Full Name
- Phone Number
- Account Balance

### User Information Stored:

- Username (unique identifier)
- Password
- Permission level

## 🎯 Permission Levels

| Permission     | Value | Description        |
| -------------- | ----- | ------------------ |
| Full Access    | -1    | All permissions    |
| List Clients   | 1     | View client list   |
| Add Clients 2  | Add   | new clients        |
| Delete Clients | 4     | Delete clients     |
| Update Clients | 8     | Modify client info |
| Find Clients   | 16    | Search clients     |
| Transactions   | 32    | Deposit/Withdraw   |
| Manage Users   | 64    | User management    |

## 🔄 Sample Data Files

## Users.txt Example:

```text
Admin#//#123#//#-1
manager#//#pass123#//#127
teller#//#teller123#//#57
```

### Clients.txt Example:

```text
1001#//#1234#//#John Smith#//#555-0101#//#2500.00
1002#//#5678#//#Jane Doe#//#555-0102#//#1800.50
1003#//#9012#//#Bob Johnson#//#555-0103#//#3200.75
```

## 🐛 Troubleshooting

### Common Issues:

1. <strong>File not found errors:</strong> Ensure Users.txt and Clients.txt exist
2. <strong>Permission denied:</strong> Check file write permissions
3. <strong>Compilation errors:</strong> Use C++11 or higher standard

### File Permissions:

```bash
chmod 644 Users.txt Clients.txt
```

## 📝 License

This project is open source and available under the [MIT](LICENSE) License.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Submit a pull request

## 📞 Support

For issues or questions:

1. Check file permissions
2. Verify data file formatting
3. Ensure proper compilation flags
