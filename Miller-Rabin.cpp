#include <iostream>
//#include <stdlib.h>
#include<math.h>

using namespace std;

typedef uint64_t u64;

/* 
Find the smallest pseudo-prime number greater than 2^15 + 2^(id mod 10). where id is your METU ID number.
Use the Miller-Rabin Test 3 times to prove that your number is a pseudo-prime.
*/


// The Miller Rabin algorithm
// returns 0 if the test is conclusive and we have "composite"
// returns 1 if the test is inconclusive and we have a (high) chance of primality.
bool MR(u64 n);
bool MillerRabin(u64 n,u64 iterations);

// power function that returns a^p where a,p are positive integers
u64 powmod(u64 a, u64 p) {
    u64 res = 1;
    while (p) {
        if (p & 1 == 1)
            res = a * res ;
        a = a * a ;
        p >>= 1;
    }
    return res;
}


// power function that returns a^p mod n where a,p,n are positive integers
u64 powmod(u64 a, u64 p, u64 n) {
    u64 res = 1;
    while (p) {
        if (p & 1 == 1)
            res = a * res % n;
        a = a * a % n;
        p >>= 1;
    }
    return res;
}



int main()
{

	unsigned my_ID = 1046663;
	u64 spp = powmod(2,15) + powmod(2, my_ID %10)+1;
	while (!MillerRabin(spp,3)){
		spp+=2;
	}
	cout<< "Smallest pseudo-prime number bigger than 2^15 + 2^3 = "<<  powmod(2,15) + powmod(2, my_ID %10) <<" is " << spp <<endl;

    return 0;
}



bool MillerRabin(u64 n,u64 iterations){
	bool prime = true;
	for(u64 i=0; i<iterations ; i++)
		prime = MR(n);
	return prime ;
	
}

bool MR(u64 n){
	if (n<2) return false;
	if (n==2) return true;
	if (n%2 == 0) return false;
	// at this point n>=3 and odd

	// Miller Rabin Step 1
	// The following block decomposes n-1 = 2^k * q
	u64 k=0;
	u64 m = n - 1;
	while (m>0 && (m %2 ==0) ){
				m = m >> 1;
				k++;
	}
	u64 q = m;
	//cout << "k="<<k << "," << "q=" << q << endl;
	//cout << n-1 << "= 2^"<<k<< "*" <<q <<endl;
	// n-1 = 2^k * q
	
	
		// Miller Rabin Step 2
		// selecting a random integer a so that 1 < a < n-1 equivalent to 2 <= a <= n-2
		u64 a = 2 + rand() % (n-4);
		
		//cout<< "a=" << a <<endl;
		//cout<< "n=" << n <<endl;	
		// Miller Rabin Step 3
		//cout << "a^q mod n=" << powmod(a,q) << endl;
		if ( ( powmod(a,q,n) ) == 1){
			return true;//inconclusive
		}
		
		// Miller Rabin Step 4
		for (u64 j=0; j<k ; j++){
			// Miller Rabin Step 5
			u64 test_pow = powmod(2,j) * q % n;
			u64 test_num = powmod(a,test_pow,n);
			//cout<< "j="<<j<<" test_num ="<<test_num << endl;
			if (test_num % n == n-1 ){
				return true;//inconclusive
			}
	
		}

	// Miller Rabin Step 6
	
		
	return false;
}
