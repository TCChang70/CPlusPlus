# C++ `string` 型別 × 迴圈 學習文件

## Part 1 — 語法教學

### 1. 概念定義（What）

C++ 的 `string`（字串）是「一串字元的集合」，就像一條串著珠子的項鍊，每顆珠子是一個字元（Character）。搭配迴圈，就能逐一取出每顆珠子來檢查、修改或統計。

使用前需引入標頭：

```cpp
#include <string>
using namespace std;
```

---

### 2. 使用時機（When）

- 逐字元分析：計算母音數、統計某字元出現次數
- 字串建構：用迴圈組合出新字串
- 搜尋與取代：走訪每個位置找目標字元
- 字串反轉、回文判斷
- 分割（Split）字串為單詞

---

### 3. `string` 核心語法速查

| 操作 | 語法 | 說明 |
|------|------|------|
| 宣告 | `string s = "hello";` | 建立字串 |
| 取長度 | `s.size()` 或 `s.length()` | 傳回字元數（`size_t` 型別）|
| 取單一字元 | `s[i]` 或 `s.at(i)` | `at()` 有邊界檢查 |
| 拼接 | `s1 + s2` 或 `s += "abc"` | 字串串接（Concatenation）|
| 子字串 | `s.substr(pos, len)` | 取出子字串（Substring）|
| 搜尋 | `s.find("ab")` | 回傳位置，找不到傳 `string::npos` |
| 取代 | `s.replace(pos, len, "xy")` | 取代子字串片段 |
| 清空 | `s.clear()` | 清空字串 |
| 空字串判斷 | `s.empty()` | 比 `s.size() == 0` 更語意清楚 |

---

### 4. 迴圈走訪 `string` 的三種方式

#### 方式一：索引式 `for`（Index-based）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";
    for (int i = 0; i < (int)s.size(); i++) {
        cout << s[i] << " ";  // h e l l o
    }
    return 0;
}
```

> 注意：`s.size()` 回傳型別是 `size_t`（無號整數），與 `int` 比較時建議加 `(int)` 轉型，避免無號數比較時的陷阱。

#### 方式二：Range-based `for`（C++11，最簡潔）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";
    for (char c : s) {
        cout << c << " ";  // h e l l o
    }
    return 0;
}
```

#### 方式三：迭代器（Iterator）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";  // h e l l o
    }
    return 0;
}
```

> 迭代器（Iterator）是進入 STL 的重要概念，`begin()` 指向第一個字元，`end()` 指向「最後一個字元的下一個位置」。

---

### 5. 進階用法

#### 5-1. 計算特定字元出現次數

```cpp
#include <iostream>
#include <string>
using namespace std;

int countChar(const string& s, char target) {
    int count = 0;
    for (char c : s) {
        if (c == target) count++;
    }
    return count;
}

int main() {
    string s = "programming";
    cout << "g 出現 " << countChar(s, 'g') << " 次" << endl;
    // 輸出：g 出現 2 次
    return 0;
}
```

---

#### 5-2. 用迴圈建構新字串（反轉字串）

```cpp
#include <iostream>
#include <string>
using namespace std;

string reverseStr(const string& s) {
    string result = "";
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        result += s[i];  // += 拼接單一字元
    }
    return result;
}

int main() {
    cout << reverseStr("hello") << endl;  // 輸出：olleh
    return 0;
}
```

---

#### 5-3. 大小寫轉換（搭配 `<cctype>`）

```cpp
#include <iostream>
#include <string>
#include <cctype>   // tolower, toupper
using namespace std;

int main() {
    string s = "Hello World";
    for (char& c : s) {       // 用 & 引用才能修改原字串
        c = tolower(c);
    }
    cout << s << endl;  // 輸出：hello world
    return 0;
}
```

| 函式 | 說明 |
|------|------|
| `tolower(c)` | 轉小寫，非字母字元不變 |
| `toupper(c)` | 轉大寫，非字母字元不變 |
| `isalpha(c)` | 判斷是否為字母 |
| `isdigit(c)` | 判斷是否為數字 |
| `isspace(c)` | 判斷是否為空白 |

---

#### 5-4. `while` 搭配 `find()` 逐一搜尋

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "apple,banana,cherry";
    string delimiter = ",";
    size_t pos = 0;

    while ((pos = s.find(delimiter)) != string::npos) {
        cout << s.substr(0, pos) << "\n";  // 印出每個單詞
        s.erase(0, pos + delimiter.size());
    }
    cout << s << "\n";  // 最後一個單詞
    // 輸出：apple / banana / cherry
    return 0;
}
```

