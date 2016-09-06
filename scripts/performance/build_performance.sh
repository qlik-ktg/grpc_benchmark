#!/bin/bash

set -ex

cd $(dirname $0)/../../..

for language in $@
do
    case "$language" in
    "c++")
        ;;
    esac
done
