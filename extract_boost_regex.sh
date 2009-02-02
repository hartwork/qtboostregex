#! /usr/bin/env bash
VERSION=1_37_0
BASE=boost_${VERSION}
ARCHIVE="$BASE.tar.bz2"
OUTPUT=boost_regex

## Setup
if [[ ${TERM} = cygwin ]]; then
    BCP=${BASE}/dist/bin/bcp
else
    BCP=bcp
    if [[ x`${BCP} --version 2>/dev/null` = x ]] ; then
        echo 'Error: bcp (Boost copy) not found, please install.'
        exit 1
    fi
fi

## Download
if [[ ! -e "$ARCHIVE" ]]; then
    echo 'Downloading...'
    wget "http://downloads.sourceforge.net/boost/$ARCHIVE" || exit 1
fi

## Extract Boost
if [[ ! -d "$BASE" ]]; then
    echo 'Extracting...'
    tar xf $ARCHIVE || exit 1

    echo 'Patching...'
    cd $BASE/libs/regex/src/ || exit 1
    mv icu.cpp icu.cpp_ORIG || exit 1
    cat icu.cpp_ORIG | sed -r 's/^(#include <boost\/regex\/icu.hpp>)/\/\/ \1/' > icu.cpp || exit 1
    rm icu.cpp_ORIG || exit 1
    cd - || exit 1
fi

## Extract Boost.Regex from Boost
if [[ ! -d "$OUTPUT" ]]; then
    if [[ ${TERM} = cygwin ]]; then
        pushd ${BASE} || exit 1
        ./configure || exit 1
        pushd tools/bcp || exit 1
        ../../tools/jam/src/bin.cygwinx86/bjam || exit 1
        popd || exit 1
        popd || exit 1
    fi

    echo 'Extracting Boost.Regex...'
    mkdir -p "$OUTPUT"
    "${BCP}" "--boost=./$BASE" regex.hpp "$OUTPUT" || exit 1
    pushd "$OUTPUT/libs/regex/build" || exit 1
    chmod a+x gcc_gen.sh
    ./gcc_gen.sh || exit 1
    make -f gcc.mak || exit 1
    make -f gcc.mak clean || exit 1
    rmdir "gcc/boost_regex-gcc-${VERSION}"
    rmdir "gcc/boost_regex-gcc-d-${VERSION}"
    popd || exit 1
fi

echo Done.

