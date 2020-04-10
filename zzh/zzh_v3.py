import time

def search(cur):
    global graph
    global temp
    global vis
    t = []
    if cur[-1] in graph:
        g = graph[cur[-1]]
    else:
        return
    for i in g:
        t.append([cur[-1], i])
    for j in t:
        if len(cur)>1 and j[1] in layer[cur[0]] and j[1] not in cur:
            x = cur+[j[1]]
            temp.append(x)
        if len(cur) < 6 and j[1] not in cur:
            search(cur+[j[1]])
        else:
            continue

def get_res():
    global graph
    global temp
    global x1
    # 储存答案
    res = []
    # 用一个set判断是否有重复
    sres = []
    for g in graph:
        while graph[g]:
            i = [g, graph[g][0]]
            graph[g].pop(0)
            temp = []
            cur = i
            search(cur)
            for j in temp:
                # res.append(j)
                if set(j) not in sres:
                    sres.append(set(j))
                    if len(j) > 2 and len(j) < 8:
                        if j[0] != min(j):
                            i = j.index(min(j))
                            j = j[i:] + j[:i]
                        res.append(j)
    res.sort(key=lambda x:(len(x), [i for i in x]))
    print(len(res))
    # print(res)
    print('time:', time.time() - x1)
    # 输出答案
    with open("result_data.txt", 'w') as f:
        f.write(str(len(res)) + '\n')
        for line in res:
            for i in range(len(line) - 1):
                f.write(str(line[i]) + ',')
            f.write(str(line[-1]) + '\n')

x1 = time.time()
# 读取文件
data = []
with open("16test_data.txt", 'r') as f:
    for line in f:
        line = line[:-1].split(',')[:-1]
        for i in range(len(line)):
            line[i] = int(line[i])
        data.append(line)
data.sort(key=lambda x:[x[0], x[1]])
# print(data)
rd = {}
cd = {}
layer = {}
for i in data:
    if i[1] not in layer:
        layer[i[1]]={i[0]:0}
    else:
        layer[i[1]] = {**layer[i[1]], **{i[0]:0}}
    if i[1] not in cd:
        cd[i[1]] = 0
    if i[0] not in rd:
        rd[i[0]] = 0
i = 0
while i < len(data):
    if data[i][0] not in cd:
        data.remove(data[i])
    elif data[i][1] not in rd:
        data.remove(data[i])
    else:
        i += 1
graph = {}
for i in data:
    if i[0] not in graph:
        graph[i[0]] = [i[1]]
    else:
        graph[i[0]].append(i[1])

get_res()
