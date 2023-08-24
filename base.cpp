#include <iostream>
#include <unordered_map>

template <typename>
class Value;

enum EValueType
{
    EFloat32,
    EDouble,
    EInt64,
    EInt32,
    EInt8,
    EUInt64,
    EUInt32,
    EUInt8,
    EUnknown // At the last
};

std::unordered_map<EValueType, std::string> TYPE_INFO = {
    {EValueType::EFloat32, "float32"},
    {EValueType::EDouble, "double"},
    {EValueType::EInt64, "int64"},
    {EValueType::EInt32, "int32"},
    {EValueType::EInt8, "int8"},
    {EValueType::EUInt64, "uint64"},
    {EValueType::EUInt32, "int32"},
    {EValueType::EUInt8, "int8"},
    {EValueType::EUnknown, "Unknown"},

};

template <typename T>
struct TypeInfo
{

public:
    EValueType get_type() { return EValueType::EUnknown;};
    EValueType get_type() const { return EValueType::EUnknown;};
};

template<> EValueType TypeInfo<float>::get_type() { return EValueType::EFloat32;};
template<> EValueType TypeInfo<double>::get_type() { return EValueType::EDouble;};
template<> EValueType TypeInfo<int64_t>::get_type() { return EValueType::EInt64;};
template<> EValueType TypeInfo<int8_t>::get_type() { return EValueType::EInt8;};
template<> EValueType TypeInfo<int32_t>::get_type() { return EValueType::EInt32;};
template<> EValueType TypeInfo<uint64_t>::get_type() { return EValueType::EUInt64;};
template<> EValueType TypeInfo<uint8_t>::get_type() { return EValueType::EUInt8;};
template<> EValueType TypeInfo<uint32_t>::get_type() { return EValueType::EUInt32;};


template<> EValueType TypeInfo<float>::get_type() const { return EValueType::EFloat32;};
template<> EValueType TypeInfo<double>::get_type() const { return EValueType::EDouble;};
template<> EValueType TypeInfo<int64_t>::get_type() const { return EValueType::EInt64;};
template<> EValueType TypeInfo<int8_t>::get_type() const { return EValueType::EInt8;};
template<> EValueType TypeInfo<int32_t>::get_type() const { return EValueType::EInt32;};
template<> EValueType TypeInfo<uint64_t>::get_type() const { return EValueType::EUInt64;};
template<> EValueType TypeInfo<uint8_t>::get_type() const { return EValueType::EUInt8;};
template<> EValueType TypeInfo<uint32_t>::get_type() const { return EValueType::EUInt32;};


class Kernal
{
protected:
    Kernal(const std::string &name) : m_name(name)
    {
    }

public:
    std::string &op_type()
    {
        return m_name;
    }

private:
    std::string m_name;
};

template <typename T>
class Add : public Kernal
{
protected:
    Add() : Kernal("Add")
    {
    }

public:
    template <typename T2>
    auto operator+(const Value<T2> &other)
    {
        auto this_of_child = static_cast<Value<T> *>(this);
        auto data = this_of_child->get_data() + other.get_data();
        return Value(data);
    }
};

template <typename T>
class Mul : public Kernal
{
protected:
    Mul() : Kernal("Mul")
    {
    }

public:
    template <typename T2>
    auto operator*(const Value<T2> &other)
    {
        auto this_of_child = static_cast<Value<T> *>(this);
        auto data = this_of_child->get_data() * other.get_data();
        return Value(data);
    }
};

template <typename T>
class Sub : public Kernal
{

protected:
    Sub() : Kernal("Sub")
    {
    }

public:
    template <typename T2>
    auto operator-(const Value<T2> &other)
    {
        auto this_of_child = static_cast<Value<T> *>(this);
        auto data = this_of_child->get_data() - other.get_data();
        return Value(data);
    }
};

template <typename T>
class Value : public Sub<T>, public Add<T>, public Mul<T>, public TypeInfo<T>
{
private:
    T m_data;

public:
    Value(const T &data) : m_data(data)
    {
    }

    Value<T> &operator=(const Value<T> &other)
    {
        m_data = other.m_data;
        return *this;
    }

    Value<T> &operator=(Value<T> &other)
    {
        m_data = other.m_data;
        return *this;
    }

    const T &get_data()
    {
        return m_data;
    }

    const T &get_data() const
    {
        return m_data;
    }

    template <class T1>
    friend std::ostream &operator<<(std::ostream &os, const Value<T1> &);
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Value<T> &val)
{
    os << "Value <" << val.m_data << " ," << " dtype = " << TYPE_INFO[val.get_type()] << " >" << std::endl;;
    return os;
}

int main()
{
    Value<float> a(3.1);

    Value<u_int8_t> b(4);
    auto ret = a + b; // Copy Constructor
    std::cout << a << " + " << b << " = " << ret << std::endl;
    ret = a * b;
    std::cout << a << " * " << b << " = " << ret << std::endl;
    ret = a + b * b;
    std::cout << a << " + " << b << " * " << b << " = " << ret << std::endl;
}
