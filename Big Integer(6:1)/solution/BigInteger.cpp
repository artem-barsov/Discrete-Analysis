#include "BigInteger.hpp"

BigInteger::BigInteger() : digits(1) { }

BigInteger::BigInteger(const BigInteger& other) {
    this->digits = other.digits;
}

BigInteger::BigInteger(std::string& val) : digits(val.length() / DIGIT_LEN + 1) {
    for (int i = 0, offs = DIGIT_LEN; (val.length()>=offs)&&(i < digits.size()); i++, offs += DIGIT_LEN) {
        digits[i] = atoi(val.c_str() + val.length()-offs);
        *(val.end()-offs) = '\0';
    }
    digits.back() = atoi(val.c_str());
    while ((digits.back() == 0) && (digits.size() > 1))
        digits.pop_back();
}

BigInteger& BigInteger::operator= (BigInteger&& other) {
    this->digits.swap(other.digits);
    return *this;
}

BigInteger& BigInteger::operator+= (const BigInteger& other) {
    if (this->digits.size() < other.digits.size())
        this->digits.resize(other.digits.size());
    bool k = 0;
    for (size_t i = 0; i < other.digits.size(); i++) {
        this->digits[i] += other.digits[i] + k;
        k = this->digits[i] >= BASE;
        if (k) this->digits[i] -= BASE;
    }
    if (k) {
        for (size_t i = other.digits.size(); ; i++) {
            if (i == this->digits.size()) {
                this->digits.push_back(k);
                break;
            }
            if (this->digits[i] < BASE - k) {
                this->digits[i] += k;
                break;
            }
            this->digits[i] = 0;
        }
    }
    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger& other) {
    if (this->digits.size() < other.digits.size()) throw "Error";
    bool k = 0;
    for (size_t i = 0; i < other.digits.size(); i++) {
        this->digits[i] -= other.digits[i] + k;
        k = this->digits[i] < 0;
        if (k) this->digits[i] += BASE;
    }
    if (k) {
        for (size_t i = other.digits.size(); i < this->digits.size(); i++) {
            if (this->digits[i] > 0) {
                this->digits[i] -= k;
                k = 0;
                break;
            }
            this->digits[i] = BASE - 1;
        }
    }
    if (k) throw "Error";
    while ((this->digits.size() > 1) && (this->digits.back() == 0)) {
        this->digits.pop_back();
    }
    return *this;
}

BigInteger& BigInteger::operator*= (const BigInteger& other) {
    if (other.digits.size() == 1)
        return *this *= other.digits[0];
    if (this->digits.size() == 1) {
        this->digits = (other * this->digits[0]).digits;
        return *this;
    }
    std::vector<int> res(this->digits.size() + other.digits.size());
    for (size_t i = 0; i < this->digits.size(); i++) {
        int k = 0;
        for (size_t j = 0; j < other.digits.size(); j++) {
            auto qurem = lldiv(this->digits[i]*1ll*other.digits[j] + res[i+j] + k, BASE);
            k = qurem.quot;
            res[i+j] = qurem.rem;
        }
        res[i + other.digits.size()] = k;
    }
    while ((res.size() > 1) && (res.back() == 0)) {
        res.pop_back();
    }
    this->digits.swap(res);
    return *this;
}

BigInteger& BigInteger::operator*= (const int other) {
    int k = 0;
    for (size_t i = 0; i < this->digits.size(); i++) {
        auto qurem = lldiv(this->digits[i]*1ll*other + k, BASE);
        this->digits[i] = qurem.rem;
        k = qurem.quot;
    }
    if (k) this->digits.push_back(k);
    while ((this->digits.size() > 1) && (this->digits.back() == 0)) {
        this->digits.pop_back();
    }
    return *this;
}

