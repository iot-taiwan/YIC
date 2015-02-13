# First Order Logic

Mokoversity 農場計畫團隊，在 YIC 進行無教科書化的教學。第一天從「寫程式的 Zero Step」開始，介紹 Formal Language 的觀念，練習最重要的寫程式技能：邏輯。最重要的寫程式技能「邏輯」，可以從 First Order Logic 的觀念開始培養。

第一天使用 First Order 的觀念來，寫開根號的演算法。從數學公式與 First Order Logic 的角度來寫開根號演算法，會得到二套很不一樣的程式碼。

## 不使用開方法

課程一開始就推翻了開方法。電腦的強項是「計算」，所以我們就讓電腦好好地算術。所了寫了底下的演算法：

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

## 何謂一階邏輯

x：輸入的數(原數)

y：x 開根號的答案


## 一階邏輯的開根號表示方法

```
∃y(y^2=x)
```

存在一個數 y，使得 y 的平方等於 x。y 即為所求


## 參考資源

[1]: ttp://www.cs.rit.edu/~rlc/Courses/IS/ClassNotes/PredicateLogic.pdf

[2]: http://zh.wikipedia.org/wiki/全称量化

[3]: http://programmermagazine.github.io/201403/htm/focus3.html


