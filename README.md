|0. linux_kernel [🔻]()|
|---|

|1. 리눅스 커널 소스 다운로드 및 압축 풀기 [🔻]()|
|---|

|2. 소스에 시스템 콜 추가 [🔻]()|
|---|

|3. 추가한 시스템 콜을 컴파일 하기 위한 환경 세팅 [🔻]()|
|---|

|4. 소스 코드 옮기고 계속 컴파일 환경 설정 [🔻]()|
|---|

|5. 컴파일 [🔻]()|
|---|

|6. 컴파일한 커널을 OS에 설치 [🔻]()|
|---|

|7. 추가한 시스템 콜이 정상적으로 작동하는지 확인해보기(유저 레벨) [🔻]()|
|---|

<br></br>

## 0️⃣  linux_kernel

가상환경(VMware)에서 우분투(Ubuntu 64-bit)를 활용하여, 커널 컴파일 및 시스템 콜을 만들었습니다.

<br></br>

## 1️⃣  리눅스 커널 소스 다운로드 및 압축 풀기

```
wget https://mirros.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.18.16.tar.xz  // 소스 다운로드
tar xvf linux-5.18.16.tar.xz  // 압축 풀기
cd linux-5.18.16
```

<br></br>

## 2️⃣  소스에 시스템 콜 추가

```
cd kernel
nano mycall.c
```

![l1](https://github.com/hardy716/linux_kernel/assets/101140679/b65298ac-f620-4e6b-9216-b178c7fe76ee)

<br></br>

## 3️⃣  추가한 시스템 콜을 컴파일 하기 위한 환경 세팅

```
nano Makefile
```

![l2](https://github.com/hardy716/linux_kernel/assets/101140679/ead27db9-4a45-4857-8007-e1a403ed3882)

```
cd ..
cd ./arch/x86/entry/syscalls
nano syscall_64.tbl
```
![l3](https://github.com/hardy716/linux_kernel/assets/101140679/4ea22ab5-a812-4ae6-9fcd-f7dfef84bd0b)

```
cd ../../../..
cd ./include/linux
nano syscalls.h
```
![l4](https://github.com/hardy716/linux_kernel/assets/101140679/3bd96836-5d87-421a-862c-7eb08ffdcddb)

<br></br>

## 4️⃣  소스 코드 옮기고 계속 컴파일 환경 설정

```
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev flex libelf-dev bison
cd ~ (tar 파일 받은 경로로 이동하기)
sudo cp -r linux-5.18.16/usr/src/linux-5.18.16
```

```
cd /usr/src/linux-5.18.16
sudo cp /boot/config-$(uname -r) .config
sudo make menuconfig
```

```
// 만약 아래 메시지가 출력되면, 디스플레이 크기 변경하고 해상도도 100%로 줄일 것
Your display is too small to run Menuconfig!
It must be at least 19 lines by 80 columns.

// 정상적으로 창이 뜨면, load -> save -> exit
```

```
sudo nano .config

// 아래와 같이 해당 항목들의 값을 ""로 변경
CONFIG_SYSTEM_TRUSTED_KEYS=""
CONFIG_SYSTEM_REVOCATION_KEYS=""
```

<br></br>

## 5️⃣  컴파일

```
sudo make -j8  // 컴파일 시간을 줄이기 위해 코어 개수를 8로 설정
```
![l5](https://github.com/hardy716/linux_kernel/assets/101140679/9e92743c-58e4-489e-ab2a-5843be897065)

중간에 위와 같은 메시지가 뜨지 않는 경우, 오타가 났을 확률이 높으므로 재확인 필요!

```
sudo make modules_install -j8  // 컴파일 시간을 줄이기 위해 코어 개수를 8로 설정
```
![l6](https://github.com/hardy716/linux_kernel/assets/101140679/5d2b0bee-cb86-4f90-9cd3-2cd1fbed86dc)

실행 결과 확인

<br></br>

## 6️⃣  컴파일한 커널을 OS에 설치

![l7](https://github.com/hardy716/linux_kernel/assets/101140679/c346ad2a-57d4-41a4-a45c-c558235ed880)

그 전의 커널 버전

![l8](https://github.com/hardy716/linux_kernel/assets/101140679/83605867-8a05-4f47-b8d6-5019e66b1365)

새로운 커널 설치하기

![l9](https://github.com/hardy716/linux_kernel/assets/101140679/84f53cc4-77f0-47ef-bea6-faf765c2fdd6)

```
sudo reboot
```

![l10](https://github.com/hardy716/linux_kernel/assets/101140679/522b3138-fda1-4eaf-b624-4b84fa756cea)

<br></br>

## 7️⃣  추가한 시스템 콜이 정상적으로 작동하는지 확인해보기(유저 레벨)

```
nano systest.c
```

![l11](https://github.com/hardy716/linux_kernel/assets/101140679/05339f23-3d0b-4349-adef-7453e8180c08)

```
gcc -o systest.out systest.c
```

![l12](https://github.com/hardy716/linux_kernel/assets/101140679/1a66ba64-e3a3-42d3-8594-c58858c1e319)

```
sudo dmesg  // 커널 메시지 확인(SYSCALL_DEFINE1, SYSCALL_DEFINE0)
```

![l13](https://github.com/hardy716/linux_kernel/assets/101140679/0fd98f14-e1f6-4142-836c-088d89471514)
