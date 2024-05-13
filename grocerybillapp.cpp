#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

// Struct to represent an item purchased by a person
struct Item {
    string name;
    double cost;
};

int main() {
    // Variables to store bill information
    double totalBill, taxes, discount, totalCharged;
    
    // Input bill details from user
    cout << "Enter total bill amount: ";
    cin >> totalBill;
    cout << "Enter taxes and charges: ";
    cin >> taxes;
    cout << "Enter discount in percentage: ";
    cin >> discount;
    discount /= 100; // Convert percentage to decimal
    cout << "Enter total amount charged: ";
    cin >> totalCharged;

    // Input the number of people
    int numPeople;
    cout << "Enter the number of people: ";
    cin >> numPeople;

    // Input the total amount of items purchased together
    double commonTotal;
    cout << "Enter the total of items purchased together: ";
    cin >> commonTotal;

    // Map to store purchases for each person
    map<string, vector<Item>> purchases;

    // Loop to input purchases for each person
    for (int i = 0; i < numPeople; ++i) {
        string name;
        cout << "Enter name of person " << i + 1 << ": ";
        cin >> name;
        
        int numItems;
        cout << "Enter the number of items for " << name << ": ";
        cin >> numItems;

        vector<Item> items;
        // Loop to input each item for the person
        for (int j = 0; j < numItems; ++j) {
            string itemName;
            double itemCost;
            cout << "Enter name and cost of item " << j + 1 << " for " << name << ": ";
            cin >> itemName >> itemCost;
            items.push_back({itemName, itemCost});
        }
        purchases[name] = items; // Store items for the person
    }
     
    // Open a file to write the invoice details
    ofstream outputFile("invoice.txt");
    outputFile << "============================\n";
    outputFile << "         Total  Bill       \n";
    outputFile << "============================\n";
       
    // Calculate total cost and common costs
    double totalCost = totalBill + taxes;
    double commonTax = (commonTotal / totalBill) * taxes;
    if (discount != 0) {
        commonTotal *= discount;
    }
    double commonCost = commonTotal + commonTax;
    double additionalCost = commonCost / numPeople;

    // Write bill details to the file
    outputFile << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl;
    outputFile << "Taxes and Charges: $" << fixed << setprecision(2) << taxes << endl;
    outputFile << "Discount: " << fixed << setprecision(2) << discount * 100 << "%" << endl;
    outputFile << "Common per individual: $" << fixed << setprecision(2) << additionalCost << endl;
    outputFile << "Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
    outputFile << "============================\n"; 

    double totalCalculatedAmount = 0.0;
    // Loop through each person's purchases and calculate their individual totals
    for (const auto& person : purchases) {
        double personTotal = 0.0;
        outputFile << person.first << "'s Items:\n";
        // Loop through each item for the person
        for (const auto& item : person.second) {
            outputFile << "- " << item.name << ": $" << item.cost << endl;
            personTotal += item.cost;
        }
        // Calculate subtotal, tax share, and total for the person
        outputFile << "Subtotal for " << person.first << " before discount: $" << personTotal << endl;
        double taxShare = (personTotal / totalBill) * taxes;
        outputFile << "Tax Share for " << person.first << ": $" << fixed << setprecision(2) << taxShare << endl;
        if (discount != 0) {
            personTotal *= discount;
        }
        personTotal += additionalCost;
        personTotal += taxShare;
        outputFile << "Total for " << person.first << ": $" << fixed << setprecision(2) << personTotal << endl;
        outputFile << "============================\n";
        totalCalculatedAmount += personTotal;
    }
    outputFile.close();

    // Check if the calculated total matches the charged amount
    if (round(totalCalculatedAmount * 10) == round(totalCharged * 10)) {
        cout << "Calculation is correct. Total matches the charged amount." << endl;
    } else {
        cout << "Calculation is incorrect. Total does not match the charged amount." << endl;
    }
    cout << "Please find your invoice.txt in your local directory." << endl;
    
    return 0;
}
