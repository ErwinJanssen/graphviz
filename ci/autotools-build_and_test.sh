#!/bin/sh

# Run this script from the root source directory

if ./autogen.sh ; then
    echo "autogen.sh succesfull."
else
    echo "Error: autogen.sh failed." >&2
    exit 1
fi

if make ; then
    echo "make succesfull."
else
    echo "Error: make failed." >&2
    exit 1
fi

if make dist ; then
    echo "make dist succesfull."
else
    echo "Error: make dist failed." >&2
    exit 1
fi
