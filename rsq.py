class RSQ():
	def __init__(self,n):
		self.dat = [0 for _ in range(n*2-1)]
		#index nのノードからのアクセス:
		#親ノード : (n-1)//2
		#子ノード : (2n+1) , (2n+2)
		self.n = n

	def update (self,node_index,value):
		""" indexの値をvalueに変更する """
		index = node_index + (self.n-1) #node_indexを実際のdotのindexに変換
		self.dat[index] += value

		#再帰的に親ノードの値も変更していく
		while index > 0 :
			index = (index - 1) // 2				 #子ノードにうつって
			self.dat[index] = self.dat[index*2+1] + self.dat[index*2+2] #二つの子ノードを比較

	def querry (self,left,right,nowNode,nowLeft,nowRight):
		"""[left,right):探索範囲,noeNode:現在のノード,[nowLeft,nowRight):現在のノードの範囲"""

		# 範囲がかぶっていない
		if nowRight < left or nowLeft > right:
			return 0

		# 現在の探索範囲が全体の範囲に包含されている
		if left <= nowLeft and nowRight <= right:
			return self.dat[nowNode]

		# さらに子ノードを見ないとわからない
		else:
			value_left = self.querry(left,right,2*nowNode+1,nowLeft,(nowLeft+nowRight)//2)
			value_right = self.querry(left,right,2*nowNode+2,(nowLeft+nowRight)//2+1,nowRight)
			return (value_left + value_right)

	def DEBUG_dat(self):
		print(self.dat)


if __name__ == "__main__":
	n ,q  = map(int,input().split(" "))
	result = []

	for i in range(1,20):
		if 2 ** i >= n:
			min_pow2 = 2 **  i
			break

	tree = SegmentTree(min_pow2)

	for i in range(q):
		com,x,y = map(int,input().split(" "))
		if com == 0:
			tree.update(x-1,y)
		else:
			result.append(tree.querry(x-1,y-1,0,0,min_pow2-1))

	for ans in result:
		print(ans)


