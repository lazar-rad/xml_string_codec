#include <string>
#include <cstring>

#define LT     '<'
#define LT_ESC "&lt;"
#define LT_LEN 4
#define GT     '>'
#define GT_ESC "&gt;"
#define GT_LEN 4
#define AMP     '&'
#define AMP_ESC "&amp;"
#define AMP_LEN 5
#define APOS     '\''
#define APOS_ESC "&apos;"
#define APOS_LEN 6
#define QUOT     '\"'
#define QUOT_ESC "&quot;"
#define QUOT_LEN 6
#define SPACE     ' '
#define SPACE_ESC "&#x20;"
#define SPACE_LEN 6

/**
 * @brief Encodes the string by escaping problematic characters, such as: < > & (space)
 *
 * @param s Raw string to be encoded
 * @return string Encoded string
 */
std::string encode_string_for_xml( std::string s )
{
    int length = s.length();
    int new_length = length;

    for (char& c : s)
    {
        switch (c)
        {
            case LT:    new_length += (LT_LEN-1);    break;
            case GT:    new_length += (GT_LEN-1);    break;
            case AMP:   new_length += (AMP_LEN-1);   break;
            case APOS:  new_length += (APOS_LEN-1);  break;
            case QUOT:  new_length += (QUOT_LEN-1);  break;
            case SPACE: new_length += (SPACE_LEN-1); break;
            default:    break;
        }
    }

    if (length == new_length) return s;

    char* buildspace = new char[new_length+1];
    char* curr_pos = &buildspace[0];

    for (char& c : s)
    {
        switch (c)
        {
            case LT:    memcpy(curr_pos, LT_ESC,    LT_LEN);    curr_pos += LT_LEN;    break;
            case GT:    memcpy(curr_pos, GT_ESC,    GT_LEN);    curr_pos += GT_LEN;    break;
            case AMP:   memcpy(curr_pos, AMP_ESC,   AMP_LEN);   curr_pos += AMP_LEN;   break;
            case APOS:  memcpy(curr_pos, APOS_ESC,  APOS_LEN);  curr_pos += APOS_LEN;  break;
            case QUOT:  memcpy(curr_pos, QUOT_ESC,  QUOT_LEN);  curr_pos += QUOT_LEN;  break;
            case SPACE: memcpy(curr_pos, SPACE_ESC, SPACE_LEN); curr_pos += SPACE_LEN; break;
            default:    *(curr_pos++) = c; break;
        }
    }

    buildspace[new_length] = '\0';

    std::string ret_str(buildspace);
    delete[] buildspace;
    return ret_str;
}

/**
 * @brief Decodes the string by deescaping the escaped characters
 *
 * @param s Encoded string
 * @return string Decoded string; If the input string was not correctly escaped, the string "error" is returned
 */
std::string decode_string_from_xml( std::string s )
{
    int length = s.length();
    char* buildspace = new char[s.length()+1];
    memcpy(buildspace, s.data(), s.length());
    buildspace[s.length()] = '\0';
    
    int dest_pos = 0;
    for (int orig_pos = 0; orig_pos < s.length(); orig_pos++, dest_pos++)
    {
        if (buildspace[orig_pos] != '&')
        {
            buildspace[dest_pos] = buildspace[orig_pos];
        }
        else
        {
            int esc_cnt = 1;
            for (; buildspace[orig_pos+esc_cnt] != ';' && buildspace[orig_pos+esc_cnt] != '\0'; esc_cnt++);
            esc_cnt++;

            if      (esc_cnt == LT_LEN    && !memcmp(&buildspace[orig_pos], LT_ESC,    LT_LEN))    buildspace[dest_pos] = LT;
            else if (esc_cnt == GT_LEN    && !memcmp(&buildspace[orig_pos], GT_ESC,    GT_LEN))    buildspace[dest_pos] = GT;
            else if (esc_cnt == AMP_LEN   && !memcmp(&buildspace[orig_pos], AMP_ESC,   AMP_LEN))   buildspace[dest_pos] = AMP;
            else if (esc_cnt == APOS_LEN  && !memcmp(&buildspace[orig_pos], APOS_ESC,  APOS_LEN))  buildspace[dest_pos] = APOS;
            else if (esc_cnt == QUOT_LEN  && !memcmp(&buildspace[orig_pos], QUOT_ESC,  QUOT_LEN))  buildspace[dest_pos] = QUOT;
            else if (esc_cnt == SPACE_LEN && !memcmp(&buildspace[orig_pos], SPACE_ESC, SPACE_LEN)) buildspace[dest_pos] = SPACE;
            else
            {
                delete[] buildspace;
                return "error";
            }

            orig_pos += esc_cnt-1;
        }
    }

    buildspace[dest_pos] = '\0';

    std::string ret_str(buildspace);
    delete[] buildspace;
    return ret_str;
}
