# Hanium
* 2020 한이음 ICT 멘토링 및 공모전 입선
* 마스크 인식 자동문 MIAD: Mask Identification and Automatic Door


---
### 개요
* 딥러닝 및 영상처리 기술을 이용하여 마스크 착용 여부를 실시간으로 판별하는 자동문 시스템
* 실내 시설 입장 시 마스크 착용을 독려하여 코로나19의 확산과 지역 감염의 최소화에 이바지하고자 함.

### 기획의도
* 2020년 초부터 코로나19가 전 세계적으로 급속히 확산되었으며 전염병이 주로 호흡기로 전파되는 만큼 마스크 착용의 중요성이 대두됨.
* 집단 감염을 최소화하기 위해 마스크를 착용하지 않은 사람이 실내 시설에 입장할 때는 자동문이 열리지 않도록 함.
* 딥러닝 기반 영상처리를 통한 자동문 개폐 시스템을 이용하면 인력 낭비를 줄일 수 있음.

### 작품내용
* 사용자가 출입문 앞에 서면 TX2 보드에 연결된 카메라에서 실시간으로 마스크 착용 여부를 확인.
* ROS 통신으로 마스크 착용 여부에 따라 라즈베리파이가 자동문을 개폐함.
* 마스크를 착용하지 않았을 경우 음성 피드백을 제공함.
* 외부 디스플레이를 통해 사용자가 어떻게 촬영되고 있는지 확인할 수 있음.

### 작품의 특징 및 장점
* 딥러닝을 활용하여 높은 정확도의 마스크 인식률: 다양한 종류의 마스크 착용 사진을 Training set으로 구성하고 CUDA, cuDNN 라이브러리를 활용하여 YOLO 알고리즘 기반의 학습을 진행. Training set의 사진 1장당 1만 회 이상의 학습을 진행하여 가중치 값을 추출하고 그 결과 85% 이상의 마스크 착용 여부 식별 가능.
* 자동화된 시스템으로 인력 보호 및 절감 가능: 카메라와 TX2 보드를 사용하여 사용자가 마스크를 착용했는지 판별하고 Raspberry Pi 3B를 통해 문을 자동으로 개폐. 따라서 출입문에서 사람이 일일이 검사할 필요가 없어 불필요한 접촉을 줄여 코로나19 감염을 줄일 수 있으며 자동화된 시스템으로 진행되기 때문에 인력 낭비 절감.
* 마스크 미착용 시 음성 피드백 송출: 마스크를 착용하지 않은 경우 단순히 문만 개폐되지 않는 것이 아니라 스피커로 경고 음성을 송출하여 마스크 착용을 독려.
* ROS를 활용한 TX2 보드와 라즈베리파이 간의 ROS 무선 통신: 서로 다른 보드 간의 ROS 통신으로 TX2 보드에서 마스크 착용 데이터를 라즈베리파이로 송수신할 수 있으며 이 값을 바탕으로 라즈베리파이가 출입문을 제어. 두 보드는 동일한 라우터 내에서 무선으로 연결되어 있어 보드 간의 물리적 거리에 구애받지 않음.


---
### nodetest_publisher.c
* ROS의 발행자 노드
* NVIDIA JETSON TX2의 YOLO 연산에 따른 마스크 인식 결과값을 Raspberry Pi 3B로 전송하는 역할

### nodetest_subscriber.c
* ROS의 구독자 노드
* 발행자 노드로부터 데이터를 수신하면 연속으로 수신하는 값들을 묶음으로 처리하여 이후 동작을 수행

### image.c
* [github.com/pjreddie/darknet](https://github.com/pjreddie/darknet) 에서의 image.c 소스코드를 참조
* 기본적인 역할은 Darknet 개발환경에서 image processing으로 마스크를 인식한 결과를 화면상에 출력
* 마스크 인식률의 연속적인 값을 임시로 저장하고 업데이트하기 위해 Circular queue로 처리하기 위한 자료구조를 구현
* Circular queue로부터 데이터를 순차적으로 ROS 환경에서 송신하기 위해 파일 처리를 활용
* NVIDIA JETSON TX2 개발 보드에서 딥러닝을 구현하기 위한 Darknet 개발환경은 모두 [여기](https://github.com/pjreddie/darknet)를 인용함


---
### 전체 시스템 구성도
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_system.jpg)
### MIAD HW 구성도
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_hw.jpg)
### MIAD DNN Training 구성도
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_dnn_training.jpg)
### MIAD SW 구성도
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_sw.jpg)


---
### MIAD 3D 모델링
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_3Dmodel.jpg)
### MIAD 마스크 레이블 인식 및 ROS 송수신
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_classification.png)
### MIAD 웹캠 디스플레이
![](https://github.com/zbumjin97/Hanium/blob/main/MIAD_display.png)
### [MIAD 구현 영상](https://www.youtube.com/watch?v=zmJI079PcNQ)
