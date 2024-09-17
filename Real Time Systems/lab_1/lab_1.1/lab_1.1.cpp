#include <iostream>

int main() {
    std::string s = "01234";
    for (unsigned int i = s.size() - 1; i >= 0; i--)
    {
        std::cout << "i = " << i;
        std::cout << " s = " << s[i] << std::endl;
    }

}