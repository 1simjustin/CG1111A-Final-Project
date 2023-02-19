import math

dataset = [[ 0, 247, 83, 77 ], \
  [ 1, 55, 174, 120 ], \
  [ 2, 247, 148, 74 ], \
  [ 3, 151, 145, 187 ], \
  [ 4, 103, 213, 233 ], \
  [ 5, 255, 255, 251 ], \
  [ 6, 39, 5, 0 ], \
  [ 0, 227, 69, 51 ], \
  [ 1, 39, 172, 109 ], \
  [ 2, 235, 140, 44 ], \
  [ 3, 133, 140, 177 ], \
  [ 4, 70, 208, 230 ], \
  [ 5, 227, 250, 245 ], \
  [ 6, 15, 0, 0 ], \
  [ 0, 255, 98, 84 ], \
  [ 1, 78, 185, 130 ], \
  [ 2, 255, 153, 66 ], \
  [ 3, 156, 153, 191 ], \
  [ 4, 102, 214, 238 ], \
  [ 5, 251, 255, 255 ], \
  [ 6, 47, 11, 0 ], \
  [ 0, 251, 88, 73 ], \
  [ 1, 70, 185, 127 ], \
  [ 2, 251, 156, 55 ], \
  [ 3, 156, 159, 191 ], \
  [ 4, 102, 214, 238 ], \
  [ 5, 251, 255, 252 ], \
  [ 6, 47, 14, 0 ], \
  [ 0, 243, 88, 73 ], \
  [ 1, 62, 179, 123 ], \
  [ 2, 251, 150, 62 ], \
  [ 3, 163, 153, 191 ], \
  [ 4, 102, 214, 234 ], \
  [ 5, 243, 253, 248 ], \
  [ 6, 39, 11, 0 ], \
  [ 0, 251, 91, 73 ], \
  [ 1, 70, 179, 130 ], \
  [ 2, 251, 150, 59 ], \
  [ 3, 149, 146, 187 ], \
  [ 4, 102, 211, 234 ], \
  [ 5, 243, 253, 255 ], \
  [ 6, 39, 3, 0 ]]

knn_k = 8
dataset_count = 6 * 7
no_col = 7

def knn(r,g,b):
    colourArray=[]
    colourArray.append(r)
    colourArray.append(g)
    colourArray.append(b)
    closest_neighbour_dist=[]
    neighbour_index=[]
    for i in range(knn_k):
        closest_neighbour_dist.append(450)
        neighbour_index.append(0)

    for i in range(dataset_count):
        euclidean = math.sqrt(pow((colourArray[0] - dataset[i][1]),2) + pow((colourArray[1] - dataset[i][2]),2) + pow((colourArray[2] - dataset[i][3]),2))
        for j in range(knn_k-1,-1,-1):
            if euclidean < closest_neighbour_dist[j]:
                for k in range(j):
                    closest_neighbour_dist[k] = closest_neighbour_dist[k + 1]
                    neighbour_index[k] = neighbour_index[k + 1]
                closest_neighbour_dist[j] = euclidean
                neighbour_index[j] = i
                break

    neighbour_color = []
    for i in range(no_col):
        neighbour_color.append(0)
    for i in range(knn_k):
        neighbour_color[dataset[neighbour_index[i]][0]] += 1
    closest_color = 0
    for i in range(1,no_col):
        if neighbour_color[i] > neighbour_color[closest_color]:
            closest_color = i
    return closest_color

correct=0
total=0
with open("Red.txt","r") as f:
    red=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 0:
            correct += 1
            red+=1
        total += 1
with open("Green.txt","r") as f:
    green=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 1:
            correct += 1
            green+=1
        total += 1
with open("Orange.txt","r") as f:
    orange=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 2:
            correct += 1
            orange+=1
        total += 1
with open("Purple.txt","r") as f:
    purple=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 3:
            correct += 1
            purple+=1
        total += 1
with open("Blue.txt","r") as f:
    blue=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 4:
            correct += 1
            blue+=1
        total += 1
with open("White.txt","r") as f:
    white=0
    lines = f.read().strip().split("\n")
    arrayed=[]
    for a in lines:
        arrayed.append(a.split("\t"))
    for a in arrayed:
        i = knn(int(a[0]),int(a[1]),int(a[2]))
        if i == 5:
            correct += 1
            white+=1
        total += 1
    
print("Correct predictions:",correct)
print("Total samples:",total)
print("Red:",red, "out of 9")
print("Green:",green, "out of 9")
print("Orange:",orange, "out of 9")
print("Purple:",purple, "out of 9")
print("Blue:",blue, "out of 9")
print("White",white, "out of 5")