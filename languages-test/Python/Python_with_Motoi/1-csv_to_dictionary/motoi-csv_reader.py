import csv

csvfile = 'test.tsv'
myReader = csv.DictReader( file(csvfile, 'r'), delimiter = '\t' )

for simona in myReader:
	print simona