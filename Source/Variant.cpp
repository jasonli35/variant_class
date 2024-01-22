#include "Variant.h"


namespace ECE141
{

Variant::Variant(const Variant & aCopy) {
    this->operator=(aCopy);
}

Variant& Variant::operator=(const Variant & aCopy){
    this->type = aCopy.type;
    this->intValue = aCopy.intValue;
    this->fValue = aCopy.fValue;
    this->cValue = aCopy.cValue;
    return *this;
}

//Variant::~Variant(){}

    Variant::Variant(int aValue) {
        operator=(aValue);
    }

    Variant::Variant(float aValue) {
        operator=(aValue);
        
    }

    Variant::Variant(const char* aValue) {
        operator=(aValue);
    }

    Variant& Variant::operator=(int aValue){
        type = VariantType::intType;
        intValue = aValue;
        return *this;
    }
    Variant& Variant::operator=(float aValue){
        type = VariantType::floatType;
        fValue = aValue;
        return *this;
    }
    Variant& Variant::operator=(const char* aValue){
        type = VariantType::stringType;
        cValue = aValue;
        return *this;
    }

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

//bool Variant::isComparable(Variant aVar) const{
//    if(!(this->getType() == VariantType::stringType) != !(aVar.getType() == VariantType::stringType)){
//        return false;
//    }
//    return true;
//}

//@precondition: the two variant is comparable
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



std::optional<bool> Variant::operator==(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return result == 0;
}

std::optional<bool> Variant::operator!=(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return !result;
}
std::optional<bool> Variant::operator<(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return result < 0;
}
std::optional<bool> Variant::operator<=(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return result <= 0;
}

std::optional<bool> Variant::operator>(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return result > 0;
}
std::optional<bool> Variant::operator>=(Variant aVar) const {
    std::optional<int> result = compare_var(aVar);
    if(result == std::nullopt) {
        return std::nullopt;
    }
    return result >= 0;
}

    std::ostream& operator<<(std::ostream& aStream, const Variant& aVariant) {
        const char *charString = aVariant.asString().c_str();
        aStream.write(charString,std::strlen(charString));
        return aStream;
    }
} // namespace ECE141
