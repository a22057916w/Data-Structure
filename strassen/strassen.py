import numpy as np

def split(matrix):
    row, col = matrix.shape
    row2, col2 = row // 2, col // 2   # x//y = floor(x/y)

    # | a b |
    # | c d |
    # return a, b, c, d
    return matrix[:row2, :col2], matrix[:row2, col2:], matrix[row2:, :col2], matrix[row2:, col2:]

def strassen(A, B):

    # Base case
    if len(A) <= 2:
        return np.matmul(A, B)

    # Splitting the matrices into quadrants
    a, b, c, d = split(A)
    e, f, g, h = split(B)

    # Computing the 7 products, recursively (p1, p2...p7)
    p1 = strassen(a+d, e+h)
    p2 = strassen(b-d, g+h)
    p3 = strassen(c-a, e+f)
    p4 = strassen(d, g-e)
    p5 = strassen(a+b, h)
    p6 = strassen(c+d, e)
    p7 = strassen(a, f-h)

    # Computing the values of the 4 quadrants
    c11 = p1 + p2 + p4 - p5
    c12 = p5 + p7
    c21 = p4 + p6
    c22 = p1 + p3 + p6 - p7

    # Combining the 4 quadrants into a single matrix by stacking horizontally and vertically.
    C = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))
    return C

if __name__ == "__main__":
    A = np.array([[1,1,1,1], [2,2,2,2], [3,3,3,3], [2,2,2,2]])
    B = np.array([[1,1,1,1], [2,2,2,2], [3,3,3,3], [2,2,2,2]])
    print(strassen(A, B))


# Reference:
#     https://www.youtube.com/watch?v=OSelhO6Qnlc (簡單清楚的教學)
#     https://www.geeksforgeeks.org/strassens-matrix-multiplication/ (example)
#     https://medium.com/%E7%84%A1%E8%A9%A9%E7%9A%84%E7%BE%8A%E5%9C%88/strassen-algorithm-%E7%94%B1%E4%BE%86%E7%8C%9C%E6%83%B3-%E8%A8%98%E6%86%B6%E6%96%B9%E6%B3%95-662ae3b5ad9b (公式紀這個)
