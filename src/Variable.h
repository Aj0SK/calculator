#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <cmath>

class Int;
class Double;

class Variable
{
public:
    Variable() { };
    virtual void print(std::ostream& where) const = 0;
    virtual bool equal(const Variable &) const = 0;
    virtual size_t hash_self() const = 0;
    virtual double value() const = 0;
    virtual ~Variable() = default;

    friend std::ostream& operator<<(std::ostream& str, const Variable& data)
    {
        data.print(str);
        return str;
    }

    struct Plus{};
    virtual std::unique_ptr<Variable> operator+(const Variable&) const
    {
        throw Plus{};
    }
    virtual std::unique_ptr<Variable> operator+(const Int& other) const = 0;
    virtual std::unique_ptr<Variable> operator+(const Double& other) const = 0;

    struct Minus{};
    virtual std::unique_ptr<Variable> operator-(const Variable&) const
    {
        throw Minus{};
    }
    virtual std::unique_ptr<Variable> operator-(const Int& other) const = 0;
    virtual std::unique_ptr<Variable> operator-(const Double& other) const = 0;

    struct Product{};
    virtual std::unique_ptr<Variable> operator*(const Variable&) const
    {
        throw Product{};
    }
    virtual std::unique_ptr<Variable> operator*(const Int& other) const = 0;
    virtual std::unique_ptr<Variable> operator*(const Double& other) const = 0;

    struct Division{};
    virtual std::unique_ptr<Variable> operator/(const Variable&) const
    {
        throw Division{};
    }
    virtual std::unique_ptr<Variable> operator/(const Int& other) const = 0;
    virtual std::unique_ptr<Variable> operator/(const Double& other) const = 0;
};
class Int : public Variable
{
private:
    int val;

public:
    Int(int x) : val(x) {};
    Int(const std::string& x) : val(stoi(x)) {};
    ~Int() {};

    double value() const override { return static_cast<double>(val); }

    void print(std::ostream& out) const override {out << std::to_string(val);};

    bool equal(const Variable& p) const override { return *this == dynamic_cast<const Int&>(p); }
    bool operator==(const Int& other) const { return other.val == this->val; }
    size_t hash_self() const override { return std::hash<double>{}(static_cast<double>(this->val)); }

    Int& operator=(Int other)
    {
        if(&other == this) return *this;
        std::swap(val, other.val);
        return *this;
    }

    std::unique_ptr<Variable> operator+(const Variable& other) const override
    {
        return other + *this;
    }
    std::unique_ptr<Variable> operator+(const Int& other) const override
    {
        return std::make_unique<Int>(val + other.val);
    }
    std::unique_ptr<Variable> operator+(const Double& other) const override;

    std::unique_ptr<Variable> operator-(const Variable& other) const override
    {
        return other - *this;
    }
    std::unique_ptr<Variable> operator-(const Int& other) const override
    {
        return std::make_unique<Int>(other.val - val);
    }
    std::unique_ptr<Variable> operator-(const Double& other) const override;

    std::unique_ptr<Variable> operator*(const Variable& other) const override
    {
        return other * *this;
    }
    std::unique_ptr<Variable> operator*(const Int& other) const override
    {
        return std::make_unique<Int>(other.val * val);
    }
    std::unique_ptr<Variable> operator*(const Double& other) const override;

    std::unique_ptr<Variable> operator/(const Variable& other) const override
    {
        return other / *this;
    }
    std::unique_ptr<Variable> operator/(const Int& other) const override
    {
        return std::make_unique<Int>(other.val / val);
    }
    std::unique_ptr<Variable> operator/(const Double& other) const override;
};
class Double : public Variable
{
private:
    double val;

public:
    Double(double x) : val(x) {};
    Double(const std::string& x) : val(stod(x)) {};
    ~Double() {};
    void print(std::ostream& out) const override {out << std::to_string(val);};

    double value() const override { return val; }

    bool equal(const Variable& p) const override { return *this == dynamic_cast<const Double &>(p); }
    bool operator==(const Double& other) const { return other.val == this->val;}
    size_t hash_self() const override { return std::hash<double>{}(this->val); }

    Double& operator=(Double other)
    {
        if(&other == this) return *this;
        std::swap(val, other.val);
        return *this;
    }

    std::unique_ptr<Variable> operator+(const Variable& other) const override
    {
        return other + *this;
    }
    std::unique_ptr<Variable> operator+(const Int& other) const override
    {
        return std::make_unique<Double>(val + other.value());
    }
    std::unique_ptr<Variable> operator+(const Double& other) const override
    {
        return std::make_unique<Double>(val + other.val);
    }
    std::unique_ptr<Variable> operator-(const Variable& other) const override
    {
        return other - *this;
    }
    std::unique_ptr<Variable> operator-(const Int& other) const override
    {
        return std::make_unique<Double>(other.value() - val);
    }
    std::unique_ptr<Variable> operator-(const Double& other) const override
    {
        return std::make_unique<Double>(other.val - val);
    }

    std::unique_ptr<Variable> operator*(const Variable& other) const override
    {
        return other * (*this);
    }
    std::unique_ptr<Variable> operator*(const Int& other) const override
    {
        return std::make_unique<Double>(other.value() * val);
    }
    std::unique_ptr<Variable> operator*(const Double& other) const override
    {
        return std::make_unique<Double>(other.val * val);
    }

    std::unique_ptr<Variable> operator/(const Variable& other) const override
    {
        return other / (*this);
    }
    std::unique_ptr<Variable> operator/(const Int& other) const override
    {
        return std::make_unique<Double>(other.value() / val);
    }
    std::unique_ptr<Variable> operator/(const Double& other) const override
    {
        return std::make_unique<Double>(other.val / val);
    }
};

inline std::unique_ptr<Variable> Int::operator+(const Double& other) const
{
    return std::make_unique<Double>(value() + other.value());
}

inline std::unique_ptr<Variable> Int::operator-(const Double& other) const
{
    return std::make_unique<Double>(other.value() - value());
}

inline std::unique_ptr<Variable> Int::operator*(const Double& other) const
{
    return std::make_unique<Double>(other.value() * value());
}

inline std::unique_ptr<Variable> Int::operator/(const Double& other) const
{
    return std::make_unique<Double>(other.value() / value());
}

inline std::unique_ptr<Variable> f_sin(const Variable& x)
{
    return std::make_unique<Double>(sin(x.value()));
}

inline std::unique_ptr<Variable> f_cos(const Variable& x)
{
    return std::make_unique<Double>(cos(x.value()));
}

inline std::unique_ptr<Variable> f_tan(const Variable& x)
{
    return std::make_unique<Double>(tan(x.value()));
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

#endif
