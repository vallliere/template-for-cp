pil exgcd(ll a, ll b)
{
    pil ret;
    if (b == 0)
        return {1, 0};
    ret = exgcd(b, a % b);
    return {ret.second, ret.first - a / b * ret.second};
}
