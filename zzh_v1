import time
x1 = time.time()

# 深度优先搜索
# graph为转账记录
# visited为已转账过的账户
# cur为现在搜索的记录
# 思路：1、从记录表的每个位置开始搜索，首先找出所有以当前搜索记录的最后一个账户为转账账户的转账记录，记为t；
#       2、然后判断，如果t中某个转账记录又回到了cur的起始点，那么就找到了一个环，否则进入递归
def search(graph, visited, cur):
    t = []
    for i in graph:
        if i[0] == cur[-1] and i[0] not in visited:
            t.append(i)
    # print(t)
    if t:
        for j in t:
            if j[1] == cur[0]:
                temp.append(cur)
            else:
                search(graph, visited + [j[0]], cur+[j[1]])

# 读取文件
data = []
with open("test_data.txt",'r') as f:
    for line in f:
        line = line[:-1].split(',')[:-1]
        for i in range(len(line)):
            line[i] = int(line[i])
        data.append(line)
graph = data

# 储存答案
res = []
# 用一个set判断是否有重复
sres = []
for i in graph:
    temp = []
    visited = [i[0]]
    cur = i
    search(graph, visited, cur)
    # print(temp)
    # 一次搜索结束后，temp中的值是以本次搜索开始位置为起点的所有环，和之前有重复，需要去重，再按题目要求排序。
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
print(res)

# 输出答案
with open("test_ressult.txt",'w') as f:
    f.write(str(len(res)) + '\n')
    for line in res:
        for i in range(len(line)-1):
            f.write(str(line[i])+',')
        f.write(str(line[-1]) + '\n')
print('time:',time.time()-x1)
