//
// This provides the declaration for the file organizer string handling
//   classes that are needed for handling the folder and file name
//   strings.  These strings can potentially be made from a number of
//   string encoding types, or even no formal encoding at all given the
//   rules for naming files in some file systems.
//
// The objective of the string handling classes is to accept any string
//   that has been found in the target file system types and determine
//   the encoding type and save it in the null terminated name string
//   table in a way that the original string can be recovered when
//   needed.  The string pointer table record associated with the
//   string will provide the information needed to assist in assuring
//   the capability exists and can be implemented.
//

#ifndef FO_UTILS_H
#define FO_UTILS_H

#include "fo-common.h"
//  #include <string>   in common
//  #include <iostream>
#include <cstdint>
#include <vector>

// not needed - is in common - using namespace std;

//
// Define the constants needed
const char esc = 0x1b;
const char us = 0x1f;
const char del = 0x7f;
const int scc_size_ascii = 39;
const int scc_size_utf_16 = 11;
const int scc_size_secondary = 37;
const int ssiz_max = 1023;  // Max size for a string used as a name string

struct significant_collation_chars
{
    //
    // GGG - Make a static array of strings to represent the characters needed
    //   for the base_search_string use in these two arrays and then use the
    //   indexes into the array to define the srchstr_node_add[] array (see
    //   below
    //
    // Characters are entered here in their ducet collation order ( see
    //   Unicode Collation Algorithm -
    //     https://unicode.org/reports/tr10/#Notation_Str
    //   and the Default Unicode Collation Element Table -
    //     http://www.unicode.org/Public/UCA/13.0.0/allkeys.txt
    //   ) and include a characteristic non-inclusive set which can be used
    //   as characters in the base_search_str of the file organizer
    //   application.
    //
    // This list based on the Ducet allkeys-13.0.0.txt listing from
    //   2020-01-28, which has been updated.
    // When I am ready, I will update this section to reflect the changes
    //   that are in the allkeys-14.0.0.txt listing from 2021-07-10.
    //
    // Some key code points   Primary Collating weight
    //                        Hexadecimal  Decimal
    //   u0001                 = 0         = 0
    //   u0021exclam           = 0x0267*1  = 615
    //   u0024dollar           = 0x1f64    = 8036
    //   u030_0                = 0x1f98    = 8088
    //   u0041_A               = 0x1fa2    = 8098
    //   u005a_Z               = 0x2286    = 8838
    //   u394delta             = 0x2322    = 8994
    //   u3c0_pi               = 0x2334    = 9012
    //   u416_ZHE              = 0x23c7    = 9159
    //   ue01_thai_ko_kai      = 0x3217    = 12823
    //   ue40_thai_sara        = 0x3251    = 12881
    //   ue45_thai_LAKKHANGYAO = 0x3256    = 12886
    //   ufffd                 = 0xfffd    = 65533
    //

