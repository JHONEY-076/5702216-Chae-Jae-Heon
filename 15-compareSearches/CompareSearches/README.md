Result 

---
![](https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/15-compareSearches/CompareSearches/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-11-26%20230332.jpg)

---

![](https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/15-compareSearches/CompareSearches/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-11-26%20230354.jpg)

---

![](https://github.com/JHONEY-076/5702216-Chae-Jae-Heon/blob/master/15-compareSearches/CompareSearches/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202024-11-26%20230413.jpg)

---


▪ A, B, C에 대해서 퀵 정렬후의 이진탐색에서 순차탐색보다 적게 비교하는 이유:

먼저 순차탐색은 배열의 첫 번째 요소부터 순서대로 하나씩 비교하여 목표의 값을 찾는 동작원리를 가지며, B의 퀵정렬 이후 정렬된 배열에서 작동하는 이진탐색은 탐색의 범위를 절반씩 줄여가며 목표의 값을 찾는 동작 원리를 가지고 있다.
그러므로 순차 탐색은 배열의 모든 요소를 처음부터 끝까지 하나하나씩 검사하기 때문에, 평균적으로 N/2번의 비교가 필요하며, 이진탐색은 매번 탐색 범위를 절반으로 줄여나가기 때문에 비교횟수가 log N에 비례하다는것을 알 수 있다.
다시 말해 순차 탐색은 O(N) 비교횟수를 갖고, 퀵정렬은 O(N log N), 이진 탐색은 log N의 비교 횟수를 갖기 때문에 퀵 정렬 후 이진탐색에서는 순차 탐색보다 비교횟수가 적은것을 알 수 있다.
