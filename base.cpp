#include <iostream>

template <typename T>
class Value {
    private:
    T m_data;
    public:
    Value(const T& data) : m_data(data) {
    }

    Value<T> operator+(Value<T> other) {
        m_data = m_data + other.m_data;
        return *this;
    }
    template <class T1>
    friend std::ostream& operator<<(std::ostream& os, const Value<T1>&);
};
template<typename T>
std::ostream &operator<<(std::ostream &os,const Value<T>& val)
{
    os << "Value <" << val.m_data << ">";
    return os;
}

int main() {
    Value a(3);

    Value b(4);
    auto ret = a + b;
    std::cout << a << " + " << b << " = " << ret <<std::endl;
}
