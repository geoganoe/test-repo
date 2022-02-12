//
// Test code

// To build, use the command:  g++ -std=c++17 -o tstr tstr.cc

#include "fo-utils.h"
#include <iostream>

using namespace std;

string nde_id_str = " new ";
ostringstream bsvistrm;
ostream& dbgs = cout;
ostream& errs = cout;
extern str_utf8 plbck_strg;


int main(int argc, char* argv[])
{
    uint16_t inf_wid = 120;
    string tst_strng;
    string tst_strn2;
    cout << "The capacity of tst_strng is " << tst_strng.capacity() << endl;
    cout << "The capacity of tst_strn2 is " << tst_strn2.capacity() << endl;
    tst_strn2 = "The quick brown fox jumped over the lazy dog's back.";
    cout << "The string tst_strn2 is [" << tst_strn2 <<
      "] and capacity of tst_strn2 is " <<
      tst_strn2.capacity() << endl;
    cout << "The plbck_strg is " <<
      ( plbck_strg.is_setup ? "setup" : "not setup" ) <<
      " and the default constr flag is " <<
      ( plbck_strg.is_nm_str ? "set" : "not set" ) <<
      " with numchr = " << plbck_strg.numchr << ", numsym = " <<
      plbck_strg.numsym << ", maxpos = " << plbck_strg.maxpos <<
      ", and vec_idx = " << plbck_strg.vec_idx << endl;
    plbck_strg.init_str( nde_id_str );
    for ( uint16_t idx = 0; idx < 3; idx++ )
    {
        tst_strng.push_back( static_cast<char>( 'A' + idx ) );
        tst_strng.push_back( static_cast<char>( 'a' + idx ) );
        cout << "The string tst_strng is [" << tst_strng <<
          "] and has capacity = " << tst_strng.capacity() << endl;
        if ( idx * 3 < tst_strn2.size() - 3 )
        {
            tst_strn2.append( tst_strn2.substr( idx * 3, 3 ) );
            cout << "The string tst_strn2 is [" << tst_strn2 <<
              "] and capacity of tst_strn2 is " <<
              tst_strn2.capacity() << endl;
        }
        str_utf8 tst_apnd( tst_strng );
        const str_utf8& disp_nm = tst_apnd;
        uint16_t col_num = plbck_strg.numsym;
        if ( col_num > 1 ) col_num += disp_nm.numsym + nde_id_str.size() + 3;
        if ( col_num > inf_wid )
        {
            cout << plbck_strg.target << endl;
            plbck_strg.clear();
        }
        string tmpid = to_string( idx );
        tmpid.insert( 0, 4 - tmpid.size(), ' ' );
        tmpid += " [";
        plbck_strg.append( tmpid );
        plbck_strg.append( disp_nm );
        plbck_strg.append( "]" );
        cout << "plbck_strg target is \"" << plbck_strg.target << "\"." << endl;
    }
    return 0;
}
