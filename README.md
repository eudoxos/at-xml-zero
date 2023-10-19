[trsf.cpp](/trsf.cpp) takes XML calibration file and x,z coordinates. It uses `AT::cx::c3d::Calib::sensor2world` to compute world coordinates.

[c6-mcs-4090-noop.xml](/c6-mcs-4090-noop.xml) was hand-edited to set all transformation steps to identity (following [3D Calibration model](http://docs.automationtechnology.de/software/cxsdk/concepts_3d/?h=#camera_model).

# Doubled coordinate mystery

The `sensor2world` routine consistently returns both coordinates doubled:

```
$ ./trsf c6-mcs-4090-noop.xml 100 10
Loaded: c6-mcs-4090-noop.xml
Original point: 100, 0, 10
Transformed point: 200, 0, 20

$ ./trsf c6-mcs-4090-noop.xml 1 2
Loaded: c6-mcs-4090-noop.xml
Original point: 1, 0, 2
Transformed point: 2, 0, 4
```

Where is the factor of two coming from?

When changing Principal point (`<cp>`; first translation in the sequence) to non-zero, it can be seen that the factor of two is applied only *afterwards*; e.g. with `<cp>10 20</cp>` (`(1-10=-9,3-20=-17)×2=(-18,-34)`):
```
$ ./trsf c6-mcs-4090-noop.xml 1 3
Loaded: c6-mcs-4090-noop.xml
Original point: 0, 0, 0
Transformed point: -18, 0, -34
```

With homography set to `0.5,0,0; 0,0.5,0; 0,0,1`, or equivalently `1,0,0; 0,1,0; 0,0,2` (instead of identity matrix), I get the result which looks correct (no more multiplication by 2):

```
$ ./trsf c6-mcs-4090-noop.xml 23 333
Loaded: c6-mcs-4090-noop.xml
Original point: 23, 0, 333
Transformed point: 23, 0, 333
```

I suspect AT's SDK has the unexpected factor of 2 somewhere in the homography computation — by accident, or just not documented. (The only other correction which could be scaling the points later is `C`, but the linear terms are very close to 1 in the calibration data, non-linear terms being close to zero.)

# Docs bug: division lens model

[AT docs](http://docs.automationtechnology.de/software/cxsdk/concepts_3d/?h=#calib_step5_1) spell the division lens model incorrectly as $$\begin{bmatrix}u \\ v\end{bmatrix}=\frac{1}{1+k_1 r^2 +k_2 r^4}\begin{bmatrix}u_c \\ v_c\end{bmatrix}$$

(with $L=\{k_1,k_2\}$). The implementation follows this formula instead:

$$\begin{bmatrix}u \\ v\end{bmatrix}=(1+\frac{k_1}{2} r^2 +\frac{k_2}{2} r^4}\begin{bmatrix}u_c \\ v_c\end{bmatrix}$$
