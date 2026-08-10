def partition(items, element):
    i = 0

    for j in range(len(items) - 1):
        if items[j] == element:
            items[j], items[-1] = items[-1], items[j]
        
        if items[j] < element:
            items[i], items[j] = items[j], items[i]
            i += 1
        
    items[i], items[-1] = items[-1], items[i]

    return i

def median_index(n):
    if n % 2:
        return n // 2;
    else:
        return n // 2 - 1;

def select(items, n):

    if len(items) <= 1:
        return items[0]
    
    medians = []

    for i in range(0, len(items), 5):
        group = sorted(items[i:i+5])
        items[i:i+5] = group
        median = group[median_index(len(group))]
        medians.append(median)
    
    pivot = select(medians, median_index(len(medians)))
    index = partition(items, pivot)

    if n == index:
        return items[index]
    elif n < index:
        return select(items[:index], n)
    else:
        return select(items[index + 1:], n - index - 1)

A = [0, 3, 2, 8, 9, 2, 3, 3, 8, 9, 0, 2, 4, 5, 7, 0, 2, 7, 7, 9, 0, 3, 7, 9, 9]
print(select(A, 4))
print(sorted(A))