#!/bin/bash
# Generate libsarif headers from JSON schema using quicktype
function usage() {
	echo "Usage: $0 <json-specification-file>"
}

function not_installed() {
	echo "Please, install quicktype."
	echo "See https://quicktype.io for details."
}

if [ "$1" == "" ] ; then
	usage
	exit 1
fi

if [ "$(command -v quicktype)" == "" ] ; then
	not_installed
	exit 2
fi

# Use quicktype to generate classes
# Add is_obj_valid() check to ensure no null objects appears
cat $1 | \
	quicktype --code-format with-getter-setter \
			  --namespace libsarif \
			  --no-boost \
			  -l c++ \
			  -s schema | \
	sed -E "s|(j\[\"\w+\"\]) = (x\.\w+\(\));|if (is_obj_valid(\2))\n            \1 = \2;|g" > include/libsarif.hpp

# Add is_obj_valid() which is true for all types besides std::shared_ptr
# ('optional' implementation used in quicktype)
perl -0777 -i -pe 's/\n\nnamespace nlohmann \{/\nnamespace nlohmann \{
    template <typename T>
    static bool is_obj_valid\(std::shared_ptr<T> ptr\) \{
        return ptr != nullptr;
    \}

    template <typename T>
    static bool is_obj_valid\(T obj\) \{
        return true;
    \}\n/igs' include/libsarif.hpp
