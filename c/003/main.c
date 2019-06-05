#include "3rdparty/json/ujdecode.h"

int main(int argc, char** argv)
{
    UJObject obj;
    void *state;
    const char input[] = "{\"name\": \"John Doe\", \"age\": 31, \"number\": 1337.37, \"address\": { \"city\": \"Uppsala\", \"population\": 9223372036854775807 } }";
    size_t cbInput = sizeof(input) - 1;

    const wchar_t *personKeys[] = { L"name", L"age", L"number", L"address"};
    UJObject oName, oAge, oNumber, oAddress;

    obj = UJDecode(input, cbInput, NULL, &state);

    if (UJObjectUnpack(obj, 4, "SNNO", personKeys, &oName, &oAge, &oNumber, &oAddress) == 4)
    {

        const wchar_t *addressKeys[] = { L"city", L"population" };
        UJObject oCity, oPopulation;

        const wchar_t *name = UJReadString(oName, NULL);
        int age = UJNumericInt(oAge);
        double number = UJNumericFloat(oNumber);

        wprintf(L"name:%ls, age:%ld, number:%lf", name, age, number);

        if (UJObjectUnpack(oAddress, 2, "SN", addressKeys, &oCity, &oPopulation) == 2)
        {
            const wchar_t *city;
            long long population;
            city = UJReadString(oCity, NULL);
            population = UJNumericLongLong(oPopulation);

            wprintf(L" city:%ls, population:%lld", city, population);
        }
    }

    UJFree(state);
}