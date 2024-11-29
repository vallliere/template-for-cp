pil exgcd(ll a, ll b)
{ // a * x + b * y = 1 -> return {x, y}
    pil ret;
    if (b == 0)
        return {1, 0};
    ret = exgcd(b, a % b);
    return {ret.second, ret.first - a / b * ret.second};
}