BigInteger& BigInteger::operator/= (BigInteger& other) {
    if (other.digits.size() == 1) {
        return *this /= other.digits[0];
    }
    *this *= BASE;
    other *= BASE;
	size_t u_size = this->digits.size();
	size_t v_size = other.digits.size();
    if (u_size < v_size) {
        this->digits = std::vector<int>(1);
        return *this;
    }
	std::vector<int> res(u_size - v_size + 1);
	int d = BASE / (other.digits.back() + 1);
    *this *= d;
    other *= d;
	if (this->digits.size() == u_size)
        this->digits.push_back(0);
	for (int j = u_size - v_size; j >= 0; --j) {
        auto qr = lldiv(this->digits[j+v_size]*1ull*BASE + this->digits[j+v_size-1], other.digits[v_size-1]);
        int q = qr.quot;
        int r = qr.rem;
		if (q == BASE || q*1ull*other.digits[v_size-2] > BASE*1ull*r + this->digits[j+v_size-2]) {
			--q;
            r += other.digits[v_size-1];
		}
		if (r < BASE && (q == BASE || q*1ull*other.digits[v_size-2] > BASE*1ull*r + this->digits[j+v_size-2])) {
			--q;
            r += other.digits[v_size-1];
		}
		BigInteger qv = other * q;
        bool k = 0;
        int u_to = j + v_size;
        int v_to = qv.digits.size()-1;
    	while (this->digits[u_to] == 0 && u_to > j)
    		--u_to;
    	while (qv.digits[v_to] == 0 && v_to > 0)
    		--v_to;
        if ((u_to - j) != v_to) {
            k = (u_to - j) < v_to;
        }
        else {
            if (!k) {
                for (; j < u_to; --u_to, --v_to) {
                    if (this->digits[u_to] != qv.digits[v_to]) {
                        k = this->digits[u_to] < qv.digits[v_to];
                        break;
                    }
                }
            }
            if (!k) k = this->digits[j] < qv.digits[0];
        }
        if (k) {
            --q;
            qv = other * q;
            k = 0;
        }
        for (int v_at = 0, u_at = j; v_at < qv.digits.size(); ++u_at, ++v_at) {
            this->digits[u_at] -= qv.digits[v_at] + k;
            k = this->digits[u_at] < 0;
            if (k) this->digits[u_at] += BASE;
        }
		res[j] = q;
	}
	while (res.size() > 1 && res.back() == 0) {
		res.pop_back();
	}
    this->digits.swap(res);
	return *this;
}

BigInteger& BigInteger::operator/= (const int other) {
    if (!other) throw "Error";
    int k = 0;
    for (int i = this->digits.size()-1; i >= 0; i--) {
        auto qurem = lldiv(this->digits[i] + k*1ull*BASE, other);
        this->digits[i] = qurem.quot;
        k = qurem.rem;
    }
    while ((this->digits.size() > 1) && (this->digits.back() == 0)) {
        this->digits.pop_back();
    }
    return *this;
}

BigInteger& BigInteger::operator^= (BigInteger& other) {
    if (other.digits.size() == 1) {
        return *this ^= other.digits[0];
    }
	BigInteger res;
    res.digits[0] = 1;
	while (other.digits.size() > 1 || other.digits[0]) {
		if (other.digits[0] & 1)
            res *= *this;
		*this *= *this;
		other /= 2;
	}
    this->digits.swap(res.digits);
	return *this;
}

BigInteger& BigInteger::operator^= (int other) {
    if (this->digits.size() == 1 && !this->digits[0] && !other)
        throw "Error";
    BigInteger res;
    res.digits[0] = 1;
	while (other) {
		if (other & 1)
            res *= *this;
		*this *= *this;
		other >>= 1;
	}
    this->digits.swap(res.digits);
	return *this;
}

BigInteger operator+ (BigInteger lhs, BigInteger& rhs) {
    return std::move(lhs += rhs);
}
BigInteger operator- (BigInteger lhs, BigInteger& rhs) {
    return std::move(lhs -= rhs);
}
BigInteger operator* (BigInteger lhs, BigInteger& rhs) {
    return std::move(lhs *= rhs);
}
BigInteger operator* (BigInteger lhs, int rhs) {
    return std::move(lhs *= rhs);
}
BigInteger operator* (int lhs, BigInteger rhs) {
    return std::move(rhs *= lhs);
}
BigInteger operator/ (BigInteger lhs, BigInteger& rhs) {
    return std::move(lhs /= rhs);
}
BigInteger operator/ (BigInteger lhs, int rhs) {
    return std::move(lhs /= rhs);
}
BigInteger operator^ (BigInteger lhs, BigInteger& rhs) {
    return std::move(lhs ^= rhs);
}
BigInteger operator^ (BigInteger lhs, int rhs) {
    return std::move(lhs ^= rhs);
}

std::ostream& operator<< (std::ostream& out, const BigInteger& bi) {
    for (int i = bi.digits.size()-1; i >= 0; i--) {
        if (i != bi.digits.size()-1) {
            out << std::setfill('0') << std::setw(bi.DIGIT_LEN);
        }
        out << bi.digits[i];
    }
    return out;
}

std::istream& operator>> (std::istream& in, BigInteger& bi) {
    std::string tmp;
    in >> tmp;
    bi = BigInteger(tmp);
    return in;
}

bool operator< (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return lhs.digits.size() < rhs.digits.size();
    }
    for (int i = lhs.digits.size()-1; i >= 0; i--) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return lhs.digits[i] < rhs.digits[i];
        }
    }
    return false;
}
bool operator> (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return lhs.digits.size() > rhs.digits.size();
    }
    for (int i = lhs.digits.size()-1; i >= 0; i--) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return lhs.digits[i] > rhs.digits[i];
        }
    }
    return false;
}
bool operator== (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.digits.size(); i++) {
        if (lhs.digits[i] != rhs.digits[i])
            return false;
    }
    return true;
}
