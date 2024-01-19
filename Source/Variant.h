#pragma once
#include <iostream>
#include <optional>
#include <string>

namespace ECE141
{
    class Variant
    {
    public:
        // ---Constructors---
        Variant(int aValue);
        Variant(float aValue);
        Variant(const char* aValue);

        // ---TODO: Add other OCF methods---

        // ---TODO: Add variant methods---

        friend std::ostream& operator<<(std::ostream& aStream, const Variant& aVariant);

    protected:
        // ---TODO: Add member variables---

    };

} // namespace ECE141