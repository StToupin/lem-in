from sys import argv, exit
from decimal import Decimal

class ParseError(Exception): pass
class DoubleRoomDefinition(Exception): pass
class MissingStartRoom(Exception): pass
class MissingEndRoom(Exception): pass
class MissingRoomInLink(Exception): pass

class Connection:
	def __init__(self, capacity, flux):
		self.capacity = capacity
		self.flux = flux

class Room:
	def __init__(self, x, y, name):
		self.x = x
		self.y = y
		self.name = name
		self.connections = {}
		self.parent = None
		self.capacity = 0

	def add_connection(self, room):
		if room in self.connections.keys():
			self.connections[room].capacity += 1
		else:
			self.connections[room] = Connection(1, 0)

class Map:
	def parse_room_line(self, line):
		from re import match
		m = match(r'^([^ ^\-]+) ([\+-]?\d+) ([\+-]?\d+)$', line)
		if m:
			name = m.group(1)
			x = int(m.group(2))
			y = int(m.group(3))
			if name in self.rooms.keys():
				raise DoubleRoomDefinition
			else:
				new_room = Room(x, y, name)
				self.rooms[name] = new_room
				return new_room
		else:
			raise ParseError
	
	def parse_link_line(self, line):
		from re import match
		m = match(r'^([^ ^\-]+)-([^ ^\-]+)$', line)
		if m:
			room_name_1 = m.group(1)
			room_name_2 = m.group(2)
			try:
				room_1 = self.rooms[room_name_1]
				room_2 = self.rooms[room_name_2]
				room_1.add_connection(room_2)
				room_2.add_connection(room_1)
			except KeyError:
				raise MissingRoomInLink
		else:
			raise ParseError

	def __init__(self, file_name):
		self.rooms = {}
		self.links = []
		self.start = None
		self.end = None
		with open(file_name, 'r') as f:
			state = 0
			for line in f:
				line = line[:-1]
				print line
				if line == "##start":
					if state == 0:
						state = 1
					else:
						raise ParseError
				elif line == "##end":
					if state == 0:
						state = 2
					else:
						raise ParseError
				elif line.startswith('#'):
					continue
				else:
					n_spaces = 0
					n_dashes = 0
					for c in line:
						if c == ' ':
							n_spaces += 1
						if c == '-':
							n_dashes += 1
					if n_dashes == 1 and n_spaces == 0:
						if state == 0:
							state = 3
						elif state != 3:
							raise ParseError
						self.parse_link_line(line)
					elif n_spaces == 2:
						if (state == 0 or state == 1 or state == 2):
							last_room = self.parse_room_line(line)
							if state == 1:
								self.start = last_room
								state = 0
							if state == 2:
								self.end = last_room
								state = 0
						else:
							raise ParseError
					else:
						raise ParseError
			if self.start == None:
				raise MissingStartRoom
			if self.end == None:
				raise MissingEndRoom

	def __str__(self):
		s = ""
		for room in self.rooms.values():
			s += '{}: ({}, {})\n'.format(room.name, room.x, room.y)
			for linked_room, connection in room.connections.items():
				s += '  -> {} (capacity: {}, flux: {})\n'.format(linked_room.name, connection.capacity, connection.flux)
		s += 'Start: {}\n'.format(self.start.name)
		s += 'End: {}\n'.format(self.end.name)
		return s

	def draw(self):
		import networkx as nx
		import matplotlib.pyplot as plt
		G = nx.Graph()
		pos = {}
		for room in self.rooms.values():
			pos[room.name] = (room.x, -room.y)
			G.add_node(room.name)
			for linked_room, connection in room.connections.items():
				if connection.flux >= 0:
					G.add_edge(room.name, linked_room.name, weight = connection.flux)
		edge_labels = dict([((u, v, ), d['weight']) for u, v, d in G.edges(data = True)])
		red_nodes = [self.start.name, self.end.name]
		node_colors = ['blue' if not node in red_nodes else 'red' for node in G.nodes()]
		nx.draw_networkx_edge_labels(G, pos, edge_labels = edge_labels)
		nx.draw(G, pos, node_color = node_colors, node_size = 1500, with_labels = True)
		plt.show()

try:
	file_name = argv[1]
except IndexError:
	print "Usage: {} map.txt".format(argv[0])
	exit(0)

m = Map(file_name)

# Edmonds-Karp

flux = 0
while True:
	# BFS
	for room in m.rooms.values():
		room.parent = None
		room.capacity = 0
	m.start.parent = 0
	m.start.capacity = Decimal('Infinity')
	queue = [m.start]
	end_reached = False
	while len(queue) > 0 and not end_reached:
		room = queue.pop(0)
		for next_room, connection in room.connections.items():
			if (connection.capacity - connection.flux) > 0 and next_room.parent == None:
				next_room.parent = room
				next_room.capacity = min(room.capacity, connection.capacity - connection.flux)
				if next_room == m.end:
					end_reached = True
					break
				queue.append(next_room)
	# algo
	if m.end.capacity == 0:
		break
	flux += m.end.capacity
	room = m.end
	while room != m.start:
		parent_room = room.parent
		parent_room.connections[room].flux += m.end.capacity
		room.connections[parent_room].flux -= m.end.capacity
		room = parent_room

#print m
#print flux
m.draw()