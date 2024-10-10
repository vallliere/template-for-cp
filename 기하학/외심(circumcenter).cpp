pid cal_circumcenter(pid a, pid b, pid c)
{
    dl x, y, d;
    d = (a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second)) * 2;
    x = (a.first * a.first + a.second * a.second) * (b.second - c.second) + (b.first * b.first + b.second + b.second) * (c.second - a.second) + (c.first * c.first + c.second * c.second) * (a.second - b.second);
    y = (a.first * a.first + a.second * a.second) * (c.first - b.first) + (b.first * b.first + b.second + b.second) * (a.first - c.first) + (c.first * c.first + c.second * c.second) * (b.first - a.first);
    return {x / d, y / d};
}
