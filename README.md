
# Projekt Semestralny - Michał Maciaszek - zadanie 5


## installation

    sudo apt update
    sudo apt install curl
    git clone https://github.com/jezykiprogramowaniazaoczneug/projektsemestralny-maciaszek.git
    cd projektsemestralny-maciaszek
    cmake CMakeLists.txt
    make

## usage
./projektsemestralny-maciaszek action input output


action - one of following:

           help    display this help
         --help    same as 'help'
        encrypt    encrypt text with Affine/Caesar cipher
         encode    morse-encode text
        decrypt    decrypt text encrypted with Affine/Caesar cipher
         decode    decode morse-encoded text


input - path to input file or:

          stdin    read from stdin
              -    same as 'stdin'
	http[s]://…    read from web resource


output - path to output file or:

         stdout    print to stdout
              -    same as 'stdout'
