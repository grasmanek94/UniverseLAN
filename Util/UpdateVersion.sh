#!/bin/bash

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
cd ../Source/Version

if UPDATE_NR=$(git rev-list HEAD --count 2>/dev/null); then
    :
else
    if [ -n "${UNIVERSELAN_FORCE_BUILD_NUMBER}" ]; then
        UPDATE_NR="${UNIVERSELAN_FORCE_BUILD_NUMBER}"
        echo "WARNING: Unable to obtain build number from git, using UNIVERSELAN_FORCE_BUILD_NUMBER=${UPDATE_NR}"
    else
        UPDATE_NR=0
        echo "WARNING: Unable to obtain build number from git, using build number 0"
    fi
fi

echo "#define BUILD_VERSION ${UPDATE_NR}" > auto_version_check.h

if cmp -s "auto_version.h" "auto_version_check.h"; then
    rm auto_version_check.h
    echo "Version doesn't need updating"
else
    echo "Updating version..."
    touch Version.cxx
    echo "touched version.cxx ..."
    rm -f auto_version.h
    mv auto_version_check.h auto_version.h
    echo "Updated version to ${UPDATE_NR}"
fi