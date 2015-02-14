# 學習 First Order Logic

Mokoversity 農場計畫團隊，在 YIC 進行無教科書化的教學。第一天從「寫程式的 Zero Step」開始，介紹 Formal Language 的觀念，練習最重要的寫程式技能：邏輯。最重要的寫程式技能「邏輯」，可以從 First Order Logic 的觀念開始培養。

第一天使用 First Order Logic 的觀念來撰寫開根號的演算法。從數學公式與 First Order Logic 的角度來寫開根號演算法，會得到二套很不一樣的程式碼。

## 不使用開方法

課程一開始就推翻了開方法（中算開方）。因為電腦的強項是「計算」，所以我們就讓電腦好好地算術。所以寫了底下的演算法：

```
int main() 
{
	float n = 1000000000;
	float x = 0.01;

	while (x * x < n)
		x = x + 0.01;

	printf("sqrt(%f) = %f\n", n, x);
}
```

小數運算還是比較耗時，可以將小數點右移，轉為整數運算後，再將小數點移回來。

這個例子，捨棄常見的開方法、長除式演算法、牛頓法與連分數等等。至於哪種方法在 ARM mbed 上效率最高，就有待同學的實驗結果了。

上述的演算法做法，並不常被拿出來討論；在大學資訊系的教學中，也不太容易看到這樣的寫法。

## 何謂 First Order Logic

讓我們來看看維基百科的解釋：

> 一階邏輯是數學基礎中很重要的一部份，因為它是公理系統的標準形式邏輯。

First Order Logic 的中文說法很很多：一階邏輯、一階謂詞演算、低階謂詞演算、量化理論或謂詞邏輯。

Frist Order Logic 既然是數學基礎很重要的一部份，那我們就透過上述的程式碼，來進行更深入的研討。

透過上述的例子，除了能討論「筆算」與「電腦算」的思考差異外，其實也討論基本的邏輯問題： 

* 對自然數 X 而言，必定存在一個集合（set）的數值：x1, x2, x3...xN；
* 並且該集合的數值，自乘（x1 * x1）的結果，都會小於 X；
* 即：x1 * x1 < X, x2 * x2 < X, x3 * x3 < X, ...
* 若該集合裡的數值，只取到小數點二位時，集合裡的數值個數為有限多個

如果從該集合取出最後一個數值，這個數就是 X 的平方根。這是一個很簡單的邏輯，一個可以找 X 平方根的邏輯。

這個觀念就是一階邏輯的運用。First Order Logic 是 Formal System 裡的一個主題，Formal System（正規系統、正規語言）利用符號來表示 First Order Logic 的語義。

如果不想用句子（語義）來表示 First Order Logic 的話，也可以改用符號來表示。

## 一階邏輯的開根號表示方法

First Order Logic 使用二個符號來表示變數（variable quantifiers）：

* ∀：for all
* ∃：there exists

變數的使用方式，例如：

* ∀X：for all X
* ∃X：there exists an X

然後有一個傳回真假值的函數 *p()*：

* ∀X p(X)：for all X, p(X) is true
* ∃X p(X)：there exists an X such that p(X) is true

一個簡單的使用範例：

* ∀X at(X, rit) → smart(X)

解釋如下：

* for all X, at(X, rit) is → smart(X) is true
* smart(X) 為 true，表示 X is smart

以上整句的意思為：everyone at RIT is smart[1]。

又如：

* ∃x p(x * x, X)

表示，存在一個數 x，使得 x * x 等於 y；也就是 x 即為所求。

## 挑戰題

(1). 如何用 First Order Logic 來設計開根號的演算法？

(2). 下列程式碼，是某個 First Order Logic 的開根號演算法。請試著撰寫這段程式碼的一階邏輯：

```
int main() 
{
	unsigned long n = 123456789;
	unsigned long x = 1, a, tmp;
	double sqrt;

	while (x * x < n)
		x = x + 1;

	x = x - 1;

	tmp = x * x;  
	a = n - tmp;

	sqrt = 1.0;
	sqrt = 2 * x;
	sqrt = 1 / sqrt;
	sqrt = x + sqrt;

	printf("sqrt(%d) = %f\n", n, sqrt);
}
```

(3). 是否能設計一套更棒的「開根號一階邏輯」？

## Coroutine 概念

接著我們打算讓 ARM mbed 幫忙計算平方根之餘，還能同時閃爍 LED，提醒我們 ARM mbed 正在執行計算的任務，任務結束後停止閃爍 LED。

這時就要引進一個重要的觀念稱為 Coroutine，中文譯作”協程“。Coroutine 的概念相當簡單，它允許程式在多個進入點暫停執行，然後在某處繼續啟動未完成的工作。簡單來說就是程式暫停現在的工作，去做另一件事，等完成之後再回頭把原本的工作結束。

以下透過兩種不同的範例實作 Coroutine：

本程式透過 Ticker 實作 Coroutine
```
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
#include "mbed.h"
 
Ticker flipper;
DigitalOut led1(LED1);
bool c=false;
void flip() {     
    while (!c) {
        led1 = !led1;
    }
    led1=1;
}
 
int main() {
 
    flipper.attach(&flip, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)
    // spin in a main loop. flipper will interrupt it to call flip
    while(1) {
        unsigned long n=100000000;
        float x=0;
        while(x*x <n)
            x = x + 0.01 ;   
        c=true;
    }
}
```

Ticker 屬於 ARM mbed 中斷機制裏的一項技術，藉由使用 Ticker 物件的相關函數，實作 Coroutine 概念。


本程式透過 Thread 實作 Coroutine
```
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
#include "mbed.h"
#include "rtos.h"
 
DigitalOut myled(LED1);
bool c=false;
void led1_thread(void const *argument) {
    
    while (!c) {
        myled = !myled;
        Thread::wait(200);
    }
    myled=1;
}
int main() {
    
    Thread th1(led1_thread);   
    while(1) {
        unsigned long n=100000000;
        float x=0;
        while(x*x <n)
            x = x + 0.01 ;   
        c=true;
    }
    
}
```

Thread，中文譯為“執行緒”，讓程式如分身一般，擁有多工處理的能力，藉由使用 Thread 物件的相關函數，實作 Coroutine 概念。


## 參考資源

[1]: http://www.cs.rit.edu/~rlc/Courses/IS/ClassNotes/PredicateLogic.pdf

[2]: http://zh.wikipedia.org/wiki/全称量化

[3]: http://programmermagazine.github.io/201403/htm/focus3.html

[4]: http://www.cs.cornell.edu/Courses/cs472/2007fa/lectures/17-kb-systems_fol.pdf

[5]: http://everything2.com/title/approximating+square+roots+using+first-order+Taylor+series
