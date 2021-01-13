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
>* 핵심 아이디어1    
>: 루트에서부터 리프까지 길을 찾아 가면서 삽입되기 전까지 지나가는 모든 노드를 **가득 차 있지 않게** 만들면서 지나갈거야    
삽입할 K가 들어갈 노드를 찾아갔는데 노드가 꽉 차있으면 노드의 중앙값을 부모에게 넘겨주면서 노드를 쪼개어(split) 키의 개수를 줄여야 한다.
쪼개고(split)나면 이제 K가 들어갈 공간이 생겼으니 K를 삽입해줄 수 있다.
하지만 여기서 문제는 노드의 부모로 K를 보내야하는데 부모도 가득 차 있는 상태라면?    
부모의 부모도 가득 차 있는 상태라면? 계속해서 루트를 향해 올라가야하는 일이 발생한다.    

<img src="https://user-images.githubusercontent.com/61036124/104415039-98257d00-55b4-11eb-8e50-4f9d074e7839.jpg" width="450px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
자, 이 트리에 17이 삽입된다고 생각해보자

<img src="https://user-images.githubusercontent.com/61036124/104415187-e470bd00-55b4-11eb-83db-f238ae7e129d.jpg" width="450px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
노드가 가득 차 있지 않으면 그냥 해당 노드로 이동하고 재귀함수를 돌리면 된다.   

<img src="https://user-images.githubusercontent.com/61036124/104415407-50ebbc00-55b5-11eb-9c26-7231a92441f2.jpg" width="450px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
해당하는 child로 들어와서 다음 노드를 바라보고 물어본다. 노드가 가득 차 있니?
노드가 가득 차 있기 때문에 해당 노드를 쪼개줘야한다.

<img src="https://user-images.githubusercontent.com/61036124/104416124-93fa5f00-55b6-11eb-8199-a3f987184903.jpg" width="450px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
Split() 함수를 실행시켜서 노드를 쪼개 준 후에 비로소 가려던 노드로 이동할 수 있다.

<img src="https://user-images.githubusercontent.com/61036124/104416261-db80eb00-55b6-11eb-8c69-66b6651dc610.jpg" width="450px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
17이 들어가야할 리프노드를 찾았다. 노드의 key의 개수가 2*t - 1 보다 작기 때문에 바로 17을 삽입해준다.



