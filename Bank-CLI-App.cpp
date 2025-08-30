#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;
#ifdef _WIN32
#include <windows.h>
#endif
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
void pauseSystem() {
#ifdef _WIN32
  system("pause");
#else
  cout << "Press Enter to continue...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
#endif
}
string readString(string message) {
  string word;
  cout << message;
  getline(cin >> ws, word);
  return word;
}
struct stUser {
  string userName, password;
  short permissions;
  bool markForDelete = 0;
};
vector<string> splitString(string s1, string delim) {
  vector<string> vString;
  short pos = s1.find(delim);
  string sWord;                      // define a string variable
  while (pos != std::string::npos) { // use find() function to get the position
                                     // of the delimiters
    sWord = s1.substr(0, pos);       // store the word
    if (sWord != "")
      vString.push_back(sWord);
    s1.erase(
        0,
        pos + delim.length()); // erase() until position and move to next word.
    pos = s1.find(delim);
  }
  if (s1 != "")
    vString.push_back(s1); // it adds last word of the string.
  return vString;
}
stUser convertLineToUserRecord(string line, string separator = "#//#") {
  stUser user;
  vector<string> vUserData;
  vUserData = splitString(line, separator);
  user.userName = vUserData[0];
  user.password = vUserData[1];
  user.permissions = stoi(vUserData[2]);
  return user;
}
const string usersFileName = "Users.txt";
vector<stUser> loadUsersDataFromFile() {
  vector<stUser> vUsers;
  fstream myFile;
  myFile.open(usersFileName, ios::in); // read Mode
  if (myFile.is_open()) {
    string line;
    stUser user;
    while (getline(myFile, line)) {
      user = convertLineToUserRecord(line);
      vUsers.push_back(user);
    }
    myFile.close();
  }
  return vUsers;
}
bool findUserByUserNameAndPassword(string userName, string password,
                                   stUser &user) {
  vector<stUser> vUsers = loadUsersDataFromFile();
  for (stUser u : vUsers)
    if (u.userName == userName && u.password == password) {
      user = u;
      return 1;
    }
  return 0;
}
stUser currentUser;
enum enMainMenuOptions {
  eListClients = 1,
  eAddNewClient,
  eDeleteClient,
  eUpdateClient,
  eFindClient,
  eTransacionsMenu,
  eManageUsers,
  eLogout
};
struct stClient {
  string accountNumber;
  string pinCode;
  string name;
  string phone;
  double accountBalance;
  bool markForDelete = 0;
};
void printClientRecordLine(stClient client) {
  cout << "| " << setw(15) << left << client.accountNumber;
  cout << "| " << setw(10) << left << client.pinCode;
  cout << "| " << setw(40) << left << client.name;
  cout << "| " << setw(12) << left << client.phone;
  cout << "| " << setw(12) << left << client.accountBalance;
}
enum enMainMenuPermissions {
  eAll = -1,
  pListClients = 1,
  pAddNewClient = 2,
  pDeleteClient = 4,
  pUpdateClient = 8,
  pFindClient = 16,
  pTransactions = 32,
  pManageUsers = 64
};
bool checkAccessPermissions(enMainMenuPermissions permission) {
  short result = permission & currentUser.permissions;
  return currentUser.permissions == enMainMenuPermissions::eAll
             ? 1
             : (result == permission ? 1 : 0);
}
void showAccessDeniedMessage() {
  cout << "\n---------------------------------------------------\n";
  cout << "Access denied.\nYou don't have permission to do this.\nPlease "
          "contact your Admin.";
  cout << "\n---------------------------------------------------\n";
}
void showMainMenu();
void goBackToMainMenu() {
  pauseSystem();
  showMainMenu();
}
void showAccessDeniedScreen(enMainMenuPermissions permission) {
  if (!checkAccessPermissions(permission)) {
    clearScreen();
    showAccessDeniedMessage();
    goBackToMainMenu();
    return;
  }
}
stClient convertLineToRecord(string line, string separator = "#//#") {
  stClient client;
  vector<string> vClientData;
  vClientData = splitString(line, separator);
  client.accountNumber = vClientData[0];
  client.pinCode = vClientData[1];
  client.name = vClientData[2];
  client.phone = vClientData[3];
  client.accountBalance = stod(vClientData[4]); // cast string to double
  return client;
}
const string clientsFileName = "Clients.txt";
vector<stClient> loadClientsDataFromFile() {
  vector<stClient> vClients;
  fstream myFile;
  myFile.open(clientsFileName, ios::in); // read Mode
  if (myFile.is_open()) {
    string line;
    stClient client;
    while (getline(myFile, line)) {
      client = convertLineToRecord(line);
      vClients.push_back(client);
    }
    myFile.close();
  }
  return vClients;
}
void showAllClientsScreen() {
  showAccessDeniedScreen(enMainMenuPermissions::pListClients);
  clearScreen();
  vector<stClient> vClients = loadClientsDataFromFile();
  cout << "\n\t\t\t\t\tBalances list (" << vClients.size() << ") client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  cout << "| " << left << setw(15) << "account number";
  cout << "| " << left << setw(10) << "pin code";
  cout << "| " << left << setw(40) << "client name";
  cout << "| " << left << setw(12) << "phone";
  cout << "| " << left << setw(12) << "balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  if (vClients.size() == 0)
    cout << "\t\t\t\tThere aren't available clients in the system!";
  else
    for (stClient client : vClients) {
      printClientRecordLine(client);
      cout << endl;
    }
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  goBackToMainMenu();
}
void clientScreen(string sChoice) {
  clearScreen();
  cout << "\n-----------------------------------\n";
  cout << "\t" << sChoice << " clients screen";
  cout << "\n-----------------------------------\n";
}
bool clientExistsByAccountNumber(string accountNumber) {
  fstream myFile;
  myFile.open(clientsFileName, ios::in); // read Mode
  if (myFile.is_open()) {
    string line;
    stClient client;
    while (getline(myFile, line)) {
      client = convertLineToRecord(line);
      if (client.accountNumber == accountNumber) {
        myFile.close();
        return 1;
      }
    }
    myFile.close();
  }
  return 0;
}
void read(stClient &client) {
  client.pinCode = readString("Please, enter the pin code       : ");
  client.name = readString("Please, enter the name           : ");
  client.phone = readString("Please, enter the phone          : ");
}
double readNum(string message) {
  double num;
  cout << message;
  cin >> num;
  while (cin.fail()) {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Invalid number, enter a valid one: ";
    cin >> num;
  }
  return num;
}
stClient readNewClient() {
  stClient client;
  client.accountNumber = readString("Please, enter the account number : ");
  while (clientExistsByAccountNumber(client.accountNumber))
    client.accountNumber =
        readString("\nClient with [" + client.accountNumber +
                   "] already exists, enter another an account number: ");
  read(client);
  client.accountBalance = readNum("Please, enter the account balance: ");
  return client;
}
void addDataLineToFile(string sDataLine) {
  fstream myFile;
  myFile.open(clientsFileName, ios::out | ios::app);
  if (myFile.is_open()) {
    myFile << sDataLine << endl;
    myFile.close();
  }
}
string convertRecordToLine(stClient client, string separator = "#//#") {
  string sClientRecord = "";
  sClientRecord += client.accountNumber + separator;
  sClientRecord += client.pinCode + separator;
  sClientRecord += client.name + separator;
  sClientRecord += client.phone + separator;
  sClientRecord += to_string(client.accountBalance);
  return sClientRecord;
}
void addNewClient() {
  stClient client;
  client = readNewClient();
  addDataLineToFile(convertRecordToLine(client));
}
void addNewClients() {
  char addMore = 'Y';
  do {
    cout << "Adding new client:\n\n";
    addNewClient();
    cout << "\nThe client is added successfully, do you want to add more "
            "clients (y / n)?\n";
    cin >> addMore;
    cout << endl << endl;
  } while (toupper(addMore) == 'Y');
}
void showAddNewClientsScreen() {
  showAccessDeniedScreen(enMainMenuPermissions::pAddNewClient);
  clientScreen("Add new");
  addNewClients();
  goBackToMainMenu();
}
bool findClientByAccountNumber(string accountNumber, vector<stClient> vClients,
                               stClient &client) {
  for (stClient c : vClients)
    if (c.accountNumber == accountNumber) {
      client = c;
      return 1;
    }
  return 0;
}
void printClientCard(stClient client) {
  cout << "\nThe following are the client details:\n";
  cout << "-----------------------------------";
  cout << "\naccount number : " << client.accountNumber;
  cout << "\npin code       : " << client.pinCode;
  cout << "\nname           : " << client.name;
  cout << "\nphone          : " << client.phone;
  cout << "\naccount balance: " << client.accountBalance;
  cout << "\n-----------------------------------\n";
}
void markClientForDeleteByAccountNumber(string accountNumber,
                                        vector<stClient> &vClients) {
  for (stClient &c : vClients)
    if (c.accountNumber == accountNumber)
      c.markForDelete = 1;
}
void saveCleintsDataToFile(vector<stClient> vClients) {
  fstream myFile;
  myFile.open(clientsFileName, ios::out); // overwrite
  string dataLine;
  if (myFile.is_open()) {
    for (stClient c : vClients)
      if (!c.markForDelete) {
        dataLine = convertRecordToLine(
            c); // we only write records that are not marked for delete.
        myFile << dataLine << endl;
      }
    myFile.close();
  }
}
void deleteClientByAccountNumber(string accountNumber,
                                 vector<stClient> &vClients) {
  stClient client;
  char answer;
  if (findClientByAccountNumber(accountNumber, vClients, client)) {
    printClientCard(client);
    cout << "\n\nAre you sure you want to delete this client (y / n)?\n";
    cin >> answer;
    if (tolower(answer) == 'y') {
      markClientForDeleteByAccountNumber(accountNumber, vClients);
      saveCleintsDataToFile(vClients);
      cout << "\n\nThis client is deleted successfully.";
    }
  } else
    cout << "\nClient with account number (" << accountNumber
         << ") is not found!";
}
void showDeleteClientScreen() {
  showAccessDeniedScreen(enMainMenuPermissions::pDeleteClient);
  clientScreen("Delete");
  vector<stClient> vClients = loadClientsDataFromFile();
  string accountNumber = readString("\nPlease, enter an account number: ");
  deleteClientByAccountNumber(accountNumber, vClients);
  goBackToMainMenu();
}
stClient changeClientRecord(string accountNumber) {
  stClient client;
  client.accountNumber = accountNumber;
  read(client);
  client.accountBalance = readNum("Please, enter the account balance: ");
  return client;
}
void updateClientByAccountNumber(string accountNumber,
                                 vector<stClient> &vClients) {
  stClient client;
  char answer;
  if (findClientByAccountNumber(accountNumber, vClients, client)) {
    printClientCard(client);
    cout << "\n\nAre you sure you want to update this client (y / n)?\n";
    cin >> answer;
    if (tolower(answer) == 'y') {
      for (stClient &c : vClients)
        if (c.accountNumber == accountNumber) {
          c = changeClientRecord(accountNumber);
          break;
        }
      saveCleintsDataToFile(vClients);
      cout << "\n\nThis client is updated successfully.";
    }
  } else
    cout << "\nClient with account number (" << accountNumber
         << ") is not found!";
}
void showUpdateClientScreen() {
  showAccessDeniedScreen(enMainMenuPermissions::pUpdateClient);
  clientScreen("Update");
  vector<stClient> vClients = loadClientsDataFromFile();
  string accountNumber = readString("\nPlease, enter an account number: ");
  updateClientByAccountNumber(accountNumber, vClients);
  goBackToMainMenu();
}
void showFindClientScreen() {
  showAccessDeniedScreen(enMainMenuPermissions::pFindClient);
  clientScreen("Find");
  vector<stClient> vClients = loadClientsDataFromFile();
  stClient client;
  string accountNumber = readString("\nPlease, enter an account number: ");
  if (findClientByAccountNumber(accountNumber, vClients, client))
    printClientCard(client);
  else
    cout << "\nClient with account number[" << accountNumber
         << "] is not found!";
  goBackToMainMenu();
}
enum enTransacionsMenuOptions {
  eDeposite = 1,
  eWithdraw,
  eTotalBalances,
  eMainFromTrans
};
void showScreenTitle(string screenTitle) {
  clearScreen();
  cout << "\n-----------------------------------\n";
  cout << "\t" << screenTitle << " screen";
  cout << "\n-----------------------------------\n";
}
void depositAccountToClientByAccountNumber(double depositedAmount,
                                           string AccountNumber,
                                           vector<stClient> &vClients) {
  char answer;
  cout << "\n\nAre you sure you want to perform this transaction (y / n)?\n";
  cin >> answer;
  if (tolower(answer) == 'y') {
    for (stClient &c : vClients)
      if (c.accountNumber == AccountNumber) {
        c.accountBalance += depositedAmount;
        cout << "\n\nDone successfully, new balance: " << c.accountBalance
             << ".\n";
        break;
      }
    saveCleintsDataToFile(vClients);
  }
}
void showTransactionsMenu();
void goBackToTransactionsMenu() {
  pauseSystem();
  showTransactionsMenu();
}
void showDepositClientScreen() {
  showScreenTitle("Deposit");
  vector<stClient> vClients = loadClientsDataFromFile();
  string accountNumber = readString("\nPlease, enter an account number: ");
  stClient client;
  while (!findClientByAccountNumber(accountNumber, vClients, client))
    client.accountNumber = readString("\nClient with account number (" +
                                      accountNumber + ") is not found!\n");
  printClientCard(client);
  double depositedAmount = readNum("\n\nPlease, enter deposit amount: ");
  depositAccountToClientByAccountNumber(depositedAmount, accountNumber,
                                        vClients);
  goBackToTransactionsMenu();
}
void showWithdrawClientScreen() {
  showScreenTitle("Withdraw");
  vector<stClient> vClients = loadClientsDataFromFile();
  string accountNumber = readString("\nPlease, enter an account number: ");
  stClient client;
  char answer;
  while (!findClientByAccountNumber(accountNumber, vClients, client))
    client.accountNumber = readString("\nClient with account number (" +
                                      accountNumber + ") is not found!\n");
  printClientCard(client);
  double withdrawAmount = readNum("\n\nPlease, enter deposit amount: ");
  while (withdrawAmount > client.accountBalance)
    withdrawAmount =
        readNum("Amount exceeds the balance, you can't withdraw up to: " +
                to_string(client.accountBalance) + ".\n");
  depositAccountToClientByAccountNumber(withdrawAmount * (-1), accountNumber,
                                        vClients);
  goBackToTransactionsMenu();
}
void printClientRecordLineAfterTransactions(stClient client) {
  cout << "| " << setw(15) << left << client.accountNumber;
  cout << "| " << setw(40) << left << client.name;
  cout << "| " << setw(12) << left << client.accountBalance;
}
void showAllClientsScreenAfterTransactions() {
  clearScreen();
  double sumAccountBalances = 0;
  vector<stClient> vClients = loadClientsDataFromFile();
  cout << "\n\t\t\t\t\tBalances list (" << vClients.size() << ") client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  cout << "| " << left << setw(15) << "account number";
  cout << "| " << left << setw(40) << "client name";
  cout << "| " << left << setw(12) << "balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  if (vClients.size() == 0)
    cout << "\t\t\t\tThere aren't available clients in the system!";
  else
    for (stClient client : vClients) {
      sumAccountBalances += client.accountBalance;
      printClientRecordLineAfterTransactions(client);
      cout << endl;
    }
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  cout << "\n\t\t\t\t\tTotal balances = " << sumAccountBalances << ".\n\n";
  goBackToTransactionsMenu();
}
void perfromTransacionsOption(enTransacionsMenuOptions transactionsMenuOption) {
  switch (transactionsMenuOption) {
  case enTransacionsMenuOptions::eDeposite:
    showDepositClientScreen();
    break;
  case enTransacionsMenuOptions::eWithdraw:
    showWithdrawClientScreen();
    break;
  case enTransacionsMenuOptions::eTotalBalances:
    showAllClientsScreenAfterTransactions();
    break;
  case enTransacionsMenuOptions::eMainFromTrans:
    showMainMenu();
    break;
  default:
    showTransactionsMenu();
  }
}
void showTransactionsMenu() {
  showAccessDeniedScreen(enMainMenuPermissions::pTransactions);
  clearScreen();
  cout << "===========================================\n";
  cout << "\t\tTransactions menu screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Deposit.\n";
  cout << "\t[2] Withdraw.\n";
  cout << "\t[3] Total balances.\n";
  cout << "\t[4] Main menu.\n";
  cout << "===========================================\n";
  perfromTransacionsOption((enTransacionsMenuOptions) short(
      readNum("Choose what you want to do [1 to 4]: ")));
}
enum enManageUsersMenuOptions {
  eListUsers = 1,
  eAddNewUser,
  eDeleteUser,
  eUpdateUser,
  eFindUser,
  eMainFromManage = 6
};
void printUserRecordLine(stUser user) {
  cout << "| " << setw(15) << left << user.userName;
  cout << "| " << setw(10) << left << user.password;
  cout << "| " << setw(40) << left << user.permissions;
}
void showManageUsersMenu();
void goBackToManageUsersMenu() {
  pauseSystem();
  showManageUsersMenu();
}
void showAllUsersScreen() {
  clearScreen();
  vector<stUser> vUsers = loadUsersDataFromFile();
  cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  cout << "| " << left << setw(15) << "User Name";
  cout << "| " << left << setw(10) << "Password";
  cout << "| " << left << setw(40) << "Permissions";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  for (stUser user : vUsers) {
    printUserRecordLine(user);
    cout << endl;
  }
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  goBackToManageUsersMenu();
}
void userScreen(string sChoice) {
  clearScreen();
  cout << "\n-----------------------------------\n";
  cout << "\t" << sChoice << " users screen";
  cout << "\n-----------------------------------\n";
}
bool userExistsByUserName(string userName) {
  fstream myFile;
  myFile.open(usersFileName, ios::in); // read Mode
  if (myFile.is_open()) {
    string line;
    stUser user;
    while (getline(myFile, line)) {
      user = convertLineToUserRecord(line);
      if (user.userName == userName) {
        myFile.close();
        return 1;
      }
    }
    myFile.close();
  }
  return 0;
}
void changePermission(char answer, string question, short &permissions,
                      enMainMenuPermissions ePermissions) {
  cout << question;
  cin >> answer;
  if (tolower(answer) == 'y')
    permissions += ePermissions;
}
int readPermissionsToSet() {
  short permissions = 0;
  char answer = 'n';
  cout << "\nDo you want to give full access (y/n)? ";
  cin >> answer;
  if (tolower(answer) == 'y')
    return eAll;
  cout << "\nDo you want to give access to:\n";
  changePermission(answer, "\nShow client list (y/n)? ", permissions,
                   enMainMenuPermissions::pListClients);
  changePermission(answer, "Add new client (y/n)? ", permissions,
                   enMainMenuPermissions::pAddNewClient);
  changePermission(answer, "Delete client (y/n)? ", permissions,
                   enMainMenuPermissions::pDeleteClient);
  changePermission(answer, "Update client (y/n)? ", permissions,
                   enMainMenuPermissions::pUpdateClient);
  changePermission(answer, "Find client (y/n)? ", permissions,
                   enMainMenuPermissions::pFindClient);
  changePermission(answer, "Transactions (y/n)? ", permissions,
                   enMainMenuPermissions::pTransactions);
  changePermission(answer, "Manage users (y/n)? ", permissions,
                   enMainMenuPermissions::pManageUsers);
  return permissions == 127 ? -1 : permissions;
}
stUser readNewUser() {
  stUser user;
  user.userName = readString("Please, enter the user name: ");
  while (userExistsByUserName(user.userName))
    user.userName = readString("\nUser with [" + user.userName +
                               "] already exists, enter another user name.\n");
  user.password = readString("Please, enter the password : ");
  user.permissions = readPermissionsToSet();
  return user;
}
string convertRecordToLine(stUser user, string separator = "#//#") {
  string sUserRecord = "";
  sUserRecord += user.userName + separator;
  sUserRecord += user.password + separator;
  sUserRecord += to_string(user.permissions);
  return sUserRecord;
}
void addDataUserLineToFile(vector<stUser> vUsers) {
  fstream myFile;
  myFile.open(usersFileName, ios::out);
  if (myFile.is_open()) {
    string line;
    for (stUser &u : vUsers) {
      line = convertRecordToLine(u);
      myFile << line << endl;
    }
    myFile.close();
  }
}
void addNewUser(vector<stUser> &vUsers) {
  stUser user;
  user = readNewUser();
  vUsers.push_back(user);
  addDataUserLineToFile(vUsers);
}
void addNewUsers() {
  vector<stUser> vUsers = loadUsersDataFromFile();
  char addMore = 'Y';
  do {
    cout << "Adding new user:\n\n";
    addNewUser(vUsers);
    cout << "\nThe user is added successfully, do you want to add more users "
            "(y / n)?\n";
    cin >> addMore;
    cout << endl << endl;
  } while (toupper(addMore) == 'Y');
}
void showAddNewUsersScreen() {
  userScreen("Add New");
  addNewUsers();
  goBackToManageUsersMenu();
}
bool findUserByUserName(string userName, stUser &user) {
  vector<stUser> vUsers = loadUsersDataFromFile();
  for (stUser u : vUsers)
    if (u.userName == userName) {
      user = u;
      return 1;
    }
  return 0;
}
void printUserCard(stUser user) {
  cout << "\nThe following are the user details:\n";
  cout << "-----------------------------------";
  cout << "\nUser Name  : " << user.userName;
  cout << "\nPassword   : " << user.password;
  cout << "\nPermissions: " << user.permissions;
  cout << "\n-----------------------------------\n";
}
void markUserForDeleteByUserName(string userName, vector<stUser> &vUsers) {
  for (stUser &u : vUsers)
    if (u.userName == userName)
      u.markForDelete = 1;
}
void saveUsersDataToFile(vector<stUser> vUsers) {
  fstream myFile;
  myFile.open(usersFileName, ios::out); // overwrite
  string dataLine;
  if (myFile.is_open()) {
    for (stUser u : vUsers)
      if (!u.markForDelete) {
        dataLine = convertRecordToLine(
            u); // we only write records that are not marked for delete.
        myFile << dataLine << endl;
      }
    myFile.close();
  }
}
void deleteUserByUserName(string userName, vector<stUser> &vUsers) {
  stUser user;
  char Answer;
  if (findUserByUserName(userName, user)) {
    printUserCard(user);
    cout << "\n\nAre you sure you want to delete this user (y / n)? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      if (user.userName == "Admin")
        cout << "\nThis user (Admin) can not be deleted.\n";
      else {
        markUserForDeleteByUserName(userName, vUsers);
        saveUsersDataToFile(vUsers);
        cout << "\n\nThis user is deleted successfully.";
      }
    }
  } else
    cout << "\nUser with user name (" << userName << ") is not found!";
}
void showDeleteUserScreen() {
  userScreen("Delete");
  vector<stUser> vUsers = loadUsersDataFromFile();
  string userName = readString("\nPlease, enter the user name: ");
  deleteUserByUserName(userName, vUsers);
  goBackToManageUsersMenu();
}
stUser changeUserRecord(string userName) {
  stUser user;
  user.userName = userName;
  user.password = readString("\n\nPlease, enter the Password: ");
  user.permissions = readPermissionsToSet();
  return user;
}
void updateUserByUserName(string userName, vector<stUser> &vUsers) {
  stUser user;
  char Answer;
  if (findUserByUserName(userName, user)) {
    printUserCard(user);
    cout << "\n\nAre you sure you want to update this user (y / n)?\n";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      for (stUser &u : vUsers)
        if (u.userName == userName) {
          if (user.userName == "Admin")
            user.password = readString("\n\nPlease, enter the Password: ");
          else
            u = changeUserRecord(userName);
          break;
        }
      saveUsersDataToFile(vUsers);
      cout << "\n\nThis client is updated successfully.";
    }
  } else
    cout << "\nUser with user name (" << userName << ") is Not Found!";
}
void showUpdateUserScreen() {
  userScreen("Update");
  vector<stUser> vUsers = loadUsersDataFromFile();
  string userName = readString("\nPlease, enter the user name: ");
  updateUserByUserName(userName, vUsers);
  goBackToManageUsersMenu();
}
void showFindUserScreen() {
  userScreen("Find");
  vector<stUser> vUsers = loadUsersDataFromFile();
  stUser user;
  string userName = readString("\nPlease, enter the user name: ");
  if (findUserByUserName(userName, user))
    printUserCard(user);
  else
    cout << "\nUser with user Name[" << userName << "] is not found!";
  goBackToManageUsersMenu();
}
void performManageUsersMenuOption(
    enManageUsersMenuOptions ManageUsersMenuOption) {
  switch (ManageUsersMenuOption) {
  case enManageUsersMenuOptions::eListUsers:
    showAllUsersScreen();
    break;
  case enManageUsersMenuOptions::eAddNewUser:
    showAddNewUsersScreen();
    break;
  case enManageUsersMenuOptions::eDeleteUser:
    showDeleteUserScreen();
    break;
  case enManageUsersMenuOptions::eUpdateUser:
    showUpdateUserScreen();
    break;
  case enManageUsersMenuOptions::eFindUser:
    showFindUserScreen();
    break;
  case enManageUsersMenuOptions::eMainFromManage:
    showMainMenu();
    break;
  default:
    showManageUsersMenu();
  }
}
void showManageUsersMenu() {
  showAccessDeniedScreen(enMainMenuPermissions::pManageUsers);
  clearScreen();
  cout << "===========================================\n";
  cout << "\t\tManage users menu screen\n";
  cout << "===========================================\n";
  cout << "\t[1] List users.\n";
  cout << "\t[2] Add new user.\n";
  cout << "\t[3] Delete user.\n";
  cout << "\t[4] Update user.\n";
  cout << "\t[5] Find user.\n";
  cout << "\t[6] Main menu.\n";
  cout << "===========================================\n";
  performManageUsersMenuOption((enManageUsersMenuOptions) short(
      readNum("Choose what you want to do [1 to 6]: ")));
}
void showLoginScreen();
void performMainMenuOption(enMainMenuOptions MainMenuOption) {
  switch (MainMenuOption) {
  case enMainMenuOptions::eListClients:
    showAllClientsScreen();
    break;
  case enMainMenuOptions::eAddNewClient:
    showAddNewClientsScreen();
    break;
  case enMainMenuOptions::eDeleteClient:
    showDeleteClientScreen();
    break;
  case enMainMenuOptions::eUpdateClient:
    showUpdateClientScreen();
    break;
  case enMainMenuOptions::eFindClient:
    showFindClientScreen();
    break;
  case enMainMenuOptions::eTransacionsMenu:
    showTransactionsMenu();
    break;
  case enMainMenuOptions::eManageUsers:
    showManageUsersMenu();
    break;
  case enMainMenuOptions::eLogout:
    showLoginScreen();
    break;
  default:
    showMainMenu();
  }
}
void showMainMenu() {
  clearScreen();
  cout << "===========================================\n";
  cout << "\t\tMain menu screen\n";
  cout << "===========================================\n";
  cout << "\t[1] Show client list.\n";
  cout << "\t[2] Add new client.\n";
  cout << "\t[3] Delete client.\n";
  cout << "\t[4] Update client info.\n";
  cout << "\t[5] Find client.\n";
  cout << "\t[6] Transactions.\n";
  cout << "\t[7] Manage users.\n";
  cout << "\t[8] Logout.\n";
  cout << "===========================================\n";
  performMainMenuOption((enMainMenuOptions) short(
      readNum("Choose what you want to do [1 to 8]: ")));
}
void showLoginScreen() {
  string userName, password;
  bool loginFailed = 0;
  do {
    clearScreen();
    cout << "\n-----------------------------------\n";
    cout << "\tLogin screen";
    cout << "\n-----------------------------------\n";
    if (loginFailed)
      cout << "Invalid username/password!\n";
    userName = readString("Please, enter the user name: ");
    password = readString("Please, enter the password: ");
    loginFailed =
        !findUserByUserNameAndPassword(userName, password, currentUser);
  } while (loginFailed);
  showMainMenu();
}
int main() {
  showLoginScreen();
  pauseSystem();
  return 0;
}