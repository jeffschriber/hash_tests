#include "determinant.h"

using namespace std;

#define ALFA(n) bits_[n]
#define BETA(n) bits_[nmo_ + n]


// Static members
int Determinant::nmo_;

Determinant::Determinant() {}

Determinant::Determinant(const std::vector<int>& occupation)
{
    for(int p = 0; p < 2 * nmo_; ++p) bits_[p] = occupation[p];
}

Determinant::Determinant(const std::vector<bool>& occupation)
{
    for(int p = 0; p < 2 * nmo_; ++p) bits_[p] = occupation[p];
}

Determinant::Determinant(const std::vector<int>& occupation_a,const std::vector<int>& occupation_b)
{
    nmo_ = occupation_a.size();

    for(int p = 0; p < nmo_; ++p){
        bits_[p] = occupation_a[p];
        bits_[p + nmo_] = occupation_b[p];
    }
}

Determinant::Determinant(const std::bitset<256>& bits )
{
    bits_ = bits;
}


bool Determinant::operator==(const Determinant& lhs) const
{
    return (bits_ == lhs.bits_);
}

bool Determinant::operator<(const Determinant& lhs) const
{
    for (int p = nmo_ - 1; p >= 0; --p){
        if ((bits_[p] == false) and (lhs.bits_[p] == true)) return true;
        if ((bits_[p] == true) and (lhs.bits_[p] == false)) return false;
    }
    return false;
}

Determinant Determinant::operator^(const Determinant& lhs) const
{
    Determinant ndet( bits_ ^ lhs.bits() );
    return ndet;
}

const std::bitset<256>& Determinant::bits() const {return bits_;}

bool Determinant::get_alfa_bit(int n) const {return bits_[n];}

bool Determinant::get_beta_bit(int n) const {return bits_[n + nmo_];}

void Determinant::set_alfa_bit(int n, bool value) {bits_[n] = value;}

void Determinant::set_beta_bit(int n, bool value) {bits_[n + nmo_] = value;}

std::vector<bool> Determinant::get_alfa_bits_vector_bool()
{
    std::vector<bool> result;
    for(int n = 0; n < nmo_;++n){
        result.push_back(bits_[n]);
    }
    return result;
}

std::vector<bool> Determinant::get_beta_bits_vector_bool()
{
    std::vector<bool> result;
    for(int n = 0; n < nmo_; ++n){
        result.push_back(bits_[nmo_ + n]);
    }
    return result;
}


std::vector<int> Determinant::get_alfa_occ()
{
    std::vector<int> occ;
    for (int p = 0; p < nmo_; ++p){
        if (bits_[p]) occ.push_back(p);
    }
    return occ;
}

std::vector<int> Determinant::get_beta_occ()
{
    std::vector<int> occ;
    for (int p = 0; p < nmo_; ++p){
        if (bits_[nmo_ + p]) occ.push_back(p);
    }
    return occ;
}

std::vector<int> Determinant::get_alfa_vir()
{
    std::vector<int> vir;
    for (int p = 0; p < nmo_; ++p){
        if (not bits_[p]) vir.push_back(p);
    }
    return vir;
}

std::vector<int> Determinant::get_beta_vir()
{
    std::vector<int> vir;
    for (int p = 0; p < nmo_; ++p){
        if (not bits_[nmo_ + p]) vir.push_back(p);
    }
    return vir;
}


/**
 * Print the determinant
 */
std::string Determinant::str() const
{
    std::string s;
    s += "|";

    for(int p = 0; p < nmo_; ++p){
        if (bits_[p] and bits_[nmo_ + p]){
            s += "2";
        }else if (bits_[p] and not bits_[nmo_ + p]){
            s += "+";
        }else if (not bits_[p] and bits_[nmo_ + p]){
            s += "-";
        }else{
            s += "0";
        }
    }
    s += ">";
    return s;
}

