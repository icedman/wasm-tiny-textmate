cmake_minimum_required(VERSION 3.0)

project(cpp_library)

set(CPP_LIBRARY_TYPE "STATIC" CACHE STRING "Library type to build")
set_property(CACHE CPP_LIBRARY_TYPE PROPERTY STRINGS STATIC SHARED)

add_library(cpp_lib ${CPP_LIBRARY_TYPE} lib.cpp
    ./libs/Onigmo/regcomp.c
    ./libs/Onigmo/regexec.c
    ./libs/Onigmo/regparse.c
    ./libs/Onigmo/regsyntax.c
    ./libs/Onigmo/st.c
    ./libs/Onigmo/regenc.c
    ./libs/Onigmo/regext.c
    ./libs/Onigmo/regposerr.c
    ./libs/Onigmo/regtrav.c
    ./libs/Onigmo/regerror.c
    ./libs/Onigmo/reggnu.c
    ./libs/Onigmo/regposix.c
    ./libs/Onigmo/regversion.c
    ./libs/Onigmo/enc/ascii.c  
    #./libs/Onigmo/enc/euc_kr.c
    #./libs/Onigmo/enc/iso_8859_10.c
    #./libs/Onigmo/enc/iso_8859_16.c
    #./libs/Onigmo/enc/iso_8859_5.c
    #./libs/Onigmo/enc/koi8_r.c
    #./libs/Onigmo/enc/us_ascii.c
    ./libs/Onigmo/enc/utf_8.c    
    #./libs/Onigmo/enc/windows_1254.c
    #./libs/Onigmo/enc/big5.c   
    #./libs/Onigmo/enc/euc_tw.c
    #./libs/Onigmo/enc/iso_8859_11.c
    #./libs/Onigmo/enc/iso_8859_1.c
    #./libs/Onigmo/enc/iso_8859_6.c
    #./libs/Onigmo/enc/koi8_u.c
    #./libs/Onigmo/enc/utf_16be.c
    #./libs/Onigmo/enc/windows_1250.c
    #./libs/Onigmo/enc/windows_1257.c
    #./libs/Onigmo/enc/cp949.c  
    #./libs/Onigmo/enc/gb18030.c
    #./libs/Onigmo/enc/iso_8859_13.c
    #./libs/Onigmo/enc/iso_8859_2.c
    #./libs/Onigmo/enc/iso_8859_7.c
    #./libs/Onigmo/enc/mktable.c 
    #./libs/Onigmo/enc/utf_16le.c
    #./libs/Onigmo/enc/windows_1251.c
    #./libs/Onigmo/enc/windows_31j.c
    #./libs/Onigmo/enc/emacs_mule.c
    #./Onigmo/enc/gb2312.c
    #./libs/Onigmo/enc/iso_8859_14.c
    #./libs/Onigmo/enc/iso_8859_3.c
    #./libs/Onigmo/enc/iso_8859_8.c
    #./libs/Onigmo/enc/shift_jis.c
    #./libs/Onigmo/enc/utf_32be.c
    #./libs/Onigmo/enc/windows_1252.c
    #./libs/Onigmo/enc/euc_jp.c 
    #./libs/Onigmo/enc/gbk.c 
    #./libs/Onigmo/enc/iso_8859_15.c
    #./libs/Onigmo/enc/iso_8859_4.c
    #./libs/Onigmo/enc/iso_8859_9.c
    ./libs/Onigmo/enc/unicode.c 
    #./libs/Onigmo/enc/utf_32le.c
    #./libs/Onigmo/enc/windows_1253.c
    ./libs/tiny-textmate/textmate.c
    ./libs/tiny-textmate/package.c
    ./libs/tiny-textmate/parser.c
    ./libs/tiny-textmate/processor.c
    ./libs/tiny-textmate/reader_cjson.c
    ./libs/tiny-textmate/theme.c
    ./libs/tiny-textmate/cJSON/cJSON.c
)

target_include_directories(cpp_lib 
    PRIVATE
    ./libs/Onigmo
    ./libs/Onigmo/enc
    ./libs/Onigmo/enc/unicode
    ./libs/tiny-textmate
    ./libs/tiny-textmate/cJSON
)

# em_link_js_library(cpp_lib "lib.js")