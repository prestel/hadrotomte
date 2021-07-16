
neve=150000

# create inclusive 5p sample
#./bin/dire --input n3lo-create-toy-5p-sample.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-5p-lhe-rwgt.lhe
#./bin/dire --input n3lo-create-toy-5p-sample.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-5p-inclusive-sample-2.lhe
# create exclusive 4p sample
#./bin/dire --input n3lo-create-toy-4p-sample-inc.cmnd --input n3lo-create-toy-4p-sample-rec.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-4p-exclusive-sample-2.lhe
#exit 0

# create inclusive 4p sample, to use for exclusive 3p sample
#./bin/dire --input n3lo-create-toy-4p-sample-inc.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-4p-inclusive-sample-2.lhe
# create exclusive 3p sample
#./bin/dire --input n3lo-create-toy-3p-sample-inc.cmnd --input n3lo-create-toy-3p-sample-rec.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-3p-exclusive-sample-2.lhe
#exit 0

# create inclusive 3p sample, to use for exclusive 2p sample
#./bin/dire --input n3lo-create-toy-3p-sample-inc.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-3p-inclusive-sample-2.lhe
# create exclusive 2p sample
./bin/dire --input n3lo-create-toy-2p-sample-inc.cmnd --input n3lo-create-toy-2p-sample-rec.cmnd --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-2p-exclusive-sample-4.lhe
#exit 0

#
#./bin/dire --input n3lo-create-toy-2p-sample-inc.cmnd --input n3lo-create-toy-2p-sample-rec.cmnd --hepmc_output toy-2p.hepmc --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-2p-combined-sample.lhe
