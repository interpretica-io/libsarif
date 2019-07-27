#!/bin/bash
function usage() {
	echo "Usage: $0 <json-specification-file>"
	exit 1
}

function not_installed() {
	echo "Please, install quicktype. See https://quicktype.io"
	exit 2
}

if [ "$1" == "" ] ; then
	usage
fi

if [ "$(command -v quicktype)" == "" ] ; then
	not_installed
fi

cat $1 | \
	quicktype --code-format with-getter-setter \
			  --namespace libsarif \
			  --no-boost \
			  -l c++ \
			  --out include/libsarif.hpp
