
neve=1000

# create inclusive 3p sample
./bin/dire --input n3lo-create-toy-dy1p-sample-inc.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-dy1p-inclusive-sample-2.lhe
