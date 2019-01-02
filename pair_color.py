def main():
  while True:
    w, h = map(int, input().split())
    if not w:
      break
   
    n = int(input())
   
    xlst = [0, w - 1]
    ylst = [0, h - 1]
    plst = []
   
    for i in range(n):
      x1, y1, x2, y2 = map(int, input().split())
      plst.append([x1,y1,x2 - 1,y2 - 1])
      xlst.append(x1)
      xlst.append(x2)
      xlst.append(x2 - 1)
      ylst.append(y1) 
      ylst.append(y2)
      ylst.append(y2 - 1)
   

    xlst = list(set(xlst))
    ylst = list(set(ylst))
    xlst.sort()
    ylst.sort()

    print(xlst)
    print(ylst)
   
    xdic = {}
    ydic = {}
   
    for i, v in enumerate(xlst):
      xdic[v] = i
    for i, v in enumerate(ylst):
      ydic[v] = i
     
    neww = xdic[xlst[-1]]
    newh = ydic[ylst[-1]]
 
    print(xdic)
    print(ydic)
    print(plst)
    painted = [[1] * (newh + 2)]
    for _ in range(neww):
      painted.append([1] + [0] * newh +  [1])
    painted.append([1] * (newh + 2))  
   
    for p in plst:
      x1, y1, x2, y2 = p
      x1, y1, x2, y2 = xdic[x1] + 1, ydic[y1] + 1, xdic[x2] + 1, ydic[y2] + 1
      for x in range(x1, x2 + 1):
        for y in range(y1, y2 + 1):
          painted[x][y] = 1
     
    stack = []
    app = stack.append
    pp = stack.pop
    direct = ((-1, 0), (1, 0), (0, -1), (0, 1))
    ans = 0
 
    for x in range(1, neww + 1):
      for y in range(1, newh + 1):
        if not painted[x][y]:
          ans += 1
          painted[x][y] = 1
          app((x,y))
          
          #幅優先探索w2
          while stack:
            px, py = pp()
            for dx, dy in direct:
              tx, ty = px + dx, py + dy
              if not painted[tx][ty]:
                painted[tx][ty] = 1
                app((tx,ty))
    print(ans)
 
main()