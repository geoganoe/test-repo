//
// Test code

// To build, use the command:  g++ -std=c++17 -o tstr tstr.cc

#include "fo-utils.h"
#include <iostream>

using namespace std;

str_utf8 plbck_strg;

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
    for ( int idx = 0; idx < 26; idx++ )
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
            plbck_strg.clear();
        }
        string tmpid = nde_id_str;
        tmpid += " [";
        plbck_strg.append( tmpid );
    }
    return 0;
}
