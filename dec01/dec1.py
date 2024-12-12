from pathlib import Path

#part 1 solved in 10:52
def solution1():
	with open(Path.cwd() / "dec01" / "data.txt") as file:
		left = []
		right = []
		for line in file.readlines():
			l, r = line.strip().split()
			left.append(int(l))
			right.append(int(r))

		left.sort()
		right.sort()

		total = 0
		for i in range(len(left)):
			total += abs(left[i] - right[i])

		print(total)


#part 2 solved in 9:30
def solution2():
	with open(Path.cwd() / "dec01" / "data.txt") as file:
		left = []
		right = []
		for line in file.readlines():
			l, r = line.strip().split()
			left.append(int(l))
			right.append(int(r))

		scores = {}
		total_score = 0

		for l in left:
			if l in scores.keys():
				# print("added")
				total_score += scores[l] * l
			else:
				partial_sum = 0
				for r in right:
					if l == r:
						partial_sum += 1
				scores[l] = partial_sum
				total_score += partial_sum * l
		print(total_score)

solution1()
solution2()