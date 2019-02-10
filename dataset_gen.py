import random
print("Enter maximum point : ")
a = int(input())

print("Enter Number of points : ")
n = int(input())

f = open("dataPoints.txt", "w+")
for i in range(n):
	x = random.randint(0,a)
	y = random.randint(0,a)
	f.write(str(i+1)+" "+str(x)+" "+str(y)+"\n")

# x = random.randint(0,90)
# y = random.randint(0,90)
# print(x, y, x+4, y+50)
# x = random.randint(0,90)
# y = random.randint(0,90)
# print(x, y, x+50, y+4)