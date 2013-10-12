
FILE_ORIGINAL=./assets/split_test/1_original_sfpc.html
FILE_SPLITED=./assets/split_test/2_splited_sfpc. # extention will be added automatically
FILE_JOINED=./assets/split_test/3_joind_sfpc.html


# split sfpc.html into 1kb files
split -b 1k ${FILE_ORIGINAL} ${FILE_SPLITED}


# join the files 
cat ${FILE_SPLITED}?? > ${FILE_JOINED}


# check file size
# 
# wc (option) [file name] 
# http://www.k-tanaka.net/unix/wc.php
# $ wc -c FILENAME #=> filesize filename
# 
# awk [-F fs] [-v var=value] [-f progfile | 'prog'] [file ...]
# http://shellscript.sunone.me/awk.html
# 
SIZE_ORIGINAL=`wc -c ${FILE_ORIGINAL} | awk '{print $1}'`
SIZE_JOINED=`wc -c ${FILE_JOINED} | awk '{print $1}'`


# string --> number
# SIZE_ORIGINAL=`expr ${SIZE_ORIGINAL}`
# SIZE_JOINED=`expr ${SIZE_JOINED}`

# fileSize check
print "Original file size:" ${SIZE_ORIGINAL} " bytes"
print "Jointed file size :" ${SIZE_JOINED} " bytes"

if [ $SIZE_ORIGINAL -lt $SIZE_JOINED ] ; then
 	print Jointed file is bigger
elif [ $SIZE_ORIGINAL -gt $SIZE_JOINED ] ; then
 	print Original file is bigger
else
	print same file size!
fi
