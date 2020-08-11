#include "variable.h"

#include <algorithm>

using std::swap;

std::unique_ptr<Variable> Int::operator+(const Variable& other) const
{
    return other + *this;
}

std::unique_ptr<Variable> Int::operator+(const Int& other) const
{
    return std::make_unique<Int>(val + other.val);
}

std::unique_ptr<Variable> Int::operator+(const Double& other) const
{
    return std::make_unique<Double>(value() + other.value());
}

std::unique_ptr<Variable> Int::operator-(const Variable& other) const
{
    return other - *this;
}
std::unique_ptr<Variable> Int::operator-(const Int& other) const
{
    return std::make_unique<Int>(other.val - val);
}

std::unique_ptr<Variable> Int::operator-(const Double& other) const
{
    return std::make_unique<Double>(other.value() - value());
}

std::unique_ptr<Variable> Int::operator*(const Variable& other) const
{
    return other * *this;
}
std::unique_ptr<Variable> Int::operator*(const Int& other) const
{
    return std::make_unique<Int>(other.val * val);
}

std::unique_ptr<Variable> Int::operator*(const Double& other) const
{
    return std::make_unique<Double>(other.value() * value());
}

std::unique_ptr<Variable> Int::operator/(const Variable& other) const
{
    return other / *this;
}

std::unique_ptr<Variable> Int::operator/(const Int& other) const
{
    return std::make_unique<Int>(other.val / val);
}

std::unique_ptr<Variable> Int::operator/(const Double& other) const
{
    return std::make_unique<Double>(other.value() / value());
}

std::unique_ptr<Variable> Int::abs() const
{
    return std::make_unique<Int>(std::abs(val));
}


std::unique_ptr<Variable> Double::operator+(const Variable& other) const
{
    return other + *this;
}
std::unique_ptr<Variable> Double::operator+(const Int& other) const
{
    return std::make_unique<Double>(val + other.value());
}
std::unique_ptr<Variable> Double::operator+(const Double& other) const
{
    return std::make_unique<Double>(val + other.val);
}
std::unique_ptr<Variable> Double::operator-(const Variable& other) const
{
    return other - *this;
}
std::unique_ptr<Variable> Double::operator-(const Int& other) const
{
    return std::make_unique<Double>(other.value() - val);
}
std::unique_ptr<Variable> Double::operator-(const Double& other) const
{
    return std::make_unique<Double>(other.val - val);
}

std::unique_ptr<Variable> Double::operator*(const Variable& other) const
{
    return other * (*this);
}
std::unique_ptr<Variable> Double::operator*(const Int& other) const
{
    return std::make_unique<Double>(other.value() * val);
}
std::unique_ptr<Variable> Double::operator*(const Double& other) const
{
    return std::make_unique<Double>(other.val * val);
}

std::unique_ptr<Variable> Double::operator/(const Variable& other) const
{
    return other / (*this);
}
std::unique_ptr<Variable> Double::operator/(const Int& other) const
{
    return std::make_unique<Double>(other.value() / val);
}
std::unique_ptr<Variable> Double::operator/(const Double& other) const
{
    return std::make_unique<Double>(other.val / val);
}

std::unique_ptr<Variable> Double::abs() const
{
    return std::make_unique<Double>(std::abs(val));
}

struct VariableHash
{
    size_t operator()(const Variable * const p) const
    {
        return p->hash_self();
    }
};


struct VariableEqual
{
    bool operator()(const Variable * const p, const Variable * const q) const
    {
        return p->equal(*q);
    }
};

std::unique_ptr<Variable> f_sin(const Variable& x)
{
    return std::make_unique<Double>(sin(x.value()));
}

std::unique_ptr<Variable> f_cos(const Variable& x)
{
    return std::make_unique<Double>(cos(x.value()));
}

std::unique_ptr<Variable> f_tan(const Variable& x)
{
    return std::make_unique<Double>(tan(x.value()));
}

std::unique_ptr<Variable> f_abs(const Variable& x)
{
    return x.abs();
}

std::unique_ptr<Variable> f_gcd(const Variable& a, const Variable& b)
{
    int x = static_cast<int>(a.value()), y = static_cast<int>(b.value());
    while(y != 0)
    {
        x %= y;
        swap(x, y);
    }
    return std::make_unique<Int>(x);
}
