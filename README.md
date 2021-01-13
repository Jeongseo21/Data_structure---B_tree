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
  <INTRODUCTION TO ALGORITHMS, Thomas H.Cormen>의 서적을 참고하였습니다.

## B트리의 특징
> * 노드의 자료를 key, 노드의 자식을 child라고 한다면, 
* 자료는 정렬된 상태로 저장된다.
* 차수를 t라고 했을 때, 노드의 key의 수는 최소값은 t-1개이고 최대값은 2*t-1개이다.(t-1 <= 키의 개수 <= 2t-1)
* 차수를 t라고 했을 때, 노드의 child의 수의 최대값은 2*t개이다.
* 차수는 2이상이어야한다.(t>=2)
* 노드의 key의 수가 n개라면 child의 수는 n+1개이다.
* 입력 자료는 중복될 수 없다.

