#include <iostream>
#include "Testable.h"
#include "Variant.h"

bool doCompareTests() {
    ECE141::Variant theV0(100);
    ECE141::Variant theV1(theV0);

    if (!(theV0 == theV1)) return false;

    ECE141::Variant theV2(200);
    if (!(theV1 < theV2)) return false;

    ECE141::Variant theV3(200.0f);
    theV0 = theV3;
    if (!(theV0 == theV3)) return false;
    if (!(theV1 < theV3)) return false;

    ECE141::Variant theV4("200");
    theV0 = theV4;
    if (!(theV0 == theV4)) return false;
    if (!(theV1 < theV4)) return false;

    return true;
}

bool doValueTests() {
    // Test constructors
    ECE141::Variant theV1(100);
    ECE141::Variant theV2(6.28f);
    ECE141::Variant theV3("testing");

    std::stringstream theOut;
    theOut << theV1 << " " << std::fixed
            << theV2 << " " << theV3 << "\n";

    std::stringstream theIn1(theOut.str());
    int theInt;
    std::string theString1, theString2;
    theIn1 >> theInt >> theString1 >> theString2;
    theString1.erase(theString1.find_last_not_of('0') + 1, std::string::npos);

    if (theInt != 100 || theString1 != "6.28" || theString2 != "testing")
        return false;

    // Test assignment operators
    theOut.str(std::string());
    ECE141::Variant theVar(theV1); // Invoke the copy-constructor
    theVar = 200;
    theOut << theVar << " ";
    theVar = 3.14f;
    theOut << std::fixed << theVar << " ";
    theVar = "again";
    theOut << std::fixed << theVar << "\n";
    std::stringstream theIn2(theOut.str());
    theIn2 >> theInt >> theString1 >> theString2;
    theString1.erase(theString1.find_last_not_of('0') + 1, std::string::npos);
    if (theInt != 200 || theString1 != "3.14" || theString2 != "again")
        return false;

    // Test asInt()
    theVar = 3.14f;
    if (theVar.asInt() != 3)
        return false;

    // Test asFloat() and asString()
    auto theFloatVal = theVar.asFloat();
    theOut.str(std::string());
    theOut << std::fixed << theFloatVal.value();
    theString1 = theOut.str();
    if (theVar.asString() != theString1)
        return false;

    return true;
}

// Returns appropriate exit code ('0' for a passing test, '1' for a failing test).
int printTestMessage(const std::string& argument, const bool hasPassed) {
    std::cout << argument << " test " << (hasPassed ? "PASS" : "FAIL") << "\n";
    return static_cast<int>(!hasPassed);
}

int main(int argc, const char* argv[]) {
    if (argc > 1) {
        const std::string argument(argv[1]);

        if (argument == "compile")
            return printTestMessage(argument, true);
        if (argument == "values")
            return printTestMessage(argument, doValueTests());
        if (argument == "compare")
            return printTestMessage(argument, doCompareTests());

        std::cerr << "Invalid argument '" << argument << "'" << std::endl;
        return 1;
    }

    // Run your code here
    std::cout << "Hello, World!" << std::endl;

    return 0;
}