    //
    //  scc_set array members (see below) *↓
    //  Some key code points               Primary
    //                            code   Collating
    //    description             point     weight
    //  ───────────────────── ──────────── ───────
    //  Unit separator cntrl  ^_ = U+001f  * .0000
    //  Dollar sign            $ = U+0024  * .1f64
    //  Latin digit zero       0 = U+0030  * .1f98
    //  Latin digit one        1 = U+0031  * .1f99
    //  Latin digit two        2 = U+0032  * .1f9a
    //  Latin digit three      3 = U+0033  * .1f9b
    //  Latin digit four       4 = U+0034  * .1f9c
    //  Thai digit Four        ๔ = U+0e54    .1f9c
    //  Latin digit five       5 = U+0035  * .1f9d
    //  Latin digit six        6 = U+0036  * .1f9e
    //  Latin digit seven      7 = U+0037  * .1f9f
    //  Latin digit eight      8 = U+0038  * .1fa0
    //  Latin digit nine       9 = U+0039  * .1fa1
    //
    //  Latin small letter a  'a' = U+0061 * .1fa2
    //  Latin small letter b  'b' = U+0062 * .1fbc
    //  Latin small letter c  'c' = U+0063 * .1fd6
    //  Latin small letter d  'd' = U+0064 * .1feb
    //  Latin small letter e  'e' = U+0065 * .2007
    //  Latin small letter f  'f' = U+0066 * .2042
    //  Latin small letter g  'g' = U+0067 * .2051
    //  Latin small letter h  'h' = U+0068 * .2075
    //  Latin small letter i  'i' = U+0069 * .2090
    //  Latin small letter j  'j' = U+006a * .20ab
    //  Latin small letter k  'k' = U+006b * .20c4
    //  Latin small letter l  'l' = U+006c * .20d6
    //  Latin small letter m  'm' = U+006d * .2109
    //  Latin small letter n  'n' = U+006e * .2118
    //  Latin small letter o  'o' = U+006f * .213c
    //  Latin small letter p  'p' = U+0070 * .216b
    //  Latin small letter q  'q' = U+0071 * .2180
    //  Latin small letter r  'r' = U+0072 * .2193
    //  Latin small letter s  's' = U+0073 * .21d2
    //  Latin small letter t  't' = U+0074 * .21f7
    //  Latin small letter u  'u' = U+0075 * .2217
    //  Latin small letter v  'v' = U+0076 * .2242
    //  Latin small letter w  'w' = U+0077 * .2259
    //  Latin small letter x  'x' = U+0078 * .2264
    //  Latin small letter y  'y' = U+0079 * .2270
    //  Latin small letter z  'z' = U+007a * .2286
    //
    //  greek letter delta      Δ = U+0394   .2322
    //  greek small delta       δ = U+03b4 * .2322
    //  greek small theta       θ = U+03b8   .232a
    //  micro symbol or mu      µ = U+00b5 * .2330
    //  greek small pi          π = U+03c0 * .2334
    //  greek small tau         τ = U+03c4   .2340
    //  greek small phi         φ = U+03c6   .2342
    //  greek small omega       ω = U+03c9 * .2346
    //  Cyrillic Cap Ltr Zhe    Ж = U+0416 * .23c7
    //  Georgian letter Ghan    ღ = U+10e6 * .25d1
    //  Tawellemet letter Yaz   ⵤ = U+2D64 * .280F
    //  Ethiopic syllabl Za     ዘ = U+12d8   .28f1 Double width letter ?
    //  Thai Char Ko Kai        ก = U+0e01 * .3217
    //  Thai Char So Sala       ศ = U+0e28   .323e
    //  Thai Char Nokhuk        ฮ = U+0e2e   .3244
    //  Thai Char Paiyannoi     ฯ = U+0e2f   .3245
    //  Thai vowel Sara E       เ = U+0e40   .3251
    //  Thai vowel Lakkhangyao  ๅ = U+0e45   .3256
    //  Batak letter A         ᯀ = U+1bc0   .3508 Double width letter
    //  Cherokee letter Lo      Ꮆ = U+13b6   .38f4
    //  Canadian Sylbc Si       ᓯ = U+14ef * .3a46
    //  Canadian Sylbc Tha     ᕦ = U+1566   .3abd Double width letter
    //  Runic Letter dagaz dg d ᛞ = U+16de   .3c53
    //  Hiragana Ltr Small Ka  ゕ = U+3095   .42e0 Double width letter
    //  Lisu letter Cha         ꓛ = U+a4db * .48ff
    //  Kangxi Radical Life    ⽣ = U+2f63   .fb40 Double width letter
    //  Circled Ideogrph Eight ㊇ = U+3287   .fb40 .d16b Double width letter
    //
    char ascii_set[ scc_size_ascii ] {
       0x01,  us, '$', '0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    uint16_t utf_16_set[ scc_size_utf_16 ] {
        //  δ ,     µ ,     π ,     ω ,
        0x03b4, 0x00b5, 0x03c0, 0x03c9,
        //  Ж ,     ღ ,     ⵤ ,     ก ,
        0x0416, 0x10e6, 0x2D64, 0x0e01,
        //  ᓯ ,     ꓛ ,     �
        0x14ef, 0xa4db, 0xfffd };
    char ascii_secondary[ scc_size_secondary ] {
        0x09, 0x0a, 0x0b, 0x0c, 0x0d,  ' ',  '_',  '-',  ',',  ';',
         ':',  '!',  '?',  '.', '\'',  '"',  '(',  ')',  '[',  ']',
         '{',  '}',  '@',  '*',  '/', '\\',  '&',  '#',  '%',  '`',
         '^',  '+',  '<',  '=',  '>',  '|',  '~' };
};

struct styp_flags
{
    uint16_t ASCII_7 : 1;
    uint16_t UTF_8_orig : 1;
    uint16_t UTF_8_compat : 1;
    uint16_t ISO_8859_1 : 1;
    uint16_t UCS_2 : 1;
    uint16_t UTF_16 : 1;
    // This flag name is changed to spare since its function is moving
    //   to the base class gbtree, so any use of the original name will
    //   produce a compile error.
    uint16_t spare_styp_flag : 2;
    // GGG - Note that the following index has a max value of 255
    uint16_t srchstr_first_ch_idx : 8;
};

