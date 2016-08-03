#include <iostream>
#include <chrono>
#include "hashtest.h"

using namespace std;

HashTest::HashTest()
{
    ncmo_ = 20;
    hash_dim = 5e6;
    
    std::vector<Determinant> dets = initial_space();


    //Test the unordered map
    chrono::steady_clock::time_point umap_start = chrono::steady_clock::now();
    umap_test(dets);
    chrono::steady_clock::time_point umap_end = chrono::steady_clock::now();
    chrono::duration<double> umap_time = chrono::duration_cast<chrono::duration<double>>(umap_end-umap_start);
    cout << "\n  Unordered map took:  " << umap_time.count() << " s" << endl;  

}

void HashTest::umap_test(std::vector<Determinant>& space)
{
    cout << "\n  Timings for Unordered map" << endl;
    det_hash<size_t> umap; 

    // Test adding to map
    chrono::steady_clock::time_point add_start = chrono::steady_clock::now();

    for( size_t I = 0; I < hash_dim; ++I ){
        umap[ space[I] ] = I;
    }

    chrono::steady_clock::time_point add_end = chrono::steady_clock::now();
    chrono::duration<double> umap_time = chrono::duration_cast<chrono::duration<double>>(add_end-add_start);
    cout << "\n  Building took:  " << umap_time.count() << " s" << endl;  
    

    // Test finding determinants
    
    chrono::high_resolution_clock::time_point find_start = chrono::high_resolution_clock::now();

    for( size_t I = 0; I < hash_dim; I += 10 ){
        det_hash<size_t>::iterator it = umap.find( space[I] ); 
        int num = it->second;
    }

    chrono::high_resolution_clock::time_point find_end = chrono::high_resolution_clock::now();
    chrono::duration<double> find_time = chrono::duration_cast<chrono::duration<double>>(find_end-find_start);
    cout << "\n  Finding took:  " << find_time.count() << " s" << endl;  

    // Test iterating

    chrono::steady_clock::time_point it_start = chrono::steady_clock::now();

    int r;
    for( det_hash<size_t>::iterator it = umap.begin(), it_end = umap.end(); it != it_end; ++it){
        r ^= it->second;
    }


    chrono::steady_clock::time_point it_end = chrono::steady_clock::now();
    chrono::duration<double> it_time = chrono::duration_cast<chrono::duration<double>>(it_end-it_start);
    cout << "\n  Iterating took:  " << it_time.count() << " s" << endl;  

    // Test erasing elements
    chrono::steady_clock::time_point erase_start = chrono::steady_clock::now();


    for( size_t I = 0; I < hash_dim; I += 10 ){
        umap.erase(space[I]); 
    }

    chrono::steady_clock::time_point erase_end = chrono::steady_clock::now();
    chrono::duration<double> erase_time = chrono::duration_cast<chrono::duration<double>>(erase_end-erase_start);
    cout << "\n  Erase took:  " << erase_time.count() << " s" << endl;  

    // Test inserting elements
    det_hash<size_t> remainder;
    for( size_t I = 0; I < hash_dim; I += 10 ){
        remainder[space[I]] = I; 
    }
    chrono::steady_clock::time_point insert_start = chrono::steady_clock::now();
    
    umap.insert( remainder.begin(), remainder.end());

    chrono::steady_clock::time_point insert_end = chrono::steady_clock::now();
    chrono::duration<double> insert_time = chrono::duration_cast<chrono::duration<double>>(insert_end-insert_start);
    cout << "\n  Insert took:  " << insert_time.count() << " s" << endl;  
}

std::vector<Determinant> HashTest::initial_space()
{

    std::vector<Determinant> det_vector;

    std::vector<int> a_occ(ncmo_);
    std::vector<int> b_occ(ncmo_);
    int nel = static_cast<int>(ncmo_ * 0.5);

    for( int i = 0; i < nel; ++i ){
        a_occ[i] = 1;
        b_occ[i] = 1;
    }
    for( int i = nel; i < ncmo_; ++i ){
        a_occ[i] = 0;
        b_occ[i] = 0;
    }

    size_t ndet = 0;
    do{
        do{
            if( ndet > hash_dim) break;
            Determinant det(a_occ,b_occ);
            det_vector.push_back(det);
            ndet++;    
       }while(std::prev_permutation(b_occ.begin(),b_occ.end()) );
   }while(std::prev_permutation(a_occ.begin(), a_occ.end()) );
    
    return det_vector;
}
