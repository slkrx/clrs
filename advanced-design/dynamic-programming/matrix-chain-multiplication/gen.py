from random import randint
height = 25
width = 6
for j in range(height):
	print("{", end="")
	for i in range(width):
		print(f"{randint(1,100):2d}", ' ' if i == width - 1 else ', ', end='', sep='')
	print("}" if j == height - 1 else "},")
