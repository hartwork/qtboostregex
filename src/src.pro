profiles_to_include = \
    $$PWD/boost_regex_files.pri \
    $$PWD/src_files.pri \
    $$PWD/src_target.pri \

for(profile, profiles_to_include) {
    include($${profile}) | error(File '$${profile}' could not be included)
}

DESTDIR = $$PWD/../lib
