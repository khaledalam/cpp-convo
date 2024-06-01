/***






 khaled_cpp_165_2024_May_27: 



Create a C++ function called MaxGCD that takes a number of type int called num, where this num should be greater than 0.

This function should return another number of type int y (1 ≤ y < num) such that gcd(num, y) + y is maximum possible. Please make the code as short as possible.




*/

#include <iostream>
#include <stdexcept>
#include <string>

int MaxGCD(std::vector<std::vector<int>> grid) {
   
   
   vector<int> a(n);
    vector<int> b(n);
    for(int i = 0 ; i < n ; i++ ){
        cin >> c;
        a[i] = (signed)(c - '0');
    }
    for(int i = 0 ; i < n ; i++ ){
        cin >> c;
        b[i] = (signed)(c - '0');
    }
    vector<signed> path;
    path.push_back(a[0]);
 
    int k = 1;
    int res;
    int count = 1;
    while( k < n ){
        while( k < n && a[k] == b[k-1] ){
            count++;
            path.push_back(a[k]);
            k++;
        }
        
        if ( k == n ) {
            break;
            path.push_back(b[k - 1]);
            res = count;
        }
        else if ( a[k] == 0 ) {
            count = 1;
            path.push_back(a[k]);
            k++;
        }
        else { // a[k] == 1 && b[k-1] == 0
            for ( int i = k - 1; i < n ; i++ )
                path.push_back(b[i]);
            res = count;
            k = n;
        }
    }
    if ( k == n && path.size() == n) {
        path.push_back(b[k - 1]);
        res = count;
    }
    
 
    for(int idx = 0 ; idx < path.size() ; idx++)
        cout << path[idx];
    cout << endl;
    
    cout <<  res << endl;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxGCD(10) == 9);
    // TEST_END

    // TEST
    assert(MaxGCD(1) == 0);
    // TEST_END

    // TEST
    try {
        MaxGCD(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxGCD(-1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}