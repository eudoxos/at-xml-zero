[trsf.cpp](/trsf.cpp) takes XML calibration file and x,z coordinates. It uses `AT::cx::c3d::Calib::sensor2world` to compute world coordinates.

[c6-mcs-4090-noop.xml](/c6-mcs-4090-noop.xml) was hand-edited to set all transformation steps to identity (following [3D Calibration model](http://docs.automationtechnology.de/software/cxsdk/concepts_3d/?h=#camera_model). Yet, it consistently returns both coordinates doubled:


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
