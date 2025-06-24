#include <iostream>
#include <vector>
using namespace std;
class Transactions{
    public:
    string type;
    double amount;
    string details;
    Transactions(string t,double amt,string det){
        type=t;
        amount=amt;
        details=det;
    }
    void show_transactions_details(){
        cout<<type<<" | "<<"amount : "<<amount<<endl;
    }
};
class Account{
    public:
    int accountNumber;
    string holderName;
    string mobileNumber;
    float balance;
    vector<Transactions> transactions;
    Account(int accno , string holname , string mobno , float bal) : accountNumber(accno) , holderName(holname) , mobileNumber(mobno) , balance(bal){}
    void add_transactions(string type, double amount, string details){
        transactions.emplace_back(type,amount,details);
        if(type == "deposit"){
            balance+=amount;
        }
        else if(type == "withdraw"){
            balance-=amount;
        }
    }
     void displayAccount() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Balance: ₹" << balance << endl;
    }

};
class customer{
    public:
    string name;
    long long int Mobile_Number;
    string gmail;
    void get_data(){
        cin.ignore();
        cout<<"Enter your name : ";
        getline(cin,name);
        cout<<"Enter your mobile number : ";
        cin>>Mobile_Number;
        if(Mobile_Number < 10)return;
        cout<<"Enter your gmail : ";
        cin>>gmail;
    }
    void Show_data(){
        cout<<"Your name : "<<name<<endl;
        cout<<"Your Mobile number : "<<Mobile_Number<<endl;
        cout<<"Your Gmail id : "<<gmail<<endl;
    }
};
int main() {
    vector<Account> accounts;
    int accCounter = 1000;

    while (true) {
        cout << "\n---- Banking System Menu ----\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Details\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, mob, gmail;
            float initBal;
            cin.ignore();
            cout << "Enter holder name: ";
            getline(cin, name);
            cout << "Enter mobile number: ";
            getline(cin, mob);
            cout << "Enter Gmail: ";
            getline(cin, gmail);
            cout << "Enter initial balance: ";
            cin >> initBal;

            Account newAcc(++accCounter, name, mob, initBal);
            accounts.push_back(newAcc);
            cout << "Account created successfully! Account Number: " << accCounter << endl;
        }
        else if (choice == 2) {
            int accno;
            double amt;
            cout << "Enter account number: ";
            cin >> accno;
            cout << "Enter deposit amount: ";
            cin >> amt;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.accountNumber == accno) {
                    acc.add_transactions("deposit", amt, "Cash deposit");
                    cout << "Amount deposited successfully.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found!\n";
        }
        else if (choice == 3) {
            int accno;
            double amt;
            cout << "Enter account number: ";
            cin >> accno;
            cout << "Enter withdraw amount: ";
            cin >> amt;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.accountNumber == accno) {
                    if (acc.balance >= amt) {
                        acc.add_transactions("withdraw", amt, "Cash withdrawal");
                        cout << "Amount withdrawn successfully.\n";
                    } else {
                        cout << "Insufficient balance!\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found!\n";
        }
        else if (choice == 4) {
            int fromAcc, toAcc;
            double amt;
            cout << "Enter sender's account number: ";
            cin >> fromAcc;
            cout << "Enter receiver's account number: ";
            cin >> toAcc;
            cout << "Enter amount to transfer: ";
            cin >> amt;

            Account *sender = nullptr, *receiver = nullptr;
            for (auto &acc : accounts) {
                if (acc.accountNumber == fromAcc) sender = &acc;
                if (acc.accountNumber == toAcc) receiver = &acc;
            }

            if (!sender || !receiver) {
                cout << "One or both accounts not found!\n";
            } else if (sender->balance < amt) {
                cout << "Insufficient balance!\n";
            } else {
                sender->add_transactions("withdraw", amt, "Transfer to " + to_string(toAcc));
                receiver->add_transactions("deposit", amt, "Transfer from " + to_string(fromAcc));
                cout << "Transfer successful!\n";
            }
        }
        else if (choice == 5) {
            int accno;
            cout << "Enter account number: ";
            cin >> accno;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.accountNumber == accno) {
                    acc.displayAccount();
                    cout << "Transaction History:\n";
                    for (auto &t : acc.transactions) {
                        t.show_transactions_details();
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found!\n";
        }
        else if (choice == 6) {
            cout << "Thank you for using the Banking System. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
