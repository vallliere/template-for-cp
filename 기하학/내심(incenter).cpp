pid cal_incenter(pid a, pid b, pid c)
{
    dl x, y, ra, rb, rc;
    ra = sqrt((b.first - c.first) * (b.first - c.first) + (b.second - c.second) * (b.second - c.second));
    rb = sqrt((c.first - a.first) * (c.first - a.first) + (c.second - a.second) * (c.second - a.second));
    rc = sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
    x = (ra * a.first + rb * b.first + rc * c.first) / (ra + rb + rc);
    y = (ra * a.second + rb * b.second + rc * c.second) / (ra + rb + rc);
    return {x, y};
}
