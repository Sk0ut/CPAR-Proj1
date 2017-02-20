N = 5
a = [1 for i in range(N*N)]
b = [i+1 for i in range(N*N)]
c = [sum([a[i*N + k] * b[k*N + j] for k in range(N)]) for i in range(N) for j in range(N)]


for i in range(N):
  for j in range(N):
    print(str(c[i*N+j]), end=' ')
  print()
