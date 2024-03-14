ll year_to_day(ll year, ll month, ll day)
{
    ll ret;
    ret = year * 365;
    ret += year / 4 + 1;
    if (year % 4 == 0)
        ret--;
    ret -= year / 100 + 1;
    if (year % 100 == 0)
        ret++;
    ret += year / 400 + 1;
    if (year % 400 == 0)
        ret--;
    vector<ll> month_day({0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        month_day[2]++;
    for (int i = 1; i < month; i++)
        ret += month_day[i];
    ret += day;
    return ret;
}