---

### 6. 常見錯誤（Common Pitfalls）

#### Pitfall 1 — `size_t` 與 `int` 混用導致無窮迴圈

```cpp
// ❌ 錯誤寫法
string s = "hello";
for (int i = s.size() - 1; i >= 0; i--) { ... }
// 若 s 為空字串：s.size() 是 size_t(0)，
// 0 - 1 = 4294967295（無號數下溢），i >= 0 永遠成立！

// ✅ 正確寫法
for (int i = (int)s.size() - 1; i >= 0; i--) { ... }
```

---

#### Pitfall 2 — Range-for 修改字元忘記加 `&`

```cpp
// ❌ 修改副本，原字串不變
for (char c : s) { c = toupper(c); }

// ✅ 加上引用 & 才能修改原字串
for (char& c : s) { c = toupper(c); }
```

---

#### Pitfall 3 — 迴圈內用 `+` 拼接效能差

```cpp
// ❌ 每次 + 都建立新字串，O(n²) 複雜度
string result = "";
for (int i = 0; i < 10000; i++) {
    result = result + "x";  // 慢！
}

// ✅ 用 += 或先 reserve()
string result = "";
result.reserve(10000);
for (int i = 0; i < 10000; i++) {
    result += "x";  // 快！
}
```

---

#### Pitfall 4 — `find()` 回傳值未判斷 `npos`

```cpp
// ❌ 若找不到，pos = string::npos（極大值），substr 會崩潰
size_t pos = s.find("xyz");
string sub = s.substr(pos, 3);  // 危險！

// ✅ 先判斷是否找到
size_t pos = s.find("xyz");
if (pos != string::npos) {
    string sub = s.substr(pos, 3);
}
```

---

## Part 2 — 練習題

---

### 練習題 1：母音計數器

**難度：** `Easy`  
**語言：** C++  
**主題：** `string` + range-based `for` + 條件判斷

---

#### 題目說明

撰寫函式 `countVowels`，接收一個 `string`，回傳其中母音字母（a, e, i, o, u，不分大小寫）的數量。

**函式簽名：**

```cpp
int countVowels(const string& s);
```

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `"Hello World"` | `3` | e, o, o 共 3 個母音 |
| `"rhythm"` | `0` | 沒有母音 |
| `"AEIOU"` | `5` | 大寫母音也計算 |

---

#### 提示

<details>
<summary>顯示提示</summary>

用 `tolower(c)` 先將字元轉小寫，再判斷是否屬於 `"aeiou"` 其中一個字元。可以用 `string("aeiou").find(c) != string::npos` 來判斷。

</details>

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int countVowels(const string& s) {
    int count = 0;
    string vowels = "aeiou";
    for (char c : s) {
        char lower = tolower(c);
        if (vowels.find(lower) != string::npos) {
            count++;
        }
    }
    return count;
}

int main() {
    cout << countVowels("Hello World") << endl;  // 3
    cout << countVowels("rhythm")      << endl;  // 0
    cout << countVowels("AEIOU")       << endl;  // 5
    return 0;
}
```

**說明：**
1. 對每個字元先 `tolower()` 轉小寫，統一處理大小寫。
2. 用 `string::find()` 判斷是否在母音集合中，找不到時回傳 `string::npos`。
3. 時間複雜度：$O(n)$，每個字元只走訪一次。

</details>

---

### 練習題 2：回文判斷

**難度：** `Medium`  
**語言：** C++  
**主題：** `string` + 索引式 `for` + 雙指標觀念

---

#### 題目說明

撰寫函式 `isPalindrome`，判斷一個字串是否為回文（Palindrome）。回文是指正讀和倒讀都一樣的字串，且忽略大小寫、只比較字母與數字（忽略空格與標點）。

**函式簽名：**

```cpp
bool isPalindrome(const string& s);
```

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `"racecar"` | `true` | 正反一樣 |
| `"A man a plan a canal Panama"` | `true` | 去除空格後為回文 |
| `"hello"` | `false` | 正反不同 |
| `""` | `true` | 空字串視為回文 |

---

#### 提示

<details>
<summary>顯示提示 1</summary>

先用迴圈把字串中的字母與數字（`isalnum(c)`）提取出來，轉小寫後存入新字串，再做比較。

</details>

<details>
<summary>顯示提示 2</summary>

比較時用雙指標（Double Pointer）：一個從頭，一個從尾，同時向中間移動，逐一比對字元是否相等。

</details>

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(const string& s) {
    // Step 1：提取有效字元並轉小寫
    string filtered = "";
    for (char c : s) {
        if (isalnum(c)) {
            filtered += tolower(c);
        }
    }

    // Step 2：雙指標從兩端向中間比對
    int left = 0, right = (int)filtered.size() - 1;
    while (left < right) {
        if (filtered[left] != filtered[right]) return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    cout << boolalpha;
    cout << isPalindrome("racecar")                       << endl;  // true
    cout << isPalindrome("A man a plan a canal Panama")   << endl;  // true
    cout << isPalindrome("hello")                         << endl;  // false
    cout << isPalindrome("")                              << endl;  // true
    return 0;
}
```

