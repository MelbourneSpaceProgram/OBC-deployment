# OBC-deployment F' project

This project was auto-generated by the F' utility tool. 

F´ (F Prime) is a component-driven framework that enables rapid development and deployment of spaceflight and other embedded software applications.
**Please Visit the F´ Website:** https://nasa.github.io/fprime/.

## Clone This Repository
```
git clone --recurse-submodules https://github.com/MelbourneSpaceProgram/OBC-deployment.git
```

## Work in the Docker Container (VS code)
0. Install and run Docker
1. VS code: Install the Dev Containers extension
2. VS code: Open the cloned folder, CMD+shift+P (For Windows: Ctrl+Shift+P), type: Dev Containers: Reopen in Container
3. VS code: After finishing building the container, create a new terminal in VS code

## How to use (A): Native
1. Work in the Docker container

2. In /OBC-deployment:
```
fprime-util generate
fprime-util build
```
2. In /OBC-deployment/Deployment
```
fprime-util generate 
fprime-util build
```
3. Open F' GDS control page
   
   In /OBC-deployment/Deployment
  ```
  fprime-gds
  ```

## How to use (B): Cross-Compiling for Raspberry pi
1. Work in the Docker container

2. In /OBC-deployment:
```
fprime-util generate
fprime-util build
```
2. In /OBC-deployment/Deployment
```
fprime-util generate raspberrypi
fprime-util build raspberrypi
```
3. Connect the board and the ground station computer to the same network

4. Open F' GDS control page

   In /OBC-deployment/Deployment (do not run in vs code terminal)
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

## Start Developing!
For detailed tutorials, refer to 

HelloWorld Tutorial: https://github.com/fprime-community/fprime-tutorial-hello-world/blob/main/docs/HelloWorld.md

MathComponent Tutorial (Custom Ports and Types): [https://nasa.github.io/fprime/Tutorials/MathComponent/Tutorial.html](https://nasa.github.io/fprime/v2.0.0/Tutorials/MathComponent/Tutorial.html)https://nasa.github.io/fprime/v2.0.0/Tutorials/MathComponent/Tutorial.html