struct fit_opts {
    //
    // This struct is primarily aimed as a set of instructions for
    //   methods used by the str_utf8 struct defined below
    //
    // Just cut off the string when maxpos is reached, set the values
    //   for numchr and numsym, and ignore any other instructions
    uint16_t plain : 1;
    //
    // Space pad and centering will fill in spaces for any string
    //   shorter than the requested maxpos with space pad just
    //   padding to the end, and centering positioning the string
    //   in the middle of the field.
    uint16_t space_pad : 1;
    uint16_t centering : 1;
    //
    // The next three flags are mutually exclusive, and if more than
    //   one is set true, only the first true will be active
    uint16_t end_trim : 1;  // If string longer than maxpos show ellipses
    uint16_t show_ends : 1; // Show both ends separated by ellipses
    uint16_t balance : 1;   // Show both ends balanced sep by ellipses
    //
    // Maybe implement this to intelligently pick the place for the
    //   ellipses by looking for the dot preceeding the extension and
    //   putting the ellipses a couple of symbols before it.
    //    uint16_t smart_ends : 1;
    //
    // If set, any trailing white space in the string will be removed
    uint16_t trim_trl_wht_space : 1;
};

fit_opts operator|( const fit_opts lft, const fit_opts rt );

//
// Some commonly needed fit_opts consts
const fit_opts fit_plain { 1, 0, 0, 0, 0, 0, 0 };
const fit_opts fit_sp_pad { 0, 1, 0, 0, 0, 0, 0 };
const fit_opts fit_center { 0, 0, 1, 0, 0, 0, 0 };
const fit_opts fit_trim_end { 0, 0, 0, 1, 0, 0, 0 };
const fit_opts fit_ends { 0, 0, 0, 0, 1, 0, 0 };
const fit_opts fit_balance { 0, 0, 0, 0, 0, 1, 0 };
const fit_opts fit_wht_trim { 0, 0, 0, 0, 0, 0, 1 };

const int bar27 = 0x08000000;
// const int max_nmst_id = 0x07fffbff;
const int bar23 = 0x0800000;
const int max_nmst_id = 0x07ffbff;  // 8,388,608
const uint16_t num_max = 1020;

typedef vector<uint16_t> index_vec;
extern vector<index_vec> ivs;
//
// struct for finding target UTF-8 string that will fit in maxpos columns
//   and for keeping track of the number of symbols in the string
struct str_utf8 {
    uint64_t numchr : 10;  // No. of char. bytes in the target str. (<1020)
    uint64_t numsym : 10;  // No. of symbol cols. req. to output str. (<1020)
    uint64_t maxpos : 10;  // Max. no. of symbol cols. allowed for str. (<1020)
    uint64_t is_setup : 1;
    uint64_t is_nm_str : 1;
    uint64_t vec_idx : 9; // Index for the symbol to char correspondence vector
    uint64_t nmst_id : 23; // Name string record ID no. (2^23-1 = new)
    //
    // Need name string id so -- see above --
    // uint16_t numchr;  // Number of character bytes in the target string
    // uint16_t numsym;  // Number of symbol columns required to output the string
    // uint16_t maxpos;  // Maximum number of symbol columns allowed for string
    // uint16_t vec_idx; // Index for the symbol to char correspondence vector
    string target;

    str_utf8();
    str_utf8( string dflt, uint16_t maxp,
      fit_opts style = fit_plain, bool dbg_out = true );
    str_utf8( string dflt, fit_opts style = fit_plain, bool dbg_out = true );
    ~str_utf8();
    void init_str( string dflt, fit_opts style = fit_plain,
      bool dbg_out = true );
    void fit_to_max_cols( fit_opts style, bool dbg_out = true );
    inline void fit_to_max_cols( bool dbg_out = true )
    {
        fit_to_max_cols( fit_plain, dbg_out );
    }
    inline void fit_to_max_cols( uint16_t maxp, fit_opts style,
      bool dbg_out = true )
    {
        maxpos = maxp;
        fit_to_max_cols( style, dbg_out );
    }
    // This is what I want, but it won't work.  I need to figure
    //   it out when I get a chance -- const inline index_vec& get_idxvec()
    //     { return get_index_vec(); } which unfortunately can change
    //   the index_vec if it isn't already set up and that violates the
    //   const guarantee, so the method now works without fixing
    //   uninitialized vectors, but will exit the program if found.
    const index_vec& get_idxvec();
    void append( const string& s );
    void append( const str_utf8& us, uint16_t sym_pos = 0,
      uint16_t sym_nm = num_max );
    void clear();

private:
    void setup_index_vec();
    index_vec& get_index_vec();
};

#if defined (INFOdisplay) || defined (USEncurses)

uint16_t find_safe_break( string subj_str, int min_sym, int max_sym,
  bool dbg_out = true );

#endif  //  defined (INFOdisplay) || defined (USEncurses)

