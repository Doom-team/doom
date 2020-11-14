#!/bin/bash
set -e

export PM_INDENT=""
export PM_NEXT=""

function process() {
    INFILE="${3}"
    OUTFILE="pm/${2}"
    export PM_BASE="${1}"
    export PM_PAGE="${2}"
    export PM_FILE="${3}"
    echo ==== ${OUTFILE} ====
    echo "${PM_INDENT}* [[${2}]]" >> pm/Index
    cat ${INFILE} |
        awk '{ gsub(/`\\``/, "`backquote`") } { print }' |
        awk '{ gsub(/:kbd:/, ":sub:") } { print }' |
        awk '{ gsub(/:download:/, ":sup:") } { print }' |
        pandoc -f RST -t pmwiki.lua > ${OUTFILE}
    export PM_NEXT="$PM_PAGE"
}

echo "" > pm/Index

# NOTE: disabled this one (to not clobber the edited version on the website)
# process "index"  "User.Index"  "source/index.rst"

# NOTE 2: we build the pages in reverse order, to ease adding "next" links
# [ hence the pm/Index file is currently useless ]

process "basics"         "User.Basics"       "source/basics/index.rst"
process "concepts"       "User.Concepts"     "source/mapping-concepts/index.rst"
process "management"     "User.Projects"     "source/project-management/index.rst"
process "user_interface" "User.UI"           "source/user-interface/index.rst"
process "installation"   "User.Installation" "source/installation.rst"
process "intro"          "User.Intro"        "source/introduction.rst"

echo "* Cookbook" >> pm/Index
PM_INDENT="    "
PM_NEXT=""

process "ck_prefabs"   "Cookbook.Prefabs"      "source/cookbook/prefabs/index.rst"
process "ck_traps"     "Cookbook.Traps"        "source/cookbook/traps/index.rst"
process "ck_pool"      "Cookbook.ToxicPool"    "source/cookbook/toxic-pool/index.rst"
process "ck_lifts"     "Cookbook.Lifts"        "source/cookbook/lifts/index.rst"
process "ck_doors"     "Cookbook.Doors"        "source/cookbook/doors/index.rst"
process "ck_teleport"  "Cookbook.Teleporters"  "source/cookbook/teleporters/index.rst"
process "ck_altar"     "Cookbook.Altar"        "source/cookbook/altar/index.rst"
process "ck_curve"     "Cookbook.CurvedStairs" "source/cookbook/curved-stairs/index.rst"
process "ck_stairs"    "Cookbook.Stairs"       "source/cookbook/stairs/index.rst"
process "ck_sky"       "Cookbook.Sky"          "source/cookbook/sky/index.rst"

echo "ALL DONE."
