#!/bin/bash

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

cd "$parent_path"

cd ../Source/Version

UPDATE_NR=$(git rev-list HEAD --count)
echo "#define BUILD_VERSION ${UPDATE_NR}" > auto_version_check.h

if cmp -s "auto_version.h" "auto_version_check.h"; then
    rm auto_version_check.h
    echo "Version doesn't need updating"
else
    echo "Updating version..."
    touch Version.cxx
    echo "touched version.cxx ..."
    rm "auto_version.h"
    mv "auto_version_check.h" "auto_version.h"
    echo "Updated version to ${UPDATE_NR}"
fi
