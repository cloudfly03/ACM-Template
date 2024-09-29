cin >> d >> _x1 >> _y1 >> _x2 >> _y2;
cout << fixed << setprecision(12);
ld radius = 0.5 * d * d;

ld base = sqrt(1 + (_y2 - _y1) * (_y2 - _y1) / ((_x2 - _x1) * (_x2 - _x1)));
base *= sqrt((_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2)) / 2;

ld _x3 = base + (_x2 - _x1) * (_y1 + _y2) / (2 * (_y2 - _y1)) - _y1 + _x1 * (_y2 - _y1) / (_x2 - _x1) + (_y1 + _y2) / 2;
ld _x4 = -base + (_x2 - _x1) * (_y1 + _y2) / (2 * (_y2 - _y1)) - _y1 + _x1 * (_y2 - _y1) / (_x2 - _x1) + (_y1 + _y2) / 2;
_x3 /= ((_y2 - _y1) / (_x2 - _x1) + (_x2 - _x1) / (_y2 - _y1));
_x4 /= ((_y2 - _y1) / (_x2 - _x1) + (_x2 - _x1) / (_y2 - _y1));
ld _y3 = -(_x2 - _x1) / (_y2 - _y1) * (_x3 - (_x1 + _x2) / 2) + (_y1 + _y2) / 2;
ld _y4 = -(_x2 - _x1) / (_y2 - _y1) * (_x4 - (_x1 + _x2) / 2) + (_y1 + _y2) / 2;

ld d1, d2, d3, d4;
ld minx1, miny1;
ld minx2, miny2;
ld minx3, miny3;
ld minx4, miny4;
bool f1, f2, f3, f4;
f1 = f2 = f3 = f4 = 0;
d1 = _x1 * _x1 + _y1 * _y1;
d2 = _x2 * _x2 + _y2 * _y2;
d3 = _x3 * _x3 + _y3 * _y3;
d4 = _x4 * _x4 + _y4 * _y4;

if (abs(_x1 - _x2) == abs(_y1 - _y2)) {
    if (min(_x1, _x2) < 0 && 0 < max(_x1, _x2)) {
        d1 = min(abs(_y1), abs(_y2));
        _x1 = 0, _y1 = d1;
        d1 *= d1;
        d2 = d3 = d4 = INF;
    }
    else if (min(_y1, _y2) < 0 && 0 < max(_y1, _y2)) {
        d1 = min(abs(_x1), abs(_x2));
        d2 = d3 = d4 = INF;
        _x1 = d1, _y1 = 0;
        d1 *= d1;
    }
}
else {
    minx1 = (_x1 * (_y1 - _y3) / (_x1 - _x3) - _y1) / ((_x1 - _x3) / (_y1 - _y3) + (_y1 - _y3) / (_x1 - _x3));
    if (minx1 < max(_x1, _x3) && minx1 > min(_x1, _x3)) {
        d1 = abs(-_x1 * (_y1 - _y3) / (_x1 - _x3) + _y1) / sqrt(1 + (_y1 - _y3) * (_y1 - _y3) / ((_x1 - _x3) * (_x1 - _x3)));
        miny1 = -(_x1 - _x3) / (_y1 - _y3) * minx1;
        f1 = 1;
    }
    minx2 = (_x1 * (_y1 - _y4) / (_x1 - _x4) - _y1) / ((_x1 - _x4) / (_y1 - _y4) + (_y1 - _y4) / (_x1 - _x4));
    if (minx2 <max(_x1, _x4) && minx2>min(_x1, _x4)) {
        d2 = abs(-_x1 * (_y1 - _y4) / (_x1 - _x4) + _y1) / sqrt(1 + (_y1 - _y4) * (_y1 - _y4) / ((_x1 - _x4) * (_x1 - _x4)));
        miny2 = -(_x1 - _x4) / (_y1 - _y4) * minx2;
        f2 = 1;
    }
    minx3 = (_x2 * (_y2 - _y3) / (_x2 - _x3) - _y2) / ((_x2 - _x3) / (_y2 - _y3) + (_y2 - _y3) / (_x2 - _x3));
    if (minx3 <max(_x2, _x3) && minx3>min(_x2, _x3)) {
        d3 = abs(-_x2 * (_y2 - _y3) / (_x2 - _x3) + _y2) / sqrt(1 + (_y2 - _y3) * (_y2 - _y3) / ((_x2 - _x3) * (_x2 - _x3)));
        miny3 = -(_x2 - _x3) / (_y2 - _y3) * minx3;
        f3 = 1;
    }
    minx4 = (_x2 * (_y2 - _y4) / (_x2 - _x4) - _y2) / ((_x2 - _x4) / (_y2 - _y4) + (_y2 - _y4) / (_x2 - _x4));
    if (minx4 <max(_x2, _x4) && minx4>min(_x2, _x4)) {
        d4 = abs(-_x2 * (_y2 - _y4) / (_x2 - _x4) + _y2) / sqrt(1 + (_y2 - _y4) * (_y2 - _y4) / ((_x2 - _x4) * (_x2 - _x4)));
        miny4 = -(_x2 - _x4) / (_y2 - _y4) * minx4;
        f4 = 1;
    }

    if (f1) {
        _x1 = minx1;
        _y1 = miny1;
    }
    if (f2) {
        _x2 = minx2;
        _y2 = miny2;
    }
    if (f3) {
        _x3 = minx3;
        _y3 = miny3;
    }
    if (f4) {
        _x4 = minx4;
        _y4 = miny4;
    }
}

if (radius <= min({ d1,d2,d3,d4 })) {
    cout << sqrt(radius) << endl;
}
else {
    ld dmin = min({ d1,d2,d3,d4 });
    ld x, y;

    if (dmin == d1) {
        x = _x1, y = _y1;
    }
    else if (dmin == d2) {
        x = _x2, y = _y2;
    }
    else if (dmin == d3) {
        x = _x3, y = _y3;
    }
    else {
        x = _x4, y = _y4;
    }

    ld a1, b1, a2, b2;

    if (y < x && y > -x) {
        a1 = d / 2, b1 = d / 2;
        a2 = d / 2, b2 = -d / 2;
    }
    else if (y < x && y < -x) {
        a1 = -d / 2, b1 = -d / 2;
        a2 = d / 2, b2 = -d / 2;
    }
    else if (y > -x && y > x) {
        a1 = d / 2, b1 = d / 2;
        a2 = -d / 2, b2 = d / 2;
    }
    else {
        a1 = -d / 2, b1 = d / 2;
        a2 = -d / 2, b2 = d / 2;
    }

    ld X = (a1 - x) * (a1 + x) / (2 * (b1 - y)) + (b1 + y) / 2 - ((a2 - x) * (a2 + x) / (2 * (b2 - y)) + (b2 + y) / 2);
    X /= ((a1 - x) / (b1 - y) - (a2 - x) / (b2 - y));
    ld Y = -(a2 - x) / (b2 - y) * (X - (a2 + x) / 2) + (b2 + y) / 2;

    ld ans = sqrt((X - x) * (X - x) + (Y - y) * (Y - y));
    cout << ans << endl;
}