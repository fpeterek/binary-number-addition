#include <iostream>
#include <algorithm>
#include <functional>


bool readInput(std::string & in1, std::string & in2, const std::string & msg) {

    std::cout << msg << std::endl;
    std::cin >> in1 >> in2;

    const bool firstIsValid = in1.size() and in1.find_first_not_of("01") == std::string::npos;
    const bool secondIsValid = in2.size() and in2.find_first_not_of("01") == std::string::npos;

    return firstIsValid and secondIsValid;

}

void normalize(std::string & in1, std::string & in2) {

    const size_t num_size = std::max(in1.size(), in2.size());
    in1 = std::string(num_size - in1.size(), '0') + in1;
    in2 = std::string(num_size - in2.size(), '0') + in2;

}

int failure() {
    std::cout << "Nespravny vstup." << std::endl;
    return -1;
}

std::pair<char, bool> getResult(const char l, const char r, bool carry) {

    const int lval = l - '0';
    const int rval = r - '0';
    const int result = lval + rval + (int)carry;

    const char retChar = (result & 1) + '0';
    const char retCarry = result & 2;

    return std::pair<char, bool>(retChar, retCarry);

}

std::string addBits(const std::string & l, const std::string & r) {

    size_t index = r.size() - 1;

    std::string result;
    std::pair<char, bool> additionRes('0', false);
    bool carry = false;

    while (index != std::string::npos) {

        const char c1 = l[index];
        const char c2 = r[index];

        additionRes = getResult(c1, c2, carry);
        carry = additionRes.second;

        const std::string bitValue = std::string(1, additionRes.first);

        result = bitValue + result;

        --index;

    }

    return std::string(1, (int)carry + '0') + result;

}

std::string add(const std::string & l, const std::string & r) {

    std::string res = addBits(l, r);

    const size_t first1 = res.find("1");

    if (first1 != std::string::npos) {
        res = res.substr(first1);
    }

    if (first1 == std::string::npos or not res.size()) {
        res = "0";
    }

    return res;

}

int main(int argc, const char * argv[]) {
    
    std::string in1;
    std::string in2;

    bool inputIsValid = readInput(in1, in2, "Zadejte dve binarni cisla:");

    if (not inputIsValid) {
        return failure();
    }

    normalize(in1, in2);

    std::cout << "Soucet: " << add(in1, in2) << std::endl;

}