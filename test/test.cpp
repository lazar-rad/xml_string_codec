#include <iostream>
#include <cstring>

#include "xml_string_codec.h"

using namespace std;

enum Action { CHECK = 0, ENCODE, DECODE };

int main(int argc, const char* argv[])
{
    Action act = CHECK;

    for (int i = 1; i < argc; i++)
    {
        switch (act)
        {
            case CHECK:  if (strlen(argv[i]) == 2)
                         {
                             if (argv[i][0] == '-')
                             {
                                 switch (argv[i][1])
                                 {
                                     case 'e': act = ENCODE; break;
                                     case 'd': act = DECODE; break;
                                     default:  act = CHECK;  break;
                                 }
                             }
                         }
                         break;
            case ENCODE: cout << encode_string_for_xml(argv[i])  << endl; act = CHECK; break;
            case DECODE: cout << decode_string_from_xml(argv[i]) << endl; act = CHECK; break;
        }
    }

    string t1_e = "a<b>c&d\'e\"f g";
    cout << "encode: " << t1_e << " >> " << encode_string_for_xml(t1_e) << endl;

    string t2_d = "A&lt;B&gt;C&amp;D&apos;E&quot;F&#x20;G";
    cout << "decode: " << t2_d << " >> " << decode_string_from_xml(t2_d) << endl;

    string t3_derr = "a&ltb";
    cout << "decode: " << t3_derr << " >> " << decode_string_from_xml(t3_derr) << endl;

    string t4_derr = "a&apot;b";
    cout << "decode: " << t4_derr << " >> " << decode_string_from_xml(t4_derr) << endl;

    string t5_derr = "a&#x21;b";
    cout << "decode: " << t5_derr << " >> " << decode_string_from_xml(t5_derr) << endl;

    string t6_derr = "a&quot";
    cout << "decode: " << t6_derr << " >> " << decode_string_from_xml(t6_derr) << endl;
}
