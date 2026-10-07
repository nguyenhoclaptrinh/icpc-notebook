// point là phân số
bool pointInLaser(point M, point A, point B)
{
    db Ax = (db) A.x.fi / A.x.se,
       Ay = (db) A.y.fi / A.y.se,
       Bx = (db) B.x.fi / B.x.se,
       By = (db) B.y.fi / B.y.se,
       Mx = (db) M.x.fi / M.x.se,
       My = (db) M.y.fi / M.y.se;

    db t1 = Mx - Ax,
       t2 = Bx - Ax,
       t3 = My - Ay,
       t4 = By - Ay;

    return ((db) t1*t2 >= 0.0 && (db) t3*t4 >= 0.0);
}
