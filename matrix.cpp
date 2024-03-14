template <typename T>
struct matrix {
    matrix(int row, int col)
    {
        _row = row, _col = col;
        _arr.resize(_row, vector<T>(_col));
    }
    int row() { return _row; }
    int col() { return _col; }
    vector<vector<T>> mat_arr() { return _arr; }
    void mod_on(ll va) { _mod_switch = true, _mod_num = va, modulo(); }
    void mod_off() { _mod_switch = false; }
    ll mod_check() { return _mod_switch ? _mod_num : -1; }
    void identity()
    {
        int i;
        assert(_row == _col);
        clear();
        for (i = 0; i < _row; i++)
            _arr[i][i] = 1;
    }
    void clear()
    {
        int i, p;
        for (i = 0; i < _row; i++)
            for (p = 0; p < _col; p++)
                _arr[i][p] = 0;
    }
    void change(int x, int y, T va)
    {
        assert(x >= 0 && x < _row && y >= 0 && y < _col);
        _arr[x][y] = va;
        if (_mod_switch)
            _arr[x][y] %= _mod_num;
    }
    T* find(int x, int y)
    {
        assert(x >= 0 && x < _row && y >= 0 && y < _col);
        return &_arr[x][y];
    }
    void init(vector<vector<T>> tem_arr)
    {
        assert(tem_arr.size() == _row && tem_arr[0].size() == _col);
        _arr = tem_arr;
        if (_mod_switch)
            modulo();
    }
    matrix pow(ll va)
    {
        matrix pw(_row, _col), ret(_row, _col);
        pw._arr = _arr;
        ret.identity();
        if (_mod_switch) {
            ret.mod_on(_mod_num);
            pw.mod_on(_mod_num);
        }
        while (va > 0) {
            if (va % 2 == 1)
                ret = pw * ret;
            va /= 2;
            pw = pw * pw;
        }
        return ret;
    }
    void print()
    {
        int i, p;
        for (i = 0; i < _row; i++) {
            for (p = 0; p < _col; p++)
                cout << _arr[i][p] << " ";
            cout << "\n";
        }
    }
    matrix operator+(const matrix& va) const
    {
        int i, p;
        assert(_row == va._row && _col == va._col);
        matrix ret(_row, _col);
        for (i = 0; i < _row; i++)
            for (p = 0; p < va._col; p++)
                ret._arr[i][p] = _arr[i][p] + va._arr[i][p];
        if (_mod_switch && va._mod_switch) {
            assert(_mod_num == va._mod_num);
            ret.mod_on(_mod_num);
        }
        return ret;
    }
    matrix operator-(const matrix& va) const
    {
        int i, p;
        assert(_row == va._row && _col == va._col);
        matrix ret(_row, _col);
        for (i = 0; i < _row; i++)
            for (p = 0; p < va._col; p++)
                ret._arr[i][p] = _arr[i][p] - va._arr[i][p];
        if (_mod_switch && va._mod_switch) {
            assert(_mod_num == va._mod_num);
            ret.mod_on(_mod_num);
        }
        return ret;
    }
    matrix operator*(const matrix& va) const
    {
        int i, p, q;
        assert(_col == va._row);
        matrix ret(_row, va._col);
        for (i = 0; i < _row; i++)
            for (p = 0; p < va._col; p++)
                for (q = 0; q < _col; q++)
                    ret._arr[i][p] += _arr[i][q] * va._arr[q][p];
        if (_mod_switch && va._mod_switch) {
            assert(_mod_num == va._mod_num);
            ret.mod_on(_mod_num);
        }
        return ret;
    }

   private:
    bool _mod_switch = false;
    int _row, _col;
    ll _mod_num;
    vector<vector<T>> _arr;
    void modulo()
    {
        int i, p;
        for (i = 0; i < _row; i++)
            for (p = 0; p < _col; p++)
                _arr[i][p] = (_arr[i][p] % _mod_num + _mod_num) % _mod_num;
    }
};
