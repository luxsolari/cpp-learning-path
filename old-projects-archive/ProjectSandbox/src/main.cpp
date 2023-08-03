#include <iostream>
#include <chrono>
#include <bitset>

#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Logitude;

    bool operator<(const CityRecord& other) const
    {
        return Population < other.Population;
    }

    bool operator==(const CityRecord& other) const
    {
        return Name == other.Name;
    }
};

namespace std
{
    // providing template specialization for the std::hash class for hashing a cityRecord
    template<>
    struct hash<CityRecord>
    {
        size_t operator()(const CityRecord& key) const
        {
            // hashing the string name to return a unique hash value for our city record
            return hash<std::string>()(key.Name);
        }
    };
}

int main() {

    // Bit shifting << left and Bit shifting >> right
    // useful for performing fast multiplications and divisions by powers of 2.
    // << will "multiply" by factors of two, by shifting the bit patterns of a value n places to the left. any value on the leftmost side is dropped when shifted out.
    // >> will "divide" by factors of two, by shifting the bit patterns of a value n places to the right. any value on the rightmost side is dropped when shifted out.

    int a = 1;
    a = a << 1; // this will multiply a by 2^1 , effectively multiplying the value by 2.

    a = a >> 1; // this is the opposite operation, dividing by 2^1, effectively dividing the value by 2.


    // bitwise AND [&] operations (using bitwise and to check for states of "flags" in a bit pattern or masking out specific bit patterns).

    int someRandomNumb   = 42;
    int someRandomMask   = 32;

    int someRandomAndResult = someRandomNumb & someRandomMask;
    std::cout << "binary representation of someRandomNumb  (" << someRandomNumb << ")           : " << std::bitset<8>(someRandomNumb) << std::endl;
    std::cout << "binary representation of someRandomMask  (" << someRandomMask << ")           : " << std::bitset<8>(someRandomMask) << std::endl;
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "binary representation of bitwise AND with mask (" << someRandomMask << "): " << std::bitset<8>(someRandomAndResult) << std::endl;
    std::cout << "result is " << someRandomAndResult << ", meaning the 3rd most significant bit from the left is turned on.\n";

    std::cout << std::endl;

    int someOtherMask = 15;
    someRandomAndResult = someRandomNumb & someOtherMask;
    std::cout << "binary representation of someRandomNumb  (" << someRandomNumb << ")           : " << std::bitset<8>(someRandomNumb) << std::endl;
    std::cout << "binary representation of someOtherMask   (" << someOtherMask << ")           : " << std::bitset<8>(someOtherMask) << std::endl;
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "binary representation of bitwise AND with mask (" << someOtherMask << "): " << std::bitset<8>(someRandomAndResult) << std::endl;
    std::cout << "result is " << someRandomAndResult << ", \"isolating\" the least 4 significant digits of the value 42, showing their \"state\".\n";


    std::unordered_map<std::string, CityRecord> cityMap;
    cityMap["Melbourne"]    = CityRecord{ "Melbourne", 5000000, 2.4, 9.4 };
    cityMap["Paris"]        = CityRecord{ "Paris", 5000000, 2.4, 9.4 };
    cityMap["London"]       = CityRecord{ "London", 5000000, 2.4, 9.4 };
    cityMap["Buenos Aires"] = CityRecord{ "Buenos Aires", 5000000, 2.4, 9.4 }; 
    cityMap["New York"]     = CityRecord{ "New York", 5000000, 2.4, 9.4 };

    CityRecord& parisData = cityMap["Paris"];
    std::cout << "Paris found: " << parisData.Population << "\n";

    std::unordered_map<CityRecord, uint32_t> foundedMap;
    foundedMap[CityRecord{ "Melbourne", 192736812, 1, 1 }] = 1800; 

    std::map<CityRecord, uint32_t> foundedOrderedMap;
    foundedOrderedMap[CityRecord{ "Melbourne", 192736812, 1, 1 }] = 1800;
    foundedOrderedMap[CityRecord{ "Dick", 192736812, 1, 1 }];

    //foundedMap[CityRecord{ "Melbourne", 5000000, 2.4, 9.4 }] = 1850;
    /*foundedMap[CityRecord{ "Paris", 5000000, 2.4, 9.4 }] = 1851;
    foundedMap[CityRecord{ "London", 5000000, 2.4, 9.4 }] = 1852;
    foundedMap[CityRecord{ "Buenos Aires", 5000000, 2.4, 9.4 }] = 1853;
    foundedMap[CityRecord{ "New York", 5000000, 2.4, 9.4 }] = 1854;*/


    return 0;
}
