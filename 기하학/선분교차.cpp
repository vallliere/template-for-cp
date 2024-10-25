
bool check_cross(pair<int64_t, int64_t> line1_s, pair<int64_t, int64_t> line1_e, pair<int64_t, int64_t> line2_s, pair<int64_t, int64_t> line2_e)
{
    int64_t x, y;
    function<int64_t(pair<int64_t, int64_t>, pair<int64_t, int64_t>, pair<int64_t, int64_t>)> check_cross_ccw = [&](pair<int64_t, int64_t> a, pair<int64_t, int64_t> b, pair<int64_t, int64_t> c) {
        int64_t x1, y1, x2, y2, ke;
        x1 = b.first - a.first, y1 = b.second - a.second;
        x2 = c.first - a.first, y2 = c.second - a.second;
        ke = x1 * y2 - x2 * y1;
        ke = (ke > 0) - (ke < 0);
        if (ke == 0) {
            x1 = min(a.first, b.first), x2 = max(a.first, b.first);
            y1 = min(a.second, b.second), y2 = max(a.second, b.second);
            if (c.first >= x1 && c.first <= x2 && c.second >= y1 && c.second <= y2)
                return ke;
            ke = 1;
        }
        return ke;
    };
    x = check_cross_ccw(line1_s, line1_e, line2_s) * check_cross_ccw(line1_s, line1_e, line2_e);
    y = check_cross_ccw(line2_s, line2_e, line1_s) * check_cross_ccw(line2_s, line2_e, line1_e);
    if ((x == -1 && y == -1) || x * y == 0)
        return 1;
    return 0;
}
