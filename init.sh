rm *.ndx
rm *.dat
gcc pds.c bst.c contact.c contact_loader.c
./a.out scandemo contact_dump.txt
./a.out newdemo contact_dump.txt
