####################################################################################################
## Boost.Regex code
####################################################################################################
BOOST_PATH = $$PWD/../boost_regex
BOOST_REGEX_PATH = $${BOOST_PATH}/boost
INTERFACE_PATH = $${BOOST_REGEX_PATH}/regex
IMPLEMENTATION_PATH = $$PWD/../boost_regex/libs/regex/src

## Ported from ALL_HEADERS variable
HEADERS += \
	$${INTERFACE_PATH}/config/borland.hpp \
	$${INTERFACE_PATH}/config/cwchar.hpp \
    \
	$${INTERFACE_PATH}/v4/basic_regex_creator.hpp \
	$${INTERFACE_PATH}/v4/basic_regex.hpp \
	$${INTERFACE_PATH}/v4/basic_regex_parser.hpp \
	$${INTERFACE_PATH}/v4/char_regex_traits.hpp \
	$${INTERFACE_PATH}/v4/cpp_regex_traits.hpp \
	$${INTERFACE_PATH}/v4/cregex.hpp \
	$${INTERFACE_PATH}/v4/c_regex_traits.hpp \
	$${INTERFACE_PATH}/v4/error_type.hpp \
	$${INTERFACE_PATH}/v4/fileiter.hpp \
	$${INTERFACE_PATH}/v4/instances.hpp \
	$${INTERFACE_PATH}/v4/iterator_category.hpp \
	$${INTERFACE_PATH}/v4/iterator_traits.hpp \
	$${INTERFACE_PATH}/v4/match_flags.hpp \
	$${INTERFACE_PATH}/v4/match_results.hpp \
	$${INTERFACE_PATH}/v4/mem_block_cache.hpp \
	$${INTERFACE_PATH}/v4/perl_matcher_common.hpp \
	$${INTERFACE_PATH}/v4/perl_matcher.hpp \
	$${INTERFACE_PATH}/v4/perl_matcher_non_recursive.hpp \
	$${INTERFACE_PATH}/v4/perl_matcher_recursive.hpp \
	$${INTERFACE_PATH}/v4/primary_transform.hpp \
	$${INTERFACE_PATH}/v4/protected_call.hpp \
	$${INTERFACE_PATH}/v4/regbase.hpp \
	$${INTERFACE_PATH}/v4/regex_format.hpp \
	$${INTERFACE_PATH}/v4/regex_fwd.hpp \
	$${INTERFACE_PATH}/v4/regex_grep.hpp \
	$${INTERFACE_PATH}/v4/regex.hpp \
	$${INTERFACE_PATH}/v4/regex_iterator.hpp \
	$${INTERFACE_PATH}/v4/regex_match.hpp \
	$${INTERFACE_PATH}/v4/regex_merge.hpp \
	$${INTERFACE_PATH}/v4/regex_raw_buffer.hpp \
	$${INTERFACE_PATH}/v4/regex_replace.hpp \
	$${INTERFACE_PATH}/v4/regex_search.hpp \
	$${INTERFACE_PATH}/v4/regex_split.hpp \
	$${INTERFACE_PATH}/v4/regex_token_iterator.hpp \
	$${INTERFACE_PATH}/v4/regex_traits_defaults.hpp \
	$${INTERFACE_PATH}/v4/regex_traits.hpp \
	$${INTERFACE_PATH}/v4/regex_workaround.hpp \
	$${INTERFACE_PATH}/v4/states.hpp \
	$${INTERFACE_PATH}/v4/sub_match.hpp \
	$${INTERFACE_PATH}/v4/syntax_type.hpp \
	$${INTERFACE_PATH}/v4/w32_regex_traits.hpp \
    \
    $${INTERFACE_PATH}/config.hpp \
	$${INTERFACE_PATH}/pattern_except.hpp \
	$${INTERFACE_PATH}/regex_traits.hpp \
	$${INTERFACE_PATH}/user.hpp \

## Headers not listed in ALL_HEADERS
HEADERS += \
    $${BOOST_REGEX_PATH}/regex.hpp

SOURCES += \
	$${IMPLEMENTATION_PATH}/cpp_regex_traits.cpp \
##	$${IMPLEMENTATION_PATH}/cregex.cpp \
	$${IMPLEMENTATION_PATH}/c_regex_traits.cpp \
##	$${IMPLEMENTATION_PATH}/fileiter.cpp \
##	$${IMPLEMENTATION_PATH}/icu.cpp \
##	$${IMPLEMENTATION_PATH}/instances.cpp \
##	$${IMPLEMENTATION_PATH}/posix_api.cpp \
	$${IMPLEMENTATION_PATH}/regex.cpp \
##	$${IMPLEMENTATION_PATH}/regex_debug.cpp \
	$${IMPLEMENTATION_PATH}/regex_raw_buffer.cpp \
	$${IMPLEMENTATION_PATH}/regex_traits_defaults.cpp \
	$${IMPLEMENTATION_PATH}/static_mutex.cpp \
##	$${IMPLEMENTATION_PATH}/usinstances.cpp \
##	$${IMPLEMENTATION_PATH}/w32_regex_traits.cpp \
##	$${IMPLEMENTATION_PATH}/wc_regex_traits.cpp \
##	$${IMPLEMENTATION_PATH}/wide_posix_api.cpp \
	$${IMPLEMENTATION_PATH}/winstances.cpp \

INCLUDEPATH += \
    $${BOOST_PATH} \
    $${BOOST_REGEX_PATH} \
