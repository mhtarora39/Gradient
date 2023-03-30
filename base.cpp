#include <iostream>


template <typename> class Value;

template <typename T>
class Kernels {
    public:
    Value<T> operator+(const Value<T>& other)
    {   
        auto this_of_child = static_cast<Value<T> *>(this);
        auto data = this_of_child->get_data() + other.get_data();
        return Value<T>(data);
    }

    Value<T> operator * (const Value<T>& other)
    {   
        auto this_of_child = static_cast<Value<T> *>(this);
        auto data = this_of_child->get_data() * other.get_data();
        return Value<T>(data);
    }

    const T& get_data() {
        return T(1);
    }
};

template <typename T>
class Value  : public Kernels <T> {
    private:
    T m_data;
    public:
    Value(const T& data) : m_data(data) {
    }

    Value<T>& operator = (const Value<T>& other) {
        m_data = other.m_data;
        return *this;
    }

    Value<T>& operator=(Value<T>& other) {
        m_data = other.m_data;
        return *this;    
    }

    const T& get_data() {
        return m_data;
    }

    const T& get_data() const {
        return m_data;
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
    Value<int> ret = a + b; // Copy Constructor
    std::cout << a << " + " << b << " = " << ret <<std::endl;
    ret = a*b;
    std::cout << a << " * " << b << " = " << ret <<std::endl;

}
