#!/bin/bash
#
# SyncRepoWithWiki - synchronize the wikiexamples with the
#                    vtk.org/Wiki/VTK?examples wiki
#
# Make sure the wiki is up
echo "Synchronizing the wikiexamples repository with the wiki."
HOST=www.github.com
echo "0) Can we access the wiki?"
ping -c 1 $HOST &> /dev/null
if test "${?}" = 1
  then
  echo "$HOST is not accessible. Try again later"
  exit
fi

echo "1) Pull updates from master repository"
git pull origin master
(cd Tarballs; git checkout .)
(cd Tarballs; git pull origin master)

echo "2) Remove all .cxx, .h, .py, .tcl, .java, .cs, .ui files from local repository"
find . -name mwclient -prune -type f -o "(" -name \*.cxx -o -name \*.h -o -name \*.tcl -o -name \*.java -o -name \*.py -o -name \*.cs -o -name \*.ui -o -name \*.cpp  ")" -exec rm -f {} \;

echo "3) Scrape the wiki"
./Admin/ScrapeWiki

echo "4) Update Wiki Templates"
git add Admin/VTKCMakeLists
git add Admin/VTKQtCMakeLists
git commit -m"SYNC: Wiki template files modified on wiki" Admin/VTKCMakeLists Admin/VTKQtCMakeLists

echo "5.1) Change python permissions to execute"
find . -name mwclient -prune -type f -o -name \*.py -exec chmod +x {} \;

echo "5.2) Process modified files"
git commit -m "SYNC: Files modified on wiki." `git status | grep modified: | cut -d":" -f2,2`

echo "6) Process new files"
find . "(" -name \*.cxx -o -name \*.h -o -name \*.tcl -o -name \*.py -o -name \*.java  -o -name \*.cs -o -name \*.ui -o -name \*.cpp ")" -exec git add {} \;
git commit -m "SYNC: Files added to wiki."

echo "7) Process deleted files"
git rm `git status | grep deleted: | cut -d":" -f2,2`
git commit -m "SYNC: Files deleted (or moved) from wiki."

echo "8) Update tarballs and push to tarball repo"
(cd Tarballs; git add *tar)
(cd Tarballs; git commit -m "SYNC: Tarballs modified")
(cd Tarballs; git push)

echo "9) Push the changes"
git push
