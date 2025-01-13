from pathlib import Path
import time

def is_report_safe(arr):
	# State can be 'inc' or 'dec' or empty
	state = ""
	prev = arr[0]
	for num in arr:
		if state == "":
			if arr[0] < arr[1]:
				state = "inc"
			else:
				state = "dec"
			continue

		if num > prev and state == "dec":
			return False

		if num < prev and state == "inc":
			return False

		if not (1 <= abs(num - prev) <= 3):
			return False

		prev = num
	return True


def is_report_safe2(arr, state_default = ""):
	# State can be 'inc' or 'dec' or empty
	state = ""
	prev = arr[0]
	has_tolerated = False
	for num in arr:
		if state == "":
			if state_default:
				state = state_default
				continue
			if arr[0] < arr[1]:
				state = "inc"
			else:
				state = "dec"
			continue

		if num > prev and state == "dec":
			if has_tolerated:return False
			else: has_tolerated = True; continue

		if num < prev and state == "inc":
			if has_tolerated:return False
			else: has_tolerated = True; continue

		if not (1 <= abs(num - prev) <= 3):
			if has_tolerated:return False
			else: has_tolerated = True; continue

		prev = num
	return True


#part 1 solved in 15:23
def solution1():
	with open(Path.cwd() / "dec2" / "data.txt") as file:
		total = 0
		for line in file.readlines():
			report = line.split()
			is_safe = is_report_safe([int(num) for num in report])
			total += int(is_safe)
		print(total)


#part 2 solved in 24:16
def solution2():
	start_time = time.time()
	with open(Path.cwd() / "dec2" / "data.txt") as file:
		total = 0
		for line in file.readlines():
			report = [int(num) for num in line.split()]
			# wrong, tried 1000, 598, 623, 633, 721
			# is_safe = is_report_safe2(report, "inc") or is_report_safe2(report, "dec")
			# if not is_safe:
			# 	is_safe = is_safe or is_report_safe(report[1:])

			is_safe = False
			for i in range(len(report)):
				temp = report.copy()
				temp.pop(i)
				is_safe = is_safe or is_report_safe(temp)

			total += int(is_safe)
		print(total)
	print(f"Time taken: {time.time() - start_time} s")

# solution1()
solution2()

print("" or "Guy")