# I use this to help with merging extern.h from upstream
s/^E/extern/
s/FDECL(\([^,]*\), *\(([^)]\+)\))/\1\2/
s/NDECL(\(.*\))/\1(void)/
s/UCHAR_P/uchar/g
s/BOOLEAN_P/boolean/g
s/XCHAR_P/xchar/g
s/SCHAR_P/schar/g
s/ALIGNTYP_P/aligntyp/g
s/CHAR_P/char/g
s/SHORT_P/short/g
s/genericptr_t/void */g
