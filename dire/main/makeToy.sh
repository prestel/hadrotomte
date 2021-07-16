

neve=1000
rm dire; make dire

./dire --input n3lo-create-toy-5p-sample.cmnd --hepmc_output toy-5p.hepmc --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-5p-combined-sample.lhe

./dire --input n3lo-create-toy-4p-sample-inc.cmnd --input n3lo-create-toy-4p-sample-rec.cmnd --hepmc_output toy-4p.hepmc --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-4p-combined-sample.lhe

exit 0

./bin/dire --input n3lo-create-toy-3p-sample-inc.cmnd --input n3lo-create-toy-3p-sample-rec.cmnd --hepmc_output toy-3p.hepmc --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-3p-combined-sample.lhe
./bin/dire --input n3lo-create-toy-2p-sample-inc.cmnd --input n3lo-create-toy-2p-sample-rec.cmnd --hepmc_output toy-2p.hepmc --nevents $neve --setting "next:numbercount = 1" --setting "random:setseed = on" --setting "random:seed = 1234" --lhef_output n3lo-2p-combined-sample.lhe
