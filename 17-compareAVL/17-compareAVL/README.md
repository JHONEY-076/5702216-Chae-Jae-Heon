Result
---
![](https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/17-compareAVL/17-compareAVL/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-12-12%20143655.jpg)

---
![](
https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/17-compareAVL/17-compareAVL/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-12-12%20143717.jpg)

---
![](
https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/17-compareAVL/17-compareAVL/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-12-12%20143736.jpg)


---


결과분석 

-이진 탐색 트리 (BST)
   평균 비교 횟수: 9.12
    =>BST는 삽입 순서에 따라 트리의 균형이 크게 달라지기 때문에, 비교횟수가 AVL 트리보다 많은것을 알 수 있다. 최악의 경우 트리의 높이가 
      O(n)까지 증가 할 수 있다.

- AVL 트리
    평균 비교 횟수: 7.42
-   =>AVL 트리는 삽입과 삭제 후 균형을 유지하기 때문에 탐색 시 비교 횟수가 적게 나타나는것을 볼수 있다. 왜냐하면 트리의 높이가 항상
-   O(long n)을 유지 하기 때문이다.


-결론 =>효율성 측면에서 

-AVL트리는 항상 균형을 유지하여 탐색시 평균 비교 횟수가 적고, 이는 검색 속도가 더 빠름을 의미한다.
-BST는 균형을 유지하지 않기 때문에, 평균 비교 횟수가 많아져 검색 속도가 느릴수 있다.

그러므로 이 결과로 보아 균형이 잡힌 AVL트리가 탐색의 효율성이 더 높다는것을 알수 있고, BST는 삽입 순성 따라 효율성이 크게 변화 할 수 있기 
때문에 평균 비교 횟수가 높게 나타남을 알 수 있다.
