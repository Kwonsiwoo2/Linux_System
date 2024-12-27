
## Hi there 👋

I’m an aspiring Embedded Systems Developer passionate about low-level programming and building efficient systems that bridge hardware and software. I enjoy solving challenges close to the metal and optimizing code for performance and resource constraints.

📚 About Me

🚀 Exploring embedded development and real-time systems

🛠️ Tinkering with microcontrollers and hardware

📖 Continuously learning and improving my coding skills

---

## 1. Yocto
Yocto 프로젝트는 임베디드 리눅스 시스템을 구축하기 위한 도구 및 메타데이터를 제공하는 오픈 소스 프로젝트입니다. 이 프로젝트는 사용자 정의 Linux 배포판을 생성하는 데 사용됩니다.

### 주요 기능:
- **레시피 기반 빌드 시스템**: 특정 패키지, 커널, 부트로더 등을 위한 레시피를 정의하여 빌드합니다.
- **확장성**: 사용자 정의 계층(layer)을 추가하여 기능을 확장할 수 있습니다.
- **최적화된 빌드**: 임베디드 장치에서 효율적인 운영을 위해 경량화된 이미지를 생성합니다.

### Yocto 워크플로우:
1. **BitBake 설정**: 레시피와 메타데이터를 이용하여 빌드 환경 구성.
2. **레이어 관리**: BSP(Board Support Package)와 애플리케이션 계층 추가.
3. **이미지 빌드**: `bitbake core-image-minimal` 명령을 사용해 이미지 생성.

---

## 2. U-Boot
U-Boot는 유연한 오픈 소스 부트로더로, 임베디드 시스템에서 하드웨어 초기화 및 운영체제 로딩을 담당합니다.

### 주요 역할:
- **하드웨어 초기화**: CPU, 메모리, 네트워크, 저장 장치 등 초기화.
- **OS 로딩**: 리눅스 커널, 다른 운영체제, 또는 사용자 정의 애플리케이션을 메모리에 로드.
- **명령 줄 인터페이스**: 부팅 옵션 변경 및 디버깅을 위한 CLI 제공.

### U-Boot 빌드:
1. **환경 설정**:
   ```bash
   make <board_config>_defconfig
   ```
2. **U-Boot 컴파일**:
   ```bash
   make -j$(nproc)
   ```
3. **결과물**:
   - `u-boot.bin`: 부팅 가능한 바이너리.
   - `u-boot.img`: 이미지 파일.

---

## 3. System Call
System Call은 사용자 애플리케이션과 운영체제 커널 간의 인터페이스를 제공합니다. 프로세스, 파일 시스템, 네트워크 등 리소스에 접근하기 위해 호출됩니다.

### 주요 시스템 콜:
- **파일 제어**: `open()`, `read()`, `write()`, `close()`
- **프로세스 제어**: `fork()`, `exec()`, `exit()`
- **메모리 관리**: `mmap()`, `brk()`
- **네트워크**: `socket()`, `connect()`, `bind()`

### 사용자 정의 System Call 작성:
1. **커널 코드 수정**: 시스템 호출 테이블에 새로운 호출 추가.
2. **시그니처 정의**: 커널 내에서 새 함수 구현.
3. **헤더 파일 업데이트**: 사용자 공간에서 호출할 수 있도록 인터페이스 제공.

---

## 4. 애플리케이션과 C 언어 연동
C 언어는 하드웨어와 소프트웨어 사이의 효율적인 인터페이스를 제공합니다. 특히 시스템 호출과 직접적인 연동이 가능합니다.

### 주요 연동 사례:
1. **하드웨어 제어**:
   - GPIO, PWM, UART와 같은 장치를 C 코드로 제어.
   - 예제:
     ```c
     int fd = open("/dev/led", O_WRONLY);
     if (fd < 0) {
         perror("Failed to open device");
         return -1;
     }
     write(fd, "1", 1);
     close(fd);
     ```

2. **시스템 호출 사용**:
   - `syscall()` 함수를 사용해 커널 기능 호출.
     ```c
     #include <unistd.h>
     #include <sys/syscall.h>

     long result = syscall(SYS_getpid);
     printf("Current PID: %ld
", result);
     ```

3. **U-Boot와 통신**:
   - U-Boot 환경 변수 읽기/쓰기.
   - 네트워크 부팅 명령 전송.

---

## 참고 자료
- [Yocto 프로젝트 공식 문서](https://www.yoctoproject.org/documentation/)
- [U-Boot 공식 문서](https://www.denx.de/wiki/U-Boot)
- [리눅스 시스템 콜 문서](https://man7.org/linux/man-pages/man2/syscall.2.html)
- [C 언어와 커널 인터페이스](https://kernelnewbies.org/)

---

### 👇 Let's Connect!

[![GitHub](https://img.shields.io/badge/GitHub-Profile-blue?logo=github)](https://github.com/Kwonsiwoo2)  [![LinkedIn](https://img.shields.io/badge/LinkedIn-Profile-blue?logo=linkedin)](https://www.linkedin.com/in/%EC%8B%9C%EC%9A%B0-%EA%B6%8C-064765341/)