//
// This set consists of the combined values defined in scc
//   the significant_collation_chars struct, and is initialized from that
//   struct by the class file_org_str_ptr_tbl_type constructor.  The
//   scc_set[] array is used to create the srchstr_node_add[] character
//      ( GGG - Some changes will be needed here as the array count is held
//        by the base class, so the array can hold 6 symbol index values )
//   array values which give the capability to have up to ?5? strings even
//   if some of them actually need more than one byte of space.  The first
//   element of the char array has to be the number of elements used and
//   the rest can be indexes into scc_set[].
const int scc_set_size = scc_size_ascii + scc_size_utf_16;
extern uint16_t scc_set[ scc_set_size ];

//
// GGG - Not used so commented out to lower object size
//  int16_t u_fractions[ 24 ] {
//      // ¼      ½       ¾       ↉       ₀       ⁰       ₁       ¹
//      0x00bc, 0x00bd, 0x00be, 0x2189, 0x2080, 0x2070, 0x2081, 0x00b9,
//      // ⅐      ⅑       ⅒       ⅓       ⅔       ⅕       ⅖       ⅗
//      0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157,
//      // ⅘      ⅙       ⅚       ⅛       ⅜       ⅝       ⅞       ⅟
//      0x2158, 0x2159, 0x215a, 0x215b, 0x215c, 0x215d, 0x215e, 0x215f };

//
// This array of strings is a ducet compatible in order list of the strings
//   evenly spaced over the file of unique sorted name strings from a recent
//   backup USB drive of the Dell 5520 Precision laptop computer.
//
//  0 'control character us'
//  1 749c    rlll4
//  2 arrayp  rll3
//  3 buildj  rllr4
//  4 constan rl2
//  5 dlmal   rlrl4
//  6 extras  rlr3
//  7 gsreu   rlrr4
//  8 iswc    r1
//  9 mainpb  rrll4
// 10 ocla    rrl3
// 11 printg  rrlr4
// 12 sam4cmp rr2
// 13 sockett rrrl4
// 14 testcq  rrr3
// 15 undem   rrrr4
// 16 zzzzz
//
// and a 33 element version for enabling a 5 level pre-computed
//   base search string implementation
//
//  0 'control character us'
//  1 26e28b  rllll5
//  2 749c    rlll4
//  3 adjacf  rlllr5
//  4 arrayp  rll3
//  5 bad01u  rllrl5
//  6 buildj  rllr4
//  7 classbp rllrr5
//  8 constan rl2
//  9 db25ma  rlrll5
// 10 dlmall  rlrl4
// 11 ecaa23  rlrlr5
// 12 extras  rlr3
// 13 fsuite  rlrrl5
// 14 gsreu   rlrr4
// 15 igamma  rlrrr5
// 16 isvoie  r1
// 17 lfcubi  rrlll5
// 18 mainpb  rrll4
// 19 msp430  rrllr5
// 20 oclcpp  rrl3
// 21 physicb rrlrl5
// 22 printg  rrlr4
// 23 reg908  rrlrr5
// 24 sam4cmp rr2
// 25 segmen  rrrll5
// 26 sockett rrrl4
// 27 strpya  rrrlr5
// 28 testcr  rrr3
// 29 tommw3  rrrrl5
// 30 underm  rrrr4
// 31 wavets  rrrrr5
// 32 zzzzz
//
// The base_search_str has been pre-computed for levels 1 to 5 based on the
//   expected distribution of strings to be processed, and are stored in the
//   array ggguniq_str_bal_list of strings.
const int ggg_bal_lst_siz = 33;
extern string ggguniq_str_bal_list[ ggg_bal_lst_siz ];
extern significant_collation_chars scc;
extern string scc_idx_to_str_bal[ ggg_bal_lst_siz ];
extern uint16_t scc_set[ scc_set_size ];
extern string my_exit_msg;

bool validate_iso8859_1char( uint16_t ch );

styp_flags identify_encoding( string ch_seq, styp_flags dflt_flg );

string utf8from8859_1( string iso8859_1 );

//
// The UTF-8 string is required to be ISO_8859_1 compatible or this
//   function will cause a program exit with error.  I. E. - Only use this
//   function on ISO_8859_1 validated strings that were converted to UTF-8
string iso8859_1from_utf8( string uft8strng );

// Define a character mask
const uint16_t cmask = 0x00ff;

string scc_set_array_to_utf8( string scc_strng );

string scc_idx_to_UTF_8( char indx );

string trans_scc( string scc_strng );

int find_scc_ascii_index( char scc_ch );

void myexit();

#ifdef INdevel    // Declarations for development only
void getout( string intro, int contprmt = 1 );

// Miscellaneous functions

void display_scc_and_strbal( bool enable = false );
#endif // #ifdef INdevel
void shoflgs( string intro, styp_flags flgs );



#endif // FO_UTILS_H
