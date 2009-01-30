header_dir = $$PWD/../include

QT += \
    core \

SOURCES += \
    $$PWD/qregexengine.cpp \
    $$PWD/qregexenginebase.cpp \
    $$PWD/qregexmatch.cpp \
    $$PWD/stringlistregexfeeder.cpp \
    $$PWD/ushorttraits.cpp \

HEADERS += \
    $${header_dir}/qregexengine.h \
    $${header_dir}/qregexenginebase.h \
    $${header_dir}/qregexfeedengine.h \
    $${header_dir}/qregexmatch.h \
    $${header_dir}/qregexmatchbase.h \
    $${header_dir}/qregexfeedmatch.h \
    $${header_dir}/stringlistregexfeeder.h \
    $${header_dir}/ushorttraits.h \

INCLUDEPATH += $${header_dir}
