rem $Id: composer.bat,v 1 2003/10/15 jcr $
@echo off
echo --------- XML Composer by jcr: 2003.10.16 ----------------------

if not exist %1 goto :end

if exist temp\nul goto :skiptemp

rem ------------ inits ------------

mkdir temp

:skiptemp
del temp\*.* /q

echo -Step1- Generating the specific stylesheet ----------------------

saxon %1 composer.xsl > comp-query.xsl

echo -Step2- Computing queries ----------------------------------------

saxon comp-driver.xml comp-query.xsl > temp\comp-res.xml

echo --- Results in: temp\comp-res.xml -----------------------------

goto :finish

:end
echo ERROR: Wrong number of parameters
echo SYNTAX: composer query.xml
echo                 query.xml: XML document containing the queries

:finish
echo --- That's all folks! ----------------------------------------
