function compileLJ {
	rm $1/*.l2
	for f in $1/* ; do
		
		if [ ${f##*.} = 'lua' ] ; then
			echo compiling $f ${f%.*}.l2
			luajit -b $f ${f%.*}.l2
		fi

		if [ -d $f ] ; then
			compileLJ $f
		fi
	done
	rm $1/*.lua
}

echo "COMPILING Luajit bytecode"
compileLJ 'lua'