/*
 * File: Variant.hpp
 * Author: Jason Li
 * Created on: January 22nd, 2023
 * Description: Header file for a type-safe unio class that can hold integer, float, and string(char*).
 */
#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <optional>
#include <cstring>

namespace ECE141
{

    enum class VariantType { intType, floatType, stringType };

    class Variant
    {
    public:
        // ---Constructors---
        
        Variant(int aValue);
        Variant(float aValue);
        Variant(const char* aValue);
        
        
        Variant(const Variant & aCopy);
        Variant& operator=(const Variant & aCopy);
        
        ~Variant(){};
       
        Variant& operator=(int aValue);
        Variant& operator=(float aValue);
        Variant& operator=(const char* aValue);
        
        std::optional<int> asInt() const;            // Retrieve value as int
        std::optional<float> asFloat() const;        // Retrieve value as float
        std::string asString() const; // Retrieve value as string
        VariantType getType() const; // Get current type of variant
        
        std::optional<int> compare_var(Variant other_variant) const; //compare the current variant to another variant
        
        std::optional<bool> operator==(Variant aVar) const;
        std::optional<bool> operator!=(Variant aVar) const;
        std::optional<bool> operator<(Variant aVar) const;
        std::optional<bool> operator<=(Variant aVar) const;
        std::optional<bool> operator>(Variant aVar) const;
        std::optional<bool> operator>=(Variant aVar) const;
       
        
        

        friend std::ostream& operator<<(std::ostream& aStream, const Variant& aVariant);

    protected:
        // ---TODO: Add member variables---
        VariantType type;
        int intValue;
        float fValue;
        std::string cValue;

    };

} // namespace ECE141
