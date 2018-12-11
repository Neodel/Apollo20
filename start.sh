cd /sys/devices/platform/bone_capemgr
echo cape-universaln > slots

cd /sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip3
echo 0 > export
echo 1 > export
cd pwm0
echo 500000 > period
echo 250000 > duty_cycle
echo 1 > enable

cd ../pwm1
echo 500000 > period
echo 250000 > duty_cycle
echo 1 > enable

cd /sys/class/gpio/gpio48/
echo out > direction
echo 0 > value

cd /sys/class/gpio/gpio31/
echo out > direction
echo 0 > value

config-pin  P9.14 pwm
config-pin  P9.16 pwm

config-pin p8.11 qep
config-pin p8.12 qep
	
config-pin p9.27 qep
config-pin p9.92 qep

config-pin P9.15 gpio
config-pin P9.13 gpio

