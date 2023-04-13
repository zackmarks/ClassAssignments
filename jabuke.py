xa,ya = map(int,input().split(" "))
xb,yb = map(int,input().split(" "))
xc,yc = map(int,input().split(" "))

area = abs(xa*(yb-yc) + xb*(yc-ya) + xc*(ya-yb))/2.0
t = int(input())
count = 0
#make three triangles with each new point as a point in the triangle, add area
for i in range(t):
	xd,yd = map(int,input().split(" "))
	areaAB = abs(xa*(yb-yd) + xb*(yd-ya) + xd*(ya-yb))/2.0
	areaBC = abs(xd*(yb-yc) + xb*(yc-yd) + xc*(yd-yb))/2.0
	areaAC = abs(xa*(yd-yc) + xd*(yc-ya) + xc*(ya-yd))/2.0
	if(areaAB + areaBC + areaAC == area):
		count += 1
print(area)
print(count)