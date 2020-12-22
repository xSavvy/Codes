## IMU Wheel 融合 
这是是采用比较简单的方式<br>
IMU的陀螺仪输出的角速度结合轮式计的线速度进行融合<br>
这里假设IMU和轮式计之间是通过$ R^(imu)_w$ 进行固练<br>
$T$
$V_{wheel} = $ 代表轮式计输出的速度<br>
$V_imu = R^{imu}_{wheel}V_{wheel}$