**說明：**
1. 先過濾出有效字元（字母或數字），轉小寫統一格式，避免大小寫和標點干擾。
2. 雙指標（Double Pointer）是比對回文的經典手法，時間 $O(n)$，空間 $O(n)$（因為建立了 `filtered`）。
3. `boolalpha` 讓 `cout` 印出 `true`/`false` 而非 `1`/`0`。

</details>

---

### 練習題 3：單詞頻率統計

**難度：** `Hard`  
**語言：** C++  
**主題：** `string` + `while` + `find()` + `map`（STL 容器）

---

#### 題目說明

撰寫函式 `wordFrequency`，接收一段以空格分隔的英文句子，輸出每個單詞及其出現次數（不分大小寫），結果依出現次數**由多到少**排序輸出。

**函式簽名：**

```cpp
void wordFrequency(const string& sentence);
```

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 |
|------|------|
| `"the cat sat on the mat the cat"` | `the: 3`<br>`cat: 2`<br>`sat: 1`<br>`on: 1`<br>`mat: 1` |

---

#### 限制條件

- 單詞只由英文字母組成，以一個空格分隔
- 不分大小寫（`The` 與 `the` 視為同一單詞）

---

#### 提示

<details>
<summary>顯示提示 1</summary>

用 `while` + `find(" ")` 的方式逐一切割單詞（參考語法教學 5-4），每次取出一個單詞後，存入 `map<string, int>` 累計計數。

</details>

<details>
<summary>顯示提示 2</summary>

`map` 無法直接依 value 排序，可以將 `map` 的內容複製到 `vector<pair<string, int>>`，再用 `sort()` 搭配自訂比較函式排序。

</details>

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

void wordFrequency(const string& sentence) {
    map<string, int> freq;
    string s = sentence;

    // Step 1：切割單詞並統計頻率
    string delimiter = " ";
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != string::npos) {
        string word = s.substr(0, pos);
        // 轉小寫
        for (char& c : word) c = tolower(c);
        freq[word]++;
        s.erase(0, pos + delimiter.size());
    }
    // 處理最後一個單詞
    for (char& c : s) c = tolower(c);
    freq[s]++;

    // Step 2：複製到 vector 排序
    vector<pair<string, int>> sorted_freq(freq.begin(), freq.end());
    sort(sorted_freq.begin(), sorted_freq.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;  // 次數多的排前面
         });

    // Step 3：輸出
    for (const auto& p : sorted_freq) {
        cout << p.first << ": " << p.second << "\n";
    }
}

int main() {
    wordFrequency("the cat sat on the mat the cat");
    return 0;
}
// 輸出：
// the: 3
// cat: 2
// mat: 1
// on: 1
// sat: 1
```

**說明：**
1. `map<string, int>` 自動處理鍵的唯一性，`freq[word]++` 若 key 不存在會自動初始化為 0 再加 1。
2. Lambda 表達式（Lambda Expression）`[](auto& a, auto& b){ return a.second > b.second; }` 作為自訂排序依據。
3. 整體時間複雜度：$O(n \log n)$，其中 $n$ 為單詞數。

</details>

---

## 現在試試看

完成三題後，挑戰延伸問題：

- **延伸 1**：修改練習題 1，改為統計每種母音各出現幾次（輸出 `a:2, e:1, ...`）。
- **延伸 2**：修改練習題 2，讓函式同時回傳「最長的回文子字串」。
- **延伸 3**：修改練習題 3，額外支援忽略標點符號（如逗號、句號）的輸入。