#include <iostream>
#include <vector>
#include <unordered_map>

#include "determinant.h"


/***
 *  A class to test the performance of
 *  various hash/map implementations
***/
class HashTest{

public:
    
    // Empty constructor
    HashTest();

    // Dimension of a determinant
    size_t ncmo_;

    // Number of elements for hash
    size_t hash_dim;

    // A function to generate source determinant
    std::vector<Determinant> initial_space();

    void umap_test(std::vector<Determinant>& space); 
};
