
def f(node,mid):
  r = 0.5 * (node ** 2 - (node % mid) * (node / mid + 1) ** 2 - (mid - (node % mid)) * (node / mid) ** 2)
  print node, mid, r
  return r

def clique(node, edge):
    #
    # Write your code here.
    #
    low = 0
    high = node
    while low + 1 < high:
        mid = (low + high) / 2
        #turan = 0.5 * (node ** 2 - (node % mid) * (node / mid + 1) ** 2 - (mid - (node % mid)) * (node / mid) ** 2)
        turan = f(node, mid)
        if turan < edge:
            low = mid
        else:
            high = mid
    return high

print clique(19,166)
print clique(3,2)

