💳💼 Credit Card Management System
A console-based **C++ application** that simulates a credit card system, enabling users to apply for credit cards, manage transactions, track reward points, and maintain a credit history, all with robust exception handling.

---
## 📝 Features
- Apply for different credit card types (Silver, Gold, Platinum) based on your credit score.
- Create and update secure 4-digit PINs.
- Make payments securely with PIN verification.
- Track transaction history and monitor outstanding balances.
- Earn reward points from your spending.
- Pay dues and maintain card health.
- View detailed card information including CVV, expiry date, and spending limit.
- Built with object-oriented design using runtime polymorphism.
- Includes robust exception handling with custom exceptions.

---
## 💻 Technologies Used

- **C++**
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)
- Exception Handling
- Time and random number generation for expiry dates and card numbers

---

## 📚 Class Overview
🛡️ Custom Exceptions
| Exception Class | Purpose |
|-----------------|---------|
| `INVALID_PIN` | Thrown for invalid PIN format |
| `INCORRECT_PIN_ERROR` | Thrown for wrong PIN entered |
| `INSUFFICIENT_BALANCE` | Triggered when spend limit is exceeded |
| `NO_CARD` | Thrown when card operations are attempted without a card |
| `INELIGIBLE_LIMIT_INCREMENT` | Used when a user tries to increase the limit without meeting the requirements |
| `DUE_PENDING` | Thrown when a cardholder attempts to surrender a card with pending dues |
| `INVALID_INPUT` | General invalid input handler |
| `PIN_NOT_GENERATED_ERROR` | Thrown when a PIN-related operation is done before generating a PIN |

---
### 💳 `CreditCard` (Base Class)
- Generates random card numbers and CVV.
- Has methods like:
  - `generatePIN()`
  - `changePIN()`
  - `Statement()`
  - `cardDetails()`
- Manages:
  - PIN
  - CVV
  - Spend Limit
  - Reward Points
  - Expiry Date
  - Transaction History

### 🧩 Derived Classes
| Class | Spend Limit | Reward Multiplier |
|-------|-------------|-------------------|
| `SilverCard` | ₹20,000 | 1% |
| `GoldCard` | ₹50,000 | 2% |
| `PlatinumCard` | ₹1,00,000 | 5% |

---

### 👤 `CardHolder`
- Stores:
  - Personal info (name, email, etc.)
  - Credit Score
  - List of credit cards
- Key Methods:
  - `applyCreditCard()`
  - `pay(receiver, amount, currentUser)`
  - `duePayment(amount)`
  - `displayCards()`
  - `dropCard(index)`

---

## ⏩ Flow of Execution

1. **Apply Card:** Credit score is checked, appropriate card is issued.
2. **Generate PIN:** Secure 4-digit PIN setup.
3. **Make Payments:** PIN is validated, spend limit checked.
4. **View Transactions:** See detailed statement of credit activity.
5. **Pay Dues:** Settle outstanding balances.
6. **Display Cards:** View card details and current status.

---

## 🎯 Sample Use Case

```cpp
CardHolder user("Raghavendra", "Karnataka", "raghavendrasadare@gmail.com", "9380616288", 900);
user.applyCreditCard(); // Issues Platinum Card
user.pay("Amazon", 3000.0, &user); // Makes a secure transaction
user.duePayment(3000.0); // Pays due amount
user.displayCards(); // View all cards and details




