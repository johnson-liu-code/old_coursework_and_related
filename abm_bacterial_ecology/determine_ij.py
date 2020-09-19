







def determine_ij(i, j, x_len, y_len):
    # Compute the i, j coordinates of neighboring cells (includes wrap-around on lattice).
    if i == 0:
        i_up = 1
        i_down = x_len - 1
    elif i == x_len - 1:
        i_up = 0
        i_down = i - 1
    else:
        i_up = i + 1
        i_down = i - 1
    if j == 0:
        j_left = y_len - 1
        j_right = 1
    elif j == y_len - 1:
        j_left = j - 1
        j_right = 0
    else:
        j_left = j - 1
        j_right = j + 1

    return i_up, i_down, j_left, j_right
