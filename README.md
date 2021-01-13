# [Data_structure] B tree & B+tree

## B트리 개요

#### 정의
B트리는 데이터를 정렬하여 탐색, 삽입, 삭제 및 순차 접근이 가능하도록 유지하는 트리형 자료구조이다.

#### B트리의 장점
B트리는 Balanced-Tree의 일종으로 어떠한 경우에도 트리의 균형이 유지된다. 
균형이 유지된다는 것은 탐색에 있어 최악의 경우에도 시간복잡도가 O(lonN)을 유지한다는 것을 의미한다.

<img src="https://mblogthumb-phinf.pstatic.net/MjAxNjExMTFfNTkg/MDAxNDc4NzkwNzQ0NzI4.ZtVhyorQj9qDa6hZwfNxJLv0IAKH2NDVa-HuftEreOQg.Zo7x4cWFIDLBdiPv6XTOrmy-M1v7JHaAz7IVtHnmfAYg.PNG.dlwoen9/LL%ED%9A%8C%EC%A0%84.png?type=w2" width="450px" height="300px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>

편향트리의 경우 최악의 경우 탐색할 때 O(N)의 시간이 걸리지만 균형트리를 유지하면 최악의 경우에도 O(logN)을 유지한다.

---------
  _B트리의 특징은 <INTRODUCTION TO ALGORITHMS, Thomas H.Cormen>의 서적의 내용에 따라 정의하였습니다_

## B트리의 특징
>* 노드의 자료를 key, 노드의 자식을 child라고 한다면, 
>* 자료는 정렬된 상태로 저장된다.
>* 차수를 t라고 했을 때, 노드의 key의 수는 최소값은 t-1개이고 최대값은 2*t-1개이다.(t-1 <= 키의 개수 <= 2t-1)
>* 차수를 t라고 했을 때, 노드의 child의 수의 최대값은 2*t개이다.
>* 차수는 2이상이어야한다.(t>=2)
>* 노드의 key의 수가 n개라면 child의 수는 n+1개이다.
>* 입력 자료는 중복될 수 없다.
---------
## B트리 삽입 구현
### 구현을 시작 하기 전에
B트리 구현을 시작하기 전에 자료조사를 하면서 굉장히 혼란스러웠다.

많은 자료들이 Bottom-up 방식으로 구현하는데 Bottom-up 논리로 삽입(insert)을 구현하는 방법은 명확했지만 같은 로직으로 삭제(delete)구현하는 방법은 굉장히 복잡했고 delete를 어떻게 구현해야할 지 충분히 이해가 가지 않았다.

결국 인터넷 자료 찾는 것을 멈추고 교과서를 펼쳤다. <INTRODUCTION TO ALGORITHMS, Thomas H.Cormen>라는 책은 1200페이지 번역체 양장본 교과서여서 좀처럼 손이 안갔는데 인터넷에서 정확한 자료를 찾기 힘들다는 판단을 하고 나니 믿을 것을 교과서 뿐이었다.

책은 인터넷의 수 많은 자료들이 Bottom-up방식을 채택해서 논리를 펼친 것과는 달리 Top-down 방식을 설명하고 있었다.

>Top-down 방식의 핵심은 "절대 다시 루트 방향으로 되돌아가지 않을거야"

책의 논리를 이해할 수록 "답은 이거다!" 하는 생각이 들었고 우리 팀원들도 같은 마음이었을 것이다. 결국 책의 논리를 따라가며 B트리 구현을 완료했다. 이 곳에 책의 내용의 전부를 기록할 수는 없지만 핵심 내용을 중심으로 설명할 계획이다.

### B 트리 삽입

