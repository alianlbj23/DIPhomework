# DIP作業
紀錄DIP所有的作業
## box filter、median filter、Laplacian image Enhancement
function.h放各個function、library.h放各個include的東西、ConsoleApplication.cpp是主程式
### padding function
先用padding function，image的外圍多一層0，好用拿來做卷積使用。
首先先定義比原image的col和row都多加2的空白matrix，因為上下左右都要多一層，然後開始將原image複製到新定義的，發現row、col是第0和倒數一行都要給0，因為迴圈是跑新定義的，跟原image每個亮度的index有落差，因此原圖複製過去的row和col都要-1，避免超出原圖範圍。
### BoxFilter function
主程式傳入padding過的圖，迴圈從1到倒數第2，避免遍歷到最外圍0的地方，boxfilter的mask定義為[[1,1,1],[1,1,1],[1,1,1]]，跑到的那點讓周圍九宮格乘上遮罩後相加，最後除以9就是該點的亮度。
### MedianFilter function
跟boxfilter作法差不多，但這邊不是處以9，而是對這九宮格的數值做排序後取中間值，有益於過濾極端值雜訊，而中間值會是當下迴圈跑到的值。
### Laplacian function
遮罩定義為[[0, -1, 0], [-1, 5, -1], [0, -1, 0]]，如果九宮格乘出來互加大大於255，就定義成255，小於0就定義成0。
