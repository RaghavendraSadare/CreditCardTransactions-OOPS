#include<iostream>
#include<vector>
#include<exception>
#include<ctime>
#include<cstdlib>
#include<limits>
using namespace std;

int randomNum() {
    return rand() % 10;
}

class INVALID_PIN: public runtime_error {
    public:
        INVALID_PIN(): runtime_error("PIN entered is not in format") {}
};

class INCORRECT_PIN_ERROR: public runtime_error {
    public:
        INCORRECT_PIN_ERROR(): runtime_error("PIN Mismatch") {}
};

class INSUFFICIENT_BALANCE: public runtime_error {
    public:
        INSUFFICIENT_BALANCE(): runtime_error("Insufficient Amount") {}
};

class NO_CARD: public runtime_error {
    public:
        NO_CARD(): runtime_error("No Credit Card Issued") {}
};

class INELIGIBLE_LIMIT_INCREMENT: public runtime_error {
    public:
        INELIGIBLE_LIMIT_INCREMENT(): runtime_error("Spend More on Credit to be eligible for Spend Limit Increment") {}
};

class DUE_PENDING: public runtime_error {
    public:
        DUE_PENDING(): runtime_error("Pay the Due Amount Before Surrendering") {}
};

class INVALID_INPUT: public runtime_error {
    public:
        INVALID_INPUT(): runtime_error("Please enter Valid Input") {}
};

class PIN_NOT_GENERATED_ERROR: public runtime_error {
    public:
        PIN_NOT_GENERATED_ERROR(): runtime_error("PIN is not generated") {}
};

void giveChoices();
void cardActions();

class Transaction {
    public:
        string To;
        double amt;
        
        Transaction(string receiver, double amount): To(receiver), amt(amount) {}
};

class CreditCard {
    protected:
        int cvv;

    public:
        int PIN;
        string cardNo;
        string cName;
        double multipler;
        double spendLimit;
        double outstandingBalance;
        string expiryDate;
        vector <Transaction> statement;
        int rewardPoints;

    friend int randomNum();

    CreditCard() {
        outstandingBalance = 0;

        // CARD NUMBER GENERATION
        for (int x=0; x<16; x++)
            cardNo.append(to_string(randomNum()));

        // CVV GENERATION
        string temp = "";
        for (int x=0; x<3; x++)
            temp.append(to_string(randomNum()));
        cvv = stoi(temp);

        // EXPIRE DATE
        expiryDate = expireDate();
    }

    virtual void cardDetails() const {
        cout << "Card No: " << cardNo << endl;
        cout << "CVV: " << cvv << endl;
        cout << "Exp Date: " << expiryDate << endl;
        cout << "Spend Limit: " << spendLimit << endl;
        cout << "Outstanding Balance: " << outstandingBalance << endl;
    }

    void generatePIN() {
        cout << "Generating PIN" << endl;
        int tempPIN;
        this->PIN = 0;
        try {
            cout << "Enter New PIN: " << endl;
            cin >> this->PIN;
            cin.ignore();
            if(this->PIN < 1000 || this->PIN > 9999) 
                throw INVALID_PIN();
        } catch(INVALID_PIN& e) {
            cout << e.what() << endl;
            this->PIN = 0;
        }
        cout << "PIN: " << this->PIN << endl;
    }

    void changePIN() {
        cout << "Change of PIN" << endl;
        int tempPIN;
        try {
            cout << "Enter Current PIN: ";
            cin >> tempPIN;
            if(PIN != tempPIN) 
                throw INCORRECT_PIN_ERROR();    
            else {
                cout << "Enter New PIN: ";
                cin >> tempPIN;
                if(tempPIN <= 0 || tempPIN > 9999) 
                    throw INVALID_PIN();        
                else {
                    PIN = tempPIN;
                    cout << "PIN Updated" << endl;
                }
            }
        } catch(INCORRECT_PIN_ERROR& e) {
            cout << e.what() << endl;
        } catch(INVALID_PIN& e) {
            cout << e.what() << endl;
        }
    }

    string expireDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int year = 1900 + ltm->tm_year + 5; // assuming the credit card validity is 5 years
        int month = 1 + ltm->tm_mon;

        string expDate;

        if (month < 10) {
            expDate = "0" + to_string(month);
        } else {
            expDate = to_string(month);
        }
        expDate.append("/");
        expDate.append(to_string(year).substr(2, 2));
        return expDate;
    }

    double Statement() {
        int x = statement.size();
        double totalSpend = 0;
        for(int i=0; i<x; i++) {
            cout << statement[i].To << ": ";
            cout << statement[i].amt << endl;
            if(statement[i].To != "Repay Due Amount")
                totalSpend += statement[i].amt;
        }
        return totalSpend;
    }

    int getPIN() {
        return PIN;
    }
};

