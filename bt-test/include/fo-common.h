//
// This provides the common declaration for the file organizer string
//   handling classes that are needed for handling the folder and
//   file name strings.  These common declarations are needed by
//   virtually every object module in the development.
//

#ifndef FO_COMMON_H
#define FO_COMMON_H

#include <string>
// #include <iostream>
#include <sstream>

using namespace std;

//
// Macro to enable code intended for development only
//   #define INdevel

//
// GGG - For now, the INFOdisplay define needs to be turned on at all
//   times until I decide how to solve the problem with getting name
//   strings.
#define INFOdisplay

//
// Macro to enable ncurses I/O capabilities
//    #define USEncurses

//
// Macro to provide the btree graphic output display coding additions
// #define GENbtreeGRF

#ifndef INFOdisplay
#ifdef USEncurses
#define INFOdisplay
#endif  //  #ifdef USEncurses
#endif // #ifndef INFOdisplay

//  struct flag_set {
//      uint16_t track_base_search_vars : 1;
//      uint16_t change_start_str_num : 1;
//      uint16_t read_strings_from_file : 1;
//      uint16_t show_info_output : 1;
//      uint16_t play_back_names_read : 1;
//      uint16_t show_data_record_sizes : 1;
//      uint16_t show_name_store_strings : 1;
//      uint16_t play_name_store_stream : 1;
//      uint16_t show_any : 1;
//  };
//
//  extern flag_set pflg;
//  extern ostringstream infstrm;
//  extern ostringstream grfstrm;
//  extern ostringstream dbstrm;
//  extern ostringstream erstrm;
#ifdef INFOdisplay    // Declarations for development only
// This is the base search variable info save stream it needs to be active
//   when the macro INdevel is defined
extern ostringstream bsvistrm;
#endif // #ifdef INFOdisplay

// extern ostream& iout;
// extern ostream& gout;
extern ostream& errs;
extern ostream& dbgs;

#ifdef INdevel
    // Declarations/definitions/code for development only

#endif // #ifdef INdevel

#endif  // FO_COMMON_H
