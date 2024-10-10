pid cal_intersection(pid v1, pid v2, pid v3, pid v4)
{
    dl x, y, d;
    d = (v1.first - v2.first) * (v3.second - v4.second) - (v1.second - v2.second) * (v3.first - v4.first);
    x = (v1.first * v2.second - v1.second * v2.first) * (v3.first - v4.first) - (v1.first - v2.first) * (v3.first * v4.second - v3.second * v4.first);
    y = (v1.first * v2.second - v1.second * v2.first) * (v3.second - v4.second) - (v1.second - v2.second) * (v3.first * v4.second - v3.second * v4.first);
    assert(d > 1e-9 || d < -1e-9);
    return {x / d, y / d};
}
