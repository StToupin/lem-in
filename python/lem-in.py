from sys import argv, exit
from map import Map

try:
	file_name = argv[1]
except IndexError:
	print "Usage: {} map.txt".format(argv[0])
	exit(0)

m = Map(file_name)
flux = m.solve()

print m
print "Flux:", flux
m.draw()