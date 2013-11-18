import csv

csvfile = 'test.tsv'
reader = csv.DictReader( file(csvfile, 'r') )

dictionary = {}

for row in reader:
	dictionary.setdefault(row["id"], []).append(row["price"])

print dictionary

for key in dictionary:
	print "--------------------"
	print "key:" + key
	print len(dictionary[key])
