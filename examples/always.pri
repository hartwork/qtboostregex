INCLUDEPATH += $$PWD/../include
LIBS += \
    -L$$PWD/../lib/ -lQtBoostRegex \
    -L$$PWD/../boost_regex/libs/regex/build/gcc/ -lboost_regex-gcc-1_34_1 \

