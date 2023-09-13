|0. linux_kernel [🔻](https://github.com/hardy716/linux_kernel#0%EF%B8%8F⃣--linux_kernel)|
|---|

|1. 리눅스 커널 소스 다운로드 및 압축 풀기 [🔻](https://github.com/hardy716/linux_kernel#1%EF%B8%8F⃣--리눅스-커널-소스-다운로드-및-압축-풀기)|
|---|

|2. 소스에 시스템 콜 추가 [🔻](https://github.com/hardy716/linux_kernel#2%EF%B8%8F⃣--소스에-시스템-콜-추가)|
|---|

|3. 추가한 시스템 콜을 컴파일 하기 위한 환경 세팅 [🔻](https://github.com/hardy716/linux_kernel#3%EF%B8%8F⃣--추가한-시스템-콜을-컴파일-하기-위한-환경-세팅)|
|---|

|4. 소스 코드 옮기고 계속 컴파일 환경 설정 [🔻](https://github.com/hardy716/linux_kernel#4%EF%B8%8F⃣--소스-코드-옮기고-계속-컴파일-환경-설정)|
|---|

|5. 컴파일 [🔻](https://github.com/hardy716/linux_kernel#5%EF%B8%8F⃣--컴파일)|
|---|

|6. 컴파일한 커널을 OS에 설치 [🔻](https://github.com/hardy716/linux_kernel#6%EF%B8%8F⃣--컴파일한-커널을-os에-설치)|
|---|

|7. 추가한 시스템 콜이 정상적으로 작동하는지 확인해보기(유저 레벨) [🔻](https://github.com/hardy716/linux_kernel#7%EF%B8%8F⃣--추가한-시스템-콜이-정상적으로-작동하는지-확인해보기유저-레벨)|
|---|

<br></br>

## 0️⃣  linux_kernel

가상환경인 VMware에서 64-bit 우분투(Ubuntu)를 기반으로 리눅스 커널의 컴파일과 시스템 콜 추가 작업을 진행했습니다.

1. 리눅스 커널:
커널은 운영 체제의 핵심 부분으로, 하드웨어와 소프트웨어 간의 상호 작용을 관리합니다. 커널은 시스템 리소스(예: 메모리, CPU 시간)를 할당하고, 장치 드라이버를 관리하며, 사용자와 시스템 간의 인터페이스 역할을 합니다.

3. 커널 컴파일:
커널 컴파일은 커널 소스 코드를 기계어로 변환하는 과정을 말합니다. 리눅스 커널은 다양한 설정 옵션을 제공하므로, 사용자는 이러한 옵션을 사용하여 자신의 환경에 맞게 커널을 커스텀화할 수 있습니다. 커널을 컴파일하면, 해당 시스템에 최적화된 커널을 얻을 수 있으며, 필요하지 않은 기능을 제거하거나 추가적인 기능을 포함시킬 수 있습니다.

4. 시스템 콜 추가:
사용자 공간의 애플리케이션과 커널 공간 사이의 인터페이스 역할을 합니다. 이를 통해 프로그램은 커널에게 다양한 서비스(예: 파일 작성, 메모리 할당)를 요청할 수 있습니다.
시스템 콜을 추가한다는 것은 새로운 기능이나 서비스를 커널에 추가하겠다는 의미입니다. 예를 들어, 특정한 하드웨어 기능을 지원하거나, 새로운 방식의 리소스 관리 기능을 구현할 수 있습니다. 

리눅스 커널은 운영 체제의 중심적인 부분이며, 커널 컴파일은 이 커널을 특정 환경에 맞게 최적화하는 과정입니다. 
시스템 콜을 추가하면 커널의 기능을 확장하여 사용자 애플리케이션에 새로운 서비스를 제공할 수 있습니다.

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
