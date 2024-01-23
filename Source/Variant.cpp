/*
 * File: Variant.cpp
 * Author: Jason Li
 * Created on: January 22nd, 2023
 * Description: This file implement a type-safe unio class that can hold integer, float, and string(char*).
 */

#include "Variant.h"

namespace ECE141
{

    /**
     * @brief Constructor for variant class
     * @param AValue   an integer
     */
    Variant::Variant(int aValue) {
        operator=(aValue);
    }

    /**
     * @brief Constructor for variant class
     * @param AValue   an float
     * Note: Overflow of aValue was not check. This function would let c++ to handle overflow internally
     */
    Variant::Variant(float aValue) {
        operator=(aValue);
    }

    /**
     * @brief Constructor for variant class
     * @param AValue   a string that you wish variant object would hold
     */
    Variant::Variant(const char* aValue) {
        operator=(aValue);
    }

    /**
     * @brief A copy constructor.
     *This function create a copy of an existing object.
     * @param aCopy a variant reference you wish to copy
     */
    Variant::Variant(const Variant & aCopy) {
        this->operator=(aCopy);
    }

    /**
     * @brief set the current variant object to the copy of an existing variant.
     *
     * @param aCopy an variant object you wish to copy from.
     * @return variant object that is an copy of aCopy.
     */
    Variant& Variant::operator=(const Variant & aCopy){
        this->type = aCopy.type;
        this->intValue = aCopy.intValue;
        this->fValue = aCopy.fValue;
        this->cValue = aCopy.cValue;
        return *this;
    }
    /**
     * @brief Setter function for integer.
     *
     * This function assign variant object to hold an new integer value.
     *
     * @param aValue integer value wish to hold.
     * @return an variant instance.

     * Note: Overflow of aValue was not check. This function would let c++ to handle overflow internally.
     */
    Variant& Variant::operator=(int aValue){
        type = VariantType::intType;
        intValue = aValue;
        return *this;
    }
    /**
     * @brief Setter function for float.
     * This function assign variant object to hold an new float value.
     * @param aValue float value wish to hold.
     * @return an variant instance.
     * Note: Overflow of aValue was not check. This function would let c++ to handle overflow internally.
     */
    Variant& Variant::operator=(float aValue){
        type = VariantType::floatType;
        fValue = aValue;
        return *this;
    }

    /**
     * @brief Setter function for string.
     * This function assign variant object to hold an new string value.
     * @param aValue string value of type (char*) wish to hold.
     * @return an variant instance.
     */
    Variant& Variant::operator=(const char* aValue){
        type = VariantType::stringType;
        cValue = aValue;
        return *this;
    }

    /**
    * @brief get the value of the current instance with optional integer data type.
    * This function would get the integer value of the current instance. If value that the instance cannot be represented with int, it would return nullopt
    * @return an integer value of the current instance.
     @return nullopt   if it is unable to convert to int. eg, for case "hello"
    */
    std::optional<int> Variant::asInt() const {
        switch (type) {
            case VariantType::intType:
                return intValue;
                break;
            case VariantType::floatType:
                return (int) fValue;
                break;
            
            default:
                try {
                    return std::stoi(cValue);
                } catch (const std::invalid_argument& e) {
                    return std::nullopt;
                } catch (const std::out_of_range& e) {
                    return std::nullopt;
                }
               
                break;
              }
    }

    /**
    * @brief get the value of the current instance with optional float data type .
     * This function would returnthe value of float data type of the current instance. If instance cannot be represented with float, it would return nullopt
     * @return an float value of the current instance.
     @return nullopt   if it is unable to convert to int. eg, for case "hello"
     */
    std::optional<float> Variant::asFloat() const {
        switch (type) {
            case VariantType::intType:
                return (std::optional<float>) intValue;
                break;
            case VariantType::floatType:
                return fValue;
                break;
            default:
                try {
                    return std::stof(cValue);
                    } catch (const std::invalid_argument& e) {
                        return std::nullopt;
                    } catch (const std::out_of_range& e) {
                        return std::nullopt;
                    }
                break;
            }
    }

    /**
     * @brief get the value of the current instance with optional string data type.
     * This function would return the value of the current instance with string data type. If instance cannot be represented with float, it would return nullopt
     * @return an string value of the current instance.
     */
    std::string Variant::asString() const {
        switch (type) {
            case VariantType::intType:
                return std::to_string(intValue);
                break;
            case VariantType::floatType:
                return std::to_string(fValue);
                break;
        
            default:
                return cValue;
                break;
            }
    }

    VariantType Variant::getType() const {
        return Variant::type;
    }

    /**
     * @brief compare two variant instance.
     * @param other_variant   another variant instance we wish to compare.
     * @return 0     if the value of two instance is the same.
     * @return <0   if the value is smaller than other_variant
     * @return >0   if the value is bigger than other_variant
     */
    std::optional<int> Variant::compare_var(Variant other_variant) const {
        if(this->getType() == VariantType::stringType && other_variant.getType() == VariantType::stringType) {
            return cValue.compare(other_variant.asString());
        }
        std::optional<float> a = this->asFloat();
        std::optional<float> b = other_variant.asFloat();
        if(a == std::nullopt || b == std::nullopt){
            return -90;
        }
        if(a < b) {
            return -1;
        }
        else if (a == b) {
            return 0;
        }
        else{
            return 1;
        }
    
    }

    /**
     * @brief compare if variant is equal.
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of two instance is the same.
     * @return false  if the value of two instance is not the same.
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator==(Variant aVar) const {
        std::optional<int> result = compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result == 0;
    }

    /**
     * @brief compare if variant is not equal.
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of two instance is not the same.
     * @return false  if the value of two instance is  the same.
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator!=(Variant aVar) const {
        std::optional<int> result =  compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result != 0;
    }
    /**
     * @brief implement < operant
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of instance is less than aVar
     * @return false     if the value of instance is not than aVar
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator<(Variant aVar) const {
        std::optional<int> result = compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result < 0;
    }

    /**
     * @brief implement <= operant
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of instance is less than or equal to aVar
     * @return false      if the value of instance is not less than or equal to aVar
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator<=(Variant aVar) const {
        std::optional<int> result = compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result <= 0;
    }

    /**
     * @brief implement > operant
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of instance is greater than aVar
     * @return false      if the value of instance is not greater than or equal to aVar
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator>(Variant aVar) const {
        std::optional<int> result = compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result > 0;
    }

    /**
     * @brief implement >= operant
     * @param other_variant   another variant instance we wish to compare.
     * @return true     if the value of instance is greater or equal to aVar
     * @return false      if the value of instance is not greater or equal to aVar
     * @return nullopt if it is uncomparable
     */
    std::optional<bool> Variant::operator>=(Variant aVar) const {
        std::optional<int> result = compare_var(aVar);
        if(result == std::nullopt) {
            return std::nullopt;
        }
        return result >= 0;
    }

    /**
     * @brief implement output stream
     * @param aStream   an output steam in std library
     * @param an variant instance we wish to print to standard out
     * @return aStream: output string
     */
    std::ostream& operator<<(std::ostream& aStream, const Variant& aVariant) {
        const char *charString = aVariant.asString().c_str();
        aStream.write(charString,std::strlen(charString));
        return aStream;
    }
} // namespace ECE141
