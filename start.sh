cd /sys/devices/platform/bone_capemgr
echo cape-universaln > slots

config-pin p8.11 qep
config-pin p8.12 qep
	
config-pin p9.27 qep
config-pin p9.92 qep

config-pin P9.15 gpio
config-pin P9.13 gpio

cd /sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip3
echo 0 > export
echo 1 > export