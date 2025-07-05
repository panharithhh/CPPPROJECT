// test_product.cpp
#include "product.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

void test_viewProduct() {
    Stock stock;
    stock.addProduct(1, "Apple", 0.99, 10, "Fruit");
    stock.addProduct(2, "Milk", 2.49, 5, "Dairy");

    // Redirect cout to capture output
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    stock.viewProduct();

    // Restore cout
    cout.rdbuf(oldCout);

    string expectedHeader = "\nID\tName\tprice\tquantity\tcategory\n"
                            "-------------------------------------------------\n";
    string expectedRows =
        "1\tApple\t0.99\t10\tFruit\n"
        "2\tMilk\t2.49\t5\tDairy\n";

    string output = buffer.str();

    // Check header
    assert(output.find(expectedHeader) == 0);

    // Check rows
    assert(output.find(expectedRows) != string::npos);

    cout << "test_viewProduct passed!" << endl;
}

int main() {
    test_viewProduct();
    return 0;
}