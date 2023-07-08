# OBC-deployment F' project

This project was auto-generated by the F' utility tool. 

F´ (F Prime) is a component-driven framework that enables rapid development and deployment of spaceflight and other embedded software applications.
**Please Visit the F´ Website:** https://nasa.github.io/fprime/.

# How to use:
0. Work in the container

VS code: build and reopen in container

2. /OBC-deployment:
```
fprime-util generate
```
2. /OBC-deployment/Deployment
```
fprime-util generate raspberrypi
fprime-util build raspberrypi
```
3. Connect the board and the ground station computer to the same network

4. /OBC-deployment/Deployment
```
fprime-gds -n --dictionary build-artifacts/raspberrypi/Deployment/dict/DeploymentTopologyAppDictionary.xml
```
5. Copy executable over to the board's home directory
in /OBC-deployment/Deployment
```
scp build-artifacts/raspberrypi/Deployment/bin/Deployment <USER_ACCOUNT>@<RASPBERRY_PI_IP_ADDRESS>:~
```
6. Running executable on the raspberry pi
```
ssh <USER_ACCOUNT>@<RASPBERRY_PI_IP_ADDRESS>
./Deployment -a <GROUND_STATION_COMPUTER_IP> -p 50000
```
