#include <iostream>
#include "Testable.h"
#include "Variant.h"

bool doCompareTests() {
    ECE141::Variant theV0(100);
    ECE141::Variant theV1(theV0);

    if (!(theV0 == theV1)) {
        std::cout << "test for construct variant using copy constructor failed" << std::endl;
        return false;
    }

    ECE141::Variant theV2(200);
    if (!(theV1 < theV2)){
        std::cout << "test for simple less than failed" << std::endl;
        return false;
    }

    ECE141::Variant theV3(200.0f);
    theV0 = theV3;
    if (!(theV0 == theV3)) {
        std::cout << "test for == float and int failed" << std::endl;
        return false;
    }
    if (!(theV1 < theV3)){
        std::cout << " < float and int failed" << std::endl;
        return false;
    }
    
    ECE141::Variant theV4("200");
    theV0 = theV4;
    
    std::optional<float> v4_float = theV4.asFloat();
    std::cout << "expected 200, actual: " <<v4_float.value()  << std::endl;
    
    if (!(theV4.asFloat() > 100.0f)) {
        std::cout << "test for convert string float to float failed and >" << std::endl;
        return false;
    }
    
    if (!(theV0 == theV4)) {
        std::cout << "test for == with integer of string type" << std::endl;
        return false;
    }
    
    if (!(theV1 < theV4)) {
        std::cout << " < comparing string of float type and int" << std::endl;
        return false;
    }
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

bool testSetterInt() {
    ECE141::Variant theV1(100);
    theV1 = 500;
    theV1 = 300;
    if(theV1.asInt() != 300)
        return false;
    return true;
}

bool testSetterNegativeInt() {
    ECE141::Variant theV1(100);
    theV1 = -500;
    theV1 = -300;
    if(theV1.asInt() != -300)
        return false;
    return true;
}

bool testSimpleNotEqual() {
    ECE141::Variant theV1(1);
    ECE141::Variant theV2(1);
    if(theV1 != theV2)
        return false;
    return true;
}

bool testSetterfloat() {
    ECE141::Variant theV1(100);
    theV1 = 3.14f;
    ECE141::Variant theV2(3.14f);

    if(theV1.asFloat() != theV2.asFloat())
        return false;
    return true;
}

bool testSetterNegativefloat() {
    ECE141::Variant theV1(100);
    theV1 = -500;
    ECE141::Variant theV2(-300.0f);
    if(theV1 != theV2)
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
    printTestMessage("compile", true);
    printTestMessage("values", doValueTests());
    printTestMessage("compare", doCompareTests());
    printTestMessage("testSetterInt", testSetterInt());
    printTestMessage("testSetterNegInt", testSetterNegativeInt());
    printTestMessage("testSetterPositiveFloat", testSetterfloat());
    printTestMessage("testSetterNegativeFloat", testSetterNegativefloat());
    printTestMessage("testSimpleNotEqual", testSimpleNotEqual());

    return 0;
}
