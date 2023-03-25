#!/bin/sh
echo "Trying to test with path:" $1
path=$1
tests=$(ls $path)

nb=0
max=0
test()
{

    if [ -d $path ]; then
        clear
        echo "-- Start testing..."
        for file in $tests; do
            echo -e "   Test:"$file
            var="${path}/${file}"
            #echo $var
            ./src/tc --object-parse $var
            res=$?
            echo -ne "\t\t\t\t\t\t"
            if [ $res -ne 0 ] ; then
                echo -ne "\033[0;31mFail\t\033[0m"
            else
                echo -ne "\033[0;32mPass\t\033[0m"
                nb=$(($nb+1))
            fi
            max=$(($max+1))
            echo
        done
        echo -e "Passing" $nb"/"$max
    else
        echo "no such a file with path:" $path
    fi
}
test
