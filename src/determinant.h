#ifndef _bitset_determinant_h_
#define _bitset_determinant_h_

#include <unordered_map>
#include <bitset>
#include <vector>

/**
 * A class to store a Slater determinant using the STL bitset container.
 *
 * The determinant is represented by a pair of alpha/beta strings
 * that specify the occupation of each molecular orbital
 * (excluding frozen core and virtual orbitals).
 *
 * |Det> = |I>
 *
 * The strings are represented using one array of bits of size 2 x nmo,
 * and the following convention is used here:
 * true <-> 1
 * false <-> 0
 */
class Determinant{
public:
    using bit_t = std::bitset<256>;

    // Class Constructor and Destructor
    /// Construct an empty determinant
    Determinant();
    /// Construct the determinant from an occupation vector that
    /// specifies the alpha and beta strings.  occupation = [Ia,Ib]
    explicit Determinant(const std::vector<int>& occupation);
    /// Construct the determinant from an occupation vector that
    /// specifies the alpha and beta strings.  occupation = [Ia,Ib]
    explicit Determinant(const std::vector<bool>& occupation);
    /// Construct an excited determinant of a given reference
    /// Construct the determinant from two occupation vectors that
    /// specifies the alpha and beta strings.  occupation = [Ia,Ib]
    explicit Determinant(const std::vector<int>& occupation_a, const std::vector<int>& occupation_b);
    /// Construct a determinant from a bitset object
    explicit Determinant(const std::bitset<256>& bits);


    /// Equal operator
    bool operator==(const Determinant& lhs) const;
    /// Less than operator
    bool operator<(const Determinant& lhs) const;
    /// XOR operator
    Determinant operator^(const Determinant& lhs) const;

    /// Get a pointer to the bits
    const std::bitset<256>& bits() const;

    /// Return the value of an alpha bit
    bool get_alfa_bit(int n) const;
    /// Return the value of a beta bit
    bool get_beta_bit(int n) const;

    /// Set the value of an alpha bit
    void set_alfa_bit(int n, bool value);
    /// Set the value of a beta bit
    void set_beta_bit(int n, bool value);

    /// Get the alpha bits
    std::vector<bool> get_alfa_bits_vector_bool();
    /// Get the beta bits
    std::vector<bool> get_beta_bits_vector_bool();

    /// Return a vector of occupied alpha orbitals
    std::vector<int> get_alfa_occ();
    /// Return a vector of occupied beta orbitals
    std::vector<int> get_beta_occ();
    /// Return a vector of virtual alpha orbitals
    std::vector<int> get_alfa_vir();
    /// Return a vector of virtual beta orbitals
    std::vector<int> get_beta_vir();

    /// Print the Slater determinant
    void print() const;
    /// Save the Slater determinant as a string
    std::string str() const;

    // Object Data
    /// The occupation vector (does not include the frozen orbitals)
    bit_t bits_;

    // Static data
    /// Number of non-frozen molecular orbitals
    static int nmo_;

    struct Hash
    {
        std::size_t operator()(const Determinant& bs) const
        {
            return std::hash<bit_t>()(bs.bits_);
        }
    };
};

using det_vec = std::vector<Determinant>;
template <typename T = double> using det_hash = std::unordered_map<Determinant, T, Determinant::Hash>;
using det_hash_it = std::unordered_map<Determinant, double, Determinant::Hash>::iterator;


#endif // _bitset_determinant_h_
