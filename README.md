# VTK_PointCloud
Point cloud visualization using VTK library

## 1. 참고 사이트

예제 코드: https://lorensen.github.io/VTKExamples/site/

클래스 설명: https://www.vtk.org/doc/nightly/html/classvtkExtractSurface.html

## 2. vtk module init 관련 issue

```cpp
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkInteractionStyle); // 필요에 따라 포함
//VTK_MODULE_INIT(vtkRenderingFreeType); // 필요에 따라 포함
//VTK_MODULE_INIT(vtkRenderingFreeTypeOpenGL); // 필요에 따라 포함
VTK_MODULE_INIT(vtkRenderingOpenGL); // 필수
```

위 include 와 macro를 헤더 선언 맨 위에 선언


## 3. vtkDemo

point cloud rendering

point 크기 조정

point 색 조정

배경색 조정

카메라 뷰 제어

시작 윈도 사이즈 조정(실행 후에도 크기 조절은 가능)



## 4. 마우스 컨트롤 (직접 눌러보고 확인을 해보시면 이해가 빠를 것 같습니다.)

좌클릭: 클릭한 방향으로 회전

우클릭: 줌인

휠 스크롤: 줌 인/아웃

ctrl + 좌클릭: 화면에 수직 한 축 중심으로 회전