class SilverCard: public CreditCard {
    public:
        SilverCard() {
            cName = "Silver Card";
            multipler = 0.01;
            rewardPoints = 0;
            spendLimit = 20000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class GoldCard: public CreditCard {
    public:
        GoldCard() {
            cName = "Gold Card";
            multipler = 0.02;
            rewardPoints = 0;
            spendLimit = 50000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class PlatinumCard: public CreditCard {
    public:
        PlatinumCard() {
            cName = "Platinum Card";
            multipler = 0.05;
            rewardPoints = 0;
            spendLimit = 100000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class CardHolder {
    public:
        string name;
        string address;
        string email;
        string phoneNo;
        vector<CreditCard*> Cards;
        CreditCard* CurrCard;
        int creditScore;

        CardHolder(string n, string a, string e, string p, int c): name(n), address(a), email(e), phoneNo(p), creditScore(c) {}

        ~CardHolder() {
            for(int i=0; i<Cards.size(); i++) {
                dropCard(i);
            }
        }

        void applyCreditCard() {
            cout << "Application for Credit Card" << endl;
            int res;
            if(creditScore > 800) {
                CurrCard = new PlatinumCard();
                Cards.push_back(CurrCard);
                CurrCard->generatePIN();
                cout << "Platinum Card Issued:" << endl;
                CurrCard->cardDetails();
            } else if(creditScore > 675) {
                CurrCard = new GoldCard();
                Cards.push_back(CurrCard);
                CurrCard->generatePIN();
                cout << "Gold Card Issued:" << endl;
                CurrCard->cardDetails();
            } else {
                CurrCard = new SilverCard();
                Cards.push_back(CurrCard);
                CurrCard->generatePIN();
                cout << "Silver Card Issued:" << endl;
                CurrCard->cardDetails();
            }
        }

        void pay(string receiver, double amt, CardHolder* currUser) {
            cout << "Transaction:" << endl;
            int cardPin;
            try {
                if(CurrCard->PIN == 0) {
                    throw PIN_NOT_GENERATED_ERROR();
                }
                if(CurrCard == nullptr) 
                    throw NO_CARD();

                cout << "Enter PIN:" << endl;
                cin >> cardPin;
                system("cls");
                if(cardPin != CurrCard->getPIN())
                    throw INCORRECT_PIN_ERROR();

                if(CurrCard->outstandingBalance + amt <= CurrCard->spendLimit) {
                    CurrCard->outstandingBalance += amt;
                    CurrCard->statement.push_back(Transaction(receiver,amt));
                    cout << "Transaction Done: " << receiver << ": " << amt << endl;
                    CurrCard->rewardPoints += amt * CurrCard->multipler;
                } else {
                    throw INSUFFICIENT_BALANCE();
                }
            } catch(INSUFFICIENT_BALANCE& e) {
                cout << "Available Limit: " << CurrCard->spendLimit - CurrCard->outstandingBalance << endl;
                cout << e.what() << endl;
            } catch(NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            } catch(INCORRECT_PIN_ERROR& e) {
                cout << e.what() << endl;
                cout << "Transaction Failed" << endl;
            } catch(PIN_NOT_GENERATED_ERROR& e) {
                cout << "Generate PIN" << endl;
                CurrCard->generatePIN();
                currUser->pay(receiver,amt,currUser);
            }
            cout << "(0) Menu" << endl;
        }

        void displayCards() {
            cout << "Displaying the list of cards:" << endl;
            for(int i=0; i<Cards.size(); i++) {
                Cards[i]->cardDetails();
                cout << endl;
            }
        }

        void duePayment(double amt) {
            cout << "Paying the Unstanding Balance of Card" << endl;
            int cardPin;
            try {
                if(CurrCard == nullptr)
                    throw NO_CARD();

                cout << "Enter PIN: " << endl;
                cin >> cardPin;
                system("cls");
                if(cardPin != CurrCard->getPIN())
                    throw INCORRECT_PIN_ERROR();

                if(CurrCard->outstandingBalance < amt) {
                    amt = CurrCard->outstandingBalance;
                }

                CurrCard->outstandingBalance -= amt;
                CurrCard->statement.push_back(Transaction("Repay Due Amount",amt));
                cout << "Outstanding Amount Cleared: " << amt << endl;
            } catch(NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            } catch(INCORRECT_PIN_ERROR& e) {
                cout << e.what() << endl;
                cout << "Transaction Failed" << endl;
            }
        }

        void incrSpendLimit() {
            system("cls");
            cout << "Application for Increment of Credit Card Limit" << endl;
            double totalSpend = CurrCard->Statement();
            try {
                if(totalSpend < 0.25 * CurrCard->spendLimit) {
                    throw INELIGIBLE_LIMIT_INCREMENT();
                } else {
                    cout << "Spend Limit before: " << CurrCard->spendLimit << endl;
                    CurrCard->spendLimit += totalSpend;
                    cout << "Spend Limit after: " << CurrCard->spendLimit << endl;
                }
            } catch(INELIGIBLE_LIMIT_INCREMENT& e) {
                cout << e.what() << endl;
            }
        }

        void dropCard(int cardInd) {
            system("cls");
            cout << "Surrendering the Card" << endl;
            try {
                if(cardInd >= Cards.size())
                    throw INVALID_INPUT();

                CurrCard = Cards[cardInd];
                if(CurrCard->outstandingBalance > 0) {
                    throw DUE_PENDING();
                } else {
                    delete CurrCard;
                    Cards.erase(Cards.begin() + cardInd);
                    cout << "Card Deleted" << endl;
                }
            } catch(INVALID_INPUT& e) {
                cout << e.what() << endl;
            } catch(DUE_PENDING& e) {
                cout << e.what() << endl;
            }
        }

        // void viewStatement() {
            
        //     for(int i=0; i<CurrCard->statement; i++) {
        //         cout << CurrCard->statement[i].To << ": " << CurrCard->statement[i].amt << endl;
        //     }
        // }
};

vector<CardHolder> Users;
CardHolder* currentUser = nullptr;

int main() {
    srand(time(0)); // Initialize random number generator

    string name, address, email, phone;
    int creditScore;
    int choice, userIndex, cardCh;
    while (true) {
        cout << "1. Add User\n2. Select User\n3. Exit\nEnter choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                cout << "Enter User Details" << endl;
                cout << "<------------------->" << endl;
                cout << "Enter name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter address: ";
                getline(cin, address);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter phone number: ";
                getline(cin, phone);
                cout << "Enter credit score: ";
                cin >> creditScore;
                Users.emplace_back(name, address, email, phone, creditScore);
                system("cls");
                cout << "User added successfully." << endl;
                break;

            case 2:
                cout << "Select User:" << endl;
                for (size_t i = 0; i < Users.size(); ++i) {
                    cout << i + 1 << ". " << Users[i].name << endl;
                }
                cout << "Enter choice: ";
                cin >> userIndex;

                if (userIndex > 0 && userIndex <= Users.size()) {
                    currentUser = &Users[userIndex - 1];
                    cout << "Selected User: " << currentUser->name << endl;
                    system("cls");
                    cardActions();
                } else {
                    cout << "Invalid user selection." << endl;
                }
                system("cls");
                break;

            case 3:
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void cardActions() {
    int cardCh = 0;
    giveChoices();
    while (cardCh != 8) {
        cin >> cardCh;
        system("cls");

        switch (cardCh) {
            case 1:
                currentUser->applyCreditCard();
                cout << "\n (0) Menu " << endl;
                break;

            case 2:
                system("cls");
                currentUser->displayCards();
                cout << "\n (0) Menu " << endl;
                break;

            case 3:
                {
                    string receiver;
                    double amt;
                    cout << "Enter Receiver Name: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, receiver);
                    cout << "Enter Amount: ";
                    cin >> amt;
                    currentUser->pay(receiver, amt,currentUser);
                }
                break;

            case 4:
                {
                    double amt;
                    cout << "Enter Amount to Repay: ";
                    cin >> amt;
                    currentUser->duePayment(amt);
                    cout << "(0) Menu" << endl;
                }
                break;

            case 5:
                currentUser->incrSpendLimit();
                break;

            case 6:
                int index;
                currentUser->displayCards();
                cout << "Enter card index to drop: ";
                cin >> index;
                currentUser->dropCard(index - 1);
                break;

            case 7:
                currentUser->CurrCard->changePIN();
                cout << "(0) Menu" << endl;
                break;

            case 8:
                cout << "Switching user..." << endl;
                currentUser = nullptr;
                break;

            case 9:
                cout << "Displaying Card Transactions:" << endl;
                currentUser->CurrCard->Statement();
                cout << "(0) Menu" << endl;
                break;

            case 10:
                currentUser = nullptr;
                break;

            case 0:
                giveChoices();
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void giveChoices() {
    cout << "1. Apply for Credit Card\n";
    cout << "2. Display All Cards\n";
    cout << "3. Pay Using Credit Card\n";
    cout << "4. Repay Due Amount\n";
    cout << "5. Increase Spend Limit\n";
    cout << "6. Drop Card\n";
    cout << "7. Change PIN\n";
    cout << "8. Switch User\n";
    cout << "9. View Statement\n";
    cout << "10. Back\n";
    cout << "0. View Menu\n";
}
